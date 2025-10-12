void lvl_done_update();
void refresh_queue_screen();
void text_stuff();
void play_next_queue();
void update_text1();
void update_text2();
void update_text3();
void unrle_bgm1();
void unrle_bgm2();

const unsigned char palette_Credits2[16]={ 0x11,0x0f,0x10,0x30,0x11,0x0f,0x2a,0x39,0x11,0x28,0x17,0x0f,0x11,0x0f,0x11,0x21 };

const uint8_t difficulty_pal_A[] ={
	0x21,	// easy
	0x2A,	// normal
	0x28,	// hard
	0x16,	// harder
	0x24,	// insane
	0x16,	// demon
	0x28,	// auto
};

const uint8_t difficulty_pal_B[] ={
	0x06,	// easy
	0x30,	// normal
	0x30,	// hard
	0x30,	// harder
	0x06,	// insane
	0x30,	// demon
	0x0F,	// auto
};

void refreshmenu();
void refreshmenu_part2();
void code_checker();
void check_if_music_stopped();
void set_fun_settings();
void checkcointimer(){
}
void checkcoinproceed(){

}

void state_lvldone() {

}

#include "defines/charmap/bgm_charmap.h"
#include "music_soundTestTables.h"
#include "sfx_soundTestTables.h"


#include "defines/charmap/bgm_charmap.h"
void state_soundtest() {
  	famistudio_music_stop();
  	music_update();

	pal_bg(paletteMenu);

	
	tempsong = 0;
	temptemp6 = 0; 	
	#define sfx tmp4
	sfx = 0;
	settingvalue = 0;
	menuMusicCurrentlyPlaying=0;
	
	crossPRGBankJump0(unrle_bgm1); 	
	update_text1();
	ppu_on_all();
	pal_fade_in();
	
	while (1) {
		//rand8();
		ppu_wait_nmi();
		oam_clear();
		check_if_music_stopped();
		 // read the first controller
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
		if (tmp4) refresh_queue_screen();
		if (tmp5) {
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist1, tempsong);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist1[tempsong & 0xFF], xbgmtextsCoveringArtist1Size[tempsong], 14, NTADR_A(9, 19));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 19));
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist2, tempsong);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist2[tempsong & 0xFF], xbgmtextsCoveringArtist2Size[tempsong], 14, NTADR_A(9, 20));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 20));
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist3, tempsong);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist3[tempsong & 0xFF], xbgmtextsCoveringArtist3Size[tempsong], 14, NTADR_A(9, 21));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 21));
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist4, tempsong);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist4[tempsong & 0xFF], xbgmtextsCoveringArtist4Size[tempsong], 14, NTADR_A(9, 22));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 22));
			tmp5 = 0;
		}

	if (joypad1.press_right || joypad1.press_left) hold_timer = 0;
	if (joypad1.press_right || (joypad1.right && hold_timer >= 15)) { tempsong++; temptemp6 = 0; if (tempsong == song_max) {tempsong = 0;} if (!queuemode) update_text1(); else update_text3(); hold_timer = 0;}
	if (joypad1.press_left || (joypad1.left && hold_timer >= 15)) { if (tempsong == 0) {tempsong = song_max - 1;} else tempsong--; temptemp6 = 0; if (!queuemode) update_text1(); else update_text3();  hold_timer = 0;}

	if (!queuemode) {		//not queue mode
		if (joypad1.press_b) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			menuMusicCurrentlyPlaying = 1;
			gameState = STATE_MENU;
			return;
		}
		if (joypad1.press_a) {
				song = tempsong;
				if (!temptemp6) { music_play(xbgmlookuptable[song]); temptemp6 = 1; songplaying = 1; }
				else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
		}					
		if (joypad1.press_select) { 
			ppu_off();
			crossPRGBankJump0(unrle_bgm2); 	   	
			ppu_on_all();
			queuemode = 1;
			update_text2();
			update_text3();
		}
	}
	else {					//queue mode
		if (joypad1.press_select) { 
			ppu_off();
			crossPRGBankJump0(unrle_bgm1);
			ppu_on_all();
			queuemode = 0;
			update_text1();
		}	
		if (joypad1.press_up) {
				play_next_queue();		//debug
		}
		if (joypad1.press_a) {
			if (music_queue[0] == 0xFF) { 
				song = tempsong;
				music_play(xbgmlookuptable[song]); 
				music_queue[0] = song;
				update_text2();
			}
			else {
				song = tempsong;
				for (tmp1 = 1; tmp1 < MAX_SONG_QUEUE_SIZE; tmp1++) {
					if (music_queue[tmp1] == 0xFF) {
						music_queue[tmp1] = song;
						break;
					}
				}
				if (music_queue[10] == 0xFF) update_text2();
			}
		}
		if (joypad1.press_b) {
			if (music_queue[0] == 0xFF) { }
			else if (music_queue[1] == 0xFF) { 
					music_queue[0] = 0xFF;
					refresh_queue_screen();
					tmp4 = 2;
					famistudio_music_stop();
					songplaying = 0;
			}
			else {
				for (tmp1 = MAX_SONG_QUEUE_SIZE - 1; tmp1--; tmp1 > 0) {
					if (music_queue[tmp1] != 0xFF) {
						music_queue[tmp1] = 0xFF;
						refresh_queue_screen();
						tmp4 = 2;
						break;
					}
				}
			}
		}
	}				
		
		// sound test codes
	if (hold_timer < 15) hold_timer++;	
	}
}


