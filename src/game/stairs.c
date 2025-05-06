
#include "../common.h"

#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "stairs.h"

extern Dungeon dungeon;
extern Entity *player;

static void touch(Entity *self, Entity *other);

void initStairs(Entity *e)
{
	e->texture = getAtlasImage("gfx/entities/stairs.png", 1);

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
{
	if (other == player)
	{
		dungeon.complete = 1;
	}
}
