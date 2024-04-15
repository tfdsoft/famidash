// prototype
void init_sprites(void);
#include "../defines/bg_charmap.h"
const unsigned char attemptstex[]="PQQRSTQ"; //ATTEMPT
const unsigned char wtxt[]="w";
const unsigned char htxt[]="x";
const unsigned char atxt[]="y";
const unsigned char rtxt[]="z";
/* 
	Reset run-length decoder back to zero
	Implemented in asm
*/
void __fastcall__ init_rld(unsigned char level);

/* 
	This should explain itself
	Requires the correct PRG1 bank to be set
	Implemented in asm
*/
void __fastcall__ unrle_next_column(void);

/* 
	Scrolling to the right, draw metatiles as we go
	Implemented in asm	
*/
void __fastcall__ draw_screen_R(void);
void __fastcall__ draw_screen_R_frame0(void);
void __fastcall__ draw_screen_R_frame1(void);
void __fastcall__ draw_screen_R_frame2(void);

void load_ground(unsigned char id){
	mmc3_set_prg_bank_1(0);
	// render to both nametable c and d
    vram_adr(NAMETABLE_C);
    vram_unrle(ground[id]);
    vram_adr(NAMETABLE_D);
    vram_unrle(ground[id]);
}

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

void unrle_first_screen(void){ // run-length decode the first screen of a level
	unsigned char i;
	init_sprites();

	mmc3_set_prg_bank_1(level_data_bank);
	// To get the draw screen R to start in the left nametable, scroll must be negative.
	scroll_x = -1;
    for (i = 0; i < 16; i++) {
        draw_screen_R_frame0();
        flush_vram_update2();
		
        draw_screen_R_frame1();
        flush_vram_update2();
		
        draw_screen_R_frame2();
        flush_vram_update2();
    }
	scroll_x = 0;
	multi_vram_buffer_horz((const char*)attemptstex,sizeof(attemptstex)-1,NTADR_C(7, 15));    	
	
	TOTALCOINSONES = 0;
	TOTALCOINSTENS = 0;
	TOTALATTEMPTSHUNDREDS = 0;
	TOTALATTEMPTSTHOUSANDS = 0;
	
	TOTALCOINSTEMP = attempts;
	
	while (TOTALCOINSTEMP > 9) {
		TOTALCOINSTENS++;
		TOTALCOINSTEMP = TOTALCOINSTEMP - 10;
		if (TOTALCOINSTENS == 10) {
			TOTALCOINSTENS = 0;
			TOTALATTEMPTSHUNDREDS++;
		}
		if (TOTALATTEMPTSHUNDREDS == 10) {
			TOTALATTEMPTSHUNDREDS = 0;
			TOTALATTEMPTSTHOUSANDS++;
		}
	}
	TOTALCOINSONES = TOTALCOINSTEMP;

	if (TOTALATTEMPTSTHOUSANDS >= 10) {
		multi_vram_buffer_horz((const char*)wtxt,sizeof(wtxt)-1,NTADR_C(15, 15));
		multi_vram_buffer_horz((const char*)htxt,sizeof(htxt)-1,NTADR_C(16, 15));
		multi_vram_buffer_horz((const char*)atxt,sizeof(atxt)-1,NTADR_C(17, 15));
		multi_vram_buffer_horz((const char*)rtxt,sizeof(rtxt)-1,NTADR_C(18, 15));


	}

	else {
		if (TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xf5+TOTALATTEMPTSTHOUSANDS, NTADR_C(15,15));
		if (TOTALATTEMPTSHUNDREDS || TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xf5+TOTALATTEMPTSHUNDREDS, NTADR_C(16,15));
		if (TOTALATTEMPTSHUNDREDS || TOTALCOINSTENS || TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xf5+TOTALCOINSTENS, NTADR_C(17,15));
		one_vram_buffer(0xf5+TOTALCOINSONES, NTADR_C(18,15));		
	}
}
