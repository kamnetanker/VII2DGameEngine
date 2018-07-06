#pragma once 
#include "GeometricEngine.h"
class Object {//Главный класс объектов(для удобной отрисовки)
public:
	Sprite Spr;//Отрисовываемая текстура 
	PointDot *OriginPoint;//главная ось персонажа
	PointDot Position;
	float angle;
	void SetTexture(Texture&t) {//Установка текстуры
		Spr.setTexture(t);
	}
	void SetPosition(int x = 0, int y = 0) {//Установка положения Текстуры
		Spr.setPosition(x, y);
		this->Position.x = x;
		this->Position.y = y;
	}
	void SetPosition() {//Установка положения Текстуры, согласно текущему положению
		Spr.setPosition(this->Position.x, this->Position.y);
	}
	void SetRotation(float angle) {//Установка вращения на угол angle против часовой стрелки, начиная с 3:00
		Spr.setRotation(angle);
		this->angle = angle;
	}
	void Draw(RenderWindow&window) {//Функция отрисовки.
		window.draw(this->Spr);
	}
};
class PhisicsObject:public Object {
public:
	Straight *Collider;//прямые по которым будет просчитываться физика объекта
	float Mass;//масса объекта
	float Upr;//упругость(влияет на отскок от поверхностей) 
	bool isNewton;//является ли объект Ньютоновским(действуют ли на него силы(например притяжение))
	Vector2D Speed;//направление (i, k) и скорость (mod) движения
	//what to do list
	//реализовать поворот вектора на angle
	//получение угла падения.(угол между векторо движения и вектором нормали к поверхности)
	//отображение симметрично вектора относительно нормали.
	//при создании физического объекта, он добавляется в список объектов физического движка.
	//предугадывание следующего положения тела по скорости объекта
	//проверка столкновения по предугаданному положению.
};