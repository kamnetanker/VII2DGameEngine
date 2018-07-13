#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <cmath>
#define M 60//�������� �����
#define G 600//���������� � ��������
#define F 0.00833//����� � ��������
#define N 0//���������� ����������� �����������
int scaleWindow = 0; //��������� �������� �������� ������������ �������� ������
using namespace std;
using namespace sf;
//����������� ������������������ �������, ���� �������� ������ ����.
float sinArr[6280];//�������� ������������������ ������� � �������� � ����� 0.001 �������
float cosArr[6280];
float tgArr[6280];
float ctgArr[6280];
void TrigPredr() {//������� ������������ ��������.
	for (float i = 0; i <= 6.28; i += 0.001) {
		sinArr[(int)(i / 0.001)] = sin(i);
		cosArr[(int)(i / 0.001)] = cos(i);
		tgArr[(int)(i / 0.001)] = sinArr[(int)(i / 0.001)]/ cosArr[(int)(i / 0.001)];
		ctgArr[(int)(i / 0.001)] = 1/ tgArr[(int)(i / 0.001)];
	}
}