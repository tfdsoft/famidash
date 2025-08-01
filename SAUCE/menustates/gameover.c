const unsigned char gameover[];

void state_gameover() {
	oam_clear();

	mmc3_set_8kb_chr(MENUBANK);
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	
	pal_bg(gameoverpalette);

	vram_adr(NAMETABLE_A);
	vram_unrle(gameover);

	menutimer = 0;
	tmp5 = 200;

	set_scroll_x(0);
	set_scroll_y(0);

	ppu_on_all();

	pal_fade_in();

	while (tmp5) {
		ppu_wait_nmi();
		tmp5--;
	}

	gameState = STATE_MENU;
	cube_data[0] = 0;
	cube_data[1] = 0;
	return;
}

const unsigned char gameover[188]={
0x03,0x02,0xfe,0x02,0x03,0x02,0xfe,0x02,0x03,0x10,0xfe,0xfe,0x02,0xfe,0x03,0x02,
0x02,0x02,0xfe,0x02,0xfe,0xfe,0x02,0xfe,0x02,0x03,0x08,0xfe,0xfe,0x02,0x03,0x05,
0xfe,0x03,0x02,0x02,0xfe,0x03,0x02,0x02,0x02,0xfe,0x03,0x02,0x02,0x03,0x09,0xfe,
0x02,0xfe,0x03,0x13,0x02,0x02,0xfe,0x02,0x03,0x06,0xfe,0x03,0xdf,0xc1,0xbb,0xc7,
0xbf,0xfe,0x03,0x3f,0xc9,0xdb,0xbf,0xcc,0xfe,0x03,0x99,0x98,0x99,0x98,0x99,0xfe,
0x03,0x1b,0xa8,0xa9,0xa8,0xa9,0xfe,0x03,0x5c,0x9a,0x9b,0xfe,0x03,0x1d,0xaa,0xab,
0xfe,0x03,0xb3,0x02,0xfe,0xfe,0x02,0x03,0x05,0xfe,0xfe,0x02,0x03,0x05,0xfe,0x03,
0x04,0x02,0x03,0x02,0xfe,0x03,0x02,0x02,0xfe,0x03,0x02,0x02,0xfe,0x02,0xfe,0x03,
0x04,0x02,0x03,0x09,0xfe,0x02,0xfe,0xfe,0x02,0x03,0x02,0xfe,0xfe,0x00,0x00,0x50,
0x10,0x40,0x50,0x00,0x03,0x0a,0x84,0x21,0x00,0x03,0x02,0x01,0x00,0x03,0x05,0x04,
0x01,0x00,0x00,0x04,0x05,0x00,0x04,0x05,0x01,0x00,0x03,0x03,0x44,0x11,0x00,0x03,
0x02,0x41,0x00,0x03,0x05,0x14,0x00,0x03,0x06,0x00,0x03,0x00
};