#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "../common.h"

#include "../game/entityFactory.h"
#include "../system/atlas.h"
#include "../system/sound.h"
#include "../system/text.h"
#include "init.h"

extern App app;

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	// Initialize SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Initialize SDL Mixer for audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Couldn't initialize SDL Mixer\n");
		exit(1);
	}

	// Initialize SDL_image for image loading
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
		printf("IMG_Init failed: %s\n", IMG_GetError());
		exit(1);
	}

	// Allocate sound channels
	Mix_AllocateChannels(MAX_SND_CHANNELS);

	// Create the SDL window
	app.window = SDL_CreateWindow("SDL2 Adventure 14", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	if (!app.window)
	{
		printf("Couldn't create window: %s\n", SDL_GetError());
		exit(1);
	}

	// Set render scaling quality
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	// Create the SDL renderer
	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
	if (!app.renderer)
	{
		printf("Couldn't create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	// Initialize SDL_ttf for fonts
	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		exit(1);
	}

	// Hide the cursor
	SDL_ShowCursor(0);
}

void initGameSystem(void)
{
	initAtlas();
	initFonts();
	initEntityFactory();
	initSound();

	loadMusic("music/A tricky puzzle_1.ogg");
	playMusic(1);
}

void cleanup(void)
{
	// Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();

	// Destroy renderer and window
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);

	// Quit SDL
	SDL_Quit();
}
