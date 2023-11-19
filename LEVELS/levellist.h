// LEVEL ORDERING =============================================
// 
// NOTE: DO *NOT* PUT LEVEL DATA HERE.
// Level order is defined here, and consists of 3 tables. The 
// first table specifies the level data pointers, the second -
// sprite data pointers, and the third one - interleaved ROM
// banks for both (in order of starting level data bank, 
// starting sprite data bank). Here is an example:
// ============================================================
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
//    0, 3, // Level data starts in bank 0,
//          // sprite data starts in bank 3
//    1, 3,
//    2, 4
// }
// ============================================================
// go wild


const unsigned char * const level_list[] = {
    stereomadness_,
    polargeist_
    };

const unsigned char * const sprite_list[] = {
    stereomadness_SP,
};

const unsigned char bank_list[] = {
    0,
    1
};


// below here is just extra dev stuff. don't uncomment. //

// const unsigned char * const level_list[] = {test_};
// const unsigned char * const level_spr[] = {stereomadness_SP};