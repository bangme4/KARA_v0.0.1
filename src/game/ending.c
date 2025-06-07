
#include "../common.h"

#include "../game/inventory.h"
#include "../system/text.h"
#include "ending.h"

extern App	   app;
extern Dungeon dungeon;
extern Entity *player;

static void logic(void);
static void draw(void);
static void drawStats(void);
static void drawCongratulations(void);
static void setStatColour(int actual, int expected, SDL_Color *c);

static int	  hasEyeball;
static int	  hasRedPotion;
static int	  mins;
static int	  secs;
static double displayTimer;

void initEnding(void)
{
	hasEyeball = hasInventoryItem("Eyeball");
	hasRedPotion = hasInventoryItem("Red potion");

	mins = dungeon.time / (FPS * FPS);
	secs = (int)(dungeon.time / FPS) % (int)FPS;

	displayTimer = FPS / 2;

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	displayTimer = MAX(0, displayTimer - app.deltaTime);

	if (displayTimer == 0)
	{
		if (app.keyboard[SDL_SCANCODE_SPACE] || app.keyboard[SDL_SCANCODE_RETURN] || app.keyboard[SDL_SCANCODE_ESCAPE])
		{
			exit(0);
		}
	}
}

static void draw(void)
{
	if (displayTimer == 0)
	{
		drawCongratulations();

		drawStats();
	}
}

static void drawCongratulations(void)
{
	char *congratulations;

	congratulations = "Congrats! You found your way out of the dungeon. You can go back now.";

	drawText(congratulations, SCREEN_WIDTH / 2, 50, 255, 255, 255, TEXT_ALIGN_CENTER, 1000);
}

static void drawStats(void)
{
	char	  message[32];
	int		  x, y;
	Prisoner *p;
	SDL_Color c;

	p = (Prisoner *)player->data;

	x = SCREEN_WIDTH / 2;
	y = 400;

	setStatColour(p->gold, dungeon.numGold, &c);
	drawText("Gold :", x, y, c.r, c.g, c.b, TEXT_ALIGN_RIGHT, 0);
	sprintf(message, "%d / %d", p->gold, dungeon.numGold);
	drawText(message, x + 15, y, c.r, c.g, c.b, TEXT_ALIGN_LEFT, 0);
	y += 50;

	setStatColour(p->silverFound, dungeon.numSilver, &c);
	drawText("Silver :", x, y, c.r, c.g, c.b, TEXT_ALIGN_RIGHT, 0);
	sprintf(message, "%d / %d", p->silverFound, dungeon.numSilver);
	drawText(message, x + 15, y, c.r, c.g, c.b, TEXT_ALIGN_LEFT, 0);
	y += 50;

	setStatColour(hasEyeball, 1, &c);
	drawText("Got Eyeball :", x, y, c.r, c.g, c.b, TEXT_ALIGN_RIGHT, 0);
	drawText(hasEyeball ? "Yes" : "No", x + 15, y, c.r, c.g, c.b, TEXT_ALIGN_LEFT, 0);
	y += 50;

	setStatColour(hasRedPotion, 1, &c);
	drawText("Got Red Potion :", x, y, c.r, c.g, c.b, TEXT_ALIGN_RIGHT, 0);
	drawText(hasRedPotion ? "Yes" : "No", x + 15, y, c.r, c.g, c.b, TEXT_ALIGN_LEFT, 0);
	y += 100;

	drawText("Time :", x, y, 255, 255, 255, TEXT_ALIGN_RIGHT, 0);
	sprintf(message, "%dm %02ds", mins, secs);
	drawText(message, x + 15, y, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
}

static void setStatColour(int actual, int expected, SDL_Color *c)
{
	c->b = 0;

	if (actual == expected)
	{
		c->r = 0;
		c->g = 255;
	}
	else
	{
		c->r = 255;
		c->g = 0;
	}
}
