
CODE_BANK_PUSH("XCD_BANK_03")

void check_if_music_stopped();
void clear_shit();
void movement();
void bounds_check();
void title_cube_shit();
void title_robot_shit();
void title_mini_wave_shit();
void title_wave_shit();
void title_ufo_shit();
void title_ball_shit();
void title_swing_shit();
void title_ship_shit();
void refreshmenu();
void refreshmenu_part2();
void loop_routine_update();
void dec_mouse_timer();
void roll_new_mode();
void settings();
void set_title_icon();
void state_demo();
void mouse_and_cursor();
void colorinc();
void colordec();
void leveldec();
void levelinc();
void set_settings();
void start_the_level();
extern uint8_t famistudio_song_speed;





const unsigned char bgmtestscreen[468]={
0x01,0x02,0x01,0x04,0xae,0x02,0x01,0x13,0xae,0x02,0x01,0x09,0xaf,0x02,0x01,0x13,
0xaf,0x02,0x01,0x06,0x06,0x07,0x04,0x01,0x17,0x06,0x07,0x02,0x01,0x03,0x08,0x09,
0x05,0x01,0x17,0x08,0x09,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,0x0d,0x02,0x01,0x03,
0x0c,0xff,0x01,0x09,0xed,0xf5,0xf3,0xe9,0xe3,0xff,0x01,0x0a,0x0d,0x02,0x01,0x03,
0x0c,0xff,0x01,0x02,0x5c,0xfe,0x01,0x11,0x5d,0xff,0x01,0x02,0x0d,0x02,0x01,0x03,
0x0c,0xff,0x6e,0xff,0xfe,0x01,0x13,0xff,0x6f,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,
0x7e,0xff,0xfe,0x01,0x13,0xff,0x7f,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x02,
0x6c,0xfe,0x01,0x11,0x6d,0xff,0x01,0x02,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,
0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x04,0xef,0xf2,0xe9,0xe7,0xe9,0xee,0xe1,0xec,
0xff,0xe1,0xf2,0xf4,0xe9,0xf3,0xf4,0xff,0x01,0x05,0x0d,0x02,0x01,0x03,0x0c,0xff,
0x5c,0xfe,0x01,0x15,0x5d,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0xfe,0x01,0x17,0xff,
0x0d,0x02,0x01,0x03,0x0c,0xff,0xfe,0x01,0x17,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,
0x6c,0xfe,0x01,0x15,0x6d,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,0x0d,0x02,
0x01,0x03,0x0c,0xff,0x01,0x06,0xe3,0xef,0xf6,0xe5,0xf2,0xe5,0xe4,0xff,0xe2,0xf9,
0xff,0x01,0x08,0x0d,0x02,0x01,0x03,0x0c,0xff,0x5c,0xfe,0x01,0x15,0x5d,0xff,0x0d,
0x02,0x01,0x03,0x0c,0xff,0xfe,0x01,0x17,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0xfe,
0x01,0x17,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0xfe,0x01,0x17,0xff,0x0d,0x02,0x01,
0x03,0x0c,0xff,0xfe,0x01,0x17,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0x6c,0xfe,0x01,
0x15,0x6d,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,0x19,0x0d,0x02,0x01,0x03,0x0c,
0xff,0xff,0xf3,0xe5,0xec,0xe5,0xe3,0xf4,0xe0,0xff,0xf4,0xef,0xe7,0xe7,0xec,0xe5,
0xff,0xf0,0xec,0xe1,0xf9,0xec,0xe9,0xf3,0xf4,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,
0xff,0xf0,0xf2,0xe5,0xf3,0xf3,0xff,0xe1,0xff,0xf4,0xef,0xff,0xf0,0xec,0xe1,0xf9,
0xff,0xe0,0xff,0xf3,0xf4,0xef,0xf0,0xff,0xff,0x0d,0x02,0x01,0x03,0x0c,0xff,0x01,
0x03,0xf0,0xf2,0xe5,0xf3,0xf3,0xff,0xe2,0xff,0xf4,0xef,0xff,0xe5,0xf8,0xe9,0xf4,
0xff,0x01,0x06,0x0d,0x02,0x01,0x03,0x0a,0x0b,0x04,0x01,0x09,0x06,0x0e,0x0e,0x07,
0x04,0x01,0x09,0x0a,0x0b,0x02,0x01,0x05,0x05,0x01,0x09,0x08,0x05,0x05,0x09,0x05,
0x01,0x09,0x02,0x01,0x03,0xff,0x5c,0x5f,0x01,0x03,0x53,0xff,0x77,0x00,0x01,0x05,
0xdd,0x77,0x00,0x01,0x05,0xdd,0x77,0x00,0x01,0x05,0xdd,0x77,0x00,0x01,0x05,0xdd,
0x77,0x00,0x01,0x05,0xdd,0x77,0x00,0x01,0x05,0xdd,0x0f,0x05,0x05,0x0d,0x07,0x05,
0x05,0x0f,0x01,0x00
};



