
#include "../common.h"

#include "../game/hud.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../system/sound.h"
#include "fakeWall.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);

void initFakeWall(Entity *e)
{
	e->texture = getAtlasImage("gfx/tiles/40.png", 1);
	e->solid = SOLID_SOLID;

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
{
	if (other == player)
	{
		setInfoMessage("A secret is revealed!");

		self->alive = ALIVE_DEAD;

		playSound(SND_SECRET, 1);
	}
}
