#include "assets.h"

#include "include.h"

__attribute__((leaf)) __asm__(
    ".section .init.100,\"ax\",@progbits \n"
    ".globl clearRAM \n"
    "clearRAM: \n"
        "lda #0 \n"
        "tax \n"
    "1: \n"
        "sta  $00,x \n"
        "sta $100,x \n"
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
        "lda #$37 \n"
        "jsr set_prg_a000 \n"

        "lda #$01 \n"
        "tax \n"
        "dex \n"
        "ldy #$a0 \n"
        "jsr famistudio_init \n"

        //"ldx #$00 \n"
        //"tax \n"
        //"dex \n"
        //"ldy #$a0 \n"
        //"jsr famistudio_sfx_init \n"
);

int main(void){
    PPU.control = PPU_CTRL_VAR = 0b10100000;
    PPU.mask = PPU_MASK_VAR = 0b00000110;
    ppu_off(); // turn off everything
    

    music_play(0);
    famistudio_music_stop();

    // clear oam buffer
    //memfill((unsigned char*)0x200,0,0x100);
    oam_clear();

    // clear palette
    //pal_bg((const char *)0x120);
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

    ppu_on_spr();

    //APU.status = 0b11111; // turn on all apu channels
    //APU.triangle.counter = 0xFF; // enable the triangle, no timer
    
    //music_bank = music_bank_0;

    

    while(1){
        pal_bright(0);
        ppu_off();
        switch(gamestate){
            default: 
                banked_call(extra_code_bank, state_startup); 
                //state_startup();
                break;
            case 1:
                banked_call(extra_code_bank, state_credits);
                //state_menu();
                break;
        }
    }
    //APU.sprite.dma;
}