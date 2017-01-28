#include "Draw.h"

Draw::Draw()
{
	m_cellHeight = 250;
	m_cellWidth = 250;
	m_cellOfset = 50;
	m_naught = al_map_rgb(0, 255, 0);
	m_cross = al_map_rgb(0, 0, 255);
	m_blank = al_map_rgb(255, 255, 255);
	m_thickness = 5;
}


Draw::~Draw()
{
}

void Draw::Update(std::shared_ptr<GameState> _currentGame)
{
	std::string tempString = _currentGame->GetBoardString();

	int x1, y1, x2, y2, cX, cY, radius;

	int crossLeftX, crossRightX, crossTopY, crossBottomY;

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

int Draw::GetInput()
{
	return 0;
}