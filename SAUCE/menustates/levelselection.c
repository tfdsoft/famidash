void draw_both_progress_bars();

void leveldec();
void levelinc();
void refreshmenu();
void refreshmenu_part2();
void start_the_level();

void check_if_music_stopped();
void dec_mouse_timer();
void loop_routine_update();

const uint8_t xbgmlookuptable[];

#include "charmaps/mainmenu_charmap.h"

const uint8_t lvlselect_irq_table[] = {
	31,
	irqtable_hscroll, 0x00, // item 0x02 gets modified every frame
	149,
	irqtable_hscroll, 0x00,

	irqtable_end // always end with 0xff
};


void levelselection() {
	if (tempplat == 1) { tempplat = 0; options |= platformer; }
	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	disco_sprites = 0;

	pal_bg(oldsplashMenu);
	write_irq_table(lvlselect_irq_table);
	set_irq_ptr(irqTable);
	oam_clear();
	ppu_off();
	pal_bright(0);
	// pal_bg(paletteMenu);
	set_scroll_x(0);
	set_scroll_y(0);  

	#if __VS_SYSTEM
		menutimer = 0;
		if (!coins_inserted) {
			pal_bg(gameoverpalette);
			vram_adr(NAMETABLE_A);
			vram_unrle(gameover); 
			vram_adr(NAMETABLE_B);
			vram_unrle(gameover);
			tmp5 = 200;
			ppu_on_all();		
	//		kandowatchesyousleep = 0;
	//		exitingLevelSelect = 1;
	//		cube_data[0] = 0;
	//		cube_data[1] = 0;
	//		return;
		} else {
	#endif

#if !__VS_SYSTEM
	vram_adr(NAMETABLE_A);
	vram_unrle(level_select_screen); 
	vram_adr(NAMETABLE_B);
	vram_unrle(level_select_screen);
#else
	vram_adr(NAMETABLE_A);
	vram_unrle(game_main_menu); 
	vram_adr(NAMETABLE_B);
	vram_unrle(game_main_menu);
#endif
	memfill(attemptCounter, 0, sizeof(attemptCounter));

	tmp8 = 0xff00;
	edit_irq_table(high_byte(tmp8),2);
	tmp4 = 1;
	crossPRGBankJump0(refreshmenu);
	crossPRGBankJump0(refreshmenu_part2);
	top_triggers = 0;
	triggers = 0;
	triggers_hit[0] = 0;
	triggers_hit[1] = 0;
	triggers_hit[2] = 0;

	// one_vram_buffer(0xb0+kandokidshackTENS, NTADR_A(17,17));
	// one_vram_buffer(0xb0+kandokidshackONES, NTADR_A(18,17));

	cube_rotate[0] = 0;
	cube_rotate[1] = 0;

	#if __VS_SYSTEM
	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(idx8_load(xbgmlookuptable, newrand() & 31));
	#else
	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(xbgmlookuptable[menu_music]);
	#endif
	menuMusicCurrentlyPlaying = 1;

	ppu_on_all();
	drawBarFlag = 2;
	low_byte(tmpA) = 1;
	draw_both_progress_bars();
	
	#if __VS_SYSTEM
	}	// end the else statement
	#endif

	ppu_wait_nmi();
	ppu_wait_nmi();
	pal_fade_to_withmusic(0,4);

	#if __VS_SYSTEM
		if (!coins_inserted) {
			while (tmp5) {
				ppu_wait_nmi();
				music_update();
				tmp5--;
			}
			ppu_off();
			kandowatchesyousleep = 0;
			exitingLevelSelect = 1;
			cube_data[0] = 0;
			cube_data[1] = 0;
			return;
		} else {
	#endif

	while (1){
		loop_routine_update();
		 // read the first controller
		check_if_music_stopped();
		// scroll
		if (tmp4) edit_irq_table(high_byte(tmp8),2);
		else edit_irq_table(low_byte(tmp8),2);
		
		if (low_byte(tmp8) > 0) {
			low_byte(tmp8) -= (low_byte(tmp8) >> 2) + 1;
		}
		
		high_byte(tmp8) = low_byte(tmp8)^0xff;
		
		if (mouse.left_press) {
			if (mouse.y >= 0x6E && mouse.y <= 0x7B) {
				if (mouse.x >= 0x09 && mouse.x <= 0x15) {
					drawBarFlag = 2;
					leveldec();
				}
				else if (mouse.x >= 0xE5 && mouse.x <= 0xEF) {
					drawBarFlag = 2;
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

		#if __VS_SYSTEM
			menutimer++;
			if (menutimer >= 2000) {
				exitingLevelSelect = 1;
				kandowatchesyousleep = 0;
				return;
			}
		#endif

		if (joypad1.press & (PAD_START | PAD_A)){
			start_the_level();
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
			return;
		}

		if (joypad1.press_b){
			exitingLevelSelect = 1;
			kandowatchesyousleep = 0;
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
			return;
		}
		
		if (joypad1.press_right){
			drawBarFlag = 2;
			levelinc();
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
		}
		if (joypad1.press_left){
			drawBarFlag = 2;
			leveldec();
			#if __VS_SYSTEM
				menutimer = 0;
			#endif		
		}

		// NOTE: this is hardcoded. It used to be 0x3F with the old scroll scheme
		if (tmp8 == 0x3B) {
			crossPRGBankJump0(refreshmenu);
			crossPRGBankJump0(refreshmenu_part2);
		}

		draw_both_progress_bars();

		dec_mouse_timer();
	}
	#if __VS_SYSTEM	
	}	// end the else statement
	#endif

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
