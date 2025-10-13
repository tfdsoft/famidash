#include "assets.h"

#include "include.h"

__attribute__((leaf)) __asm__(
    ".section .init.100,\"ax\",@progbits \n"
    ".globl clearRAM \n"
    "clearRAM: \n"
        "lda #0 \n"
        "tax \n"
    "1: \n"
        "pha \n"
        "sta  $00,x \n"
        "sta $200,x \n"
        "sta $300,x \n"
        "sta $400,x \n"
        "sta $500,x \n"
        "sta $600,x \n"
        "sta $700,x \n"
        "inx \n"
        "bne 1b \n"
    // end of clearRAM

    ".section .init.300,\"ax\",@progbits \n"
        "lda #$01 \n"
        "jsr set_prg_a000 \n"

        "lda #$01 \n"
        "tax \n"
        "dex \n"
        "ldy #$a0 \n"
        "jsr famistudio_init \n"
);

int main(void){
    PPU.control = PPU_CTRL_VAR = 0b10100000;
    //PPU.mask = PPU_MASK_VAR = 0b00011000;
    ppu_off(); // turn off everything

    
    // clear oam buffer
    memfill((unsigned char*)0x200,0,0x100);

    pal_col(0,0x0f);
    pal_bright(0);
    

    set_chr_bank(0,0);
    set_chr_bank(1,2);
    set_chr_bank(2,4);
    set_chr_bank(3,5);
    set_chr_bank(4,6);
    set_chr_bank(5,7);

    // clear chr
    vram_adr(0x0000);
    vram_fill(0,0x2000);

    // write chr
    //set_prg_8000(0);
    //vram_adr(0x0000);
    //vram_copy(chr_tiles_global, 0x400);
    //vram_copy(chr_tiles_grid, 0x100);
    //vram_copy(chr_tiles_cross, 0x100);
    //vram_copy(chr_tiles_brick, 0x100);
    //vram_copy(chr_tiles_black, 0x100);
    
    // write nametable
    //vram_adr(0x2000);
    //vram_unrle(test_header);

    // clear palette
    //pal_bg(test_palette);
    
    // clear apu
    //memfill((unsigned char*)0x4000,0,0x10);
    
    

    //set_prg_8000(61);// actually c000
    //PPU.control = PPU_CTRL_VAR = 0b10100000;
    //ppu_on_all();
    

    //pal_fade_to(0,4);

    //APU.status = 0b11111; // turn on all apu channels
    //APU.triangle.counter = 0xFF; // enable the triangle, no timer
    
    while(1){
        ppu_wait_nmi();
        scroll(0,0);
        switch (gamestate) {
            case 0: state_startup(); break;
        }
    }
}