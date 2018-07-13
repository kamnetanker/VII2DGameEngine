#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <cmath>
#define M 60//Стандарт метра
#define G 600//гравитация в пикселях
#define F 0.00833//время в секундах
#define N 0//количество изначальных балванчиков
int scaleWindow = 0; //изменение размеров объектов соответствуя размерам экрана
using namespace std;
using namespace sf;
//Предрассчет тригонометрический функций, дабы ускорить работу игры.
float sinArr[6280];//значения тригонометрических функций в радианах с шагом 0.001 радиана
float cosArr[6280];
float tgArr[6280];
float ctgArr[6280];
void TrigPredr() {//функция предрассчета значений.
	for (float i = 0; i <= 6.28; i += 0.001) {
		sinArr[(int)(i / 0.001)] = sin(i);
		cosArr[(int)(i / 0.001)] = cos(i);
		tgArr[(int)(i / 0.001)] = sinArr[(int)(i / 0.001)]/ cosArr[(int)(i / 0.001)];
		ctgArr[(int)(i / 0.001)] = 1/ tgArr[(int)(i / 0.001)];
	}
}