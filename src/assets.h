#include <stdint.h>

#define putinbank(bank) __attribute__((section(bank),retain))

#define IDENT(x) x
#define XSTR(x) #x
#define STR(x) XSTR(x)

#define file(symbol, bank) __attribute__((section((".prg_rom_"STR(bank))),retain)) const uint8_t symbol[]

// LEVELS
// banks 0-31 are reserved for level data.

// GRAPHICS
#define chr_bank_0 32       // menu graphics
#define chr_bank_1 33       // level graphics
#define chr_bank_2 34       // 
#define chr_bank_3 35

// MUSIC DATA
#define sfx_bank 36         // sound fx!
#define music_bank_0 37     // the freakin' music.
#define music_bank_1 38     // |    go to src/famistudio/music_assets.s
#define music_bank_2 39     // V    to set these banks manually.

// SAMPLES
#define dpcm_bank_0 40      // the samplOH MY GOD WHY ARE THERE SO MANY
#define dpcm_bank_1 41      // |    yeah i guess kando wasn't joking
#define dpcm_bank_2 42      // |    when he said "no more space"
#define dpcm_bank_3 43      // |
#define dpcm_bank_4 44      // |
#define dpcm_bank_5 45      // |
#define dpcm_bank_6 46      // |
#define dpcm_bank_7 47      // |
#define dpcm_bank_8 48      // |
#define dpcm_bank_9 49      // |
#define dpcm_bank_10 50     // |
#define dpcm_bank_11 51     // |
#define dpcm_bank_12 52     // |
#define dpcm_bank_13 53     // |    on top of all this, there's still
#define dpcm_bank_14 54     // |    a whole sample bank being left
#define dpcm_bank_15 55     // V    out: bank16.

// banks 56-57 are reserved, on the off-chance we need more extra code

#define extra_code_bank 59  // gamestates that don't need to switch
                            // banks frequently can go in here

#define nametable_bank_0 60 // neslib-rle-packed nametables
#define nametable_bank_1 61 // V

// banks 62 and 63 are fixed. not much i can do about that

extern const uint8_t chr_menu_global[];
extern const uint8_t chr_font[];
extern const uint8_t chr_logo[];
extern const uint8_t chr_famidash[];

extern const uint8_t chr_tiles_global[];
extern const uint8_t chr_tiles_grid[];
extern const uint8_t chr_tiles_cross[];
extern const uint8_t chr_tiles_brick[];
extern const uint8_t chr_tiles_black[];

