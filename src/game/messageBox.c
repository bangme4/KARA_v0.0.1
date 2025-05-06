
#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/sound.h"
#include "../system/text.h"
#include "messageBox.h"

extern App	   app;
extern Dungeon dungeon;

static AtlasImage *messageBoxArrow;
static double	   messageBoxTimer;
static int		   messageBoxTextIndex;
static double	   messageBoxArrowPulse;

void initMessageBox(void)
{
	messageBoxArrow = getAtlasImage("gfx/misc/messageBoxArrow.png", 1);

	messageBoxTimer = 1;
	messageBoxTextIndex = 0;
	messageBoxArrowPulse = 0;
}

void doMessageBox(void)
{
	MessageBox  *msg;
	unsigned int len;

	msg = dungeon.messageBoxHead.next;

	if (msg != NULL)
	{
		messageBoxArrowPulse += (0.15 * app.deltaTime);

		messageBoxTimer = MAX(messageBoxTimer - app.deltaTime, 0);

		if (messageBoxTimer == 0)
		{
			len = strlen(msg->message) + 1;

			messageBoxTextIndex = MIN(messageBoxTextIndex + 1, len);

			messageBoxTimer = 1;

			if (messageBoxTextIndex < len && messageBoxTextIndex % 4 == 0)
			{
				playSound(SND_CHAT, 0);
			}
		}

		if (app.keyboard[SDL_SCANCODE_SPACE] || app.keyboard[SDL_SCANCODE_RETURN])
		{
			app.keyboard[SDL_SCANCODE_SPACE] = app.keyboard[SDL_SCANCODE_RETURN] = 0;

			dungeon.messageBoxHead.next = msg->next;

			if (msg->next == NULL)
			{
				dungeon.messageBoxTail = &dungeon.messageBoxHead;
			}

			free(msg);

			messageBoxTimer = 1;

			messageBoxTextIndex = 0;
		}
	}
}

void drawMessageBox(void)
{
	MessageBox *msg;
	char		text[MAX_LINE_LENGTH];
	SDL_Rect	box;

	msg = dungeon.messageBoxHead.next;

	if (msg != NULL)
	{
		memset(text, 0, sizeof(text));

		STRNCPY(text, msg->message, messageBoxTextIndex);

		box.w = 600;
		box.h = getWrappedTextHeight(msg->message, box.w);
		box.x = (SCREEN_WIDTH - box.w) / 2;
		box.y = 80;

		box.x -= 10;
		box.w += 20;
		box.y -= 5;
		box.h += 5;

		drawRect(box.x, box.y, box.w, box.h, msg->color.r, msg->color.g, msg->color.b, 192);

		drawOutlineRect(box.x, box.y, box.w, box.h, 255, 255, 255, 128);

		drawText(msg->speaker, box.x, box.y - 45, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
		drawText(text, box.x + 10, box.y, 255, 255, 255, TEXT_ALIGN_LEFT, 600);

		if (msg->next != NULL)
		{
			blitAtlasImage(messageBoxArrow, box.x + box.w, box.y + box.h + (sin(messageBoxArrowPulse) * 8), 1, SDL_FLIP_NONE);
		}
	}
}

void addMessageBox(char *speaker, char *message, int r, int g, int b)
{
	MessageBox *msg;

	msg = malloc(sizeof(MessageBox));
	memset(msg, 0, sizeof(MessageBox));
	dungeon.messageBoxTail->next = msg;
	dungeon.messageBoxTail = msg;

	STRCPY(msg->speaker, speaker);
	STRCPY(msg->message, message);
	msg->color.r = r;
	msg->color.g = g;
	msg->color.b = b;
}
