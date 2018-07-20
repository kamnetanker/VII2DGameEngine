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
	PointDot pos;//позиция относительно левого верхнего угла экрана
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
			//иногда надо писать комментарии, но я займусь этим 13.03.2018, ну возможно 15.03.2018

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
class Object {//Главный класс объектов(для удобной отрисовки)
public:
	Sprite Spr;//Отрисовываемая текстура 
	PointDot OriginPoint;//главная ось персонажа
	PointDot Position;
	float width;
	float height;
	float angle;
	bool isCharackter = false;
	void SetTexture(Texture&t) {//Установка текстуры
		this->Spr.setTexture(t);
		this->width = t.getSize().x;
this->height = t.getSize().y;
	}
	void SetPosition(int x, int y = 0) {//установка положения по координатам
		this->Spr.setPosition(x + CureMapLvl.pos.x, y + CureMapLvl.pos.y);
		this->Position.x = x;
		this->Position.y = y;
	}
	void SetPosition() {//установка положения по координатам 
		this->Spr.setPosition(this->Position.x + CureMapLvl.pos.x, this->Position.y + CureMapLvl.pos.y); 
	}
	void SetRotation(float angle) {//Установка вращения на угол angle против часовой стрелки, начиная с 3:00
		this->Spr.setRotation(angle);
		this->angle = angle;
	}
	void Draw(RenderWindow&window) {//Функция отрисовки.
		window.draw(this->Spr);
	}
	void SetOrigin(float x, float y) {//установка центральной оси относительно координат объекта
		this->Spr.setOrigin(this->Spr.getPosition().x + x, this->Spr.getPosition().y + y);
		this->OriginPoint.x = x;
		this->OriginPoint.y = y;
	}
};
class PhisicsObject :public Object {
public:
	Straight *Collider;//прямые по которым будет просчитываться физика объекта
	float Mass;//масса объекта
	float Upr;//упругость(влияет на отскок от поверхностей)  
	bool isGravity; //действует ли на объект гравитация
	bool isRagdoll; //действуют ли на объект другие силы
	Vector2D Speed;//направление (i, k) и скорость (mod) движения
	int Normals = 4;
	//what to do list
	//поворот вектора на angle
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

	//получение угла падения.(угол между векторо движения и вектором нормали к поверхности)
	float cosAngleVec(Straight &Arg) {//получение косинуса угла между вектором скорости и нормалью к пересекаемой плоскостью.
		return this->Speed.i*Arg.A1 + this->Speed.k*Arg.B1;
	}
	float AngleVec(Straight &Arg) {//получение угла между вектором скорости и нормалью к пересекаемой плоскостью.
		return acos(this->Speed.i*Arg.A1 + this->Speed.k*Arg.B1);
	}
	//отображение симметрично вектора относительно нормали.
	void RotateDropSpeedAngle(Straight &Arg) {
		float Angle = 6.28 - 2 * this->AngleVec(Arg); //Получаем угол поворота
		this->Speed.Rotate(Angle);
	}
	//при создании физического объекта, он добавляется в список объектов физического движка.
	//предугадывание следующего положения тела по скорости объекта
	void NextPos(float&arg) {
		for (int i = 0; i < this->Normals; i++) {
			this->Collider[i] += this->Speed*arg;
		}
	}
	void CancelMove() {//отмена перемещения, если встретили столкновение
		for (int i = 0; i < this->Normals; i++) {
			this->Collider[i] -= this->Speed;
		}
	}
	//проверка столкновения по предугаданному положению.
	bool Across(Straight&Arg) {
		for (int i = 0; i < this->Normals; i++) {
			if (this->Collider[i].cross(Arg))return true;
		}
		return false;
	}
	//получение импульса объекта
	Vector2D getImpulse() {
		return this->Speed*Mass;
	}
	//перевод импульса в полученную скорость.
	void setImpulse(Vector2D&Arg) {
		this->Speed = Arg;
		this->Speed.mod /= this->Mass;
	}
	//Переменная и метод для проверки ближайших прямых
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
	//функция движения
	void Move(float&arg) {
		this->NextPos(arg);
		if (this->CollisionWithNearest()) {//если столкновение, то отменить перемещение

			this->CancelMove();
		}
		else if(this->isCharackter==false){//если не персонаж
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
//создать класс raycast
class Raycast {


};
//класс Phisics engine
class phisicsEngine {
public: 
	void Gravity(PhisicsObject&arg) {//проверка гравитации

	}
	


};