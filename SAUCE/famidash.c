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
	mmc3_set_8kb_chr(MENUBANK);

	// disable debug mode toggle
	options &= debugtoggle^0xFF;

    //pal_bg(paletteDefault);
    //pal_spr(paletteDefaultSP);
    // use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

	mouse.x = 0x78;
	mouse.y = 0x60;
	mouse_mask = 1;
    set_vram_buffer(); // do at least once

    // ppu_on_all();
    // pal_fade_to(4,0);

	// needed for cc65 to export the label for mesen
    gameState = 0x01;
	
	// These are done at init time
    // level = 0x00;
	// auto_fs_updates = 0;

	//mmc3_set_prg_bank_1(GET_BANK(playPCM));
	//playPCM(0);

	pal_spr(paletteDefaultSP);
	menuMusicCurrentlyPlaying = 0;
	crossPRGBankJump0(gameboy_check);
	gameState = 0x05;
    while (1){
		ppu_wait_nmi();
		switch (gameState){
			case 0x01: {
				mmc3_set_prg_bank_1(GET_BANK(state_menu));
				if (!kandowatchesyousleep) state_menu();
				else {
					pal_fade_to_withmusic(4,0);
					ppu_off();
					pal_bg(splashMenu);
					kandowatchesyousleep = 1;

					//
					practice_point_count = 0;
					#include "defines/mainmenu_charmap.h"
					levelselection();
				}
				break;
			}
			case 0x02: {
				state_game();
				use_auto_chrswitch = 0;
				break;
			}
			case 0x03: {
				mmc3_set_prg_bank_1(GET_BANK(state_lvldone));
				state_lvldone();
				break;
			}
			case 0x04: {
				mmc3_set_prg_bank_1(GET_BANK(bgmtest));
				bgmtest();
				break;
			}
			case 0x05: {
				#if !__VS_SYSTEM
					music_play(song_scheming_weasel);
				#endif
				mmc3_set_prg_bank_1(GET_BANK(state_savefile_validate));
				state_savefile_validate();
				break;
			}
			case 0x06: {
				mmc3_set_prg_bank_1(GET_BANK(state_savefile_editor));
				state_savefile_editor();
				break;
			}


			case 0xF0: {
				mmc3_set_prg_bank_1(GET_BANK(funsettings));
				funsettings();
				break;
			}
			case 0xF1: {
				mmc3_set_prg_bank_1(GET_BANK(state_instructions));
				state_instructions();
				break;
			}
			#if LEVELSET != 'A'
			case 0xF2: {
				mmc3_set_prg_bank_1(GET_BANK(state_playmain));
				state_playmain();
				break;
			}
			#endif
			case 0xFE: {
				mmc3_set_prg_bank_1(GET_BANK(state_exit));
				state_exit();
				break;
			}
			default: {
				mmc3_set_prg_bank_1(GET_BANK(state_demo));
				state_demo();
				break;
			}
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
	// Enable SRAM write
	POKE(0xA001, 0x80);
	

	color_emphasis(COL_EMP_DARK);
	mmc3_disable_irq();
	// fill with zeros
	memfill((uint8_t *)0x6000, 0, 0x1FFE);
	edit_irq_table(0xff,0);
	//sfx_play(sfx_death, 0);

	color_emphasis(COL_EMP_NORMAL);

	// set the first three bytes; LEET, and save version.
	// if none of these are what is expected, the game will tell you
	SRAM_VALIDATE[0] = 0x13;
	SRAM_VALIDATE[1] = 0x37;
	SRAM_VALIDATE[2] = FLAG_SAVE_VER;
	forced_credits = 1;
	// only non-zero values need to be set here

	twoplayer = 0;
	//musicoff = 0;
	//sfxoff = 0;
	//jumpsound = 0;
	//oneptwoplayer = 0;
	//platformer = 0;
	options = 0; 
	tmp2 = 0;
	do {
		coin1_obtained[tmp2] = 0;
		coin2_obtained[tmp2] = 0;
		coin3_obtained[tmp2] = 0;
		LEVELCOMPLETE[tmp2] = 0;
		level_completeness_normal[tmp2] = 0;
		level_completeness_practice[tmp2] = 0;
	} while (++tmp2 < (MAX_LEVEL_COMPLETE));
	tmp2 = 0;
	do {
		achievements[tmp2] = 0;
	} while (++tmp2 < (sizeof(achievements)));
	invisible = 0;
	color1 = 0x2A;
	color2 = 0X2C;		
	color3 = 0x0F;
	discomode = 0;
	icon = 0;
	trails = 0;
	retro_mode = 0;
	//palette_cycle_mode = 0;
	gameboy_mode = 0;
	viseffects = 1;
	invisblocks = 0;
	cam_seesaw = 0;
	menu_music = 0;
	#if !__VS_SYSTEM
	auto_practicepoints = 1;
	practice_music_sync = 0;
	#endif
	return;
}
