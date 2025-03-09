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
	DECO1, //bot
	DECO1,  //polar
	DECO1,  //dry
	DECO1, //base
	DECO1,  //cant
	DECO1,  //jumper
	DECO1,  //time
	DECO1,  //cycles
	DECOCLOUD,  //xstep
	DECOCLOUD, //clutterfunk
	DECOCLOUD, //TOE
	DECOCLOUD, //electroman
	DECO1, //clubstep
	DECO1, //electrodynamix
	DECO1, //hexagon force
	DECO1, //blast processing
	DECO1, //TOE2
	DECO1, //geometrical dominator
	EXTRASPRITES1, //deadlocked
	EXTRASPRITES1, //fingerdash
	EXTRASPRITES1, //dash
	DECO1, //RETRAY
//	DECO1, //SONAR
	EXTRASPRITES1, //the challenge
//	DECO1, //level easy
	DECO1, //dreamer
//	DECO1, //lookatthislevel
	DECO1, //groundtospace
	DECOCLOUD, //kappaclysm
	DECO1, //sunshine
	DECO1, //revolution
	DECO1, //lost in the woods
	DECO1, //bloodbath but no
	EXTRASPRITES1, //rainbow tylenol
	DECO1, //a pretty easy level
	DECO1, //LIGHTNING ROAD
	DECOCLOUD, //NIGHTMARE
	DECO1, //DEMON PARK
	DECO1, //death moon
	DECOCLOUD, //DECODE
	EXTRASPRITES1, //dear nostalgists
//	DECO1, //super cycles
	DECO1, //problematic
	DECO1, //fire temple
	DECO1, //forest temple
//	EXTRASPRITES1, //EON
//	DECO1, //pg clubstep
//	DECO1, //stalemate
//	DECOCLOUD, //bloodbath
//	DECO1, //cataclysm
	DECOCLOUD, //lucky draw
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
	SPIKESA, //clubstep
	SPIKESA, //electrodynamix
	SPIKESB, //hexagon force
	SPIKESB, //blast processing
	SPIKESA, //TOE2
	SPIKESC, //geometrical dominator
	SPIKESA, //deadlocked
	SPIKESC, //fingerdash
	SPIKESA, //dash
	SPIKESA, //RETRAY
//	SPIKESA, //SONAR
	SPIKESA, //the challenge
//	SPIKESA, //level easy
	SPIKESA, //dreamer
//	SPIKESA, //lookatthislevel
	SPIKESA, //groundtospace
	SPIKESC, //kappaclysm
	SPIKESA, //sunshine
	SPIKESA, //revolution
	SPIKESA, //lost in the woods
	SPIKESA, //bloodbath but no
	SPIKESA, //rainbow tylenol
	SPIKESC, //a pretty easy level
	SPIKESC, //lightning road
	SPIKESB, //nightmare
	SPIKESC, //demon park
	SPIKESB, //death moon
	SPIKESB, //decode
	SPIKESC, //dear nostalgists
//	SPIKESA, //super cycles
	SPIKESB, //problematic
	SPIKESB, //fire temple
	SPIKESB, //forest temple
//	SPIKESB, //eon
//	SPIKESA, //pg clubstep
//	SPIKESA, //STALEMATE
//	SPIKESC, //bloodbath
//	SPIKESC, //cataclysm
	SPIKESB, //lucky draw
	SPIKESA, //test4
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
	BLOCKSB, //clubstep
	BLOCKSB, //electrodynamix
	BLOCKSB, //hexagon force
	BLOCKSB, //blast processing
	BLOCKSB, //TOE2
	BLOCKSB, //geometrical dominator
	BLOCKSB, //deadlocked
	BLOCKSB, //fingerdash
	BLOCKSB, //dash
	BLOCKSB, //RETRAY
//	BLOCKSB, //SONAR
	BLOCKSB, //the challenge
//	BLOCKSA, //level easy
	BLOCKSB, //dreamer
//	BLOCKSB, //lookatthislevel
	BLOCKSB, //groundtospace
	BLOCKSB, //kappaclysm
	BLOCKSB, //sunshine
	BLOCKSB, //revolution
	BLOCKSB, //lost in the woods
	BLOCKSB, //bloodbath but no
	BLOCKSA, //rainbow tylenol
	BLOCKSC, //a pretty easy level
	BLOCKSA, //LIGHTNING ROAD
	BLOCKSC, //nightmare
	BLOCKSA, //demon park
	BLOCKSB, //death moon
	BLOCKSB, //decode
	BLOCKSA, //dear nostalgists
