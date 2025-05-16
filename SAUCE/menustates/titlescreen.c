#if __VS_SYSTEM
void color_picker();
#endif

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

const uint8_t xbgmlookuptable[];

#if !__VS_SYSTEM
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
#else
const uint8_t loNTAddrTableTitleScreen[]={
    LSB(NTADR_A(9, 11)),	// -1 = 4
    LSB(NTADR_A(15, 11)),	// 0
    LSB(NTADR_A(21, 11)),	// 1 
    LSB(NTADR_A(15, 17)),	// 2
    LSB(NTADR_A(18, 17)),	// 3
    LSB(NTADR_A(27, 1)),	// 4
    LSB(NTADR_A(9, 11)),	// 5 = 0
    LSB(NTADR_A(15, 11))	// 5 = 0
};

const uint8_t hiNTAddrTableTitleScreen[]={
    MSB(NTADR_A(9, 11)),	// -1 = 4
    MSB(NTADR_A(15, 11)),	// 0
    MSB(NTADR_A(21, 11)),	// 1
    MSB(NTADR_A(15, 17)),	// 2
    MSB(NTADR_A(18, 17)),	// 3
    MSB(NTADR_A(27, 1)),	// 4
    MSB(NTADR_A(9, 11)),	// 5 = 0
    MSB(NTADR_A(15, 11))	// 5 = 0
};
#endif

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

#include "charmaps/mainmenu_charmap.h"

const char palsystem[] = "FOR PAL SYSTEMS";
#define NTSC_SYS PEEK(0x00)




const uint8_t menu_irq_table[] = {
	180,
	irqtable_hscroll, 0x00,

	irqtable_end // always end with 0xff
};

#if __VS_SYSTEM

const unsigned char nocoinstext[] = "INSERT COIN";
const unsigned char coinstext[] = "COINS INSERTED ";
const unsigned char vstext[] = "VS";

#endif
void state_menu() {
	poweroffcheck = 0xff;
	#if __VS_SYSTEM
		menuselection = 0;
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
		if (menuselection != 5) {
			one_vram_buffer('a', tmp5);
			one_vram_buffer('b', addloNOC(tmp5, 1));
			one_vram_buffer(' ', NTADR_A(26, 2));
			one_vram_buffer(' ', NTADR_A(26, 3));
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
		}
		else {
			one_vram_buffer(0x1B, NTADR_A(27,2));
			one_vram_buffer(0x1C, NTADR_A(28,2));
			one_vram_buffer(0x1D, NTADR_A(27,3));
			one_vram_buffer(0x1E, NTADR_A(28,3));
		}
	#endif

	while (!(joypad1.press & (PAD_START | PAD_A))
		#if __VS_SYSTEM
			|| !coins_inserted
		#endif
		){

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
					
				#if !__VS_SYSTEM					
					oam_spr(currplayer_x_small, currplayer_y_small, 0x3F, 0x20);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, 0x3F, 0x60);
				#else
					oam_spr(currplayer_x_small, currplayer_y_small, 0x3F, 0x23);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, 0x3F, 0x63);
				#endif
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
						
				#if !__VS_SYSTEM
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7 + 2, 0x20);
				#else
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x23);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7 + 2, 0x23);
				#endif					
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
				#if !__VS_SYSTEM
					oam_spr(currplayer_x_small-8, currplayer_y_small, tmp1, 0x20);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x20);					
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp3, 0x20);					
				#else
					oam_spr(currplayer_x_small-8, currplayer_y_small, tmp1, 0x23);
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x23);					
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp3, 0x23);					
				#endif					
					break;
				case 5:		//spider
