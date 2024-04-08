#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")


const unsigned char* const leveltexts[] = {
  level1text, level2text, level3text, level4text, level5text, level6text, level7text, level8text, level9text, levelAtext, levelBtext, levelCtext
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
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelBtext)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelCtext)) / 2),
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
	sizeof(levelBtext) - 1,
	sizeof(levelCtext) - 1,
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

};

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

	// Enable SRAM write
	POKE(0xA001, 0x80);

	// Get it? it spells DASH
	if (SRAM_VALIDATE[0] != 0x0D
	 || SRAM_VALIDATE[1] != 0x0A
	 || SRAM_VALIDATE[2] != 0x05
	 || SRAM_VALIDATE[3] != 0x06) {
		// set the validation header and then reset coin counts
		SRAM_VALIDATE[0] = 0x0d;
		SRAM_VALIDATE[1] = 0x0a;
		SRAM_VALIDATE[2] = 0x05;
		SRAM_VALIDATE[3] = 0x06;
		LEVEL1COINS = 0;
		LEVEL2COINS = 0;
		LEVEL3COINS = 0;
		LEVEL4COINS = 0;
		LEVEL5COINS = 0;
		LEVEL6COINS = 0;
		LEVEL7COINS = 0;
		LEVEL8COINS = 0;
		LEVEL9COINS = 0;
		LEVELACOINS = 0;
	}

	kandotemp = 1;

	TOTALCOINSONES = 0;
	TOTALCOINSTENS = 0;
	TOTALCOINS = LEVEL1COINS + LEVEL2COINS + LEVEL3COINS + LEVEL4COINS + LEVEL5COINS + LEVEL6COINS + LEVEL7COINS + LEVEL8COINS + LEVEL9COINS + LEVELACOINS;

	TOTALCOINSTEMP = TOTALCOINS;
	
	while (TOTALCOINSTEMP > 9) {
		TOTALCOINSTENS = TOTALCOINSTENS + 1;
		TOTALCOINSTEMP = TOTALCOINSTEMP - 10;
	}
	TOTALCOINSONES = TOTALCOINSTEMP;
	
		

	oam_clear();

	// Expand the data for the menu nametable while the PPU is still off
    vram_adr(NAMETABLE_A);
    vram_unrle(game_main_menu);

	refreshmenu();

	one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
	one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));

	ppu_on_all();
	pal_fade_to(0,4);
	while (1){
		ppu_wait_nmi();
		music_update();
		pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

		if (pad_new & PAD_SELECT){
			if (pad & PAD_A){
				if (pad & PAD_B){
					LEVEL1COINS = 0;
					LEVEL2COINS = 0;
					LEVEL3COINS = 0;
					LEVEL4COINS = 0;
					LEVEL5COINS = 0;
					LEVEL6COINS = 0;
					LEVEL7COINS = 0;
					LEVEL8COINS = 0;
					LEVEL9COINS = 0;
					LEVELACOINS = 0;					
					TOTALCOINSONES = 0;
					TOTALCOINSTENS = 0;
					one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
					one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));					
					famistudio_sfx_play(sfx_death, 0);
				}
			}
		}


		if (pad_new & PAD_START){
			gameState = 0x02;
			pal_fade_to(4,0);
			kandotemp = 0;
			return;
		}
		if (pad_new & (PAD_SELECT | PAD_RIGHT)){
			++level;
			if (level > 0x0B){
				level = 0x00;
			}
			refreshmenu();
		//	break;
		}
		if (pad_new & PAD_LEFT){
			--level;
			if (level == 0xFF){
				level = 0x0B;
			}
			
			//break;
			refreshmenu();
		}
	}
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
