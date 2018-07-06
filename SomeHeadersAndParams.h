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