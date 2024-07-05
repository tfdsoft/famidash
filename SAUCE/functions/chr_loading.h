#define FIRST_CHR_BANK 32
#define ICON_CHR_BANK 36

// the part where the chr shenanigans is declared as existing n whatnot
    extern void mmc3_tmp_prg_bank_1();
    extern unsigned char CHR_MENU_GLOBAL[];
    extern unsigned char CHR_MENU_LOGOBUTTONS[];
    extern unsigned char CHR_MENU_DIFFICULTIES[];
    extern unsigned char CHR_PUSAB_TRANSBG[];
    extern unsigned char CHR_PUSAB_BLACKBG[];

    extern unsigned char CHR_CUSTOMIZE_BORDERS[];
    extern unsigned char CHR_CUSTOMIZE_MISC[];

    extern unsigned char CHR_CUSTOMIZE_ICONS[];

    extern unsigned char CHR_INGAME_GLOBAL[];
    extern unsigned char CHR_INGAME_TILESET_CHECKERBOARD[];

// end

// data: name of the array
// bytes: amount of bytes to write x256
// where: which 256 byte segment to write to
void verybadchrload(uint8_t* data, uint8_t bytes, uint8_t where){
    
    mmc3_tmp_prg_bank_1(FIRST_CHR_BANK+chr_load_bank_offset);

    POKE(0x2006, where);
    POKE(0x2006, 0x00);
    // set where we're writing to, offset by where * 256 bytes

    tmp6 = (bytes << 8);
    for(tmp5 = 0; tmp5 < tmp6; tmp5++){
        tmp1 = data[tmp5];
        POKE(0x2007, tmp1);
    }


    mmc3_pop_prg_bank_1();
}