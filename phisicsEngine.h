#pragma once 
#include "GeometricEngine.h"
class Object {//Главный класс объектов(для удобной отрисовки)
public:
	Sprite Spr;//Отрисовываемая текстура 
	PointDot OriginPoint;//главная ось персонажа
	PointDot Position;
	float width;
	float height;
	float angle;
	void SetTexture(Texture&t) {//Установка текстуры
		this->Spr.setTexture(t);
		this->width = t.getSize().x;
		this->height = t.getSize().y;
	}
	void SetPosition(int x = 0, int y = 0) {//Установка положения Текстуры
		this->Spr.setPosition(x, y);
		this->Position.x = x;
		this->Position.y = y;
	}
	void SetPosition() {//Установка положения Текстуры, согласно текущему положению
		this->Spr.setPosition(this->Position.x, this->Position.y);
	}
	void SetRotation(float angle) {//Установка вращения на угол angle против часовой стрелки, начиная с 3:00
		this->Spr.setRotation(angle);
		this->angle = angle;
	}
	void Draw(RenderWindow&window) {//Функция отрисовки.
		window.draw(this->Spr);
	}
	void SetOrigin(float x, float y) {//установка центральной оси относительно координат объекта
		this->Spr.setOrigin(this->Spr.getPosition().x+x, this->Spr.getPosition().y+y);
		this->OriginPoint.x = x;
		this->OriginPoint.y = y;
	}
};
class PhisicsObject:public Object {
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
	void NextPos() {
		for (int i = 0; i < this->Normals; i++) {
			this->Collider[i] += this->Speed;
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
			if(this->Collider[i].cross(Arg))return true;
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
	//функция движения
};
//создать класс raycast