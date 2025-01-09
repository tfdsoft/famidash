
CODE_BANK_PUSH("LVL_BANK_00")
void lvl_done_update();
void mouse_and_cursor();

const uint8_t difficulty_pal_A[] ={
	0x21,	// easy
	0x2A,	// normal
	0x28,	// hard
	0x16,	// harder
	0x24,	// insane
	0x16,	// demon
	0x13,	// danger
};

const uint8_t difficulty_pal_B[] ={
	0x06,	// easy
	0x30,	// normal
	0x30,	// hard
	0x30,	// harder
	0x06,	// insane
	0x30,	// demon
	0x21,	// danger
};

void refreshmenu();
void refreshmenu_part2();
void code_checker();
void check_if_music_stopped();
void set_fun_settings();
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
	oam_clear();
    ppu_off();

	delay_spr_0 = 0x20;

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

	#include "defines/endlevel_charmap.h"
	//multi_vram_buffer_horz((const char*)menutext3,sizeof(menutext3)-1,NTADR_C(6, 16));
	//multi_vram_buffer_horz((const char*)menutext4,sizeof(menutext4)-1,NTADR_C(8, 18));
	//multi_vram_buffer_horz((const char*)attemptstext,sizeof(attemptstext)-1,NTADR_C(7, 19));
	
	tmp1 = 0;
	tmpptr1 = NULL;
	//crossPRGBankJump0(increment_attempt_count); WTF WHO PUT THIS HERE
	display_attempt_counter(0xD0, NTADR_A(20, 13));	// Same bank as this
	
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

    set_scroll_x(0x00);


	tmp5 = 0x0000; // speed
	tmp6 = 0xf000; // real y 

	//	one_vram_buffer(0xD0+coins, NTADR_A(12,9));

	
    set_scroll_y(0xe8);
    ppu_on_all();

	sfx_play(sfx_level_complete, 0);
	menuselection = 1;
	practice_point_count = 0;

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
						gameState = 2;
						pal_fade_to_withmusic(4,0);
						memfill(attemptCounter, 0, sizeof(attemptCounter));

						//oam_clear();
						coins = 0;
						return;					
					}
					if (mouse.x >= 0xA6 && mouse.x <= 0xc3) {
						sfx_play(sfx_exit_level, 0);
						music_update();
						gameState = 1;
						menuselection = 0;
						kandowatchesyousleep = 1;
						//oam_clear();
						menuMusicCurrentlyPlaying = 0;
						return;
					}
				}
			}

			if (joypad1.press_left) { menuselection ^= 1; lvl_done_update(); }
			if (joypad1.press_right) { menuselection ^= 1; lvl_done_update(); }
			if (joypad1.press_start || joypad1.press_a){
				if (menuselection) {
					
					sfx_play(sfx_exit_level, 0);
					music_update();
					gameState = 1;
					menuselection = 0;
					kandowatchesyousleep = 1;

					//oam_clear();
					menuMusicCurrentlyPlaying = 0;
					return;
				} else {
					
					sfx_play(sfx_start_level, 0);
					gameState = 2;
					pal_fade_to_withmusic(4,0);
					memfill(attemptCounter, 0, sizeof(attemptCounter));
					coins = 0;


					//oam_clear();
					return;
				}
			}



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



CODE_BANK_PUSH("XCD_BANK_05")

const unsigned char bgmtestscreen[];

#include "defines/bgm_charmap.h"
const unsigned char TEXT_xlevel1text1[]="STEREO$";
const unsigned char TEXT_xlevel1text2[]="BACK$ON";
const unsigned char TEXT_xlevel1text5[]="BASE$AFTER";
const unsigned char TEXT_xlevel1textC[]="THEORY$OF";
const unsigned char TEXT_xlevel1textD[]="ELECTROMAN";
const unsigned char TEXT_xweasel[]="SCHEMING";
const unsigned char TEXT_challenge[]="THE";
const unsigned char TEXT_hexagon[]="HEXAGON";
const unsigned char TEXT_blast[]="BLAST";
const unsigned char TEXT_speed[]="AT$THE$SPEED";
const unsigned char TEXT_crackdown[]="OKIBA";
const unsigned char TEXT_against[]="8$BIT$AGAINST";


