#include "include.h"

void main(){
    ppu_off();
    ppu_on_all();
    famistudio_music_play(0);
    while (1){
        ppu_wait_nmi();
    }
}