
// game states
#define MENU 0x01
#define GAME 0x02




#pragma bss-name(push, "ZEROPAGE")
// zero-page variables go here




#pragma bss-name(push, "BSS")
// other variables go here

unsigned char collisionMap[432];

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