const unsigned char TEXT_xlevel2text1[]="MADNESS";
const unsigned char TEXT_xlevel2text2[]="TRACK";
const unsigned char TEXT_xlevel2text3[]="POLARGEIST";
const unsigned char TEXT_xlevel2text4[]="DRY$OUT";
const unsigned char TEXT_xlevel2text5[]="BASE";
const unsigned char TEXT_xlevel2text6[]="CANT$LET$GO";
const unsigned char TEXT_xlevel2text7[]="JUMPER";
const unsigned char TEXT_xlevel2text8[]="TIME$MACHINE";
const unsigned char TEXT_xlevel2text9[]="CYCLES";
const unsigned char TEXT_xlevel2textA[]="XSTEP";
const unsigned char TEXT_xlevel2textB[]="CLUTTERFUNK";
const unsigned char TEXT_xlevel2textC[]="EVERYTHING";
const unsigned char TEXT_xlevel22textC[]="EVERYTHING$2";
const unsigned char TEXT_xlevel2textD[]="ADVENTURES";
const unsigned char TEXT_xlevel2textE[]="DECODE";
const unsigned char TEXT_2texteveryend[]="EVERY$END";
const unsigned char TEXT_2texteon[]="EON";
const unsigned char TEXT_2textelectrodynamix[]="ELECTRODYNAMIX";
const unsigned char TEXT_2textmidnight[]="MIDNIGHT";
const unsigned char TEXT_2textclubstep[]="CLUBSTEP";
const unsigned char TEXT_2textpractice[]="PRACTICE";
const unsigned char TEXT_2textmenu[]="MENU";
const unsigned char TEXT_2textweasel[]="WEASEL";
const unsigned char TEXT_2challenge[]="CHALLENGE";
const unsigned char TEXT_2deathmoon[]="DEATH$MOON";
const unsigned char TEXT_2hexagon[]="FORCE";
const unsigned char TEXT_2blast[]="PROCESSING";
const unsigned char TEXT_2textretray[]="RETRAY";
const unsigned char TEXT_2textstereo[]="MADNESS$2";
const unsigned char TEXT_2textinfernoplex[]="INFERNOPLEX";
const unsigned char TEXT_2textproblematic[]="PROBLEMATIC";
const unsigned char TEXT_2textspeed[]="OF$LIGHT";
const unsigned char TEXT_2textspeed2[]="OF$LIGHT$PT$2";
const unsigned char TEXT_2textcrackdown[]="CRACKDOWN";
const unsigned char TEXT_2textstalemate[]="STALEMATE";
const unsigned char TEXT_2textwoods[]="HAUNTED$WOODS";
const unsigned char TEXT_2textchaoz[]="CHAOZ$FANTASY";
const unsigned char TEXT_2textjustright[]="JUST$RIGHT";
const unsigned char TEXT_against2[]="THE$ODDS$REDUX";

const unsigned char TEXT_sfxtext0[]="DEATH";
const unsigned char TEXT_sfxtext1[]="CLICK";
const unsigned char TEXT_sfxtext2[]="LEVEL$COMPLETE";
const unsigned char TEXT_sfxtext3[]="COIN";
const unsigned char TEXT_sfxtext4[]="CHEST$OPEN";
const unsigned char TEXT_sfxtext5[]="ORBS";
const unsigned char TEXT_sfxtext6[]="DIAMONDS";
const unsigned char TEXT_sfxtext7[]="EXIT$LEVEL";
const unsigned char TEXT_sfxtext8[]="START$LEVEL";
const unsigned char TEXT_sfxtext9[]="INVALID";
const unsigned char TEXT_sfxtextA[]="ACHIEVEMENT$GET";

const unsigned char* const sfxtexts[] = {
	TEXT_sfxtext0, TEXT_sfxtext1, TEXT_sfxtext2, TEXT_sfxtext3, TEXT_sfxtext4, TEXT_sfxtext5, TEXT_sfxtext6, TEXT_sfxtext7, TEXT_sfxtext8, TEXT_sfxtext9, TEXT_sfxtextA
};

const unsigned char sfxtexts_size[] = {
	sizeof(TEXT_sfxtext0) - 1,
	sizeof(TEXT_sfxtext1) - 1,
	sizeof(TEXT_sfxtext2) - 1,
	sizeof(TEXT_sfxtext3) - 1,
	sizeof(TEXT_sfxtext4) - 1,
	sizeof(TEXT_sfxtext5) - 1,
	sizeof(TEXT_sfxtext6) - 1,
	sizeof(TEXT_sfxtext7) - 1,
	sizeof(TEXT_sfxtext8) - 1,
	sizeof(TEXT_sfxtext9) - 1,
	sizeof(TEXT_sfxtextA) - 1
};


const unsigned char* const xbgmtexts1[] = {
	0, 
	TEXT_xlevel1text1, 
	TEXT_xlevel1text2, 
	0, 
	0, 
	TEXT_xlevel1text5, 
	0, 
	0, 
	0, 
	0, 
	0, 
	0, 
	TEXT_xlevel1textC, 
	TEXT_xlevel1textD, 
	0, 
	0, 
	TEXT_hexagon, 
	TEXT_blast, 
	TEXT_xlevel1textC, 
	0, 
	0, 
	0, 
	0, 
	0, 
	TEXT_xlevel1text1, 
	0, 
	0, 
	TEXT_xweasel, 
	TEXT_challenge,
	TEXT_speed,
	TEXT_speed,
	0,
	TEXT_crackdown,
	0,
	0,
	0,
	0,
	TEXT_against,
};

const unsigned char* const xbgmtexts2[] = {
	TEXT_2textmenu, 
	TEXT_xlevel2text1, 
	TEXT_xlevel2text2, 
	TEXT_xlevel2text3, 
	TEXT_xlevel2text4, 
	TEXT_xlevel2text5, 
	TEXT_xlevel2text6,
	TEXT_xlevel2text7, 
	TEXT_xlevel2text8, 
	TEXT_xlevel2text9, 
	TEXT_xlevel2textA, 
	TEXT_xlevel2textB, 
	TEXT_xlevel2textC, 
	TEXT_xlevel2textD, 
	TEXT_2textclubstep, 
	TEXT_2textelectrodynamix, 
	TEXT_2hexagon, 
	TEXT_2blast, 
	TEXT_xlevel22textC, 
	TEXT_xlevel2textE, 
	TEXT_2textpractice, 
	TEXT_2textretray, 
	TEXT_2textinfernoplex,
	TEXT_2textproblematic,
	TEXT_2textstereo,
	TEXT_2texteon, 
	TEXT_2deathmoon, 
	TEXT_2textweasel, 
	TEXT_2challenge,
	TEXT_2textspeed,
	TEXT_2textspeed2,
	TEXT_2textmidnight,
	TEXT_2textcrackdown,
	TEXT_2textstalemate,
	TEXT_2textwoods,
	TEXT_2textchaoz,
	TEXT_2textjustright,
	TEXT_against2,
};

