#pragma once 
#include "GeometricEngine.h"
View ViewPoint;
void SetNewView(float x, float y) {
	ViewPoint.setCenter(x + 100, y); 
}

class Coords {
public:
	Texture mapT;
	Sprite mapS;
	PointDot pos;//������� ������������ ������ �������� ���� ������
	Straight **colission;
	PointDot **pd;
	int countCoords = 0; 
	int countPD=0;
	Coords(string texM, int x = 0, int y = 0, string map = "map1.data"){
		this->mapT.loadFromFile(texM);
		this->mapT.setSmooth(false);
		this->mapS.setTexture(this->mapT);
		this->pos.x = x;
		this->pos.y = y;
		ifstream fin;
		fin.open(map);
		bool isx = true;
		char tmp;
		fin >> tmp;
		while (!fin.eof()) {
			if (tmp == '(') {
				if (countCoords == 0) {
					this->countCoords++;
					this->countPD = 1;
					this->pd = (PointDot**)malloc(sizeof(PointDot*) * countCoords);
					this->pd[countCoords - 1] = (PointDot*)malloc(sizeof(PointDot) * countPD);
				}
				else {
					this->countCoords++;
					this->countPD = 1;
					this->pd = (PointDot**)realloc(this->pd, sizeof(PointDot*) * countCoords);
					this->pd[countCoords - 1] = (PointDot*)malloc(sizeof(PointDot) * countPD);
				}

				while (tmp != ')') {
					if ((tmp - '0') >= 0 && (tmp - '0') <= 9) {
						int i = 0, tmpI = 0;
						while (tmp != ','&&tmp != ';') {
							tmpI = tmpI * 10 + (tmp - '0');
							fin >> tmp;
							if (tmp == ',')isx = false;
							if (tmp == ';')isx = true;
						}
						if (!isx)this->pd[countCoords - 1][countPD - 1].x = tmpI;
						else this->pd[countCoords - 1][countPD - 1].y = tmpI;
						this->pd[countCoords - 1][countPD - 1].end = false;

					}
					if (tmp != ';')
						fin >> tmp;
					if (tmp == ';') {
						fin >> tmp;
						if ((tmp - '0') >= 0 && (tmp - '0') <= 9) {
							this->countPD++;
							this->pd[countCoords - 1] = (PointDot*)realloc(pd[countCoords - 1], sizeof(PointDot) * countPD);
						}
					}

					if (tmp == ')') {
						this->pd[countCoords - 1][countPD - 1].end = true;
					}
				}
			}

			fin >> tmp;
			//������ ���� ������ �����������, �� � ������� ���� 13.03.2018, �� �������� 15.03.2018

		}
		 
		fin.close();
		this->colission = new Straight*[this->countCoords];
		for (int i = 0; i < this->countCoords; i++) {
			this->colission[i] = new Straight[this->countPD];
		 }
		for (int i = 0; i < this->countCoords; i++) {
			for (int k = 0; ; k++) {
				if(this->pd[i][k+1].end!=true)
				this->colission[i][k] = Straight(this->pd[i][k], this->pd[i][k+1]);
				else {
					this->colission[i][k] = Straight(this->pd[i][k], this->pd[i][0]);
					break;
				}
			}
		}
	}
};
Coords CureMapLvl("map.png", 0, 0);
class Object {//������� ����� ��������(��� ������� ���������)
public:
	Sprite Spr;//�������������� �������� 
	PointDot OriginPoint;//������� ��� ���������
	PointDot Position;
	float width;
	float height;
	float angle;
	bool isCharackter = false;
	void SetTexture(Texture&t) {//��������� ��������
		this->Spr.setTexture(t);
		this->width = t.getSize().x;
this->height = t.getSize().y;
	}
	void SetPosition(int x, int y = 0) {//��������� ��������� �� �����������
		this->Spr.setPosition(x + CureMapLvl.pos.x, y + CureMapLvl.pos.y);
		this->Position.x = x;
		this->Position.y = y;
	}
	void SetPosition() {//��������� ��������� �� ����������� 
		this->Spr.setPosition(this->Position.x + CureMapLvl.pos.x, this->Position.y + CureMapLvl.pos.y); 
	}
	void SetRotation(float angle) {//��������� �������� �� ���� angle ������ ������� �������, ������� � 3:00
		this->Spr.setRotation(angle);
		this->angle = angle;
	}
	void Draw(RenderWindow&window) {//������� ���������.
		window.draw(this->Spr);
	}
	void SetOrigin(float x, float y) {//��������� ����������� ��� ������������ ��������� �������
		this->Spr.setOrigin(this->Spr.getPosition().x + x, this->Spr.getPosition().y + y);
		this->OriginPoint.x = x;
		this->OriginPoint.y = y;
	}
};
class PhisicsObject :public Object {
public:
	Straight *Collider;//������ �� ������� ����� �������������� ������ �������
	float Mass;//����� �������
	float Upr;//���������(������ �� ������ �� ������������)  
	bool isGravity; //��������� �� �� ������ ����������
	bool isRagdoll; //��������� �� �� ������ ������ ����
	Vector2D Speed;//����������� (i, k) � �������� (mod) ��������
	int Normals = 4;
	//what to do list
	//������� ������� �� angle
	PhisicsObject() {
		this->Collider = new Straight[4];
		PointDot a = PointDot(this->Spr.getPosition().x, this->Spr.getPosition().y);
		a.SetPosition(a.x + this->width, a.y);
		PointDot b = a;
		this->Collider[0] = Straight(a, b);
		a = b;
		b.SetPosition(b.x, b.y + this->height);
		this->Collider[1] = Straight(a, b);
		a = b;
		b.SetPosition(b.x - this->width, b.y);
		this->Collider[2] = Straight(a, b);
		a = b;
		b.SetPosition(b.x, b.y - this->height);
		this->Collider[3] = Straight(a, b);
	}
	void RotateToAngle(float angle) {
		this->Speed.Rotate(angle);
	}

