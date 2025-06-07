
#include "../common.h"

#include "../game/dungeon.h"
#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/text.h"
#include "title.h"
#include "SDL_image.h"

extern App app;

static void logic(void);
static void draw(void);
static void drawLogo(void);

static AtlasImage *logo1;
static AtlasImage *logo2;
static double	   logoAlpha;
static int		   gotoDungeon;
static double	   gotoDungeonTimer;
static double	   tickVal;
static SDL_Texture* backgroundTexture;

void initTitle(void)
{
    logo1 = getAtlasImage("gfx/misc/logo1.png", 1);
    logo2 = getAtlasImage("gfx/misc/logo2.png", 1);

   	SDL_Surface* background = IMG_Load("assets/background.jpg");
	if (!background) {
		printf("IMG_Load Error: %s\n", IMG_GetError());
	} else {
		printf("Background loaded: %dx%d\n", background->w, background->h);
	}

	backgroundTexture = SDL_CreateTextureFromSurface(app.renderer, background);
	if (!backgroundTexture) {
		printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
	} else {
		printf("Background texture created successfully.\n");
	}

	SDL_FreeSurface(background);


    logoAlpha = 0;
    gotoDungeon = 0;
    tickVal = 0;
    gotoDungeonTimer = FPS / 2;

    app.delegate.logic = logic;
    app.delegate.draw = draw;
}


static void logic(void)
{
	if (!gotoDungeon)
	{
		logoAlpha = MIN(logoAlpha + app.deltaTime * 2, 255);

		tickVal += app.deltaTime;

		if (app.keyboard[SDL_SCANCODE_SPACE])
		{
			app.keyboard[SDL_SCANCODE_SPACE] = 0;

			gotoDungeon = 1;
		}
	}
	else
	{
		gotoDungeonTimer -= app.deltaTime;

		if (gotoDungeonTimer <= 0)
		{
			initDungeon();
		}
	}
}

static void draw(void)
{
	int c;

	if (!gotoDungeon)
	{
		SDL_RenderCopy(app.renderer, backgroundTexture, NULL, NULL);

		drawLogo();

		c = ((int)tickVal % (int)FPS < FPS / 2) ? 255 : 192;

		drawText("Press Space!", SCREEN_WIDTH / 2, 400, c, c, c, TEXT_ALIGN_CENTER, 0);

		drawText("Made by Team BIT @2025", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, 128, 128, 128, TEXT_ALIGN_CENTER, 0);
	}
}

static void drawLogo(void)
{
	int x, y;

	x = (SCREEN_WIDTH - (logo1->rect.w + logo2->rect.w)) / 2;
	y = 150;

	SDL_SetTextureAlphaMod(logo1->texture, logoAlpha);

	blitAtlasImage(logo1, x, y, 0, SDL_FLIP_NONE);
	blitAtlasImage(logo2, x + logo1->rect.w, y, 0, SDL_FLIP_NONE);

	SDL_SetTextureAlphaMod(logo1->texture, 255);
}
