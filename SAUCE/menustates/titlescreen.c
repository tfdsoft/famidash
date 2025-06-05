// Forward declarations of routines
// Will be replaced during the physics update

#define NTSC_SYS PEEK(0x00)

const char palsystem[] = "FOR PAL SYSTEMS";

extern uint8_t famistudio_song_speed;

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

// Button table
#include "defines/titlescreen_buttons.c"


#if !__THE_ALBUM


void color_picker();

void bounds_check();

void title_cube_shit();
void title_ship_shit();
void title_ball_shit();
void title_ufo_shit();
void title_robot_shit();
void title_wave_shit();
void title_mini_wave_shit();
void title_swing_shit();

void roll_new_mode();
void settings();
void set_title_icon();

// Forward declarations of tables

const uint8_t xbgmlookuptable[];

const uint8_t BG_Table2[];
const uint8_t G_Table2[];
const uint8_t menu_color_table[];

const uint8_t UFO_Title_Jump_Table[];
const uint8_t BALL_Title_Jump_Table[];
const uint8_t shipFrameTable[];
const uint8_t robotFrameTable1[];
const uint8_t robotFrameTable2[];
const uint8_t robotFrameTable3[];
const uint8_t spiderFrameTable1[];
const uint8_t spiderFrameTable2[];
const uint8_t spiderFrameTable3[];
const uint8_t swingFrameTable1[];
const uint8_t swingFrameTable2[];
const uint8_t miniShipFrameTable[];
const uint8_t miniSwingFrameTable[];
const uint8_t mysteryFrameTable[];

const uint8_t menu_irq_table[];


// Declarations of strings
#include "defines/charmap/mainmenu_charmap.h"	// Set it for the further routine


#if __VS_SYSTEM
const unsigned char nocoinstext[] = "INSERT COIN";
const unsigned char coinstext[] = "COINS INSERTED ";
const unsigned char vstext[] = "VS";
#endif


// Title screen modes
#define	TITLEMODE_CUBE		0
#define	TITLEMODE_UFO		1
#define	TITLEMODE_MINICUBE	2
#define	TITLEMODE_SHIP		3
#define	TITLEMODE_ROBOT		4
#define	TITLEMODE_SPIDER	5
#define	TITLEMODE_WAVE		6
#define	TITLEMODE_BALL		7
#define	TITLEMODE_SWING		8
#define	TITLEMODE_MINISHIP	9
#define	TITLEMODE_MINIBALL	10
#define	TITLEMODE_MINIWAVE	11
#define	TITLEMODE_MINIUFO	12
#define	TITLEMODE_MINIROBOT	13
#define	TITLEMODE_MINISPDR	14
#define	TITLEMODE_MINISWING	15
#define	TITLEMODE_META		0xFF

// System-dependent defines
#if __VS_SYSTEM
#define coinCondition coins_inserted
#else
#define coinCondition true
#endif

// Routines start