const unsigned char xbgmtext2_size[] = {
	sizeof(TEXT_2textmenu) - 1,
	sizeof(TEXT_xlevel2text1) - 1,	
	sizeof(TEXT_xlevel2text2) - 1,	
	sizeof(TEXT_xlevel2text3) - 1,
	sizeof(TEXT_xlevel2text4) - 1,	
	sizeof(TEXT_xlevel2text5) - 1,	
	sizeof(TEXT_xlevel2text6) - 1,	
	sizeof(TEXT_xlevel2text7) - 1,	
	sizeof(TEXT_xlevel2text8) - 1,
	sizeof(TEXT_xlevel2text9) - 1,	
	sizeof(TEXT_xlevel2textA) - 1,	
	sizeof(TEXT_xlevel2textB) - 1,
	sizeof(TEXT_xlevel2textC) - 1,	
	sizeof(TEXT_xlevel2textD) - 1,	
	sizeof(TEXT_2textclubstep) - 1,
	sizeof(TEXT_2textelectrodynamix) - 1,
	sizeof(TEXT_2hexagon) - 1,
	sizeof(TEXT_2blast) - 1,
	sizeof(TEXT_xlevel22textC) - 1,	
	sizeof(TEXT_xlevel2textE) - 1,
	sizeof(TEXT_2textpractice) - 1,
	sizeof(TEXT_2textretray) - 1,
	sizeof(TEXT_2textinfernoplex) - 1,
	sizeof(TEXT_2textproblematic) - 1,
	sizeof(TEXT_2textstereo) - 1,	
	sizeof(TEXT_2texteon) - 1,
	sizeof(TEXT_2deathmoon) - 1,
	sizeof(TEXT_2textweasel) - 1,
	sizeof(TEXT_2challenge) - 1,
	sizeof(TEXT_2textspeed) - 1,
	sizeof(TEXT_2textspeed2) - 1,
	sizeof(TEXT_2textmidnight) - 1,
	sizeof(TEXT_2textcrackdown) - 1,
	sizeof(TEXT_2textstalemate) - 1,
	sizeof(TEXT_2textwoods) - 1,
	sizeof(TEXT_2textchaoz) - 1,
	sizeof(TEXT_2textjustright) - 1,
	sizeof(TEXT_against2) - 1,
};
const unsigned char xbgmtext1_size[] = {
	0,
	sizeof(TEXT_xlevel1text1) - 1,	
	sizeof(TEXT_xlevel1text2) - 1,	
	0,
	0,
	sizeof(TEXT_xlevel1text5) - 1,	
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(TEXT_xlevel1textC) - 1,	
	sizeof(TEXT_xlevel1textD) - 1,	
	0,
	0,
	sizeof(TEXT_hexagon) - 1,	
	sizeof(TEXT_blast) - 1,	
	sizeof(TEXT_xlevel1textC) - 1,	
	0,
	0,
	0,
	0,
	0,
	sizeof(TEXT_xlevel1text1) - 1,	
	0,
	0,
	sizeof(TEXT_xweasel) - 1,	
	sizeof(TEXT_challenge) - 1,	
	sizeof(TEXT_speed) - 1,	
	sizeof(TEXT_speed) - 1,	
	0,
	sizeof(TEXT_crackdown) - 1,	
	0,
	0,
	0,
	0,
	sizeof(TEXT_against) - 1,	
};


const uint8_t xbgm_lookup_table2[] = {
	song_menu_theme,
	song_stereo_madness,
	song_back_on_track,
	song_polargeist,
	song_dry_out,
	song_base_after_base,
	song_cant_let_go,
	song_jumper,
	song_time_machine,
	song_cycles,
	song_xstep, 
	song_clutterfunk,
	song_theory_of_everything, 
	song_electroman_adventures, 
	song_clubstep,
	song_electrodynamix,
	song_hexagon_force,
	song_blast_processing,
	song_toe_2,
	song_endgame, 
	song_practice,
	song_retray,
	song_infernoplex,
	song_problematic,
	song_stereo_madness_2,
	song_eon,
	song_death_moon,
	song_scheming_weasel,
	song_the_challenge,
	song_atthespeedoflight,
	song_atthespeedoflight2,
	song_midnight,
	song_crackdown,
	song_stalemate,
	song_haunted_woods,
	song_chaozfantasy,
	song_just_right,
	song_against_the_odds_redux,
};



const char TEXT_debug_mode[] = "DEBUG MODE ENABLED";