const unsigned char SoundQueue[416]={
0x01,0x02,0x01,0x04,0xae,0x02,0x01,0x13,0xae,0x02,0x01,0x09,0xaf,0x02,0x01,0x13,
0xaf,0x02,0x01,0x04,0x06,0x07,0x04,0x01,0x1b,0x06,0x07,0x08,0x09,0x05,0x01,0x1b,
0x08,0x09,0x0c,0xff,0x01,0x1d,0x0d,0x0c,0xff,0x01,0x0b,0xed,0xf5,0xf3,0xe9,0xe3,
0xff,0x01,0x0c,0x0d,0x0c,0xff,0x01,0x04,0x5c,0xfe,0x01,0x11,0x5d,0xff,0x01,0x04,
0x0d,0x0c,0xff,0x01,0x02,0x6e,0xff,0xfe,0x01,0x13,0xff,0x6f,0xff,0x01,0x02,0x0d,
0x0c,0xff,0x01,0x02,0x7e,0xff,0xfe,0x01,0x13,0xff,0x7f,0xff,0x01,0x02,0x0d,0x0c,
0xff,0x01,0x04,0x6c,0xfe,0x01,0x11,0x6d,0xff,0x01,0x04,0x0d,0x0c,0xff,0x01,0x1d,
0x0d,0x0c,0xff,0x01,0x07,0xf0,0xec,0xe1,0xf9,0xec,0xe9,0xf3,0xf4,0xff,0xf1,0xf5,
0xe5,0xf5,0xe5,0xff,0x01,0x07,0x0d,0x0c,0xff,0x5c,0xfe,0x01,0x19,0x5d,0xff,0x0d,
0x0c,0xff,0xfe,0x01,0x1b,0xff,0x0d,0x0c,0xff,0xfe,0x01,0x1b,0xff,0x0d,0x0c,0xff,
0xfe,0x01,0x1b,0xff,0x0d,0x0c,0xff,0xfe,0x01,0x1b,0xff,0x0d,0x0c,0xff,0xfe,0x01,
0x1b,0xff,0x0d,0x0c,0xff,0xfe,0x01,0x1b,0xff,0x0d,0x0c,0xff,0xfe,0x01,0x1b,0xff,
0x0d,0x0c,0xff,0xfe,0x01,0x1b,0xff,0x0d,0x0c,0xff,0xfe,0x01,0x1b,0xff,0x0d,0x0c,
0xff,0xfe,0x01,0x1b,0xff,0x0d,0x0c,0xff,0x6c,0xfe,0x01,0x19,0x6d,0xff,0x0d,0x0c,
0xff,0x01,0x03,0xf3,0xe5,0xec,0xe5,0xe3,0xf4,0xe0,0xff,0xf4,0xef,0xe7,0xe7,0xec,
0xe5,0xff,0xf0,0xec,0xe1,0xf9,0xec,0xe9,0xf3,0xf4,0xff,0x01,0x02,0x0d,0x0c,0xff,
0x01,0x03,0xf0,0xf2,0xe5,0xf3,0xf3,0xff,0xe1,0xff,0xf4,0xef,0xff,0xe1,0xe4,0xe4,
0xff,0xf4,0xef,0xff,0xf1,0xf5,0xe5,0xf5,0xe5,0xff,0x01,0x02,0x0d,0x0c,0xff,0x01,
0x03,0xf0,0xf2,0xe5,0xf3,0xf3,0xff,0xe2,0xff,0xf4,0xef,0xff,0xf2,0xe5,0xed,0xef,
0xf6,0xe5,0xff,0x01,0x08,0x0d,0x0c,0xff,0x01,0x03,0xf0,0xf2,0xe5,0xf3,0xf3,0xff,
0xf5,0xf0,0xff,0xf4,0xef,0xff,0xf3,0xeb,0xe9,0xf0,0xff,0xf4,0xef,0xff,0xee,0xe5,
0xf8,0xf4,0xff,0xff,0x0d,0x0a,0x0b,0x04,0x01,0x0b,0x06,0x0e,0x0e,0x07,0x04,0x01,
0x0b,0x0a,0x0b,0x02,0x02,0x05,0x01,0x0b,0x08,0x05,0x05,0x09,0x05,0x01,0x0b,0x02,
0x02,0x7f,0x5c,0x5f,0x01,0x03,0x53,0xdf,0x55,0x00,0x01,0x05,0x55,0x55,0x00,0x01,
0x05,0x55,0x11,0x00,0x01,0x05,0x44,0x11,0x00,0x01,0x05,0x44,0x11,0x00,0x01,0x05,
0x44,0x55,0x00,0x01,0x05,0x45,0x07,0x05,0x05,0x0d,0x07,0x05,0x05,0x0d,0x01,0x00
};

void unrle_bgm1() {
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);  
}
void unrle_bgm2() {
	vram_adr(NAMETABLE_A);
	vram_unrle(SoundQueue);  
}



const uint8_t xbgm_lookup_table[] = {
	song_menu_theme,
	song_menu_theme_b_sides,
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
	song_geometrical_dominator,
	song_deadlocked,
	song_fingerdash,
	song_dash,
	song_the_challenge,
	song_practice,
	song_scheming_weasel,
	
	song_against_the_odds_redux,
	song_atthespeedoflight,
	song_atthespeedoflight2,
	song_atthespeedoflight3,
	song_atthespeedoflightfull,
	song_beast_mode_gdw_cut,
	song_candyland,
	song_chaozfantasy,
	song_chaoz_impact,
	song_clutterfunk_2,
	song_death_moon,
	song_driving_by_night,
	song_endgame,
	song_freedom_dive,
	song_glint,
	song_retray,
	song_ground_to_space,
	song_haunted_woods,
	song_hell,
	song_idols,
	song_infernoplex,
	song_infernoplex_full,
	song_jack_russel,
	song_just_right,
	song_kesobomb,
	song_lost,
	song_ludicrous_speed,
	song_machina_gdw_cut,
	song_magic_touch,
	song_mayhem_short,
	song_mayhem,
	song_metamorphosis,
	song_midnight,
	song_ninox,
	song_crackdown,
	song_payload_gdw_cut,
	song_problematic,
	song_pyrophoric,
	song_rainbow_tylenol,
	song_stalemate,
	song_stalemate_full,
	song_stereo_madness_2,
	song_subtle_oddities,
	song_eon,
	song_thoughts,
	song_ultimatedestruction,
	song_youve_been_trolled,
	song_whats_a_future_funk,
	song_windfall,
	song_years_gdw_cut,
};