void state_menu() {
	poweroffcheck = 0xff;
	#if __VS_SYSTEM
		menuselection = TITLE_BTN_LEVELMAIN;
	#endif
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

	#if !__VS_SYSTEM
		#if LEVELSET == 'A'
			if (LEVELCOMPLETE[0] && 
			LEVELCOMPLETE[1] && 
			LEVELCOMPLETE[2] && 
			LEVELCOMPLETE[3] && 
			LEVELCOMPLETE[4] && 
			LEVELCOMPLETE[5] && 
			LEVELCOMPLETE[6] && 
			LEVELCOMPLETE[7] && 
			LEVELCOMPLETE[8] && 
			LEVELCOMPLETE[9] && 
			LEVELCOMPLETE[0x0A] && 
			LEVELCOMPLETE[0x0B] && 
			LEVELCOMPLETE[0x0C]) all_levels_complete = 0xFC;
		#else
			all_levels_complete = 0xFC;
		#endif
	#endif

	
	ppu_off();

	#if !__VS_SYSTEM
	gamemode = 0;
	#endif

	if (all_levels_complete == 0xFC) pal_bg(splashMenu2);
	else pal_bg (splashMenu);
	
	newrand();

	#if __VS_SYSTEM
	color_picker();
	#endif

	mmc3_set_8kb_chr(MENUBANK);

	set_title_icon();
	set_title_icon();

	
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	
	
	
//	set_scroll_x(0);
//    set_scroll_y(0);

	kandowatchesyousleep = 0;

	if (!NTSC_SYS) multi_vram_buffer_horz(palsystem, sizeof(palsystem)-1, NTADR_A(9,7));
	//mmc3_set_prg_bank_1(GET_BANK(state_menu));

	#if __VS_SYSTEM
	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(idx8_load(xbgmlookuptable, newrand() & 31));
	#else
	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(xbgmlookuptable[menu_music]);
	#endif
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
	#if __VS_SYSTEM
		if (coins_inserted) { 
			one_vram_buffer('a', tmp5);
			one_vram_buffer('b', addloNOC(tmp5, 1)); 
		}
	#else
		if (menuselection != TITLE_BTN_FUNSETTINGS) {
			one_vram_buffer('a', tmp5);
			one_vram_buffer('b', addloNOC(tmp5, 1));
		} else {
			one_vram_buffer(0x6F, NTADR_A(26, 2));
			one_vram_buffer(0x7F, NTADR_A(26, 3));
		}
	#endif
	roll_new_mode();
	kandoframecnt = 0;
	teleport_output = 0Xff;
	currplayer_y_small = 160;
	currplayer_x_small = 0;
	titlecolor3 = color3;
	titlecolor2 = color2;
	titlecolor1 = color1;
	#if !__VS_SYSTEM
		if (all_levels_complete != 0xFC) {
			one_vram_buffer(0x19, NTADR_A(27,2));
			one_vram_buffer(0x1A, NTADR_A(28,2));
			one_vram_buffer(0x2D, NTADR_A(27,3));
			one_vram_buffer(0x4D, NTADR_A(28,3));
		} else {
			one_vram_buffer(0x1B, NTADR_A(27,2));
			one_vram_buffer(0x1C, NTADR_A(28,2));
			one_vram_buffer(0x1D, NTADR_A(27,3));
			one_vram_buffer(0x1E, NTADR_A(28,3));
		}
	#endif

	while (!(joypad1.press & (PAD_START | PAD_A)) || !coinCondition){

		#if __VS_SYSTEM

		if (showarrownow) {
			tmp4 = menuselection; ++tmp4;
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			one_vram_buffer('a', tmp5);
			one_vram_buffer('b', addloNOC(tmp5, 1)); 
			showarrownow = 0;
		}
		
/*    DEBUG STUFF
		if (joypad1.press & PAD_SELECT && coins_inserted != 255) { 
			for (tmp2 = 0; tmp2 < 255; tmp2++) {
		
			coins_inserted++; 
			sfx_play(sfx_coin,0); 
		
			}
		}
*/
		multi_vram_buffer_horz(vstext, sizeof(vstext)-1, NTADR_A(25,5));
		if (!coins_inserted) multi_vram_buffer_horz(nocoinstext, sizeof(nocoinstext)-1, NTADR_A(11,9));
		else {
			multi_vram_buffer_horz(coinstext, sizeof(coinstext)-1, NTADR_A(7,9));
			hexToDec(coins_inserted);

			tmp1 = 0;
			
			if (hexToDecOutputBuffer[4]) {
				one_vram_buffer(0xD0+hexToDecOutputBuffer[4], NTADR_A(24,9));
				tmp1++;
			}

			if (hexToDecOutputBuffer[4] | hexToDecOutputBuffer[3]) {
				one_vram_buffer(0xD0+hexToDecOutputBuffer[3], NTADR_A(24+tmp1,9));
				tmp1++;
			}
			
			if (hexToDecOutputBuffer[4] | hexToDecOutputBuffer[3] | hexToDecOutputBuffer[2]) {
				one_vram_buffer(0xD0+hexToDecOutputBuffer[2], NTADR_A(24+tmp1,9));
				tmp1++;
			}

			if (hexToDecOutputBuffer[4] | hexToDecOutputBuffer[3] | hexToDecOutputBuffer[2] | hexToDecOutputBuffer[1]) {
				one_vram_buffer(0xD0+hexToDecOutputBuffer[1], NTADR_A(24+tmp1,9));
				tmp1++;
			}
			one_vram_buffer(0xD0+hexToDecOutputBuffer[0], NTADR_A(24+tmp1,9));			
		}

		#endif

		pal_col(0x11,titlecolor3);
		pal_col(0x12,titlecolor1);
		pal_col(0x13,titlecolor2);
		pal_set_update();

		loop_routine_update();
		 // read the first controller

		newrand();
		newrand();
		newrand();
		if (titlemode != TITLEMODE_META) currplayer_x_small += speed;
		if (currplayer_x_small >= 0xFB) { 
			roll_new_mode();		
		}
		//temp values:
		//teleport_output
		//currplayer_gravity
		//tmp2 tmp7
		//tmpi8



		if (currplayer_x_small <= 0xF7) {
			#if !__VS_SYSTEM
				#define xtra 0
			#else
				#define xtra 3
			#endif

			switch (titlemode) {
				case TITLEMODE_CUBE:
					//oam_spr(currplayer_x_small, currplayer_y_small, 1, 0x20);
					//oam_spr(currplayer_x_small + 8, currplayer_y_small, 3, 0x20);
					title_cube_shit();

					high_byte(player_x[0]) = currplayer_x_small;
					high_byte(player_y[0]) = currplayer_y_small;
					crossPRGBankJump0(drawplayerone);
					break;
				case TITLEMODE_UFO:
					title_ufo_shit();
					
					oam_spr(currplayer_x_small, currplayer_y_small, 0x3F, 0x20+xtra);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, 0x3F, 0x60+xtra);
					break;
				case TITLEMODE_MINICUBE:
					title_cube_shit();
					mini[0] = 1;
					high_byte(player_x[0]) = currplayer_x_small;
					high_byte(player_y[0]) = currplayer_y_small;
					crossPRGBankJump0(drawplayerone);
					mini[0] = 0;
					break;
				case TITLEMODE_SHIP:
					title_ship_shit();

					tmp7 = idx8_load(shipFrameTable, tmpi8 + 3);

					if (currplayer_y_small == 160 && tmp7 < 0x29) tmp7 = 0x29;
					else if (currplayer_y_small == 8 && tmp7 > 0x29) tmp7 = 0x29;
					
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20+xtra);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7 + 2, 0x20+xtra);
					break;
				case TITLEMODE_ROBOT:
					title_robot_shit();
					
					if (!(kandoframecnt & 0x07)) { ++ballframe; ballframe &= 3; }

					if (currplayer_y_small == 160) {
						if (!retro_mode) {
							tmp1 = idx8_load(robotFrameTable1, ballframe & 1);
						} else {
							tmp1 = 0xFF;
						}			
						tmp2 = idx8_load(robotFrameTable2, ballframe | (retro_mode << 2));
						tmp3 = idx8_load(robotFrameTable3, get_Y);
					} else {
						tmp1 = 0xFF;
						tmp2 = 0x0F + (retro_mode * 2); // 0x0F or 0x11
						tmp3 = tmp2 + 2;				// 0x11 or 0x13
					}

					oam_spr(currplayer_x_small-8, currplayer_y_small, tmp1, 0x20+xtra);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x20+xtra);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp3, 0x20+xtra);
					break;
				case TITLEMODE_SPIDER:
//					if (kandoframecnt & 1) {
//						if (!(newrand() & 31)) 	invert_gravity(currplayer_gravity);
//					}

					//if (!currplayer_gravity) {
					currplayer_y_small = 160; tmp7 = 0x20+xtra;
					//}
//					else { currplayer_y_small = 8; tmp7 = 0xA0; }

					if (!(kandoframecnt & 0x07)) { ++ballframe; ballframe &= 3; }

					tmp1 = idx8_load(spiderFrameTable1, ballframe);
					tmp2 = idx8_load(spiderFrameTable2, get_Y);
					tmp3 = idx8_load(spiderFrameTable3, get_Y);

					oam_spr(currplayer_x_small - 8, currplayer_y_small, tmp1, tmp7);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp3, tmp7);
					break;
				case TITLEMODE_WAVE:
					title_wave_shit();

					if (currplayer_y_small == 160 || currplayer_y_small == 8) {
						tmp1 = 0x29;
						tmp2 = 0x20+xtra;
					} else {
						tmp1 = 0x2D;
						if (currplayer_gravity) {
							tmp2 = 0xA0+xtra;
						} else {
							tmp2 = 0x20+xtra;
						}
					}

					oam_spr(currplayer_x_small, currplayer_y_small, tmp1, tmp2);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp1 + 2, tmp2);
					break;
				case TITLEMODE_BALL:
					title_ball_shit();
					
					if (!(kandoframecnt & 0x07)) ballframe ^= 1;

					if (retro_mode && currplayer_gravity) tmp7 = 0xA0+xtra;
					else tmp7 = 0x20+xtra;

					if (ballframe) tmp2 = 0x3F;
					else tmp2 = 0x1B;

					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp2, tmp7 + 0x40);
					break;
				case TITLEMODE_SWING:
					title_swing_shit();

					if (!(kandoframecnt & 0x07)) { ++ballframe; ballframe &= 3; }
					
					tmp2 = idx8_load(swingFrameTable1, ballframe & 1);
					tmp7 = idx8_load(swingFrameTable2, ballframe);

					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp2+2, tmp7);
					break;
				case TITLEMODE_MINISHIP:
					title_ship_shit();

					tmp7 = idx8_load(miniShipFrameTable, tmpi8 + 3);

					if (currplayer_y_small == 160 && tmp7 < 0x05) tmp7 = 0x05;
					else if (currplayer_y_small == 8 && tmp7 > 0x05) tmp7 = 0x05;

					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20+xtra);
					break;
				case TITLEMODE_MINIBALL:
					title_ball_shit();

					if (retro_mode && currplayer_gravity) tmp7 = 0xA0+xtra;
					else tmp7 = 0x20+xtra;

					oam_spr(currplayer_x_small, currplayer_y_small, 0x3D, tmp7);
					break;
				case TITLEMODE_MINIWAVE:
					title_mini_wave_shit();
					
					if (currplayer_y_small == 160 || currplayer_y_small == 8) {
						tmp1 = 0x0D;
						tmp2 = 0x20;
						oam_spr(currplayer_x_small, currplayer_y_small, 0x0D, 0x20+xtra);
					} else {
						tmp1 = 0x11;
						if (currplayer_gravity) {
							tmp2 = 0xA0+xtra;
						} else {
							tmp2 = 0x20+xtra;
						}
					}

					oam_spr(currplayer_x_small, currplayer_y_small, tmp1, tmp2);
					break;
				case TITLEMODE_MINIUFO:
					title_ufo_shit();
					
					oam_spr(currplayer_x_small, currplayer_y_small, 0x19, 0x20+xtra);
					break;
				case TITLEMODE_MINIROBOT:	
					title_robot_shit();

					if (!(kandoframecnt & 0x07)) {
						if (ballframe == 2) ballframe = 0;
						else ++ballframe;
					}

					tmp2 = 0x37 + (ballframe * 2);

					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x20+xtra);
					break;

				case TITLEMODE_MINISPDR:
					/*
					if (kandoframecnt & 1) {
						if (!(newrand() & 31)) 	invert_gravity(currplayer_gravity);
					}

					if (!currplayer_gravity) { 
					*/
					currplayer_y_small = 160; tmp7 = 0x20+xtra; 
					/*
					} else { currplayer_y_small = 8; tmp7 = 0xA0; }
					*/
					
					if (!(kandoframecnt & 0x07)) { ++ballframe; ballframe &= 3; }
					tmp2 = 0x21 + (ballframe * 2);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, tmp7);
					break;
				case TITLEMODE_MINISWING:
					title_swing_shit();

					if (!(kandoframecnt & 0x07)) { ++ballframe; ballframe &= 3; }

					tmp7 = idx8_load(miniSwingFrameTable, ballframe);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20+xtra);
					break;
				case TITLEMODE_META:
					if (!(kandoframecnt & 0x07)) {
						if (ballframe == 5) ballframe = 0;
						else ++ballframe;
					}

					if (ballframe != 5) {
						tmp7 = idx8_load(mysteryFrameTable, ballframe);
						oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20+xtra);
						oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7, 0xE0+xtra);
					} else {
						roll_new_mode();
					}
					break;
			};
		}


		//if ((pad[0] & PAD_LEFT) && (pad[0] & PAD_DOWN) && (pad[0] & PAD_SELECT) && (pad_new[0] & PAD_B)) { color_emphasis(COL_EMP_GREY); color_emphasis(COL_EMP_GREEN); }
		if (!(kandoframecnt & 127)) {
			color_picker();
		}
		dec_mouse_timer();
		tmp3 = 0;	
		
		if (joypad1.press_right && coinCondition) {
			if (menuselection == TITLE_BTN_MAX) menuselection = 0;
			else menuselection++;
			tmp3--;
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
		}
		if (joypad1.press_left && coinCondition) {
			if (menuselection == 0) menuselection = TITLE_BTN_MAX;
			else menuselection--;
			tmp3++;
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
		}

		if (tmp3 && coinCondition) {    // menu selection incremented or decremented
			tmp4 = menuselection; ++tmp4;
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
		#if !__VS_SYSTEM
			if (menuselection != TITLE_BTN_FUNSETTINGS) {
				one_vram_buffer('a', tmp5);
				one_vram_buffer('b', addloNOC(tmp5, 1));
			} else {
				one_vram_buffer(0x6F, NTADR_A(26, 2));
				one_vram_buffer(0x7F, NTADR_A(26, 3));
			}
		#else
			one_vram_buffer('a', tmp5);
			one_vram_buffer('b', addloNOC(tmp5, 1));
		#endif

			tmp4 += tmp3;   // Get the old index
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
		#if !__VS_SYSTEM
			if (tmp4 != TITLE_BTN_FUNSETTINGS+1) {
		#endif
				one_vram_buffer(' ', tmp5);
				one_vram_buffer(' ', addloNOC(tmp5, 1));
		#if !__VS_SYSTEM
			} else {
				one_vram_buffer(' ', NTADR_A(26, 2));
				one_vram_buffer(' ', NTADR_A(26, 3));
			}
		#endif

		}
		#if !__VS_SYSTEM
			if (joypad1.press_select) {
				tmp2 = 0;
				gameState = STATE_CREDITS;
				famistudio_music_stop();
				music_update();
				menuMusicCurrentlyPlaying = 0;
				ppu_wait_nmi();
				return;
			}
		#endif
		low_byte(tmp8) += CUBE_SPEED_X05>>8;
		edit_irq_table(low_byte(tmp8), 2); 