	//��������� ���� �������.(���� ����� ������� �������� � �������� ������� � �����������)
	float cosAngleVec(Straight &Arg) {//��������� �������� ���� ����� �������� �������� � �������� � ������������ ����������.
		return this->Speed.i*Arg.A1 + this->Speed.k*Arg.B1;
	}
	float AngleVec(Straight &Arg) {//��������� ���� ����� �������� �������� � �������� � ������������ ����������.
		return acos(this->Speed.i*Arg.A1 + this->Speed.k*Arg.B1);
	}
	//����������� ����������� ������� ������������ �������.
	void RotateDropSpeedAngle(Straight &Arg) {
		float Angle = 6.28 - 2 * this->AngleVec(Arg); //�������� ���� ��������
		this->Speed.Rotate(Angle);
	}
	//��� �������� ����������� �������, �� ����������� � ������ �������� ����������� ������.
	//�������������� ���������� ��������� ���� �� �������� �������
	void NextPos(float&arg) {
		for (int i = 0; i < this->Normals; i++) {
			this->Collider[i] += this->Speed*arg;
		}
	}
	void CancelMove() {//������ �����������, ���� ��������� ������������
		for (int i = 0; i < this->Normals; i++) {
			this->Collider[i] -= this->Speed;
		}
	}
	//�������� ������������ �� �������������� ���������.
	bool Across(Straight&Arg) {
		for (int i = 0; i < this->Normals; i++) {
			if (this->Collider[i].cross(Arg))return true;
		}
		return false;
	}
	//��������� �������� �������
	Vector2D getImpulse() {
		return this->Speed*Mass;
	}
	//������� �������� � ���������� ��������.
	void setImpulse(Vector2D&Arg) {
		this->Speed = Arg;
		this->Speed.mod /= this->Mass;
	}
	//���������� � ����� ��� �������� ��������� ������
	bool CollisionWithNearest() {
		float myPosX = this->Position.x + this->width / 2;
		for (int i = 0; i < CureMapLvl.countCoords; i++) {
			for (int k = 0; i < CureMapLvl.countPD; i++) { 
					if (abs(myPosX - CureMapLvl.colission[i][k].Ox1) < 500 || abs(myPosX - CureMapLvl.colission[i][k].Ox2) < 500){
						if (this->Across(CureMapLvl.colission[i][k]))return true;
					} 
			}
		}
		return false;
	}
	//������� ��������
	void Move(float&arg) {
		this->NextPos(arg);
		if (this->CollisionWithNearest()) {//���� ������������, �� �������� �����������

			this->CancelMove();
		}
		else if(this->isCharackter==false){//���� �� ��������
			this->Position.x += this->Speed.i*this->Speed.mod*arg;
			this->Position.y += this->Speed.k*this->Speed.mod*arg;
			this->SetPosition();
		}
		else {
			this->Position.x += this->Speed.i*this->Speed.mod*arg;
			this->Position.y += this->Speed.k*this->Speed.mod*arg; 
			SetNewView(this->Position.x, this->Position.y);
		}
	}
};
//������� ����� raycast
class Raycast {


};
//����� Phisics engine
class phisicsEngine {
public: 
	void Gravity(PhisicsObject&arg) {//�������� ����������

	}
	


};