#include "../common.h"

#include "../game/hud.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../system/sound.h"
#include "silver.h"

extern Dungeon dungeon;
extern Entity *player;

static void touch(Entity *self, Entity *other);

void initSilver(Entity *e)
{
	e->texture = getAtlasImage("gfx/entities/silverCoin.png", 1);

	e->touch = touch;

	dungeon.numSilver++;
}

static void touch(Entity *self, Entity *other)
{
	Prisoner *p;

	if (other == player)
	{
		p = (Prisoner *)other->data;

		p->silver++;
		p->silverFound++;

		self->alive = ALIVE_DEAD;

		setInfoMessage("Picked up a silver coin.");

		playSound(SND_COIN, 1);
	}
}
