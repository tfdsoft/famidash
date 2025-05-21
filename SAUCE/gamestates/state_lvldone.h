CODE_BANK_PUSH("XCD_BANK_06")

void checkcointimer();
void checkcoinproceed();
void lvl_done_update();

void state_lvldone() {
	#define current_state tmp2
	#define sprite_0_y tmp3
	#define delay_spr_0 tmp4
	#define delay_timer tmpptr1
	#define top_scroll scroll_x
	oam_clear();
    ppu_off();

	delay_spr_0 = 0x20;
	#if __VS_SYSTEM
	menutimer = 0;
	#endif
	current_state = 0;
	// Set palettes back to natural colors since we aren't fading back in
	pal_bright(4);
	pal_bg(paletteMenu);
	pal_col(0x0A,0x2A);
	pal_col(0x0B,0x21);
	pal_set_update();
    //pal_spr(paletteMenu);
	pal_spr(paletteDefaultSP);
	mmc3_set_1kb_chr_bank_0(LEVELCOMPLETEBANK);
	mmc3_set_1kb_chr_bank_1(PRACTICECOMPLETEBANK);
	mmc3_set_1kb_chr_bank_2(LEVELCOMPLETEBANK+2);
	mmc3_set_1kb_chr_bank_3(LEVELCOMPLETEBANK+3);
	
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	// Make a nametable for the chain
    vram_adr(NAMETABLE_C);
	vram_fill(0xfe, 0x3c0);
	vram_fill(0x00, 0x3f);

	// Copy the level done screen to the bot left and right nametable
	vram_adr(NAMETABLE_A);
	if (practice_point_count) {
		vram_unrle(practicedone);
	} else {
		vram_unrle(leveldone);
	}

	#include "defines/charmap/endlevel_charmap.h"

	tmp1 = 0;
	tmpptr1 = NULL;
	#if !__VS_SYSTEM
	display_attempt_counter(0xD0, NTADR_A(20, 13));	// Same bank as this
	#endif
	
	hexToDec(jumps);

	tmp1 = 0;
	
	if (hexToDecOutputBuffer[4]) {
		one_vram_buffer(0xD0+hexToDecOutputBuffer[4], NTADR_A(18,15));
		tmp1++;
	}

	if (hexToDecOutputBuffer[4] | hexToDecOutputBuffer[3]) {
		one_vram_buffer(0xD0+hexToDecOutputBuffer[3], NTADR_A(18+tmp1,15));
		tmp1++;
	}
	
	if (hexToDecOutputBuffer[4] | hexToDecOutputBuffer[3] | hexToDecOutputBuffer[2]) {
		one_vram_buffer(0xD0+hexToDecOutputBuffer[2], NTADR_A(18+tmp1,15));
		tmp1++;
	}

	if (hexToDecOutputBuffer[4] | hexToDecOutputBuffer[3] | hexToDecOutputBuffer[2] | hexToDecOutputBuffer[1]) {
		one_vram_buffer(0xD0+hexToDecOutputBuffer[1], NTADR_A(18+tmp1,15));
		tmp1++;
	}
	one_vram_buffer(0xD0+hexToDecOutputBuffer[0], NTADR_A(18+tmp1,15));
	
	if (!practice_point_count) {
		LEVELCOMPLETE[level] = 1;
		
		if (coins & COIN_1) coin1_obtained[level] = 1;
		if (coins & COIN_2) coin2_obtained[level] = 1;
		if (coins & COIN_3) coin3_obtained[level] = 1;

		level_completeness_normal[level] = 100;
	} else {
		level_completeness_practice[level] = 100;
	}
	
	flush_vram_update2();

    set_scroll_x(0x00);


	tmp5 = 0x0000; // speed
	tmp6 = 0xf000; // real y 

    set_scroll_y(0xe8);
    ppu_on_all();

	sfx_play(sfx_level_complete, 0);
	menuselection = 1;
	practice_point_count = 0;

	#if __VS_SYSTEM
	coins_inserted--;
	#endif
	
	while (1) {
		ppu_wait_nmi();
		
		music_update();

 		// read the first controller

		kandoframecnt++;

		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;
		switch (current_state) {
		case 0:
			tmp5 += 0x40;
			tmp6 -= tmp5;
			set_scroll_y(high_byte(tmp6));
			
			if (high_byte(tmp6) < 10) {
				current_state = 1;
				tmp5 = -0x0600;
			}
			break;
		case 1:
			tmp5 += 0x40;
			tmp6 -= tmp5;
			set_scroll_y(high_byte(tmp6));
			if (high_byte(tmp6) < 5 && !(high_byte(tmp5) & 0x80)) {
				current_state = 2;
				tmp5 = -0x0300;
			}
			break;
		case 2:
			tmp5 += 0x40;
			tmp6 -= tmp5;
			set_scroll_y(high_byte(tmp6));
			if (high_byte(tmp6) < 3 && !(high_byte(tmp5) & 0x80)) {
				current_state = 3;
				set_scroll_y(0);
			}
			break;
		case 3:
			// Draw the level stat text
			//achievements
			kandokidshack = 0;
			kandokidshack2 = 0;

			tmp2 = 0;
			do {
				// kandokidshack = kandokidshack + coin1_obtained[tmp2] + coin2_obtained[tmp2] + coin3_obtained[tmp2];
				__A__ = tmp2; __asm__("tay");
				__A__ = kandokidshack;
				__asm__("clc \n adc %v, y", coin1_obtained);
				__asm__("clc \n adc %v, y", coin2_obtained);
				__asm__("clc \n adc %v, y", coin3_obtained);
				kandokidshack = __A__;
				
				if (LEVELCOMPLETE[tmp2]) kandokidshack2 += stars_list[tmp2];
				tmp2++;
			}
			#ifdef FLAG_ENABLE_TEST_LEVELS
			while (tmp2 < 255);
			#else
			while (tmp2 < LEVEL_COUNT2);
			#endif

			tmp2 = 0;


/*
			do {
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
			} while (++tmp2 <= 10);

			if (!achievements[11]) {
				if (kandokidshack >= 10) {
					achievements[11] = 1;
					//display text here
				}
			}

			if (!achievements[12]) {
				if (kandokidshack >= 20) {
					achievements[12] = 1;
					//display text here
				}
			}
				
			
			if (!achievements[13]) {
				if (kandokidshack >= 30) {
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
*/
			current_state = 4;
			tmp1 = 1;
			break;
		case 4: // coin 1
			if (coins & COIN_1){
				one_vram_buffer(0x90, NTADR_A(11,18));
				one_vram_buffer(0x91, NTADR_A(12,18));
				one_vram_buffer(0xA0, NTADR_A(11,19));
				one_vram_buffer(0xA1, NTADR_A(12,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 5: // coin 2
			if (coins & COIN_2){
				one_vram_buffer(0x90, NTADR_A(15,18));
				one_vram_buffer(0x91, NTADR_A(16,18));
				one_vram_buffer(0xA0, NTADR_A(15,19));
				one_vram_buffer(0xA1, NTADR_A(16,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 6: // coin 3
			if (coins & COIN_3){
				one_vram_buffer(0x90, NTADR_A(19,18));
				one_vram_buffer(0x91, NTADR_A(20,18));
				one_vram_buffer(0xA0, NTADR_A(19,19));
				one_vram_buffer(0xA1, NTADR_A(20,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 7:
		lvl_done_update();
		oam_clear();

			mouse_and_cursor();

			if (mouse.left_press) {
				if (mouse.y >= 0xC5 && mouse.y <= 0xE3) {
					if (mouse.x >= 0x36 && mouse.x <= 0x53) {
						sfx_play(sfx_start_level, 0);
						gameState = STATE_GAME;
						pal_fade_to_withmusic(4,0);
						memfill(attemptCounter, 0, sizeof(attemptCounter));

						//oam_clear();
						coins = 0;
						return;					
					}
					if (mouse.x >= 0xA6 && mouse.x <= 0xc3) {
						sfx_play(sfx_exit_level, 0);
						music_update();
						gameState = STATE_MENU;
						menuselection = 0;
						kandowatchesyousleep = 1;
						//oam_clear();
						menuMusicCurrentlyPlaying = 0;
						return;
					}
				}
			}

		#if !__VS_SYSTEM	// Disable level restarting on VS system
			if (joypad1.press_left) { menuselection ^= 1; lvl_done_update(); }
			if (joypad1.press_right) { menuselection ^= 1; lvl_done_update(); }
			if (joypad1.press_start || joypad1.press_a){
				if (menuselection) {
		#else
			if (joypad1.press_start || joypad1.press_a || menutimer == 2000){
		#endif

					sfx_play(sfx_exit_level, 0);
					music_update();
					gameState = STATE_MENU;
					menuselection = 0;
					kandowatchesyousleep = 1;

					//oam_clear();
					menuMusicCurrentlyPlaying = 0;
					return;
			#if !__VS_SYSTEM
				} else {
					
					sfx_play(sfx_start_level, 0);
					gameState = STATE_GAME;
					pal_fade_to_withmusic(4,0);
					memfill(attemptCounter, 0, sizeof(attemptCounter));
					coins = 0;


					//oam_clear();
					return;
				}
			#endif
			}


		#if __VS_SYSTEM
			menutimer++;
		#endif

		}
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
						
	}
	#undef current_state
	#undef sprite_0_y
	#undef delay_spr_0
	#undef delay_timer
	#undef top_scroll
}

#include "defines/charmap/endlevel_charmap.h"
void lvl_done_update() {
	if (menuselection) {
		one_vram_buffer(0xFF, NTADR_A(8,23));
		one_vram_buffer(0xFF, NTADR_A(9,23));
		one_vram_buffer(0x94, NTADR_A(22,23));
		one_vram_buffer(0x95, NTADR_A(23,23));
	} else {
		one_vram_buffer(0x94, NTADR_A(8,23));
		one_vram_buffer(0x95, NTADR_A(9,23));
		one_vram_buffer(0xFF, NTADR_A(22,23));
		one_vram_buffer(0xFF, NTADR_A(23,23));
	}
}	


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

CODE_BANK_POP()
