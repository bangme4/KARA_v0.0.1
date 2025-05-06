
#include "../common.h"

#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "wall.h"

static void activate(Entity *e);
static void load(Entity *e, cJSON *root);
static void updateSolid(Entity *e);

void initWall(Entity *e)
{
	e->activate = activate;
	e->load = load;
}

static void activate(Entity *e)
{
	e->solid = !e->solid;

	updateSolid(e);
}

static void load(Entity *e, cJSON *root)
{
	e->solid = cJSON_GetObjectItem(root, "solid")->valueint;

	updateSolid(e);
}

static void updateSolid(Entity *e)
{
	if (e->solid)
	{
		e->texture = getAtlasImage("gfx/tiles/40.png", 1);
	}
	else
	{
		e->texture = NULL;
	}
}
