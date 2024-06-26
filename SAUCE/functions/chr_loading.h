uint8_t* PPU_ADDR = (uint8_t*)0x2006;
uint8_t* PPU_DATA = (uint8_t*)0x2007;

void verybadchrload(uint8_t* data, uint16_t bytes){
    
    // womp womp, here we go iguess

    // start at the beginning
    *PPU_ADDR = high_byte(data);
    *PPU_ADDR = low_byte(data);

    for(tmp5 = 0; tmp5 < bytes; tmp5++){
        tmp1 = data[tmp5];
        *PPU_DATA = tmp1;
    }
}