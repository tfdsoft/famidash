#include "levels.h"


banked(level_bank_0) const u8 lvl_test_tiles[] = {
    0,27,1,27,
};
banked(level_bank_0) const u8 lvl_test_sprites[] = {
    0,
};



banked(level_bank_0) const struct Level lvl_test_level = {
    /* NAME */
    "lmao",

    /* COLORS */ {
        0x20,//background
        0x20,//ground
    },

    (u8*)lvl_test_tiles, level_bank_0,
    (u8*)lvl_test_sprites, level_bank_0
};





