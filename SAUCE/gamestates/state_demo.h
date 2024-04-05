void state_demo(){
    ppu_off();
    
    pal_bg((char *)paletteMenu);

    mmc3_tmp_prg_bank_1(0);
    vram_adr(NAMETABLE_A);
//    vram_unrle(dem_funnies);
    mmc3_pop_prg_bank_1();

	mmc3_set_8kb_chr(8);

	oam_clear();
	ppu_on_all();
	pal_fade_to(0,4);
	while (1){
		ppu_wait_nmi();

		pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

		if (pad_new & PAD_START){
			gameState = 0x02;
			pal_fade_to(4,0);
			return;
		}
	}
}