#pragma once
/*
void gravityMath(Map *map, objects *character, float time, void fo(Map&, objects&) = NULL) {

if (character->hasFulcrum == false) {
float d;
PointDot posDown = PointDot(character->GCx + character->width / 2, character->GCy + character->height);

posDown.x = loop(posDown.x);
posDown.y = loop(posDown.y);
if (posDown.y >= 768) {
posDown.y = posDown.y;
}
Straight characterMove = Straight(posDown, character->speed*time);
PointDot nearestDot;
PointDot tmpNearest;
for (int i = 0; i < map->countObj; i++) {///цикл перебора прямых опор(Fulcrum)
for (int j = 0; ; j++) {

if (map->Collider[i][j] == posDown.x) {
d = posDown.y - map->Collider[i][j].GetPos(posDown.x).y;
if (d < 5 && d>0) {
character->GCy = map->Collider[i][j].GetPos(posDown.x).y - character->height;
character->hasFulcrum = true;
character->speed = Vector2D(character->speed.i*character->speed.mod, 0);
character->follow.i = character->myFulcrum->A1;
character->follow.k = character->myFulcrum->B1;
return;
}
if (nearestDot.x == 0 && nearestDot.y == 0) {
nearestDot = characterMove*map->Collider[i][j];
if (loop(posDown.x) == loop(nearestDot.x) && loop(posDown.y) == loop(nearestDot.y)) {
character->hasFulcrum = true;
character->speed = Vector2D(character->speed.i*character->speed.mod, 0);
character->follow.i = character->myFulcrum->A1;
character->follow.k = character->myFulcrum->B1;
return;
}
if (nearestDot.x != 0 && nearestDot.y != 0) {
character->myFulcrum = &map->Collider[i][j];
}
}
else {
tmpNearest = characterMove*map->Collider[i][j];
if (Vector2D(tmpNearest, posDown).mod < Vector2D(nearestDot, posDown).mod&&tmpNearest.x == 0 && tmpNearest.y == 0) {
nearestDot = tmpNearest;
if (nearestDot.x != 0 && nearestDot.y != 0) {
character->myFulcrum = &map->Collider[i][j];
}
}
}
}
if (map->mapC[i][j + 1].end)break;


}
}
if (nearestDot.x == 0 && nearestDot.y == 0) { //исправить на ускорение
character->Move(*map, fo, F);
character->speed += character->gravity*time;
//character->GCy += (int)character->gravity.k*character->gravity.mod*time;
}
else {
character->GCy = (int)(nearestDot.y - character->height);
character->speed = Vector2D(character->speed.i*character->speed.mod, 0);
character->follow.i = character->myFulcrum->A1;
character->follow.k = character->myFulcrum->B1;
character->hasFulcrum = true;
}
}
}
backup ща менять буду 23.04.18







*/
///map test source code//////////////////////////
/*if (character.hasFulcrum == true) {
fprintf(f, "%d: Ok\n", i);
character.GCx = i+1;
character.GCy = 0;
character.hasFulcrum = false;
applyCoordsForCam(&testMap, character);
cout << i<<endl;
i++;
}
else if(character.GCy>800)
{
fprintf(f, "%d: Faild", i);
character.GCx = i+1;
character.GCy = 0;
applyCoordsForCam(&testMap, character);
cout << i << endl;
i++;
}*////////////////////////////////////////////


