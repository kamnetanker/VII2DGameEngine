#pragma once
#include "SomeHeadersAndParams.h"
///////////////////////////////////////////////////////////////////////КЛАССЫ И СТРУКТУРЫ ОБЪЕКТОВ
CircleShape Circle1 = CircleShape(5);
CircleShape Circle2 = CircleShape(5);
float loop(float &a) {
	if ((a - (int)a) <= 0.5) {
		return floor(a);
	}
	else {
		return ceil(a);
	}

}
struct mapCoords {//структура отвечающая за координаты твёрдых тел
	int x;
	int y;
	bool end = false; 
};
class PointDot {//класс, отвечающий за точку
public:
	float x;
	float y; 
	PointDot(float x, float y) {
		this->x = x;
		this->y = y;
	}
	PointDot( ) {
		this->x = 0;
		this->y = 0;
	} 
	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
};
float Dist(PointDot a, PointDot b) {
	return 1.41*((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y)) / (abs(b.x - a.x) + abs(b.y - a.y));
}

class Vector2D {//класс вектора. пояснения не требуются
public:
	float i, k; //координаты единичного вектора 
	float mod;//модуль вектора
	Vector2D(float x, float y) {
		if (x != 0 ||y != 0) {
			this->mod = sqrt(x*x + y*y);
			this->i = x / mod;
			this->k = y / mod;
		}
		else {
			this->mod = 0;
			this->i = 0;
			this->k = 0;

		}
	}
	 
	Vector2D(PointDot a, PointDot b) {
		float x = a.x - b.x;
		float y = a.y - b.y;
		if (x != 0 || y != 0) {
			this->mod = sqrt(x*x + y*y); 
			this->i = x / mod;
			this->k = y / mod;
		}
		else {
			this->mod = 0;
			this->i = 0;
			this->k = 0;

		}
	}

