#pragma once 
#include "phisicsEngine.h" 
class Engine {
public: 
	RenderWindow *window;//������� ���� ������
	Object *p;//������ �������� ��� ��������� ������ ����
	int countObject = 0;//���������� �������� ��� ���������

	Engine() {//��������������� ������
		TrigPredr();
		window = new RenderWindow(VideoMode(1280, 720), "SFML is Fun");//������������� ����
		this->Update();//������� ���������� ������
	}
	void AddObj(Object &newObj) {//���������� ������� � ������ ��������
		this->countObject++;//����������� ���������� ��������
		Object *newP = new Object[this->countObject];//������ ����� ������ ��������
		for (int i = 0; i < this->countObject - 1; i++) {//��� �� ������� ��� �������.
			newP[i] = this->p[i];//��������� ��� ������������ ������� � ����� ������
		}
		newP[this->countObject - 1] = newObj;//����� ������ ��������� � ��������� ������
		delete[] this->p;//������� ������ ������
		this->p = newP;//���������� ����� ������ 
	}
	void Update() {//������� ���������� ������
		RenderWindow &w = *this->window;//��������� �� ���� ����
		Clock clock;//���� ��� �������� �������� ��� ����������� �� ���������� ������
		float f;//���������� ��� �������� ���������� �������
		while (w.isOpen()) {//���� ���� �������
			Event event;//����� �������� ����
			while (w.pollEvent(event)) {
				if (event.type == Event::Closed) {
					w.close();
				}
			}


			f = clock.getElapsedTime().asSeconds();//�������� ��������� ����� � ������ 
												   //��������� �������� �����
			clock.restart();
			if (f > F) {
				//����� ��������� ������� ���� ������ �������, ���������������� ��� ����.
				w.clear();//������� ����
				this->drawObjects(w);//�������� ������� ��������� ���� ��������
				w.display();//���������� ������������ ����
			}
		}
	}
	void drawObjects(RenderWindow &w) {//������� ��������� ��������
		for (int i = 0; i < this->countObject; i++) {
			w.draw(this->p[i].Spr);
		}
	}
};