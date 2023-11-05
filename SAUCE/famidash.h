
// game states
#define MENU 0x01
#define GAME 0x02




#pragma bss-name(push, "ZEROPAGE")
// zero-page variables go here

unsigned char i;
unsigned char run;
unsigned char value;
unsigned char tmp1;
unsigned char tmp2;
unsigned short tmp3;
unsigned short tmp4;







#pragma bss-name(push, "BSS")
// other variables go here
unsigned char gameState;
unsigned char a;



unsigned short address;



unsigned char collisionMap[432]; // collision map, for a 16*27 tile area
unsigned char columnBuffer[27];

struct player {
	unsigned short x; // low byte is sub-pixel
	unsigned short y;
	signed short vel_x; // speed, signed, low byte is sub-pixel
	signed short vel_y;
};

const unsigned char paletteDefault[] = {
    0x0F, 0x00, 0x10, 0x30,
    0x0F, 0x00, 0x10, 0x30,
    0x0F, 0x00, 0x10, 0x30,
    0x0F, 0x00, 0x10, 0x30
};





// prototypes
void load_ground(unsigned char id);