const uint8_t loNTAddrTableTitleScreen[]={
    LSB(NTADR_A(9, 11)),	// -1 = 4
    LSB(NTADR_A(15, 11)),	// 0
    LSB(NTADR_A(21, 11)),	// 1 
    LSB(NTADR_A(9, 17)),	// 2
    LSB(NTADR_A(15, 17)),	// 3
    LSB(NTADR_A(21, 17)),	// 3
    LSB(NTADR_A(27, 1)),	// 4
    LSB(NTADR_A(9, 11)),	// 5 = 0
    LSB(NTADR_A(15, 11))	// 5 = 0
};

const uint8_t hiNTAddrTableTitleScreen[]={
    MSB(NTADR_A(9, 11)),	// -1 = 4
    MSB(NTADR_A(15, 11)),	// 0
    MSB(NTADR_A(21, 11)),	// 1
    MSB(NTADR_A(9, 17)),	// 2
    MSB(NTADR_A(15, 17)),	// 3
    MSB(NTADR_A(21, 17)),	// 3
    MSB(NTADR_A(27, 1)),	// 4
    MSB(NTADR_A(9, 11)),	// 5 = 0
    MSB(NTADR_A(15, 11))	// 5 = 0
};

void gameboy_check();
void state_menu();
//void bgmtest();


const uint8_t BG_Table2[]={
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x1A,
	0x1B,
	0x1C
};

const uint8_t G_Table2[]={
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x2A,
	0x2B,
	0x2C
};

#include "defines/mainmenu_charmap.h"

const uint8_t lvlselect_irq_table[] = {
	31,
	irqtable_hscroll, 0x00, // item 0x02 gets modified every frame
	149,
	irqtable_hscroll, 0x00,

	irqtable_end // always end with 0xff
};
void draw_both_progress_bars();
void levelselection() {


}


void draw_progress_bar();
void draw_full_progress_bar();
void draw_percentage();

/*
	all 8 bit tmps:

	tmp1 : x
	tmp2 : y
	tmp3 : offset into sprite table
	tmp4 : needed inside the transitions
	tmp7 : percentage
	
	free 8 bit tmps inside calls:
	- tmp8
	damn...

	technically i can use the low byte of 16 bits tmps
*/
void draw_both_progress_bars() {
	

		
}
void calculate_sprite_pos();
void draw_bar_sprites() {
}

void draw_full_progress_bar() {
	if (drawBarFlag) crossPRGBankJump0(draw_progress_bar);
	// end tmp3 need

	// tmp5 is now used for the temporary sprite x pos with subpixels
	draw_bar_sprites();
	// end tmp5 usage
}

void draw_level_progress() {
	update_level_completeness();
	hexToDec(__A__);
	tmp1 = 116;		// x
	tmp2 = 0;		// y
	tmp3 = 25;		// offset
	draw_percentage();	
}

void draw_percentage() {
	if (hexToDecOutputBuffer[2]) { 				  
		high_byte(tmp6) = hexToDecOutputBuffer[2]; // number
		crossPRGBankJump0(put_number);
	}

	if (hexToDecOutputBuffer[2] | hexToDecOutputBuffer[1]) {
		tmp1 += 8;					    		   // x
		high_byte(tmp6) = hexToDecOutputBuffer[1]; // number
		crossPRGBankJump0(put_number);
	}

	tmp1 += 8;					   			   // x
	high_byte(tmp6) = hexToDecOutputBuffer[0]; // number
	crossPRGBankJump0(put_number);

	tmp1 += 8;					    // x
	high_byte(tmp6) = 10; 			// percentage
	crossPRGBankJump0(put_number);
}

#include "defines/mainmenu_customize.h"

const uint8_t loNTAddrTableCustomizeScreen[] = {
	LSB(NTADR_A(13, 8)),		// -1 = 3
	LSB(NTADR_A(4, 14)),		// 0
	LSB(NTADR_A(13, 14)),		// 1
	LSB(NTADR_A(22, 14)),		// 2
	LSB(NTADR_A(13, 8)),		// 3
	LSB(NTADR_A(4, 14))			// 4 = 0
};

const uint8_t hiNTAddrTableCustomizeScreen[] = {
	MSB(NTADR_A(13, 8)),		// -1 = 3
	MSB(NTADR_A(4, 14)),		// 0
	MSB(NTADR_A(13, 14)),		// 1
	MSB(NTADR_A(22, 14)),		// 2
	MSB(NTADR_A(13, 8)),		// 3
	MSB(NTADR_A(4, 14))			// 4 = 0
};

void updateColors() {
	if (joypad1.press_up) {
		crossPRGBankJump0(colorinc);
	}
	if (joypad1.press_down) { 
		crossPRGBankJump0(colordec);
	}
	//if ((pad[0] & PAD_SELECT) && (pad_new[0] & PAD_A)) icon_colors[settingvalue] = 0x0D;	
}

void customize_screen() {

}




const uint8_t UFO_Title_Jump_Table[]={
	5,
	4,
	3,
	3,
	2,
	2,
	2,
	2,
	1,
	1,
	1,
	1,
	1,
	0,
	-1,
	-1,
	-1,
	-1,
	-1,
	-2,
	-2,
	-2,
	-2,
	-3,
	-3,
	-4,
	-5,
};

const uint8_t BALL_Title_Jump_Table[]={
	1,
	1,
	1,
	2,
	2,
	3,
	3,
	4,
};
	
const uint8_t menu_color_table[]={
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C
};

#include "defines/mainmenu_charmap.h"

const char palsystem[] = "FOR PAL SYSTEMS";
#define NTSC_SYS PEEK(0x00)




