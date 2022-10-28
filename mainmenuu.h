#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

#define Max_main_menu 3

class mainmenuu
{
public:

	mainmenuu(float width, float hight);

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int mainmenuuPressed()
	{
		return mainmenuuselected;
	}


	~mainmenuu();

private:
	int mainmenuuselected;
	sf::Font font;
	sf::Text mainmenu[Max_main_menu];
};