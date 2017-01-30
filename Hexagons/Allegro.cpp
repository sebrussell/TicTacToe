#include "Allegro.h"

Allegro::Allegro()
{
	Initialise();

	m_cellHeight = 250;
	m_cellWidth = 250;
	m_cellOfset = 50;
	m_naught = al_map_rgb(0, 255, 0);
	m_cross = al_map_rgb(0, 0, 255);
	m_blank = al_map_rgb(255, 255, 255);
	m_background = al_map_rgb(0, 0, 0);
	m_font = al_map_rgb(255, 145, 0);
	m_buttonColour = al_map_rgb(0, 0, 0);
	m_thickness = 5;
	m_currentMousePosition = -1;

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
	}
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	GenerateGrid();
}

Allegro::~Allegro()
{
}

int Allegro::Initialise()
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

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}


	font = al_load_ttf_font("pricedown.ttf", 90, 0);

	return 0;
}

void Allegro::GenerateGrid()
{
	ButtonCoords tempButton;

	tempButton.topY = -m_cellHeight - m_cellOfset;
	tempButton.leftX = -m_cellWidth - m_cellOfset;


	for (size_t i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6 || i == 0)
		{
			tempButton.topY += m_cellHeight + m_cellOfset;
			tempButton.bottomY = tempButton.topY + m_cellHeight;

			tempButton.leftX = -m_cellWidth - m_cellOfset;
			tempButton.rightX = tempButton.leftX + m_cellWidth;
		}
		tempButton.leftX += m_cellWidth + m_cellOfset;
		tempButton.rightX = tempButton.leftX + m_cellWidth;

		tempButton.centerX = tempButton.leftX + (m_cellWidth / 2);
		tempButton.centerY = tempButton.topY + (m_cellHeight / 2);

		m_grid.push_back(tempButton);
	}

	ButtonCoords replay, quit;

	replay.topY = SCREEN_H * 0.5;
	replay.bottomY = SCREEN_H * 0.6;
	replay.leftX = SCREEN_W * 0.1;
	replay.rightX = SCREEN_W * 5 / 12;
	replay.centerX = ((replay.rightX - replay.leftX) / 2) + replay.leftX;
	replay.centerY = replay.topY * 0.94;
	replay.textToShow = "Replay";

	quit.topY = replay.topY;
	quit.bottomY = replay.bottomY;
	quit.leftX = SCREEN_W * 7 / 12;
	quit.rightX = SCREEN_W * 0.9;
	quit.centerX = ((quit.rightX - quit.leftX) / 2) + quit.leftX;
	quit.centerY = quit.topY * 0.94;
	quit.textToShow = "Quit";

	m_exitButtons.push_back(replay);
	m_exitButtons.push_back(quit);
}

void Allegro::Update(std::shared_ptr<GameState> _currentGame)
{
	std::string tempString = _currentGame->GetBoardString();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	m_currentMousePosition = -1;
	int radius, crossLeftX, crossRightX, crossTopY, crossBottomY;
	radius = (m_cellWidth / 2) * 0.8;

	for (size_t i = 0; i < m_grid.size(); i++)
	{
		crossTopY = m_grid[i].topY + (0.1 * m_cellHeight);
		crossBottomY = m_grid[i].bottomY - (0.1 * m_cellHeight);
		crossLeftX = m_grid[i].leftX + (0.1 * m_cellWidth);
		crossRightX = m_grid[i].rightX - (0.1 * m_cellWidth);

		al_draw_filled_rectangle(m_grid[i].leftX, m_grid[i].topY, m_grid[i].rightX, m_grid[i].bottomY, m_blank);

		switch (tempString[i])
		{
		case 'x':
			al_draw_line(crossLeftX, crossTopY, crossRightX, crossBottomY, m_cross, m_thickness);
			al_draw_line(crossRightX, crossTopY, crossLeftX, crossBottomY, m_cross, m_thickness);
			break;
		case 'o':
			al_draw_circle(m_grid[i].centerX, m_grid[i].centerY, radius, m_naught, m_thickness);
			break;
		}
	}

	al_flip_display();
}

void Allegro::DrawOutcome(std::shared_ptr<GameState> _currentGame)
{
	m_naught = al_map_rgba(0, 255, 0, 50);
	m_cross = al_map_rgba(0, 0, 255, 50);
	m_blank = al_map_rgba(255, 255, 255, 50);
	m_background = al_map_rgba(100, 100, 100, 50);

	Update(_currentGame);

	m_naught = al_map_rgb(0, 255, 0);
	m_cross = al_map_rgb(0, 0, 255);

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

	switch (_currentGame->GetGameStatus())
	{
	case GameState::draw:
		al_draw_textf(font, m_font, SCREEN_W / 2, SCREEN_H * 0.35, ALLEGRO_ALIGN_CENTRE, "Draw");
		std::cout << "draw" << std::endl;
		break;
	case GameState::oWon:
		al_draw_textf(font, m_font, SCREEN_W / 2, SCREEN_H * 0.35, ALLEGRO_ALIGN_CENTRE, "Naught Won");
		std::cout << "o won" << std::endl;
		break;
	case GameState::xWon:
		al_draw_textf(font, m_font, SCREEN_W / 2, SCREEN_H * 0.35, ALLEGRO_ALIGN_CENTRE, "Cross Won");
		std::cout << "x won" << std::endl;
		break;
	}

	DrawExitButtons();

	al_flip_display();
}

void Allegro::DrawExitButtons()
{
	for (size_t i = 0; i < m_exitButtons.size(); i++)
	{
		al_draw_filled_rectangle(m_exitButtons[i].leftX, m_exitButtons[i].topY, m_exitButtons[i].rightX, m_exitButtons[i].bottomY, m_buttonColour);

		al_draw_textf(font, m_font, m_exitButtons[i].centerX, m_exitButtons[i].centerY, ALLEGRO_ALIGN_CENTRE, m_exitButtons[i].textToShow);
	}
}

int Allegro::GetInput(bool _endGame)
{
	al_wait_for_event(event_queue, &ev);

	std::vector<ButtonCoords> buttons;

	if (_endGame == true)
	{
		buttons = m_exitButtons;
	}
	else
	{
		buttons = m_grid;
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].leftX <= ev.mouse.x && buttons[i].rightX >= ev.mouse.x)
		{
			if (buttons[i].topY <= ev.mouse.y && buttons[i].bottomY >= ev.mouse.y)
			{
				m_currentMousePosition = i;
			}
		}
	}

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if (_endGame == true && m_currentMousePosition == 1)
		{
			return -2;
		}
		else
		{
			return m_currentMousePosition;
		}		
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -2;
	}
	else
	{
		return -1;
	}
}

