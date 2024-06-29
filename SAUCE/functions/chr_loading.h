#define FIRST_CHR_BANK 32

extern void mmc3_tmp_prg_bank_1();
extern unsigned char CHR_MENU_GLOBAL[];
extern unsigned char CHR_MENU_LOGOBUTTONS[];
extern unsigned char CHR_MENU_DIFFICULTIES[];
extern unsigned char CHR_PUSAB_TRANSBG[];
extern unsigned char CHR_PUSAB_BLACKBG[];


// data: name of the array
// bytes: amount of bytes to write x256
// where: which 256 byte segment to write to
void verybadchrload(uint8_t* data, uint8_t bytes, uint8_t where){
    
    mmc3_tmp_prg_bank_1(FIRST_CHR_BANK);
    // womp womp, here we go iguess

    // start at the beginning
    POKE(0x2006, where);
    POKE(0x2006, 0x00);

    tmp6 = (bytes << 8);
    for(tmp5 = 0; tmp5 < tmp6; tmp5++){
        tmp1 = data[tmp5];
        POKE(0x2007, tmp1);
    }


    mmc3_pop_prg_bank_1();
}