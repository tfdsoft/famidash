// prototype
void init_sprites(void);

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
    set_data_pointer((char *)active_level[0]);
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
}
