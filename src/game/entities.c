
#include "../common.h"

#include "../game/entityFactory.h"
#include "../json/cJSON.h"
#include "../system/draw.h"
#include "../system/util.h"
#include "entities.h"

extern Dungeon dungeon;

static void loadEntities(void);
static void postLoad(void);

void initEntities(void)
{
	dungeon.entityTail = &dungeon.entityHead;

	dungeon.entityId = 0;

	loadEntities();

	postLoad();
}

Entity *spawnEntity(void)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	dungeon.entityTail->next = e;
	dungeon.entityTail = e;

	e->id = dungeon.entityId++;
	e->facing = FACING_LEFT;

	return e;
}

void doEntities(void)
{
	Entity *e, *prev;

	prev = &dungeon.entityHead;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->alive == ALIVE_DEAD)
		{
			if (e == dungeon.entityTail)
			{
				dungeon.entityTail = prev;
			}

			if (e->data != NULL)
			{
				free(e->data);
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

void drawEntities(void)
{
	Entity *e;
	int		x, y;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->alive != ALIVE_DEAD && e->texture != NULL)
		{
			x = e->x - dungeon.camera.x;
			y = e->y - dungeon.camera.y;

			if (x >= 0 && y >= 0 && x < MAP_RENDER_WIDTH && y < MAP_RENDER_HEIGHT)
			{
				x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				y = (y * TILE_SIZE) + (TILE_SIZE / 2);

				x += dungeon.renderOffset.x;
				y += dungeon.renderOffset.y;

				blitAtlasImage(e->texture, x, y, 1, e->facing == FACING_LEFT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
			}
		}
	}
}

Entity *getEntityAt(int x, int y)
{
	Entity *e;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->x == x && e->y == y)
		{
			return e;
		}
	}

	return NULL;
}

void addEntityToDungeon(Entity *e)
{
	e->next = NULL;

	dungeon.entityTail->next = e;
	dungeon.entityTail = e;
}

void removeEntityFromDungeon(Entity *remove)
{
	Entity *e, *prev;

	prev = &dungeon.entityHead;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e == remove)
		{
			if (e == dungeon.entityTail)
			{
				dungeon.entityTail = prev;
			}

			prev->next = e->next;

			remove->next = NULL;
		}

		prev = e;
	}
}

static Entity *getEntityById(unsigned long id)
{
	Entity *e;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->id == id)
		{
			return e;
		}
	}

	return NULL;
}

void activateEntities(char *name)
{
	Entity *e;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->activate != NULL && strcmp(e->name, name) == 0)
		{
			e->activate(e);
		}
	}
}

static void loadEntities(void)
{
	cJSON *root, *node;
	char	 *text;

	text = readFile("data/entities.json");

	root = cJSON_Parse(text);

	for (node = root->child; node != NULL; node = node->next)
	{
		initEntity(node);
	}

	cJSON_Delete(root);

	free(text);
}

static void postLoad(void)
{
	Entity	   *e;
	Chest	  *chest;
	Merchant	 *merchant;
	Blacksmith *blacksmith;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (strcmp(e->name, "Chest") == 0)
		{
			chest = (Chest *)e->data;

			chest->item = getEntityById(chest->itemId);

			removeEntityFromDungeon(chest->item);
		}
		else if (strcmp(e->name, "Merchant") == 0)
		{
			merchant = (Merchant *)e->data;

			merchant->item = getEntityById(merchant->itemId);

			removeEntityFromDungeon(merchant->item);
		}
		else if (strcmp(e->name, "Blacksmith") == 0)
		{
			blacksmith = (Blacksmith *)e->data;

			blacksmith->item = getEntityById(blacksmith->itemId);

			removeEntityFromDungeon(blacksmith->item);
		}
	}
}
