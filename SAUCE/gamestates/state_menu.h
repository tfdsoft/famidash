#pragma code-name(push, "XCD_BANK_03")
#pragma data-name(push, "XCD_BANK_03")
#pragma rodata-name(push, "XCD_BANK_03")

void state_demo();
void mouse_and_cursor();
void colorinc();
void colordec();
void leveldec();
void levelinc();
void set_settings();
void start_the_level();

const uint8_t loNTAddrTableTitleScreen[]={
    LSB(NTADR_A(9, 11)),	// -1 = 4
    LSB(NTADR_A(15, 11)),	// 0
    LSB(NTADR_A(21, 11)),	// 1 
    LSB(NTADR_A(12, 17)),	// 2
    LSB(NTADR_A(18, 17)),	// 3
    LSB(NTADR_A(9, 11)),	// 4
    LSB(NTADR_A(15, 11))	// 5 = 0
};

const uint8_t hiNTAddrTableTitleScreen[]={
    MSB(NTADR_A(9, 11)),	// -1 = 4
    MSB(NTADR_A(15, 11)),	// 0
    MSB(NTADR_A(21, 11)),	// 1
    MSB(NTADR_A(12, 17)),	// 2
    MSB(NTADR_A(18, 17)),	// 3
    MSB(NTADR_A(9, 11)),	// 4
    MSB(NTADR_A(15, 11))	// 5 = 0
};

