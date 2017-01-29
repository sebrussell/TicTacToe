#include "Allegro.h"

Allegro::Allegro()
{
	Initialise();
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
	

	font = al_load_ttf_font("TimesNewRoman.ttf", 10, 0);

	return 0;
}

