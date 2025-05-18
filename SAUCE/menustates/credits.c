void mouse_and_cursor();

#include "charmaps/mainmenu_charmap.h"

#ifdef FLAG_ENABLE_VER_NUM
	#ifdef FLAG_BETA_BUILD
		const unsigned char ver[] = "DEMO";
	#else
		const unsigned char ver[] = " VER";
	#endif
#endif

void state_credits(){
	mmc3_disable_irq();
	
    ppu_off();
	pal_bright(0);
    
    pal_bg(palette_Credits);

	vram_adr(NAMETABLE_A);
	vram_unrle(Credits);
	vram_adr(NAMETABLE_B);
	vram_unrle(Credits2);

	multi_vram_buffer_horz(ver, sizeof(ver)-1, NTADR_A(1,24));
	one_vram_buffer(FLAG_MAJ_VER, NTADR_A(6,24));
	#ifdef FLAG_BETA_BUILD
		one_vram_buffer(0x18, NTADR_A(7,24)); // dot
		one_vram_buffer(FLAG_MIN_VER, NTADR_A(8,24));
//		one_vram_buffer(0x18, NTADR_A(9,24)); // dot
//		one_vram_buffer(FLAG_MAJ_VER, NTADR_A(10,24));
	#endif
	
	// __asm__("LDA mmc3PRG1Bank \nPHA ");
    // mmc3_set_prg_bank_1(0);
    // vram_adr(NAMETABLE_A);
	//    vram_unrle(dem_funnies);
    // __asm__("PLA \n JSR %v ", mmc3_set_prg_bank_1);

	oam_clear();
	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(0xFF);	
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);	
	ppu_on_all();
	ppu_wait_nmi();

	pal_fade_to(0,4);
	tmp1 = 0;

	/*	Incomplete code for reproducing what is being screamed into the Famicom microphone
	(He forgor about the PCM bit)
	OG by UserSniper, commit 7e47f425
	POKE(0x4015, 0b00010000);
	while (1) {
		POKE(0x4011, fc_mic_poll()<<4);
	}
	*/
	ppu_wait_nmi();
	
	do {
		oam_clear();
       	mouse_and_cursor();
		newrand();
	    kandoframecnt++;
		
		if (!forced_credits &&
			(joypad1.press || ((mouse.connected)
				? mouse.left_press || mouse.right_press
				: joypad2.press))) {
					gameState = STATE_MENU; return;
		}
		ppu_wait_nmi();
		#if __VS_SYSTEM
			crossPRGBankJump0(check_if_music_stopped);
		#endif
		music_update();
		tmp1++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
	} while (tmp1 != 0);

	tmp1 = 0;
	do {
		oam_clear();
		mouse_and_cursor();
		newrand();
	    kandoframecnt++;
		#if __VS_SYSTEM
			crossPRGBankJump0(check_if_music_stopped);
		#endif
		music_update();
		if (!forced_credits &&
			(joypad1.press || ((mouse.connected)
				? mouse.left_press || mouse.right_press
				: joypad2.press))) {
				gameState = STATE_MENU; return;
		}
		
		ppu_wait_nmi();
		tmp1++;
		set_scroll_x(tmp1<<2);
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;				
	} while (tmp1 < 64);

	tmp1 = 0;
	set_scroll_x(256);
	do {
		oam_clear();
		mouse_and_cursor();
		newrand();
		kandoframecnt++;
		if (!forced_credits &&
			(joypad1.press || ((mouse.connected)
				? mouse.left_press || mouse.right_press
				: joypad2.press))) {
					gameState = STATE_MENU; return;
		}
		ppu_wait_nmi();
		#if __VS_SYSTEM
			crossPRGBankJump0(check_if_music_stopped);
		#endif
		music_update();
		tmp1++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;				
	} while (tmp1 != 0);
	forced_credits = 0;
	gameState = STATE_MENU;
	return; 
	
}