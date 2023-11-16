void do_the_scroll_thing(){
    
	if (player.x > 0x3000){ // change x scroll
		tmp1 = (player.x - 0x3000) >> 8;
		scroll_x += tmp1;
		high_byte(player.x) = high_byte(player.x) - tmp1;
	}



	if (player.y < 0x6000){ // change y scroll (upward)
		tmp1 = (0x6000 - player.y) >> 8;
		scroll_y -= tmp1;
		high_byte(player.y) = high_byte(player.y) + tmp1;
	}
	while (scroll_y < 0x10) {
		++scroll_y;
		--high_byte(player.y);
	}


	if (player.y > 0x8000){ // change y scroll (upward)
		tmp1 = (player.y - 0x8000) >> 8;
		scroll_y += tmp1;
		high_byte(player.y) = high_byte(player.y) - tmp1;
	}
	while (scroll_y > 0xEF) {
		--scroll_y;
		++high_byte(player.y);
	}


    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}