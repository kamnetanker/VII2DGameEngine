#pragma once 
#include "phisicsEngine.h" 
class Engine {
public: 
	RenderWindow *window;//Главное окно Движка
	Object *p;//Массив объектов для отрисовки каждый кадр
	PhisicsObject *pp;//Массив физических объектов объектов для отрисовки каждый кадр
	int countObject = 0;//Количество объектов для отрисовки
	int countPObject = 0;//Количество физических объектов для отрисовки

	Engine() {//Ининициализация Движка
		
		TrigPredr();
		window = new RenderWindow(VideoMode(1280, 950), "SFML is Fun");//Инициализация окна
		ViewPoint.reset(sf::FloatRect(0, 0, 1280, 950));//размер "вида" камеры при создании объекта вида камеры. 
		this->Update();//Функция обновления движка
	}
	void AddObj(Object &newObj) {//Добавление объекта в массив объектов
		this->countObject++;//Увеличиваем количество объектов
		Object *newP = new Object[this->countObject];//создаём новый массив объектов
		for (int i = 0; i < this->countObject - 1; i++) {//Идём по массиву уже существ.
			newP[i] = this->p[i];//Добавляем уже существующие объекты в новый массив
		}
		newP[this->countObject - 1] = newObj;//Новый объект добавляем в созданный массив
		delete[] this->p;//удаляем старый массив
		this->p = newP;//Записываем новый массив 
	}


	void AddPhisObj(PhisicsObject &newObj) {//Добавление физического объекта в массив объектов
		this->countPObject++;//Увеличиваем количество объектов
		PhisicsObject *newP = new PhisicsObject[this->countPObject];//создаём новый массив объектов
		for (int i = 0; i < this->countPObject - 1; i++) {//Идём по массиву уже существ.
			newP[i] = this->pp[i];//Добавляем уже существующие объекты в новый массив
		}
		newP[this->countPObject - 1] = newObj;//Новый объект добавляем в созданный массив
		delete[] this->pp;//удаляем старый массив
		this->pp = newP;//Записываем новый массив 
	} 
	void Update() {//Функция обновления движка
		RenderWindow &w = *this->window;//Указатель на наше окно
		Clock clock;//Часы для плавного движения вне зависимости от количества кадров
		float f;//переменная для хранения прошедшего времени
		while (w.isOpen()) {//Пока окно открыто
			Event event;//Эвент закрытия окна
			while (w.pollEvent(event)) {
				if (event.type == Event::Closed) {
					w.close();
				}
			} 
			f = clock.getElapsedTime().asSeconds();//Получаем прошедшее время с начала 
												   //обработки прошлого кадра
			
			if (f > F) {
				clock.restart();
				//здесь требуется указать ваши личные функции, использовавшиеся для игры.
				w.setView(ViewPoint);//Устанавливаем новый вид в окне sfml
				w.clear();//очищаем окно
				w.draw(CureMapLvl.mapS);//отрисовываем карту
				this->drawObjects(w);//Вызываем функцию отрисовки всех объектов
				w.display();//показываем получившийся кадр
			}
		}
	}
	void drawObjects(RenderWindow &w) {//Функция отрисовки объектов
		for (int i = 0; i < this->countObject; i++) {
			w.draw(this->p[i].Spr);
		}
		for (int i = 0; i < this->countPObject; i++) {
			w.draw(this->pp[i].Spr);
		}
	}
};