//#include "defines/bgm_charmap.h"
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
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);   	
	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	while (1) {
		
		ppu_wait_nmi();
		music_update();
		oam_clear();
		crossPRGBankJump0(check_if_music_stopped);
		mouse_and_cursor();
		 // read the first controller
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
		if (mouse.left_press) {
			if ((mouse.x >= 0x63 && mouse.x <= 0x8C)) {
				if (mouse.y >= 0x34 && mouse.y <= 0x3A) {		
					settingvalue = 0;
				}
				else if ((mouse.y >= 0x6C && mouse.y <= 0x73)) {		
					settingvalue = 1;
				}
			}
			if ((mouse.x >= 0x2E && mouse.x <= 0xCC) && (mouse.y >= 0xAC && mouse.y <= 0xB3)) {		
				if (settingvalue == 1) { sfx_play(sfx, 0); }
				else {
					if (!temptemp6) { music_play(xbgm_lookup_table2[song]); temptemp6 = 1; songplaying = 1; }
					else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
				}
			}
			if ((mouse.x >= 0x56 && mouse.x <= 0xA5) && (mouse.y >= 0x24 && mouse.y <= 0x2B)) {		
				code_checker();
				if (gameState == 0xF0) return;
			}
			if ((mouse.y >= 0x4E && mouse.y <= 0x5C)) {
				if ((mouse.x >= 0x24 && mouse.x <= 0x2C)) {		
					if (song == 0) {song = song_max - 1;} else song--; temptemp6 = 0; settingvalue = 0;
				}
				else if ((mouse.x >= 0xCC && mouse.x <= 0xD4)) {		
					temptemp6 = 0; song++; if (song == song_max) {song = 0;} settingvalue = 0;
				}
			}
			if ((mouse.y >= 0x86 && mouse.y <= 0x93)) {

				if ((mouse.x >= 0x24 && mouse.x <= 0x2C)) {		
					if (sfx == 0) {sfx = sfx_max - 1;} else sfx--; settingvalue = 1;
				}
				else if ((mouse.x >= 0xCC && mouse.x <= 0xD4)) {		
					sfx++; if (sfx == sfx_max) {sfx= 0;} settingvalue = 1;
				}
			}
			if ((mouse.x >= 0x35 && mouse.x <= 0xC4)) {
				if (mouse.y >= 0xBC && mouse.y <= 0xC4) {		
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
	__A__ = idx16_load_hi_NOC(xbgmtexts1, song);
	if (__A__) draw_padded_text(xbgmtexts1[song & 0x7F], xbgmtext1_size[song], 18, NTADR_A(7, 10));
	else one_vram_buffer_horz_repeat('$', 17, NTADR_A(7, 10));
	__A__ = idx16_load_hi_NOC(xbgmtexts2, song);
	if (__A__) draw_padded_text(xbgmtexts2[song & 0x7F], xbgmtext2_size[song], 18, NTADR_A(7, 11));
	else one_vram_buffer_horz_repeat('$', 17, NTADR_A(7, 11));
	
	draw_padded_text(sfxtexts[sfx & 0x7F], sfxtexts_size[sfx], 18, NTADR_A(7, 18));

	
		if (settingvalue == 0) {
			one_vram_buffer('c', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			if (joypad1.press_right) { song++; temptemp6 = 0; if (song == song_max) {song = 0;} }
			if (joypad1.press_left) { if (song == 0) {song = song_max - 1;} else song--; temptemp6 = 0; }
			if (joypad1.press_a) {
					if (!temptemp6) { music_play(xbgm_lookup_table2[song]); temptemp6 = 1; songplaying = 1; }
					else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
			}					
		}		
		else if (settingvalue == 1) {
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer('c', NTADR_A(11, 14));
			if (joypad1.press_right) { sfx++; if (sfx == sfx_max) {sfx= 0;} };
			if (joypad1.press_left) { if (sfx == 0) {sfx = sfx_max - 1;} else sfx--; }
			if (joypad1.press_a) sfx_play(sfx, 0);
		}

		if (joypad1.press_down) settingvalue ^= 1;
		if (joypad1.press_up) settingvalue ^= 1;
		
		if (joypad1.press_select) menu_music = song;
		if (joypad1.press_b) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			menuMusicCurrentlyPlaying = 1;
			gameState = 1;
			return;
		}

				
		
		// sound test codes
		if (joypad1.press_start) {
			code_checker();
			if (gameState == 0xF0) return;
		}
	}
}
#define sfx tmp4
void code_checker() {
	last_gameState = gameState;
	sfx_play(sfx_achievement_get, 0);
	tmp3 = 1;

	// bgm 9 & sfx 2
	if (song == 0x9 && sfx == 0x2 && kandokidshack3 == 0) {
		kandokidshack3++;
		tmp3--;
	}
	
	else if (song == 1 && sfx == 7 && kandokidshack3 == 1) {
		all_levels_complete = 0xFC;
		gameState = 0xF0; // fun settings gamestate
		tmp3--;
	}		
	else kandokidshack3 = 0;
	
/*   debug code disabled
	if (song == 0xB && sfx == 0x7) {
		multi_vram_buffer_horz(TEXT_debug_mode, sizeof(TEXT_debug_mode)-1, NTADR_A(7,26));
		options |= debugtoggle;
		tmp3--;
	}
*/

	// this is quite literally the greatest hack ever
	// since sfx doesn't update until the next frame i can just
	// overwrite the success sfx with the invalid one
	if (tmp3) sfx_play(sfx_invalid, 0);	
}

#undef sfx


const unsigned char bgmtestscreen[463]={
0x01,0x02,0x01,0x04,0xae,0x02,0x01,0x13,0xae,0x02,0x01,0x09,0xaf,0x02,0x01,0x13,
0xaf,0x02,0x01,0x06,0x06,0x07,0x04,0x01,0x17,0x06,0x07,0x02,0x01,0x03,0x08,0x09,
0x05,0x01,0x17,0x08,0x09,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,0x0d,0x02,0x01,0x03,
0x0c,0xff,0x01,0x07,0xf3,0xef,0xf5,0xee,0xe4,0xff,0xf4,0xe5,0xf3,0xf4,0xff,0x01,
0x07,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,
0x09,0xed,0xf5,0xf3,0xe9,0xe3,0xff,0x01,0x0a,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,
0x03,0x5c,0xfe,0x01,0x0f,0x5d,0xff,0x01,0x03,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,
0x03,0xfe,0x01,0x11,0xff,0x01,0x03,0x0d,0x02,0x01,0x03,0x0c,0xff,0xff,0x6e,0xff,
0xfe,0x01,0x11,0xff,0x6f,0xff,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0xff,0x7e,0xff,
0xfe,0x01,0x11,0xff,0x7f,0xff,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x03,0x6c,
0xfe,0x01,0x0f,0x6d,0xff,0x01,0x03,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,0x0d,
0x02,0x01,0x03,0x0c,0xff,0x01,0x09,0xf3,0xef,0xf5,0xee,0xe4,0xff,0x01,0x0a,0x0d,
0x02,0x01,0x03,0x0c,0xff,0x01,0x03,0x5c,0xfe,0x01,0x0f,0x5d,0xff,0x01,0x03,0x0d,
0x02,0x01,0x03,0x0c,0xff,0x01,0x03,0xfe,0x01,0x11,0xff,0x01,0x03,0x0d,0x02,0x01,
0x03,0x0c,0xff,0xff,0x6e,0xff,0xfe,0x01,0x11,0xff,0x6f,0xff,0xff,0x0d,0x02,0x01,
0x03,0x0c,0xff,0xff,0x7e,0xff,0xfe,0x01,0x11,0xff,0x7f,0xff,0xff,0x0d,0x02,0x01,
0x03,0x0c,0xff,0x01,0x03,0x6c,0xfe,0x01,0x0f,0x6d,0xff,0x01,0x03,0x0d,0x02,0x01,
0x03,0x0c,0xff,0x01,0x19,0x0d,0x02,0x01,0x03,0x0c,0xff,0xff,0xf3,0xe5,0xec,0xe5,
0xe3,0xf4,0xe0,0xf3,0xe5,0xf4,0xff,0xed,0xe5,0xee,0xf5,0xff,0xed,0xf5,0xf3,0xe9,
0xe3,0xff,0x01,0x02,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,0x0d,0x02,0x01,0x03,
0x0c,0xff,0xff,0xf0,0xf2,0xe5,0xf3,0xf3,0xff,0xe1,0xff,0xf4,0xef,0xff,0xf0,0xec,
0xe1,0xf9,0xff,0xe0,0xff,0xf3,0xf4,0xef,0xf0,0xff,0xff,0x0d,0x02,0x01,0x03,0x0c,
0xff,0x01,0x19,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x03,0xf0,0xf2,0xe5,0xf3,0xf3,
0xff,0xe2,0xff,0xf4,0xef,0xff,0xf2,0xe5,0xf4,0xf5,0xf2,0xee,0xff,0x01,0x04,0x0d,
0x02,0x01,0x03,0x0a,0x0b,0x04,0x01,0x09,0x06,0x0e,0x0e,0x07,0x04,0x01,0x09,0x0a,
0x0b,0x02,0x01,0x05,0x05,0x01,0x09,0x08,0x05,0x05,0x09,0x05,0x01,0x09,0x02,0x01,
0x43,0xff,0x5c,0x5f,0x01,0x03,0x53,0xff,0x77,0x00,0x01,0x05,0xdd,0x77,0x00,0x01,
0x05,0xdd,0x77,0x00,0x01,0x05,0xdd,0x77,0x00,0x01,0x05,0xdd,0x77,0x00,0x01,0x05,
0xdd,0xf7,0x50,0x50,0xd0,0x70,0x50,0x50,0xfd,0x0f,0x01,0x06,0x0f,0x01,0x00
};



CODE_BANK_POP()


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


#include "defines/mainmenu_charmap.h"


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
	settingvalue = 0; 
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(funsettingscreen);   
	//kandotemp4 = 0;
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	ppu_on_all();
	one_vram_buffer('c', NTADR_A(4, 7));	// settingvalue is set to 0 by default	
	pal_fade_to_withmusic(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		oam_clear();
		crossPRGBankJump0(check_if_music_stopped);
		mouse_and_cursor();
		 // read the first controller
		if (mouse.left_press) {
			if (mouse.x >= 0x2D && mouse.x <= 0xDD) {
				if (mouse.y >= 0x34 && mouse.y <= 0x3C) {
					settingvalue = 0; set_fun_settings();
				}
				else if (mouse.y >= 0x44 && mouse.y <= 0x4C) {
					settingvalue = 1; set_fun_settings();
				}
				else if (mouse.y >= 0x54 && mouse.y <= 0x5C) {
					settingvalue = 2; set_fun_settings();
				}
				else if (mouse.y >= 0x64 && mouse.y <= 0x6C) {
					settingvalue = 3; set_fun_settings();
				}
				else if (mouse.y >= 0x74 && mouse.y <= 0x7C) {
					settingvalue = 4; set_fun_settings();
				}
				else if (mouse.y >= 0x84 && mouse.y <= 0x8C) {
					settingvalue = 5; set_fun_settings();
				}
				else if (mouse.y >= 0x94 && mouse.y <= 0x9C) {
					settingvalue = 6; set_fun_settings();
				}
				else if (mouse.y >= 0xA4 && mouse.y <= 0xAC) {
					settingvalue = 7; set_fun_settings();
				}

			}
			if ((mouse.x >= 0x1D && mouse.x <= 0xDD) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				gameState = last_gameState;
				return;
			}

		}	
		if (invisible) 	one_vram_buffer('g', NTADR_A(26, 7));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 7));	// this is auto optimized by cc65

		if ((options & platformer)) 	one_vram_buffer('g', NTADR_A(26, 9));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 9));	// this is auto optimized by cc65

		if (retro_mode) 	one_vram_buffer('g', NTADR_A(26, 11));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 11));	// this is auto optimized by cc65

		if (discomode) 	one_vram_buffer('g', NTADR_A(26, 13));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 13));	// this is auto optimized by cc65
		
		if (invisblocks) 	one_vram_buffer('g', NTADR_A(26, 15));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 15));	// this is auto optimized by cc65
		
		if (cam_seesaw) 	one_vram_buffer('g', NTADR_A(26, 17));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 17));	// this is auto optimized by cc65

		if (cursedmusic & 0x40) 	one_vram_buffer('g', NTADR_A(26, 21));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 21));	// this is auto optimized by cc65
		