void refresh_queue_screen() {
		if (!tmp4 || tmp4 == 0xFF) {
//					ppu_off();
//					crossPRGBankJump0(unrle_bgm2);
					update_text2();
//					ppu_on_all();
					tmp4 = 2;
		}
		else if (tmp4 == 1) {
					update_text3();
					tmp4 = 3;
		}			
		else if (tmp4 == 2) {
			for (tmp1 = 2; tmp1 < 4; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));		
			if (music_queue[tmp1] != 0xFF) {
				tmp3 = music_queue[tmp1];
				__A__ = idx16_load_hi_NOC(xbgmtextsUpper, tmp3);
				if (__A__) { 
					multi_vram_buffer_horz(xbgmtextsUpper[tmp3 & 0x7F], xbgmtextsUpperSize[tmp3], NTADR_A(3, (13 + (tmp1))));
					multi_vram_buffer_horz(xbgmtextsLower[tmp3 & 0x7F], xbgmtextsLowerSize[tmp3], NTADR_A((4 + xbgmtextsUpperSize[tmp3]), (13 + (tmp1))));
				} else {
					multi_vram_buffer_horz(xbgmtextsLower[tmp3 & 0x7F], xbgmtextsLowerSize[tmp3], NTADR_A(3, (13 + (tmp1))));
					one_vram_buffer_horz_repeat('$', 7, NTADR_A((3 + xbgmtextsLowerSize[tmp3]), (13 + (tmp1))));
				}				
			} else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			tmp4 = 1;
			}
		}
		else if (tmp4 == 3) {
			for (tmp1 = 4; tmp1 < 6; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			if (music_queue[tmp1] != 0xFF) {
				text_stuff();			
			}
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			tmp4 = 4;
			}
		}
		else if (tmp4 == 4) {
			for (tmp1 = 6; tmp1 < 8; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			if (music_queue[tmp1] != 0xFF) {
				text_stuff();			
			}
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			tmp4 = 5;
			}
		}
		else if (tmp4 == 5) {
			for (tmp1 = 8; tmp1 < 10; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			if (music_queue[tmp1] != 0xFF) {
				text_stuff();			
			}
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			}
			tmp4 = 0;
		}
			
}					

//CODE_BANK_POP()




void colorinc() {
	if (idx8_inc(icon_colors, settingvalue) & 0x30) {
		if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
			idx8_store(icon_colors, settingvalue, (icon_colors[settingvalue] + 0x10) & 0x30);
	} else {
		if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
			icon_colors[settingvalue] = 0x0F;
	}	
}

void colordec() {
	if (idx8_dec(icon_colors, settingvalue) & 0x30) {
		if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
			idx8_store(icon_colors, settingvalue, (icon_colors[settingvalue] & 0x30) | 0x0C);
	} else {
		if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
			icon_colors[settingvalue] = 0x0C;
	}
}	


