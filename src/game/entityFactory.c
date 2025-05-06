
#include "../common.h"

#include "../game/bat.h"
#include "../game/blacksmith.h"
#include "../game/chest.h"
#include "../game/door.h"
#include "../game/dungeonMistress.h"
#include "../game/entities.h"
#include "../game/fakeWall.h"
#include "../game/goblin.h"
#include "../game/gold.h"
#include "../game/item.h"
#include "../game/merchant.h"
#include "../game/player.h"
#include "../game/signpost.h"
#include "../game/silver.h"
#include "../game/stairs.h"
#include "../game/torch.h"
#include "../game/trigger.h"
#include "../game/wall.h"
#include "../json/cJSON.h"
#include "entityFactory.h"

extern Dungeon dungeon;

static void addInitFunc(const char *id, void (*init)(Entity *e));

static InitFunc initFuncHead, *initFuncTail;

void initEntityFactory(void)
{
	memset(&initFuncHead, 0, sizeof(InitFunc));
	initFuncTail = &initFuncHead;

	addInitFunc("player", initPlayer);
	addInitFunc("item", initItem);
	addInitFunc("chest", initChest);
	addInitFunc("gold", initGold);
	addInitFunc("silver", initSilver);
	addInitFunc("signpost", initSignpost);
	addInitFunc("torch", initTorch);
	addInitFunc("goblin", initGoblin);
	addInitFunc("door", initDoor);
	addInitFunc("dungeonMistress", initDungeonMistress);
	addInitFunc("merchant", initMerchant);
	addInitFunc("blacksmith", initBlacksmith);
	addInitFunc("bat", initBat);
	addInitFunc("wall", initWall);
	addInitFunc("fakeWall", initFakeWall);
	addInitFunc("trigger", initTrigger);
	addInitFunc("stairs", initStairs);
}

static void addInitFunc(const char *type, void (*init)(Entity *e))
{
	InitFunc *initFunc;

	initFunc = malloc(sizeof(InitFunc));
	memset(initFunc, 0, sizeof(InitFunc));
	initFuncTail->next = initFunc;
	initFuncTail = initFunc;

	STRCPY(initFunc->type, type);
	initFunc->init = init;
}

void initEntity(cJSON *root)
{
	char	 *type;
	InitFunc *initFunc;
	Entity   *e;

	type = cJSON_GetObjectItem(root, "type")->valuestring;

	for (initFunc = initFuncHead.next; initFunc != NULL; initFunc = initFunc->next)
	{
		if (strcmp(initFunc->type, type) == 0)
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading entity '%s'", type);

			e = spawnEntity();

			e->id = cJSON_GetObjectItem(root, "id")->valueint;
			e->x = cJSON_GetObjectItem(root, "x")->valueint;
			e->y = cJSON_GetObjectItem(root, "y")->valueint;

			if (cJSON_GetObjectItem(root, "name"))
			{
				STRCPY(e->name, cJSON_GetObjectItem(root, "name")->valuestring);
			}

			initFunc->init(e);

			if (e->load != NULL)
			{
				e->load(e, root);
			}

			dungeon.entityId = MAX(e->id, dungeon.entityId) + 1;

			return;
		}
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Unknown entity type '%s'", type);
	exit(1);
}
