/*==============================================
 *  ENGINE CONFIGURATION
 *  customize your ROM configuration.
**============================================*/

// Sound Test Bank =============================
#define sound_test_bank 61


















/*==============================================
 *  You shouldn't have to touch anything
 *  below this point.
**============================================*/

typedef unsigned char u8;
typedef unsigned short u16;
#define u24 __BitInt(24)
typedef unsigned long u32;

#define XSTR(x) #x
#define STR(x) XSTR(x)

#define NULL ((void*)0)

#define nametable_address_A(x,y) (0x2000 + ((y<<5) + x))
#define nametable_address_B(x,y) (0x2400 + ((y<<5) + x))
#define nametable_address_C(x,y) (0x2800 + ((y<<5) + x))
#define nametable_address_D(x,y) (0x2c00 + ((y<<5) + x))

 #define lo(a) *((unsigned char *)&a)
 #define hi(a) *(((unsigned char *)&a) + 1)

#define banked(bank) __attribute__((section(".prg_rom_"STR(bank)),used))
#define sram __attribute__((section(".prg_ram"),retain))
#define file(symbol, bank) __attribute__((section((".prg_rom_"STR(bank))),retain)) const u8 symbol[]


__attribute__((section(".aligned"),retain)) struct sprite_buffer {
    unsigned char y;
    unsigned char tile;
    unsigned char attr;
    unsigned char x;
} sprite_buffer[64];

extern u8 se_frame_count;
extern u8 se_ppu_ctrl_var, se_ppu_mask_var;
extern u8 se_palette_update;
extern u8 __prg_8000, __prg_a000;
extern void* se_post_nmi_ptr;
extern void* se_irq_ptr;
extern u8 se_sample_in_progress;
extern u8 se_irq_table[32], se_irq_table_position;
extern const u8 se_identity_table[256];

struct pad {
    union {
        unsigned char hold;
        struct {
            unsigned char right : 1;
            unsigned char left : 1;
            unsigned char down : 1;
            unsigned char up : 1;
            #if __VS_SYSTEM
            unsigned char select : 1;
            unsigned char start : 1;
            #else
            unsigned char start : 1;
            unsigned char select : 1;
            #endif
            unsigned char b : 1;
            unsigned char a : 1;
        };
    };
    union {
        unsigned char press;
        struct {
            unsigned char press_right : 1;
            unsigned char press_left : 1;
            unsigned char press_down : 1;
            unsigned char press_up : 1;
            #if __VS_SYSTEM
            unsigned char press_select : 1;
            unsigned char press_start : 1;
            #else
            unsigned char press_start : 1;
            unsigned char press_select : 1;
            #endif
            unsigned char press_b : 1;
            unsigned char press_a : 1;
        };
    };
    union {
        unsigned char release;
        struct {
            unsigned char release_right : 1;
            unsigned char release_left : 1;
            unsigned char release_down : 1;
            unsigned char release_up : 1;
            #if __VS_SYSTEM
            unsigned char release_select : 1;
            unsigned char release_start : 1;
            #else
            unsigned char release_start : 1;
            unsigned char release_select : 1;
            #endif
            unsigned char release_b : 1;
            unsigned char release_a : 1;
        };
    };
};
extern struct pad joypad1;
extern struct pad joypad2;

__attribute__((leaf)) void se_init(u8 A12_invert);
__attribute__((leaf)) void nofunction();

__attribute__((leaf)) void disable_nmi();
__attribute__((leaf)) void enable_nmi();

__attribute__((leaf)) void banked_call_a000(u8 bank, void(*method)(void));
__attribute__((leaf)) void set_prg_c000(u8 bank);
__attribute__((leaf)) void set_prg_a000(u8 bank);
__attribute__((leaf)) void set_chr_bank(u8 window, u8 bank);
#define jsrfar_noargs(bank, func) __asm__ volatile("jsr jsrfar \n .word "STR(func)"\n .byte "STR(bank)" \n")

#define se_vram_address(address) __asm__ volatile("ldx #>"STR(address)"\n stx $2006 \n ldx #<"STR(address)"\n stx $2006")
__attribute__((leaf)) void se_vram_unrle(const void* data, u8 usezero);
__attribute__((leaf)) void se_vram_donut_decompress(const u8 * data, u8 bank);



__attribute__((leaf)) void se_wait_vsync();
__attribute__((leaf)) void se_wait_frames(u8 frames);
__attribute__((leaf)) void se_turn_off_rendering();
__attribute__((leaf)) void se_turn_on_rendering();

__attribute__((leaf)) void se_set_palette_background(const u8* data);
__attribute__((leaf)) void se_set_palette_sprites(const u8* data);
__attribute__((leaf)) void se_set_palette_all(const u8* data);
__attribute__((leaf)) void se_clear_palette();
__attribute__((leaf)) void se_set_palette_color(u8 index, u8 color);
__attribute__((leaf)) void se_set_palette_brightness_background(u8 bright);
__attribute__((leaf)) void se_set_palette_brightness_sprites(u8 bright);
__attribute__((leaf)) void se_set_palette_brightness_all(u8 bright);
__attribute__((leaf)) void se_fade_palette_to(u8 from, u8 to);

__attribute__((leaf)) void se_clear_sprites();
__attribute__((leaf)) void se_draw_sprite(u8 x, u8 y, u8 tile, u8 attr);
__attribute__((leaf)) void se_draw_metasprite(u8 x, u8 y, const u8* const data);

__attribute__((leaf)) void se_one_vram_buffer(
	const char data, const u16 ppu_addr
);
__attribute__((leaf)) void se_one_vram_buffer_repeat_horizontal(
	const char data, const u8 len, const u16 ppu_addr
);
__attribute__((leaf)) void se_string_vram_buffer(
	const char *data, const u16 ppu_addr
);




__attribute__((leaf)) void se_memory_fill(void* ptr, u8 data, u16 length);
__attribute__((leaf)) void se_memory_copy(void* to, void* from, u16 length);


#define se_write_function_to_irq_table(ptr, index) __asm__ volatile( \
    "lda #<"STR(ptr)" \n" \
    "sta se_irq_table + "STR(index)" \n" \
    "lda #>"STR(ptr)" \n" \
    "sta se_irq_table + "STR(index)"+1 \n" \
)

#define se_play_sample(ptr, bank, rate) __asm__ volatile( \
    "lda #<"STR(ptr)" \n" \
    "ldx #>"STR(ptr)" \n" \
    "sta $d1 \n" \
    "stx $d2 \n" \
    "lda #"STR(bank)" \n" \
    "ldx #"STR(rate)" \n" \
    "jsr se_play_sample \n" \
)


// == the compiler/linker figures these out ==
#include "musicDefines.h"
#include "musicBankData.h"
#include "music_soundTestTables.h"
#include "sfx_soundTestTables.h"
// ===========================================
#include "music/EXPORTS/sfx.h"


#include "famistudio_wrappers.c"
__asm__ (
    ".section .prg_rom_fixed_lo.famistudio_dpcm_bank_callback \n"
    "famistudio_dpcm_bank_callback: \n"
    "pha \n"
    "lda "STR(se_sample_in_progress)" \n"
    "beq 1f \n"
    "pla \n"
    "rts \n"
    "1: \n"
    "pla \n"
    "clc \n"
    "adc #"STR(dpcm_bank_0)" \n"
    "jmp set_prg_8000 \n"
    ".globl famistudio_dpcm_bank_callback \n"
);