#include "defines/charmap/mainmenu_charmap.h"

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

	pal_fade_to(0,4);

	while (tmp5) {
		ppu_wait_nmi();
		tmp5--;
	}

	gameState = STATE_MENU;
	cube_data[0] = 0;
	cube_data[1] = 0;
	return;
}