#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")


void do_the_scroll_thing(){
    
	if (player.x > 0x5000){ // change x scroll
		tmp1 = (player.x - 0x5000) >> 8;
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(player.x) = high_byte(player.x) - tmp1;
	}


	if (player.y < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
		tmp1 = (0x4000 - player.y) >> 8;
		scroll_y -= tmp1;
		high_byte(player.y) = high_byte(player.y) + tmp1;
	}
	while (scroll_y < 0x08) {
		++scroll_y;
		--high_byte(player.y);
	}


	if (player.y > 0xA000){ // change y scroll (upward)
		tmp1 = (player.y - 0xA000) >> 8;
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

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
