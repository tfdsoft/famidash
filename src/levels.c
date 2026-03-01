#include "levels.h"


banked(2) const u8 lvl_test_tiles[] = {
    #embed "./levels/fd2_test_level.lvl"
};
banked(2) const u8 lvl_test_sprites[] = {
    0,
};

banked(level_bank_0) const struct Level lvl_test_header = {
    /* NAME (up to 23 characters) */
    "lmao",

    /* COLORS */ {
        0x20,//background
        0x20,//ground
    },

    15, // level height

    (u8*)lvl_test_tiles, 2,
    (u8*)lvl_test_sprites, 2
};





