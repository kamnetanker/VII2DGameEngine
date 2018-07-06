#pragma once
#include "SomeHeadersAndParams.h"
#include "AnotherFunc.h"
///////////////////////////////////////////////////////////////////////КЛАССЫ И СТРУКТУРЫ ОБЪЕКТОВ
CircleShape Circle1 = CircleShape(5);
CircleShape Circle2 = CircleShape(5); 
class PointDot {//класс, отвечающий за точку
public:
	float x;
	float y;
	PointDot(float x, float y) {
		this->x = x;
		this->y = y;
	}
	PointDot() {
		this->x = 0;
		this->y = 0;
	}
	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	float Distance(PointDot &b) {
		return 1.41*((b.x - this->x)*(b.x - this->x) + (b.y - this->y)*(b.y - this->y)) / (abs(b.x - this->x) + abs(b.y - this->y));
	}
}; 

class Vector2D {//класс вектора. пояснения не требуются
public:
	float i, k; //координаты единичного вектора 
	float mod;//модуль вектора
	Vector2D(float x, float y) {
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

	Vector2D(PointDot &a, PointDot &b) {
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
		 return Vector2D(this->mod*this->i + a.mod*a.i, this->mod*this->k + a.mod*a.k); 
	}
	void operator +=(Vector2D &a) {
		*this = Vector2D(this->mod*this->i + a.mod*a.i, this->mod*this->k + a.mod*a.k);

	}
	Vector2D operator -(Vector2D &a) {
		return Vector2D(this->mod*this->i - a.mod*a.i, this->mod*this->k - a.mod*a.k); 
	}
	void operator -=(Vector2D &a) {
		*this = Vector2D(this->mod*this->i - a.mod*a.i, this->mod*this->k - a.mod*a.k); 
	}
	Vector2D operator *(float &a) {
		return Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a); 
	}
	Vector2D operator *(double &a) {
		return Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a); 
	}
	void operator *=(float &a) {
		*this = Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a); 
	}
	void operator *=(float a) {
		*this = Vector2D((this->mod*this->i)*a, (this->mod*this->k)*a); 
	}
	Vector2D operator /(float &a) {
		return Vector2D((this->mod*this->i) / a, (this->mod*this->k) / a); 
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
		this->A = -1 * AB.k*AB.mod;
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
		this->A1 = b.k;
		this->B1 = -1 * b.i;
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
		if (loop(this->A) == loop(A.A) && loop(this->B) == loop(A.B)) {
			return PointDot(0, 0);
		}
		if (loop(this->A) == 0) {
			y = -1 * this->D / this->B;
			y = loop(y);
		}
		else if (loop(A.A) == 0) {
			y = -1 * A.D / A.B;
			y = loop(y);
		}
		else if (this->B*A.A - this->A*A.B != 0) {
			y = (this->A*A.D - this->D*A.A) / (this->B*A.A - this->A*A.B);
			y = loop(y);
		}
		else {
			return PointDot(0, 0);
		}
		if (A.A != 0) {
			x = -1 * (A.B*y + A.D) / A.A;
			x = loop(x);
		}
		else if (this->A != 0) {
			x = -1 * (this->B*y + this->D) / this->A;
			x = loop(x);
		}
		else {
			return PointDot(0, 0);
		}
		if (x >= loop(this->Ox1) && x <= loop(this->Ox2) && y >= loop(this->Oy1) && y <= loop(this->Oy2) && x >= loop(A.Ox1) && x <= loop(A.Ox2) && y >= loop(A.Oy1) && y <= loop(A.Oy2)) {
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
		return (this->Ox1 <= a&&this->Ox2 >= a);
	}

	PointDot GetValue(float x) {
		if (this->A == 0) {
			return PointDot(x, (this->D / this->B)*-1);
		}
		if (this->B == 0) {
			return PointDot(x, (this->D / this->A)*-1);
		}
		float y = -1 * (((this->A / this->B)*x) + (this->D / this->B));
		return PointDot(x, y);
	}

};