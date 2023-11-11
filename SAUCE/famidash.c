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

    ppu_on_all();
    
    gameState = 0x01;
    
    
    while (1){
        ppu_wait_nmi();

		switch (gameState){
			case 0x01: state_menu(); break;
			case 0x02: state_game(); break;
		}
    }
}
























































































