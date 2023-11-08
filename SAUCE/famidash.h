
// game states
#define MENU 0x01
#define GAME 0x02

// physics defines
#define CUBE_SPEED_X1 0x02C4
#define PAD_HEIGHT_YELLOW -0x760



#pragma bss-name(push, "ZEROPAGE")
// zero-page variables go here

unsigned char tmp1;
unsigned char tmp2;
unsigned char tmp3;
unsigned char tmp4;

unsigned char pad;
unsigned char pad_new;





#pragma bss-name(push, "BSS")
// other variables go here

unsigned char collisionMap0[240];   // collision map, for a 16*27 tile area
unsigned char collisionMap1[192];
unsigned char columnBuffer[27];     // column buffer, to be pushed to the collision map

unsigned char rld_column;

unsigned char level;

unsigned char gameState;

unsigned short pseudo_scroll_x;
unsigned short scroll_x;
unsigned char scroll_y;
unsigned char scroll_count;

unsigned short address;
unsigned char x; // room loader code
unsigned char y;
unsigned short index;



const unsigned char * const active_level[] = {collisionMap0,collisionMap1};

struct player {
	unsigned short x; // low byte is sub-pixel
	unsigned short y;
	signed short vel_x; // speed, signed, low byte is sub-pixel
	signed short vel_y;
};

const unsigned char paletteDefault[] = {
    0x11,0x0c,0x0f,0x30,	// palette 0, used for level tiles
	0x0f,0x01,0x11,0x30,	// palette 1, used for ground
	0x0f,0x28,0x14,0x30,	// palette 2, UNUSED
	0x0f,0x0f,0x00,0x30 	// palette 3, used for text
};





// prototypes