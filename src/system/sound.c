
#include <SDL2/SDL_mixer.h>

#include "../common.h"

#include "sound.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSound(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);

	music = NULL;

	loadSounds();
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
	sounds[SND_WALK] = Mix_LoadWAV("sound/166506__yoyodaman234__concrete-footstep-4.ogg");
	sounds[SND_DOOR] = Mix_LoadWAV("sound/117415__joedeshon__wooden-door-close.ogg");
	sounds[SND_CHEST] = Mix_LoadWAV("sound/391947__ssierra1202__chest-openning-crack.ogg");
	sounds[SND_COIN] = Mix_LoadWAV("sound/368203__kermite607__coin-dropped.ogg");
	sounds[SND_ITEM] = Mix_LoadWAV("sound/571629__ugila__item-pickup.ogg");
	sounds[SND_SECRET] = Mix_LoadWAV("sound/195486__qubodup__nice-game-find.ogg");
	sounds[SND_CHAT] = Mix_LoadWAV("sound/273833__alienxxx__micro-clicks-001.ogg");
	sounds[SND_BAT] = Mix_LoadWAV("sound/468442__breviceps__video-game-squeak.ogg");
}
