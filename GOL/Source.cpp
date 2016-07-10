#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

using namespace sf;

void initIm(Image & im){
	for (int i = 0; i < im.getSize().x; i++){
		for (int j = 0; j < im.getSize().y; j++){
			if (rand() % 2 == 0){
				im.setPixel(i, j, Color::Black);
			}
		}
	}
}

int getSideAlive(Image& im, int x, int y){
	int s = 0;
	if (x > 0){
		if (im.getPixel(x - 1, y) == Color::White){
			s++;
		}
	}
	if (x < im.getSize().x - 1){
		if (im.getPixel(x + 1, y) == Color::White){
			s++;
		}
	}
	if (y > 0){
		if (im.getPixel(x, y - 1) == Color::White){
			s++;
		}
	}
	if (y < im.getSize().y - 1){
		if (im.getPixel(x, y + 1) == Color::White){
			s++;
		}
	}
	//--------------------------------------------------
	if (x > 0 && y > 0){
		if (im.getPixel(x - 1, y -1) == Color::White){
			s++;
		}
	}
	if (x < im.getSize().x - 1 && y < im.getSize().y -1){
		if (im.getPixel(x + 1, y +1) == Color::White){
			s++;
		}
	}
	if (y > 0 && x < im.getSize().x - 1){
		if (im.getPixel(x+1, y - 1) == Color::White){
			s++;
		}
	}
	if (y < im.getSize().y - 1 && x > 0){
		if (im.getPixel(x-1, y + 1) == Color::White){
			s++;
		}
	}


	return s;
}

void changeIm(Image & im){
	Image tmp(im);
	for (int i = 0; i < im.getSize().x; i++){
		for (int j = 0; j < im.getSize().y; j++){
			if (getSideAlive(im, i, j) == 3){
				tmp.setPixel(i, j, Color::White);
			}
			else if (getSideAlive(im, i, j) == 2){

			}
			else{
				tmp.setPixel(i, j, Color::Black);
			}
		}
	}
	im = tmp;
}

int main()
{
	srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(400, 300), "SFML works!");
	Image im;
	im.create(window.getSize().x, window.getSize().y, Color::White);
	initIm(im);
	Texture tx;
	tx.loadFromImage(im);
	Sprite sp;
	sp.setTexture(tx);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		while (Mouse::isButtonPressed(Mouse::Button::Left) || Mouse::isButtonPressed(Mouse::Button::Right))
		{
			if (Mouse::isButtonPressed(Mouse::Button::Left)){
				if (Mouse::getPosition(window).x >= 0 && Mouse::getPosition(window).x < window.getSize().x &&
					Mouse::getPosition(window).y >= 0 && Mouse::getPosition(window).y < window.getSize().y){
					im.setPixel(Mouse::getPosition(window).x, Mouse::getPosition(window).y, Color::White);
				}
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Right)){
				if (Mouse::getPosition(window).x >= 0 && Mouse::getPosition(window).x < window.getSize().x &&
					Mouse::getPosition(window).y >= 0 && Mouse::getPosition(window).y < window.getSize().y){
					im.setPixel(Mouse::getPosition(window).x, Mouse::getPosition(window).y, Color::Black);
				}
			}
			window.clear();
			tx.loadFromImage(im);
			sp.setTexture(tx);
			window.draw(sp);
			window.display();
		}
		
        window.clear();
		window.draw(sp);
		changeIm(im);
		tx.loadFromImage(im);
		sp.setTexture(tx);
        window.display();
		//_sleep(10);
    }

    return 0;
}