

void vram_copy(unsigned char* from, unsigned short count){
    for(unsigned short i=0; i<count; i++){
        PPU.vram.data = from[i];
    }
    
}