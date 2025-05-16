void set_fun_settings();

#include "charmaps/mainmenu_charmap.h"

const unsigned char gameboytext1[];
const unsigned char gameboytext2[];
const unsigned char gameboytext3[];
const unsigned char gameboytext4[];
const unsigned char gameboytext5[];
const unsigned char gameboytext6[];
const unsigned char gameboytext7[];
const unsigned char gameboytext8[];

const unsigned char* const gameboytexts[];

const unsigned char gameboy_text_size[];

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
	one_vram_buffer('c', NTADR_A(4, 5));	// settingvalue is set to 0 by default	
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
				if (mouse.y >= 0x24 && mouse.y <= 0x2C) {
					settingvalue = 0; set_fun_settings();
				}
				else if (mouse.y >= 0x34 && mouse.y <= 0x3C) {
					settingvalue = 1; set_fun_settings();
				}
				else if (mouse.y >= 0x44 && mouse.y <= 0x4C) {
					settingvalue = 2; set_fun_settings();
				}
				else if (mouse.y >= 0x54 && mouse.y <= 0x5C) {
					settingvalue = 3; set_fun_settings();
				}
				else if (mouse.y >= 0x64 && mouse.y <= 0x6C) {
					settingvalue = 4; set_fun_settings();
				}
				else if (mouse.y >= 0x74 && mouse.y <= 0x7C) {
					settingvalue = 5; set_fun_settings();
				}
				else if (mouse.y >= 0x84 && mouse.y <= 0x8C) {
					settingvalue = 6; set_fun_settings();
				}
				else if (mouse.y >= 0x94 && mouse.y <= 0x9C) {
					settingvalue = 7; set_fun_settings();
				}
				else if (mouse.y >= 0xA4 && mouse.y <= 0xAC) {
					settingvalue = 8; set_fun_settings();
				}

			}
			if ((mouse.x >= 0x1D && mouse.x <= 0xDD) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				gameState = last_gameState;
				return;
			}

		}	
		if (invisible) 	one_vram_buffer('g', NTADR_A(26, 5));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 5));	// this is auto optimized by cc65

		if ((options & platformer)) 	one_vram_buffer('g', NTADR_A(26, 7));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 7));	// this is auto optimized by cc65

		if (retro_mode) 	one_vram_buffer('g', NTADR_A(26, 9));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 9));	// this is auto optimized by cc65

		if (discomode) 	one_vram_buffer('g', NTADR_A(26, 11));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 11));	// this is auto optimized by cc65
		
		if (invisblocks) 	one_vram_buffer('g', NTADR_A(26, 13));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 13));	// this is auto optimized by cc65
		
		if (cam_seesaw) 	one_vram_buffer('g', NTADR_A(26, 15));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 15));	// this is auto optimized by cc65

		if (cursedmusic & 0x40) 	one_vram_buffer('g', NTADR_A(26, 19));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 19));	// this is auto optimized by cc65
		
		if (practice_music_sync) 	one_vram_buffer('g', NTADR_A(26, 21));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 21));	// this is auto optimized by cc65


//		if (cursedmusic) 	one_vram_buffer('g', NTADR_A(26, 21));	// believe it or not, 
//		else 	one_vram_buffer('f', NTADR_A(26, 21));	// this is auto optimized by cc65
		
		__A__ = idx16_load_hi_NOC(gameboytexts, gameboy_mode);
		if (__A__) { draw_padded_text(gameboytexts[gameboy_mode & 0x7F], gameboy_text_size[gameboy_mode], 8, NTADR_A(19, 17)); 	one_vram_buffer('g', NTADR_A(26, 17));	}// believe it or not, 
		else { one_vram_buffer_horz_repeat('$', 8, NTADR_A(19, 17)); one_vram_buffer('f', NTADR_A(26, 17)); }



		tmp1 = settingvalue;

		if (joypad1.press & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 8) { settingvalue = 0; }
			else { settingvalue++;  }
		}

		if (joypad1.press & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 8; }
			else { settingvalue--;  }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, 5)+((tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, 5)+((settingvalue<<8)>>2));
		}

		one_vram_buffer('X'-0x1B, NTADR_A(26, 11));
		if (discomode & 0x02) { one_vram_buffer('2' - 0x20, NTADR_A(25, 11)); }
		else if (discomode & 0x04) { one_vram_buffer('3' - 0x20, NTADR_A(25, 11));}
		else if (discomode & 0x08) { one_vram_buffer('4' - 0x20, NTADR_A(25, 11));}
		else if (discomode & 0x10) { one_vram_buffer('5' - 0x20, NTADR_A(25, 11));}
		else if (discomode & 0x01) { one_vram_buffer('1' - 0x20, NTADR_A(25, 11));}
		else { one_vram_buffer(' '-0x01, NTADR_A(25, 11)); one_vram_buffer(0x0F, NTADR_A(26, 11)); }

		if (joypad1.press & (PAD_START | PAD_A)) {
			set_fun_settings();
		}
			
		if (joypad1.press_b) {
			gameState = last_gameState;
			return;
		}

		gameboy_check();

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
		case 0x08: practice_music_sync ^= 0x01; break;
	};
}

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