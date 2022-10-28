#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include<fstream>
#include<vector>
#include<string>
#include<stdio.h>
#include<utility>
#include<algorithm>
#include "mainmenuu.h"
using namespace std;
using namespace sf;
const int ROWS = 12;		// number of columns in the ball grid
const int COLUMNS = 23;		// number of Rows in the ball grid
const int COLORS_COUNT = 3; // number of ball colors (Green, Red, Blue)
const Color COLORS[COLORS_COUNT] = { Color::Green, sf::Color::Red, sf::Color::Blue };
//void fall(int , int); 
struct Target
{
	bool isHitted = false;
	CircleShape circle;
};
//2d array
Target drawn_balls[ROWS][COLUMNS]; // Balls grid
int dummy_rows = 6; // number of dummy rows in the ball grid to reserve rows for added balls in case of not matching colors
int connected_ball[ROWS][COLUMNS] = { 0 }; // to store array of matching color network
int Final_Score = 0; // to store the Score - number of falls balls
void network(int, int, int); // Function to detect the dimensions(Row and colum) for connected balls to the shooter 
void connected_balls(int, int, int); // Function to add the dimensions(Row and colum) for connected balls to the array (connected_ball[ROWS][COLUMNS])
int Page_number;
int lastRow, lastCol;
void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font);
//void collision3(int i, int j);
//void collision1(int i, int j);
//void collision2(int i, int j);

