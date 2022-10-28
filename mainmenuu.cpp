#include "mainmenuu.h"
#define SFML_FONT_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include<fstream>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;


mainmenuu::mainmenuu(float width, float hight)
{

	if (!font.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\«·Œÿ.ttf"))
	{
		//cout << "no font is here";
	}

	//play
	int max = 0;

	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(sf::Color::Black);
	mainmenu[0].setString("Play");
	mainmenu[0].setCharacterSize(60);
	mainmenu[0].setPosition(400, 480);
	//
		/*ifstream input("high score.txt");
		mainmenu[1].setFont(font);
		mainmenu[1].setFillColor(sf::Color::Black);
		ofstream output("high score.txt");
		output << max;
		mainmenu[1].setString("high score:" + to_string(max));
		mainmenu[1].setCharacterSize(50);
		mainmenu[1].setPosition(80, 450);*/
	///Options
	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::Black);
	mainmenu[1].setString("high score");
	mainmenu[1].setCharacterSize(60);
	mainmenu[1].setPosition(400, 557);

		// Exit

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::Black);
	mainmenu[2].setString("Exit");
	mainmenu[2].setCharacterSize(60);
	mainmenu[2].setPosition(400, 640);





	mainmenuuselected = 0;
}

mainmenuu::~mainmenuu()
{

}


void mainmenuu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; i++)
	{
		window.draw(mainmenu[i]);
	}
}



void mainmenuu::MoveUp()
{
	if (mainmenuuselected - 1 >= -1)  // check if not on the last item (exit)
	{
		mainmenu[mainmenuuselected].setFillColor(Color::Black);

		mainmenuuselected--; //move to next item

		if (mainmenuuselected == -1)
		{
			mainmenuuselected = 2;
		}

		mainmenu[mainmenuuselected].setFillColor(Color::Blue);   // change the new item color
	}



}

void mainmenuu::MoveDown()
{
	if (mainmenuuselected + 1 <= Max_main_menu)  // check if not on the last item (exit)
	{
		mainmenu[mainmenuuselected].setFillColor(Color::Black);


		mainmenuuselected++; //move to next item	


		if (mainmenuuselected == 3)
		{
			mainmenuuselected = 0;
		}

		mainmenu[mainmenuuselected].setFillColor(Color::Blue);   // change the new item color
	}

}