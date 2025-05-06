
#include "../common.h"

#include "../game/fogOfWar.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "torch.h"

#define VIS_DISTANCE 32

void initTorch(Entity *e)
{
	e->texture = getAtlasImage("gfx/entities/torch.png", 1);
	e->solid = SOLID_SOLID;

	updateFogOfWar(e, VIS_DISTANCE);
}
