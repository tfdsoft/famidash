#include "assets.h"

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