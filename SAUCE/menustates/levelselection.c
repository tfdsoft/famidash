void draw_both_progress_bars();

void leveldec();
void levelinc();
void refreshmenu();
void start_the_level();

void check_if_music_stopped();
void dec_mouse_timer();
void loop_routine_update();

const uint8_t xbgmlookuptable[];
const uint8_t lvlselect_irq_table[];

#include "defines/charmap/mainmenu_charmap.h"

void state_levelselect() {
	oam_clear();

	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);

	#if __VS_SYSTEM
		menutimer = 0;
	#endif

	pal_bg(oldsplashMenu);

	if (tempplat == 1) { tempplat = 0; options |= platformer; }
	slowmode = 0;
	disco_sprites = 0;
	
	vram_adr(NAMETABLE_A);
	vram_unrle(level_select_screen); 
	vram_adr(NAMETABLE_B);
	vram_unrle(level_select_screen);
	
	write_irq_table(lvlselect_irq_table);
	set_irq_ptr(irqTable);
	edit_irq_table(high_byte(tmp8),2);

	set_scroll_x(0);
	set_scroll_y(0);  

	tmp8 = 0xff00;
	tmp4 = 1;
	crossPRGBankJump0(refreshmenu);
	top_triggers = 0;
	triggers = 0;
	triggers_hit[0] = 0;
	triggers_hit[1] = 0;
	triggers_hit[2] = 0;

	drawBarFlag = 2;
	low_byte(tmpA) = 1;
	draw_both_progress_bars();
	
	practice_point_count = 0;

	// one_vram_buffer(0xb0+kandokidshackTENS, NTADR_A(17,17));
	// one_vram_buffer(0xb0+kandokidshackONES, NTADR_A(18,17));

	cube_rotate[0] = 0;
	cube_rotate[1] = 0;

	#if __VS_SYSTEM
	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(idx8_load(xbgmlookuptable, newrand() & 31));
	#else

	#if !__HUGE_ROM
	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(xbgmlookuptable[menu_music]);
	#else
	if (menuMusicCurrentlyPlaying == 0 && !nestopia) music_play(xbgmlookuptable[menutheme]);
	#endif

	#endif
	menuMusicCurrentlyPlaying = 1;

	ppu_on_all();

	pal_fade_in();

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
				gameState = STATE_MENU;
				draw_both_progress_bars();
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
			gameState = STATE_MENU;
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
			draw_both_progress_bars();
			return;
		}
		if (joypad1.press_left || joypad1.press_right) hold_timer = 0;
		if (joypad1.press_right || (joypad1.right && hold_timer >= 15)){
			drawBarFlag = 2;
			levelinc();
			#if __VS_SYSTEM
				menutimer = 0;
			#endif
			hold_timer = 0;
		}
		if (joypad1.press_left || (joypad1.left && hold_timer >= 15)){
			drawBarFlag = 2;
			leveldec();
			#if __VS_SYSTEM
				menutimer = 0;
			#endif		
			hold_timer = 0;
		}

		// NOTE: this is hardcoded. It used to be 0x3F with the old scroll scheme
		if (tmp8 == 0x3B) {
			crossPRGBankJump0(refreshmenu);
		}

		draw_both_progress_bars();

		dec_mouse_timer();
		if (hold_timer < 15) hold_timer++;
	}

}

void leveldec() {
	--level;
	low_byte(tmp8) = 0xff;
	tmp4 = 0;
	if (!normalorcommlevels) {
		if (level == 0xFF) level = LEVEL_COUNT - 1;
	} else {
		#if LEVEL_COUNT > 0
			if (level < LEVEL_COUNT)
		#else
			if (level == 0xFF)
		#endif
				level = LEVEL_COUNT2 - 1;
	}
	crossPRGBankJump0(refreshmenu);
}			

void levelinc() {
	++level;
	low_byte(tmp8) = 0xff;
	tmp4 = 1;
	if (!normalorcommlevels) {
		#if LEVEL_COUNT > 0	// technically has no effect, but it silences the warning
			if (level >= LEVEL_COUNT)
		#endif
				level = 0x00;
	} else {
		if (level >= LEVEL_COUNT2) level = LEVEL_COUNT;
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
	} while (++tmpA < 30);
	gameState = STATE_GAME;
	menuMusicCurrentlyPlaying = 0;
}

const uint8_t lvlselect_irq_table[] = {
	31,
	irqtable_hscroll, 0x00, // item 0x02 gets modified every frame
	149,
	irqtable_hscroll, 0x00,

	irqtable_end // always end with 0xff
};