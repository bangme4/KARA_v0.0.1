
#include "../common.h"

#include "../game/inventory.h"
#include "../game/messageBox.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "goblin.h"

#define STATE_INIT		0
#define STATE_WANT_FOOD 1

extern Entity *player;

static void touch(Entity *self, Entity *other);

static SDL_Color mbColor;

void initGoblin(Entity *e)
{
	Goblin *goblin;
	goblin = malloc(sizeof(Goblin));
	memset(goblin, 0, sizeof(Goblin));

	e->texture = getAtlasImage("gfx/entities/goblin.png", 1);
	e->solid = SOLID_SOLID;
	e->data = goblin;

	e->touch = touch;

	mbColor.r = 0;
	mbColor.g = 64;
	mbColor.b = 0;
}

static void touch(Entity *self, Entity *other)
{
	Goblin   *g;
	Prisoner *p;

	if (other == player)
	{
		self->facing = (other->x > self->x) ? FACING_RIGHT : FACING_LEFT;

		g = (Goblin *)self->data;
		p = (Prisoner *)other->data;

		switch (g->state)
		{
			case STATE_INIT:
				addMessageBox("Prisoner", "Excuse me, do you mind if I just squeeze past?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
				addMessageBox("Goblin", "Go away! I'm meant to be guarding this magical 'House' icon from the contestant. But I'm in a bad mood because I left my lunch in the fridge today, and I'm really hungry.", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Goblin", "Now I'm going to have to wait until I get home, but I'm on an extended shift here so that's hours away. Stupid job, stupid contract.", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Goblin", "So, unless you've got something to eat, you can just push off.", mbColor.r, mbColor.g, mbColor.b);
				g->state = STATE_WANT_FOOD;
				break;

			case STATE_WANT_FOOD:
				if (hasInventoryItem("Cheese"))
				{
					addMessageBox("Prisoner", "Will this do?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
					addMessageBox("Goblin", "Cheese! Wow, and it's a big lump, too!", mbColor.r, mbColor.g, mbColor.b);
					addMessageBox("Goblin", "Thanks, stranger, I'm going to go and enjoy this. Back soon.", mbColor.r, mbColor.g, mbColor.b);

					removeInventoryItem("Cheese");

					self->alive = ALIVE_DEAD;
				}
				else
				{
					addMessageBox("Goblin", "Unless you've got some food, I don't want to talk to you.", mbColor.r, mbColor.g, mbColor.b);
				}
				break;

			default:
				break;
		}
	}
}