int main()
{
	RenderWindow MENU(sf::VideoMode(960, 720), "bubble shooter", Style::Default);
	RectangleShape background;
	background.setSize(Vector2f(960, 720));
	Texture Maintexture;

	Maintexture.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\bubbleshooter.jpeg");
	background.setTexture(&Maintexture);

	RectangleShape playbackground;
	playbackground.setSize(Vector2f(960, 720));
	Texture playtexture;

	playtexture.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\playbackground.jpeg");
	playbackground.setTexture(&playtexture);
	mainmenuu mainMenu(960, 720);
	bool hasSameColor = false;
	while (true)
	{

		while (MENU.isOpen())
		{
			mainmenuu menu(500, 1000);
			Event event;
			while (MENU.pollEvent(event))
			{

				if (event.type == Event::Closed)
					MENU.close();

				if (event.type == sf::Event::KeyReleased)
				{

					if (event.key.code == sf::Keyboard::Up)
					{
						mainMenu.MoveUp();
						break;
					}


					if (event.key.code == sf::Keyboard::Down)
					{
						mainMenu.MoveDown();
						break;
					}

					if (event.key.code == Keyboard::Return)
					{


						if (mainMenu.mainmenuuPressed() == 0)
						{
							MENU.close();
							Page_number = 0;
						}

						if (mainMenu.mainmenuuPressed() == 1)
						{
							MENU.close();
							Page_number = 1;
						}

						if (mainMenu.mainmenuuPressed() == 2)
						{
							MENU.close();
							Page_number = 2;
						}

					}
				}
			}


			MENU.clear();
			MENU.draw(background);
			mainMenu.draw(MENU);
			MENU.display();
		}
		// window play//////////////////////////////
		if (Page_number == 0)
		{
			RenderWindow Play(sf::VideoMode(700, 700), "Play", Style::Close);
			Music music;
			music.openFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\musis2 (1).ogg");
			music.play();
			//  create 2d arr store all balls color in 
			for (int i = 0; i < ROWS - dummy_rows; i++)
			{
				for (int j = 0; j < COLUMNS; j++) // COLUMNS - dummy_rows for added balls
				{
					int colorIndex = (std::rand() % COLORS_COUNT - 1) + 1;
					drawn_balls[i][j].circle.setRadius(15.f);
					drawn_balls[i][j].circle.setPosition(j * 30, i * 30);
					drawn_balls[i][j].circle.setFillColor(COLORS[colorIndex]);
					lastRow = i + 1;
					lastCol = j + 1;
					if (lastCol == COLUMNS) lastCol = 0;
				}
			}

			const int x = 0, y = 0;
			Play.setFramerateLimit(30);

			///////////////// shooter

			Play.setFramerateLimit(60);
			const  int size = 26;
			int counter = 0;
			CircleShape shooter[size];
			for (int i = 0; i < size; i++)
			{
				shooter[i].setScale(0, 0);
				shooter[i].setRadius(15.0);
				shooter[i].setPosition(Vector2f(0, Play.getSize().y - shooter[i].getRadius() * 3));
			}
			shooter[0].setScale(1, 1);
			for (int i = 0; i < size - 2; i += 3)
			{
				shooter[i].setFillColor(Color::Red);
				shooter[i + 1].setFillColor(Color::Green);
				shooter[i + 2].setFillColor(Color::Blue);

			}
			shooter[24].setFillColor(Color::Red);
			shooter[25].setFillColor(Color::Green);
			////////function rand
			int balls = size - 1;
			Font ballsX;
			ballsX.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\«·Œÿ.ttf");
			Text num_balls;
			num_balls.setFont(ballsX);
			num_balls.setString("balls:" + to_string(balls));
			num_balls.setPosition(590, 590);
			num_balls.setCharacterSize(32);
			num_balls.setFillColor(Color::Black);

			Font scorex;
			scorex.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\«·Œÿ.ttf");
			Text scores;
			scores.setFont(scorex);
			scores.setString("score:" + to_string(Final_Score));
			scores.setPosition(590, 550);
			scores.setCharacterSize(32);
			scores.setFillColor(Color::Black);

			/////////////////////////////high score
			int max = 0;
			Font high_score;
			high_score.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\«·Œÿ.ttf");
			Text High_score;
			High_score.setFont(high_score);
			High_score.setString("highscore:" + to_string(max));
			High_score.setPosition(520, 520);
			High_score.setCharacterSize(32);
			High_score.setFillColor(Color::Black);
			
			///////// sound
			SoundBuffer buffer;
			buffer.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\music.ogg");
			Sound sound;
			sound.setBuffer(buffer);
			
			while (Play.isOpen())
			{

				Event aevent;
				while (Play.pollEvent(aevent))
				{
					if (aevent.type == Event::Closed)
					{
						Play.close();
					}
					////// shooter
					if (Mouse::isButtonPressed(Mouse::Left) && counter < size)
					{
						shooter[counter + 1].setScale(1, 1);
						counter++;
						cout << "ball Number" << counter << "\n";
					}
					shooter[counter].setPosition(Mouse::getPosition(Play).x, shooter[counter].getPosition().y);
					/////screen collision
					if (shooter[counter].getPosition().x < 0.f)
					{
						shooter[counter].setPosition(0.f, shooter[counter].getPosition().y);
					}
					if (shooter[counter].getPosition().x > 670.f)
					{
						shooter[counter].setPosition(670.f, shooter[counter].getPosition().y);
					}


				}
				for (int i = 0; i < counter; i++)
				{
					shooter[i].move(0, -15.f);
				}
				Play.clear();

				Play.draw(playbackground);
				Play.draw(num_balls);
				Play.draw(High_score);
				Play.draw(scores);
				

				for (size_t i = 0; i < size; i++)
				{
					Play.draw(shooter[i]);
				}
				// start playing			
				for (int i = 0; i < ROWS; i++)
				{
					for (size_t j = 0; j < COLUMNS; j++)
					{
						// Drawing balls
						Play.draw(drawn_balls[i][j].circle);

						///collision
						for (int k = 0; k < counter; k++)
						{
							// Testing if the shooter scale intersect with drawn ball scale - detect row,column for hitted ball
							if (shooter[k].getGlobalBounds().intersects(drawn_balls[i][j].circle.getGlobalBounds()))
							{
								sf::Vector2f pos = shooter[k].getPosition();
								// Testing if hitted ball is the same color of shooter or not
								if (shooter[k].getFillColor() == drawn_balls[i][j].circle.getFillColor())
								{
									cout << "Same Color"; cout << i; cout << j;
									drawn_balls[i][j].isHitted = true;
									//collision1(i,j);
									// Detect drwan ball network - Level 1 , ball jitted by shooter
									network(i, j, 1);

									// Detect drwan ball network - Level 2
									for (int ii = 0; ii < ROWS; ii++)
									{
										for (int jj = 0; jj < COLUMNS; jj++)

										{
											if (connected_ball[ii][jj] == 1)
											{
												network(ii, jj, 2);

												scores.setString("score:" + to_string(Final_Score));
												fstream hscore;
												//hscore.open("highestscore.txt ", ios::out);  // write
												//if (hscore.is_open())
												//{
												//	hscore << Final_Score;
												//	if (Final_Score > max)
												//	{
												//		max = Final_Score;
												//		hscore << max;
												//	}
												//	hscore.close();
												//}
												//hscore.open("highestscore.txt ", ios::app);  // write
												//if (hscore.is_open())
												//{
												//	hscore << " highest score = ";
												//}	hscore.close();

												hscore.open("highestscore.txt", ios::in); // read 
												if (hscore.is_open())
												{
													string line;
													while (getline(hscore, line))
													{
														if (Final_Score > max)
														{
															max = Final_Score;
															hscore << max;
															High_score.setString("highscore:" + to_string(max));
														}
														
														
													}
													hscore.close();
												}
												

												sound.play();
											}

										}
									}
									// Detect drwan ball network - Level 3
									for (int ii = 0; ii < ROWS; ii++)
									{
										for (int jj = 0; jj < COLUMNS; jj++)
										{
											if (connected_ball[ii][jj] == 2)
											{
												network(ii, jj, 3);
											}

										}
									}

								}

								// Hitted ball is not same color, to be added in dummy rows in case of last row in ball grid 
								else
								{
									if (shooter[k].getFillColor() != drawn_balls[i][j].circle.getFillColor())
									{
										drawn_balls[lastRow][lastCol].circle.setPosition(pos.x, pos.y + 5);
										drawn_balls[lastRow][lastCol].circle.setRadius(15.0f);
										drawn_balls[lastRow][lastCol].circle.setFillColor(shooter[k].getFillColor());
										shooter[k].setScale(0, 0);

										lastCol++;
										if (lastCol == COLUMNS) {
											lastCol = 0;
											lastRow++;
										}
										cout << "Hiitted diff \n";
									}
								}


								shooter[k].setScale(0, 0);
								balls--;
								num_balls.setString("balls:" + to_string(balls));
							}
						}
						if (drawn_balls[i][j].isHitted) // loop for all connected balls in the array to fall
						{
							for (int ii = 0; ii < ROWS; ii++)
							{
								for (int jj = 0; jj < COLUMNS; jj++)
								{
									if (connected_ball[ii][jj] == 1 || connected_ball[ii][jj] == 2 || connected_ball[ii][jj] == 3)
									{
										drawn_balls[ii][jj].circle.move(0, 8.f);


									}

								}
							}
						}

					}
				}
				Play.display();
			}




		}
		//if (Page_number == 1)
		//{
		//	RenderWindow highscore (sf::VideoMode(700, 700), "high scoer", Style::Close);
		//	sf::Font font;
		//	font.loadFromFile("C:\\Users\\HP\\OneDrive\\”ÿÕ «·„ﬂ »\\Project3\\Project3\\«·Œÿ.ttf");
		//	
		//	FILE* fp;
		//	char temp[255];
		//	int score[6];
		//	string name[6];
		//	vector <pair<int, string>> userScore;
		//	fp = fopen("./Score.txt", "r");
		//	for (int i = 0; i < 5; i++)
		//	{
		//		fscanf(fp, "%s", &temp);
		//		name[i] = temp;
		//		fscanf(fp, "%d", &score[i]);
		//		userScore.push_back(make_pair(score[i], name[i]));
		//		//cout << temp << " " << score;
		//	}
		//	name[5] = "HAHA";
		//	score[5] = 1234;
		//	userScore.push_back(make_pair(score[5], name[5]));
		//	sort(userScore.begin(), userScore.end());
		//	fclose(fp);
		//	fopen("./Score.txt", "w");
		//	for (int i = 5; i >= 1; i--)
		//	{
		//		strcpy(temp, userScore[i].second.c_str());
		//		fprintf(fp, "%s %d\n", temp, userScore[i].first);
		//	}
		//	fclose(fp);
		//	while (highscore.isOpen())
		//	{
		//		Event aevent;
		//		while (highscore.pollEvent(aevent))
		//		{
		//			if (aevent.type == Event::Closed)
		//			{
		//				highscore.close();
		//			}

		//			if (aevent.type == Event::KeyPressed)
		//			{
		//				if (aevent.key.code == Keyboard::Escape)
		//				{
		//					Options.close();
		//				}
		//			}
		//		}


		//	}
		//	
		//	Options.clear();
		//	


		//	Options.display();

		//}



		//

		MENU.clear();
		MENU.draw(background);


	}
	system("pause");
	return 0;
}
void fall(int row, int column)
{
	// Right from Original
	if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[row + 1][column].circle.getFillColor()))
	{
		drawn_balls[row + 1][column].circle.move(0, 8.f);
	}
	// Left from Original
	if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[row - 1][column].circle.getFillColor()))
	{
		// Above from Left		
		if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[row - 1][column - 1].circle.getFillColor()))
		{
			drawn_balls[row - 1][column - 1].circle.move(0, 8.f);
		}

		// Left from Left
		if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[row - 1][column].circle.getFillColor()))
		{
			drawn_balls[row - 1][column].circle.move(0, 8.f);
		}
		drawn_balls[row - 1][column].circle.move(0, 8.f);
	}

	// Above from Original
	if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[row][column - 1].circle.getFillColor()))
	{
		// Right from Above 
		if (drawn_balls[row][column - 1].circle.getFillColor() == (drawn_balls[row + 1][column - 1].circle.getFillColor()))
		{
			drawn_balls[row + 1][column - 1].circle.move(0, 8.f);
		}

		// Left from Above 
		if (drawn_balls[row][column - 1].circle.getFillColor() == (drawn_balls[row - 1][column - 1].circle.getFillColor()))
		{
			drawn_balls[row - 1][column - 1].circle.move(0, 8.f);
		}

		// Above from Above 
		if (drawn_balls[row][column - 1].circle.getFillColor() == (drawn_balls[row][column - 2].circle.getFillColor()))
		{
			drawn_balls[row][column - 2].circle.move(0, 8.f);
		}
		drawn_balls[row][column - 1].circle.move(0, 8.f);
	}

	// Hitted One
	drawn_balls[row][column].circle.move(0, 8.f);


}

