#include "include.h"

void main(){
    ppu_off();
    ppu_mask(0x00);

    pal_bg(paletteDefault);
    pal_spr(paletteDefault);
    // use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

    set_vram_buffer(); // do at least once
    
    scroll_y = 0xEF;
    load_ground(0);
    
    init_rld(0);
    unrle_first_screen();

    famistudio_music_play(song_stereo_madness_foreverbound);

    ppu_on_all();
    
    
    
    
    while (1){
        ppu_wait_nmi();

        pad = pad_poll(0);
        pad_new = get_pad_new(0);

        do_the_scroll_thing();
        
        
        

        

        draw_screen_R();
        gray_line();
    }
}
























































