//	BLOCKSB, //super cycles
	BLOCKSB, //problematic
	BLOCKSB, //fire temple
	BLOCKSB, //forest temple
//	BLOCKSA, //EON
//	BLOCKSB, //pg clubstep
//	BLOCKSB, //stalemate
//	BLOCKSB, //bloodbath
//	BLOCKSB, //cataclysm
	BLOCKSB, //lucky draw
	BLOCKSB, //test4
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
	SAWBLADESA, //clubstep
	SAWBLADESA, //electrodynamix
	SAWBLADESA, //hexagon force
	SAWBLADESA, //blast processing
	SAWBLADESA, //TOE2
	SAWBLADESA, //geometrical dominator
	SAWBLADESA, //deadlocked
	SAWBLADESA, //fingerdash
	SAWBLADESA, //dash
	SAWBLADESA, //retray
//	SAWBLADESA, //SONAR
	SAWBLADESA, //the challenge
//	SAWBLADESA, //level easy
	SAWBLADESA, //dreamer
//	SAWBLADESA, //lookatthislevel
	SAWBLADESA, //groundtospace
	SAWBLADESA, //kappaclysm
	SAWBLADESA, //sunshine
	SAWBLADESA, //revolution
	SAWBLADESA, //lost in the woods
	SAWBLADESA, //bloodbath but no
	SAWBLADESA, //rainbow tylenol
	SAWBLADESA, //a pretty easy level
	SAWBLADESA, //LIGHTNING ROAD
	SAWBLADESA, //nightmare
	SAWBLADESA, //demon park
	SAWBLADESA, //death moon
	SAWBLADESA, //decode
	SAWBLADESA, //dear nostalgists
//	SAWBLADESA, //super cycles
	SAWBLADESA, //problematic
	SAWBLADESA, //fire temple
	SAWBLADESA, //forest temple
//	SAWBLADESA, //EON
//	SAWBLADESA, //PG CLUBSTEP
//	SAWBLADESA, //stalemate
//	SAWBLADESA, //bloodbath
//	SAWBLADESA, //cataclysm
	LETTERBANK, //lucky draw
	SAWBLADESA, //test4
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
    DEMON,  //CLUBSTEP
    INSANE,  //electrodynamix
    INSANE,  //hexagon force
    HARDER, //blast processing
    DEMON,  //TOE2
    HARDER, //geometrical dominiator
    DEMON,  //deadlocked
    INSANE,  //fingerdash
    INSANE,  //dash
    EASY, //RETRAY
//    EASY, //SONAR
    NORMAL, //the challenge
//    NORMAL, //level easy
    HARD, //dreamer
//    HARD, //lookatthislevel
    HARD, //groundtospace
    HARDER, //kappaclysm
    HARDER, //sunshine
    HARDER, //revolution
    INSANE, //lost in the woods
    INSANE, //bloodbath but no
    INSANE, //rainbow tylenol
    INSANE, //a pretty easy level
    DEMON, //lightning road
    DEMON, //nightmare
    DEMON, //demon park
    DEMON, //death moon
    DEMON, //decode
    DEMON, //dear nostalgists
//    DEMON, //super cycles
    DEMON, //problematic
    DEMON, //fire temple
    DEMON, //forest temple
//    DEMON, //eon
//    DEMON, //pg clubstep
//    DEMON, //stalemate
//    DEMON, //bloodbath
//    DEMON, //cataclysm
    DEMON, //lucky draw
    DEMON,
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
	14,  //clubstep
	12,  //electrodynamix
	12,  //hexagon force
	10,  //blast processing
	14,  //TOE2
	10,  //geometrical dominiator
	15,  //DEADLOCKED
	12,  //fingerdash
	12,  //dash
	2,   //retray
//	2,   //SONAR
	3,   //the challenge
//	3,   //level easy
	4,   //dreamer
//	4,   //lookatthislevel
	5,   //groundtospace
	6,  //kappaclysm
	7,  //sunshine
	7,  //revolution
	8,  //lost in the woods
	8,  //rainbow tylenol
	8,  //bloodbath but no
	9,  //a pretty easy level
	10, //lightning road
	10, //nightmare
	10, //demon park
	10, //death moon
	10, //decode
	10, //dear nostlagists
//	10, //super cycles
	10, //problematic
	10, //fire temple
	10, //forest temple
//	10, //eon
//	10, //pg clubstep
//	10, //stalemate
//	10, //bloodbath
//	10, //cataclysm
	10, // lucky draw
	0,
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