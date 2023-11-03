#include "include.h"

void main(){
    ppu_off();
    pal_bg(paletteDefault);
    load_ground(0);
    ppu_on_all();
    famistudio_music_play(song_geometry_dash_menu_theme);
    while (1){
        ppu_wait_nmi();
    }
}
























































































void load_ground(unsigned char id){
    vram_adr(NAMETABLE_B);
    vram_unrle(ground[id]);
}