	Vector2D() {
		this->mod = 0;
		this->i = 0;
		this->k = 0;
	}
	Vector2D operator +(Vector2D &a) {
		Vector2D res = Vector2D(this->mod*this->i + a.mod*a.i, this->mod*this->k + a.mod*a.k);
		return res;
	}
	void operator +=(Vector2D &a) {
		*this = Vector2D(this->mod*this->i + a.mod*a.i, this->mod*this->k + a.mod*a.k);

	}
	Vector2D operator -(Vector2D &a) {
		Vector2D res = Vector2D(this->mod*this->i - a.mod*a.i, this->mod*this->k - a.mod*a.k);
		return res;
	}
	void operator -=(Vector2D &a) {
		*this = Vector2D(this->mod*this->i - a.mod*a.i, this->mod*this->k - a.mod*a.k);

	}
	Vector2D operator *(float &a) {
		Vector2D res = Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a);
		return res;
	}
	Vector2D operator *(double &a) {
		Vector2D res = Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a);
		return res;
	}
	void operator *=(float &a) {
		*this = Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a);

	}
	void operator *=(float a) {
		*this = Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a);

	}
	Vector2D operator /(float &a) {
		Vector2D res = Vector2D((this->mod*this->i) / a, (this->mod*this->k) / a);
		return res;
	}
	void operator /=(float &a) {
		*this = Vector2D((this->mod*this->i) / a, (this->mod*this->k) / a);
	}
	void operator =(Vector2D &a) {
		this->mod = a.mod;
		this->i = a.i;
		this->k = a.k;
	}

};
class Straight {
public:
	float A, B, D, Ox1, Ox2, Oy1, Oy2;  
	float A1, B1;
	Straight() {
		this->A = 0;
		this->B = 0;
		this->D = 0;
		this->Ox1 = 0;
		this->Ox2 = 0;
		this->Oy1 = 0;
		this->Oy2 = 0;
		this->A1 = 0;
		this->B1 = 0;
	}
	Straight(float x1, float y1, float x2, float y2, float Ox1 = 0, float Ox2 = 0, float Oy1 = 0, float Oy2 = 0) {
		if (Ox1 == 0 && Ox2 == 0 && Oy1 == 0 && Oy2 == 0) {
			Ox1 = x1;
			Ox2 = x2;
			Oy1 = y1;
			Oy2 = y2;
		}
		this->A = y2 - y1;
		this->B = -1 * (x2 - x1);
		this->D = -1 * (A*x1 + B*y1);
		this->Ox1 = Ox1;
		this->Ox2 = Ox2;
		this->Oy1 = Oy1;
		this->Oy2 = Oy2;
		if (this->Ox2 < this->Ox1) {
			float tmp = this->Ox1;
			this->Ox1 = this->Ox2;
			this->Ox2 = tmp;
		}
		if (this->Oy2 < this->Oy1) {
			float tmp = this->Oy1;
			this->Oy1 = this->Oy2;
			this->Oy2 = tmp;
		}
	}
	Straight(PointDot &a, PointDot &b) { 
		Vector2D AB = Vector2D(a, b);
		this->A = -1*AB.k*AB.mod;
		this->A1 = AB.i;
		this->B = AB.i*AB.mod;
		this->B1 = AB.k;
		this->D = -1 * (A*a.x + B*a.y);
		/*не уверен в работоспособности этого кода, по этому перепишу чуть более новый код. выше
		this->A = a.y - b.y;
		this->B = -1 * (b.x - a.x);
		*/
		this->Ox1 = a.x;
		this->Ox2 = b.x;
		this->Oy1 = a.y;
		this->Oy2 = b.y;
		if (this->Ox2 < this->Ox1) {
			float tmp = this->Ox1;
			this->Ox1 = this->Ox2;
			this->Ox2 = tmp;
		}
		if (this->Oy2 < this->Oy1) {
			float tmp = this->Oy1;
			this->Oy1 = this->Oy2;
			this->Oy2 = tmp;
		}
	}
	Straight(PointDot &a, Vector2D &b) {
		this->A = -1 * b.k*b.mod;
		this->B = b.i*b.mod;
		this->A1 =  b.k;
		this->B1 = -1*b.i;
		this->D = -1 * (A*a.x + B*a.y);
		this->Ox1 = a.x;
		this->Ox2 = a.x + b.i*b.mod;
		this->Oy1 = a.y;
		this->Oy2 = a.y + b.k*b.mod;
		if (this->Ox2 < this->Ox1) {
			float tmp = this->Ox1;
			this->Ox1 = this->Ox2;
			this->Ox2 = tmp;
		}
		if (this->Oy2 < this->Oy1) {
			float tmp = this->Oy1;
			this->Oy1 = this->Oy2;
			this->Oy2 = tmp;
		}
	}
	PointDot operator*(Straight &A) {
		float x, y;
		if (loop(this->A) == loop(A.A)&&loop(this->B) == loop(A.B)) {
			return PointDot(0,0);
		}
		if (loop(this->A) == 0) {
			y = -1*this->D / this->B;
			y = loop(y);
		}
		else if (loop(A.A) == 0) {
			y = -1*A.D / A.B;
			y = loop(y);
		}
		else if(this->B*A.A - this->A*A.B !=0){
			y = (this->A*A.D-this->D*A.A) / (this->B*A.A-this->A*A.B);
			y = loop(y);
		}
		else {
			return PointDot(0, 0);
		}
		if (A.A != 0) {
			x = -1 * (A.B*y + A.D) / A.A;
			x = loop(x);
		}
		else if(this->A!=0) {
			x = -1 * (this->B*y + this->D) / this->A;
			x = loop(x);
		}
		else {
			return PointDot(0, 0);
		}
		if (x >= loop(this->Ox1)&&x <= loop(this->Ox2)&&y >= loop(this->Oy1)&&y <= loop(this->Oy2)&&x >= loop(A.Ox1)&&x <= loop(A.Ox2)&&y >=loop(A.Oy1)&&y <= loop(A.Oy2)) {
			return PointDot(x, y);
		}
		else
		{
			return PointDot(0, 0);
		} 
	}
	bool operator==(PointDot &a) {
		return this->A*a.x + this->B*a.y + D == 0;
	}
	bool operator==(float &a) {
		return (this->Ox1<=a&&this->Ox2>=a);
	}
	 
