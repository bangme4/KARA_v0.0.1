
#include "../common.h"

#include "../game/messageBox.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../system/sound.h"
#include "bat.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);

void initBat(Entity *e)
{
	e->texture = getAtlasImage("gfx/entities/vampireBat.png", 1);
	e->solid = SOLID_SOLID;

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
{
	Prisoner *p;

	if (other == player)
	{
		p = (Prisoner *)other->data;

		if (p->hasDagger)
		{
			self->alive = ALIVE_DEAD;

			playSound(SND_BAT, 1);
		}
		else
		{
			addMessageBox("Prisoner", "Ouch! It bit me. I can't get past.", p->mbColor.r, p->mbColor.g, p->mbColor.b);
		}
	}
}
