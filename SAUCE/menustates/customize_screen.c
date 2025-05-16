void clear_shit();
void colorinc();
void colordec();
void updateColors();

const uint8_t loNTAddrTableCustomizeScreen[];
const uint8_t hiNTAddrTableCustomizeScreen[];

#include "charmaps/mainmenu_customize.h"

void customize_screen() {
#define prev_icon tmp8
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
	#if __VS_SYSTEM
	menutimer = 0;
	#endif
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

	
	printDecimal(kandokidshack2, 2, 0xD0, 0xFF, NTADR_A(26,4));
	printDecimal(kandokidshack, 2, 0xD0, 0xFF, NTADR_A(26,5));

	one_vram_buffer('h', NTADR_A(13, 8));		
	one_vram_buffer('i', NTADR_A(13, 9));
	one_vram_buffer('f', NTADR_A(18, 8));
	one_vram_buffer('g', NTADR_A(18, 9));
	prev_icon = !icon;
	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	tmp1 = iconTable[icon] + 'a';
	one_vram_buffer(tmp1, NTADR_A(15, 8));
	one_vram_buffer(++tmp1, NTADR_A(16, 8));
	one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(15, 9));
	one_vram_buffer(++tmp1, NTADR_A(16, 9));
	prev_icon = icon;	
	while (1) {
		tmp3 = 0;
		check_if_music_stopped();
		loop_routine_update();

		pal_col(0x0a,color1);
		pal_col(0x0b,color2);
		pal_col(0x09,color3);
		pal_set_update();
		 // read the first controller
	
//mouse stuff

	#if !__VS_SYSTEM
		if (mouse.left_press || (mouse.left && hold_timer >= 15)) {
//icon
			if ((mouse.x >= 0x76 && mouse.x <= 0x83)) { 
				if (mouse.y >= 0x34 && mouse.y <= 0x3C) {
					icon++;
					if (icon > (MAX_ICONS - 1)) icon = 0;				
					settingvalue = 3;
					hold_timer = 0;					
					clear_shit();
				}
				else if (mouse.y >= 0x4D && mouse.y <= 0x54) {
					if (icon == 0) icon = MAX_ICONS - 1;
					else icon--;				
					settingvalue = 3;
					hold_timer = 0;					
					clear_shit();
					
				}
//color 2
				else if ((mouse.y >= 0x64 && mouse.y <= 0x6C)) {
					settingvalue = 1;
					colorinc();
					hold_timer = 0;					
					clear_shit();
					
				}
				else if ((mouse.y >= 0x7D && mouse.y <= 0x83)) {
					settingvalue = 1;			
					colordec();
					hold_timer = 0;					
					clear_shit();
					
				}

				
			}
//color 1
			else if ((mouse.x >= 0x2E && mouse.x <= 0x3B)) {
				if (mouse.y >= 0x63 && mouse.y <= 0x6C) {
					settingvalue = 0;
					colorinc();
					hold_timer = 0;					
					clear_shit();
					
				}
				else if ((mouse.y >= 0x7D && mouse.y <= 0x83)) {
					settingvalue = 0;			
					colordec();
					hold_timer = 0;					
					clear_shit();
					
				}
			}
//color3
			else if ((mouse.x >= 0xBE && mouse.x <= 0xCB)) {
				if (mouse.y >= 0x63 && mouse.y <= 0x6C) {
					settingvalue = 2;
					colorinc();
					hold_timer = 0;					
					clear_shit();
					
				}
				else if ((mouse.y >= 0x7D && mouse.y <= 0x83)) {
					settingvalue = 2;			
					colordec();
					hold_timer = 0;					
					clear_shit();
					
				}
			}
			if ((mouse.x >= 0x35 && mouse.x <= 0xBC) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				return;			//go back
			}
		}
	#endif
//end mouse stuff
		if (!retro_mode) {
			if (icon != prev_icon) {
				tmp1 = iconTable[icon] + 'a';
				one_vram_buffer(tmp1, NTADR_A(15, 8));
				one_vram_buffer(++tmp1, NTADR_A(16, 8));
				one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(15, 9));
				one_vram_buffer(++tmp1, NTADR_A(16, 9));
				prev_icon = icon;
			}
		} else {
			if (prev_icon) {
				one_vram_buffer('a'+0x6E, NTADR_A(15,8));
				one_vram_buffer('b'+0x6E, NTADR_A(16,8));
				one_vram_buffer('c'+0x6E, NTADR_A(15,9));
				one_vram_buffer('d'+0x6E, NTADR_A(16,9));
				prev_icon = 0;
			}
		}
		if (settingvalue == 3 && !retro_mode) {
			if (joypad1.press_up || (joypad1.up && hold_timer >= 15)) {
				icon++;
				#if __VS_SYSTEM
				menutimer = 0;
				#endif
				if (icon > (MAX_ICONS - 1)) icon = 0;
				hold_timer = 0;
			}
			if (joypad1.press_down || (joypad1.down && hold_timer >= 15)) {
				#if __VS_SYSTEM
				menutimer = 0;
				#endif
				if (icon == 0) icon = MAX_ICONS - 1;
				else icon--;
				hold_timer = 0;				
			}
		} else if (settingvalue != 3) updateColors();

		if (joypad1.press_right) {
			settingvalue++;
			#if __VS_SYSTEM
			menutimer = 0;
			#endif
			if (settingvalue == 4) settingvalue = 0;
			tmp3--;
		}
		if (joypad1.press_left) {
			if (settingvalue == 0) settingvalue = 3;
			else settingvalue--;
			#if __VS_SYSTEM
			menutimer = 0;
			#endif
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

		if (joypad1.press_b) {
			return;
		}
		dec_mouse_timer();
		hold_timer++;
		#if __VS_SYSTEM
		menutimer++;
		if (menutimer >= 2000) return;						
		#endif
	}
#undef prev_icon
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

void updateColors() {
	if (joypad1.press_up) {
		colorinc();
	}
	if (joypad1.press_down) { 
		colordec();
	}
	//if ((pad[0] & PAD_SELECT) && (pad_new[0] & PAD_A)) icon_colors[settingvalue] = 0x0D;	
}

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