const unsigned char* const leveltexts[] = {
  level1text, level2text, NULL, NULL, level5text, NULL, NULL, NULL, NULL, NULL, NULL, levelCtext, levelDtext, NULL, NULL, NULL, NULL, NULL, NULL, NULL, level15text
};
const unsigned char* const leveltexts2[] = {
  level1text2, level2text2, level3text2, level4text2, level5text2, level6text2, level7text2, level8text2, level9text2, levelAtext2, levelBtext2, levelCtext2, levelDtext2, levelEtext2, levelFtext2, level10text2, level11text2, level12text2, level13text2, level14text2, level15text2
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
	0,
	0,
	0,
	0,
	0,
	sizeof(level15text) - 1,
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
	sizeof(levelEtext2) - 1,
	sizeof(levelFtext2) - 1,
	sizeof(level10text2) - 1,
	sizeof(level11text2) - 1,
	sizeof(level12text2) - 1,
	sizeof(level13text2) - 1,
	sizeof(level14text2) - 1,
	sizeof(level15text2) - 1,
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
void __fastcall__ refreshmenu(void) {
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

	// Normal level completeness stuff
		printDecimal(level_completeness_normal[level], 3, '0', ' ', NTADR_A(14, 16)+tmp5);

	// Practice level completeness stuff
		printDecimal(level_completeness_practice[level], 3, '0', ' ', NTADR_A(14, 19)+tmp5);

	//palette stuff
		tmp3 = level % 9;
		pal_col(0,colors_list[tmp3]);
		pal_col(0xE,colors_list[tmp3]);
		pal_set_update();
	//coin stuff
		coins = 0;


	// then in the function...
	// combine all three into a single number from 0 - 7 to represent which coins have been grabbed
		tmp7 = byte((byte(coin3_obtained[level] << 1) | coin2_obtained[level]) << 1) | coin1_obtained[level];
		tmp7 = byte(tmp7<<1) + tmp7;
	// actually draw the coins
		multi_vram_buffer_horz((const char * const)coin_counter+tmp7, 3, NTADR_A(22, 12)+tmp5);

};
void gameboy_check();
void state_menu();
//void bgmtest();


#include "defines/mainmenu_charmap.h"

const uint8_t lvlselect_irq_table[] = {
	31,
	irqtable_hscroll, 0x00, // item 0x02 gets modified every frame
	149,
	irqtable_hscroll, 0x00,

	irqtable_end // always end with 0xff
};
void levelselection() {

	if (normalorcommlevels) level = LEVEL_COUNT;
	else if (level >= LEVEL_COUNT) level -= LEVEL_COUNT;
	
	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(38);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();

	write_irq_table(lvlselect_irq_table);
	set_irq_ptr(irqTable);

	oam_clear();
	ppu_off();
	pal_bright(0);
	// pal_bg(paletteMenu);
	set_scroll_x(0);
	set_scroll_y(0);  
	
	vram_adr(NAMETABLE_A);
	vram_unrle(game_main_menu); 
	vram_adr(NAMETABLE_B);
	vram_unrle(game_main_menu);

	memfill(attemptCounter, 0, sizeof(attemptCounter));

	tmp8 = 0xff00;
	edit_irq_table(high_byte(tmp8),2);
	tmp4 = 1;
	refreshmenu();
	

	// one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
	// one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));

	cube_rotate[0] = 0;
	cube_rotate[1] = 0;

	if (kandotemp == 0) music_play(song_menu_theme);
	kandotemp = 1;

	ppu_on_all();
	ppu_wait_nmi();
	ppu_wait_nmi();
	pal_fade_to_withmusic(0,4);
	
	while (1){
		newrand();
		ppu_wait_nmi();
		music_update();
		mouse_and_cursor();
		 // read the first controller

		// scroll
		if (tmp4) edit_irq_table(high_byte(tmp8),2);
		else edit_irq_table(low_byte(tmp8),2);

		if ((PEEK(0x01) & 1)) 
			low_byte(tmp8) >>= 1;
		high_byte(tmp8) = low_byte(tmp8)^0xff;

		if (mouse.left.click) {
			if (mouse.y >= 0x6E && mouse.y <= 0x7B) {
				if (mouse.x >= 0x09 && mouse.x <= 0x15) {
					leveldec();
				}
				else if (mouse.x >= 0xE5 && mouse.x <= 0xEF) {
					levelinc();				
				}
			}
			if (((mouse.y >= 0x3D && mouse.y <= 0x6C) && (mouse.x >= 0x2D && mouse.x <= 0xCC))) {
				start_the_level();
				return;				
			}
			
		}
		// no longer required because of the menu option 
		//if (twoplayer) one_vram_buffer('d', NTADR_A(31, 2));
		//else one_vram_buffer('e', NTADR_A(31, 2));

		//if (pad[0] & PAD_UP && pad_new[0] & PAD_SELECT) { twoplayer ^= 0x01; sfx_play(sfx_coin, 0); }

		if (pad_new[0] & PAD_START){
			start_the_level();
			return;
		}

		if (pad_new[0] & (PAD_B)){
			kandowatchesyousleep = 0;
			return;
		}
			
			
		if (pad_new[0] & PAD_RIGHT){
			levelinc();
		//	break;
		}
		if (pad_new[0] & PAD_LEFT){
			leveldec();
		}
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
						
	}	

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
	if (pad_new[0] & PAD_UP) {
		crossPRGBankJump0(colorinc);
	}
	if (pad_new[0] & PAD_DOWN) { 
		crossPRGBankJump0(colordec);
	}
	//if ((pad[0] & PAD_SELECT) && (pad_new[0] & PAD_A)) icon_colors[settingvalue] = 0x0D;	
}

void customize_screen() {
	
	settingvalue = 3; 
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	ppu_off();
	pal_bg(paletteMenu);
	pal_col(0x00, 0x00);
	pal_set_update();
	mmc3_set_8kb_chr(MENUICONBANK);
	mmc3_set_2kb_chr_bank_0(38);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	vram_adr(NAMETABLE_A);
	vram_unrle(customizescreen);   	

	TOTALCOINS = 0;
	TOTALSTARS = 0;

	do {
		// TOTALCOINS = TOTALCOINS + coin1_obtained[tmp2] + coin2_obtained[tmp2] + coin3_obtained[tmp2];
		__A__ = tmp2; __asm__("tay");
		__A__ = TOTALCOINS;
		__asm__("clc \n adc %v, y", coin1_obtained);
		__asm__("clc \n adc %v, y", coin2_obtained);
		__asm__("clc \n adc %v, y", coin3_obtained);
		TOTALCOINS = __A__;
		if (LEVELCOMPLETE[tmp2]) TOTALSTARS += stars_list[tmp2];

		tmp2++;
	}
	#ifdef FLAG_ENABLE_TEST_LEVELS
	while (tmp2 < 255);
	#else
	while (tmp2 < LEVEL_COUNT2); 
	#endif

	
	printDecimal(TOTALSTARS, 2, 0xD0, 0xFF, NTADR_A(26,4));
	printDecimal(TOTALCOINS, 2, 0xD0, 0xFF, NTADR_A(26,5));

	one_vram_buffer('h', NTADR_A(13, 8));		
	one_vram_buffer('i', NTADR_A(13, 9));
	one_vram_buffer('f', NTADR_A(18, 8));
	one_vram_buffer('g', NTADR_A(18, 9));

	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	while (1) {
		tmp3 = 0;

		ppu_wait_nmi();
		music_update();

		pal_col(0x0a,color1);
		pal_col(0x0b,color2);
		pal_col(0x09,color3);
		pal_set_update();
		mouse_and_cursor();
		 // read the first controller
	
//mouse stuff

		if (mouse.left.click) {
//icon
			if ((mouse.x >= 0x76 && mouse.x <= 0x83)) { 
				if (mouse.y >= 0x34 && mouse.y <= 0x3C) {
					icon++;
					if (icon > (MAX_ICONS - 1)) icon = 0;				
					//settingvalue = 3;
				}
				else if (mouse.y >= 0x4D && mouse.y <= 0x54) {
					if (icon == 0) icon = MAX_ICONS - 1;
					else icon--;				
					//settingvalue = 3;
				}
//color 2
				else if ((mouse.y >= 0x64 && mouse.y <= 0x6C)) {
					settingvalue = 1;
					crossPRGBankJump0(colorinc);
				}
				else if ((mouse.y >= 0x7D && mouse.y <= 0x83)) {
					settingvalue = 1;			
					crossPRGBankJump0(colordec);
				}

				
			}
//color 1
			if ((mouse.x >= 0x2E && mouse.x <= 0x3B)) {
				if (mouse.y >= 0x63 && mouse.y <= 0x6C) {
					settingvalue = 0;
					crossPRGBankJump0(colorinc);
				}
				else if ((mouse.y >= 0x7D && mouse.y <= 0x83)) {
					settingvalue = 0;			
					crossPRGBankJump0(colordec);
				}
			}
//color3
			if ((mouse.x >= 0xBE && mouse.x <= 0xCB)) {
				if (mouse.y >= 0x63 && mouse.y <= 0x6C) {
					settingvalue = 2;
					crossPRGBankJump0(colorinc);
				}
				else if ((mouse.y >= 0x7D && mouse.y <= 0x83)) {
					settingvalue = 2;			
					crossPRGBankJump0(colordec);
				}
			}
			if ((mouse.x >= 0x35 && mouse.x <= 0xBC) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				return;			//go back
			}
		}
//end mouse stuff
	
		if (!retro_mode) {
			tmp1 = iconTable[icon] + 'a';
			one_vram_buffer(tmp1, NTADR_A(15, 8));		
			one_vram_buffer(++tmp1, NTADR_A(16, 8));		
			one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(15, 9));		
			one_vram_buffer(++tmp1, NTADR_A(16, 9));		
		}
		else {
			one_vram_buffer('a'+0x6E, NTADR_A(15,8));			
			one_vram_buffer('b'+0x6E, NTADR_A(16,8));			
			one_vram_buffer('c'+0x6E, NTADR_A(15,9));			
			one_vram_buffer('d'+0x6E, NTADR_A(16,9));			
		}
		if (settingvalue == 3 && !retro_mode) {
			if (pad_new[0] & PAD_UP) {
				icon++;
				if (icon > (MAX_ICONS - 1)) icon = 0;
			}
			if (pad_new[0] & PAD_DOWN) {
				if (icon == 0) icon = MAX_ICONS - 1;
				else icon--;
			}
		} else if (settingvalue != 3) updateColors();

		if (pad_new[0] & PAD_RIGHT) {
			settingvalue++;
			if (settingvalue == 4) settingvalue = 0;
			tmp3--;
		}
		if (pad_new[0] & PAD_LEFT) {
			if (settingvalue == 0) settingvalue = 3;
			else settingvalue--;
			tmp3++;
		}

		if (tmp3) {
			tmp4 = settingvalue; ++tmp4;
			tmp5 = loNTAddrTableCustomizeScreen[tmp4]|(hiNTAddrTableCustomizeScreen[tmp4]<<8);
			one_vram_buffer('h', tmp5);		
			one_vram_buffer('i', tmp5 + VRAM_OFF(0, 1));
			one_vram_buffer('f', tmp5 = addloNOC(tmp5, VRAM_OFF(5, 0)));
			one_vram_buffer('g', tmp5 + VRAM_OFF(0, 1));

			tmp4 += tmp3;   // Get the old index
			tmp5 = loNTAddrTableCustomizeScreen[tmp4]|(hiNTAddrTableCustomizeScreen[tmp4]<<8);
			one_vram_buffer(' ', tmp5);		
			one_vram_buffer(' ', tmp5 + VRAM_OFF(0, 1));
			one_vram_buffer(' ', tmp5 = addloNOC(tmp5, VRAM_OFF(5, 0)));
			one_vram_buffer(' ', tmp5 + VRAM_OFF(0, 1));
		}

		if (pad_new[0] & PAD_B) {
			return;
		}
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
						
	}
}





