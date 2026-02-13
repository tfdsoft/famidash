// since mos-clang doesn't suck at being a compiler,
// i'm not going to re-use 1.x's physics table since
// it's optimized for cc65

const u16 phys_speed[] = {
    0x02C4, // 1x
    0x023B, //.5x
    0x0371, // 2x
    0x0429, // 3x
    0x051E, // 4x
};

const u16 phys_gravity[] = {
    0x009a, // cube
};

const u16 phys_jumpvel[] = {
    -0x6ac, // cube
};