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
