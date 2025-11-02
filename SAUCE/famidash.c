// THE GAME LOOP ==============================================
//
// yup, this is the entire game loop. it's that simple.
// I wanted to make the code super easy to read, so I split it
// into dozens of files, each containing segments of code.
//
// ============================================================

#if __HUGE_ROM
void choose_menu_theme();
#endif

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
	// Black out the PPU
    ppu_off();
    // Set brightness to nothing while at it
    pal_bright(0);
    // Enable both sprites and BG in the leftmost 8 pixels
    ppu_mask(0x00 | (1 << 1) | (1 << 2));
    // use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);
	// do at least once
    set_vram_buffer();
    // Set *a* palette
	pal_spr(paletteDefaultSP);

    // Initialize mapper
    mmc3_disable_irq();

    // Initialize controllers
	#if !__THE_ALBUM
	mouse.x = 0x78;
	mouse.y = 0x60;
	mouse_mask = 1;
	#endif
	// disable debug mode toggle
	options &= ~debugtoggle;

	// assigning value at startup as opposed to compile time
	// is needed for cc65 to export the label for mesen
	gameState = STATE_SAVEVALIDATE;
	nmi_fs_updates_on();

	menuMusicCurrentlyPlaying = 0;



    while (1){
    	forceNoFadeOut = 0;
		switch (gameState){
			case STATE_SOUNDTEST: {
				mmc3_set_prg_bank_1(GET_BANK(state_soundtest));
				state_soundtest();
				break;
			}
			case STATE_SAVEVALIDATE: {
				#if !__VS_SYSTEM
					music_play(song_scheming_weasel);
				#endif
				mmc3_set_prg_bank_1(GET_BANK(state_savefile_validate));
				state_savefile_validate();
				break;
			}

			case STATE_MENU: {
				#if __THE_ALBUM
					cursedmusic = 0;
				#endif
				#if __THE_ALBUM || __HUGE_ROM
					for (tmp1 = 0; tmp1 < MAX_SONG_QUEUE_SIZE; tmp1++) {
						music_queue[tmp1] = 0xFF;
					};
				#endif
				mmc3_set_prg_bank_1(GET_BANK(state_menu));
				state_menu();
				break;			
			}
			
		#if !__THE_ALBUM		//non-album states
		
			case STATE_GAME: {
				state_game();
				use_auto_chrswitch = 0;
				if (gameState == STATE_LVLDONE)	forceNoFadeOut = 1;
				break;
			}
			case STATE_LVLDONE: {
				mmc3_set_prg_bank_1(GET_BANK(state_lvldone));
				state_lvldone();
				break;
			}
			case STATE_FUNSETTINGS: {
				mmc3_set_prg_bank_1(GET_BANK(state_funsettings));
				state_funsettings();
				break;
			}
			case STATE_INSTRUCTIONS: {
				mmc3_set_prg_bank_1(GET_BANK(state_instructions));
				state_instructions();
				break;
			}
			case STATE_LEVELSELECT: {
				mmc3_set_prg_bank_1(GET_BANK(state_levelselect));
				state_levelselect();
				break;
			}
			case STATE_CUSTOMIZE: {
				mmc3_set_prg_bank_1(GET_BANK(state_customize));
				state_customize();
				break;
			}
			#if OFFICIAL_LEVEL_COUNT == 0 && TOTAL_LEVEL_COUNT != 0	// A levelset has levels but no official ones
			case STATE_PLAYMAIN: {
				mmc3_set_prg_bank_1(GET_BANK(state_playmain));
				state_playmain();
				break;
			}
			#endif

			#if !__VS_SYSTEM
			case STATE_SETTINGS: {
				mmc3_set_prg_bank_1(GET_BANK(state_settings));
				state_settings();
				break;
			}
			#endif

			#if __VS_SYSTEM
			case STATE_GAMEOVER: {
				mmc3_set_prg_bank_1(GET_BANK(state_gameover));
				state_gameover();
				break;
			}
			#endif

		#endif

			default: {
				mmc3_set_prg_bank_1(GET_BANK(state_credits));
				state_credits();
				#if __HUGE_ROM
				if (!menuthemechosen) crossPRGBankJump0(choose_menu_theme);
				#endif
				break;
			}
			

		}
		framerate = trueFramerate;
		cpuRegion = trueCpuRegion;
		fullRegion = trueFullRegion;
		nmi_fs_updates_on();
		if (!forceNoFadeOut) pal_fade_out();
		mmc3_disable_irq();
		ppu_off();
		if (forceNoFadeOut) flush_vram_update2();
    }
}

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
