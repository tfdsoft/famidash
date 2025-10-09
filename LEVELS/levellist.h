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
#define BLOCKSA 4
#define BLOCKSB 6
#define BLOCKSC 8
#define BLOCKSD 10
#define SAWBLADESA 12
#define LETTERBANK 96

#define DECO1 26
#define DECOCLOUD 30
#define EXTRASPRITES1 34

const uint8_t DECOTYPE[] = {
	DECO1,
	DECO1,
	DECO1,
	DECO1,
	DECO1,
	DECO1,
	DECO1,
	DECO1,
	DECO1,
	DECOCLOUD,
	DECOCLOUD, //clutterfunk
	DECOCLOUD,
	DECOCLOUD,
	DECOCLOUD,
	DECOCLOUD,
	DECOCLOUD, //lucky draw
	EXTRASPRITES1,
	EXTRASPRITES1,
	DECOCLOUD,
	EXTRASPRITES1,
};

const unsigned char spike_set[] = {
	SPIKESA, //stereo madness
	SPIKESA, //back on track
	SPIKESA, //polargeist
	SPIKESA, //dryout
	SPIKESA, //base after base
	SPIKESA, //cant let go
	SPIKESA, //jumper
	SPIKESA, //time machine
	SPIKESA, //cycles
	SPIKESB, //xstep
	SPIKESB, //clutterfunk
	SPIKESB, //theory of everything
	SPIKESB, //electroman
	SPIKESB, //nightmare
	SPIKESB, //decode
	SPIKESB, //lucky draw
	SPIKESB, //test1
	SPIKESB, //test2
	SPIKESB, //test3
	SPIKESB, //test4
	SAWBLADESA, //danger
};

const unsigned char block_set[] = {
	BLOCKSA, //stereo madness
	BLOCKSA, //back on track
	BLOCKSA, //polargeist
	BLOCKSA, //dryout
	BLOCKSA, //base after base
	BLOCKSA, //cant let go
	BLOCKSA, //jumper
	BLOCKSA, //time machine
	BLOCKSA, //cycles
	BLOCKSC, //xstep
	BLOCKSD, //clutterfunk
	BLOCKSB, //theory of everything
	BLOCKSB, //electroman
	BLOCKSC, //nightmare
	BLOCKSB, //decode
	BLOCKSB, //lucky draw
	BLOCKSA, //test1
	BLOCKSB, //test2
	BLOCKSB, //test3
	BLOCKSA, //test4
	SAWBLADESA, //danger
};

const unsigned char saw_set[] = {
	SAWBLADESA, //stereo madness
	SAWBLADESA, //back on track
	SAWBLADESA, //polargeist
	SAWBLADESA, //dryout
	SAWBLADESA, //base after base
	SAWBLADESA, //cant let go
	SAWBLADESA, //jumper
	SAWBLADESA, //time machine
	SAWBLADESA, //cycles
	SAWBLADESA, //xstep
	SAWBLADESA, //clutterfunk
	SAWBLADESA, //theory of everything
	SAWBLADESA, //electroman
	SAWBLADESA, //nightmare
	SAWBLADESA, //decode
	LETTERBANK, //lucky draw
	SAWBLADESA, //test1
	SAWBLADESA, //test2
	SAWBLADESA, //test3
	SAWBLADESA, //test4
	SAWBLADESA, //danger
};


const unsigned char difficulty_list[] = {
    EASY,
    EASY,
    NORMAL,
    NORMAL,
    HARD,
    HARD,
    HARDER,
    HARDER,
    HARDER,
    INSANE,
    INSANE,
    INSANE,
    INSANE,
    DEMON, //decode
    DEMON, //nightmare
    DEMON, //lucky draw
    DEMON,
    DEMON,
    DEMON,
    DEMON,
    DANGER,
};

const unsigned char stars_list[] = {
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	10,
	10,
	10,
	10,
	0,
	0,
	0,
	0,
	69,
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
	0, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x20, 0x22, 0x24, 0x26, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4A, 0x4C, 0x4E, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C
};


extern const unsigned char level_list_lo[];
extern const unsigned char level_list_hi[];
extern const unsigned char level_list_bank[];
extern const unsigned char sprite_list_lo[];
extern const unsigned char sprite_list_hi[];
extern const unsigned char sprite_list_bank[];