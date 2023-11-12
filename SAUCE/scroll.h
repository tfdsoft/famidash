void do_the_scroll_thing(){
    
	tmp5 = player.x;
	if (player.x > 0x3000){
		tmp1 = (player.x - 0x3000) >> 8;
        if (tmp1 > 3) tmp1 = 3; // max scroll change
		scroll_x += tmp1;
		high_byte(player.x) = high_byte(player.x) - tmp1;
	}

    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}