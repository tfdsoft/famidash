#include "metatiles.h"

void load_metatiles(u8 start_slot, const struct Metatile* mts, u8 size){
    for(u8 i=0; i<size; i++){
        metatiles_TL[start_slot+i] = mts[i].topleft;
        metatiles_TR[start_slot+i] = mts[i].topright;
        metatiles_BL[start_slot+i] = mts[i].bottomleft;
        metatiles_BR[start_slot+i] = mts[i].bottomright;
    }
}

// METATILES 0-15 ARE RESERVED!!!!!!!!!!!!!!

// load these into slot 16
banked(level_bank_0) const struct Metatile mt_default_blocks[] = {
    {4, 6, 5, 7}, // block
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    {0x28, 0x2a, 0x29, 0x2b}, // add ground (top left)
    {0x2a, 0x2a, 0x2b, 0x2b}, // add ground (top center)
    {0x2a, 0x2c, 0x2b, 0x2d}, // add ground (top right)
    {},
    {0x0c, 0x00, 0x0d, 0x00}, // pulserod mid (up)
    {},
    {0x00, 0x0e, 0x00, 0x0f}, // pulserod mid (down)
    {},

    {0x10, 0x12, 0x11, 0x13}, // spike (up)
    {0x14, 0x16, 0x15, 0x17}, // spike (right)
    {0x18, 0x1a, 0x19, 0x1b}, // spike (down)
    {0x1c, 0x1e, 0x1d, 0x1f}, // spike (left)
    {0x00, 0x00, 0x30, 0x32}, // half spike (up)
    {0x36, 0x00, 0x37, 0x00}, // half spike (right)
    {0x31, 0x33, 0x00, 0x00}, // half spike (down)
    {0x00, 0x34, 0x00, 0x35}, // half spike (left)

    {0x00, 0x34, 0x30, 0x3b}, // half spike corner (ul)
    {0x36, 0x00, 0x39, 0x32}, // half spike corner (ur)
    {0x38, 0x33, 0x37, 0x00}, // half spike corner (dr)
    {0x33, 0x3a, 0x00, 0x35}, // half spike corner (dl)
    {},
    {},
    {},
    {},
};