	PointDot GetPos(float x) { 
		if (this->A == 0) {
			return PointDot(x, (this->D / this->B)*-1);
		}
		if (this->B == 0) {
			return PointDot(x, (this->D / this->A)*-1);
		}
		float y =- 1 * (((this->A / this->B)*x) + (this->D / this->B));
		return PointDot(x, y);
	}

};
class Level {
public:
	int CountStraight;
	Straight *pStraight;
	Level() {
		this->pStraight = new Straight[1];
		this->CountStraight = 0;
	}
	Straight* Resize() {
		Straight *tmp = new Straight[this->CountStraight];
		for (int i = 0; i < this->CountStraight - 1; i++)tmp[i] = this->pStraight[i];
		return tmp;
	}
	void Add(Straight *pStraight) {
		this->CountStraight++;
		this->pStraight = this->Resize();
		this->pStraight[this->CountStraight - 1] = *pStraight;
	}
};
Level *cureLevel;
class Map {//класс карты никто не наследует, он содержит лишь локальные координаты, спрайт отрисовки и массив координат для обработки столкновения
public:
	int locX, locY;
	Texture mapT;
	Sprite mapS;
	mapCoords **mapC;
	Straight **Collider;
	int countObj = 0;
	int countCoords = 0;
	Map(string texM, int x = 0, int y = 0, string map = "map1.data") {
		cureLevel = new Level();
		this->mapT.loadFromFile(texM);
		this->mapT.setSmooth(false);
		this->mapS.setTexture(this->mapT);
		this->locX = x;
		this->locY = y;
		ifstream fin;
		fin.open(map);
		bool isx = true;
		char tmp;
		fin >> tmp;
		while (!fin.eof()) {
			if (tmp == '(') {
				if (countObj == 0) {
					this->countObj++;
					this->countCoords = 1;
					this->mapC = (mapCoords**)malloc(sizeof(mapCoords*) * countObj);
					this->mapC[countObj - 1] = (mapCoords*)malloc(sizeof(mapCoords) * countCoords);
				}
				else {
					this->countObj++;
					this->countCoords = 1;
					this->mapC = (mapCoords**)realloc(mapC, sizeof(mapCoords*) * countObj);
					this->mapC[countObj - 1] = (mapCoords*)malloc(sizeof(mapCoords) * countCoords);
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
						if (!isx)this->mapC[countObj - 1][countCoords - 1].x = tmpI;
						else this->mapC[countObj - 1][countCoords - 1].y = tmpI;
						this->mapC[countObj - 1][countCoords - 1].end = false;

					}
					if (tmp != ';')
						fin >> tmp;
					if (tmp == ';') {
						fin >> tmp;
						if ((tmp - '0') >= 0 && (tmp - '0') <= 9) {
							this->countCoords++;
							this->mapC[countObj - 1] = (mapCoords*)realloc(mapC[countObj - 1], sizeof(mapCoords) * countCoords);
						}
					}

					if (tmp == ')') {
						this->mapC[countObj - 1][countCoords - 1].end = true;
					}
				}
			}

			fin >> tmp;
			//иногда надо писать комментарии, но я займусь этим 13.03.2018, ну возможно 15.03.2018

		}

		/*for (int i = 0; i < countObj; i++) {///цикл перебора координат опор(Fulcrum)
		for (int j = 0; ; j++) {
		cout << mapC[i][j].x << " " << mapC[i][j].y << endl;
		if (mapC[i][j].end)break;
		}
		}*/
		fin.close();
		this->Collider = (Straight**)malloc(sizeof(Straight*)*this->countObj);
		for (int i = 0; i < this->countObj; i++) {///цикл перебора координат опор(Fulcrum)
			for (int j = 0; ; j++) {
				if(j==0)this->Collider[i]=(Straight*)malloc(sizeof(Straight)*1);
				else this->Collider[i] = (Straight*)realloc(this->Collider[i], sizeof(Straight) * (j+1));
				this->Collider[i][j] = Straight(PointDot(this->mapC[i][j].x, this->mapC[i][j].y), PointDot(this->mapC[i][j + 1].x, this->mapC[i][j + 1].y));
				cureLevel->Add(&this->Collider[i][j]);
				if (mapC[i][j+1].end)break;
			}
		}
	}

};