/*
		if (joypad1.press_b) {
			oam_clear();
			gameState = STATE_EXIT;
			return;
		}
*/
		#if !__VS_SYSTEM
		
		if (mouse.left_press) {
			if ((uint8_t)(currplayer_y_small - 8) <= (uint8_t)mouse.y && (uint8_t)(currplayer_y_small + 8) >= (uint8_t)mouse.y) {
				if (mouse.x >= currplayer_x_small && (uint8_t)(currplayer_x_small + 16) >= mouse.x) {
					if (titlemode != TITLEMODE_META) {
						titlemode = TITLEMODE_META;		//crossPRGBankJump8(playPCM, 1); 
						sfx_play(sfx_death,0);
						ballframe = 0;
					}
				}
			}
				
			
			if ((mouse.y >= 0x5E && mouse.y <= 0x7A)) {
				if (mouse.x >= 0x41 && mouse.x <= 0x5A) {
					menuselection = TITLE_BTN_CUSTOMIZE; break;
				} else if (mouse.x >= 0x6F && mouse.x <= 0x8C) {
					menuselection = TITLE_BTN_LEVELMAIN; break;
				} else if (mouse.x >= 0xA1 && mouse.x <= 0xBA) {
					menuselection = TITLE_BTN_LEVELCOMM; break;
				}
			} else if ((mouse.y >= 0x8C && mouse.y <= 0x9B)) {
				if (mouse.x >= 0x46 && mouse.x <= 0x56) {
					menuselection = TITLE_BTN_SOUNDTEST; break;
				} else if (mouse.x >= 0x76 && mouse.x <= 0x86) {
					menuselection = TITLE_BTN_SETTINGS; break;
				} else if (mouse.x >= 0xA6 && mouse.x <= 0xB6) {
					menuselection = TITLE_BTN_INSTRUCTIONS; break;
				}
			} else if ((mouse.y >= 0x0D && mouse.y <= 0x1C)) {
				if (mouse.x >= 0xD6 && mouse.x <= 0xE4) {
					menuselection = TITLE_BTN_FUNSETTINGS; break;
				}
			}
		}	
		#endif


		#if __VS_SYSTEM
			menutimer++;
			if (menutimer >= 2000) {
				menutimer = 0;
				gameState = STATE_CREDITS;
				music_update();
				ppu_off();
				return;
			}			
		#endif
	}	
