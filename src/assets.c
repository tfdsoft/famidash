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

#define sample_bank_0 52
#define sample_bank_1 53
#define sample_bank_2 54
#define sample_bank_3 55

#define chr_bank_0 56
#define chr_bank_1 57
#define chr_bank_2 58
#define chr_bank_3 59

#define startup_bank 60
#define debug_bank 0

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



// block sets
file(chr_tiles_global, chr_bank_1) = {
    #embed "./chr/dnt/General.bin"
};    
file(chr_tiles_grid, chr_bank_1) = {
    #embed "./chr/dnt/Grid.bin"
};    
file(chr_tiles_cross, chr_bank_1) = {
    #embed "./chr/dnt/Cross.bin"
};
file(chr_tiles_brick, chr_bank_1) = {
    #embed "./chr/dnt/Brick.bin"
};
file(chr_tiles_black, chr_bank_1) = {
    #embed "./chr/dnt/Black.bin"
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