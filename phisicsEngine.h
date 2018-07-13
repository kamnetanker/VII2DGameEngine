#pragma once 
#include "GeometricEngine.h"
class Object {//������� ����� ��������(��� ������� ���������)
public:
	Sprite Spr;//�������������� �������� 
	PointDot OriginPoint;//������� ��� ���������
	PointDot Position;
	float width;
	float height;
	float angle;
	void SetTexture(Texture&t) {//��������� ��������
		this->Spr.setTexture(t);
		this->width = t.getSize().x;
		this->height = t.getSize().y;
	}
	void SetPosition(int x = 0, int y = 0) {//��������� ��������� ��������
		this->Spr.setPosition(x, y);
		this->Position.x = x;
		this->Position.y = y;
	}
	void SetPosition() {//��������� ��������� ��������, �������� �������� ���������
		this->Spr.setPosition(this->Position.x, this->Position.y);
	}
	void SetRotation(float angle) {//��������� �������� �� ���� angle ������ ������� �������, ������� � 3:00
		this->Spr.setRotation(angle);
		this->angle = angle;
	}
	void Draw(RenderWindow&window) {//������� ���������.
		window.draw(this->Spr);
	}
	void SetOrigin(float x, float y) {//��������� ����������� ��� ������������ ��������� �������
		this->Spr.setOrigin(this->Spr.getPosition().x+x, this->Spr.getPosition().y+y);
		this->OriginPoint.x = x;
		this->OriginPoint.y = y;
	}
};
class PhisicsObject:public Object {
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
	PhisicsObject(){
		this->Collider = new Straight[4];
		PointDot a = PointDot(this->Spr.getPosition().x, this->Spr.getPosition().y);
		a.SetPosition(a.x+this->width, a.y);
		PointDot b = a;
		this->Collider[0] = Straight(a, b);
		a = b;
		b.SetPosition(b.x, b.y+this->height);
		this->Collider[1] = Straight(a, b);
		a = b;
		b.SetPosition(b.x-this->width, b.y);
		this->Collider[2] = Straight(a, b);
		a = b;
		b.SetPosition(b.x, b.y-this->height);
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
	void NextPos() {
		for (int i = 0; i < this->Normals; i++) {
			this->Collider[i] += this->Speed;
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
			if(this->Collider[i].cross(Arg))return true;
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
	//������� ��������
};
//������� ����� raycast