//	set_scroll_y(0);		does this break anything?
//	set_scroll_x(0);
	oam_clear();
	ppu_wait_nmi();
	tmp7 = newrand() & 255;
	normalorcommlevels = 1;
	switch (menuselection) {
		case TITLE_BTN_LEVELMAIN:
			#if LEVELSET != 'A'
				tmp2 = 0;
				gameState = STATE_PLAYMAIN;
				music_update();
				pal_fade_to_withmusic(4,0);
				ppu_wait_nmi();		
				break;
				// no fall through lmao
			#else
				normalorcommlevels = 0;
				// fall through lmao
			#endif
		case TITLE_BTN_LEVELCOMM:
			POKE(0x2005, 0x00);
			POKE(0x2005, 0x00);
			mmc3_disable_irq(); // reset scroll before playing
			kandowatchesyousleep = 1;

			if (!tmp7) crossPRGBankJump8(playPCM, 1);
			else crossPRGBankJump8(playPCM, 0);

			if (normalorcommlevels) level = LEVEL_COUNT;
			else level = 0;

			levelselection();
			return;

		#if !__VS_SYSTEM
			case TITLE_BTN_SOUNDTEST: gameState = STATE_SOUNDTEST; return;
			case TITLE_BTN_SETTINGS: crossPRGBankJump0(settings); return;
			case TITLE_BTN_INSTRUCTIONS:
				tmp2 = 0;
				gameState = STATE_INSTRUCTIONS;
				music_update();
				pal_fade_to_withmusic(4,0);
				ppu_wait_nmi();		
				break;
			case TITLE_BTN_FUNSETTINGS:
				if (all_levels_complete != 0xFC)
					sfx_play(sfx_invalid, 0);
				else {
					POKE(0x2005, 0x00);
					POKE(0x2005, 0x00);
					mmc3_disable_irq(); // reset scroll before playing
					last_gameState = gameState;
					gameState = STATE_FUNSETTINGS;
					return;
				}
				break;
		#endif
			case TITLE_BTN_CUSTOMIZE: customize_screen(); return;
	};
	
}

