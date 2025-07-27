void mouse_and_cursor();

const unsigned char palette_Credits[];

void state_instructions(){
	oam_clear();
		
	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);

	pal_bg(palette_Credits);
	
	vram_adr(NAMETABLE_A);
	vram_unrle(instructions);

	ppu_on_all();

	pal_fade_to(0,4);

	do {
		oam_clear();
		mouse_and_cursor();

		ppu_wait_nmi();

		newrand();
		kandoframecnt++;
	} while (!joypad1.press
		#if !__VS_SYSTEM
			&& !mouse.left_press
		#endif
		);
	gameState = STATE_MENU;
	return;
}	