const uint8_t menu_irq_table[] = {
	180,
	irqtable_hscroll, 0x00,

	irqtable_end // always end with 0xff
};
void state_menu() {
	poweroffcheck = 0xff;
	if (exitingLevelSelect) {
		draw_both_progress_bars();
		pal_fade_to_withmusic(4,0);
		exitingLevelSelect = 0;
	} else {	
		pal_fade_to_withmusic(4,0);
	}
	mmc3_disable_irq();

	do {
		discoframe = newrand() & 15;
	} while (discoframe > 11);

	if (joypad1.select) nestopia = 1;

	all_levels_complete = 0xFC;

	
	ppu_off();

	gamemode = 0;

	if (all_levels_complete == 0xFC) pal_bg(splashMenu2);
	else pal_bg (splashMenu);
	
	newrand();

	mmc3_set_8kb_chr(MENUBANK);

	set_title_icon();
	set_title_icon();

	
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	
	
	
//	set_scroll_x(0);
//    set_scroll_y(0);

	kandowatchesyousleep = 0;

	if (!NTSC_SYS) multi_vram_buffer_horz(palsystem, sizeof(palsystem)-1, NTADR_A(9,7));
	//mmc3_set_prg_bank_1(GET_BANK(state_menu));

	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(xbgm_lookup_table[menu_music]);
	menuMusicCurrentlyPlaying = 1;

	settingvalue = 0;
	practice_point_count = 0;
	
	// Enable SRAM write
	POKE(0xA001, 0x80);

	write_irq_table(menu_irq_table);
	//edit_irq_table(2, low_byte(tmp8));
	set_irq_ptr(irqTable);
	tmp8 = 0;
	

	menuMusicCurrentlyPlaying = 1;
	//invisible = 0;
	

	oam_clear();

	//POKE(0x200, 175);
	//POKE(0x201, 0x02); // Use the second tile in the BG side which is pure black
	//POKE(0x202, 0b00100000); // second palette
	//POKE(0x203, 0x00);
	
	// Expand the data for the menu nametable while the PPU is still off
    vram_adr(NAMETABLE_A);
    vram_unrle(game_start_screen);
	vram_adr(NAMETABLE_B);
    vram_unrle(game_start_screen);

	set_scroll_x(0);

	speed = 1;
 	ppu_on_all();
	joypad1.press = 0;
	pal_fade_to_withmusic(0,4);

	tmp4 = menuselection; ++tmp4;
	tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
	if (menuselection != 5) {
		one_vram_buffer('a', tmp5);
		one_vram_buffer('b', addloNOC(tmp5, 1));
		one_vram_buffer(' ', NTADR_A(26, 2));
		one_vram_buffer(' ', NTADR_A(26, 3));
		
	}
	else {
		one_vram_buffer(0x6F, NTADR_A(26, 2));
		one_vram_buffer(0x7F, NTADR_A(26, 3));
		
	}	

	roll_new_mode();
	kandoframecnt = 0;
	teleport_output = 0Xff;
	currplayer_y_small = 160;
	currplayer_x_small = 0;
	titlecolor3 = color3;
	titlecolor2 = color2;
	titlecolor1 = color1;
/*	if (all_levels_complete != 0xFC) {
		one_vram_buffer(0x19, NTADR_A(27,2));
		one_vram_buffer(0x1A, NTADR_A(28,2));
		one_vram_buffer(0x2D, NTADR_A(27,3));
		one_vram_buffer(0x4D, NTADR_A(28,3));
	}
	else {
		one_vram_buffer(0x1B, NTADR_A(27,2));
		one_vram_buffer(0x1C, NTADR_A(28,2));
		one_vram_buffer(0x1D, NTADR_A(27,3));
		one_vram_buffer(0x1E, NTADR_A(28,3));
	}	*/
	while (!(joypad1.press & (PAD_START | PAD_A))){

		pal_col(0x11,titlecolor3);
		pal_col(0x12,titlecolor1);
		pal_col(0x13,titlecolor2);
		pal_set_update();

		loop_routine_update();
		 // read the first controller

		newrand();
		newrand();
		newrand();
		if (titlemode != 0xFF) currplayer_x_small += speed;
		if (currplayer_x_small >= 0xFB) { 
			roll_new_mode();		
		}
		//temp values:
		//teleport_output
		//currplayer_gravity
		//tmp2 tmp7
		//tmpi8



		if (currplayer_x_small <= 0xF7) {
			switch (titlemode) {
				case 0:		//cube
					//oam_spr(currplayer_x_small, currplayer_y_small, 1, 0x20);
					//oam_spr(currplayer_x_small + 8, currplayer_y_small, 3, 0x20);
					title_cube_shit();

					high_byte(player_x[0]) = currplayer_x_small;
					high_byte(player_y[0]) = currplayer_y_small;
					crossPRGBankJump0(drawplayerone);
					break;
				case 1:		//UFO
					title_ufo_shit();
					
					oam_spr(currplayer_x_small, currplayer_y_small, 0x3F, 0x20);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, 0x3F, 0x60);
					break;
				case 2:		//mini cube
					title_cube_shit();
					mini[0] = 1;
					high_byte(player_x[0]) = currplayer_x_small;
					high_byte(player_y[0]) = currplayer_y_small;
					crossPRGBankJump0(drawplayerone);
					mini[0] = 0;
					break;
				case 3:		//ship
					title_ship_shit();

					switch (tmpi8) {
						case 0:
							tmp7 = 0x29;
							break;
						case 1:
							tmp7 = 0x2D;
							break;
						case 2:
						case 3:
							tmp7 = 0x31;
							break;
						case -1:
							tmp7 = 0x25;
							break;
						case -2:
						case -3:
							tmp7 = 0x21;
							break;

					};
						if (currplayer_y_small == 160 && tmp7 < 0x29) tmp7 = 0x29;
						else if (currplayer_y_small == 8 && tmp7 > 0x29) tmp7 = 0x29;
						
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7 + 2, 0x20);
					break;
				case 4:		//robot

					title_robot_shit();
					
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					if (currplayer_y_small == 160) {
						if (!retro_mode) {
							switch (ballframe) {
								case 0:
									tmp1 = 0x01;
									tmp2 = 0x03;
									tmp3 = 0x05;
									break;
								case 1:
									tmp1 = 0xFF;
									tmp2 = 0x07;
									tmp3 = 0x09;
									break;
								case 2:
									tmp1 = 0x01;
									tmp2 = 0x0B;
									tmp3 = 0x05;
									break;
								case 3:
									tmp1 = 0xFF;
									tmp2 = 0x0D;
									tmp3 = 0x09;
									break;	
							};
						}
						else {
							switch (ballframe) {
								case 0:
									tmp1 = 0xFF;
									tmp2 = 0x01;
									tmp3 = 0x03;
									break;
								case 1:
									tmp1 = 0xFF;
									tmp2 = 0x07;
									tmp3 = 0x09;
									break;
								case 2:
									tmp1 = 0xFF;
									tmp2 = 0x0B;
									tmp3 = 0x0D;
									break;
								case 3:
									tmp1 = 0xFF;
									tmp2 = 0x11;
									tmp3 = 0x13;
									break;	
							};
						}						
					}
					else {
						tmp1 = 0xFF;
						if (!retro_mode) {
							tmp2 = 0x0F;
							tmp3 = 0x11;
						}
						else {
							tmp2 = 0x11;
							tmp3 = 0x13;							
						}
					}
					oam_spr(currplayer_x_small-8, currplayer_y_small, tmp1, 0x20);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x20);					
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp3, 0x20);					
					break;
				case 5:		//spider
