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

    ppu_mask(0x00 | (1 << 1) | (1 << 2));

    // banking for CHR to allocate dierctly
    /*
    mmc3_set_2kb_chr_bank_0(0);
    mmc3_set_2kb_chr_bank_1(2);
    mmc3_set_1kb_chr_bank_0(4);
    mmc3_set_1kb_chr_bank_1(5);
    mmc3_set_1kb_chr_bank_2(6);
    mmc3_set_1kb_chr_bank_3(7);
    */
    
	mmc3_set_8kb_chr(12);

    pal_bg((char *)paletteDefault);
    pal_spr((char *)paletteDefaultSP);
    // use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

    set_vram_buffer(); // do at least once

    // ppu_on_all();
    // pal_fade_to(4,0);
    gameState = 0x01;
    level = 0x00;
  	player_gravity[0] = 0x00;
	if (twoplayer) player_gravity[1] = 0x00;
	else player_gravity[1] = 0x01;	

	auto_fs_updates = 0;
	
    while (1){
        ppu_wait_nmi();

		switch (gameState){
			case 0x01: {
				mmc3_set_prg_bank_1(GET_BANK(state_menu));
				menuselection = 0;
				state_menu(); 
				break;
			}
			case 0x02: {
  				player_gravity[0] = 0x00;
			//	if (twoplayer)
				player_gravity[1] = 0x00;
			//	else player_gravity[1] = 0x01;						
				state_game(); break;
			}
			case 0x03: {
				mmc3_set_prg_bank_1(0);
				state_lvldone();
				break;
			}
			//case 0x04: state_demo(); break;
		}
    }
}
// ============================================================


// WHY I SPLIT THE GAME LOOP ==================================
//
// I like making my code super readable by outsiders, and I
// felt like this was the best way to do it.
// ============================================================

void setdefaultoptions() {
		SRAM_VALIDATE[0] = 0x0d;
		SRAM_VALIDATE[1] = 0x0a;
		SRAM_VALIDATE[2] = 0x01;
		SRAM_VALIDATE[3] = 0x04;
		for (tmp2 = 0; tmp2 <= LEVEL_COUNT; tmp2++) {
			coin1_obtained[tmp2] = 0;
			coin2_obtained[tmp2] = 0;
			coin3_obtained[tmp2] = 0;
		}

		tmp2 = 0;
		while (tmp2 <= LEVEL_COUNT) {
			LEVELCOMPLETE[tmp2] = 0;
			tmp2++;
		}
		SRAM_VALIDATE[0x0E] = 0;
		SRAM_VALIDATE[0x0F] = 0;
		SRAM_VALIDATE[0x10] = 0;
		SRAM_VALIDATE[0x11] = 0;
		SRAM_VALIDATE[0x12] = 0;
		SRAM_VALIDATE[0x13] = 0;
		SRAM_VALIDATE[0x14] = 0;
		SRAM_VALIDATE[0x15] = 0;
		SRAM_VALIDATE[0x16] = 0;
		SRAM_VALIDATE[0x17] = 0;
		SRAM_VALIDATE[0x18] = 0;
		SRAM_VALIDATE[0x19] = 0;
		SRAM_VALIDATE[0x1A] = 0;
		SRAM_VALIDATE[0x1B] = 0;
		SRAM_VALIDATE[0x1C] = 0;
		SRAM_VALIDATE[0x1D] = 0;
		SRAM_VALIDATE[0x1E] = 0;
		SRAM_VALIDATE[0x1F] = 0;
		musicoff = 0;
		sfxoff = 0;
		jumpsound = 0;
		twoplayer = 0;
		oneptwoplayer = 0;
		platformer = 0;
		invisible = 0;
		color1 = 0x2A;
		color2 = 0X21;		
		color3 = 0x0F;
		return;
}