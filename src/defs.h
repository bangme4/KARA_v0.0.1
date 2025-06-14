
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define FPS		   60.0
#define LOGIC_RATE (FPS / 1000)

#define MAX_NAME_LENGTH		32
#define MAX_FILENAME_LENGTH 256
#define MAX_LINE_LENGTH		1024

#define NUM_ATLAS_BUCKETS 64

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16

#define TILE_SIZE 64

#define MAX_TILES 64

#define MAP_WIDTH  180
#define MAP_HEIGHT 90

#define MAP_RENDER_WIDTH  19
#define MAP_RENDER_HEIGHT 10

#define TILE_HOLE	0
#define TILE_GROUND 1
#define TILE_DARK	35
#define TILE_WALL	40

#define NUM_INVENTORY_SLOTS 2

enum
{
	FACING_LEFT,
	FACING_RIGHT
};

enum
{
	SOLID_NON_SOLID,
	SOLID_SOLID
};

enum
{
	ALIVE_ALIVE,
	ALIVE_DEAD
};

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	SND_WALK,
	SND_DOOR,
	SND_CHEST,
	SND_COIN,
	SND_ITEM,
	SND_SECRET,
	SND_CHAT,
	SND_BAT,
	SND_MAX
};