#include "defines/mainmenu_charmap.h"

void settings() {
	settingvalue = 0; 
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	ppu_off();
	pal_bg(paletteSettings);
	vram_adr(NAMETABLE_A);
	vram_unrle(settingscreen);   	
	mmc3_set_2kb_chr_bank_0(38);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	ppu_on_all();
	one_vram_buffer('c', NTADR_A(4, 7));	// settingvalue is set to 0 beforehand
	pal_fade_to_withmusic(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		mouse_and_cursor();
		 // read the first controller
		
		if (twoplayer) one_vram_buffer('g', NTADR_A(26, 7));
		else one_vram_buffer('f', NTADR_A(26, 7));

		if (options & oneptwoplayer) one_vram_buffer('g', NTADR_A(26, 9));
		else one_vram_buffer('f', NTADR_A(26, 9));

		if (options & sfxoff) one_vram_buffer('f', NTADR_A(26, 11));
		else one_vram_buffer('g', NTADR_A(26, 11));

		if (options & musicoff) one_vram_buffer('f', NTADR_A(26, 13));
		else one_vram_buffer('g', NTADR_A(26, 13));

		if (options & jumpsound) one_vram_buffer('g', NTADR_A(26, 15));
		else one_vram_buffer('f', NTADR_A(26, 15));

		if (viseffects) one_vram_buffer('g', NTADR_A(26, 17));
		else one_vram_buffer('f', NTADR_A(26, 17));

		if (trails == 1) one_vram_buffer('g', NTADR_A(26, 19));
		else if (trails == 2) one_vram_buffer('*', NTADR_A(26, 19));
		else one_vram_buffer('f', NTADR_A(26, 19));

		tmp1 = settingvalue;

		if (mouse.left.click) {
			if (mouse.x >= 0x2D && mouse.x <= 0xDD) {
				if (mouse.y >= 0x34 && mouse.y <= 0x3C) {
					settingvalue = 0; set_settings();
				}
				else if (mouse.y >= 0x44 && mouse.y <= 0x4C) {
					settingvalue = 1; set_settings();
				}
				else if (mouse.y >= 0x54 && mouse.y <= 0x5C) {
					settingvalue = 2; set_settings();
				}
				else if (mouse.y >= 0x64 && mouse.y <= 0x6C) {
					settingvalue = 3; set_settings();
				}
				else if (mouse.y >= 0x74 && mouse.y <= 0x7C) {
					settingvalue = 4; set_settings();
				}
				else if (mouse.y >= 0x84 && mouse.y <= 0x8C) {
					settingvalue = 5; set_settings();
				}
				else if (mouse.y >= 0x94 && mouse.y <= 0x9C) {
					settingvalue = 6; set_settings();
				}

			}
			if ((mouse.x >= 0x1D && mouse.x <= 0xDD) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				return;
			}

		}	

		if (pad_new[0] & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 7) { settingvalue = 0;  }
			else { settingvalue++;   }
		}

		if (pad_new[0] & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 7;  }
			else { settingvalue--;   }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, 7)+((tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, 7)+((settingvalue<<8)>>2));
		}
		
		if (pad_new[0] & (PAD_A | PAD_START)) {
			set_settings();
		}
		if (options & platformer) {
			twoplayer = 0;
			one_vram_buffer('X',NTADR_A(26,7));
		}
		if (twoplayer) options &= platformer^0xff;		

		if (pad_new[0] & PAD_B) {
			return;
		}
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
				
	}
}


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
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	
	ppu_off();
    pal_bg(splashMenu);

	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(38);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	
	
	
	set_scroll_x(0);
    set_scroll_y(0);

	kandowatchesyousleep = 0;

	if (!NTSC_SYS) multi_vram_buffer_horz(palsystem, sizeof(palsystem)-1, NTADR_A(9,7));
	//mmc3_set_prg_bank_1(GET_BANK(state_menu));

	if (kandotemp == 0) music_play(song_menu_theme);
	kandotemp = 1;

	settingvalue = 0;
	has_practice_point = 0;
	
	// Enable SRAM write
	POKE(0xA001, 0x80);

	write_irq_table(menu_irq_table);
	//edit_irq_table(2, low_byte(tmp8));
	set_irq_ptr(irqTable);
	tmp8 = 0;
	

	kandotemp = 1;
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

	
 	ppu_on_all();
	pad[0] = 0;
	pad_new[0] = 0;
	pal_fade_to_withmusic(0,4);
	tmp4 = menuselection; ++tmp4;
	tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
	one_vram_buffer('a', tmp5);
	one_vram_buffer('b', addloNOC(tmp5, 1));
	kandoframecnt = 0;
	while (!(pad_new[0] & PAD_START)){
		ppu_wait_nmi();
		music_update();
		mouse_and_cursor();
		 // read the first controller

		newrand();
		player_x[0] += 1;
		oam_spr(player_x[0], 160, 1, 0);
		oam_spr(player_x[0] + 8, 160, 3, 0);
		//if ((pad[0] & PAD_LEFT) && (pad[0] & PAD_DOWN) && (pad[0] & PAD_SELECT) && (pad_new[0] & PAD_B)) { color_emphasis(COL_EMP_GREY); color_emphasis(COL_EMP_GREEN); }
		if (!(kandoframecnt & 127)) {
			tmp3 = 0x80 + BG_Table2[discoframe];
			
			if (tmp3 < 0x80) tmp3 += 0x80;
			else if (tmp3 >= 0xF0) tmp3 -= 0x80;
			tmp2 = (tmp3 & 0x3F);  		    
				pal_col(0, tmp2);
				pal_col(0x11, tmp2)
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
			discoframe++;
			if (discoframe == 12) discoframe = 0;
		}
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;		
		tmp3 = 0;
		
		if (pad_new[0] & PAD_RIGHT) {
			if (menuselection == 4) menuselection = 0;
			else menuselection++;
			tmp3--;
		}
		if (pad_new[0] & PAD_LEFT) {
			if (menuselection == 0) menuselection = 4;
			else menuselection--;
			tmp3++;
		}

		if (tmp3) {    // menu selection incremented
			tmp4 = menuselection; ++tmp4;
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			one_vram_buffer('a', tmp5);
			one_vram_buffer('b', addloNOC(tmp5, 1));

			tmp4 += tmp3;   // Get the old index
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			one_vram_buffer(' ', tmp5);
			one_vram_buffer(' ', addloNOC(tmp5, 1));
		}
		if (pad_new[0] & PAD_SELECT) {
				tmp2 = 0;
				gameState = 0;
				famistudio_music_stop();
				music_update();
				kandotemp = 0;
				ppu_wait_nmi();
				return;
		}
		low_byte(tmp8) += CUBE_SPEED_X05>>8;
		edit_irq_table(low_byte(tmp8), 2); 


		if (pad_new[0] & PAD_B) {
			gameState = 0xFE;
			return;
		}
		if (mouse.left.click) {
			if ((mouse.y >= 0x5E && mouse.y <= 0x7A)) {
				if (mouse.x >= 0x41 && mouse.x <= 0x5A) {
					menuselection = 4; break;
				}
				else if (mouse.x >= 0x6F && mouse.x <= 0x8C) {
					menuselection = 0; break;
				}
				else if (mouse.x >= 0xA1 && mouse.x <= 0xBA) {
					menuselection = 1; break;
				}
			}				
			else if ((mouse.y >= 0x8C && mouse.x <= 0x9B)) {
				if (mouse.x >= 0x5E && mouse.x <= 0x6D) {
					menuselection = 2; break;
				}
				else if (mouse.x >= 0x8E && mouse.x <= 0x9D) {
					menuselection = 3; break;
				}
			}
		}	
		
		
	}	
	set_scroll_y(0);
	set_scroll_x(0);
	ppu_wait_nmi();
	tmp7 = newrand() & 255;
	normalorcommlevels = 1;
	switch (menuselection) {
		case 0x00:
			normalorcommlevels = 0;
			// fall through lmao
		case 0x01: 
			POKE(0x2005, 0x00);
			POKE(0x2005, 0x00);
			mmc3_disable_irq(); // reset scroll before playing
			kandowatchesyousleep = 1; 
			if(!tmp7) crossPRGBankJump8(playPCM, 1); 
			else crossPRGBankJump8(playPCM, 0);  
			levelselection(); 
			return;		
		case 0x02: gameState = 4; return;
		case 0x03: settings(); return;
		case 0x04: customize_screen(); return;
	};
	
}


