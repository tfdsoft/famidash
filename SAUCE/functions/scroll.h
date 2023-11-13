void do_the_scroll_thing(){
    
	if (player.x > 0x3000){ // change x scroll
		tmp1 = (player.x - 0x3000) >> 8;
		scroll_x += tmp1;
		high_byte(player.x) = high_byte(player.x) - tmp1;
	}



	if (player.y < 0x3c00){ // change y scroll (upward)
		tmp1 = (0x3c00 - player.y) >> 8;
		scroll_y -= tmp1;
		high_byte(player.y) = high_byte(player.y) + tmp1;
	}

	if (player.y > 0xb100){ // change y scroll (upward)
		tmp1 = (player.y - 0xb100) >> 8;
		scroll_y += tmp1;
		high_byte(player.y) = high_byte(player.y) - tmp1;
	}

	

    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}