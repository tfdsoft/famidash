
const unsigned char* const leveltexts[] = {
  level1text, level2text, level3text, level4text, level5text, level6text, level7text, level8text, level9text, levelAtext
};

#define GAME_MENU_TITLE_X_OFFSET 9
const unsigned char level_text_padding[] = {
    GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level1text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level2text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level3text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level4text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level5text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level6text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level7text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level8text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level9text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelAtext)) / 2),
};
const unsigned char level_text_size[] = {
    sizeof(level1text) - 1,
	sizeof(level2text) - 1,
	sizeof(level3text) - 1,
	sizeof(level4text) - 1,
	sizeof(level5text) - 1,
	sizeof(level6text) - 1,
	sizeof(level7text) - 1,
	sizeof(level8text) - 1,
	sizeof(level9text) - 1,
	sizeof(levelAtext) - 1,
};

/*
	Refreshes level name & number
*/
void __fastcall__ refreshmenu(void) {
	#include "../defines/color1_charmap.h"
	// Clear out the previous title
	one_vram_buffer_horz_repeat(' ', 17, NTADR_A(8, 14));
	// center this by offseting the write by the padding amount
	multi_vram_buffer_horz((const char*)leveltexts[level],
		level_text_size[level],
		NTADR_A(level_text_padding[level], 14));
}

void state_menu(){
	ppu_off();
	pal_bright(0);
    pal_bg((char *)paletteMenu);
	set_scroll_x(0);
    set_scroll_y(0);

	mmc3_set_prg_bank_1(0);

	switch (kandotemp){
		case 0x00:	music_play(song_menu_theme); break;
		case 0x01:	break;
	}

	coins = 0;
	kandotemp = 1;

	oam_clear();

	// Expand the data for the menu nametable while the PPU is still off
    vram_adr(NAMETABLE_A);
    vram_unrle(game_main_menu);

	refreshmenu();

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
		if (pad_new & (PAD_SELECT | PAD_RIGHT)){
			++level;
			if (level > 9){
				level = 0x00;
			}
			refreshmenu();
		//	break;
		}
		if (pad_new & PAD_LEFT){
			--level;
			if (level == 0xFF){
				level = 0x09;
			}
			
			//break;
			refreshmenu();
		}
	}
}


