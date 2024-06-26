uint8_t* PPU_ADDR = (uint8_t*)0x2006;
uint8_t* PPU_DATA = (uint8_t*)0x2007;

void verybadchrload(uint8_t* data, uint16_t bytes){
    


    // womp womp, here we go iguess
    ppu_off();

    // start at the beginning
    *PPU_ADDR = 0x00;
    *PPU_ADDR = 0x00;
    

    
}