//		if (cursedmusic) 	one_vram_buffer('g', NTADR_A(26, 21));	// believe it or not, 
//		else 	one_vram_buffer('f', NTADR_A(26, 21));	// this is auto optimized by cc65
		
		__A__ = idx16_load_hi_NOC(gameboytexts, gameboy_mode);
		if (__A__) { draw_padded_text(gameboytexts[gameboy_mode & 0x7F], gameboy_text_size[gameboy_mode], 8, NTADR_A(19, 19)); 	one_vram_buffer('g', NTADR_A(26, 19));	}// believe it or not, 
		else { one_vram_buffer_horz_repeat('$', 8, NTADR_A(19, 19)); one_vram_buffer('f', NTADR_A(26, 19)); }



		tmp1 = settingvalue;

		if (joypad1.press & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 7) { settingvalue = 0; }
			else { settingvalue++;  }
		}

		if (joypad1.press & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 7; }
			else { settingvalue--;  }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, 7)+((tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, 7)+((settingvalue<<8)>>2));
		}

		one_vram_buffer('X'-0x1B, NTADR_A(26, 13));
		if (discomode & 0x02) { one_vram_buffer('2' - 0x20, NTADR_A(25, 13)); }
		else if (discomode & 0x04) { one_vram_buffer('3' - 0x20, NTADR_A(25, 13));}
		else if (discomode & 0x08) { one_vram_buffer('4' - 0x20, NTADR_A(25, 13));}
		else if (discomode & 0x10) { one_vram_buffer('5' - 0x20, NTADR_A(25, 13));}
		else if (discomode & 0x01) { one_vram_buffer('1' - 0x20, NTADR_A(25, 13));}
		else { one_vram_buffer(' '-0x01, NTADR_A(25, 13)); one_vram_buffer(0x0F, NTADR_A(26, 13)); }

		if (joypad1.press & (PAD_START | PAD_A)) {
			set_fun_settings();
		}
			
		if (joypad1.press_b) {
			gameState = last_gameState;
			return;
		}

		crossPRGBankJump0(gameboy_check);

