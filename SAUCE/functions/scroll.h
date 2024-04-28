#pragma code-name(push, "XCD_BANK_02")
#pragma data-name(push, "XCD_BANK_02")
#pragma rodata-name(push, "XCD_BANK_02")


void do_the_scroll_thing(){

	#define curr_x tmp5
	#define curr_y tmp6

	curr_x = player_x[currplayer & 0x7F];
	curr_y = player_y[currplayer & 0x7F];
    
	if (curr_x > 0x5000){ // change x scroll
		tmp1 = MSB(curr_x - 0x5000);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(curr_x) = high_byte(curr_x) - tmp1;
	}

	if (!dual) {
		if (curr_y < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x4000 - curr_y);
			scroll_y -= tmp1;
			high_byte(curr_y) = high_byte(curr_y) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(curr_y);
		}

		
		if (curr_y > 0xA000){ // change y scroll (upward)
			tmp1 = MSB(curr_y - 0xA000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(curr_y) = high_byte(curr_y) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}
	else {
		if (curr_y < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x0700 - curr_y);
			scroll_y -= tmp1;
			high_byte(curr_y) = high_byte(curr_y) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(curr_y);
		}

		
		if (curr_y > 0xF000){ // change y scroll (upward)
			tmp1 = MSB(curr_y - 0xF000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(curr_y) = high_byte(curr_y) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}


    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);

	store_short_arr_NOC(player_x, currplayer, curr_x);
	store_short_arr_NOC(player_y, currplayer, curr_y);
}
void do_the_scroll_thing2(){

	curr_x = player_x[currplayer & 0x7F];
	curr_y = player_y[currplayer & 0x7F];
    
	if (curr_x > 0x5000){ // change x scroll
		tmp1 = MSB(curr_x - 0x5000);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(curr_x) = high_byte(curr_x) - tmp1;
	}


	if (!dual) {
		if (curr_y < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x4000 - curr_y);
			scroll_y -= tmp1;
			high_byte(curr_y) = high_byte(curr_y) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(curr_y);
		}

		
		if (curr_y > 0xA000){ // change y scroll (upward)
			tmp1 = MSB(curr_y - 0xA000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(curr_y) = high_byte(curr_y) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}
	else {
		if (curr_y < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x0700 - curr_y);
			scroll_y -= tmp1;
			high_byte(curr_y) = high_byte(curr_y) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(curr_y);
		}

		
		if (curr_y > 0xF000){ // change y scroll (upward)
			tmp1 = MSB(curr_y - 0xF000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(curr_y) = high_byte(curr_y) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}


    set_scroll_x(scroll_x);
 //   set_scroll_y(scroll_y);

 	store_short_arr_NOC(player_x, currplayer, curr_x);
	store_short_arr_NOC(player_y, currplayer, curr_y);

	#undef curr_x
	#undef curr_y
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
