
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

}

void draw_percentage() {

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

void check_if_music_stopped2() {
	if (famistudio_song_speed == 0x80) { music_play(song_menu_theme); }
}


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

	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(song_menu_theme);
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

	//roll_new_mode();
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

		check_if_music_stopped2();

		pal_col(0x11,titlecolor3);
		pal_col(0x12,titlecolor1);
		pal_col(0x13,titlecolor2);
		pal_set_update();

		loop_routine_update();
		 // read the first controller

		newrand();
		newrand();
		newrand();
		//temp values:
		//teleport_output
		//currplayer_gravity
		//tmp2 tmp7
		//tmpi8




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