//		if (gameboy_mode) kandotemp4 = 1;
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
						
	}
}

void set_fun_settings() {
	switch (settingvalue) {
		case 0x00: invisible ^= 1; break;
		case 0x01: options ^= platformer; break;
		case 0x02: retro_mode ^= 1; break;
		case 0x03: 
			if (discomode & 0x10) discomode = 0;
			else {
				discomode = discomode << 1;
				if (discomode == 0) ++discomode;
			}
			
			break;
		case 0x04: invisblocks ^= 1; break;
		case 0x05: cam_seesaw = (cam_seesaw > 0 ? 0 : 1); break;
		case 0x06: gameboy_mode = (gameboy_mode == 8 ? 0 : gameboy_mode + 1); break;
		case 0x07: cursedmusic ^= 0x40; break;
	};
}	






const unsigned char* const leveltexts[] = {
  level1text, 
  level2text, 
  NULL, 
  NULL, 
  level5text, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  levelCtext, 
  levelDtext, 
  NULL, 
  NULL, 
  levelhexagontext, 
  levelblasttext, 
  levelCtext, 
  NULL,
  NULL, 
  levelchallengetext, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  levelwoodstext,
  levelbloodbath2,
  levelprettyeasytext,
  level16text, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
//  NULL, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  NULL, 
  NULL,  
  NULL,  
  NULL,  
  NULL,  
  NULL,  
  NULL
};
const unsigned char* const leveltexts2[] = {
  level1text2, 
  level2text2, 
  level3text2, 
  level4text2, 
  level5text2, 
  level6text2, 
  level7text2, 
  level8text2, 
  level9text2, 
  levelAtext2, 
  levelBtext2, 
  levelCtext2, 
  levelDtext2, 
  levelclubtext2,
  levelelectrodynamix2,
  levelhexagon2, 
  levelblast2, 
  levelCtext22, 
  levelretray2,
  levelsonar2,
  levelchallengetext2, 
  leveleasy2, 
  leveldreamer2,
  levelkappaclysm2, 
  levelsunshine2, 
  levelrevolution2, 
  levelwoods2,
  levelbloodbathbutno2,
  levelprettyeasytext2,
  level16text2, 
  levelEtext2, 
  level19text2, 
  leveldeathmoon2, 
  leveldecode2, 
//  levelnostalgists2, 
  levelsupercycles2,
  levelproblematic2, 
  levelfiretemple2,
  levelforesttemple2,
  leveleon2, 
  levelpgclubtext2,
  levelstalemate2,
  levelbloodbath2,
  levelcataclysm2,
  level10text2, 
  level14text2,
};


