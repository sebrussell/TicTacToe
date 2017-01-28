#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"			//defines all the other files that will be used
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include <iostream>

class Allegro
{
public:
	Allegro();
	~Allegro();
	int Initialise();
private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font;
	const float FPS = 60;
	const int SCREEN_W = 850;
	const int SCREEN_H = 850;
	const int BOUNCER_SIZE = 32;
};

