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

    load_ground(0);
    set_scroll_y(0xEF);
    
    init_rld(0);
    unrle_first_screen();

    famistudio_music_play(song_stereo_madness_foreverbound);

    ppu_on_all();
    
    
    
    
    while (1){
        ppu_wait_nmi();
        gray_line();
        scroll_x += CUBE_SPEED_X1;

        set_scroll_x(high_byte(scroll_x));
        
        
        draw_screen_R();
    }
}
























































































void load_ground(unsigned char id){
    vram_adr(NAMETABLE_C);
    vram_unrle(ground[id]);
}