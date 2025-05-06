
#include "../common.h"

#include "../game/entities.h"
#include "../json/cJSON.h"
#include "trigger.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);
static void load(Entity *e, cJSON *root);

void initTrigger(Entity *e)
{
	Trigger *t;

	t = malloc(sizeof(Trigger));
	memset(t, 0, sizeof(Trigger));

	e->data = t;

	e->touch = touch;
	e->load = load;
}

static void touch(Entity *self, Entity *other)
{
	Trigger *t;

	if (other == player)
	{
		t = (Trigger *)self->data;

		activateEntities(t->target);

		self->alive = ALIVE_DEAD;
	}
}

static void load(Entity *e, cJSON *root)
{
	Trigger *t;

	t = (Trigger *)e->data;

	STRCPY(t->target, cJSON_GetObjectItem(root, "target")->valuestring);
}
