#include "assets.h"

#include "include.h"



int main(void){
    set_prg_mode(PRG_MODE_1); // set 0xc000 - 0xdfff as swappable
    

    PPU.control = PPU_CTRL_VAR = 0b10100000;
    PPU.mask = 0; 
    ppu_off(); // turn off everything


    
    set_chr_bank(0,0);
    set_chr_bank(1,2);
    set_chr_bank(2,4);
    set_chr_bank(3,5);
    set_chr_bank(4,6);
    set_chr_bank(5,7);
    // write chr
    set_prg_8000(0);
    vram_adr(0x0000);
    vram_copy((void*)0xc000, 0x2000);
    

    // clear nametables
    vram_fill(0, 0x1000);

    vram_adr(0x2000);
    vram_unrle(test_header);

    // clear palette
    pal_col(0,0x0f);
    pal_col(1,0x00);
    pal_col(2,0x10);
    pal_col(3,0x30);
    
    //vram_fill(0, 0x1c);


    APU.status = 0b11111; // turn on all apu channels
    APU.triangle.counter = 0xFF; // enable the triangle, no timer


    set_prg_8000(61);

    pal_bright(4);
    ppu_on_all();
    //PPU.control = 0b10100000;

    
    while(1){
        unsigned char tmp;
        unsigned short yscroll;
        ppu_wait_nmi();
        

        scroll(0,0);

        APU.triangle.period_low = low_byte(pitch);
        APU.triangle.len_period_high = ((high_byte(pitch) & 0x07) + 0x08);
        pitch += 16;

        for (unsigned char i=0;i<128;i++){
            PPU.mask = (0b00011000 + (tmp & 0b11100000));
            tmp += 0b00100000;
        }
        PPU.mask = (0b00011000);
    }
}