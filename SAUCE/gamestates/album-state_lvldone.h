
CODE_BANK_PUSH("XCD_BANK_04")
void lvl_done_update();
void mouse_and_cursor();
void refresh_queue_screen();
void text_stuff();
void play_next_queue();
void update_text1();
void update_text2();
void update_text3();
void unrle_bgm1();
void unrle_bgm2();

const unsigned char palette_Credits2[16]={ 0x11,0x0f,0x10,0x30,0x11,0x0f,0x2a,0x39,0x11,0x28,0x17,0x0f,0x11,0x0f,0x11,0x21 };

const unsigned char blanktext2[] = "$$$$$$$$$$$$$";

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

void state_playmain() {
	
}

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

#include "defines/bgm_charmap.h"
#include "music_soundTextTables.h"
#include "sfx_soundTextTables.h"

//CODE_BANK_PUSH("XCD_BANK_05")

const unsigned char bgmtestscreen[];
const unsigned char SoundQueue[];


#include "defines/bgm_charmap.h"
void bgmtest() {
	song = 0;
	temptemp6 = 0; 	
	#define sfx tmp4
	sfx = 0;
	settingvalue = 0;
  	famistudio_music_stop();
  	music_update();
	menuMusicCurrentlyPlaying=0;
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	ppu_off();
	pal_bg(paletteMenu);
	crossPRGBankJump0(unrle_bgm1); 	
	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	update_text1();
	while (1) {
		//rand8();
		ppu_wait_nmi();
		music_update();
		oam_clear();
		check_if_music_stopped();
		mouse_and_cursor();
		 // read the first controller
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
		if (tmp4) refresh_queue_screen();
		if (tmp5) {
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist1, song);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist1[song & 0x7F], xbgmtextsCoveringArtist1Size[song], 14, NTADR_A(9, 19));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 19));
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist2, song);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist2[song & 0x7F], xbgmtextsCoveringArtist2Size[song], 14, NTADR_A(9, 20));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 20));
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist3, song);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist3[song & 0x7F], xbgmtextsCoveringArtist3Size[song], 14, NTADR_A(9, 21));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 21));
			__A__ = idx16_load_hi_NOC(xbgmtextsCoveringArtist4, song);
			if (__A__) draw_padded_text(xbgmtextsCoveringArtist4[song & 0x7F], xbgmtextsCoveringArtist4Size[song], 14, NTADR_A(9, 22));
			else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 22));
			tmp5 = 0;
		}