//					if (kandoframecnt & 1) {
//						if (!(newrand() & 31)) 	invert_gravity(currplayer_gravity);
//					}

					//if (!currplayer_gravity) { 
					currplayer_y_small = 160; tmp7 = 0x20; 
					//}
//					else { currplayer_y_small = 8; tmp7 = 0xA0; }

					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:
							tmp1 = 0x21;
							tmp2 = 0x23;
							tmp3 = 0x25;
							break;
						case 1:
							tmp1 = 0x27;
							tmp2 = 0x29;
							tmp3 = 0x2B;
							break;
						case 2:
							tmp1 = 0x2D;
							tmp2 = 0x2F;
							tmp3 = 0x31;
							break;
						case 3:
							tmp1 = 0xFF;
							tmp2 = 0x33;
							tmp3 = 0x35;
							break;	
					}
					oam_spr(currplayer_x_small - 8, currplayer_y_small, tmp1, tmp7);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);					
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp3, tmp7);					
					break;				
				case 6:		//wave
					title_wave_shit();
					
					if (currplayer_y_small == 160 || currplayer_y_small == 8) {
						tmp1 = 0x29;
						tmp2 = 0x20;
					}
					else if (currplayer_gravity) {
						tmp1 = 0x2D;
						tmp2 = 0xA0;
					}
					else {
						tmp1 = 0x2D;
						tmp2 = 0x20;
					}
					oam_spr(currplayer_x_small, currplayer_y_small, tmp1, tmp2);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp1 + 2, tmp2);
					break;				
				case 7:		//ball
					title_ball_shit();
					
					if (!(kandoframecnt & 0x07)) ballframe ^= 1;

					if (retro_mode && currplayer_gravity) tmp7 = 0xA0;
					else tmp7 = 0x20;

					if (ballframe) tmp2 = 0x3F;
					else tmp2 = 0x1B;						

					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp2, tmp7 + 0x40);

					break;
				case 8:		//swing
					title_swing_shit();


					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:
							tmp2 = 0x31;
							tmp7 = 0x20;
							break;
						case 1:
							tmp2 = 0x35;
							tmp7 = 0x20;
							break;
						case 2:
							tmp2 = 0x31;
							tmp7 = 0x20;
						case 3:
							tmp2 = 0x35;
							tmp7 = 0xA0;
							break;	
					};
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);					
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp2+2, tmp7);					
					break;
				case 9:		//mini ship
					title_ship_shit();

					switch (tmpi8) {
						case 0:
							tmp7 = 0x05;
							break;
						case 1:
							tmp7 = 0x07;
							break;
						case 2:
						case 3:
							tmp7 = 0x09;
							break;
						case -1:
							tmp7 = 0x03;
							break;
						case -2:
						case -3:
							tmp7 = 0x01;
							break;

					};
					if (currplayer_y_small == 160 && tmp7 < 0x05) tmp7 = 0x05;
					else if (currplayer_y_small == 8 && tmp7 > 0x05) tmp7 = 0x05;					

					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);

					break;	
				case 10:		//mini ball
					title_ball_shit();
					if (retro_mode && currplayer_gravity) tmp7 = 0xA0;
					else tmp7 = 0x20;					
					oam_spr(currplayer_x_small, currplayer_y_small, 0x3D, tmp7);
					break;	
				case 11:		//mini wave
					title_mini_wave_shit();
					
					if (currplayer_y_small == 160 || currplayer_y_small == 8) {
						tmp1 = 0x0D;
						tmp2 = 0x20;
						oam_spr(currplayer_x_small, currplayer_y_small, 0x0D, 0x20);
					}
					else if (currplayer_gravity) {
						tmp1 = 0x11;
						tmp2 = 0xA0;
					}
					else {
						tmp1 = 0x11;
						tmp2 = 0x20;
					}
					oam_spr(currplayer_x_small, currplayer_y_small, tmp1, tmp2);
					break;	
				case 12:		//mini ufo
					title_ufo_shit();
					
					oam_spr(currplayer_x_small, currplayer_y_small, 0x19, 0x20);
					break;		
				case 13:		//mini robot
					
					title_robot_shit();

					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 2 ? -2 : 1;

					tmp2 = 0x37 + (ballframe * 2);

					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x20);
					break;

				case 14:		//mini spider
				/*
					if (kandoframecnt & 1) {
						if (!(newrand() & 31)) 	invert_gravity(currplayer_gravity);
					}

					if (!currplayer_gravity) { 
					*/
					currplayer_y_small = 160; tmp7 = 0x20; 
					//}
					//else { currplayer_y_small = 8; tmp7 = 0xA0; }

					
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:				
							tmp2 = 0x21;
							break;
						case 1:				
							tmp2 = 0x23;
							break;
						case 2:				
							tmp2 = 0x25;
							break;
						case 3:				
							tmp2 = 0x27;
							break;
					};
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);
					break;
				case 15:		//mini swing

					title_swing_shit();

					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:	
							tmp7 = 0x3F;
							break;
						case 1:				
							tmp7 = 0x1B;
							break;
						case 2:				
							tmp7 = 0x3F;
							break;
						case 3:				
							tmp7 = 0x3D;
							break;
					};	
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);
					break;
				case 0xFF:
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 5 ? -5 : 1;
					switch (ballframe) {
						case 0:
							tmp7 = 0x1D;
							break;
						case 1:
							tmp7 = 0x7D;
							break;
						case 2:
							tmp7 = 0x1F;
							break;
						case 3:
							tmp7 = 0x7F;
							break;	
						case 4:
							tmp7 = 0xFF;
							break;	
						case 5:
							roll_new_mode();
							break;
					};
					if (ballframe != 5) {
						oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);
						oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7, 0xE0);					
					}
					break;					
			};
		}


		//if ((pad[0] & PAD_LEFT) && (pad[0] & PAD_DOWN) && (pad[0] & PAD_SELECT) && (pad_new[0] & PAD_B)) { color_emphasis(COL_EMP_GREY); color_emphasis(COL_EMP_GREEN); }
		if (!(kandoframecnt & 127)) {
			tmp3 = 0x80 + BG_Table2[discoframe];
			
			if (tmp3 < 0x80) tmp3 += 0x80;
			else if (tmp3 >= 0xF0) tmp3 -= 0x80;
			tmp2 = (tmp3 & 0x3F);  		    
				pal_col(0, tmp2);
				pal_col(0x11, tmp2);
				// pal_col(1, oneShadeDarker(tmp2)); 
				// pal_col(9, oneShadeDarker(tmp2)); 
				pal_set_update();
		
			tmp3 = 0xC0 + BG_Table2[discoframe];
			
			if (tmp3 < 0x80) tmp3 += 0x80;
			else if (tmp3 >= 0xF0) tmp3 -= 0x80;
			tmp2 = (tmp3 & 0x3F);  		    
			//	pal_col(6, tmp2);
			//	pal_col(5, oneShadeDarker(tmp2)); 
			//	pal_set_update();
			pal_set_update();
			discoframe++;
			if (discoframe == 12) discoframe = 0;
		}
		dec_mouse_timer();
		tmp3 = 0;	
		
		if (joypad1.press_right) {
			//if (menuselection == 6) menuselection = 0;
			//else menuselection++;
			//tmp3--;
		}
		if (joypad1.press_left) {
			//if (menuselection == 0) menuselection = 6;
			//else menuselection--;
			//tmp3++;
		}

		if (tmp3 ) {    // menu selection incremented
			tmp4 = menuselection; ++tmp4;
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			if (menuselection != 5) {
				one_vram_buffer('a', tmp5);
				one_vram_buffer('b', addloNOC(tmp5, 1));
				one_vram_buffer(' ', NTADR_A(26, 2));
				one_vram_buffer(' ', NTADR_A(26, 3));
				
			}
			else {
				one_vram_buffer(0x6F, NTADR_A(26, 2));
				one_vram_buffer(0x7F, NTADR_A(26, 3));
				
			}

			tmp4 += tmp3;   // Get the old index
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			one_vram_buffer(' ', tmp5);
			one_vram_buffer(' ', addloNOC(tmp5, 1));
		}
		if (joypad1.press_select) {
				tmp2 = 0;
				gameState = 0;
				famistudio_music_stop();
				music_update();
				menuMusicCurrentlyPlaying = 0;
				ppu_wait_nmi();
				return;
		}
		low_byte(tmp8) += CUBE_SPEED_X05>>8;
		edit_irq_table(low_byte(tmp8), 2); 

