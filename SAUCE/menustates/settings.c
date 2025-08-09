void mouse_and_cursor();
void set_settings();

#include "defines/charmap/mainmenu_charmap.h"

#define firstSettingY	5
#define settingCount	8

void state_settings() {
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);

	pal_bg(paletteSettings);

	vram_adr(NAMETABLE_A);
	vram_unrle(settingscreen);
	one_vram_buffer('c', NTADR_A(4, firstSettingY));	// settingvalue is set to 0

	settingvalue = 0;

	ppu_on_all();
	pal_fade_in();

	while (1) {
		ppu_wait_nmi();
		oam_clear();
		mouse_and_cursor();
		 // read the first controller
		
		if (twoplayer) one_vram_buffer('g', NTADR_A(26, firstSettingY));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY));

		if (options & oneptwoplayer) one_vram_buffer('g', NTADR_A(26, firstSettingY+2));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+2));

		if (options & sfxoff) one_vram_buffer('f', NTADR_A(26, firstSettingY+4));
		else one_vram_buffer('g', NTADR_A(26, firstSettingY+4));

		if (options & musicoff) one_vram_buffer('f', NTADR_A(26, firstSettingY+6));
		else one_vram_buffer('g', NTADR_A(26, firstSettingY+6));

		if (options & jumpsound) one_vram_buffer('g', NTADR_A(26, firstSettingY+8));
		else one_vram_buffer('f', NTADR_A(26, 13));

		if (viseffects) one_vram_buffer('g', NTADR_A(26, firstSettingY+10));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+10));

		if (trails == 1) one_vram_buffer('g', NTADR_A(26, firstSettingY+12));
		else if (trails == 2) one_vram_buffer('*', NTADR_A(26, firstSettingY+12));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+12));

		if (auto_practicepoints) one_vram_buffer('g', NTADR_A(26, firstSettingY+14));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+14));

		tmp1 = settingvalue;

		if (mouse.left_press) {
			if (mouse.x >= 0x2D && mouse.x <= 0xDD) {
				if (mouse.y >= 0x24 && mouse.y <= 0x2C) {
					settingvalue = 0; set_settings();
				}
				else if (mouse.y >= 0x34 && mouse.y <= 0x4C) {
					settingvalue = 1; set_settings();
				}
				else if (mouse.y >= 0x44 && mouse.y <= 0x4C) {
					settingvalue = 2; set_settings();
				}
				else if (mouse.y >= 0x54 && mouse.y <= 0x5C) {
					settingvalue = 3; set_settings();
				}
				else if (mouse.y >= 0x64 && mouse.y <= 0x6C) {
					settingvalue = 4; set_settings();
				}
				else if (mouse.y >= 0x74 && mouse.y <= 0x7C) {
					settingvalue = 5; set_settings();
				}
				else if (mouse.y >= 0x84 && mouse.y <= 0x8C) {
					settingvalue = 6; set_settings();
				}
				else if (mouse.y >= 0x94 && mouse.y <= 0x9C) {
					settingvalue = 7; set_settings();
				}
			}
			if ((mouse.x >= 0x1D && mouse.x <= 0xDD) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				break;
			}

		}

		if (joypad1.press & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == settingCount) { settingvalue = 0;  }
			else { settingvalue++;   }
		}

		if (joypad1.press & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = settingCount;  }
			else { settingvalue--;   }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, firstSettingY)+(		(tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, firstSettingY)+((settingvalue<<8)>>2));
		}
		
		if (joypad1.press & (PAD_A | PAD_START)) {
			set_settings();
		}
		if (options & platformer) {
			twoplayer = 0;
			one_vram_buffer('X',NTADR_A(26,7));
		}
		if (twoplayer) options &= ~platformer;		

		if (joypad1.press_b) {
			break;
		}
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
				
	}
	gameState = STATE_MENU;
}

const uint8_t xbgmlookuptable[];

void set_settings() {
	switch (settingvalue) {
		case 0: // oneptwoplayer
			twoplayer ^= 1; break;
		case 1: // oneptwoplayer
			options ^= oneptwoplayer; break;
		case 2: // sfxoff
			options ^= sfxoff; break;
		case 3: // musicoff
			options ^= musicoff; if (options & musicoff) { famistudio_music_stop(); music_update(); } else { music_play(xbgmlookuptable[menu_music]); } break;
		case 4: // jumpsound
			options ^= jumpsound; break;
		case 5:
			viseffects ^= 1; if (!viseffects) trails = 0; break;
		case 6:
			trails = trails == 2 ? 0 : trails + 1; break;					
		case 7:
			auto_practicepoints ^= 1; break;
		case 8:
			if (joypad1.a && joypad1.press_start) {
				setdefaultoptions();
				__asm__("JMP ($FFFC)");	// restart the game lmao	
			}
			break;
	}
}	
