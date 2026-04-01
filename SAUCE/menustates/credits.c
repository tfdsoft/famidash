void mouse_and_cursor();

#include "defines/charmap/mainmenu_charmap.h"

#ifdef FLAG_ENABLE_VER_NUM
	#ifdef FLAG_BETA_BUILD
		const unsigned char ver[] = "DEMO";
	#else
		const unsigned char ver[] = " VER";
	#endif
	const unsigned char verNum[] = {FLAG_MAJ_VER, 0x18, FLAG_MIN_VER, 0x18, FLAG_PATCH_VER};
#endif

#if __THE_ALBUM || __HUGE_ROM
void check_if_music_stopped_3() {
	if (famistudio_song_speed == 0x80) music_play(song_scheming_weasel);
}
#endif

void credits_loop() {
	oam_clear();
	#if !__THE_ALBUM
		mouse_and_cursor();
	#endif
	newrand();
    kandoframecnt++;
	#if __VS_SYSTEM
		crossPRGBankJump0(check_if_music_stopped);
	#elif __THE_ALBUM || __HUGE_ROM
		check_if_music_stopped_3();
	#endif

	#if !__THE_ALBUM
	if (!forced_credits &&
		(joypad1.press || ((mouse.connected)
			? mouse.left_press || mouse.right_press
			: joypad2.press))) {
			gameState = STATE_MENU; return;
	}
	#else
	if (!forced_credits &&
		(joypad1.press || joypad2.press)) {
			gameState = STATE_MENU; return;
	}		
	#endif
	ppu_wait_nmi();
	tmp1++;
	if (kandoframecnt & 1 && mouse_timer) mouse_timer--;
}

void state_credits(){
	oam_clear();
	
	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(0xFF);	
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);	
    
    pal_bg(palette_Credits);

	vram_adr(NAMETABLE_A);
	vram_unrle(Credits);
	vram_unrle(Credits2);
	#if !__THE_ALBUM
		vram_adr(NAMETABLE_D);
		vram_unrle(Credits3);
	#endif

	multi_vram_buffer_horz(ver, sizeof(ver)-1, NTADR_A(1,24));
	multi_vram_buffer_horz(verNum, sizeof(verNum), NTADR_A(6,24));

	ppu_on_all();
	ppu_wait_nmi();

	pal_fade_in();

	/*	Incomplete code for reproducing what is being screamed into the Famicom microphone
	(He forgor about the PCM bit)
	OG by UserSniper, commit 7e47f425
	POKE(0x4015, 0b00010000);
	while (1) {
		POKE(0x4011, fc_mic_poll()<<4);
	}
	*/
	ppu_wait_nmi();
	
	tmp1 = 0;
	do {
		credits_loop();
		if (gameState != STATE_CREDITS) return;
	} while (tmp1 != 0);

	#if !__THE_ALBUM
		// tmp1 = 0; redundant since that's the loop condition
		do {
			credits_loop();
			set_scroll_x(tmp1<<2);
			if (gameState != STATE_CREDITS) return;
		} while (tmp1 < 64);

		set_scroll_x(256);
		tmp1 = 0;
		do {
			credits_loop();
			if (gameState != STATE_CREDITS) return;
		} while (tmp1 != 0);

		// tmp1 = 0; redundant since that's the loop condition
		do {
			credits_loop();
			set_scroll_y(tmp1<<2);
			if (gameState != STATE_CREDITS) return;
		} while (tmp1 < (0xF0 >> 2));

		tmp1 = 0;
		set_scroll_y(256);
	#endif

	do {
		credits_loop();
		if (gameState != STATE_CREDITS) return;
	} while (tmp1 != 0);

	forced_credits = 0;
	gameState = STATE_MENU;

	return; 
	
}


#ifdef level_luckydraw
	#include "defines/charmap/luckydraw_charmap.h"
	const unsigned char triggerstext[]="TRIGGERS SURVIVED"; //ATTEMPT
	const unsigned char toptriggerstext[]="TOP TRIGGERS SURVIVED"; //ATTEMPT

void Lucky_Draw_Text_Stuff() {
			if (level == level_luckydraw && (triggers_hit[0] || triggers_hit[1] || triggers_hit[2])) {
				multi_vram_buffer_horz((const char*)triggerstext,sizeof(triggerstext)-1,NTADR_C(1, 6));
				one_vram_buffer(0xF5+triggers_hit[2], NTADR_C(20,6));
				one_vram_buffer(0xF5+triggers_hit[1], NTADR_C(21,6));
				one_vram_buffer(0xF5+triggers_hit[0], NTADR_C(22,6));
				one_vram_buffer(0xD0, NTADR_C(23,6));
				one_vram_buffer(0xF5+8, NTADR_C(24,6));
				one_vram_buffer(0xF5+0, NTADR_C(25,6));
				one_vram_buffer(0xF5+0, NTADR_C(26,6));
				
				if (triggers > top_triggers) top_triggers = triggers;

				multi_vram_buffer_horz((const char*)toptriggerstext,sizeof(toptriggerstext)-1,NTADR_C(1, 8));

				
				hexToDec(top_triggers);

				if (hexToDecOutputBuffer[2])
					one_vram_buffer(0xf5+hexToDecOutputBuffer[2], NTADR_C(23,8));

				if (hexToDecOutputBuffer[2] | hexToDecOutputBuffer[1])
					one_vram_buffer(0xf5+hexToDecOutputBuffer[1], NTADR_C(24,8));

				one_vram_buffer(0xf5+hexToDecOutputBuffer[0], NTADR_C(25,8));	
		
				one_vram_buffer(0xD0, NTADR_C(26,8));
				one_vram_buffer(0xF5+8, NTADR_C(27,8));
				one_vram_buffer(0xF5+0, NTADR_C(28,8));
				one_vram_buffer(0xF5+0, NTADR_C(29,8));			
			
				triggers = 0;
				triggers_hit[0] = 0;
				triggers_hit[1] = 0;
				triggers_hit[2] = 0;
			}
}
#endif
