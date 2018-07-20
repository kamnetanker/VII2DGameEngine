#pragma once 
#include "phisicsEngine.h" 
class Engine {
public: 
	RenderWindow *window;//������� ���� ������
	Object *p;//������ �������� ��� ��������� ������ ����
	PhisicsObject *pp;//������ ���������� �������� �������� ��� ��������� ������ ����
	int countObject = 0;//���������� �������� ��� ���������
	int countPObject = 0;//���������� ���������� �������� ��� ���������

	Engine() {//��������������� ������
		
		TrigPredr();
		window = new RenderWindow(VideoMode(1280, 950), "SFML is Fun");//������������� ����
		ViewPoint.reset(sf::FloatRect(0, 0, 1280, 950));//������ "����" ������ ��� �������� ������� ���� ������. 
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


	void AddPhisObj(PhisicsObject &newObj) {//���������� ����������� ������� � ������ ��������
		this->countPObject++;//����������� ���������� ��������
		PhisicsObject *newP = new PhisicsObject[this->countPObject];//������ ����� ������ ��������
		for (int i = 0; i < this->countPObject - 1; i++) {//��� �� ������� ��� �������.
			newP[i] = this->pp[i];//��������� ��� ������������ ������� � ����� ������
		}
		newP[this->countPObject - 1] = newObj;//����� ������ ��������� � ��������� ������
		delete[] this->pp;//������� ������ ������
		this->pp = newP;//���������� ����� ������ 
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
			
			if (f > F) {
				clock.restart();
				//����� ��������� ������� ���� ������ �������, ���������������� ��� ����.
				w.setView(ViewPoint);//������������� ����� ��� � ���� sfml
				w.clear();//������� ����
				w.draw(CureMapLvl.mapS);//������������ �����
				this->drawObjects(w);//�������� ������� ��������� ���� ��������
				w.display();//���������� ������������ ����
			}
		}
	}
	void drawObjects(RenderWindow &w) {//������� ��������� ��������
		for (int i = 0; i < this->countObject; i++) {
			w.draw(this->p[i].Spr);
		}
		for (int i = 0; i < this->countPObject; i++) {
			w.draw(this->pp[i].Spr);
		}
	}
};