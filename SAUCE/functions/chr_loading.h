#define FIRST_CHR_BANK 32

extern const unsigned char CHR_MENU_GLOBAL[];

void verybadchrload(uint8_t* data, uint8_t bytes, uint8_t where){
    
    mmc3_tmp_prg_bank_1(FIRST_CHR_BANK); // THIS DOES NOT EXIST IN THE C SPACE FSR //
    // womp womp, here we go iguess

    // start at the beginning
    POKE(0x2006, where);
    POKE(0x2006, 0x00);

    tmp6 = (bytes << 8);
    for(tmp5 = 0; tmp5 < tmp6; tmp5++){
        tmp1 = data[tmp5];
        POKE(0x2007, data);
    }


    mmc3_pop_prg_bank_1();
}