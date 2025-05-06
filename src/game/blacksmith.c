
#include "../common.h"

#include "../game/inventory.h"
#include "../game/messageBox.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "blacksmith.h"

#define STATE_INIT		  0
#define STATE_NEED_SILVER 1
#define STATE_HAS_SILVER  2
#define SILVER_REQUIRED	  14

extern Entity *player;

static void touch(Entity *self, Entity *other);
static void load(Entity *e, cJSON *root);

static SDL_Color mbColor;

void initBlacksmith(Entity *e)
{
	Blacksmith *blacksmith;
	blacksmith = malloc(sizeof(Blacksmith));
	memset(blacksmith, 0, sizeof(Blacksmith));

	STRCPY(e->name, "Blacksmith");
	e->texture = getAtlasImage("gfx/entities/blacksmith.png", 1);
	e->solid = SOLID_SOLID;
	e->data = blacksmith;

	e->touch = touch;
	e->load = load;

	mbColor.r = 64;
	mbColor.g = 16;
	mbColor.b = 64;
}

static void touch(Entity *self, Entity *other)
{
	Blacksmith *b;
	Prisoner	 *p;
	char		message[128];

	if (other == player)
	{
		self->facing = (other->x > self->x) ? FACING_RIGHT : FACING_LEFT;

		b = (Blacksmith *)self->data;
		p = (Prisoner *)other->data;

		switch (b->state)
		{
			case STATE_INIT:
				addMessageBox("Blacksmith", "Alright, mate? The devil in the blue dress got you playing her little game, has she? You're not going to have much luck against the vampire bats using just your bare hands.", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Prisoner", "I was thinking the same. Got a magical sword or something you can sell me?", p->mbColor.r, p->mbColor.g, p->mbColor.b);

				memset(message, 0, sizeof(message));
				sprintf(message, "I do! All I'll need is %d silver coins. You'll find plenty lying around the dungeon, I'm sure.", SILVER_REQUIRED);

				addMessageBox("Blacksmith", message, mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Prisoner", "Ha, I see. You'd melt down the silver into the blade of a magical weapon, to use against the bats?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
				addMessageBox("Blacksmith", "What? No! Those aren't real silver. They're just chocolate, wrapped in silver paper.", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Prisoner", "...", p->mbColor.r, p->mbColor.g, p->mbColor.b);
				addMessageBox("Prisoner", "What about gold?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
				addMessageBox("Blacksmith", "Got plenty of that, mate.", mbColor.r, mbColor.g, mbColor.b);

				b->state = STATE_NEED_SILVER;
				break;

			case STATE_NEED_SILVER:
				if (p->silver == 0)
				{
					addMessageBox("Blacksmith", "Let me know when you find all the silver.", mbColor.r, mbColor.g, mbColor.b);
				}
				else if (p->silver < SILVER_REQUIRED)
				{
					memset(message, 0, sizeof(message));
					sprintf(message, "Sorry, pal, still short %d. Gonna need all %d.", SILVER_REQUIRED - p->silver, SILVER_REQUIRED);

					addMessageBox("Prisoner", "I managed to find some.", p->mbColor.r, p->mbColor.g, p->mbColor.b);
					addMessageBox("Blacksmith", message, mbColor.r, mbColor.g, mbColor.b);
				}
				else
				{
					if (addToInventory(b->item))
					{
						addMessageBox("Prisoner", "Phew, I think that's all you need?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
						addMessageBox("Blacksmith", "Get in! You legend! Here's the dagger, as promised. You know how to use it?", mbColor.r, mbColor.g, mbColor.b);
						addMessageBox("Prisoner", "You stick 'em with the pointy end.", p->mbColor.r, p->mbColor.g, p->mbColor.b);
						addMessageBox("Blacksmith", "That's the spirit! Best of luck, mate.", mbColor.r, mbColor.g, mbColor.b);

						p->silver -= SILVER_REQUIRED;

						b->item = NULL;

						b->state = STATE_HAS_SILVER;
					}
					else
					{
						addMessageBox("Prisoner", "I can't carry anything else. I'll need to drop something before I can get the dagger.", p->mbColor.r, p->mbColor.g, p->mbColor.b);
					}
				}
				break;

			case STATE_HAS_SILVER:
				addMessageBox("Blacksmith", "Nom nom nom! These coins are really good. I love dark chocolate. None of that milk chocolate stuff for me.", mbColor.r, mbColor.g, mbColor.b);
				break;
		}
	}
}

static void load(Entity *e, cJSON *root)
{
	Blacksmith *blacksmith;

	blacksmith = (Blacksmith *)e->data;

	blacksmith->itemId = cJSON_GetObjectItem(root, "itemId")->valueint;
}
