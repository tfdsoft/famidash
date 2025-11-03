// since mos-clang doesn't suck at being a compiler,
// i'm not going to re-use 1.x's physics table since
// it's optimized for cc65

__attribute__((section(".prg_rom_fixed_lo.1"),retain))
const uint16_t phys_speed[] = {
    0x02C4, // 1x
    0x023B, //.5x
};