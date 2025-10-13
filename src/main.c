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
        "lda #$00 \n"
        "tax \n"
        "ldy #$a0 \n"
        "jsr famistudio_init \n"
);

int main(void){
    PPU.control = PPU_CTRL_VAR = 0b10100000;
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
    ppu_wait_nmi();

    // write chr
    set_prg_8000(0);
    vram_adr(0x0000);
    vram_copy((void*)0xc000, 0x2000);
    
    // write nametable
    vram_adr(0x2000);
    vram_unrle(test_header);

    // clear palette
    pal_bg(test_palette);
    
    // clear apu
    //memfill((unsigned char*)0x4000,0,0x10);
    
    

    //set_prg_8000(61);// actually c000
    //PPU.control = PPU_CTRL_VAR = 0b10100000;
    ppu_on_all();
    

    pal_fade_to(0,4);

    //APU.status = 0b11111; // turn on all apu channels
    //APU.triangle.counter = 0xFF; // enable the triangle, no timer
    
    
    famistudio_music_play(0);
    while(1){
        unsigned char tmp;
        //unsigned short yscroll;
        ppu_wait_nmi();
        set_prg_a000(1);
        famistudio_update();
        

        scroll(0,0);

        //APU.triangle.period_low = low_byte(pitch);
        //APU.triangle.len_period_high = ((high_byte(pitch) & 0x07) + 0x08);
        //pitch += 16;

        for (unsigned char i=0;i<128;i++){
            PPU.mask = (0b00011000 + (tmp & 0b11100000));
            tmp += 0b00100000;
        }
        PPU.mask = (0b00011000);
    }
}