/*
		if (joypad1.press_b) {
			oam_clear();
			gameState = 0xFE;
			return;
		}
*/
		if (mouse.left_press) {
			if ((uint8_t)(currplayer_y_small - 8) <= (uint8_t)mouse.y && (uint8_t)(currplayer_y_small + 8) >= (uint8_t)mouse.y) {
				if (mouse.x >= currplayer_x_small && (uint8_t)(currplayer_x_small + 16) >= mouse.x) {
					if (titlemode != 0xFF) {
						titlemode = 0xFF;		//crossPRGBankJump8(playPCM, 1); 
						sfx_play(sfx_death,0);
						ballframe = 0;
					}
				}
			}
				
			
			if ((mouse.y >= 0x5E && mouse.y <= 0x7A)) {
				if (mouse.x >= 0x41 && mouse.x <= 0x5A) {
//					menuselection = 6; break;
				}
				else if (mouse.x >= 0x6F && mouse.x <= 0x8C) {
					menuselection = 0; break;
				}
				else if (mouse.x >= 0xA1 && mouse.x <= 0xBA) {
//					menuselection = 1; break;
				}
			}				
			else if ((mouse.y >= 0x8C && mouse.y <= 0x9B)) {
				if (mouse.x >= 0x46 && mouse.x <= 0x56) {
//					menuselection = 2; break;
				}
				else if (mouse.x >= 0x76 && mouse.x <= 0x86) {
//					menuselection = 3; break;
				}				
				else if (mouse.x >= 0xA6 && mouse.x <= 0xB6) {
//					menuselection = 4; break;
				}				
			}
			else if ((mouse.y >= 0x0D && mouse.y <= 0x1C)) {
				if (mouse.x >= 0xD6 && mouse.x <= 0xE4) {
//					menuselection = 5; break;
				}
			}
		}	
		
		
	}	
