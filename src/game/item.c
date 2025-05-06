
#include "../common.h"

#include "../game/hud.h"
#include "../game/inventory.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../system/sound.h"
#include "item.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);
static void load(Entity *e, cJSON *root);

void initItem(Entity *e)
{
	e->touch = touch;
	e->load = load;
}

static void touch(Entity *self, Entity *other)
{
	char message[64];

	if (other == player)
	{
		if (addToInventory(self))
		{
			memset(message, 0, sizeof(message));

			sprintf(message, "Picked up %s", self->name);

			setInfoMessage(message);

			playSound(SND_ITEM, 1);
		}
		else
		{
			setInfoMessage("Can't carry anything else.");
		}
	}
}

static void load(Entity *e, cJSON *root)
{
	e->texture = getAtlasImage(cJSON_GetObjectItem(root, "texture")->valuestring, 1);
}
