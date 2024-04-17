// game states
#define MENU 0x01
#define GAME 0x02

// physics defines
#define PAD_HEIGHT_YELLOW -0x7A0
#define PAD_HEIGHT_PINK -0x4A0
#define PAD_HEIGHT_BLUE -0x3A0

#define ORB_BALL_HEIGHT_BLUE -0x1A0

#define CUBE_WIDTH 0x0F
#define CUBE_HEIGHT 0x0F

#define MINI_CUBE_WIDTH 0x07
#define MINI_CUBE_HEIGHT 0x07

#define JUMP_VEL -0x5B0
#define MINI_JUMP_VEL -0x5B0
#define UFO_JUMP_VEL -0x530

#define ROBOT_JUMP_VEL -0x2B0
#define MINI_ROBOT_JUMP_VEL -0x2B0

#define CUBE_SPEED_X05 0x162
#define CUBE_SPEED_X1 0x2C4
#define CUBE_SPEED_X2 0x588

#define ROBOT_JUMP_TIME 16

#define CUBE_MAX_FALLSPEED 0x600
#define MINI_CUBE_MAX_FALLSPEED 0x500
#define MINI_UFO_MAX_FALLSPEED 0x500

#define CUBE_GRAVITY 0x6B
#define MINI_CUBE_GRAVITY 0x6F

#define BALL_GRAVITY 0x6B
#define MINI_BALL_GRAVITY 0x6F

#define SHIP_MAX_FALLSPEED 0x300
#define MINI_SHIP_MAX_FALLSPEED 0x340

#define SHIP_GRAVITY 0x35
#define MINI_SHIP_GRAVITY 0x35

#pragma allow-eager-inline(on)

#pragma bss-name(push, "ZEROPAGE")
// zero-page variables go here

unsigned char tmp1;
unsigned char tmp2;
unsigned char tmp3;
unsigned char tmp4;
unsigned short tmp5;
unsigned short tmp6;
unsigned char* tmpptr1;
unsigned char* tmpptr2;
long unsigned int tmplong;

unsigned char pad[2];
unsigned char pad_new[2];

unsigned char gamemode;
unsigned char cube_data[2];
// unsigned char cube_data2;
unsigned short cube_rotate[2];



unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;

unsigned short old_x;
unsigned short old_y;

//unsigned char gravity;
unsigned char mini;
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
unsigned char dual;
unsigned char twoplayer;

unsigned char * sprite_data;
unsigned char* level_data;

#pragma bss-name(pop)
// other variables go here

#pragma bss-name(push, "SRAM")
unsigned char SRAM_VALIDATE[4];

unsigned char LEVEL1COINS;
unsigned char LEVEL2COINS;
unsigned char LEVEL3COINS;
unsigned char LEVEL4COINS;
unsigned char LEVEL5COINS;
unsigned char LEVEL6COINS;
unsigned char LEVEL7COINS;
unsigned char LEVEL8COINS;
unsigned char LEVEL9COINS;
unsigned char LEVELACOINS;

unsigned char LEVELCOMPLETE[0x20];

#pragma bss-name(pop)

unsigned char TOTALCOINS;
unsigned long TOTALCOINSTEMP;
unsigned char TOTALATTEMPTSHUNDREDS;
unsigned char TOTALATTEMPTSTHOUSANDS;
unsigned char TOTALCOINSTENS;
unsigned char TOTALCOINSONES;
unsigned char coins;

unsigned short player_x[2];
unsigned short player_y[2];
signed short player_vel_x[2];
signed short player_vel_y[2];
unsigned char player_gravity[2];

unsigned char collisionMap0[240];   // collision map, for a 16*27 tile area
unsigned char collisionMap1[192];
const unsigned char * const active_level[] = {collisionMap0,collisionMap1};

unsigned char rld_column;
unsigned char spr_index;

unsigned char speed;
unsigned char shuffle_offset;
unsigned char count;
unsigned char kandotemp;                                                                                              
unsigned char kandotemp2[2];
unsigned char kandotemp5;
unsigned char kandoframecnt;
unsigned long attempts;
unsigned char currplayer;
unsigned char controllingplayer;
unsigned char spiderframe[2];
unsigned char robotframe[2];
unsigned char ballframe;
unsigned char robotjumpframe[2];
unsigned char robotjumptime[2];
unsigned char level;
unsigned char level_data_bank;

unsigned char gameState;

unsigned char parallax_scroll_x;
unsigned char invincible_counter;
unsigned long int scroll_x; // gotta love massive levels amirite fellas
unsigned short scroll_y;
unsigned char song;


// the funny uh uhhhhh um the uhh sprite storidge
// X_lowbyte, X_highbyte, Y_lowbyte, Y_highbyte, object id, unused, unused, unused
#define max_loaded_sprites 16
unsigned short activesprites_x[max_loaded_sprites];
unsigned short activesprites_y[max_loaded_sprites];
unsigned char activesprites_type[max_loaded_sprites];
unsigned char activesprites_anim_frame[max_loaded_sprites];
signed char activesprites_anim_frame_count[max_loaded_sprites];

unsigned char activesprites_realx[max_loaded_sprites];
unsigned char activesprites_realy[max_loaded_sprites];
unsigned char activesprites_active[max_loaded_sprites];




unsigned char DEBUG_MODE = 0;




//struct player {
//	unsigned short x; // low byte is sub-pixel
//	unsigned short y;
//	signed short vel_x; // speed, signed, low byte is sub-pixel
//	signed short vel_y;
//};

//struct player player = {0x0000,0xb000};

//struct player2 {
//	unsigned short x; // low byte is sub-pixel
//	unsigned short y;
//	signed short vel_x; // speed, signed, low byte is sub-pixel
//	signed short vel_y;
//};

//struct player2 player2 = {0x0000,0xb000};

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
	0x00,0x88,0x14,0x30,	// palette 2, UNUSED
	0x00,0x0f,0x00,0x30 	// palette 3, used for text
};

const unsigned char paletteDefaultSP[16]={
	0x00,0x0f,0x2a,0x21,
	0x00,0x0f,0x24,0x28,
	0x00,0x0f,0x26,0x30,
	0x00,0x14,0x24,0x24 
};

const unsigned char paletteMenu[16] = {
	0x17,0x0f,0x10,0x30,
	0x17,0x0f,0x2a,0x28,
	0x17,0x0f,0x17,0x27,
	0x17,0x0f,0x11,0x30
};

