/*==============================================
 *  ROM SETTINGS
 *  customize your ROM configuration.
**============================================*/

// Program ROM size (16 - 1024 kB) =============
#define SE_PROGRAM_ROM_SIZE     512

// Character RAM size (1 - 256 kB) =============
#define SE_CHARACTER_RAM_SIZE   128

// Work RAM size (1 - 8 kB) ====================
#define SE_WORK_RAM_SIZE        8












/*==============================================
 *  You shouldn't have to touch anything
 *  below this point.
**============================================*/

//#include <ines.h>

//MAPPER_PRG_ROM_KB(STR(SE_PROGRAM_ROM_SIZE));

// extra memory!
//MAPPER_PRG_NVRAM_KB(STR(SE_WORK_RAM_SIZE));
//MAPPER_USE_BATTERY;

// 32kb of chr-ram should be fine
//MAPPER_CHR_ROM_KB(0);
//MAPPER_CHR_RAM_KB(STR(SE_CHARACTER_RAM_SIZE));

// four screens of characters
//MAPPER_USE_4_SCREEN_NAMETABLE;

// multiregion
//INES_TIMING_MULTIREGION;

__asm__ (
    "__prg_rom_size = "STR(SE_PROGRAM_ROM_SIZE)" \n"
    ".global __prg_rom_size \n"
    "__chr_rom_size = 0 \n"
    ".global __chr_rom_size \n"
    "__chr_ram_size = "STR(SE_CHARACTER_RAM_SIZE)" \n"
    ".global __chr_ram_size \n"
    "__prg_nvram_size = "STR(SE_WORK_RAM_SIZE)" \n"
    ".global __prg_nvram_size \n"
    "__battery = 1 \n"
    ".global __battery \n"





    "__four_screen = 1 \n"
    ".global __four_screen \n"
    // Expansion Port Sound Module
    "__console_type = 3 \n"
    ".global __console_type \n"
    "__extended_console_type = 4 \n" 
    ".global __extended_console_type \n"
);


__attribute__((leaf)) __asm__(
    ".section .init.100,\"ax\",@progbits \n"
    ".globl clearRAM \n"
    "clearRAM: \n"
        "lda #0 \n"
        "tax \n"
    "1: \n"
        "sta  $00,x \n"
        "pha \n"
        "sta $200,x \n"
        "sta $300,x \n"
        "sta $400,x \n"
        "sta $500,x \n"
        "sta $600,x \n"
        "sta $700,x \n"
        "inx \n"
        "bne 1b \n"

    // end of clearRAM
    "lda #$c0\n"
    "sta $4017\n" // disable apu frame counter irq

);