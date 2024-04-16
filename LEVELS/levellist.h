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

#define EASY 0
#define NORMAL 1
#define HARD 2
#define HARDER 3
#define INSANE 4
#define DEMON 5


const unsigned char * const level_list[] = {
    stereomadness_,
    backontrack_,
    polargeist_,
    dryout_,
    baseafterbase_,
    cantletgo_,
    jumper_,
    timemachine_,
    cycles_,
    xstep_,
    test_,
    test2_,
    };

const unsigned char * const sprite_list[] = {
    stereomadness_SP,
    backontrack_SP,
    polargeist_SP,
    dryout_SP,
    baseafterbase_SP,
    cantletgo_SP,
    jumper_SP,
    timemachine_SP,
    cycles_SP,
    xstep_SP,
    test_SP,
    test2_SP,
};

const unsigned char bank_list[] = {
    1,
    8,
    2,
    7,
    5,
    3,
    4,
    9,
    6,
    0x0A,
    0x0C,
    0x0D,
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
    EASY,
    EASY,
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
	0,
	0,
};

// below here is just extra dev stuff. don't uncomment. //

// const unsigned char * const level_list[] = {test_};
// const unsigned char * const level_spr[] = {stereomadness_SP};