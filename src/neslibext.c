



void vram_copy(const unsigned char* from, unsigned short count){
    //PPU_CTRL_VAR &= 0b01111111;
    //PPU.control = PPU_CTRL_VAR;
    for(unsigned short i=0; i<count; i++){
        PPU.vram.data = from[i];
    }
    //PPU_CTRL_VAR |= 0b10000000;
    //PPU.control = PPU_CTRL_VAR;
}


void pal_fade_to(unsigned char from, unsigned char to){

    if(from < to) {
        while (from < to){
            pal_bright(++from);
            ppu_wait_nmi();
            ppu_wait_nmi();
        }
    }else{
        while (from > to){
            pal_bright(--from);
            ppu_wait_nmi();
            ppu_wait_nmi();
        }
    }
}


