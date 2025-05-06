
#include "../common.h"

#include "../game/inventory.h"
#include "../game/messageBox.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "merchant.h"

#define STATE_INIT		 0
#define STATE_WANT_ALBUM 1
#define STATE_HAS_ALBUM	 2

extern Entity *player;

static void touch(Entity *self, Entity *other);
static void load(Entity *e, cJSON *root);

static SDL_Color mbColor;

void initMerchant(Entity *e)
{
	Merchant *merchant;
	merchant = malloc(sizeof(Merchant));
	memset(merchant, 0, sizeof(Merchant));

	STRCPY(e->name, "Merchant");
	e->texture = getAtlasImage("gfx/entities/merchant.png", 1);
	e->solid = SOLID_SOLID;
	e->data = merchant;

	e->touch = touch;
	e->load = load;

	mbColor.r = 16;
	mbColor.g = 32;
	mbColor.b = 64;
}

static void touch(Entity *self, Entity *other)
{
	Merchant *m;
	Prisoner *p;

	if (other == player)
	{
		self->facing = (other->x > self->x) ? FACING_RIGHT : FACING_LEFT;

		m = (Merchant *)self->data;
		p = (Prisoner *)other->data;

		switch (m->state)
		{
			case STATE_INIT:
				addMessageBox("Merchant", "Hey, I hear you've been tasked with finding all those magical icons. I might have something that will help you.", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Prisoner", "A map?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
				addMessageBox("Merchant", "Noooooo, don't be silly. A lantern, to help you find your way through the crushing darkness of The Cursed Maze, over in east.", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Prisoner", "How much gold will it cost me?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
				addMessageBox("Merchant", "Gold? I don't want gold, I've got plenty of that already. What I want is a copy of Fleetwood Mac's Rumours album, on vinyl. I heard there's a copy somewhere in this dungeon.", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Prisoner", "Would a 192kbs MP3 do?", p->mbColor.r, p->mbColor.g, p->mbColor.b);
				addMessageBox("Merchant", "...", mbColor.r, mbColor.g, mbColor.b);
				addMessageBox("Prisoner", "Sorry, that was in poor taste.", p->mbColor.r, p->mbColor.g, p->mbColor.b);

				m->state = STATE_WANT_ALBUM;
				break;

			case STATE_WANT_ALBUM:
				if (hasInventoryItem("Rumours"))
				{
					addMessageBox("Prisoner", "I found this in the store room.", p->mbColor.r, p->mbColor.g, p->mbColor.b);
					addMessageBox("Merchant", "No way! That's awesome. I've got the album on CD, but vinyl just sounds better, you know.", mbColor.r, mbColor.g, mbColor.b);
					addMessageBox("Prisoner", "That's not actually true, it's ...", p->mbColor.r, p->mbColor.g, p->mbColor.b);
					addMessageBox("Merchant", "VINYL. SOUNDS. BETTER. Nick Cage said so, in The Rock.", mbColor.r, mbColor.g, mbColor.b);
					addMessageBox("Prisoner", "Actually a decent Michael Bay film, that.", p->mbColor.r, p->mbColor.g, p->mbColor.b);
					addMessageBox("Merchant", "Agreed. Anyway, here's the lantern I promised you.", mbColor.r, mbColor.g, mbColor.b);
					addMessageBox("Prisoner", "What the heck?!", p->mbColor.r, p->mbColor.g, p->mbColor.b);
					addMessageBox("Merchant", "Okay, it's a Jack-o'-lantern, but it still works.", mbColor.r, mbColor.g, mbColor.b);
					addMessageBox("Prisoner", "Right ...", p->mbColor.r, p->mbColor.g, p->mbColor.b);

					removeInventoryItem("Rumours");

					addToInventory(m->item);

					m->item = NULL;

					m->state = STATE_HAS_ALBUM;
				}
				else
				{
					addMessageBox("Merchant", "Let me know if you find that Rumours record, will you?", mbColor.r, mbColor.g, mbColor.b);
				}
				break;

			case STATE_HAS_ALBUM:
				addMessageBox("Merchant", "Can't wait to get home tonight and whack this bad boy on my turntable.", mbColor.r, mbColor.g, mbColor.b);
				break;

			default:
				break;
		}
	}
}

static void load(Entity *e, cJSON *root)
{
	Merchant *merchant;

	merchant = (Merchant *)e->data;

	merchant->itemId = cJSON_GetObjectItem(root, "itemId")->valueint;
}
