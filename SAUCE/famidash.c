#include "include.h"

void main(){
    ppu_off();
    pal_bg(paletteDefault);
    load_ground(0);
    ppu_on_all();
    famistudio_music_play(song_geometry_dash_menu_theme);
    set_scroll_y(0x100);
    while (1){
        ppu_wait_nmi();
    }
}
























































































void load_ground(unsigned char id){
    vram_adr(NAMETABLE_C);
    vram_unrle(ground[id]);
}