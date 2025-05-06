
#include "../common.h"

#include "../game/ending.h"
#include "../game/entities.h"
#include "../game/fogOfWar.h"
#include "../game/hud.h"
#include "../game/inventory.h"
#include "../game/map.h"
#include "../game/messageBox.h"
#include "../game/player.h"
#include "dungeon.h"

extern App	   app;
extern Dungeon dungeon;

static void logic(void);
static void draw(void);

void initDungeon(void)
{
	memset(&dungeon.messageBoxHead, 0, sizeof(dungeon.messageBoxHead));

	dungeon.messageBoxTail = &dungeon.messageBoxHead;

	initMap();

	initFogOfWar();

	initEntities();

	initHud();

	initMessageBox();

	initInventory();

	dungeon.renderOffset.x = (SCREEN_WIDTH - (MAP_RENDER_WIDTH * TILE_SIZE)) / 2;
	dungeon.renderOffset.y = 20;

	app.delegate.logic = &logic;
	app.delegate.draw = &draw;
}

static void logic(void)
{
	dungeon.time += app.deltaTime;

	if (dungeon.messageBoxHead.next == NULL)
	{
		doPlayer();
	}
	else
	{
		doMessageBox();
	}

	doEntities();

	doHud();

	if (dungeon.complete)
	{
		initEnding();
	}
}

static void draw(void)
{
	drawMap();

	drawEntities();

	drawFogOfWar();

	drawHud();

	drawMessageBox();
}

void initDungeonView(void)
{
	app.delegate.logic = &logic;
	app.delegate.draw = &draw;
}
