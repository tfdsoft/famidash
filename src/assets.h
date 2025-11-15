#include <stdint.h>

#define IDENT(x) x
#define XSTR(x) #x
#define STR(x) XSTR(x)

#define putinbank(bank) __attribute__((section(".prg_rom_"STR(bank)),used))

#define file(symbol, bank) __attribute__((section((".prg_rom_"STR(bank))),retain)) const uint8_t symbol[]






// LEVELS
// level data grows upward from bank 1.

// MUSIC
// music data grows downward from bank 51.

// GRAPHICS
#define chr_bank_0 52       // menu graphics
#define chr_bank_1 53       // level graphics
#define chr_bank_2 54       // backgrounds
#define chr_bank_3 55

// MORE CODE
#define sound_test_bank 58  // gamestates that don't need to switch
#define extra_code_bank 59  // gamestates that don't need to switch
#define extra_code_bank_1 60// banks frequently can go in here

// SOUND FX
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

extern const uint8_t chr_background_0[];
//extern const uint8_t chr_background_1[];
extern const uint8_t chr_background_2[];

extern const uint8_t chr_ground_0[];
extern const uint8_t chr_ground_1[];
extern const uint8_t chr_ground_2[];
extern const uint8_t chr_ground_3[];



extern const uint8_t * const chr_bg[];
extern const uint8_t * const chr_g[];