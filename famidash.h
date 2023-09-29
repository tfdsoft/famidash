#define ACCEL 30
#define DECEL 50
#define GRAVITY 0x58
#define MAX_SPEED 0x240
#define JUMP_VEL -0x540
#define MAX_RIGHT 0x6000
#define CUBE_SPEED 0x0280



#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned short cube_rotate;
unsigned char pad1;
unsigned char pad1_new;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned int temp5;
unsigned int temp6;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up
unsigned char direction; //facing left or right?
#define LEFT 0
#define RIGHT 1

int address;
unsigned short x; // room loader code
unsigned char y;
unsigned char nt;
unsigned char index;
unsigned char room;
unsigned char map;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char scroll_count;
unsigned int pseudo_scroll_x;
//unsigned int pseudo_scroll_y;
unsigned char L_R_switch;
unsigned int old_x;
//unsigned int old_y;
unsigned char temp_x;
unsigned char temp_y;

unsigned char map_loaded; //only load it once
unsigned char temp_room;

unsigned char song;
#define MAX_SONGS 1
enum {SONG_GAME, SONG_PAUSE};




#pragma bss-name(push, "BSS")

unsigned char c_map[240];
unsigned char c_map2[240];

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic; 

struct CUBE {
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
};

struct CUBE Cube = {0x1000,0xb400}; // starting position
// the width and height should be 1 less than the dimensions (14x12)
// note, I'm using the top left as the 0,0 on x,y

#define CUBE_WIDTH 15
#define CUBE_HEIGHT 15







const unsigned char palette_bg[]={
0x21,0x0c,0x0f,0x30,
0x21,0x01,0x1c,0x30,
0x21,0x28,0x14,0x20,
0x21,0x0f,0x00,0x20
}; 




const unsigned char palette_sp[]={
0x00,0x0f,0x2a,0x21,
0x00,0x12,0x22,0x32,
0x00,0x13,0x23,0x33,
0x00,0x14,0x24,0x34 
}; 


// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes
// 5th byte, 	1000 0000 = floor collision
// 				0100 0000 = all collision, solid
//				0000 0011 = palette

const unsigned char metatiles1[]={
	0, 0, 0, 0,  0,
	10, 11, 26, 3,  1,
	26, 3, 42, 43,  1,
	42, 43, 42, 27,  1,
	42, 27, 58, 59,  1,
	11, 11, 3, 3,  1,
	3, 3, 43, 43,  1,
	43, 43, 27, 27,  1,
	27, 27, 59, 59,  1,
	11, 12, 3, 28,  1,
	3, 28, 43, 44,  1,
	43, 44, 27, 44,  1,
	27, 44, 59, 60,  1,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,

	32, 33, 48, 49,  0,
	34, 35, 50, 51,  0,
	0, 0, 52, 53,  0,
	0, 0, 176, 177,  2,
	162, 163, 178, 179,  2,
	0, 0, 180, 181,  2,
	166, 167, 182, 183,  2,
	226, 231, 0, 0,  0,
	0, 0, 54, 55,  0,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,
	1, 1, 1, 1,  0,

	64, 65, 80, 81,  0,
	68, 69, 86, 87,  0,
	70, 67, 86, 83,  0,
	70, 71, 84, 85,  0,
	66, 71, 82, 87,  0,
	64, 69, 82, 87,  0,
	68, 65, 86, 83,  0,
	70, 67, 84, 81,  0,
	66, 71, 80, 85,  0,
	72, 71, 86, 87,  0,
	70, 73, 86, 87,  0,
	70, 71, 86, 89,  0,
	70, 71, 88, 87,  0,
	66, 67, 82, 83,  0,
	68, 69, 84, 85,  0
};


#define COL_DEATH 0x80
#define COL_ALL 0x40

const unsigned char is_solid[]={

	// go find famidash.bmp for a reference point

	0,			// the blank tile
	COL_ALL,	// start of ground tiles
	COL_ALL,
	COL_ALL, 
	COL_ALL, 
	COL_ALL,
	COL_ALL,
	COL_ALL, 
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,	// end of ground tiles
	0,
	0,
	0,
	
	COL_ALL,	// default block
	COL_DEATH,	// big spike
	COL_DEATH,	// small spike
	0,			// yellow pad
	0, 			// yellow orb
	0,			// pink pad
	0,			// pink orb
	0,			// bg trigger
	COL_DEATH,	// ground spikes
	0,
	0,
	0,
	0,
	0,
	0,
	0,

	COL_ALL,	// default block 2
	COL_ALL,	// start of checkerboard blocks
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,	// end of checkerboard blocks
	0
};



#include "BG/Room1.c"

#define MAX_ROOMS (8-1)
#define MAX_SCROLL (MAX_ROOMS*0x100)-1
// data is exactly 240 bytes, 16 * 15
// doubles as the collision map data


const unsigned char * const Rooms[]= {
	Room1_0,Room1_1,Room1_2,Room1_3,Room1_4,Room1_5,Room1_6,Room1_7
};


// PROTOTYPES
void load_room(void);
void draw_sprites(void);
void movement(void);	
void draw_screen_R(void);
void new_cmap(void);
void die_lmao(void);

char bg_collision_sub(void);
char bg_coll_L(void);
char bg_coll_R(void);
char bg_coll_U(void);
char bg_coll_D(void);
char bg_coll_D2(void);
char bg_coll_death(void);