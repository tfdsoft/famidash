void state_menu(){
	ppu_off();

	set_scroll_x(0);
    set_scroll_y(0);


	switch (kandotemp){
		case 0x00:	music_play(song_menu_theme); break;
		case 0x01:	break;
	}


	kandotemp = 1;
	
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
	vram_adr(NTADR_A(2,24));
	for(tmp1=0;menutext2[tmp1];++tmp1){
		vram_put(0xA0+menutext2[tmp1]);
	}

	
	mmc3_set_2kb_chr_bank_0(8);
    mmc3_set_2kb_chr_bank_1(10);
    mmc3_set_1kb_chr_bank_0(12);
    mmc3_set_1kb_chr_bank_1(13);
    mmc3_set_1kb_chr_bank_2(14);
    mmc3_set_1kb_chr_bank_3(15);


	one_vram_buffer(0xD0+level, NTADR_A(29,24));

	vram_adr(NTADR_A(2,25));	
	switch (level){
		case 0x01: 
			for(tmp1=0;level1text[tmp1];++tmp1){
				vram_put(0xA0+level1text[tmp1]);
			};
			break;
		case 0x02: 
			for(tmp1=0;level2text[tmp1];++tmp1){
				vram_put(0xA0+level2text[tmp1]);
			};
			break;
		case 0x03: 
			for(tmp1=0;level3text[tmp1];++tmp1){
				vram_put(0xA0+level3text[tmp1]);
			};
			break;
		case 0x04: 
			for(tmp1=0;level4text[tmp1];++tmp1){
				vram_put(0xA0+level4text[tmp1]);
			};
			break;
		case 0x05: 
			for(tmp1=0;level5text[tmp1];++tmp1){
				vram_put(0xA0+level5text[tmp1]);
			};
			break;
		case 0x06: 
			for(tmp1=0;level6text[tmp1];++tmp1){
				vram_put(0xA0+level6text[tmp1]);
			};
			break;
		case 0x07: 
			for(tmp1=0;level7text[tmp1];++tmp1){
				vram_put(0xA0+level7text[tmp1]);
			};
			break;
	}

	oam_clear();
	ppu_on_all();
	pal_fade_to(0,4);
	while (1){
		ppu_wait_nmi();
		music_update();

		pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

		if (pad_new & PAD_START){
			gameState = 0x02;
			pal_fade_to(4,0);
			kandotemp = 0;
			return;
		}
		if (pad_new & PAD_SELECT){
			++level;
			if (level > 7){
				level = 0x01;
			}
			one_vram_buffer(0xD0+level, NTADR_A(29,24));
			break;
		}
		if (pad_new & PAD_LEFT){
			--level;
			if (level == 0){
				level = 0x07;
			}
			one_vram_buffer(0xD0+level, NTADR_A(29,24));
			break;
		}
		if (pad_new & PAD_RIGHT){
			++level;
			if (level > 7){
				level = 0x01;
			}
			one_vram_buffer(0xD0+level, NTADR_A(29,24));
			break;
		}
		//gray_line();
	}
}