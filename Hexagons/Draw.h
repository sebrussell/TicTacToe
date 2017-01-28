#pragma once
#include "GameState.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

class Draw
{
public:
	Draw();
	~Draw();
	void Update(std::shared_ptr<GameState> _currentGame);
	int GetInput();
private:
	int m_cellHeight, m_cellWidth, m_cellOfset, m_thickness;
	ALLEGRO_COLOR m_naught, m_cross, m_blank;
};