//	set_scroll_y(0);		does this break anything?
//	set_scroll_x(0);
	oam_clear();
	ppu_wait_nmi();
	tmp7 = newrand() & 255;
	normalorcommlevels = 1;
	switch (menuselection) {
		case 0x00:
			gameState = 0x04;
			return;
	};
	
}


void leveldec() {
	--level;
	//if (level == 0x0B) level = 0x0A;	//THEORY OF EVERYTHING SKIP
	low_byte(tmp8) = 0xff;
	tmp4 = 0;
	if (!normalorcommlevels) {
		if (level == 0xFF){
			level = LEVEL_COUNT-1;
			
		}
	}
	else {
		if (level < LEVEL_COUNT) level = LEVEL_COUNT2 - 1;
	}
	//break;
	crossPRGBankJump0(refreshmenu);
}			

void levelinc() {
	++level;
	//if (level == 0x0B) level = 0x0C;	//THEORY OF EVERYTHING SKIP
	low_byte(tmp8) = 0xff;
	tmp4 = 1;
	if (!normalorcommlevels) {
		if (level >= LEVEL_COUNT){
			level = 0x00;
			
		}
	}
	else {
		if (level >= LEVEL_COUNT2){
			level = LEVEL_COUNT;
		}
	}
	crossPRGBankJump0(refreshmenu);
}			

void start_the_level() {
	sfx_play(sfx_start_level, 0);
	famistudio_music_stop();
	if (tmp4) edit_irq_table(high_byte(tmp8),2);
	else edit_irq_table(low_byte(tmp8),2);
	tmpA = 0;
	do {
		oam_clear();
		draw_both_progress_bars();
		ppu_wait_nmi();
		music_update();
	} while (++tmpA < 30);
	gameState = 0x02;
	pal_fade_to(4,0);
	menuMusicCurrentlyPlaying = 0;
}			

void set_title_icon() {
		if (titlemode < 4) {
			while (tmp7 > 26) {
				tmp7 = newrand() & 31;
			}
			titleicon = tmp7;
			tmp7 = tmp7 * 2;
			tmp7 += 40;
			mmc3_set_2kb_chr_bank_0(retro_mode ? 18 : tmp7);
		}
		else if ((titlemode <= 7 && titlemode != 6) || titlemode == 13 || titlemode == 10) {
			mmc3_set_2kb_chr_bank_0(retro_mode == 0 ? 20 : 22);	
		}
		else if ((titlemode <= 15 && titlemode != 13) || titlemode == 6) {
			mmc3_set_2kb_chr_bank_0(retro_mode == 0 ? 24 : 26);		
		}
}			

void roll_new_mode() {
	speed = (newrand() & 3); 
	if (speed == 0) speed = 1; 
	currplayer_gravity = GRAVITY_DOWN; 
	currplayer_x_small = 0x08; 
	currplayer_y_small = 0xA0;
	player_vel_y[0] = 0;
	tmpi8 = 0;
	teleport_output = 0XFF;
	tmp7 = titlemode;
	do {
		do {
			titlemode = newrand() & 15;
		} while (titlemode > 9);
	} while (titlemode == tmp7);
	if (titlemode >= 8) {
		titlemode = (newrand() & 7) + 8;
	}
	if (retro_mode && titlemode == 0) titlemode = tmp7;
	if (retro_mode && titlemode == 2) titlemode = tmp7;
//	titlemode = 11; //to test
	if (titlemode == 1 || titlemode == 3 || titlemode == 6 || titlemode == 9 || titlemode == 11 || titlemode == 12) {
		while (tmp1 > 0xA0 && tmp1 <= 0x20) {
			tmp1 = newrand() & 0xFF;
		}
		currplayer_y_small = tmp1;
	}
		
		
	ballframe = 0;
	oam_clear();
/*
	while (tmp1 >= 53) {
		tmp1 = newrand() & 63;
	}
	while (tmp2 >= 53) {
		tmp2 = newrand() & 63;
	}
	while (tmp3 >= 53) {
		tmp3 = newrand() & 63;
	}
*/
//	titlecolor1 = menu_color_table[tmp1];
//	titlecolor2 = menu_color_table[tmp2];   most of our colors suck
//	titlecolor3 = menu_color_table[tmp3];
	set_title_icon();
}			

void dec_mouse_timer() {
	kandoframecnt++;
	if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
}		

void loop_routine_update() {
	newrand();
	ppu_wait_nmi();
	music_update();
	oam_clear();
	mouse_and_cursor();
}		


void bounds_check() {
	if (currplayer_y_small >= 160) {
		currplayer_y_small = 160;
	}		
	else if (currplayer_y_small < 0x08) currplayer_y_small = 0x08;	
}	
void title_ship_shit() {
	if (kandoframecnt & 1) { if (!(newrand() & 7)) invert_gravity(currplayer_gravity); }

	currplayer_y_small -= tmpi8;

	if (currplayer_y_small >= 160) {
		currplayer_y_small = 160;
	}		
	else if (currplayer_y_small < 0x08) { 
		currplayer_y_small = 0x08; 
		currplayer_gravity = GRAVITY_DOWN;
		tmpi8 = 0;
	}					


	if (currplayer_gravity) {
		if (!(kandoframecnt & 7)) { if (tmpi8 < 3) tmpi8++; }
	}

	else {
		
		if (!(kandoframecnt & 7)) { if (tmpi8 > -3) tmpi8--; }
	}
}					

