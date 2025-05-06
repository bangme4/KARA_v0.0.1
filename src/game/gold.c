
#include "../common.h"

#include "../game/hud.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../system/sound.h"
#include "gold.h"

extern Dungeon dungeon;
extern Entity *player;

static void touch(Entity *self, Entity *other);
static void load(Entity *e, cJSON *root);

void initGold(Entity *e)
{
	Gold *gold;

	gold = malloc(sizeof(Gold));
	memset(gold, 0, sizeof(Gold));

	e->data = gold;

	e->touch = touch;
	e->load = load;
}

static void touch(Entity *self, Entity *other)
{
	Prisoner *p;
	Gold	 *gold;
	char	  message[32];

	if (other == player)
	{
		p = (Prisoner *)other->data;
		gold = (Gold *)self->data;

		p->gold += gold->value;

		self->alive = ALIVE_DEAD;

		if (gold->value == 1)
		{
			STRCPY(message, "Picked up a gold coin.");
		}
		else
		{
			memset(message, 0, sizeof(message));

			sprintf(message, "Picked up %d gold coins.", gold->value);
		}

		setInfoMessage(message);

		playSound(SND_COIN, 1);
	}
}

static void load(Entity *e, cJSON *root)
{
	Gold *gold;

	gold = (Gold *)e->data;

	gold->value = cJSON_GetObjectItem(root, "value")->valueint;

	if (gold->value > 1)
	{
		e->texture = getAtlasImage("gfx/entities/goldCoins.png", 1);
	}
	else
	{
		e->texture = getAtlasImage("gfx/entities/goldCoin.png", 1);
	}

	dungeon.numGold += gold->value;
}
