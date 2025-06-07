
#include "../common.h"

#include "../game/messageBox.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "signpost.h"

extern Entity *player;

static void touch(Entity *e, Entity *other);
static void load(Entity *e, cJSON *root);

void initSignpost(Entity *e)
{
	Signpost *signpost;

	signpost = malloc(sizeof(Signpost));
	memset(signpost, 0, sizeof(Signpost));

	e->texture = getAtlasImage("gfx/entities/signpost.png", 1);
	e->solid = SOLID_SOLID;
	e->data = signpost;

	e->touch = touch;
	e->load = load;
}

static void touch(Entity *self, Entity *other)
{
	Signpost *signpost;

	if (other == player)
	{
		signpost = (Signpost *)self->data;

		addMessageBox("mail monster", signpost->message, 90, 70, 30);
	}
}

static void load(Entity *e, cJSON *root)
{
	Signpost *signpost;

	signpost = (Signpost *)e->data;

	STRCPY(signpost->message, cJSON_GetObjectItem(root, "message")->valuestring);
}
