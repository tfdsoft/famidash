void init_rld(void){ // reset run-length decoder back to zero
    rld_i = 0;
    rld_j = 0;
    rld_tmp = 0;
    rld_run = 0;    // amount of tiles to place
    rld_value = 0;  // the tile to repeat
    rld_column = 0;
    rld_value = level_list[level][0]; // set the value and run to the first tile type and length
    rld_run = level_list[level][1];
}

void unrle_next_column(unsigned char level){ // this should explain itself
    rld_j = 0;
	level_data = (unsigned char *) level_list[level];
    while (rld_j < 27) { // level is 27 tiles high, so run for 27 tiles
        columnBuffer[rld_j] = rld_value; // write a value to the column buffer

        --rld_run; // decrement run by 1
        ++rld_j; // increment column buffer write location
        if (rld_run == 0){
            ++rld_i; // go to the next rle index in the level data
            rld_value = *(level_data++);
			rld_run = *(level_data++);
        }
    }
    
    rld_j = 0;
    while (rld_j < 27) { // write the column buffer to the collision map
        rld_tmp = columnBuffer[rld_j];
        collisionMap0[(rld_j<<4)+rld_column] = rld_tmp;
        // NEVER use two pointers on the same line.
        // it will compile to 55 instructions whereas doing the above compiles to just 10
        ++rld_j;
    }
    ++rld_column;
}



void unrle_first_screen(unsigned char lvl){ // run-length decode the first screen of a level
    tmp1 = 0x00;
    while (!(tmp1 & 0x08)){
        unrle_next_column(lvl);
        unrle_next_column(lvl);
        ++tmp1;
    }

    set_data_pointer(active_level[0]);
    set_mt_pointer(metatiles1);
    for(y=0; ;y+=0x20){
		for(x=0; ;x+=0x20){
	    	address = get_ppu_addr(0, x, y);
	    	index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
	    	flush_vram_update2();
	    	if (x == 0xe0) break;
	    }
	    if (y == 0xe0) break;
    }
    set_data_pointer(active_level[1]);
    for(y=0; ;y+=0x20){
		for(x=0; ;x+=0x20){
	    	address = get_ppu_addr(2, x, y);
	    	index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
	    	flush_vram_update2();
	    	if (x == 0xe0) break;
	    }
	    if (y == 0xa0) break;
    }
}





void draw_screen_R(void){
	// scrolling to the right, draw metatiles as we go
	low_byte(pseudo_scroll_x) = scroll_x + 0xF8;
	
	tmp1 = (pseudo_scroll_x >> 8);
	
	x = pseudo_scroll_x & 0xff;

	tmp2 = get_frame_count();
    tmp2 = tmp2 & 1;
	set_data_pointer(active_level[tmp2]);
	

	switch(scroll_count){
		case 0:
			address = get_ppu_addr(tmp2, x, 0);
			index = 0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(tmp2, x, 0x20);
			index = 0x20 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
            break;
			
		case 1:
			address = get_ppu_addr(tmp2, x, 0x40);
			index = 0x40 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(tmp2, x, 0x60);
			index = 0x60 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		case 2:
			address = get_ppu_addr(tmp2, x, 0x80);
			index = 0x80 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(tmp2, x, 0xa0);
			index = 0xa0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		case 3:
            if (tmp2 & 1) break;
			address = get_ppu_addr(tmp2, x, 0xc0);
			index = 0xc0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(tmp2, x, 0xe0);
			index = 0xe0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
            break;
	}

    set_data_pointer(active_level[1]);
    tmp2 = 2;
    

	++scroll_count;
	scroll_count &= 3; //mask off top bits, keep it 0-3
}