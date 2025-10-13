

void vram_copy(unsigned char* from, unsigned short count){
    for(unsigned short i=0; i<count; i++){
        PPU.vram.data = from[i];
    }
    
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