void connected_balls(int ci, int cj, int Clevel) // to add level value (1,2,3) to network balls
{
	connected_ball[ci][cj] = Clevel;
	cout << "\n"; cout << "level:"; cout << Clevel; cout << "\t";
	cout << ci;
	cout << cj;
	cout << "\n========";
	cout << "Score:"; cout << Final_Score;

}
void network(int row, int column, int level) // Recieve hitted ball dimension (i,j) (row,column)
{
	// Right
	for (int i = row; i < ROWS; i++)
	{
		if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[i][column].circle.getFillColor()))
		{
			if (connected_ball[i][column] == 0) // to prevent replication in cout<<
			{
				Final_Score = Final_Score + 1;
				connected_balls(i, column, level);
			}
		}
		else
		{
			break;
		}
	}
	// Left	
	for (int i = row - 1; i >= 0; i--)
	{
		if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[i][column].circle.getFillColor()))
		{
			if (connected_ball[i][column] == 0) // to prevent replication in cout<<
			{
				Final_Score = Final_Score + 1;
				connected_balls(i, column, level);
			}
		}
		else
		{
			break;
		}
	}

	// Above
	for (int i = column - 1; i >= 0; i--)
	{
		if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[row][i].circle.getFillColor()))
		{
			if (connected_ball[row][i] == 0) // to prevent replication in cout<<
			{
				Final_Score = Final_Score + 1;
				connected_balls(row, i, level);
			}
		}
		else
		{
			break;
		}
	}

	// Below
	for (int i = column; i < COLUMNS; i++)
	{
		if (drawn_balls[row][column].circle.getFillColor() == (drawn_balls[row][i].circle.getFillColor()))
		{
			if (connected_ball[row][i] == 0) // to prevent replication in cout<<
			{
				Final_Score = Final_Score + 1;
				connected_balls(row, i, level);
			}
		}
		else
		{
			break;
		}
	}

}
//void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font)
//{
//
//	sf::Text text;
//	text.setFont(*font);
//	text.setPosition(x, y);
//	text.setString(word);
//	text.setCharacterSize(32);
//	
//}
//void collision1(int i, int j) {
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i + 1][j - 1].circle.getFillColor())
//	{
//		collision1(i + 1, j - 1);
//		collision3(i + 1, j - 1);
//	}
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i + 1][j].circle.getFillColor())
//	{
//		collision1(i + 1, j);
//		collision3(i + 1, j);
//	}
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i][j - 1].circle.getFillColor())
//	{
//		collision1(i, j - 1);
//	}
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i - 1][j - 1].circle.getFillColor())
//	{
//		collision1(i - 1, j - 1);
//	}
//
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i - 1][j].circle.getFillColor())
//	{
//		collision2(i - 1, j);
//	}
//	drawn_balls[i][j].circle.move(0, 3.f);
//}
//void collision2(int i, int j)
//{
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i][j - 1].circle.getFillColor())
//	{
//		collision2(i, j - 1);
//	}
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i - 1][j - 1].circle.getFillColor())
//	{
//		collision2(i - 1, j - 1);
//	}
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i - 1][j].circle.getFillColor())
//	{
//		collision2(i - 1, j);
//	}
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i - 1][j + 1].circle.getFillColor())
//	{
//		collision2(i - 1, j + 1);
//		collision3(i - 1, j + 1);
//	}
//	drawn_balls[i][j].circle.move(0, 3.f);
//}
//void collision3(int i, int j)
//{
//	if (j < 5)
//	{
//		if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i + 1][j + 1].circle.getFillColor())
//		{
//			collision3(i + 1, j + 1);
//		}
//		if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i][j + 1].circle.getFillColor())
//		{
//			collision3(i, j + 1);
//		}
//	}
//	if (drawn_balls[i][j].circle.getFillColor() == drawn_balls[i + 1][j].circle.getFillColor())
//	{
//		collision3(i + 1, j);
//	}
//	drawn_balls[i][j].circle.move(0, 3.f);
//}