const unsigned char level_text_size[] = {
    sizeof(level1text) - 1,
	sizeof(level2text) - 1,
	0,
	0,
	sizeof(level5text) - 1,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(levelCtext) - 1,
	sizeof(levelDtext) - 1,
	0,
	0,
	sizeof(levelhexagontext) - 1,
	sizeof(levelblasttext) - 1,
	sizeof(levelCtext) - 1,
	0,
	0,
	sizeof(levelchallengetext) - 1,
	0,
	0,
	0,
	0,
	0,
	sizeof(levelwoodstext) - 1,
	sizeof(levelbloodbath2) - 1,
	sizeof(levelprettyeasytext) - 1,
	sizeof(level16text) - 1,
	0,
	0,
	0,
	0,
//	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
const unsigned char level_text_size2[] = {
    sizeof(level1text2) - 1,
	sizeof(level2text2) - 1,
	sizeof(level3text2) - 1,
	sizeof(level4text2) - 1,
	sizeof(level5text2) - 1,
	sizeof(level6text2) - 1,
	sizeof(level7text2) - 1,
	sizeof(level8text2) - 1,
	sizeof(level9text2) - 1,
	sizeof(levelAtext2) - 1,
	sizeof(levelBtext2) - 1,
	sizeof(levelCtext2) - 1,
	sizeof(levelDtext2) - 1,
	sizeof(levelclubtext2) - 1,
	sizeof(levelelectrodynamix2) - 1,
	sizeof(levelhexagon2) - 1,
	sizeof(levelblast2) - 1,
	sizeof(levelCtext22) - 1,
	sizeof(levelretray2) - 1,
	sizeof(levelsonar2) - 1,
	sizeof(levelchallengetext2) - 1,
	sizeof(leveleasy2) - 1,
	sizeof(leveldreamer2) - 1,
	sizeof(levelkappaclysm2) - 1,
	sizeof(levelsunshine2) - 1,
	sizeof(levelrevolution2) - 1,
	sizeof(levelwoods2) - 1,
	sizeof(levelbloodbathbutno2) - 1,
	sizeof(levelprettyeasytext2) - 1,
	sizeof(level16text2) - 1,
	sizeof(levelEtext2) - 1,
	sizeof(level19text2) - 1,
	sizeof(leveldeathmoon2) - 1,
	sizeof(leveldecode2) - 1,
//	sizeof(levelnostalgists2) - 1,
	sizeof(levelsupercycles2) - 1,
	sizeof(levelproblematic2) - 1,
	sizeof(levelfiretemple2) - 1,
	sizeof(levelforesttemple2) - 1,
	sizeof(leveleon2) - 1,
	sizeof(levelpgclubtext2) - 1,
	sizeof(levelstalemate2) - 1,
	sizeof(levelbloodbath2) - 1,
	sizeof(levelcataclysm2) - 1,
	sizeof(level10text2) - 1,
	sizeof(level14text2) - 1,
};

const char coin_counter[][3] = {
  "___",
  "^__",
  "_^_",
  "^^_",
  "__^",
  "^_^",
  "_^^",
  "^^^",
};


#include "defines/color1_charmap.h"

/*
	Refreshes level name & number
*/
void refreshmenu() {
	tmp5 = ((level&1)<<10);
	set_scroll_x(((level-tmp4)&1)<<8);
	
	__A__ = idx16_load_hi_NOC(leveltexts, level);
	if (__A__) draw_padded_text(leveltexts[level & 0x7F], level_text_size[level], 17, NTADR_A(8, 10)+tmp5);
	else one_vram_buffer_horz_repeat(' ', 17, NTADR_A(8, 10)+tmp5);
	// if (leveltexts2[level]) // always true
	draw_padded_text(leveltexts2[level & 0x7F], level_text_size2[level], 17, NTADR_A(8, 11)+tmp5);

	if (LEVELCOMPLETE[level]) { one_vram_buffer('y', NTADR_A(7, 9)+tmp5);
	one_vram_buffer('z', NTADR_A(8, 9)+tmp5); }
	else one_vram_buffer_horz_repeat(' ', 2, NTADR_A(7, 9)+tmp5);

	{	// write the difficulty
		tmp1 = difficulty_list[level];
		pal_col(0x0a, difficulty_pal_A[tmp1]);
		pal_col(0x0b, difficulty_pal_B[tmp1]);
		pal_set_update();
		
		tmp1 = (tmp1 << 1) + 'a';
		one_vram_buffer(tmp1, NTADR_A(7, 10)+tmp5);
		one_vram_buffer(++tmp1, NTADR_A(8, 10)+tmp5);
		one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(7, 11)+tmp5);
		one_vram_buffer(++tmp1, NTADR_A(8, 11)+tmp5);
		

	}
	// Star count stuff
		printDecimal(stars_list[level], 2, '0', ' ', NTADR_A(22, 9)+tmp5);

	// level number
	#ifdef FLAG_ENABLE_TEST_LEVELS
		printDecimal(level, 3, '0', ' ', NTADR_A(29, 2));
		printDecimal(level, 3, '0', ' ', NTADR_B(29, 2));
	#endif
};

