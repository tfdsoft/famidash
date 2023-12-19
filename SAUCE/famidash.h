// game states
#define MENU 0x01
#define GAME 0x02

// physics defines
#define PAD_HEIGHT_YELLOW -0x760

#define CUBE_WIDTH 0x0F
#define CUBE_HEIGHT 0x0F

#define JUMP_VEL -0x5B0
#define CUBE_SPEED_X1 0x2C4
#define CUBE_MAX_FALLSPEED 0x600
#define CUBE_GRAVITY 0x6B
#define SHIP_MAX_FALLSPEED 0x300
#define SHIP_GRAVITY 0x35

#pragma bss-name(push, "ZEROPAGE")
// zero-page variables go here

unsigned char tmp1;
unsigned char tmp2;
unsigned char tmp3;
unsigned char tmp4;
unsigned short tmp5;
unsigned short tmp6;

unsigned char pad;
unsigned char pad_new;

unsigned char gamemode;
unsigned char cube_data;
signed short cube_rotate;

unsigned char coordinates;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;

unsigned short old_x;
unsigned short old_y;

unsigned char gravity;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up

unsigned short address;
unsigned char x; // room loader code
unsigned char y;
unsigned short index;
unsigned short index2;
unsigned char temp_x;
unsigned char temp_y;
unsigned char temp_room;

#pragma bss-name(pop)
// other variables go here

unsigned char collisionMap0[240];   // collision map, for a 16*27 tile area
unsigned char collisionMap1[192];
const unsigned char * const active_level[] = {collisionMap0,collisionMap1};

unsigned char rld_column;
unsigned char spr_index;

unsigned char level;
unsigned char level_data_bank;
unsigned char * sprite_data;

unsigned char gameState;

unsigned long int scroll_x; // gotta love massive levels amirite fellas
unsigned short scroll_y;
unsigned char song;


// the funny uh uhhhhh um the uhh sprite storidge
// X_lowbyte, X_highbyte, Y_lowbyte, Y_highbyte, object id, unused, unused, unused
#define max_loaded_sprites 16
unsigned short activesprites_x[max_loaded_sprites];
unsigned short activesprites_y[max_loaded_sprites];
unsigned char activesprites_type[max_loaded_sprites];

unsigned char activesprites_realx[max_loaded_sprites];
unsigned char activesprites_realy[max_loaded_sprites];
unsigned char activesprites_active[max_loaded_sprites];







struct player {
	unsigned short x; // low byte is sub-pixel
	unsigned short y;
	signed short vel_x; // speed, signed, low byte is sub-pixel
	signed short vel_y;
};

struct player player = {0x0000,0xb000};

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic;
struct Base Generic2;





const unsigned char paletteDefault[16] = {
    0x11,0x0c,0x0f,0x30,	// palette 0, used for level tiles
	0x00,0x01,0x11,0x30,	// palette 1, used for ground
	0x00,0x28,0x14,0x30,	// palette 2, UNUSED
	0x00,0x0f,0x00,0x30 	// palette 3, used for text
};

const unsigned char paletteDefaultSP[16]={
	0x00,0x0f,0x2a,0x21,
	0x00,0x0f,0x24,0x28,
	0x00,0x0f,0x26,0x30,
	0x00,0x14,0x24,0x34 
};

const unsigned char paletteMenu[16] = {
	0x17,0x0f,0x11,0x30,
	0x17,0x0f,0x2a,0x28,
	0x17,0x0f,0x16,0x36,
	0x17,0x0f,0x0f,0x0f
};




