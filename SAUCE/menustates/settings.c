void mouse_and_cursor();
void set_settings();

#include "defines/charmap/mainmenu_charmap.h"

#define firstSettingY	3
#define settingCount	9

#define SETTINGS_BTN_2PLAYER	0
#define SETTINGS_BTN_P1CTRLP2	1
#define SETTINGS_BTN_SFX		2
#define SETTINGS_BTN_MUSIC		3
#define SETTINGS_BTN_VFX		4
#define SETTINGS_BTN_CLICKSFX	5
#define SETTINGS_BTN_XTRATRAILS	6
#define SETTINGS_BTN_AUTOCHKPTS	7
#define SETTINGS_BTN_PALFULLSPD	8
#define SETTINGS_BTN_WIPESAVE	9

void state_settings() {
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);

	pal_bg(paletteSettings);

	vram_adr(NAMETABLE_A);
	vram_unrle(settingscreen);

	one_vram_buffer('c', NTADR_A(4, firstSettingY));	// settingvalue is set to 0

	if (framerate == SPEED_NTSC) {
		one_vram_buffer_horz_repeat(0xFF, 27-6+1, NTADR_A(6, firstSettingY+16));
	}

	settingvalue = 0;

	ppu_on_all();
	pal_fade_in();

	while (1) {
		ppu_wait_nmi();
		oam_clear();
		mouse_and_cursor();
		 // read the first controller
		
		if (twoplayer) one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_2PLAYER*2)));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_2PLAYER*2)));

		if (options & oneptwoplayer) one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_P1CTRLP2*2)));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_P1CTRLP2*2)));

		if (options & sfxoff) one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_SFX*2)));
		else one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_SFX*2)));

		if (options & musicoff) one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_MUSIC*2)));
		else one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_MUSIC*2)));

		if (options & jumpsound) one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_CLICKSFX*2)));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_CLICKSFX*2)));

		if (viseffects) one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_VFX*2)));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_VFX*2)));

		if (trails == 1) one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_XTRATRAILS*2)));
		else if (trails == 2) one_vram_buffer('*', NTADR_A(26, firstSettingY+(SETTINGS_BTN_XTRATRAILS*2)));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_XTRATRAILS*2)));

		if (auto_practicepoints) one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_AUTOCHKPTS*2)));
		else one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_AUTOCHKPTS*2)));

		if (framerate != SPEED_NTSC) {
			if (options & fullpalspeed) one_vram_buffer('g', NTADR_A(26, firstSettingY+(SETTINGS_BTN_PALFULLSPD*2)));
			else one_vram_buffer('f', NTADR_A(26, firstSettingY+(SETTINGS_BTN_PALFULLSPD*2)));
		}

		tmp1 = settingvalue;

		if (mouse.left_press) {
			if (mouse.x >= 0x2D && mouse.x <= 0xDD) {
				if (mouse.y >= 0x14 && mouse.y <= 0x1C) {
					settingvalue = 0; set_settings();
				} else if (mouse.y >= 0x24 && mouse.y <= 0x2C) {
					settingvalue = 1; set_settings();
				} else if (mouse.y >= 0x34 && mouse.y <= 0x3C) {
					settingvalue = 2; set_settings();
				} else if (mouse.y >= 0x44 && mouse.y <= 0x4C) {
					settingvalue = 3; set_settings();
				} else if (mouse.y >= 0x54 && mouse.y <= 0x5C) {
					settingvalue = 4; set_settings();
				} else if (mouse.y >= 0x64 && mouse.y <= 0x6C) {
					settingvalue = 5; set_settings();
				} else if (mouse.y >= 0x74 && mouse.y <= 0x7C) {
					settingvalue = 6; set_settings();
				} else if (mouse.y >= 0x84 && mouse.y <= 0x8C) {
					settingvalue = 7; set_settings();
				} else if (mouse.y >= 0x94 && mouse.y <= 0x9C) {
					settingvalue = 8; set_settings();
				}
			}
			if ((mouse.x >= 0x1D && mouse.x <= 0xDD) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				break;
			}

		}

		if (joypad1.press & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == settingCount)
				settingvalue = 0;
			else if (framerate == SPEED_NTSC && settingvalue == SETTINGS_BTN_PALFULLSPD-1)
				settingvalue = SETTINGS_BTN_PALFULLSPD+1;	// Skip full PAL speed on NTSC
			else
				settingvalue++;
		}

		if (joypad1.press & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0)
				settingvalue = settingCount;
			else if (framerate == SPEED_NTSC && settingvalue == SETTINGS_BTN_PALFULLSPD+1)
			 	settingvalue = SETTINGS_BTN_PALFULLSPD-1;	// Skip full PAL speed on NTSC
			else
				settingvalue--;
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
		case SETTINGS_BTN_2PLAYER:
			twoplayer ^= 1; break;
		case SETTINGS_BTN_P1CTRLP2:
			options ^= oneptwoplayer; break;
		case SETTINGS_BTN_SFX:
			options ^= sfxoff; break;
		case SETTINGS_BTN_MUSIC:
			options ^= musicoff; if (options & musicoff) { famistudio_music_stop(); music_update(); } else { music_play(xbgmlookuptable[menu_music]); } break;
		case SETTINGS_BTN_CLICKSFX:
			options ^= jumpsound; break;
		case SETTINGS_BTN_VFX:
			viseffects ^= 1; if (!viseffects) trails = 0; break;
		case SETTINGS_BTN_XTRATRAILS:
			trails = trails == 2 ? 0 : trails + 1; break;					
		case SETTINGS_BTN_AUTOCHKPTS:
			auto_practicepoints ^= 1; break;
		case SETTINGS_BTN_PALFULLSPD:
			options ^= fullpalspeed; break;
		case SETTINGS_BTN_WIPESAVE:
			if (joypad1.a && joypad1.press_start) {
				setdefaultoptions();
				__asm__("JMP ($FFFC)");	// restart the game lmao	
			}
			break;
	}
}	
