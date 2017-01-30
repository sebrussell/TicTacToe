#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"			//defines all the other files that will be used
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include <iostream>
#include "GameState.h"

class Allegro
{
public:
	struct ButtonCoords
	{
		int topY, bottomY, leftX, rightX, centerX, centerY;
		bool hidden;
		char* textToShow;
	};

	Allegro();
	~Allegro();
	int Initialise();

	//functions for the draw 'class'

	void Update(std::shared_ptr<GameState> _currentGame);
	int GetInput(bool _endGame);
	void DrawOutcome(std::shared_ptr<GameState> _currentGame);
	void DrawExitButtons();
	void GenerateGrid();
private:	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font;
	const float FPS = 60;
	const int SCREEN_W = 850;
	const int SCREEN_H = 850;
	const int BOUNCER_SIZE = 32;

	//variables for the draw 'class' that has been merged with the allegro class

	int m_cellHeight, m_cellWidth, m_cellOfset, m_thickness, m_currentMousePosition;
	ALLEGRO_COLOR m_naught, m_cross, m_blank, m_font, m_background, m_buttonColour;
	ALLEGRO_EVENT ev;
	std::vector<ButtonCoords> m_grid;
	
	std::vector<ButtonCoords> m_exitButtons;
};

