
#include "../common.h"

#include "../game/dungeon.h"
#include "../game/entities.h"
#include "../game/map.h"
#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/text.h"
#include "inventory.h"

extern App	   app;
extern Dungeon dungeon;
extern Entity *player;

static void logic(void);
static void draw(void);
static void drawInventorySlots(void);
static void cycleSlot(int dir);
static void dropSelectedItem(void);
static void updatePrisonerAttributes(Prisoner *p);

static AtlasImage *slotArrow;
static int		   selectedSlot;
static double	   slotArrowPulse;
static int		   canDrop;

void initInventory(void)
{
	slotArrow = getAtlasImage("gfx/hud/inventoryArrow.png", 1);
}

void initInventoryView(void)
{
	Entity *e;

	selectedSlot = 0;

	slotArrowPulse = 0;

	canDrop = 1;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e != player && e->x == player->x && e->y == player->y)
		{
			canDrop = 0;
		}
	}

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	slotArrowPulse += (0.15 * app.deltaTime);

	if (app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_UP])
	{
		app.keyboard[SDL_SCANCODE_W] = app.keyboard[SDL_SCANCODE_UP] = 0;

		cycleSlot(-1);
	}

	if (app.keyboard[SDL_SCANCODE_S] || app.keyboard[SDL_SCANCODE_DOWN])
	{
		app.keyboard[SDL_SCANCODE_S] = app.keyboard[SDL_SCANCODE_DOWN] = 0;

		cycleSlot(1);
	}

	if (app.keyboard[SDL_SCANCODE_RETURN])
	{
		app.keyboard[SDL_SCANCODE_RETURN] = 0;

		if (canDrop)
		{
			dropSelectedItem();

			initDungeonView();
		}
	}

	if (app.keyboard[SDL_SCANCODE_TAB] || app.keyboard[SDL_SCANCODE_ESCAPE])
	{
		app.keyboard[SDL_SCANCODE_TAB] = app.keyboard[SDL_SCANCODE_ESCAPE] = 0;

		initDungeonView();
	}
}

static void cycleSlot(int dir)
{
	selectedSlot += dir;

	slotArrowPulse = 0;

	if (selectedSlot < 0)
	{
		selectedSlot = NUM_INVENTORY_SLOTS - 1;
	}

	if (selectedSlot >= NUM_INVENTORY_SLOTS)
	{
		selectedSlot = 0;
	}
}

static void dropSelectedItem(void)
{
	Prisoner *p;
	Entity   *e;

	p = (Prisoner *)player->data;

	if (p->inventorySlots[selectedSlot] != NULL)
	{
		e = p->inventorySlots[selectedSlot];

		e->x = player->x;
		e->y = player->y;

		addEntityToDungeon(e);

		p->inventorySlots[selectedSlot] = NULL;
	}

	updatePrisonerAttributes(p);
}

static void updatePrisonerAttributes(Prisoner *p)
{
	int i;

	p->hasLantern = p->hasDagger = 0;

	for (i = 0; i < NUM_INVENTORY_SLOTS; i++)
	{
		if (p->inventorySlots[i] != NULL)
		{
			if (strcmp(p->inventorySlots[i]->name, "Lantern") == 0)
			{
				p->hasLantern = 1;
			}

			if (strcmp(p->inventorySlots[i]->name, "Dagger") == 0)
			{
				p->hasDagger = 1;
			}
		}
	}
}

static void draw(void)
{
	drawMap();

	drawEntities();

	drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 128);

	drawInventorySlots();

	if (canDrop)
	{
		drawText("[ENTER] Drop item", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 255, 255, 255, TEXT_ALIGN_CENTER, 0);
	}
	else
	{
		drawText("Can't drop anything here", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 190, 190, 190, TEXT_ALIGN_CENTER, 0);
	}
}

static void drawInventorySlots(void)
{
	int		  i, x, y;
	Prisoner *p;

	p = (Prisoner *)player->data;

	for (i = 0; i < NUM_INVENTORY_SLOTS; i++)
	{
		x = (SCREEN_WIDTH / 2) - 100;
		y = 250 + (i * 128);

		drawRect(x - 64, y - 48, 350, 96, 0, 0, 0, 255);

		drawOutlineRect(x - 64, y - 48, 350, 96, 255, 255, 255, 255);

		if (p->inventorySlots[i] != NULL)
		{
			blitAtlasImageScaled(p->inventorySlots[i]->texture, x, y, 64, 64, 1);

			drawText(p->inventorySlots[i]->name, x + 64, y - 22, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
		}
		else
		{
			drawText("(empty)", x + 64, y - 22, 160, 160, 160, TEXT_ALIGN_LEFT, 0);
		}

		if (i == selectedSlot)
		{
			blitAtlasImage(slotArrow, (x - 100) + (sin(slotArrowPulse) * 16), y, 1, SDL_FLIP_NONE);
		}
	}
}

int addToInventory(Entity *e)
{
	Prisoner *p;
	int		  i;

	p = (Prisoner *)player->data;

	for (i = 0; i < NUM_INVENTORY_SLOTS; i++)
	{
		if (p->inventorySlots[i] == NULL)
		{
			p->inventorySlots[i] = e;

			removeEntityFromDungeon(e);

			updatePrisonerAttributes(p);

			return 1;
		}
	}

	return 0;
}

int hasInventoryItem(char *name)
{
	Prisoner *p;
	int		  i;

	p = (Prisoner *)player->data;

	for (i = 0; i < NUM_INVENTORY_SLOTS; i++)
	{
		if (p->inventorySlots[i] != NULL && strcmp(p->inventorySlots[i]->name, name) == 0)
		{
			return 1;
		}
	}

	return 0;
}

void removeInventoryItem(char *name)
{
	Prisoner *p;
	Entity   *e;
	int		  i;

	p = (Prisoner *)player->data;

	for (i = 0; i < NUM_INVENTORY_SLOTS; i++)
	{
		if (p->inventorySlots[i] != NULL && strcmp(p->inventorySlots[i]->name, name) == 0)
		{
			e = p->inventorySlots[i];

			p->inventorySlots[i] = NULL;

			e->alive = ALIVE_DEAD;

			addEntityToDungeon(e);

			return;
		}
	}
}