/*
		if (mouse.left_press) {
			if ((mouse.x >= 0x63 && mouse.x <= 0x8C)) {
				if (mouse.y >= 0x34 && mouse.y <= 0x3A) {		
					settingvalue = 0;
				}
				else if ((mouse.y >= 0x6C && mouse.y <= 0x73)) {		
					settingvalue = 1;
				}
			}
			if ((mouse.x >= 0x2E && mouse.x <= 0xCC)) {
				if ((mouse.y >= 0xB4 && mouse.y <= 0xBB)) {		
					if (settingvalue == 1) { sfx_play(sfx, 0); }
					else {
						if (!temptemp6) { music_play(xbgm_lookup_table2[song]); temptemp6 = 1; songplaying = 1; }
						else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
					}
				}
				if ((mouse.y >= 0xA4 && mouse.y <= 0xAB)) {
					menu_music = song; sfx_play(sfx_orbs, 0);
				}
			}
			if ((mouse.x >= 0x56 && mouse.x <= 0xA5) && (mouse.y >= 0x24 && mouse.y <= 0x2B)) {		
//				code_checker();
				if (gameState == 0xF0) return;
			}

			if ((mouse.x >= 0x35 && mouse.x <= 0xC4)) {
				if (mouse.y >= 0xC4 && mouse.y <= 0xCD) {		
					tmp3--;			
					one_vram_buffer(' ', NTADR_A(11, 7));
					one_vram_buffer(' ', NTADR_A(11, 14));
					menuMusicCurrentlyPlaying = 1;
					gameState = 1;
					return;
				}
				else if (mouse.y >= 0x3D && mouse.y <= 0x64) {
					if (!temptemp6) { music_play(xbgm_lookup_table2[song]); temptemp6 = 1; songplaying = 1; }
					else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
				}
				else if (mouse.y >= 0x75 && mouse.y <= 0x9C) {
					sfx_play(sfx, 0);
				}
			}
		}			
	*/

	if (joypad1.press_right || joypad1.press_left) hold_timer = 0;
	if (joypad1.press_right || (joypad1.right && hold_timer >= 15)) { song++; temptemp6 = 0; if (song == song_max) {song = 0;} if (!queuemode) update_text1(); else update_text3(); hold_timer = 0;}
	if (joypad1.press_left || (joypad1.left && hold_timer >= 15)) { if (song == 0) {song = song_max - 1;} else song--; temptemp6 = 0; if (!queuemode) update_text1(); else update_text3();  hold_timer = 0;}

	if (!queuemode) {		//not queue mode
		if (joypad1.press_b) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			menuMusicCurrentlyPlaying = 1;
			gameState = 1;
			return;
		}
		if (joypad1.press_a) {
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
				music_play(xbgmlookuptable[song]); 
				music_queue[0] = song;
				update_text2();
			}
			else {
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
					multi_vram_buffer_horz(xbgmtextsUpperSize[tmp3 & 0x7F], xbgmtextsUpperSize[tmp3], NTADR_A(3, (13 + (tmp1))));
					__A__ = idx16_load_hi_NOC(xbgmtextsLowerSize, tmp3);
					multi_vram_buffer_horz(xbgmtextsLower[tmp3 & 0x7F], xbgmtextsLowerSize[tmp3], NTADR_A((4 + xbgmtextsUpperSize[tmp3]), (13 + (tmp1))));
				}
				else {
					__A__ = idx16_load_hi_NOC(xbgmtextsLower, tmp3);
					multi_vram_buffer_horz(xbgmtextsLower[tmp3 & 0x7F], xbgmtextsLowerSize[tmp3], NTADR_A(3, (13 + (tmp1))));
					multi_vram_buffer_horz(blanktext2, 7, NTADR_A((3 + xbgmtextsLowerSize[tmp3]), (13 + (tmp1))));

				}				
			}
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
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


#include "defines/bgm_charmap.h"


const unsigned char gameboytext1[]="  GREY";
const unsigned char gameboytext2[]="   RED";
const unsigned char gameboytext3[]=" GREEN";
const unsigned char gameboytext4[]="  BLUE";
const unsigned char gameboytext5[]="YELLOW";
const unsigned char gameboytext6[]="PURPLE";
const unsigned char gameboytext7[]="  CYAN";
const unsigned char gameboytext8[]="  DARK";

const unsigned char* const gameboytexts[] = {
	0, gameboytext1, gameboytext2, gameboytext3, gameboytext4, gameboytext5, gameboytext6, gameboytext7, gameboytext8
};

const unsigned char gameboy_text_size[] = {
	0,
	sizeof(gameboytext1) - 1,
	sizeof(gameboytext2) - 1,
	sizeof(gameboytext3) - 1,
	sizeof(gameboytext4) - 1,
	sizeof(gameboytext5) - 1,
	sizeof(gameboytext6) - 1,
	sizeof(gameboytext7) - 1,
	sizeof(gameboytext8) - 1
};



void funsettings() {

}

void set_fun_settings() {

}	







#include "defines/bgm_charmap.h"

/*
	Refreshes level name & number
*/
void refreshmenu() {

};

void refreshmenu_part2() {

}

#include "defines/bgm_charmap.h"
void lvl_done_update() {

}	


