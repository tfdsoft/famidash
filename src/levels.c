#include "levels.h"


banked(2) const u8 lvl_test_tiles[] = {
    #embed "./levels/fd2_test_level.lvl"
};
banked(2) const u8 lvl_test_sprites[] = {
    0,
};

banked(level_bank_0) const struct Level lvl_test_header = {
    /* NAME (up to 23 characters) */
    .name = "lmao",

    .color = {
        .bg = 0x20,//background
        .g = 0x20,//ground
    },

    .height = 15, // level height

    .tile_data = (u8*)lvl_test_tiles,
    .tile_bank = 2,
    
    .sprite_data = (u8*)lvl_test_sprites,
    .sprite_bank = 2
};





