#pragma once 
#include "phisicsEngine.h" 
class Engine {
public: 
	RenderWindow *window;//Главное окно Движка
	Object *p;//Массив объектов для отрисовки каждый кадр
	int countObject = 0;//Количество объектов для отрисовки

	Engine() {//Ининициализация Движка
		TrigPredr();
		window = new RenderWindow(VideoMode(1280, 720), "SFML is Fun");//Инициализация окна
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
			clock.restart();
			if (f > F) {
				//здесь требуется указать ваши личные функции, использовавшиеся для игры.
				w.clear();//очищаем окно
				this->drawObjects(w);//Вызываем функцию отрисовки всех объектов
				w.display();//показываем получившийся кадр
			}
		}
	}
	void drawObjects(RenderWindow &w) {//Функция отрисовки объектов
		for (int i = 0; i < this->countObject; i++) {
			w.draw(this->p[i].Spr);
		}
	}
};