void set_title_icon() {
		if (titlemode < TITLEMODE_ROBOT) {	// cube, ufo, mini cube, ship
			do {
				tmp7 = newrand() & 31;
			} while (tmp7 > 26);
			titleicon = tmp7;
			tmp7 = 40 + (tmp7 * 2);
			mmc3_set_2kb_chr_bank_0(retro_mode ? 18 : tmp7);
		} else if (
			(titlemode <= TITLEMODE_BALL && titlemode != TITLEMODE_WAVE) || \
			titlemode == TITLEMODE_MINIROBOT || titlemode == TITLEMODE_MINIBALL	\
		){
			mmc3_set_2kb_chr_bank_0(retro_mode == 0 ? 20 : 22);	
		} else if (titlemode <= TITLEMODE_MINISWING) {
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
	teleport_output = 0xFF;
	tmp7 = titlemode;
	do {
		titlemode = newrand() & 15;
	} while (titlemode > TITLEMODE_MINISHIP || titlemode == tmp7); // 1st: old sanity check? we have more
	if (titlemode >= 8) {
		titlemode = (newrand() & 7) + 8;
	}
	if (retro_mode && (titlemode == TITLEMODE_CUBE || titlemode == TITLEMODE_MINICUBE))
		titlemode = tmp7;

	if (
		titlemode == TITLEMODE_UFO		|| titlemode == TITLEMODE_SHIP		||	\
		titlemode == TITLEMODE_WAVE 	|| titlemode == TITLEMODE_MINISHIP	||	\
		titlemode == TITLEMODE_MINIWAVE	|| titlemode == TITLEMODE_MINIUFO		\
	) {
		while (tmp1 > 0xA0 && tmp1 <= 0x20) {
			tmp1 = newrand() & 0xFF;
		}
		currplayer_y_small = tmp1;
	}
	
	ballframe = 0;
	oam_clear();
#if __VS_SYSTEM
	while (tmp1 >= 53) {
		tmp1 = newrand() & 63;
	}
	while (tmp2 >= 53) {
		tmp2 = newrand() & 63;
	}
	while (tmp3 >= 53) {
		tmp3 = newrand() & 63;
	}
	titlecolor1 = menu_color_table[tmp1];
	titlecolor2 = menu_color_table[tmp2]; //  most of our colors suck
	titlecolor3 = menu_color_table[tmp3];
#endif
	set_title_icon();
}			

void bounds_check() {
	if (currplayer_y_small >= 160) {
		currplayer_y_small = 160;
	} else if (currplayer_y_small < 0x08) currplayer_y_small = 0x08;	
}

void title_ship_shit() {
	if (kandoframecnt & 1) { if (!(newrand() & 7)) invert_gravity(currplayer_gravity); }

	currplayer_y_small -= tmpi8;

	if (currplayer_y_small >= 160) {
		currplayer_y_small = 160;
	} else if (currplayer_y_small < 0x08) { 
		currplayer_y_small = 0x08; 
		currplayer_gravity = GRAVITY_DOWN;
		tmpi8 = 0;
	}					


	if (currplayer_gravity) {
		if (!(kandoframecnt & 7)) { if (tmpi8 < 3) tmpi8++; }
	} else {
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
	} else currplayer_y_small += 4;
	if (!(newrand() & 15)) teleport_output = 0;
	
	if (currplayer_y_small >= 160) {
		currplayer_y_small = 160;
	} else if (currplayer_y_small < 0x08) { currplayer_y_small = 0x08; teleport_output = 0x0E; }
}	
void title_cube_shit() {
	if (teleport_output <= 0x1A) {
		currplayer_y_small -= UFO_Title_Jump_Table[teleport_output];		//hop hop
		teleport_output++;
	} else currplayer_y_small += 4;

	if (currplayer_y_small >= (titlemode == 0 ? 160 : 164)) {
		currplayer_y_small = titlemode == 0 ? 160 : 164;
		player_vel_y[0] = 0;
	}		
	
	if (currplayer_y_small == (titlemode == 0 ? 160 : 164) && !(newrand() & 15)) { 
		teleport_output = 0;
		player_vel_y[0] = 1;
	} else if (currplayer_y_small < 0x08) { currplayer_y_small = 0x08; teleport_output = 0x0E; }
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

void color_picker() {
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
	discoframe++;
	pal_set_update();
	if (discoframe == 12) discoframe = 0;
}

// Tables start


const uint8_t UFO_Title_Jump_Table[]={
	5,
	4,
	3,	3,
	2,	2,	2,	2,
	1,	1,	1,	1,	1,
	0,
	-1,	-1,	-1,	-1,	-1,
	-2,	-2,	-2,	-2,
	-3,	-3,
	-4,
	-5,
};

const uint8_t BALL_Title_Jump_Table[]={
	1,	1,	1,
	2,	2,
	3,	3,
	4,
};
	
const uint8_t menu_color_table[]={
	0x00,	0x01,	0x02,	0x03,	0x04,	0x05,	0x06,	0x07,
	0x08,	0x09,	0x0A,	0x0B,	0x0C,					0x0F,
	0x10,	0x11,	0x12,	0x13,	0x14,	0x15,	0x16,	0x17,
	0x18,	0x19,	0x1A,	0x1B,	0x1C,
	0x20,	0x21,	0x22,	0x23,	0x24,	0x25,	0x26,	0x27,
	0x28,	0x29,	0x2A,	0x2B,	0x2C,
	0x30,	0x31,	0x32,	0x33,	0x34,	0x35,	0x36,	0x37,
	0x38,	0x39,	0x3A,	0x3B,	0x3C
};

const uint8_t shipFrameTable[] = {0x21, 0x21, 0x25, 0x29, 0x2D, 0x31, 0x31};

const uint8_t robotFrameTable1[] = {0x01, 0xFF};
const uint8_t robotFrameTable2[] = {0x03, 0x07, 0x0B, 0x0D, 0x01, 0x07, 0x0B, 0x11};
const uint8_t robotFrameTable3[] = {0x05, 0x09, 0x05, 0x09, 0x03, 0x09, 0x0D, 0x13};

const uint8_t spiderFrameTable1[] = {0x21, 0x27, 0x2D, 0xFF};
const uint8_t spiderFrameTable2[] = {0x23, 0x29, 0x2F, 0x33};
const uint8_t spiderFrameTable3[] = {0x25, 0x2B, 0x31, 0x35};

const uint8_t swingFrameTable1[] = {0x31, 0x35};
#if !__VS_SYSTEM
const uint8_t swingFrameTable2[] = {0x20, 0x20, 0x20, 0xA0};
#else
const uint8_t swingFrameTable2[] = {0x23, 0x23, 0x23, 0xA3};
#endif

const uint8_t miniShipFrameTable[] = {0x01, 0x01, 0x03, 0x05, 0x07, 0x09, 0x09};

const uint8_t miniSwingFrameTable[] = {0x3F, 0x1B, 0x3F, 0x3D};

const uint8_t mysteryFrameTable[] = {0x1D, 0x7D, 0x1F, 0x7F, 0xFF};





#else
	

//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM

CODE_BANK_PUSH("XCD_BANK_03")

void loop_routine_update();
void state_demo();





const unsigned char state_soundtestscreen[468]={
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
	vram_unrle(state_soundtestscreen);  
}
void unrle_bgm2() {
	vram_adr(NAMETABLE_A);
	vram_unrle(SoundQueue);  
}

#include "defines/mainmenu_customize.h"


#include "defines/menunametable.h"
#include "defines/mainmenu_charmap.h"


void check_if_music_stopped2() {
	if (famistudio_song_speed == 0x80) { music_play(song_menu_theme); }
}


void state_menu() {
	poweroffcheck = 0xff;
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();

	do {
		discoframe = newrand() & 15;
	} while (discoframe > 11);

	ppu_off();

	gamemode = 0;

	if (all_levels_complete == 0xFC) pal_bg(splashMenu2);
	else pal_bg (splashMenu);
	
	newrand();

	mmc3_set_8kb_chr(MENUBANK);

	mmc3_set_2kb_chr_bank_1(MOUSEBANK);

	if (!NTSC_SYS) multi_vram_buffer_horz(palsystem, sizeof(palsystem)-1, NTADR_A(9,7));

	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(song_menu_theme);
	menuMusicCurrentlyPlaying = 1;

	settingvalue = 0;
	
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
		
		low_byte(tmp8) += CUBE_SPEED_X05>>8;
		edit_irq_table(low_byte(tmp8), 2); 
	}	

	if (joypad1.select) cursedmusic = 0x40;
	oam_clear();
	ppu_wait_nmi();
	tmp7 = newrand() & 255;
	switch (menuselection) {
		case 0x00:
			gameState = 0x04;
			return;
	};
	
}

void loop_routine_update() {
	newrand();
	ppu_wait_nmi();
	music_update();
	oam_clear();
}		







CODE_BANK_POP()

#endif