void title_swing_shit() {
	if (kandoframecnt & 1) { 
		if (!(newrand() & 15)) {
			invert_gravity(currplayer_gravity); 
		}
	}

	if ((kandoframecnt & 3) == 0)
			if (currplayer_gravity) {
				currplayer_vel_y_small -= 1;
				if (currplayer_vel_y_small <= -3) currplayer_vel_y_small = -3;
			} else {
				currplayer_vel_y_small += 1;
				if (currplayer_vel_y_small >= 3) currplayer_vel_y_small = 3;
			}

			
	currplayer_y_small += currplayer_vel_y_small;

	bounds_check();
}

void title_ball_shit() {
/*
	if (kandoframecnt & 1 && (currplayer_y_small == 0x08 || currplayer_y_small == 0xA0)) { 
		if (!(newrand() & 31)) {
			if (currplayer_y_small == 0x08) { currplayer_gravity = GRAVITY_UP; teleport_output = 0; }
			else { currplayer_gravity = GRAVITY_DOWN; teleport_output = 0; }
		}
	}

	if (currplayer_gravity) { 
		currplayer_y_small += BALL_Title_Jump_Table[teleport_output];
		if (teleport_output < 7) teleport_output++;
	}

	else { 
		currplayer_y_small -= BALL_Title_Jump_Table[teleport_output];
		if (teleport_output < 7) teleport_output++;
	}
*/
	bounds_check();
}

void title_ufo_shit() {
	if (teleport_output <= 0x1A) {
		currplayer_y_small -= UFO_Title_Jump_Table[teleport_output];		//hop hop
		teleport_output++;
	}
	else currplayer_y_small += 4;
	if (!(newrand() & 15)) teleport_output = 0;
	
	if (currplayer_y_small >= 160) {
		currplayer_y_small = 160;
	}		
	else if (currplayer_y_small < 0x08) { currplayer_y_small = 0x08; teleport_output = 0x0E; }
}	
void title_cube_shit() {
	if (teleport_output <= 0x1A) {
		currplayer_y_small -= UFO_Title_Jump_Table[teleport_output];		//hop hop
		teleport_output++;
	}
	else currplayer_y_small += 4;

	if (currplayer_y_small >= (titlemode == 0 ? 160 : 164)) {
		currplayer_y_small = titlemode == 0 ? 160 : 164;
		player_vel_y[0] = 0;
	}		
	
	if (currplayer_y_small == (titlemode == 0 ? 160 : 164) && !(newrand() & 15)) { 
		teleport_output = 0;
		player_vel_y[0] = 1;
	}
	
	else if (currplayer_y_small < 0x08) { currplayer_y_small = 0x08; teleport_output = 0x0E; }
}					

void title_wave_shit() {
	tmp2 = newrand() & 63;
	if (kandoframecnt & 1) { if (tmp2 >= 60) invert_gravity(currplayer_gravity); }
		
	if (currplayer_gravity) currplayer_y_small -= speed;

	else currplayer_y_small += speed;
	bounds_check();
}
void title_mini_wave_shit() {
	tmp2 = newrand() & 63;
	if (kandoframecnt & 1) { if (tmp2 >= 60) invert_gravity(currplayer_gravity); }
		
	if (currplayer_gravity) currplayer_y_small -= (speed << 1);

	else currplayer_y_small += (speed << 1);
	bounds_check();
}

void title_robot_shit() {
	if (kandoframecnt & 1 && !currplayer_gravity) {
		if (!(newrand() & 15)) { tmpi8 = newrand() & 15; currplayer_gravity = GRAVITY_UP; teleport_output = 0; }
	}

	if (currplayer_gravity) {
		if (teleport_output < 0x0C) { currplayer_y_small -= UFO_Title_Jump_Table[teleport_output]; teleport_output++; }
		if (teleport_output == 0x0C && tmpi8 > 0) { currplayer_y_small -= UFO_Title_Jump_Table[teleport_output]; tmpi8--; }
		else { currplayer_y_small -= UFO_Title_Jump_Table[teleport_output]; teleport_output++; if (teleport_output > 0x1A) teleport_output = 0x1A; }
		if (currplayer_y_small >= 160) { currplayer_gravity = GRAVITY_DOWN; tmpi8 = 0; teleport_output = 0; currplayer_y_small = 160; }
	}
					
}
void clear_shit() {
	one_vram_buffer(' ', NTADR_A(4,14));	
	one_vram_buffer(' ', NTADR_A(4,15));	
	one_vram_buffer(' ', NTADR_A(9,14));	
	one_vram_buffer(' ', NTADR_A(9,15));	
	one_vram_buffer(' ', NTADR_A(13,14));	
	one_vram_buffer(' ', NTADR_A(13,15));	
	one_vram_buffer(' ', NTADR_A(18,14));	
	one_vram_buffer(' ', NTADR_A(18,15));	
	one_vram_buffer(' ', NTADR_A(22,14));	
	one_vram_buffer(' ', NTADR_A(22,15));	
	one_vram_buffer(' ', NTADR_A(27,14));	
	one_vram_buffer(' ', NTADR_A(27,15));	
	one_vram_buffer(' ', NTADR_A(13,8));	
	one_vram_buffer(' ', NTADR_A(13,9));	
	one_vram_buffer(' ', NTADR_A(18,8));	
	one_vram_buffer(' ', NTADR_A(18,9));	
	
}




CODE_BANK_POP()
