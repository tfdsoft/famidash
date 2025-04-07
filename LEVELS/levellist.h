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
	DECO1, //sonar
	DECO1, //level easy
	DECOCLOUD, //ninox
	DECO1, //look at this level
	DECO1, //subzero
	DECO1, //pyrophoric
	EXTRASPRITES1, //subtle oddities
	DECO1, //high life
	DECO1, //super cycles
	DECO1, //clutterfunk 2
	EXTRASPRITES1, //speed racer
	DECO1, //pg clubstep
	EXTRASPRITES1, //hell
	EXTRASPRITES1, //eon
	DECO1, //stalemate
	DECOCLOUD, //bloodbath
	DECO1, //cataclysm
	DECO1, //aftermath
	DECO1, //aftercatabath
	DECO1, //slaughterhouse
	DECO1, //test4
};

const unsigned char spike_set[] = {
	SPIKESA, //stereo madness
	SPIKESA, //sonar
	SPIKESA, //level easy
	SPIKESB, //ninox
	SPIKESA, //look at this level
	SPIKESA, //subzero
	SPIKESA, //pyrophoric
	SPIKESA, //subtle oddities
	SPIKESA, //high life
	SPIKESA, //super cycles
	SPIKESC, //clutterfunk 2
	SPIKESA, //speed racer
	SPIKESA, //pg clubstep
	SPIKESA, //hell
	SPIKESB, //eon
	SPIKESA, //stalemate
	SPIKESC, //bloodbath
	SPIKESC, //cataclysm
	SPIKESC, //aftermath
	SPIKESC, //aftercatabath
	SPIKESA, //slaughterhouse
	SPIKESC, //test4
};

const unsigned char block_set[] = {
	BLOCKSA, //stereo madness
	BLOCKSB, //sonar
	BLOCKSA, //level easy
	BLOCKSC, //ninox
	BLOCKSB, //look at this level
	BLOCKSB, //subzero
	BLOCKSB, //pyrophoric
	BLOCKSB, //subtle oddities
	BLOCKSB, //high life
	BLOCKSB, //super cycles
	BLOCKSB, //clutterfunk 2
	BLOCKSB, //speed racer
	BLOCKSB, //pg clubstep
	BLOCKSA, //hell
	BLOCKSA, //eon
	BLOCKSB, //stalemate
	BLOCKSB, //bloodbath
	BLOCKSB, //cataclysm
	BLOCKSB, //aftermath
	BLOCKSB, //aftercatabath
	BLOCKSB, //slaughterhouse
	BLOCKSB, //test4
};

const unsigned char saw_set[] = {
	SAWBLADESA, //stereo madness
	SAWBLADESA, //sonar
	SAWBLADESA, //level easy
	SAWBLADESA, //ninox
	SAWBLADESA, //look at this level
	SAWBLADESA, //subzero
	SAWBLADESA, //pyrophoric
	SAWBLADESA, //subtle oddities
	SAWBLADESA, //high life
	SAWBLADESA, //super cycles
	SAWBLADESA, //clutterfunk 2
	SAWBLADESA, //speed racer
	SAWBLADESA, //PG CLUBSTEP
	SAWBLADESA, //hell
	SAWBLADESA, //eon
	SAWBLADESA, //stalemate
	SAWBLADESA, //bloodbath
	SAWBLADESA, //cataclysm
	SAWBLADESA, //aftermath
	SAWBLADESA, //aftercatabath
	SAWBLADESA, //slaughterhouse
	SAWBLADESA, //test4
};


const unsigned char difficulty_list[] = {
    EASY,
    EASY, //sonar
    NORMAL, //level easy
    NORMAL, //ninox
    HARD, //look at this level
    HARD, //subzero
    HARDER, //pyrophoric
    INSANE, //subtle oddities
    INSANE, //high life
    DEMON, //super cycles
    DEMON, //clutterfunk 2
    DEMON, //speed racer
    DEMON, //pg clubstep
    DEMON, //hell
    DEMON, //eon
    DEMON, //stalemate
    DEMON, //bloodbath
    DEMON, //cataclysm
    DEMON, //aftermath
    DEMON, //aftercatabath
    DEMON, //slaughterhouse
    EASY, //test4
};

const unsigned char stars_list[] = {
	1,
	2,   //sonar
	3,   //level easy
	3,   //ninox
	4,   //look at this level
	5, //subzero
	6, //pyrophoric
	8, //subtle oddities
	9, //high life
	10, //super cycles
	10, //clutterfunk 2
	10, //speed racer
	10, //pg clubstep
	10, //hell
	10, //eon
	10, //stalemate
	10, //bloodbath
	10, //cataclysm
	10, //aftermath
	10, //aftercatabath
	10, //slaughterhouse
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