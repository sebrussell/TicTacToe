#pragma once
#include "GameState.h"
#include <iostream>
#include "Allegro.h"


class Draw
{
public:
	Draw(ALLEGRO_DISPLAY* display);
	~Draw();
	void Update(std::shared_ptr<GameState> _currentGame);	
	int GetInput();
	void DrawOutcome(std::shared_ptr<GameState> _currentGame);
private:
	int m_cellHeight, m_cellWidth, m_cellOfset, m_thickness, m_currentMousePosition;
	ALLEGRO_COLOR m_naught, m_cross, m_blank;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT ev;
};

