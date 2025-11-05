#include "assets.h"

// menu stuff
file(chr_font, chr_bank_0) = {
    #embed "./chr/dnt/Font.bin"
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








__attribute__((section(".prg_rom_fixed_lo.2000"), retain))
const uint8_t * const chr_bg[] = {
    chr_background_0,
    chr_background_1,
    chr_background_2
};

__attribute__((section(".prg_rom_fixed_lo.2001"), retain))
const uint8_t * const chr_g[] = {
    chr_ground_0,
    chr_ground_1,
    chr_ground_2,
    chr_ground_3,
};



/*
.segment "_pprg__rom__45"
	firstDMCBankPtr := *
	.incbin "music_bank0.dmc"
.segment "_pprg__rom__46"
	.incbin "music_bank2.dmc"
.segment "_pprg__rom__47"
	.incbin "music_bank6.dmc"
.segment "_pprg__rom__48"
	.incbin "music_bank8.dmc"
.segment "_pprg__rom__49"
	.incbin "music_bank10.dmc"
.segment "_pprg__rom__50"
	.incbin "music_bank14.dmc"
.segment "_pprg__rom__51"
	.incbin "music_bank16.dmc"
    */