void refreshmenu_part2() {
	
	// Normal level completeness stuff
		//printDecimal(level_completeness_normal[level], 3, '0', ' ', NTADR_A(14, 16)+tmp5);

	// Practice level completeness stuff
		//printDecimal(level_completeness_practice[level], 3, '0', ' ', NTADR_A(14, 19)+tmp5);

	//palette stuff
		tmp3 = level % 9;
		pal_col(0,colors_list[tmp3]);
		pal_col(0xE,colors_list[tmp3]);
		
		pal_spr(paletteLVLSelectSP);
		pal_col(0x10,colors_list[tmp3]);
		pal_col(0x1E,colors_list[tmp3]);
		pal_set_update();
	//coin stuff
		coins = 0;


	// then in the function...
	// combine all three into a single number from 0 - 7 to represent which coins have been grabbed
		tmp7 = byte((byte(coin3_obtained[level] << 1) | coin2_obtained[level]) << 1) | coin1_obtained[level];
		tmp7 = byte(tmp7<<1) + tmp7;
	// actually draw the coins
		multi_vram_buffer_horz((const char * const)coin_counter+tmp7, 3, NTADR_A(22, 12)+tmp5);

}

#include "defines/endlevel_charmap.h"
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


#define BAR_TILES 20
#define CENTER_TILES BAR_TILES - 2
#define BAR_MAX 100
#define NUMBER_PER_TILES BAR_MAX / BAR_TILES
void draw_progress_bar() {
	#define nametable_A !(level & 1)
	
	drawBarFlag--;

	if (tmp7 >= NUMBER_PER_TILES) {
		if (nametable_A) {
			one_vram_buffer(0x8c, NTADR_A(tmp1, tmp2));
		} else {
			one_vram_buffer(0x8c, NTADR_B(tmp1, tmp2));
		}
		high_byte(tmp6) = (tmp7 >= BAR_MAX ? BAR_MAX - NUMBER_PER_TILES : tmp7);

		
		high_byte(tmpA) = 0;
		do {
			high_byte(tmp6) -= NUMBER_PER_TILES;
			high_byte(tmpA) += 1;
		} while (high_byte(tmp6) >= NUMBER_PER_TILES);
		
		if (nametable_A) {
			one_vram_buffer_horz_repeat(0x6b, high_byte(tmpA), NTADR_A(tmp1 + 1, tmp2));
			one_vram_buffer_horz_repeat(0x02, BAR_TILES - high_byte(tmpA), NTADR_A(tmp1 + high_byte(tmpA), tmp2));
		} else {
			one_vram_buffer_horz_repeat(0x6b, high_byte(tmpA), NTADR_B(tmp1 + 1, tmp2));
			one_vram_buffer_horz_repeat(0x02, BAR_TILES - high_byte(tmpA), NTADR_B(tmp1 + high_byte(tmpA), tmp2));
		}
	} else {
		if (nametable_A) {
			one_vram_buffer(0x7c, NTADR_A(tmp1, tmp2));
			one_vram_buffer_horz_repeat(0x02, CENTER_TILES, NTADR_A(tmp1 + 1, tmp2));
		} else {
			one_vram_buffer(0x7c, NTADR_B(tmp1, tmp2));
			one_vram_buffer_horz_repeat(0x02, CENTER_TILES, NTADR_B(tmp1 + 1, tmp2));
		}
	}
	
	if (tmp7 >= BAR_MAX) {
		if (nametable_A) {
			one_vram_buffer(0x8d, NTADR_A(tmp1 + (BAR_TILES - 1), tmp2));
		} else {
			one_vram_buffer(0x8d, NTADR_B(tmp1 + (BAR_TILES - 1), tmp2));
		}
	} else {
		if (nametable_A) {
			one_vram_buffer(0x7d, NTADR_A(tmp1 + (BAR_TILES - 1), tmp2));
		} else {
			one_vram_buffer(0x7d, NTADR_B(tmp1 + (BAR_TILES - 1), tmp2));
		}
	}
	#undef nametable_A
}

#define TOTAL_PIXELS 8 * BAR_TILES // 8 * 20 = 160
#define PIXELS_PER_UNIT (TOTAL_PIXELS * 10) / (BAR_MAX) // (1600 / 100) = 1.6 | multiplied by 10 because of no floats
#define PIXELS_PER_PERCENTAGE (PIXELS_PER_UNIT * 256) / 10 // 1.6 * 256 = 409.6

void calculate_sprite_pos() {
	high_byte(tmp5) = tmp1;
	low_byte(tmp5) = 0;
	tmp3 = 1;

	if (tmp7 != 0) {
		do {
			tmp3++;
			tmp5 += PIXELS_PER_PERCENTAGE;
		} while (tmp3 < tmp7);
	}

	tmp1 = high_byte(tmp5);
}

CODE_BANK_POP()