void update_text1() {
	__A__ = idx16_load_hi_NOC(xbgmtextsUpper, tempsong);
	if (__A__) draw_padded_text(xbgmtextsUpper[tempsong & 0xFF], xbgmtextsUpperSize[tempsong], 14, NTADR_A(9, 7));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
	__A__ = idx16_load_hi_NOC(xbgmtextsLower, tempsong);
	if (__A__) draw_padded_text(xbgmtextsLower[tempsong & 0xFF], xbgmtextsLowerSize[tempsong], 14, NTADR_A(9, 8));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
	
	__A__ = idx16_load_hi_NOC(xbgmtextsLowerOrigArtist, tempsong);
	if (__A__) draw_padded_text(xbgmtextsLowerOrigArtist[tempsong & 0xFF], xbgmtextsLowerOrigArtistSize[tempsong], 14, NTADR_A(9, 14));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 14));
	__A__ = idx16_load_hi_NOC(xbgmtextsUpperOrigArtist, tempsong);
	if (__A__) draw_padded_text(xbgmtextsUpperOrigArtist[tempsong & 0xFF], xbgmtextsUpperOrigArtistSize[tempsong], 14, NTADR_A(9, 13));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 13));

	tmp5 = 1;
}	

void update_text3() {
	__A__ = idx16_load_hi_NOC(xbgmtextsUpper, tempsong);
	if (__A__) draw_padded_text(xbgmtextsUpper[tempsong & 0xFF], xbgmtextsUpperSize[tempsong], 14, NTADR_A(9, 7));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
	__A__ = idx16_load_hi_NOC(xbgmtextsLower, tempsong);
	if (__A__) draw_padded_text(xbgmtextsLower[tempsong & 0xFF], xbgmtextsLowerSize[tempsong], 14, NTADR_A(9, 8));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
}
void update_text2() {
	if (music_queue[0] != 0xFF) one_vram_buffer(0x9F, NTADR_A(1, 13));
	else one_vram_buffer(0xFF, NTADR_A(1, 13));
	for (tmp1 = 0; tmp1 < 2; tmp1++) {			//limited to 5??
		if (music_queue[tmp1] != 0xFF) {
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			text_stuff();
		}
		else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
	}	
	//ppu_on_all();
	tmp4 = 2;
}	

void play_next_queue() {
			tmp1 = 0;

			for (tmp1 = 0; tmp1 < MAX_SONG_QUEUE_SIZE; tmp1++) {		
				tmp2 = tmp1 + 1;
				music_queue[tmp1] = music_queue[tmp2];
			}

			music_queue[MAX_SONG_QUEUE_SIZE] = 0xFF;

			if (music_queue[0] != 0xFF) { music_play(xbgmlookuptable[music_queue[0]]); }
			else { famistudio_music_stop(); songplaying = 0; }
				
			//refresh_queue_screen();
			tmp4 = 0xFF;
}			


void check_if_music_stopped() {
	if (!queuemode) {
		if (songplaying && famistudio_song_speed == 0x80) { music_play(xbgmlookuptable[song]); }
	}
	else {
		if (famistudio_song_speed == 0x80) {

			play_next_queue();

		}
	}
}	


void text_stuff() {
				tmp3 = music_queue[tmp1];
				__A__ = idx16_load_hi_NOC(xbgmtextsUpper, tmp3);
				if (__A__) { 
					multi_vram_buffer_horz(xbgmtextsUpper[tmp3 & 0x7F], xbgmtextsUpperSize[tmp3], NTADR_A(3, (13 + (tmp1))));
					__A__ = idx16_load_hi_NOC(xbgmtextsLower, tmp3);
					multi_vram_buffer_horz(xbgmtextsLower[tmp3 & 0x7F], xbgmtextsLowerSize[tmp3], NTADR_A((4 + xbgmtextsUpperSize[tmp3]), (13 + (tmp1))));
				}
				else {
					__A__ = idx16_load_hi_NOC(xbgmtextsLower, tmp3);
					multi_vram_buffer_horz(xbgmtextsLower[tmp3 & 0x7F], xbgmtextsLowerSize[tmp3], NTADR_A(3, (13 + (tmp1))));
					one_vram_buffer_horz_repeat('$', 7, NTADR_A((3 + xbgmtextsLowerSize[tmp3]), (13 + (tmp1))));

				}	
}				
