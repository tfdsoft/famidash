extern volatile unsigned char VRAM_UPDATE;
#pragma zpsym ("VRAM_UPDATE")

#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")


void checkcointimer(){
	if (tmp1 == 1){
		sfx_play(sfx_coin,0);
		tmp1 = 50;
	}
}
void checkcoinproceed(){
	if (tmp1 == 0 || tmp1 == 30) {
		tmp2++;
		tmp1 = 1;
	}
}


void state_lvldone() {
	#define current_state tmp2
	#define sprite_0_y tmp3
	#define delay_spr_0 tmp4
	#define delay_timer tmpptr1
	#define top_scroll scroll_x
    ppu_off();

	delay_spr_0 = 0x20;

	current_state = 0;

	// Set palettes back to natural colors since we aren't fading back in
	pal_bright(4);

    pal_bg(paletteMenu);
	pal_col(0x0A,0x2A);
	pal_col(0x0B,0x21);
    pal_spr(paletteMenu);

	mmc3_set_8kb_chr(LEVELCOMPLETEBANK);

	// Make an a nametable for the chain
    vram_adr(NAMETABLE_A);
	vram_fill(0xfe, 0x3c0);
	vram_fill(0x00, 0x3f);
	// vertical increment: draw the chains
	vram_inc(1);
    vram_adr(NTADR_A(5, 0));
	vram_fill(0xae, 30);
    vram_adr(NTADR_A(26, 0));
	vram_fill(0xae, 30);

	// Make an empty nametable for the scroll split
    vram_adr(NAMETABLE_B);
	vram_inc(0);
	vram_fill(0xfe, 0x3c0);
	vram_fill(0x00, 0x3f);

	// Copy the level done screen to the bot left and right nametable
    vram_adr(NAMETABLE_C);
    vram_unrle(leveldone);

	// Change the text attributes for the press to return
	// no longer required
    //vram_adr(0x2be1);
	//vram_fill(0xff, 0x6);

    vram_adr(NAMETABLE_D);
    vram_unrle(leveldone);

	#include "defines/endlevel_charmap.h"
	//multi_vram_buffer_horz((const char*)menutext3,sizeof(menutext3)-1,NTADR_C(6, 16));
	//multi_vram_buffer_horz((const char*)menutext4,sizeof(menutext4)-1,NTADR_C(8, 18));
	//multi_vram_buffer_horz((const char*)attemptstext,sizeof(attemptstext)-1,NTADR_C(7, 19));
	
	tmp1 = 0;
	tmpptr1 = NULL;

	display_attempt_counter(0xD0, NTADR_C(25, 13));	// Same bank as this
	
	if (!has_practice_point) {
		LEVELCOMPLETE[level] = 1;
		
		if (coins & COIN_1) coin1_obtained[level] = 1;
		if (coins & COIN_2) coin2_obtained[level] = 1;
		if (coins & COIN_3) coin3_obtained[level] = 1;

		level_completeness_normal[level] = 100;
	} else {
		level_completeness_practice[level] = 100;
	}
	
	
	if (!coins) {
		tmp1 = sizeof(coins0) - 1;
		tmpptr1 = (unsigned char*)coins0;
	} else if ((coins & 7) == 7) {
		tmp1 = sizeof(coins3) - 1;
		tmpptr1 = (unsigned char*)coins3;
	} else if (((coins & COIN_1) && (coins & COIN_2)) || ((coins & COIN_2) && (coins & COIN_3)) || ((coins & COIN_1) && (coins & COIN_3))) {
		tmp1 = sizeof(coins2) - 1;
		tmpptr1 = (unsigned char*)coins2;
	} else if (coins & COIN_1 || coins & COIN_2 || coins & COIN_3) {
		tmp1 = sizeof(coins1) - 1;
		tmpptr1 = (unsigned char*)coins1;
	}
	 
	//if (tmp1) multi_vram_buffer_horz((const char*)tmpptr1,tmp1,NTADR_C(17,18));
	flush_vram_update2();

	// Set the start of the scroll to the top nametable
	// so we can scroll it down (so the screen comes up)
    top_scroll = 0x00;

	// setup sprite zero at the very bottom of the screen for now
	sprite_0_y = 0xee;
	POKE(0x200, sprite_0_y);
	POKE(0x201, 0x02); // Use the second tile in the BG side which is pure black
	POKE(0x202, 0x02); // second palette
	POKE(0x203, 0);

    set_scroll_x(0);
    set_scroll_y(top_scroll);

	//	one_vram_buffer(0xD0+coins, NTADR_A(12,9));

    ppu_on_all();



	sfx_play(sfx_level_complete, 0);
	menuselection = 1;

	while (1) {
		// Rather hacky, but when doing sprite zero at the bottom of the screen we DON'T 
		// want to skip a frame, so we re-enable NMI and then if NMI happens during the frame
		// we don't have a lag frame by skipping it.
		if (VRAM_UPDATE == 1) {
        	ppu_wait_nmi();
		}
		// force re-enable NMI every frame.
		VRAM_UPDATE = 1;

		music_update();

		// wait for sprite zero hit
		if (current_state > 0 && current_state < 3) {
			xy_split(0x100, scroll_y);
		}

 		// read the first controller
		pad_poll(0);
		// Move the sprite zero hit to the new location
		POKE(0x200, sprite_0_y);

		switch (current_state) {
		case 0:
			// Scroll the screen top bar up a bit
			top_scroll += 2;
			set_scroll_y(top_scroll);
			if (top_scroll >= 31) {
				scroll_y = 256 + 208 - 1;
				current_state = 1;
			}
			break;
		case 1:
			// keep scrolling up, but have sprite zero follow now
			sprite_0_y -= 2;
			top_scroll += 2;
			set_scroll_y(top_scroll);
			// Play the level complete noise
			// if (top_scroll == 115) {
			// }
			if (top_scroll > 151) {
				current_state = 2;
			}
			break;
		case 2:
			// keep scrolling up, but change the scroll split Y
			// so it starts to "unravel"
			sprite_0_y -= 2;
			top_scroll += 2;
			scroll_y -= 4;
			set_scroll_y(top_scroll);
			if (top_scroll == 240) {
				set_scroll_x(0);
				set_scroll_y(0x100);
				current_state = 3;
			}
			break;
		case 3:
			// Draw the level stat text
			//achievements
			TOTALCOINS = 0;
			TOTALSTARS = 0;

			#ifdef FLAG_ENABLE_TEST_LEVELS
			for (tmp2 = 0; tmp2 < 255; tmp2++)
			#else
			for (tmp2 = 0; tmp2 < LEVEL_COUNT; tmp2++) 
			#endif
			{
				// TOTALCOINS = TOTALCOINS + coin1_obtained[tmp2] + coin2_obtained[tmp2] + coin3_obtained[tmp2];
				__A__ = tmp2; __asm__("tay");
				__A__ = TOTALCOINS;
				__asm__("clc \n adc %v, y", coin1_obtained);
				__asm__("clc \n adc %v, y", coin2_obtained);
				__asm__("clc \n adc %v, y", coin3_obtained);
				TOTALCOINS = __A__;
				
				if (LEVELCOMPLETE[tmp2]) TOTALSTARS += stars_list[tmp2];
			}

			for (tmp2 = 0; tmp2 <= 10; tmp2++) {
				if (!achievements[tmp2]) {
					if (LEVELCOMPLETE[tmp2]) {
						achievements[tmp2] = 1;
						switch (tmp2) {
							case 0:
							case 1:
							case 2:
							case 3:			//display achievements here
							case 4:
							case 5:
							case 6:
							case 7:
							case 8:
							case 9:
							case 10: break;
						};
					}
				}
			}

			if (!achievements[11]) {
				if (TOTALCOINS >= 10) {
					achievements[11] = 1;
					//display text here
				}
			}

			if (!achievements[12]) {
				if (TOTALCOINS >= 20) {
					achievements[12] = 1;
					//display text here
				}
			}
				
			
			if (!achievements[13]) {
				if (TOTALCOINS >= 30) {
					achievements[13] = 1;
					//display text here
				}
			}
				
			
			if (!achievements[14]) {
				
			}
			if (!achievements[15]) {
				
			}
			if (!achievements[16]) {
				
			}
			if (!achievements[17]) {
				
			}
			if (!achievements[18]) {
				
			}
			if (!achievements[19]) {
				
			}

			current_state = 4;
			tmp1 = 1;
			break;
		case 4: // coin 1
			if (coins & COIN_1){
				one_vram_buffer(0x90, NTADR_C(11,18));
				one_vram_buffer(0x91, NTADR_C(12,18));
				one_vram_buffer(0xA0, NTADR_C(11,19));
				one_vram_buffer(0xA1, NTADR_C(12,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 5: // coin 2
			if (coins & COIN_2){
				one_vram_buffer(0x90, NTADR_C(15,18));
				one_vram_buffer(0x91, NTADR_C(16,18));
				one_vram_buffer(0xA0, NTADR_C(15,19));
				one_vram_buffer(0xA1, NTADR_C(16,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 6: // coin 3
			if (coins & COIN_3){
				one_vram_buffer(0x90, NTADR_C(19,18));
				one_vram_buffer(0x91, NTADR_C(20,18));
				one_vram_buffer(0xA0, NTADR_C(19,19));
				one_vram_buffer(0xA1, NTADR_C(20,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 7:
			if (pad_new[0] & PAD_LEFT) menuselection ^= 1;
			if (pad_new[0] & PAD_RIGHT) menuselection ^= 1;
			if (pad_new[0] & PAD_START){
				if (menuselection) {
					
					sfx_play(sfx_exit_level, 0);
					music_update();
					gameState = 1;
					menuselection = 0;
					kandowatchesyousleep = 1;
					kandotemp = 0;
					return;
				} else {
					
					sfx_play(sfx_start_level, 0);
					gameState = 2;
					pal_fade_to_withmusic(4,0);
					memfill(attemptCounter, 0, sizeof(attemptCounter));
					coins = 0;
					return;
				}
			}


			if (menuselection) {
				one_vram_buffer(' ', NTADR_C(8,23));
				one_vram_buffer(' ', NTADR_C(9,23));
				one_vram_buffer(0x94, NTADR_C(22,23));
				one_vram_buffer(0x95, NTADR_C(23,23));
			} else {
				one_vram_buffer(0x94, NTADR_C(8,23));
				one_vram_buffer(0x95, NTADR_C(9,23));
				one_vram_buffer(' ', NTADR_C(22,23));
				one_vram_buffer(' ', NTADR_C(23,23));
			}
			break;
		}
	}
	#undef current_state
	#undef sprite_0_y
	#undef delay_spr_0
	#undef delay_timer
	#undef top_scroll
}
const unsigned char xlevel1text[]="STEREO ";
const unsigned char xlevel2text[]="BACK ON";
const unsigned char xlevel5text[]="BASE AFTER";
const unsigned char xlevelCtext[]="THEORY OF";
const unsigned char xlevelDtext[]="ELECTROMAN";

const unsigned char xlevel1text2[]="MADNESS";
const unsigned char xlevel2text2[]="TRACK";
const unsigned char xlevel3text2[]="POLARGEIST";
const unsigned char xlevel4text2[]="DRY OUT";
const unsigned char xlevel5text2[]="BASE";
const unsigned char xlevel6text2[]="CANT LET GO";
const unsigned char xlevel7text2[]="JUMPER";
const unsigned char xlevel8text2[]="TIME MACHINE";
const unsigned char xlevel9text2[]="CYCLES";
const unsigned char xlevelAtext2[]="XSTEP";
const unsigned char xlevelBtext2[]="CLUTTERFUNK";
const unsigned char xlevelCtext2[]="EVERYTHING";
const unsigned char xlevelDtext2[]="ADVENTURES";
const unsigned char xlevelEtext2[]="DECODE";
const unsigned char practicetext2[]="PRACTICE";
const unsigned char testformenu2[]="MENU";
const unsigned char everyendtext2[]="EVERY END";


const unsigned char* const xbgmtexts1[] = {
	0, 0, 0, 0, 0, xlevelDtext, 0, xlevel2text, xlevel5text, xlevel1text, xlevelCtext, 0, 0, 0, 0, 0, 0
};

const unsigned char* const xbgmtexts2[] = {
	xlevelBtext2, xlevelEtext2, practicetext2, xlevel8text2, xlevel3text2, xlevelDtext2, xlevel9text2, xlevel2text2, xlevel5text2, xlevel1text2, xlevelCtext2, testformenu2, xlevelAtext2, everyendtext2, xlevel7text2, xlevel4text2, xlevel6text2
};

const unsigned char xbgmtext2_size[] = {
	sizeof(xlevelBtext2) - 1,
	sizeof(xlevelEtext2) - 1,
	sizeof(practicetext2) - 1,
	sizeof(xlevel8text2) - 1,
	sizeof(xlevel3text2) - 1,
	sizeof(xlevelDtext2) - 1,	
	sizeof(xlevel9text2) - 1,	
	sizeof(xlevel2text2) - 1,	
	sizeof(xlevel5text2) - 1,	
	sizeof(xlevel1text2) - 1,	
	sizeof(xlevelCtext2) - 1,	
	sizeof(testformenu2) - 1,	
	sizeof(xlevelAtext2) - 1,	
	sizeof(everyendtext2) - 1,	
	sizeof(xlevel7text2) - 1,	
	sizeof(xlevel4text2) - 1,	
	sizeof(xlevel6text2) - 1,	
};
const unsigned char xbgmtext1_size[] = {
	0,
	0,
	0,
	0,
	0,
	sizeof(xlevelDtext) - 1,	
	0,
	sizeof(xlevel2text) - 1,	
	sizeof(xlevel5text) - 1,	
	sizeof(xlevel1text) - 1,	
	sizeof(xlevelCtext) - 1,	
	0,
	0,
	0,
	0,
	0,
	0,
};




#include "defines/bg_charmap.h"
const char TEXT_debug_mode[] = "DEBUG MODE ENABLED";
#include "defines/mainmenu_charmap.h"


void bgmtest() {
	song = 0;
	#define sfx tmp4
	sfx = 0;
	settingvalue = 0;
  	famistudio_music_stop();
  	music_update();
	kandotemp=0;
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);   	
	#include "defines/mainmenu_charmap.h"
	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	while (1) {
		
		ppu_wait_nmi();
		music_update();
		pad_poll(0); // read the first controller
		
	__A__ = idx16_hi_NOC(xbgmtexts1, song);
	if (__A__) draw_padded_text(xbgmtexts1[song & 0x7F], xbgmtext1_size[song], 17, NTADR_A(7, 10));
	else one_vram_buffer_horz_repeat(' ', 17, NTADR_A(7, 10));
	__A__ = idx16_hi_NOC(xbgmtexts2, song);
	if (__A__) draw_padded_text(xbgmtexts2[song & 0x7F], xbgmtext2_size[song], 17, NTADR_A(7, 11));
	else one_vram_buffer_horz_repeat(' ', 17, NTADR_A(7, 11));

		one_vram_buffer(' ', NTADR_A(14, 17));
		one_vram_buffer(0xd0+sfx, NTADR_A(15,17));

		if (settingvalue == 0) {
			one_vram_buffer('c', NTADR_A(11, 8));
			one_vram_buffer(' ', NTADR_A(11, 15));
			if (pad_new[0] & PAD_RIGHT) { song++; if (song == song_max) {song = 0;} }
			if (pad_new[0] & PAD_LEFT) { if (song == 0) {song = song_max - 1;} else song--; }
			if (pad_new[0] & PAD_A) music_play(song);
		}		
		else if (settingvalue == 1) {
			one_vram_buffer(' ', NTADR_A(11, 8));
			one_vram_buffer('c', NTADR_A(11, 15));
			if (pad_new[0] & PAD_RIGHT) { sfx++; if (sfx == sfx_max) {sfx= 0;} };
			if (pad_new[0] & PAD_LEFT) { if (sfx == 0) {sfx = sfx_max - 1;} else sfx--; }
			if (pad_new[0] & PAD_A) famistudio_sfx_play(sfx, 0);
		}

		if (pad_new[0] & PAD_DOWN) settingvalue ^= 1;
		if (pad_new[0] & PAD_UP) settingvalue ^= 1;
		
		if (pad_new[0] & PAD_SELECT) famistudio_music_stop();
		if (pad_new[0] & PAD_B) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			kandotemp = 1;
			gameState = 1;
			return;
		}


		
		// sound test codes
		if (pad_new[0] & PAD_START) {
			last_gameState = gameState;
			sfx_play(sfx_achievement_get, 0);
			tmp3 = 1;

			// bgm 9 & sfx 2
			if (song == 0x9 && sfx == 0x2) {
				gameState = 0xF0; // fun settings gamestate
				return;
			}
			if (song == 0xB && sfx == 0x7) {
				multi_vram_buffer_horz(TEXT_debug_mode, sizeof(TEXT_debug_mode)-1, NTADR_A(7,26));
				options |= debugtoggle;
				tmp3--;
			}

			// this is quite literally the greatest hack ever
			// since sfx doesn't update until the next frame i can just
			// overwrite the success sfx with the invalid one
			if (tmp3) sfx_play(sfx_invalid, 0);
		}
	}
	#undef sfx
}


void gameboy_check() {
		if (gameboy_mode == 0) color_emphasis(COL_EMP_NORMAL);
		else if (gameboy_mode == 1) color_emphasis(COL_EMP_GREY);
		else if (gameboy_mode == 2) { color_emphasis(COL_EMP_GREYRED); }
		else if (gameboy_mode == 3) { color_emphasis(COL_EMP_GREYGREEN); }
		else if (gameboy_mode == 4) { color_emphasis(COL_EMP_GREYBLUE); }
		else if (gameboy_mode == 5) { color_emphasis(COL_EMP_GREYYELLOW); }
		else if (gameboy_mode == 6) { color_emphasis(COL_EMP_GREYPURPLE); }
		else if (gameboy_mode == 7) { color_emphasis(COL_EMP_GREYCYAN); }
		else if (gameboy_mode == 8) { color_emphasis(COL_EMP_GREYDARK); }
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
