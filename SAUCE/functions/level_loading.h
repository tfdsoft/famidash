
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

void load_ground(unsigned char id){
	mmc3_set_prg_bank_1(0);
    vram_adr(NAMETABLE_C);
    vram_unrle(ground[id]);
}

void unrle_first_screen(void){ // run-length decode the first screen of a level
	mmc3_set_prg_bank_1(level_data_bank);
    tmp1 = 0x10;
    while (tmp1 != 0){
        unrle_next_column();
        --tmp1;
    }

    set_data_pointer((char *)active_level[0]);
    set_mt_pointer((char *)metatiles1);
	#define _y tmp1
	#define _x tmp2
    for(_y=0; ;_y+=0x20){
		for(_x=0; ;_x+=0x20){
	    	address = get_ppu_addr(0, _x, _y);
	    	index = (_y & 0xf0) + (_x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
	    	flush_vram_update2();
	    	if (_x == 0xe0) break;
	    }
	    if (_y == 0xe0) break;
    }
    set_data_pointer((char *)active_level[1]);
    for(_y=0; ;_y+=0x20){
		for(_x=0; ;_x+=0x20){
	    	address = get_ppu_addr(2, _x, _y);
	    	index = (_y & 0xf0) + (_x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
	    	flush_vram_update2();
	    	if (_x == 0xe0) break;
	    }
	    if (_y == 0xa0) break;
    }
	#undef _y
	#undef _x
}