/*
///huinya
float Tmp = this->GCx + this->width / 2;
if (!(*(this->myFulcrum) == Tmp)&&this->hasFulcrum) {
Straight &Nearest=*myFulcrum;
PointDot A0= Nearest.GetPos(Tmp);
PointDot B0 = PointDot(Tmp, this->GCy + this->height);
float nearest = Dist(A0, B0);
float nearTmp = nearest;
for (int i = 0; i < map.countObj; i++) {///цикл перебора прямых опор(Fulcrum)
for (int j = 0; ; j++) {
if (map.Collider[i][j] == Tmp) {
PointDot A = map.Collider[i][j].GetPos(Tmp);
PointDot B = PointDot(Tmp, this->GCy + this->height);
nearTmp = Dist(A, B);
if (nearTmp < nearest) {
nearest = nearTmp;
this->myFulcrum = &map.Collider[i][j];
}
}
}
}
this->follow.i = this->myFulcrum->A1;
this->follow.k = this->myFulcrum->B1;
}










*/
//Моя старая версия библиотеки
/*
void gravityMath(Map *map, objects *character, float time, void fo(Map&, objects&) = NULL) {

if (character->hasFulcrum == false) {
float d;
bool jumpUp = false;
PointDot posDown = PointDot(character->GCx + character->width / 2, character->GCy + character->height);
if (character->speed.k < 0) {
posDown.y = character->GCy;
jumpUp = true;
}
posDown.x = loop(posDown.x);
posDown.y = loop(posDown.y);
if (posDown.x >= 925 - character->width / 2) {
posDown.y = posDown.y;
}
Straight characterMove = Straight(posDown, character->speed*time);
PointDot nearestDot;
PointDot tmpNearest;
for (int i = 0; i < map->countObj; i++) {///цикл перебора прямых опор(Fulcrum)
for (int j = 0; ; j++) {
//cout << posDown.x << endl;
if (i == 0 && j == 2 && posDown.x >= 1153) {
i = 0;
}
if (map->Collider[i][j] == posDown.x) {
d = posDown.y - map->Collider[i][j].GetPos(posDown.x).y;
if (d <= 5 && d>0) {
if (jumpUp == false) {
character->GCy = map->Collider[i][j].GetPos(posDown.x).y - character->height-1;
character->hasFulcrum = true;
character->speed = Vector2D(character->speed.i*character->speed.mod, 0);
character->follow.i = character->myFulcrum->A1;
character->follow.k = character->myFulcrum->B1;
return;
}
else {
character->speed.k = 0;
}

}
if (nearestDot.x == 0 && nearestDot.y == 0) {
nearestDot = characterMove*map->Collider[i][j];
if (loop(posDown.x) == loop(nearestDot.x) && loop(posDown.y) == loop(nearestDot.y)) {
character->hasFulcrum = true;
character->speed = Vector2D(character->speed.i*character->speed.mod, 0);
character->follow.i = character->myFulcrum->A1;
character->follow.k = character->myFulcrum->B1;
return;
}
if (nearestDot.x != 0 && nearestDot.y != 0) {
character->myFulcrum = &map->Collider[i][j];
}
}
else {
tmpNearest = characterMove*map->Collider[i][j];
if (Vector2D(tmpNearest, posDown).mod < Vector2D(nearestDot, posDown).mod&&tmpNearest.x == 0 && tmpNearest.y == 0) {
nearestDot = tmpNearest;
if (nearestDot.x != 0 && nearestDot.y != 0) {
character->myFulcrum = &map->Collider[i][j];
}
}
}
}
if (map->mapC[i][j + 1].end)break;


}
}

if (nearestDot.x == 0 && nearestDot.y == 0) { //исправить на ускорение
character->Move(*map, fo, F);
character->speed += character->gravity*time;
//character->GCy += (int)character->gravity.k*character->gravity.mod*time;
}
else {
if (jumpUp == false) {
character->GCy = (int)(nearestDot.y - character->height);
character->speed = Vector2D(character->speed.i*character->speed.mod, 0);
character->follow.i = character->myFulcrum->A1;
character->follow.k = character->myFulcrum->B1;
character->hasFulcrum = true;
}else character->speed.k = 0;
}
}
}





















#pragma warning (disable : 4996)
#include "phisics.h"
int CollSize = 10;
int curePos = 0;
int cureDraw=0;
///////////////////////////////////////////////////////////////////////ФУНКЦИИ ДВИЖЕНИЯ И ФИЗИКА



//////////////////////////////////////////////////////////////////////
int main()
{
//FILE *f = fopen("test.txt", "w+");

RenderWindow window(VideoMode(1280, 720), "SFML is Fun");

///////////////////////////////////////////////////////////////// создание объекта текстуры
Map testMap=Map("map.png" ,0, 0);
testMap.mapS.setPosition(testMap.locX, testMap.locY);
objects character = objects(testMap, "character0.png",  window.getSize().x / 2 ,   window.getSize().y * 3 / 4  , 0);
//character.hasFulcrum = true;
objects* another = new objects[N];
for (int j = 0; j < N; j++) {
another[j] = objects(testMap, "character0.png", 0,0);
another[j].spr.setTexture(character.tex);
another[j].GCx = j;
}
cout << character.width;
Clock clock;
int i = 0;
void(*fo)(Map&, objects&) = NULL;
fo = &applyCoordsForCam;

/////////////////////////////////////////////////////////////////часть отрисовки
while (window.isOpen()) {
float time = clock.getElapsedTime().asSeconds();

//cout << time << endl;


Event event;
while (window.pollEvent(event)) {
if (event.type == Event::Closed) {
window.close();
}
}


window.clear();
if (time >= F) {
clock.restart();
//////////////////////////////////////////////тело программы
//cout << character.GCy<<endl;

if (Keyboard::isKeyPressed(Keyboard::D) && character.hasFulcrum) {//обработка нажатия клавиши D
if (character.follow.i > 0) {
character.speed = character.follow*character.Vspeed;
}
else {
character.speed = character.follow*character.Vspeed;
character.speed *= -1;
}
}
if (Keyboard::isKeyPressed(Keyboard::A) && character.hasFulcrum) {//обработка нажатия клавиши D
if (character.follow.i > 0) {
character.speed = character.follow*character.Vspeed;
character.speed *= -1;
}
else {
character.speed = character.follow*character.Vspeed;
}
}
if (Keyboard::isKeyPressed(Keyboard::Space) && character.hasFulcrum) {
character.jump();
}


gravityMath(&testMap, &character, F,fo);

character.Move(testMap, fo, F);



window.draw(testMap.mapS);
for (int j = 0; j < N; j++) {
gravityMath(&testMap, &another[j], F,fo);
// if (another[j].hasFulcrum == true) {
// another[j].hasFulcrum = false;
//another[j].GCx = 10*j;
//another[j].GCy = 0;

// }
if (another[j].hasFulcrum&&another[j].right) {
another[j].speed = another[j].follow*another[j].Vspeed;
another[j].speed *= -1;
}
if (another[j].hasFulcrum&&!another[j].right) {
another[j].speed = another[j].follow*another[j].Vspeed;

}
if (another[j].GCx < 100&& another[j].right == false) {
another[j].right = true;
}
if (another[j].GCx >= 1800&& another[j].right ==true) {
another[j].hasFulcrum = false;
another[j].GCy = 0;
another[j].speed.k = 1;
another[j].speed.i = 0;
another[j].speed.mod = G;
another[j].right = false;
}
if(another[j].hasFulcrum)
another[j].jump();
another[j].Move(testMap, fo, F);
window.draw(another[j].spr);
}
window.draw(Circle1);
window.draw(Circle2);
window.draw(character.spr);
///////////////////////////////////////////// дисплей только тут

window.display();
}
}
return 0;
}


































*/