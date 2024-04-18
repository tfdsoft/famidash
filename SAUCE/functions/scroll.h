#pragma code-name(push, "EXT_BANK_01")
#pragma data-name(push, "EXT_BANK_01")
#pragma rodata-name(push, "EXT_BANK_01")


void do_the_scroll_thing(){
    
	if (player_x[currplayer] > 0x5000){ // change x scroll
		tmp1 = (player_x[currplayer] - 0x5000) >> 8;
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(player_x[currplayer]) = high_byte(player_x[currplayer]) - tmp1;
	}


	if (player_y[currplayer] < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
		tmp1 = (0x4000 - player_y[currplayer]) >> 8;
		scroll_y -= tmp1;
		high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) + tmp1;
	}
	while (scroll_y < 0x08) {
		++scroll_y;
		--high_byte(player_y[currplayer]);
	}


	if (player_y[currplayer] > 0xA000){ // change y scroll (upward)
		tmp1 = (player_y[currplayer] - 0xA000) >> 8;
		scroll_y += tmp1;
		high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - tmp1;
	}
	while (scroll_y > 0xEF) {
		--scroll_y;
		++high_byte(player_y[currplayer]);
	}


    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}
void do_the_scroll_thing2(){
    
	if (player_x[currplayer] > 0x5000){ // change x scroll
		tmp1 = (player_x[currplayer] - 0x5000) >> 8;
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(player_x[currplayer]) = high_byte(player_x[currplayer]) - tmp1;
	}


	if (player_y[currplayer] < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
		tmp1 = (0x4000 - player_y[currplayer]) >> 8;
		scroll_y -= tmp1;
		high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) + tmp1;
	}
	while (scroll_y < 0x08) {
		++scroll_y;
		--high_byte(player_y[currplayer]);
	}


	if (player_y[currplayer] > 0xA000){ // change y scroll (upward)
		tmp1 = (player_y[currplayer] - 0xA000) >> 8;
		scroll_y += tmp1;
		high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - tmp1;
	}
	while (scroll_y > 0xEF) {
		--scroll_y;
		++high_byte(player_y[currplayer]);
	}


    set_scroll_x(scroll_x);
 //   set_scroll_y(scroll_y);
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
