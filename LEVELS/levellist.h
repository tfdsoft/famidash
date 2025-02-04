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
#define	DANGER 6


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
	DECO1, //level easy
//	EXTRASPRITES1, //dear nostalgists
	DECO1, //super cycles
	DECO1, //clutterfunk 2
	DECO1, //pg clubstep
	EXTRASPRITES1, //eon
	DECO1, //cataclysm
	DECO1, //aftermath
	DECO1, //aftercatabath
};

const unsigned char spike_set[] = {
	SPIKESA, //stereo madness
	SPIKESA, //level easy
//	SPIKESC, //dear nostalgists
	SPIKESA, //super cycles
	SPIKESA, //clutterfunk 2
	SPIKESA, //pg clubstep
	SPIKESB, //eon
	SPIKESC, //cataclysm
	SPIKESC, //aftermath
	SPIKESC, //aftercatabath
};

const unsigned char block_set[] = {
	BLOCKSA, //stereo madness
	BLOCKSA, //level easy
//	BLOCKSA, //dear nostalgists
	BLOCKSB, //super cycles
	BLOCKSB, //clutterfunk 2
	BLOCKSB, //pg clubstep
	BLOCKSA, //eon
	BLOCKSB, //cataclysm
	BLOCKSB, //aftermath
	BLOCKSB, //aftercatabath
};

const unsigned char saw_set[] = {
	SAWBLADESA, //stereo madness
	SAWBLADESA, //level easy
//	SAWBLADESA, //dear nostalgists
	SAWBLADESA, //super cycles
	SAWBLADESA, //clutterfunk 2
	SAWBLADESA, //PG CLUBSTEP
	SAWBLADESA, //eon
	SAWBLADESA, //cataclysm
	SAWBLADESA, //aftermath
	SAWBLADESA, //aftercatabath
};


const unsigned char difficulty_list[] = {
    EASY,
    NORMAL, //level easy
//    DEMON, //dear nostalgists
    DEMON, //super cycles
    DEMON, //clutterfunk 2
    DEMON, //pg clubstep
    DEMON, //eon
    DEMON, //cataclysm
    DEMON, //aftermath
    DEMON, //aftercatabath
};

const unsigned char stars_list[] = {
	1,
	3,   //level easy
//	10, //dear nostlagists
	10, //super cycles
	10, //clutterfunk 2
	10, //pg clubstep
	10, //eon
	10, //cataclysm
	10, //aftermath
	10, //aftercatabath
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