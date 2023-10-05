#define ACCEL 30
#define DECEL 50
#define GRAVITY 0x6C
#define MAX_SPEED 0x240
#define JUMP_VEL -0x5B0
#define MAX_RIGHT 0x6000
#define CUBE_SPEED 0x02C4
#define YEL_PAD_HEIGHT -0x760
//#define CUBE_SPEED 0x0000

#define CUBE_DEATH 0x01
#define CUBE_ORBJUMP 0x02


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
#define MAX_SONGS 5
enum {SONG_GAME, SONG_PAUSE};




#pragma bss-name(push, "BSS")

unsigned char cube_data = 0;






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

struct CUBE Cube = {0x0000,0xb400}; // starting position
// the width and height should be 1 less than the dimensions (14x12)
// note, I'm using the top left as the 0,0 on x,y

#define CUBE_WIDTH 15
#define CUBE_HEIGHT 15










const unsigned char palette_bg[]={
0x21,0x0c,0x0f,0x30,
0x21,0x01,0x11,0x30,
0x21,0x28,0x14,0x30,
0x21,0x0f,0x00,0x30
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
	10, 11, 26, 27,  1,
	26, 27, 26, 27,  1,
	42, 43, 42, 43,  1,
	42, 43, 58, 59,  1,
	11, 11, 27, 27,  1,
	27, 27, 27, 27,  1,
	43, 43, 43, 43,  1,
	43, 43, 59, 59,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,

	32, 33, 48, 49,  0,
	34, 35, 50, 51,  0,
	0, 0, 52, 53,  0,
	0, 0, 176, 177,  2,
	162, 163, 178, 179,  2,
	0, 0, 180, 181,  2,
	166, 167, 182, 183,  2,
	226, 231, 0, 0,  0,
	0, 0, 54, 55,  0,
	36, 37, 0, 0,  0,
	12, 13, 28, 29,  0,
	44, 45, 60, 61,  0,
	14, 15, 30, 31,  0,
	40, 0, 56, 0,  0,
	38, 39, 0, 0,  0,
	0, 41, 0, 57,  0,

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
	68, 69, 84, 85,  0,
	70, 71, 86, 87,  0,

	64, 65, 82, 83,  0,
	68, 65, 84, 81,  0,
	66, 67, 80, 81,  0,
	64, 69, 80, 85,  0
};



#define COL_DEATH 0x80
#define COL_ALL 0x40
#define COL_YEL_ORB 0x20
#define COL_YEL_PAD 0x10

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
	COL_YEL_PAD,// yellow pad
	COL_YEL_ORB,// yellow orb
	0,			// pink pad
	0,			// pink orb
	0,			// bg trigger
	COL_DEATH,	// ground spikes
	COL_ALL,	// half-slab 2
	COL_DEATH,	// the other spikes
	COL_DEATH,
	COL_DEATH,
	COL_DEATH,
	COL_DEATH,
	COL_DEATH,

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
	0,

	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL
};



#include "BG/Room1.c"

#define MAX_ROOMS 58
#define MAX_SCROLL (MAX_ROOMS*0x100)-1
// data is exactly 240 bytes, 16 * 15
// doubles as the collision map data


const unsigned char * const Rooms[]= {
	Room1_0,Room1_1,Room1_2,Room1_3,
	Room1_4,Room1_5,Room1_6,Room1_7,
	Room1_8,Room1_9,Room1_10,Room1_11,
	Room1_12,Room1_13,Room1_14,Room1_15,

	Room1_16,Room1_17,Room1_18,Room1_19,
	Room1_20,Room1_21,Room1_22,Room1_23,
	Room1_24,Room1_25,Room1_26,Room1_27,
	Room1_28,Room1_29,Room1_30,Room1_31,

	Room1_32,Room1_33,Room1_34,Room1_35,
	Room1_36,Room1_37,Room1_38,Room1_39,
	Room1_40,Room1_41,Room1_42,Room1_43,
	Room1_44,Room1_45,Room1_46,Room1_47,

	Room1_48,Room1_49,Room1_50,Room1_51,
	Room1_52,Room1_53,Room1_54,Room1_55,
	Room1_56,Room1_57
};





// PROTOTYPES
void load_room(void);
void draw_sprites(void);
void movement(void);	
void draw_screen_R(void);
void new_cmap(void);
void reset_level(void);
void orbjump(void);
void padjump(void);

char bg_collision_sub(void);
char bg_coll_L(void);
char bg_coll_R(void);
char bg_coll_U(void);
char bg_coll_D(void);
char bg_coll_D2(void);
char bg_coll_death(void);
char bg_coll_orbs(void);
char bg_coll_pads(void);