//					if (kandoframecnt & 1) {
//						if (!(newrand() & 31)) 	invert_gravity(currplayer_gravity);
//					}

					//if (!currplayer_gravity) { 
				#if !__VS_SYSTEM
					currplayer_y_small = 160; tmp7 = 0x20; 
				#else
					currplayer_y_small = 160; tmp7 = 0x23; 
				#endif				
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
						#if !__VS_SYSTEM
						tmp2 = 0x20;
						#else
						tmp2 = 0x23;
						#endif
					}
					else if (currplayer_gravity) {
						tmp1 = 0x2D;
						#if !__VS_SYSTEM
						tmp2 = 0xA0;
						#else
						tmp2 = 0xA3;
						#endif
					}
					else {
						tmp1 = 0x2D;
						#if !__VS_SYSTEM
						tmp2 = 0x20;
						#else
						tmp2 = 0x23;
						#endif
					}
					oam_spr(currplayer_x_small, currplayer_y_small, tmp1, tmp2);
					oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp1 + 2, tmp2);
					break;				
				case 7:		//ball
					title_ball_shit();
					
					if (!(kandoframecnt & 0x07)) ballframe ^= 1;

				#if !__VS_SYSTEM
					if (retro_mode && currplayer_gravity) tmp7 = 0xA0;
					else tmp7 = 0x20;
				#else
					if (retro_mode && currplayer_gravity) tmp7 = 0xA3;
					else tmp7 = 0x23;
				#endif					

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
							#if !__VS_SYSTEM
							tmp7 = 0x20;
							#else
							tmp7 = 0x23;
							#endif
							break;
						case 1:
							tmp2 = 0x35;
							#if !__VS_SYSTEM
							tmp7 = 0x20;
							#else
							tmp7 = 0x23;
							#endif
							break;
						case 2:
							tmp2 = 0x31;
							#if !__VS_SYSTEM
							tmp7 = 0x20;
							#else
							tmp7 = 0x23;
							#endif
						case 3:
							tmp2 = 0x35;
							#if !__VS_SYSTEM
							tmp7 = 0xA0;
							#else
							tmp7 = 0xA3;
							#endif
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

				#if !__VS_SYSTEM
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);
				#else
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x23);
				#endif					

					break;	
				case 10:		//mini ball
					title_ball_shit();
				#if !__VS_SYSTEM
					if (retro_mode && currplayer_gravity) tmp7 = 0xA0;
					else tmp7 = 0x20;					
				#else
					if (retro_mode && currplayer_gravity) tmp7 = 0xA3;
					else tmp7 = 0x23;					
				#endif					
					oam_spr(currplayer_x_small, currplayer_y_small, 0x3D, tmp7);
					break;	
				case 11:		//mini wave
					title_mini_wave_shit();
					
					if (currplayer_y_small == 160 || currplayer_y_small == 8) {
						tmp1 = 0x0D;
						tmp2 = 0x20;
					#if !__VS_SYSTEM
						oam_spr(currplayer_x_small, currplayer_y_small, 0x0D, 0x20);
					#else
						oam_spr(currplayer_x_small, currplayer_y_small, 0x0D, 0x23);
					#endif						
					}
					else if (currplayer_gravity) {
						tmp1 = 0x11;
						#if !__VS_SYSTEM
						tmp2 = 0xA0;
						#else
						tmp2 = 0xA3;
						#endif
					}
					else {
						tmp1 = 0x11;
						#if !__VS_SYSTEM
						tmp2 = 0x20;
						#else
						tmp2 = 0x23;
						#endif
					}
					oam_spr(currplayer_x_small, currplayer_y_small, tmp1, tmp2);
					break;	
				case 12:		//mini ufo
					title_ufo_shit();
					
					#if !__VS_SYSTEM
					oam_spr(currplayer_x_small, currplayer_y_small, 0x19, 0x20);
					#else
					oam_spr(currplayer_x_small, currplayer_y_small, 0x19, 0x23);
					#endif
					break;		
				case 13:		//mini robot
					
					title_robot_shit();

					if (!(kandoframecnt & 0x07)) ballframe += ballframe == 2 ? -2 : 1;

					tmp2 = 0x37 + (ballframe * 2);

					#if !__VS_SYSTEM
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x20);
					#else
					oam_spr(currplayer_x_small, currplayer_y_small, tmp2, 0x23);
					#endif
					break;

				case 14:		//mini spider
				/*
					if (kandoframecnt & 1) {
						if (!(newrand() & 31)) 	invert_gravity(currplayer_gravity);
					}

					if (!currplayer_gravity) { 
					*/
					#if !__VS_SYSTEM
					currplayer_y_small = 160; tmp7 = 0x20; 
					#else
					currplayer_y_small = 160; tmp7 = 0x23; 
					#endif
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
					#if !__VS_SYSTEM
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);
					#else
					oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x23);
					#endif
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
					#if !__VS_SYSTEM
						oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x20);
						oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7, 0xE0);					
					#else
						oam_spr(currplayer_x_small, currplayer_y_small, tmp7, 0x23);
						oam_spr(currplayer_x_small + 8, currplayer_y_small, tmp7, 0xE3);	
					#endif						
					}
					break;					
			};
		}


		//if ((pad[0] & PAD_LEFT) && (pad[0] & PAD_DOWN) && (pad[0] & PAD_SELECT) && (pad_new[0] & PAD_B)) { color_emphasis(COL_EMP_GREY); color_emphasis(COL_EMP_GREEN); }
		if (!(kandoframecnt & 127)) {
		#if !__VS_SYSTEM
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
		#else
			color_picker();
		#endif
		}
		dec_mouse_timer();
		tmp3 = 0;	
		
		if (
			joypad1.press_right 
		#if __VS_SYSTEM
			&& coins_inserted
		#endif
			) {
			#if !__VS_SYSTEM
				if (menuselection == 6) menuselection = 0;
			#else
				if (menuselection == 5) menuselection = 0;
				else if (menuselection == 1) { menuselection = 5; tmp3--; tmp3--; tmp3--; }
			#endif
			else menuselection++;
			tmp3--;
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
		}
		if (
			joypad1.press_left
		#if __VS_SYSTEM
			&& coins_inserted
		#endif
			) {
			#if !__VS_SYSTEM
				if (menuselection == 0) menuselection = 6;
			#else
				if (menuselection == 0) menuselection = 5;
				else if (menuselection == 5) { menuselection = 1; tmp3++; tmp3++; tmp3++; }
			#endif
			else menuselection--;
			tmp3++;
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
		}

		if (
			tmp3
		#if __VS_SYSTEM
			&& coins_inserted
		#endif
			) {    // menu selection incremented
			tmp4 = menuselection; ++tmp4;
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			#if !__VS_SYSTEM
			if (menuselection != 5) {
			#else
			if (menuselection != 4) {
			#endif
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
		#if !__VS_SYSTEM
		if (joypad1.press_select) {
				tmp2 = 0;
				gameState = 0;
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
			gameState = 0xFE;
			return;
		}
*/
		#if !__VS_SYSTEM
		
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
					menuselection = 6; break;
				}
				else if (mouse.x >= 0x6F && mouse.x <= 0x8C) {
					menuselection = 0; break;
				}
				else if (mouse.x >= 0xA1 && mouse.x <= 0xBA) {
					menuselection = 1; break;
				}
			}				
			else if ((mouse.y >= 0x8C && mouse.y <= 0x9B)) {
				if (mouse.x >= 0x46 && mouse.x <= 0x56) {
					menuselection = 2; break;
				}
				else if (mouse.x >= 0x76 && mouse.x <= 0x86) {
					menuselection = 3; break;
				}				
				else if (mouse.x >= 0xA6 && mouse.x <= 0xB6) {
					menuselection = 4; break;
				}				
			}
			else if ((mouse.y >= 0x0D && mouse.y <= 0x1C)) {
				if (mouse.x >= 0xD6 && mouse.x <= 0xE4) {
					menuselection = 5; break;
				}
			}
		}	
		#endif


		#if __VS_SYSTEM
			menutimer++;
			if (menutimer >= 2000) {
				menutimer = 0;
				gameState = 0;
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
		case 0x00:
			#if LEVELSET == 'A'
			normalorcommlevels = 0;
			// fall through lmao
			#else
			tmp2 = 0;
			gameState = 0xF2;
			music_update();
			pal_fade_to_withmusic(4,0);
			ppu_wait_nmi();		
			break;
			// no fall through lmao
			#endif
		case 0x01: 
			POKE(0x2005, 0x00);
			POKE(0x2005, 0x00);
			mmc3_disable_irq(); // reset scroll before playing
			kandowatchesyousleep = 1; 
			if(!tmp7) crossPRGBankJump8(playPCM, 1); 
			else crossPRGBankJump8(playPCM, 0);  
			if (normalorcommlevels) level = LEVEL_COUNT;
			else level = 0;
			levelselection(); 
			return;		
		case 0x02: gameState = 4; return;
		#if __VS_SYSTEM
			case 0x03:
			case 0x04:
				break;
			case 0x05: customize_screen(); return;
		#else
			case 0x03: crossPRGBankJump0(settings); return;
			case 0x04: 
				tmp2 = 0;
				gameState = 0xF1;
				music_update();
				pal_fade_to_withmusic(4,0);
				ppu_wait_nmi();		
				break;
			case 0x05: 
				if (all_levels_complete != 0xFC) { sfx_play(sfx_invalid, 0); }
				else {
					POKE(0x2005, 0x00);
					POKE(0x2005, 0x00);
					mmc3_disable_irq(); // reset scroll before playing
					last_gameState = gameState;
					gameState = 0xF0; // fun settings gamestate
					return;
				}
				break;
			case 0x06: customize_screen(); return;
		#endif
	};
	
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

#if __VS_SYSTEM
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
#endif
