/*==============================================
 *  ASSETS
 *  got any binary files or data that need to
 *  be included? Put them here.
 *==============================================
 *  USAGE:
 *  file(symbol, bank) = {
 *      #embed "<path/to/file>"
 *  }
 *  symbol: the keyword that gets created
 *          after adding the file to the project
 *  bank:   the bank where the file will reside
 *==============================================
 *  EXAMPLE
 *  to add a compressed graphics file to
 *  bank 52, you'd use it like this:
 * 
 *  file(CHR_menu_font_pusab, 52) = {
 *      #embed "./chr/dnt/Menu_Font_Pusab.bin"
 *  }
**============================================*/

// menu stuff
file(chr_menu_font_pusab, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Font_Pusab.bin"
};  
file(chr_menu_global, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Global.bin"
};
file(chr_menu_buttons, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Buttons.bin"
};
file(chr_menu_pause, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Pause.bin"
};
file(chr_menu_difficulties, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Difficulties.bin"
};
file(chr_menu_tfdlogo, chr_bank_0) = {
    #embed "./chr/dnt/Menu_TFDLogo.bin"
};    
file(chr_menu_famidash, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Famidash.bin"
}; 
file(chr_menu_robtop, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Robtop.bin"
};    
file(chr_menu_iconkit, chr_bank_0) = {
    #embed "./chr/dnt/Menu_Iconkit.bin"
};    



// block sets
file(chr_tiles_global, chr_bank_1) = {
    #embed "./chr/dnt/General.bin"
};    
file(chr_tiles_checker, chr_bank_1) = {
    #embed "./chr/dnt/Game_Tiles_Checker.bin"
};    
file(chr_tiles_x, chr_bank_1) = {
    #embed "./chr/dnt/Game_Tiles_X.bin"
};
file(chr_tiles_black, chr_bank_1) = {
    #embed "./chr/dnt/Game_Tiles_Black.bin"
};
file(chr_tiles_chipped, chr_bank_1) = {
    #embed "./chr/dnt/Game_Tiles_Chipped.bin"
};
file(chr_tiles_brick, chr_bank_1) = {
    #embed "./chr/dnt/Game_Tiles_Brick.bin"
};



file(chr_tiles_onedotnine, chr_bank_1) = {
    #embed "./chr/dnt/Game_Tiles_onedotnine.bin"
};


// backgrounds
file(chr_background_0, chr_bank_2) = {
    #embed "./chr/dnt/Background0.bin"
};
file(chr_background_1, chr_bank_2) = {
    #embed "./chr/dnt/Background1.bin"
};
file(chr_background_2, chr_bank_2) = {
    #embed "./chr/dnt/Background2.bin"
};

#ifdef ROM_LITE
file(chr_ad_0, chr_bank_4) = {
    0x11, 0x21, 0x39,
    #embed "./chr/dnt/Ad_GDA.bin"
};
file(chr_ad_1, chr_bank_4) = {
    0x16, 0x10, 0x30,
    #embed "./chr/dnt/Ad_SNES.bin"
};
file(chr_ad_2, chr_bank_4) = {
    0x2d, 0x10, 0x30,
    #embed "./chr/dnt/Ad_Slope.bin"
};
file(chr_ad_3, chr_bank_4) = {
    0x12, 0x10, 0x39,
    #embed "./chr/dnt/Ad_WiiDash.bin"
};
file(chr_ad_4, chr_bank_4) = {
    0x0c, 0x1c, 0x39,
    #embed "./chr/dnt/Ad_FD2.bin"
};
file(chr_ad_5, chr_bank_4) = {
    0x0f, 0x19, 0x29,
    #embed "./chr/dnt/Ad_Retray.bin"
};
file(chr_ad_6, chr_bank_4) = {
    0x02, 0x11, 0x2b,
    #embed "./chr/dnt/Ad_Tactus.bin"
};
file(chr_ad_7, chr_bank_4) = {
    0x0f, 0x16, 0x20,
    #embed "./chr/dnt/Ad_Famiwiki.bin"
};

banked(chr_bank_4) const u8 * const chr_ads[] = {
    chr_ad_0,
    chr_ad_1,
    chr_ad_2,
    chr_ad_3,
    chr_ad_4,
    chr_ad_5,
    chr_ad_6,
    chr_ad_7
};

#endif


// grounds
file(chr_ground_0, chr_bank_3) = {
    #embed "./chr/dnt/Ground0.bin"
};
file(chr_ground_1, chr_bank_3) = {
    #embed "./chr/dnt/Ground1.bin"
};
file(chr_ground_2, chr_bank_3) = {
    #embed "./chr/dnt/Ground2.bin"
};
file(chr_ground_3, chr_bank_3) = {
    #embed "./chr/dnt/Ground3.bin"
};


file(chr_icon0, chr_bank_3) = {
    #embed "./chr/dnt/Icon0.bin"
};






//__attribute__((section(".prg_rom_fixed_lo.2000"), retain))
const u8 * const chr_bg[] = {
    chr_background_0,
    chr_background_1,
    chr_background_2
};

//__attribute__((section(".prg_rom_fixed_lo.2001"), retain))
const u8 * const chr_g[] = {
    chr_ground_0,
    chr_ground_1,
    chr_ground_2,
    chr_ground_3,
};





// samples n such
file(samples_0, sample_bank_0) = {
    #embed "./samples/geometryDash0.pcm"
};
file(samples_1, sample_bank_1) = {
    #embed "./samples/geometryDash1.pcm"
};
file(pcm_playsound_01, sample_bank_2) = {
    #embed "./samples/playSound_01.pcm"
};