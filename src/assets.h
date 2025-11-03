#include <stdint.h>

#define putinbank(bank) __attribute__((section(bank),retain))

#define IDENT(x) x
#define XSTR(x) #x
#define STR(x) XSTR(x)

#define file(symbol, bank) __attribute__((section((".prg_rom_"STR(bank))),retain)) const uint8_t symbol[]






// LEVELS
// banks 0-31 are reserved for level data.

// turns out, the music exporter grows downward from
// bank 51. this means everything afterward is fair-game.

#define chr_bank_0 52       // menu graphics
#define chr_bank_1 53       // level graphics
#define chr_bank_2 54       // 
#define chr_bank_3 55

#define extra_code_bank 60  // gamestates that don't need to switch
                            // banks frequently can go in here

#define sfx_bank 61         // sound effects.

// banks 62 and 63 are fixed. not much i can do about that

extern const uint8_t chr_font[];
extern const uint8_t chr_menu_global[];
extern const uint8_t chr_menu_buttons[];
extern const uint8_t chr_menu_difficulties[];
extern const uint8_t chr_menu_tfdlogo[];
extern const uint8_t chr_menu_famidash[];
extern const uint8_t chr_menu_robtop[];

extern const uint8_t chr_tiles_global[];
extern const uint8_t chr_tiles_grid[];
extern const uint8_t chr_tiles_cross[];
extern const uint8_t chr_tiles_brick[];
extern const uint8_t chr_tiles_black[];



extern const uint8_t chr_ground_0[];
extern const uint8_t chr_ground_1[];
extern const uint8_t chr_ground_2[];
extern const uint8_t chr_ground_3[];

