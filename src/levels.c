#include "levels.h"


banked(level_data_bank_0) const u8 lvl_test_tiles[] = {
    #embed "./levels/fd2_test_level.lvl"
};
banked(level_data_bank_0) const u8 lvl_test_sprites[] = {
    0,
};

banked(level_header_bank) const struct Level lvl_test_header = {
    /* NAME (up to 23 characters) */
    .name = "lmao",

    .color = {
        .bg = 0x20,//background
        .g = 0x20,//ground
    },

    .tileset = {
        .blocks = {
            chr_tiles_grid,
            chr_tiles_cross,
            chr_tiles_black,
            chr_tiles_funnylookingsquares,
        },
        .metatiles = {
            mt_normal_blockset,
            mt_normal_blockset,
            mt_normal_blockset,
            mt_normal_blockset,
        }
    },

    .height = 15, // level height

    .tile_data = (u8*)lvl_test_tiles,
    .tile_bank = level_data_bank_0,
    
    .sprite_data = (u8*)lvl_test_sprites,
    .sprite_bank = level_data_bank_0
};





