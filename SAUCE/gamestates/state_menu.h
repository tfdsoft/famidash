void state_menu(){
	ppu_off();

	set_scroll_x(0);
    set_scroll_y(0);

	music_play(song_menu_theme);

	// make the entire first nametable use bg palette 3
	vram_adr(0x23C0);
	for(tmp1=0;tmp1<0x40;++tmp1){
		vram_put(0xFF);
	}

	// print menu text
	vram_adr(NTADR_A(4,4));
	for(tmp1=0;menutext1[tmp1];++tmp1){
		vram_put(0xA0+menutext1[tmp1]);
	} 
	vram_adr(NTADR_A(7,24));
	for(tmp1=0;menutext2[tmp1];++tmp1){
		vram_put(0xA0+menutext2[tmp1]);
	}
	vram_adr(NTADR_A(9,25));
	for(tmp1=0;menutext3[tmp1];++tmp1){
		vram_put(0xA0+menutext3[tmp1]);
	}
	vram_adr(NTADR_A(2,27));
	for(tmp1=0;menutext4[tmp1];++tmp1){
		vram_put(0xA0+menutext4[tmp1]);
	}


	ppu_on_all();

	while (1){
		ppu_wait_nmi();
		music_update();

		pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

		if (pad_new & PAD_START){
			gameState = 0x02;
			return;
		}
		if (pad_new & PAD_SELECT){
			level = 0x05;
			gameState = 0x02;
			return;
		}
		gray_line();
	}
}