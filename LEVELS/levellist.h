// LEVEL ORDERING =============================================
// 
// NOTE: DO *NOT* PUT LEVEL DATA HERE.
// Level order is defined here, and consists of 3 tables. The 
// first table specifies the level data pointers, the second -
// sprite data pointers, and the third one - the ROM bank of 
// the level data. Here is an example:
//
// const unsigned char * const your_moms_house[] = {
//    level_name_1_, 
//    level_name_2_,
//    level_name_3_
//  };
//
// const unsigned char * const your_moms_sprites[] = {
//    level_name_1_SP,
//    level_name_2_SP,
//    level_name_3_SP,
// };
//
// const unsigned char your_moms_bank_account[] = {
//    0, // Level data starts in bank 0,
//    1,
//    2,
// }
// ============================================================
// go wild

#define	EASY 0
#define	NORMAL 1
#define	HARD 2
#define	HARDER 3
#define	INSANE 4
#define	DEMON 5
#define	AUTO 6


#define SPIKESA 0
#define SPIKESB 2
#define SPIKESC 4
#define BLOCKSA 6
#define BLOCKSB 8
#define BLOCKSC 10
#define BLOCKSD 12
#define SAWBLADESA 14
#define LETTERBANK 111

#define DECO1 28
#define DECOCLOUD 32
#define EXTRASPRITES1 36

const uint8_t DECOTYPE[] = {
	DECO1, //sm
	DECO1, //depression madness
	DECO1, //xmas
	DECO1, //test4
};

const unsigned char spike_set[] = {
	SPIKESA, //stereo madness
	SPIKESA, //depression madness
	SPIKESA, //nine circles
	SPIKESA, //cmas again
	SPIKESC, //test4
};

const unsigned char block_set[] = {
	BLOCKSA, //stereo madness
	BLOCKSA, //depression madness
	BLOCKSB, //nine circles
	BLOCKSB, //xmas yet again
	BLOCKSB, //test4
};

const unsigned char saw_set[] = {
	SAWBLADESA, //stereo madness
	SAWBLADESA, //depression madness
	SAWBLADESA, //nine circles
	SAWBLADESA, //xmas yet again 2: electric boogaloo
	SAWBLADESA, //test4
};


const unsigned char difficulty_list[] = {
    EASY, // stereo madness for some reaosn
    AUTO, //depression madness
	INSANE, //i think you get it by this point
	HARD, //feliz navisdad
    AUTO, //test4
};

const unsigned char stars_list[] = {
	1,
	69,   //depression madness
	10,   //FUCKING NINE CIRCLES AGAINASDKJFADSJLLGHADSJLF
	0, //test4
};
const unsigned char colors_list[] = {
	0x12,
	0x14,
	0x15,
	0x16,
	0x17,
	0x28,
	0x2A,
	0x2C,
	0x11,
};
// exported from export_levels.py





static const uint8_t iconTable[] = {
	0, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x20, 0x22, 0x24, 0x26, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4A, 0x4C, 0x4E, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E
};


extern const unsigned char level_list_lo[];
extern const unsigned char level_list_hi[];
extern const unsigned char level_list_bank[];
extern const unsigned char sprite_list_lo[];
extern const unsigned char sprite_list_hi[];
extern const unsigned char sprite_list_bank[];