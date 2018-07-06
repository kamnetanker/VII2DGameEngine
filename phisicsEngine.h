#pragma once 
#include "GeometricEngine.h"
class Object {//������� ����� ��������(��� ������� ���������)
public:
	Sprite Spr;//�������������� �������� 
	PointDot *OriginPoint;//������� ��� ���������
	PointDot Position;
	float angle;
	void SetTexture(Texture&t) {//��������� ��������
		Spr.setTexture(t);
	}
	void SetPosition(int x = 0, int y = 0) {//��������� ��������� ��������
		Spr.setPosition(x, y);
		this->Position.x = x;
		this->Position.y = y;
	}
	void SetPosition() {//��������� ��������� ��������, �������� �������� ���������
		Spr.setPosition(this->Position.x, this->Position.y);
	}
	void SetRotation(float angle) {//��������� �������� �� ���� angle ������ ������� �������, ������� � 3:00
		Spr.setRotation(angle);
		this->angle = angle;
	}
	void Draw(RenderWindow&window) {//������� ���������.
		window.draw(this->Spr);
	}
};
class PhisicsObject:public Object {
public:
	Straight *Collider;//������ �� ������� ����� �������������� ������ �������
	float Mass;//����� �������
	float Upr;//���������(������ �� ������ �� ������������) 
	bool isNewton;//�������� �� ������ ������������(��������� �� �� ���� ����(�������� ����������))
	Vector2D Speed;//����������� (i, k) � �������� (mod) ��������
	//what to do list
	//����������� ������� ������� �� angle
	//��������� ���� �������.(���� ����� ������� �������� � �������� ������� � �����������)
	//����������� ����������� ������� ������������ �������.
	//��� �������� ����������� �������, �� ����������� � ������ �������� ����������� ������.
	//�������������� ���������� ��������� ���� �� �������� �������
	//�������� ������������ �� �������������� ���������.
};