typedef struct AtlasImage AtlasImage;
typedef struct Texture	  Texture;
typedef struct Entity	  Entity;
typedef struct MessageBox MessageBox;
typedef struct cJSON	  cJSON;
typedef struct InitFunc	  InitFunc;

struct AtlasImage
{
	char		 filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect	 rect;
	int			 rotated;
	AtlasImage  *next;
};

struct Texture
{
	char		 name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	Texture		*next;
};

typedef struct
{
	int data[MAP_WIDTH][MAP_HEIGHT];
} Map;

typedef struct
{
	int lightLevel;
	int hasSolidEntity;
} VisData;

struct MessageBox
{
	char		speaker[MAX_NAME_LENGTH];
	char		message[MAX_LINE_LENGTH];
	SDL_Color	color;
	MessageBox *next;
};

struct Entity
{
	unsigned long id;
	int			  x;
	int			  y;
	char		  name[MAX_NAME_LENGTH];
	int			  facing;
	int			  alive;
	int			  solid;
	AtlasImage   *texture;
	void(*data);
	void (*touch)(Entity *self, Entity *other);
	void (*load)(Entity *e, cJSON *root);
	void (*activate)(Entity *self);
	Entity *next;
};

typedef struct
{
	int		  gold;
	int		  silver;
	int		  silverFound;
	Entity   *inventorySlots[NUM_INVENTORY_SLOTS];
	int		  hasLantern;
	int		  hasDagger;
	SDL_Color mbColor;
} Prisoner;

typedef struct
{
	int		isOpen;
	int		itemId;
	Entity *item;
} Chest;

typedef struct
{
	char message[MAX_LINE_LENGTH];
} Signpost;

typedef struct
{
	int value;
} Gold;

typedef struct
{
	int state;
} Goblin;

typedef struct
{
	int iconsFound;
} DungeonMistress;

typedef struct
{
	int		state;
	int		itemId;
	Entity *item;
} Merchant;

typedef struct
{
	int		state;
	int		itemId;
	Entity *item;
} Blacksmith;

typedef struct
{
	int locked;
} Door;

typedef struct
{
	char target[MAX_NAME_LENGTH];
} Trigger;

typedef struct
{
	SDL_Point	  renderOffset;
	SDL_Point	  camera;
	Entity		  entityHead, *entityTail;
	MessageBox	  messageBoxHead, *messageBoxTail;
	Map			  map;
	unsigned long entityId;
	int			  numGold;
	int			  numSilver;
	int			  complete;
	double		  time;
} Dungeon;

struct InitFunc
{
	char type[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;
	SDL_Renderer *renderer;
	SDL_Window   *window;
	int			  keyboard[MAX_KEYBOARD_KEYS];
	double		  deltaTime;
	struct
	{
		int fps;
	} dev;
} App;
