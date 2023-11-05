void init_rld(void){
    rld_i = 0;
    rld_j = 0;
    rld_tmp = 0;
    rld_run = 0;    // amount of tiles to place
    rld_value = 0;  // the tile to repeat
}

void load_next_column(unsigned char level, unsigned char column){
    rld_j = 0;
    if (column == 0) {
        rld_value = level_list[level][0]; // set the value and run to the first tile type and length
        rld_run = level_list[level][1];
    }
    while (rld_j < 27) { // level is 27 tiles high, so run for 27 tiles
        columnBuffer[rld_j] = rld_value; // write a value to the column buffer

        --rld_run; // decrement run by 1
        ++rld_j; // increment column buffer write location
        if (rld_run == 0){
            ++rld_i; // go to the next rle index in the level data
            rld_value = level_list[level][rld_i*2]; // set the value and run to the next tile type and length
            rld_run = level_list[level][(rld_i*2)+1];
        }
    }
    
    rld_j = 0;
    while (rld_j < 27) { // write the column buffer to the collision map
        rld_tmp = columnBuffer[rld_j];
        collisionMap[(rld_j<<4)+column] = rld_tmp;
        // NEVER use two pointers on the same line.
        // it will compile to 55 instructions whereas doing the above compiles to just 10
        ++rld_j;
    }
}



void load_first_screen(unsigned char level){
    tmp1 = 0x00;
    while (!(tmp1 & 0x08)){
        load_next_column(level, (tmp1<<1));
        load_next_column(level, (tmp1<<1)+1);
        ++tmp1;
    }
    

    set_data_pointer(collisionMap);
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
}

void draw_screen_R(){

}