#pragma code-name(push, "XCD_BANK_03")
#pragma data-name(push, "XCD_BANK_03")
#pragma rodata-name(push, "XCD_BANK_03")

void refreshmenu();
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
	mmc3_set_2kb_chr_bank_0(0xFF);
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
	crossPRGBankJump0(refreshmenu);
	

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
		loop_routine_update();
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
		dec_mouse_timer();
						
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
	mmc3_set_2kb_chr_bank_0(0xFF);
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

		loop_routine_update();

		pal_col(0x0a,color1);
		pal_col(0x0b,color2);
		pal_col(0x09,color3);
		pal_set_update();
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
			else if ((mouse.x >= 0x2E && mouse.x <= 0x3B)) {
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
			else if ((mouse.x >= 0xBE && mouse.x <= 0xCB)) {
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
		dec_mouse_timer();
						
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
	newrand();

	mmc3_set_8kb_chr(MENUBANK);

	set_title_icon();
	set_title_icon();

	
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

	speed = 1;
 	ppu_on_all();
	pad_new[0] = 0;
	pal_fade_to_withmusic(0,4);
	tmp4 = menuselection; ++tmp4;
	tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
	one_vram_buffer('a', tmp5);
	one_vram_buffer('b', addloNOC(tmp5, 1));
	kandoframecnt = 0;
	currplayer_y = 160;
	currplayer_x = 0;
	while (!(pad_new[0] & PAD_START)){
		pal_col(0x11,color3);
		pal_col(0x12,color1);
		pal_col(0x13,color2);
		pal_set_update();


		loop_routine_update();
		 // read the first controller

		newrand();
		newrand();
		newrand();
		if (titlemode != 0xFF) currplayer_x += speed;
		if (currplayer_x >= 0xFB) { 
			roll_new_mode();		
		}
		if (currplayer_x <= 0xF7) {
			switch (titlemode) {
				case 0:		//cube
					oam_spr(currplayer_x, currplayer_y, 1, 0);
					oam_spr(currplayer_x + 8, currplayer_y, 3, 0);
					break;
				case 1:		//UFO
					oam_spr(currplayer_x, currplayer_y, 0x3F, 0);
					oam_spr(currplayer_x + 8, currplayer_y, 0x3F, 0x40);
					break;
				case 2:		//mini cube
					oam_spr(currplayer_x, currplayer_y, 0x35, 0);
					break;
				case 3:		//ship
					oam_spr(currplayer_x, currplayer_y, 0x29, 0);
					oam_spr(currplayer_x + 8, currplayer_y, 0x2B, 0);
					break;
				case 4:		//robot
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:
							oam_spr(currplayer_x-8, currplayer_y, 0x01, 0);
							oam_spr(currplayer_x, currplayer_y, 0x03, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x05, 0);					
							break;
						case 1:
							oam_spr(currplayer_x, currplayer_y, 0x07, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x09, 0);					
							break;
						case 2:
							oam_spr(currplayer_x-8, currplayer_y, 0x01, 0);
							oam_spr(currplayer_x, currplayer_y, 0x0B, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x05, 0);					
							break;
						case 3:
							oam_spr(currplayer_x, currplayer_y, 0x0D, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x09, 0);					
							break;	
					}
					break;
				case 5:		//spider
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:
							oam_spr(currplayer_x - 8, currplayer_y, 0x21, 0);
							oam_spr(currplayer_x, currplayer_y, 0x23, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x25, 0);					
							break;
						case 1:
							oam_spr(currplayer_x - 8, currplayer_y, 0x27, 0);					
							oam_spr(currplayer_x, currplayer_y, 0x29, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x2B, 0);					
							break;
						case 2:
							oam_spr(currplayer_x - 8, currplayer_y, 0x2D, 0);
							oam_spr(currplayer_x, currplayer_y, 0x2F, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x31, 0);					
							break;
						case 3:
							oam_spr(currplayer_x, currplayer_y, 0x33, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x35, 0);					
							break;	
					}
					break;				
				case 6:		//wave
					tmp2 = newrand() & 31;
					if (kandoframecnt & 1) { if (tmp2 >= 30) currplayer_gravity ^= 1; }
						
					if (currplayer_gravity) currplayer_y -= speed;

					else currplayer_y += speed;
					if (currplayer_y >= 160) {
						currplayer_y = 160;
					}		
					else if (currplayer_y < 0x08) currplayer_y = 0x08;
					
					if (currplayer_y == 160 || currplayer_y == 8) {
						oam_spr(currplayer_x, currplayer_y, 0x17, 0);
						oam_spr(currplayer_x + 8, currplayer_y, 0x19, 0);
					}
					else if (currplayer_gravity) {
						oam_spr(currplayer_x, currplayer_y, 0x3B, 0x80);
						oam_spr(currplayer_x + 8, currplayer_y, 0x3D, 0x80);
					}
					else {
						oam_spr(currplayer_x, currplayer_y, 0x3B, 0);
						oam_spr(currplayer_x + 8, currplayer_y, 0x3D, 0);
					}
					break;				
				case 7:		//ball
					if (!(kandoframecnt & 0x07)) ballframe ^= 1;
					if (ballframe) {
						oam_spr(currplayer_x, currplayer_y, 0x3F, 0);
						oam_spr(currplayer_x + 8, currplayer_y, 0x3F, 0x40);
					}
					else {
						oam_spr(currplayer_x, currplayer_y, 0x1B, 0);
						oam_spr(currplayer_x + 8, currplayer_y, 0x1B, 0x40);
					}						
					break;
				case 8:		//swing
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:
							oam_spr(currplayer_x, currplayer_y, 0x31, 0);
							oam_spr(currplayer_x + 8, currplayer_y, 0x33, 0);					
							break;
						case 1:
							oam_spr(currplayer_x, currplayer_y, 0x35, 0);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x37, 0);					
							break;
						case 2:
							oam_spr(currplayer_x, currplayer_y, 0x31, 0);
							oam_spr(currplayer_x + 8, currplayer_y, 0x33, 0);					
							break;
						case 3:
							oam_spr(currplayer_x, currplayer_y, 0x35, 0x80);					
							oam_spr(currplayer_x + 8, currplayer_y, 0x37, 0x80);					
							break;	
					};
					break;
				case 9:		//mini ship
					oam_spr(currplayer_x, currplayer_y, 0x05, 0);
					break;	
				case 10:		//mini ball
					oam_spr(currplayer_x, currplayer_y, 0x0B, 0);
					break;	
				case 11:		//mini wave
					tmp2 = newrand() & 31;
					if (kandoframecnt & 1) { if (tmp2 >= 30) currplayer_gravity ^= 1; }
						
					if (currplayer_gravity) currplayer_y -= speed;

					else currplayer_y += (speed << 1);
					if (currplayer_y >= 160) {
						currplayer_y = 160;
					}		
					else if (currplayer_y < 0x08) currplayer_y = 0x08;
					
					if (currplayer_y == 160 || currplayer_y == 8) {
						oam_spr(currplayer_x, currplayer_y, 0x0D, 0);
						
					}
					else if (currplayer_gravity) {
						oam_spr(currplayer_x, currplayer_y, 0x11, 0x80);
						
					}
					else {
						oam_spr(currplayer_x, currplayer_y, 0x11, 0);
						
					}
					break;	
				case 12:		//mini ufo
					oam_spr(currplayer_x, currplayer_y, 0x19, 0);
					break;		
				case 13:		//mini robot
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:				
							oam_spr(currplayer_x, currplayer_y, 0x13, 0);
							break;
						case 1:				
							oam_spr(currplayer_x, currplayer_y, 0x15, 0);
							break;
						case 2:				
							oam_spr(currplayer_x, currplayer_y, 0x17, 0);
							break;
						case 3:				
							oam_spr(currplayer_x, currplayer_y, 0x15, 0);
							break;
					};
					break;

				case 14:		//mini spider
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:				
							oam_spr(currplayer_x, currplayer_y, 0x21, 0);
							break;
						case 1:				
							oam_spr(currplayer_x, currplayer_y, 0x23, 0);
							break;
						case 2:				
							oam_spr(currplayer_x, currplayer_y, 0x25, 0);
							break;
						case 3:				
							oam_spr(currplayer_x, currplayer_y, 0x27, 0);
							break;
					};
					break;
				case 15:		//mini swing
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 3 ? -3 : 1;
					switch (ballframe) {
						case 0:				
							oam_spr(currplayer_x, currplayer_y, 0x3F, 0);
							break;
						case 1:				
							oam_spr(currplayer_x, currplayer_y, 0x1B, 0);
							break;
						case 2:				
							oam_spr(currplayer_x, currplayer_y, 0x3F, 0);
							break;
						case 3:				
							oam_spr(currplayer_x, currplayer_y, 0x3D, 0);
							break;
					};	
					break;
				case 0xFF:
					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 5 ? -5 : 1;
					switch (ballframe) {
						case 0:
							oam_spr(currplayer_x, currplayer_y, 0x1D, 0);
							oam_spr(currplayer_x + 8, currplayer_y, 0x1D, 0xC0);					
							break;
						case 1:
							oam_spr(currplayer_x, currplayer_y, 0x7D, 0);
							oam_spr(currplayer_x + 8, currplayer_y, 0x7D, 0xC0);					
							break;
						case 2:
							oam_spr(currplayer_x, currplayer_y, 0x1F, 0);
							oam_spr(currplayer_x + 8, currplayer_y, 0x1F, 0xC0);					
							break;
						case 3:
							oam_spr(currplayer_x, currplayer_y, 0x7F, 0);
							oam_spr(currplayer_x + 8, currplayer_y, 0x7F, 0xC0);					
							break;	
						case 4:
							break;	
						case 5:
							roll_new_mode();
							break;
					};
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
		dec_mouse_timer();
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
			oam_clear();
			gameState = 0xFE;
			return;
		}
		if (mouse.left.click) {
			if (mouse.y >= (currplayer_y - 8) && mouse.y <= (currplayer_y + 8)) {
				if (mouse.x >= currplayer_x && mouse.x <= (currplayer_x + 16)) {
					titlemode = 0xFF;		//crossPRGBankJump8(playPCM, 1); 
					ballframe = 0;
				}
			}
				
			
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
			else if ((mouse.y >= 0x8C && mouse.y <= 0x9B)) {
				if (mouse.x >= 0x5E && mouse.x <= 0x6D) {
					menuselection = 2; break;
				}
				else if (mouse.x >= 0x8E && mouse.x <= 0x9D) {
					menuselection = 3; break;
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
		case 0x03: crossPRGBankJump0(settings); return;
		case 0x04: customize_screen(); return;
	};
	
}


void mouse_and_cursor() {
	crossPRGBankJump0(mouse_update);	
	pad_poll(0);
	if (mouse.connected) {
		if (mouse.left.press || mouse.left.click || mouse.right.press || mouse.right.click) mouse_timer = 120;
		if (mouse.right.click) pad_new[0] |= PAD_B;
		if (mouse.right.press) pad[0] |= PAD_B;
		if (!(kandoframecnt & 0x07)) mouseframe += mouseframe == 7 ? -7 : 1;
		if (kandoframecnt > 0xFC) kandoframecnt = 0;
		if (mouse_timer) oam_spr(mouse.x, mouse.y - 1, (0xA1 + (2*mouseframe)), 2);	
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
	crossPRGBankJump0(refreshmenu);
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
	crossPRGBankJump0(refreshmenu);
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

void set_title_icon() {
		if (titlemode < 4) {
			while (tmp7 > 26) {
				tmp7 = newrand() & 31;
			}
			tmp7 = tmp7 * 2;
			tmp7 += 38;
			mmc3_set_2kb_chr_bank_0(tmp7);
		}
		else if (titlemode <= 7) {
			mmc3_set_2kb_chr_bank_0(18);		
		}
		else if (titlemode <= 15) {
			mmc3_set_2kb_chr_bank_0(22);		
		}
}			

void roll_new_mode() {
	speed = (newrand() & 3); 
	if (speed == 0) speed = 1; 
	currplayer_x = 8; 
	currplayer_y = 160; 
	titlemode = newrand() & 15;
//	titlemode = 6; //to test
	ballframe = 0;
	oam_clear();
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

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
