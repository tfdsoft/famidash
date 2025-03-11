// prototype
void init_sprites();
#include "defines/bg_charmap.h"
const unsigned char attempttext[]="PQQRSTQ"; //ATTEMPT
#include "defines/luckydraw_charmap.h"
const unsigned char triggerstext[]="TRIGGERS SURVIVED"; //ATTEMPT
const unsigned char toptriggerstext[]="TOP TRIGGERS SURVIVED"; //ATTEMPT


//const unsigned char whartxt[]="wxyz";	// WHAR
void setdefaultoptions();
/* 
	Reset run-length decoder back to zero
	Implemented in asm
*/
void __fastcall__ init_rld(uint8_t level);

/* 
	This should explain itself
	Requires the correct PRG1 bank to be set
	Implemented in asm
*/
void __fastcall__ unrle_next_column();

/* 
	Scrolling to the right, draw metatiles as we go
	Returns 1 if it actually did anything
	Implemented in asm	
*/
char __fastcall__ draw_screen();

/*
	Load ground tiles into collision map
	Implemented in asm
*/
void __fastcall__ load_ground(uint8_t id);

/*
	Dummy unrle columns, way faster
	Implemented in asm
*/
void __fastcall__ dummy_unrle_columns(uint16_t columns);

void increase_parallax_scroll_column() {
	// The parallax is a 6 x 9 tile background, and when it repeats
	// horizontally, we offset the start of the next column by 3
	// to stagger the repeat
	parallax_scroll_column++;
	if (parallax_scroll_column >= 6) {
		parallax_scroll_column = 0;
		parallax_scroll_column_start += 3;
		if (parallax_scroll_column_start >= 9) {
			parallax_scroll_column_start = 0;
		}
	}
}

extern unsigned char drawing_frame;
void unrle_first_screen(){ // run-length decode the first screen of a level
	// register unsigned char i;
	#define i (*((uint8_t *)&ii))
	register uint16_t ii;
	mmc3_set_prg_bank_1(GET_BANK(increment_attempt_count));
	increment_attempt_count();
	coins = 0;
	outline_color = 0x30;	
	cube_data[0] = 0;
	cube_data[1] = 0;

	mmc3_set_prg_bank_1(level_data_bank);

	// If practice mode has set a scroll position to restart from
	// Then we dummy unrle, and adjust the parallax to match
	if (practice_point_count) {

		ii = lohi_arr32_load(practice_scroll_x, curr_practice_point) >> 4;
		dummy_unrle_columns(ii);

		__A__ = -(6 * (9 / 3) / 2); __asm__("tay \n sty %v", parallax_scroll_column);
		while (ii != 0) {
			parallax_scroll_column++;
			if (parallax_scroll_column == 0) {
				__asm__("sty %v", parallax_scroll_column);
			}
			ii--;
		}
		parallax_scroll_column_start = -3;
		__asm__("ldy #3");
		unrle_first_screen_addition_loop:
			__asm__("tya ");
			parallax_scroll_column_start += __A__;
			__asm__("tya ");
			parallax_scroll_column += __A__;
			__asm__("bmi %g", unrle_first_screen_addition_loop);
		parallax_scroll_column <<= 1;

		//mmc3_set_prg_bank_1(GET_BANK(restore_practice_state));
		
		crossPRGBankJump0(restore_practice_state);	

		music_update();

		mmc3_set_prg_bank_1(GET_BANK(draw_screen));
		// Draw the nametable starting from where the scroll is set
		i = -16;
		do {
			if (draw_screen()) flush_vram_update2();	// if draw_screen did anything, flush vram
			i++;
			uint32_inc(scroll_x);
		} while (i != 0);
		
	//	memcpy(famistudio_state, practice_famistudio_state, sizeof(practice_famistudio_state));
	
	} 
	else {
		// To get the draw screen R to start in the left nametable, scroll must be negative.
		low_word(scroll_x) = LSW(-256); high_word(scroll_x) = MSW(-256);
		parallax_scroll_x = 0;
		parallax_scroll_column = 0;
		parallax_scroll_column_start = 0;
		mmc3_set_prg_bank_1(GET_BANK(draw_screen));
		i = 0;
	}
	

	// Draw the nametable starting from where the scroll is set
    do {
		if (draw_screen()) flush_vram_update2();	// if draw_screen did anything, flush vram
		i++;
		uint32_inc(scroll_x);
	} while (i != 0);

	init_sprites();
	
	set_scroll_x(scroll_x);
	set_scroll_y(scroll_y);
	if (!practice_point_count) {
		multi_vram_buffer_horz((const char*)attempttext,sizeof(attempttext)-1,NTADR_C(6, 15));
	
//		if (TOTALATTEMPTSTHOUSANDS >= 10)
//			multi_vram_buffer_horz((const char*)whartxt,sizeof(whartxt)-1,NTADR_C(15, 15));
//
//		else {
			if (level == luckydraw && (triggers_hit[0] || triggers_hit[1] || triggers_hit[2])) {
				multi_vram_buffer_horz((const char*)triggerstext,sizeof(triggerstext)-1,NTADR_C(1, 17));
				one_vram_buffer(0xF5+triggers_hit[2], NTADR_C(20,17));
				one_vram_buffer(0xF5+triggers_hit[1], NTADR_C(21,17));
				one_vram_buffer(0xF5+triggers_hit[0], NTADR_C(22,17));
				one_vram_buffer(0xD0, NTADR_C(23,17));
				one_vram_buffer(0xF5+8, NTADR_C(24,17));
				one_vram_buffer(0xF5+0, NTADR_C(25,17));
				one_vram_buffer(0xF5+0, NTADR_C(26,17));
				
				if (triggers > top_triggers) top_triggers = triggers;

				multi_vram_buffer_horz((const char*)toptriggerstext,sizeof(toptriggerstext)-1,NTADR_C(1, 19));

				
				hexToDec(top_triggers);

				if (hexToDecOutputBuffer[2])
					one_vram_buffer(0xf5+hexToDecOutputBuffer[2], NTADR_C(23,19));

				if (hexToDecOutputBuffer[2] | hexToDecOutputBuffer[1])
					one_vram_buffer(0xf5+hexToDecOutputBuffer[1], NTADR_C(24,19));

				one_vram_buffer(0xf5+hexToDecOutputBuffer[0], NTADR_C(25,19));	
		
				one_vram_buffer(0xD0, NTADR_C(26,19));
				one_vram_buffer(0xF5+8, NTADR_C(27,19));
				one_vram_buffer(0xF5+0, NTADR_C(28,19));
				one_vram_buffer(0xF5+0, NTADR_C(29,19));			
			
				triggers = 0;
				triggers_hit[0] = 0;
				triggers_hit[1] = 0;
				triggers_hit[2] = 0;
			}
			
			mmc3_set_prg_bank_1(GET_BANK(_display_attempt_counter));
			display_attempt_counter(0xF5, NTADR_C(20, 15));
			
			
	}
	
}
