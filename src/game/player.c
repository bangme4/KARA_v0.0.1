#include "../common.h"

#include "../game/entities.h"
#include "../game/fogOfWar.h"
#include "../game/inventory.h"
#include "../system/atlas.h"
#include "../system/sound.h"
#include "player.h"

#define VIS_DISTANCE 8

extern App	   app;
extern Dungeon dungeon;
extern Entity *player;

static void movePlayer(int dx, int dy);

static double moveDelay;

void initPlayer(Entity *e)
{
	Prisoner *p;

	player = e;

	p = malloc(sizeof(Prisoner));
	memset(p, 0, sizeof(Prisoner));
	p->mbColor.r = p->mbColor.g = p->mbColor.b = 32;

	player->solid = SOLID_SOLID;
	player->texture = getAtlasImage("gfx/entities/prisoner.png", 1);
	player->facing = FACING_LEFT;

	player->data = p;

	movePlayer(0, 0);

	moveDelay = 0;
}

void doPlayer(void)
{
	moveDelay = MAX(0, moveDelay - app.deltaTime);

	if (moveDelay == 0)
	{
		if (app.keyboard[SDL_SCANCODE_A])
		{
			movePlayer(-1, 0);

			player->facing = FACING_LEFT;
		}

		if (app.keyboard[SDL_SCANCODE_D])
		{
			movePlayer(1, 0);

			player->facing = FACING_RIGHT;
		}

		if (app.keyboard[SDL_SCANCODE_W])
		{
			movePlayer(0, -1);
		}

		if (app.keyboard[SDL_SCANCODE_S])
		{
			movePlayer(0, 1);
		}

		if (app.keyboard[SDL_SCANCODE_TAB])
		{
			app.keyboard[SDL_SCANCODE_TAB] = 0;

			initInventoryView();
		}
	}
}

static void movePlayer(int dx, int dy)
{
	int		x, y;
	Entity *e;

	x = player->x + dx;
	y = player->y + dy;

	x = MAX(0, MIN(x, MAP_WIDTH - 1));
	y = MAX(0, MIN(y, MAP_HEIGHT - 1));

	if (dungeon.map.data[x][y] >= TILE_GROUND && dungeon.map.data[x][y] < TILE_WALL)
	{
		e = getEntityAt(x, y);

		if (e == NULL || e->solid == SOLID_NON_SOLID || e == player)
		{
			player->x = x;
			player->y = y;

			dungeon.camera.x = x;
			dungeon.camera.x -= (MAP_RENDER_WIDTH / 2);
			dungeon.camera.x = MIN(MAX(dungeon.camera.x, 0), MAP_WIDTH - MAP_RENDER_WIDTH);

			dungeon.camera.y = y;
			dungeon.camera.y -= (MAP_RENDER_HEIGHT / 2);
			dungeon.camera.y = MIN(MAX(dungeon.camera.y, 0), MAP_HEIGHT - MAP_RENDER_HEIGHT);

			moveDelay = 5;

			if (dx != 0 || dy != 0)
			{
				playSound(SND_WALK, 0);
			}
		}

		if (e != NULL && e->touch != NULL)
		{
			e->touch(e, player);
		}

		updateFogOfWar(player, VIS_DISTANCE);
	}
}