/*
#include "defines/mainmenu_charmap.h"

void bgmtest() {
	
  	famistudio_music_stop();
  	music_update();
	kandotemp=0;
	pal_fade_to(4,0);
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);   	
	ppu_on_all();
	pal_fade_to(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		 // read the first controller
		
		one_vram_buffer(' '-1, NTADR_A(14, 10));
		one_vram_buffer(0xb0+song, NTADR_A(15,10));

		if (settingvalue == 0) {
			one_vram_buffer('c', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
		}		
		else if (settingvalue == 1) {
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer('c', NTADR_A(11, 14));
		}
		if (pad_new[0] & PAD_DOWN) settingvalue ^= 1;
		if (pad_new[0] & PAD_UP) settingvalue ^= 1;
		if (pad_new[0] & PAD_RIGHT && settingvalue == 0) { song++; if (song == song_max) {song = 0;} }
		if (pad_new[0] & PAD_LEFT && settingvalue == 0) { if (song == 0) {song = song_max - 1;} else song--; }
//		if (pad_new[0] & PAD_RIGHT && settingvalue == 1) sfx ++;
		if ((pad_new[0] & PAD_START || pad_new[0] & PAD_A) && settingvalue == 0) music_play(song);
		if (pad_new[0] & PAD_B) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			return;
		}
	}
	
}
*/

