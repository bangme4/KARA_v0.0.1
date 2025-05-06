
#include "../common.h"

#include "../system/text.h"
#include "draw.h"

extern App app;

static void showFPS(void);

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 8, 8, 8, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	if (0)
	{
		showFPS();
	}

	SDL_RenderPresent(app.renderer);
}

static void showFPS(void)
{
	char fps[8];

	memset(fps, 0, sizeof(fps));

	sprintf(fps, "%d", app.dev.fps);

	drawText(fps, SCREEN_WIDTH - 10, 0, 255, 255, 255, TEXT_ALIGN_RIGHT, 0);
}

void blit(SDL_Texture *texture, int x, int y, int center)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = atlasImage->rect.w;
	dest.h = atlasImage->rect.h;

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->rect, &dest, 0, NULL, flip);
}

void blitAtlasImageScaled(AtlasImage *atlasImage, int x, int y, int w, int h, int center)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	if (center)
	{
		dest.x -= w / 2;
		dest.y -= h / 2;
	}

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->rect, &dest, 0, NULL, SDL_FLIP_NONE);
}

void drawRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawBlendMode(app.renderer, a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_RenderFillRect(app.renderer, &rect);
}

void drawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawBlendMode(app.renderer, a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_RenderDrawRect(app.renderer, &rect);
}
