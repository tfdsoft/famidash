// since mos-clang doesn't suck at being a compiler,
// i'm not going to re-use 1.x's physics table since
// it's optimized for cc65

putinbank(fixed_lo.physics)
const uint16_t phys_speed[] = {
    0x02C4, // 1x
    0x023B, //.5x
    0x0371, // 2x
    0x0429, // 3x
    0x051E, // 4x
};

putinbank(fixed_lo.physics)
const uint16_t phys_gravity[] = {
    0x009a, // cube
};

putinbank(fixed_lo.physics)
const uint16_t phys_jumpvel[] = {
    -0x6ac, // cube
};