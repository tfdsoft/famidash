// Button table
#include "defines/titlescreen_buttons.c"

void loop_routine_update();
void state_credits();

void unrle_bgm1();
void unrle_bgm2();

void check_if_music_stopped2();


// Forward declarations of tables

const uint8_t BG_Table2[];
const uint8_t G_Table2[];

const uint8_t menu_irq_table[];

// Declarations of strings
#include "defines/charmap/mainmenu_charmap.h"	// Set it for the further routine
const char palsystem[] = "FOR PAL SYSTEMS";

void state_menu() {
	oam_clear();

	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);

	// Palette
	if (all_levels_complete == 0xFC) pal_bg(splashMenu2);
	else pal_bg (splashMenu);

	// Tilemap 1
    vram_adr(NAMETABLE_A);
    vram_unrle(game_start_screen);
	vram_adr(NAMETABLE_B);
    vram_unrle(game_start_screen);

    // Tilemap 2
	if (fullRegion == 1) multi_vram_buffer_horz(palsystem, sizeof(palsystem)-1, NTADR_A(9,7));

	// Tilemap 3
	tmp4 = menuselection; ++tmp4;
	tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
	if (menuselection != TITLE_BTN_FUNSETTINGS) {
		one_vram_buffer('a', tmp5);
		one_vram_buffer('b', addloNOC(tmp5, 1));
		one_vram_buffer(' ', NTADR_A(26, 2));
		one_vram_buffer(' ', NTADR_A(26, 3));
	} else {
		one_vram_buffer(0x6F, NTADR_A(26, 2));
		one_vram_buffer(0x7F, NTADR_A(26, 3));
	}

	poweroffcheck = 0xff;

	do {
		discoframe = newrand() & 15;
	} while (discoframe > 11);

	gamemode = 0;
	
	newrand();

	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(song_menu_theme);
	menuMusicCurrentlyPlaying = 1;

	settingvalue = 0;
	
	tmp8 = 0;

	//invisible = 0;

	speed = 1;
	joypad1.press = 0;
	
	write_irq_table(menu_irq_table);
	//edit_irq_table(2, low_byte(tmp8));
	set_irq_ptr(irqTable);
	
	set_scroll_x(0);

 	ppu_on_all();
	
	pal_fade_in();


	kandoframecnt = 0;
	while (!(joypad1.press & (PAD_START | PAD_A))){

		check_if_music_stopped2();

		loop_routine_update();
		 // read the first controller

		newrand();
		newrand();
		newrand();

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
		kandoframecnt++;
		tmp3 = 0;	
		
		low_byte(tmp8) += MSB(CUBE_SPEED_X05(framerate));
		edit_irq_table(low_byte(tmp8), 2); 
	}	

	if (joypad1.select) cursedmusic = 0x40;
	oam_clear();
	ppu_wait_nmi();
	tmp7 = newrand() & 255;

	gameState = STATE_SOUNDTEST;
	return;
		
}

void loop_routine_update() {
	newrand();
	ppu_wait_nmi();
	oam_clear();
}		

void unrle_bgm1() {
	vram_adr(NAMETABLE_A);
	vram_unrle(state_soundtestscreen);  
}
void unrle_bgm2() {
	vram_adr(NAMETABLE_A);
	vram_unrle(SoundQueue);  
}

void check_if_music_stopped2() {
	if (famistudio_song_speed == 0x80) { music_play(song_menu_theme); }
}


const uint8_t BG_Table2[]={
			0x11,	0x12,	0x13,	0x14,	0x15,	0x16,	0x17,
	0x18,	0x19,	0x1A,	0x1B,	0x1C
};

const uint8_t G_Table2[]={
			0x21,	0x22,	0x23,	0x24,	0x25,	0x26,	0x27,
	0x28,	0x29,	0x2A,	0x2B,	0x2C
};

const uint8_t menu_irq_table[] = {
	180,
	irqtable_hscroll, 0x00,

	irqtable_end // always end with 0xff
};
