#include "Draw.h"

Draw::Draw(ALLEGRO_DISPLAY* display)
{
	m_cellHeight = 250;
	m_cellWidth = 250;
	m_cellOfset = 50;
	m_naught = al_map_rgb(0, 255, 0);
	m_cross = al_map_rgb(0, 0, 255);
	m_blank = al_map_rgb(255, 255, 255);
	m_thickness = 5;
	m_currentMousePosition = -1;

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
	}
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
}


Draw::~Draw()
{
}

void Draw::Update(std::shared_ptr<GameState> _currentGame)	
{
	std::string tempString = _currentGame->GetBoardString();
	int x1, y1, x2, y2, cX, cY, radius, crossLeftX, crossRightX, crossTopY, crossBottomY;
	m_currentMousePosition = -1;	

	y1 = -m_cellHeight - m_cellOfset;
	x1 = -m_cellWidth - m_cellOfset;
	radius = (m_cellWidth / 2) * 0.8;

	for (size_t i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6 || i == 0)
		{
			y1 += m_cellHeight + m_cellOfset;
			y2 = y1 + m_cellHeight;

			x1 = -m_cellWidth - m_cellOfset;
			x2 = x1 + m_cellWidth;
		}
		x1 += m_cellWidth + m_cellOfset;
		x2 = x1 + m_cellWidth;

		cX = x1 + (m_cellWidth / 2);
		cY = y1 + (m_cellHeight / 2);

		crossTopY = y1 + (0.1 * m_cellHeight);
		crossBottomY = y2 - (0.1 * m_cellHeight);
		crossLeftX = x1 + (0.1 * m_cellWidth);
		crossRightX = x2 - (0.1 * m_cellWidth);

		if (x1 <= ev.mouse.x && x2 >= ev.mouse.x)
		{
			if (y1 <= ev.mouse.y && y2 >= ev.mouse.y)
			{
				m_currentMousePosition = i;
			}
		}

		al_draw_filled_rectangle(x1, y1, x2, y2, m_blank);

		switch (tempString[i])
		{
		case 'x':
			al_draw_line(crossLeftX, crossTopY, crossRightX, crossBottomY, m_cross, m_thickness);
			al_draw_line(crossRightX, crossTopY, crossLeftX, crossBottomY, m_cross, m_thickness);
			break;
		case 'o':
			al_draw_circle(cX, cY, radius, m_naught, m_thickness);
			break;
		}
	}
	al_flip_display();
}

void Draw::DrawOutcome(std::shared_ptr<GameState> _currentGame)
{
	Update(_currentGame);

	int box1X, box1Y, box2X, box2Y;

	if (_currentGame->GetGameStatus() != GameState::draw)
	{
		for (size_t i = 0; i < 2; i++)
		{
			box1X = ((_currentGame->GetWinningPosition()[0 + i] % 3) * (m_cellWidth + m_cellOfset)) + (m_cellWidth / 2);
			box1Y = (floor(_currentGame->GetWinningPosition()[0 + i] / 3) * (m_cellHeight + m_cellOfset)) + (m_cellHeight / 2);

			box2X = ((_currentGame->GetWinningPosition()[1 + i] % 3) * (m_cellWidth + m_cellOfset)) + (m_cellWidth / 2);
			box2Y = (floor(_currentGame->GetWinningPosition()[1 + i] / 3) * (m_cellHeight + m_cellOfset)) + (m_cellHeight / 2);

			if (_currentGame->GetGameStatus() == GameState::oWon)
			{
				al_draw_line(box1X, box1Y, box2X, box2Y, m_naught, m_thickness * 2);
			}
			if (_currentGame->GetGameStatus() == GameState::xWon)
			{
				al_draw_line(box1X, box1Y, box2X, box2Y, m_cross, m_thickness * 2);
			}
		}
	}	
	
	al_flip_display();

	switch (_currentGame->GetGameStatus())
	{
	case GameState::draw:
		std::cout << "draw" << std::endl;
		break;
	case GameState::oWon:
		std::cout << "o won" << std::endl;
		break;
	case GameState::xWon:
		std::cout << "x won" << std::endl;
		break;
	}
}



int Draw::GetInput()
{
	al_wait_for_event(event_queue, &ev);
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		return m_currentMousePosition;
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -2;
	}
	else
	{
		return -1;
	}
}