class objects {//родительский класс для всех остальных объектов, кроме карты, карта является самостоятельным объектом.
public:
	float LCx, LCy, GCx, GCy;//локальные координаты по х у соответственно и глобальные соответственно
	bool hasFulcrum;//есть ли опора
	Vector2D speed;
	float Vspeed;
	Vector2D gravity;
	Vector2D follow;
	Texture tex;
	Sprite spr;
	Straight *myFulcrum;
	bool right = true;
	short int control;//кто контролирует объект. 0 - пользователь, 1 - ии, 2 - неконтроллируемый объект
	int width, height; 
	Vector2D Jump;
	PointDot posDown;
	objects(Map k, int controll = 2) {
		this->myFulcrum = &Straight(PointDot(0,0),PointDot(0,0));
		this->Vspeed = 5 * M;//Произведение метра в секунду(5) на стандарт 1 метр(60 px)
		this->speed = Vector2D(0, 0);
		this->follow= Vector2D(0, 0);
		this->gravity = Vector2D(0, G);
		this->hasFulcrum = true;
		this->LCx = 0;
		this->LCy = 0;
		this->GCx = -1 * k.locX;
		this->GCy = -1 * k.locY;
		this->control = controll;
		this->Jump = Vector2D(0, -0.5 * G);
		this->posDown= PointDot(this->GCx + this->width / 2, this->GCy + this->height);
	}
	objects(Map k, string text_e, int controll = 2) {
		this->myFulcrum = &Straight(PointDot(0, 0), PointDot(0, 0));
		this->speed = Vector2D(0, 0);
		this->gravity = Vector2D(0, G);
		this->Vspeed = 5 * M;//Произведение метра в секунду(5) на стандарт 1 метр(60 px)
		this->follow = Vector2D(0, 0);
		this->hasFulcrum = false;
		this->LCx = 0;
		this->LCy = 0;
		this->GCx = -1 * k.locX;
		this->GCy = -1 * k.locY;
		this->tex.loadFromFile(text_e);
		this->tex.setSmooth(false);
		this->spr.setTexture(this->tex);
		this->control = controll;
		this->width = this->tex.getSize().x;
		this->height = this->tex.getSize().y;
		this->Jump = Vector2D(0, -0.5 * G);
		this->posDown = PointDot(this->GCx + this->width / 2, this->GCy + this->height);
	}
	objects(Map k, string text_e, float x, float y, int controll = 2) {
		this->myFulcrum = &k.Collider[0][0];
		this->speed = Vector2D(0, 0);
		this->Vspeed = 5 * M;//Произведение метра в секунду(5) на стандарт 1 метр(60 px)
		this->gravity = Vector2D(0, G);
		this->follow = Vector2D(this->myFulcrum->A1, this->myFulcrum->B1);
		this->hasFulcrum = false;
		this->LCx = x;
		this->LCy = y;
		this->GCx = x-1 * k.locX;
		this->GCy = y-1 * k.locY;
		this->tex.loadFromFile(text_e);
		this->tex.setSmooth(false);
		this->spr.setTexture(this->tex);
		this->control = controll;
		this->spr.setPosition(LCx, LCy);
		this->width = this->tex.getSize().x;
		this->height = this->tex.getSize().y;
		this->Jump = Vector2D(0, -0.5 * G);
		this->posDown = PointDot(this->GCx + this->width / 2, this->GCy + this->height);
	}
	objects() { 
		this->myFulcrum = &Straight(PointDot(0, 0), PointDot(0, 0));
	}
	void jump() { 
		this->GCy -= 2;  
		this->speed += this->Jump;
		this->speed.mod = this->Jump.mod;
		this->hasFulcrum= false;
	}
	void Move(Map&map, void applyCoordsForCam(Map&,objects&), float t) {
		Collision(map, *this, 0.00833);
		if (SerchNext(map, *this, F)) {
			this->GCx += this->speed.i*this->speed.mod*t;
		}
		else {
			this->speed.i = 0;
		}
			this->GCx = loop(this->GCx);
			this->GCy += this->speed.k*this->speed.mod*t;
			this->GCy = loop(this->GCy);
		
		if (this->hasFulcrum) {//обнуление перемещения, если мы стоим на поверхности
			this->speed.i = 0;
			this->speed.k = 0;
		}
		float Tmp = (this->GCx + this->width / 2);
		if (this->hasFulcrum && !(*(this->myFulcrum) == Tmp)) {
			this->GCy -= 1;
			
		this->hasFulcrum = false;
			this->speed.k = 1;
			this->speed.i = 0;
			this->speed.mod = G;
		}
		 
		
		if (this->control == 0) {
			applyCoordsForCam(map, *this);
		}
		else {
			this->spr.setPosition(this->GCx + map.locX, this->GCy + map.locY);
		}
	}
	Straight* Collision(Map&map, objects&character, float t) {
		if (character.speed.i != 0 || character.speed.k != 0) {
			float &mod = character.speed.mod;
			float &i = character.speed.i;
			float &k = character.speed.k;
			float modTransI = i*mod*t;
			float modTransK = k*mod*t;
			PointDot a;//минимальное количество опорных точек соответствующих углам отсчета перемещения
			PointDot b;
			PointDot c;
			PointDot d;
			//движение вправо
			if (i > 0 && k == 0) {
				a.x = character.GCx + character.width;//a есть точка в правом верхнем угле модельки
				a.y = character.GCy;
				b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
				b.y = a.y + modTransK;
				d.x = character.GCx + character.width;//d есть точка в правом нижнем углу
				d.y = character.GCy + character.height;
				c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
				c.y = d.y + modTransK;
				Straight A1 = Straight(a, b);
				Straight A2 = Straight(b, c);
				Straight A3 = Straight(c, d); 
				for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)
					  
						a = A1*cureLevel->pStraight[i];
						if (a.x != 0 && a.y != 0) {

							Circle1.setPosition(a.x + map.locX, a.y + map.locY); 
							return &cureLevel->pStraight[i];;
						}
						a = A2*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A3*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						} 	 
				}
				return NULL;

			}
			//движение влево
			if (i<0&&k==0) {
				a.x = character.GCx;//a есть точка в левом верхнем угле модельки
				a.y = character.GCy;
				b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
				b.y = a.y + modTransK;
				d.x = character.GCx;//d есть точка в левом нижнем углу
				d.y = character.GCy + character.height;
				c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
				c.y = d.y + modTransK;
				Straight A1 = Straight(a, b);
				Straight A2 = Straight(b, c);
				Straight A3 = Straight(c, d);
				for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)

					a = A1*cureLevel->pStraight[i];
					if (a.x != 0 && a.y != 0) {

						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
					a = A2*cureLevel->pStraight[i];;
					if (a.x != 0 && a.y != 0) {
						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
					a = A3*cureLevel->pStraight[i];;
					if (a.x != 0 && a.y != 0) {
						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
				}
				return NULL;
			}
			//движение вверх
			if (i==0&&k<0) {
				a.x = character.GCx;//a есть точка в левом верхнем угле модельки
				a.y = character.GCy;
				b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
				b.y = a.y + modTransK;
				d.x = character.GCx+character.width;//d есть точка в правом верхнем углу
				d.y = character.GCy;
				c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
				c.y = d.y + modTransK;
				Straight A1 = Straight(a, b);
				Straight A2 = Straight(b, c);
				Straight A3 = Straight(c, d);
				for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)

					a = A1*cureLevel->pStraight[i];
					if (a.x != 0 && a.y != 0) {

						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
					a = A2*cureLevel->pStraight[i];;
					if (a.x != 0 && a.y != 0) {
						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
					a = A3*cureLevel->pStraight[i];;
					if (a.x != 0 && a.y != 0) {
						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
				}
				return NULL;
			}
			//движение вниз
			if (i==0&&k>0) {
				a.x = character.GCx;//a есть точка в левом нижнем угле модельки
				a.y = character.GCy+character.height;
				b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
				b.y = a.y + modTransK;
				d.x = character.GCx + character.width;//d есть точка в правом нижнем углу
				d.y = character.GCy+character.height;
				c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
				c.y = d.y + modTransK;
				Straight A1 = Straight(a, b);
				Straight A2 = Straight(b, c);
				Straight A3 = Straight(c, d);
				for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)

					a = A1*cureLevel->pStraight[i];
					if (a.x != 0 && a.y != 0) {

						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
					a = A2*cureLevel->pStraight[i];;
					if (a.x != 0 && a.y != 0) {
						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
					a = A3*cureLevel->pStraight[i];;
					if (a.x != 0 && a.y != 0) {
						Circle1.setPosition(a.x + map.locX, a.y + map.locY);
						return &cureLevel->pStraight[i];;
					}
				}
				return NULL;
			}
			if (i != 0 && k != 0) {
				PointDot e;
				PointDot f;
				if (i>0&&k<0) {//Движение вправо вверх
					a.x = character.GCx;//a есть точка в левом верхнем угле модельки
					a.y = character.GCy;
					b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
					b.y = a.y + modTransK;
					d.x = character.GCx + character.width;//d есть точка в правом верхнем углу
					d.y = character.GCy;
					c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
					c.y = d.y + modTransK;
					e.x= character.GCx+character.width;//точка в правом нижнем углу
					e.y = character.GCy + character.height;
					f.x= e.x + modTransI;//Перемещение точки e
					f.y = e.y + modTransK;
					Straight A1 = Straight(a, b);
					Straight A2 = Straight(b, c);
					Straight A3 = Straight(c, f);
					Straight A4 = Straight(f, e);
					for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)

						a = A1*cureLevel->pStraight[i];
						if (a.x != 0 && a.y != 0) {

							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A2*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A3*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A4*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						 
					}
					return NULL; 
				}

				if (i>0 && k>0) {//Движение вправо вниз
					a.x = character.GCx+character.width;//a есть точка в правом верхнем угле модельки
					a.y = character.GCy;
					b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
					b.y = a.y + modTransK;
					d.x = character.GCx + character.width;//d есть точка в правом нижнем углу
					d.y = character.GCy + character.height;
					c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
					c.y = d.y + modTransK;
					e.x = character.GCx;//точка в левом нижнем углу
					e.y = character.GCy + character.height;
					f.x = e.x + modTransI;//Перемещение точки e
					f.y = e.y + modTransK;
					Straight A1 = Straight(a, b);
					Straight A2 = Straight(b, c);
					Straight A3 = Straight(c, f);
					Straight A4 = Straight(f, e);
					for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)

						a = A1*cureLevel->pStraight[i];
						if (a.x != 0 && a.y != 0) {

							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A2*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A3*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A4*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}

					}
					return NULL;
				}
				if (i<0 && k>0) {//Движение влево вниз
					a.x = character.GCx+character.width;//a есть точка в правом нижнем угле модельки
					a.y = character.GCy+character.height;
					b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
					b.y = a.y + modTransK;
					d.x = character.GCx;//d есть точка в левом нижнем углу
					d.y = character.GCy + character.height;
					c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
					c.y = d.y + modTransK;
					e.x = character.GCx;//точка в левом верхнем углу
					e.y = character.GCy;
					f.x = e.x + modTransI;//Перемещение точки e
					f.y = e.y + modTransK;
					Straight A1 = Straight(a, b);
					Straight A2 = Straight(b, c);
					Straight A3 = Straight(c, f);
					Straight A4 = Straight(f, e);
					for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)

						a = A1*cureLevel->pStraight[i];
						if (a.x != 0 && a.y != 0) {

							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A2*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A3*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A4*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}

					}
					return NULL;
				}
				if (i<0 && k<0) {//Движение влево вверх
					a.x = character.GCx;//a есть точка в левом нижнем угле модельки
					a.y = character.GCy+character.height;
					b.x = a.x + modTransI;//b есть точка, куда переместится a в случае перемещения
					b.y = a.y + modTransK;
					d.x = character.GCx;//d есть точка в левом верхнем углу
					d.y = character.GCy;
					c.x = d.x + modTransI;//c есть точка куда переместится d в случае перемещения
					c.y = d.y + modTransK;
					e.x = character.GCx + character.width;//точка в правом верхнем углу
					e.y = character.GCy;
					f.x = e.x + modTransI;//Перемещение точки e
					f.y = e.y + modTransK;
					Straight A1 = Straight(a, b);
					Straight A2 = Straight(b, c);
					Straight A3 = Straight(c, f);
					Straight A4 = Straight(f, e);
					for (int i = 0; i < cureLevel->CountStraight; i++) {///цикл перебора прямых опор(Fulcrum)

						a = A1*cureLevel->pStraight[i];
						if (a.x != 0 && a.y != 0) {

							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A2*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A3*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}
						a = A4*cureLevel->pStraight[i];;
						if (a.x != 0 && a.y != 0) {
							Circle1.setPosition(a.x + map.locX, a.y + map.locY);
							return &cureLevel->pStraight[i];;
						}

					}
					return NULL;
				} 
			}
		}
		return NULL;
	}
	
	bool SerchNext(Map&map, objects&character, float t) {
		if (character.speed.i != 0) { 
			Straight *d;
			PointDot a1;
			PointDot a2;
			PointDot b1;
			PointDot b2;
			if (character.speed.i > 0) {
				a1.x = character.GCx + character.width;
				a1.y = character.GCy;
				a2.x = a1.x + character.speed.i*character.speed.mod*t; 
				a2.y = a1.y + character.speed.k*character.speed.mod*t; 
				b1.x = character.GCx + character.width;
				b1.y = character.GCy + character.height;
				if (character.hasFulcrum)b1.y -= character.height / 4 + 2; 
				b2.x = b1.x + character.speed.i*character.speed.mod*t; 
				b2.y = b1.y + character.speed.k*character.speed.mod*t;
				a1.y = character.GCy;
				a2.x = loop(a2.x);
				a2.y = loop(a2.y);
				b2.x = loop(b2.x);
				b2.y = loop(b2.y); 
				d = &Straight(a1, b1);
			}
			else {
				a1.x = character.GCx;
				a1.y = character.GCy;
				a2.x = a1.x + character.speed.i*character.speed.mod*t;
				a2.y = a1.y + character.speed.k*character.speed.mod*t;
				b1.x = character.GCx;
				b1.y = character.GCy + character.height;
				if (character.hasFulcrum)b1.y -= character.height/ 4 + 2;
				b2.x = b1.x + character.speed.i*character.speed.mod*t;
				b2.y = b1.y + character.speed.k*character.speed.mod*t;
				a2.x = loop(a2.x);
				a2.y = loop(a2.y);
				b1.x = loop(b1.x);
				b1.y = loop(b1.y);
				d = &Straight(a1, b1);
			}
			Straight a = Straight(a1, a2);
			Straight b = Straight(a2, b1);
			Straight c = Straight(b1, b2);
			
			for (int i = 0; i < map.countObj; i++) {///цикл перебора прямых опор(Fulcrum)
				for (int j = 0; ; j++) { 
					 
						a1 = a*map.Collider[i][j];
						a2 = b*map.Collider[i][j];
						b1 = c*map.Collider[i][j];
						if (character.hasFulcrum&&b1.x != 0 && b1.y != 0) { 
							float posY = character.GCy + character.height+ character.speed.k*character.speed.mod*t;
							posY -= character.height / 4 + 2;
							posY = loop(posY);
							character.GCy += b1.y- posY+1;
							character.hasFulcrum = false;
							character.myFulcrum = &map.Collider[i][j];
							return false;
						}
						b2 = *d*map.Collider[i][j];
						if ((a1.x != 0 && a1.y != 0 || a2.x != 0 && a2.y != 0 || b1.x != 0 && b1.y != 0)&&b2.x==0&&b2.y==0) {
							return false;
						} 
					if (map.mapC[i][j + 1].end)break;
				}
			} 
		}
		return true;
	}
};
void gravityMath(Map *map, objects *character, float time, void fo(Map&, objects&) = NULL) { 
	if (character->hasFulcrum == false) {
		Straight *pStr=character->Collision(*map, *character, time);
		//Здесь продолжение
	  
 	}
}
void applyCoordsForCam(Map &map, objects &character) {
	map.locX -= character.GCx - (character.LCx - map.locX);
	map.locY -= character.GCy - (character.LCy - map.locY);
	map.mapS.setPosition(map.locX, map.locY);
}











///для обработки отрисовки NPC
/*

another[j].spr.setPosition(another[j].GCx + testMap.locX, another[j].GCy + testMap.locY);
*/