void mouse_and_cursor() {
	crossPRGBankJump0(mouse_update);	
	pad_poll(0);
	if (mouse.connected) {
		if (mouse.left.press || mouse.left.click || mouse.right.press || mouse.right.click) mouse_timer = 120;
//		if (mouse.left.press) pad[0] |= PAD_A;
//		if (mouse.left.click) pad_new[0] |= PAD_A;
		if (mouse.right.click) pad_new[0] |= PAD_B;
		if (mouse.right.press) pad[0] |= PAD_B;
		if (!(kandoframecnt & 0x07)) mouseframe += mouseframe == 7 ? -7 : 1;
		if (kandoframecnt > 0xFC) kandoframecnt = 0;
		oam_clear();
		if (mouse_timer) oam_spr(mouse.x, mouse.y - 1, (0xA1 + (2*mouseframe)), 2);	
	}
}

void set_settings() {
	switch (settingvalue) {
		case 0: // oneptwoplayer
			twoplayer ^= 1; break;
		case 1: // oneptwoplayer
			options ^= oneptwoplayer; break;
		case 2: // sfxoff
			options ^= sfxoff; break;
		case 3: // musicoff
			options ^= musicoff; if (options & musicoff) { famistudio_music_stop(); music_update(); } else { music_play(song_menu_theme); } break;
		case 4: // jumpsound
			options ^= jumpsound; break;
		case 5:
			viseffects ^= 1; break;
		case 6:
			trails = trails == 2 ? 0 : trails + 1; break;					
		case 7:
			if (pad[0] & PAD_A && pad_new[0] & PAD_START) {
				setdefaultoptions();
				__asm__("JMP ($FFFC)");	// restart the game lmao	
			}
			break;
	}
}			

void leveldec() {
	--level;
	if (level == 0x0B) level = 0x0A;	//THEORY OF EVERYTHING SKIP
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
	refreshmenu();
}			

void levelinc() {
	++level;
	if (level == 0x0B) level = 0x0C;	//THEORY OF EVERYTHING SKIP
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
	refreshmenu();
}			

void start_the_level() {
	sfx_play(sfx_start_level, 0);
	famistudio_music_stop();
	tmp1 = 0;
	do {
		ppu_wait_nmi();
		music_update();
	} while (++tmp1 < 30);
	gameState = 0x02;
	pal_fade_to(4,0);
	kandotemp = 0;
}			
#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
