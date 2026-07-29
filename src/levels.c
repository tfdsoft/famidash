#include "levels.h"


banked(level_data_bank_0) const u8 lvl_test_tiles[] = {
    #embed "./levels/fd2_test_level.lvl"
};
banked(level_data_bank_0) const u8 lvl_test_sprites[] = {
    0,
};

banked(level_header_bank) const struct Level lvl_test_header = {
    /* NAME (up to 23 characters) */
    .name = "electrodynamix",

    .color = {
        .bg = 0x19,//background
        .g = 0x2a,//ground
    },

    .tileset = {
        .background = 0,
        .ground = 1,

        .blocks = {
            chr_tiles_brick,
            chr_tiles_x,
            chr_tiles_black,
            chr_tiles_onedotnine
        },
        .metatiles = {
            mt_normal_blockset,
            mt_normal_blockset,
            mt_normal_blockset,
            mt_normal_blockset,
        }
    },

    .song = song_stay_inside_me,

    .height = 32, // level height

    .tile_data = (u8*)lvl_test_tiles,
    .tile_bank = level_data_bank_0,
    
    .sprite_data = (u8*)lvl_test_sprites,
    .sprite_bank = level_data_bank_0
};