#define BAR_TILES 20
#define CENTER_TILES BAR_TILES - 2
#define BAR_MAX 100
#define NUMBER_PER_TILES BAR_MAX / BAR_TILES
void draw_progress_bar() {

}

#define TOTAL_PIXELS 8 * BAR_TILES // 8 * 20 = 160
#define PIXELS_PER_UNIT (TOTAL_PIXELS * 10) / (BAR_MAX) // (1600 / 100) = 1.6 | multiplied by 10 because of no floats
#define PIXELS_PER_PERCENTAGE (PIXELS_PER_UNIT * 256) / 10 // 1.6 * 256 = 409.6

void calculate_sprite_pos() {

}


void update_text1() {
	__A__ = idx16_load_hi_NOC(xbgmtextsUpper, song);
	if (__A__) draw_padded_text(xbgmtextsUpper[song & 0x7F], xbgmtextsUpperSize[song], 14, NTADR_A(9, 7));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
	__A__ = idx16_load_hi_NOC(xbgmtextsLower, song);
	if (__A__) draw_padded_text(xbgmtextsLower[song & 0x7F], xbgmtextsLowerSize[song], 14, NTADR_A(9, 8));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
	
	__A__ = idx16_load_hi_NOC(xbgmtextsOrigArtistLower, song);
	if (__A__) draw_padded_text(xbgmtextsOrigArtistLower[song & 0x7F], xbgmtextsOrigArtistLowerSize[song], 14, NTADR_A(9, 14));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 14));
	__A__ = idx16_load_hi_NOC(xbgmtextsOrigArtistUpper, song);
	if (__A__) draw_padded_text(xbgmtextsOrigArtistUpper[song & 0x7F], xbgmtextsOrigArtistUpperSize[song], 14, NTADR_A(9, 13));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 13));

	tmp5 = 1;
}	

void update_text3() {
	__A__ = idx16_load_hi_NOC(xbgmtextsUpper, song);
	if (__A__) draw_padded_text(xbgmtextsUpper[song & 0x7F], xbgmtextsUpperSize[song], 14, NTADR_A(9, 7));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
	__A__ = idx16_load_hi_NOC(xbgmtextsLower, song);
	if (__A__) draw_padded_text(xbgmtextsLower[song & 0x7F], xbgmtextsLowerSize[song], 14, NTADR_A(9, 8));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
}
void update_text2() {
	//ppu_off();
//	__A__ = idx16_load_hi_NOC(xbgmtexts1, song);
//	if (__A__) draw_padded_text(xbgmtexts1[song & 0x7F], xbgmtext1_size[song], 14, NTADR_A(9, 7));
//	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
//	__A__ = idx16_load_hi_NOC(xbgmtexts2, song);
//	if (__A__) draw_padded_text(xbgmtexts2[song & 0x7F], xbgmtext2_size[song], 14, NTADR_A(9, 8));
//	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
	
//	one_vram_buffer(0xB0, NTADR_A(5,13)); // 0
//	one_vram_buffer(0xB1, NTADR_A(5,14)); // 1
//	one_vram_buffer(0xB2, NTADR_A(5,15)); // 2
//	one_vram_buffer(0xB3, NTADR_A(5,16)); // 3
//	one_vram_buffer(0xB4, NTADR_A(5,17)); // 4
//	one_vram_buffer(0xB5, NTADR_A(5,18)); // 5
//	one_vram_buffer(0xB6, NTADR_A(5,19)); // 6
//	one_vram_buffer(0xB7, NTADR_A(5,20)); // 7
//	one_vram_buffer(0xB8, NTADR_A(5,21)); // 8
//	one_vram_buffer(0xB9, NTADR_A(5,22)); // 9
	
//	for (tmp1 = 0; tmp1 < 10; tmp1++) {
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
					multi_vram_buffer_horz(blanktext2, 7, NTADR_A((3 + xbgmtextsLowerSize[tmp3]), (13 + (tmp1))));

				}	
}				

CODE_BANK_POP()

