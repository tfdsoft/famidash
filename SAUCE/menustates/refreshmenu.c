// To be merged into levelselection.c

const uint8_t difficulty_pal_A[];
const uint8_t difficulty_pal_B[];

#include "defines/charmap/color1_charmap.h"
#include "menutext.h"

const char coin_counter[][3];

/*
	Refreshes level name & number
*/
void refreshmenu() {
	tmp5 = ((level&1)<<2)<<8;
	set_scroll_x(((level-tmp4)&1)<<8);
	
	__A__ = idx16_load_hi_NOC(levelTextsUpper, level);
	if (__A__) draw_padded_text(levelTextsUpper[level & 0x7F], levelTextsUpperSize[level], 17, NTADR_A(8, 10)+tmp5);
	else one_vram_buffer_horz_repeat(' ', 17, NTADR_A(8, 10)+tmp5);
	// if (leveltexts2[level]) // always true
	draw_padded_text(levelTextsLower[level & 0x7F], levelTextsLowerSize[level], 17, NTADR_A(8, 11)+tmp5);

	if (LEVELCOMPLETE[level]) { one_vram_buffer('y', NTADR_A(7, 9)+tmp5);
	one_vram_buffer('z', NTADR_A(8, 9)+tmp5); }
	else one_vram_buffer_horz_repeat(' ', 2, NTADR_A(7, 9)+tmp5);

	{	// write the difficulty
		tmp1 = difficulty_list[level];
		pal_col(0x0a, difficulty_pal_A[tmp1]);
		pal_col(0x0b, difficulty_pal_B[tmp1]);
		pal_set_update();
		
		tmp1 = (tmp1 << 1) + 'a';
		one_vram_buffer(tmp1, NTADR_A(7, 10)+tmp5);
		one_vram_buffer(++tmp1, NTADR_A(8, 10)+tmp5);
		one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(7, 11)+tmp5);
		one_vram_buffer(++tmp1, NTADR_A(8, 11)+tmp5);
		

	}
	// Star count stuff
		printDecimal(stars_list[level], 2, '0', ' ', NTADR_A(22, 9)+tmp5);

	// level number
	#ifdef FLAG_ENABLE_TEST_LEVELS
		printDecimal(level, 3, '0', ' ', NTADR_A(29, 2));
		printDecimal(level, 3, '0', ' ', NTADR_B(29, 2));
	#endif

	//palette stuff
		tmp3 = level % 9;
		pal_col(0,colors_list[tmp3]);
		pal_col(0xE,colors_list[tmp3]);
		
		pal_spr(paletteLVLSelectSP);
		pal_col(0x10,colors_list[tmp3]);
		pal_col(0x1E,colors_list[tmp3]);
		pal_set_update();
	//coin stuff
		coins = 0;

	// then in the function...
	// combine all three into a single number from 0 - 7 to represent which coins have been grabbed
		tmp7 = byte((byte(coin3_obtained[level] << 1) | coin2_obtained[level]) << 1) | coin1_obtained[level];
		tmp7 = byte(tmp7<<1) + tmp7;
	// actually draw the coins
		multi_vram_buffer_horz((const char * const)coin_counter+tmp7, 3, NTADR_A(22, 12)+tmp5);

}

const uint8_t difficulty_pal_A[] ={
	0x21,	// easy
	0x2A,	// normal
	0x28,	// hard
	0x16,	// harder
	0x24,	// insane
	0x16,	// demon
	0x28,	// auto
};

const uint8_t difficulty_pal_B[] ={
	0x06,	// easy
	0x30,	// normal
	0x30,	// hard
	0x30,	// harder
	0x06,	// insane
	0x30,	// demon
	0x0F,	// auto
};

const char coin_counter[][3] = {
  "___",
  "^__",
  "_^_",
  "^^_",
  "__^",
  "^_^",
  "_^^",
  "^^^",
};