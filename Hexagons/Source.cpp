#include <stdio.h>
#include <string.h>
#include <cmath>
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"			//defines all the other files that will be used
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include <vector>
#include <memory>
#include <ctime>
#include <iostream>

#include "GameState.h"
#include "Tree.h"

// nice colour (42, 120, 242);

const float FPS = 60;
const int SCREEN_W = 900;					//sets some default values for the program 
const int SCREEN_H = 900;
const int BOUNCER_SIZE = 32;

//list of functions so main can use them, would be better in a different file 

int InitialiseAllegro(ALLEGRO_TIMER * timer, ALLEGRO_DISPLAY * display);

int main(int argc, char **argv)															//start of main 
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;													//more default variables 

	double deltaTime = 0;
	double totalTime = 0;
	std::clock_t begin, end;

	srand(time(NULL));
	InitialiseAllegro(timer, display);     //initialises allegro, randomness and starts the display	

	ALLEGRO_FONT *font = al_load_ttf_font("TimesNewRoman.ttf", 10, 0);				//used for the text 

	Tree test;
	test.GenerateTree();


	int position;
	std::string tempString;

	bool gameOver = false;

	while (1 == 1)																										//loop through until done
	{
		begin = clock();
		//Draw();
		//UserInput();

		if (test.GetNode()->DidXGoLast() == false)
		{
			std::cout << "Enter position";
			tempString = test.GetNode()->GetBoardString();
			std::cin >> position;
			tempString[position] = 'x';

			for (std::shared_ptr<GameState> l : test.GetNode()->GetChildNodes())		//change this to actual not 2015 stuff
			{
				if (l->GetBoardString() == tempString)
				{
					test.SetNode(l);
					break;
				}
			}
		}
		else
		{
			std::shared_ptr<GameState> tempNode = test.GetNode()->GetChildNodes().front();

			if (test.GetNode()->GetChildNodes().size() > 0)
			{
				for (std::shared_ptr<GameState> l : test.GetNode()->GetChildNodes())		//change this to actual not 2015 stuff
				{
					if (l->GetNodeValue() < tempNode->GetNodeValue())
					{
						tempNode = l;
					}
				}
			}
			else
			{
				gameOver = true;
			}
			

			test.SetNode(tempNode);
		}

		if (gameOver == false)
		{
			std::cout << test.GetNode()->GetBoardString()[0] << "|" << test.GetNode()->GetBoardString()[1] << "|" << test.GetNode()->GetBoardString()[2] << std::endl;
			std::cout << "-----" << std::endl;
			std::cout << test.GetNode()->GetBoardString()[3] << "|" << test.GetNode()->GetBoardString()[4] << "|" << test.GetNode()->GetBoardString()[5] << std::endl;
			std::cout << "-----" << std::endl;
			std::cout << test.GetNode()->GetBoardString()[6] << "|" << test.GetNode()->GetBoardString()[7] << "|" << test.GetNode()->GetBoardString()[8] << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Game over";
		}

		
 		
		
		end = clock();
		deltaTime = double(end - begin) / CLOCKS_PER_SEC;															//this is used for delta time and timers
		totalTime += deltaTime;
	}
	return 0;
}



int InitialiseAllegro(ALLEGRO_TIMER * timer, ALLEGRO_DISPLAY * display)
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize the prar!\n");
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	//display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}
	return 0;
}
