void mouse_and_cursor();

const unsigned char palette_Credits[];

void state_instructions(){
	mmc3_disable_irq();
	
	ppu_off();
	pal_bright(0);
    
	pal_bg(palette_Credits);
	
	vram_adr(NAMETABLE_A);
	vram_unrle(instructions);

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
	music_update();
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

	
	do {
		oam_clear();
		mouse_and_cursor();
		music_update();
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