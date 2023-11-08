void load_ground(unsigned char id){
    vram_adr(NAMETABLE_C);
    vram_unrle(ground[id]);
}

void unrle_first_screen(void){ // run-length decode the first screen of a level
    tmp1 = 0x00;
    while (!(tmp1 & 0x08)){
        unrle_next_column();
        unrle_next_column();
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



void wait_hang_on_should_i_write_to_the_collision_map(){
	
	if ((rld_column == x>>4)){
		unrle_next_column();
		unrle_next_column();
	}
	// I'M BANGING MY HEAD AGAINST THE WALL TRYING TO FIGURE OUT THE MATH FOR THIS
	// basically, for every two tiles scrolled, write two
	// new columns to the buffer before drawing 
}



void draw_screen_R(void){
	//scrolling to the right, draw metatiles as we go
	pseudo_scroll_x = high_byte(scroll_x) + 0x100;
	
	x = pseudo_scroll_x;
	tmp4 = x >> 4;

	wait_hang_on_should_i_write_to_the_collision_map();

	if (!(scroll_count & 4)){
		set_data_pointer(active_level[0]);
		switch(scroll_count & 3){
			case 0:
				address = get_ppu_addr(0, x, 0);
				index = 0 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
			
				address = get_ppu_addr(0, x, 0x20);
				index = 0x20 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
	            break;
			
			case 1:
				address = get_ppu_addr(0, x, 0x40);
				index = 0x40 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
			
				address = get_ppu_addr(0, x, 0x60);
				index = 0x60 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
				break;
			
			case 2:
				address = get_ppu_addr(0, x, 0x80);
				index = 0x80 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
			
				address = get_ppu_addr(0, x, 0xa0);
				index = 0xa0 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
				break;
			
			case 3:
				address = get_ppu_addr(0, x, 0xc0);
				index = 0xc0 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
			
				address = get_ppu_addr(0, x, 0xe0);
				index = 0xe0 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
        	    break;
		}
	} else {
		set_data_pointer(active_level[1]);
		switch(scroll_count & 3){
			case 0:
				address = get_ppu_addr(2, x, 0);
				index = 0 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
			
				address = get_ppu_addr(2, x, 0x20);
				index = 0x20 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
	            break;
			
			case 1:
				address = get_ppu_addr(2, x, 0x40);
				index = 0x40 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
			
				address = get_ppu_addr(2, x, 0x60);
				index = 0x60 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
				break;
			
			case 2:
				address = get_ppu_addr(2, x, 0x80);
				index = 0x80 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
			
				address = get_ppu_addr(2, x, 0xa0);
				index = 0xa0 + (tmp4);
				buffer_4_mt(address, index); // ppu_address, index to the data
				break;
		}
	}

	++scroll_count;
	scroll_count &= 7; //mask off top bits, keep it 0-3
}

