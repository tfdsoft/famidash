// THE GAME LOOP ==============================================
//
// yup, this is the entire game loop. it's that simple.
// I wanted to make the code super easy to read, so I split it
// into dozens of files, each containing segments of code.
//
// ============================================================



// THE INCLUDE FILE ===========================================
//
// The entirety of the project is on the shoulders of this
// singular line. 
//
//                    DO. NOT. REMOVE. IT.
//
// If you have issues with the repository and the cause is you
// removing this line, the entire team will be informed to not
// communicate with you further.
#include "include.h"
// ============================================================



// VOID MAIN() ================================================
//
// This isn't an int main() because i don't use the terminal to
// debug lmao
void main(){
    ppu_off();

    ppu_mask(0x00);

    // banking for CHR to allocate dierctly
    /*
    mmc3_set_2kb_chr_bank_0(0);
    mmc3_set_2kb_chr_bank_1(2);
    mmc3_set_1kb_chr_bank_0(4);
    mmc3_set_1kb_chr_bank_1(5);
    mmc3_set_1kb_chr_bank_2(6);
    mmc3_set_1kb_chr_bank_3(7);
    */
    

    pal_bg((char *)paletteDefault);
    pal_spr((char *)paletteDefaultSP);
    // use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

    set_vram_buffer(); // do at least once

    ppu_on_all();
    pal_fade_to(4,0);
    gameState = 0x01;
    level = 0x01;
    
    while (1){
        ppu_wait_nmi();

		switch (gameState){
			case 0x01: state_menu(); break;
			case 0x02: state_game(); break;
            case 0x03: state_lvldone(); break;
            case 0x04: state_demo(); break;
		}
    }
}
// ============================================================


// WHY I SPLIT THE GAME LOOP ==================================
//
// I like making my code super readable by outsiders, and I
// felt like this was the best way to do it.
// ============================================================