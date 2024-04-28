#pragma code-name(push, "XCD_BANK_02")
#pragma data-name(push, "XCD_BANK_02")
#pragma rodata-name(push, "XCD_BANK_02")


void do_the_scroll_thing(){
    
	if (player_x_curr > 0x5000){ // change x scroll
		tmp1 = MSB(player_x_curr - 0x5000);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(player_x_curr) = high_byte(player_x_curr) - tmp1;
	}

	if (!dual) {
		if (player_y_curr < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x4000 - player_y_curr);
			scroll_y -= tmp1;
			high_byte(player_y_curr) = high_byte(player_y_curr) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(player_y_curr);
		}

		
		if (player_y_curr > 0xA000){ // change y scroll (upward)
			tmp1 = MSB(player_y_curr - 0xA000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(player_y_curr) = high_byte(player_y_curr) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}
	else {
		if (player_y_curr < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x0700 - player_y_curr);
			scroll_y -= tmp1;
			high_byte(player_y_curr) = high_byte(player_y_curr) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(player_y_curr);
		}

		
		if (player_y_curr > 0xF000){ // change y scroll (upward)
			tmp1 = MSB(player_y_curr - 0xF000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(player_y_curr) = high_byte(player_y_curr) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}


    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}
void do_the_scroll_thing2(){

    
	if (player_x_curr > 0x5000){ // change x scroll
		tmp1 = MSB(player_x_curr - 0x5000);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(player_x_curr) = high_byte(player_x_curr) - tmp1;
	}


	if (!dual) {
		if (player_y_curr < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x4000 - player_y_curr);
			scroll_y -= tmp1;
			high_byte(player_y_curr) = high_byte(player_y_curr) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(player_y_curr);
		}

		
		if (player_y_curr > 0xA000){ // change y scroll (upward)
			tmp1 = MSB(player_y_curr - 0xA000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(player_y_curr) = high_byte(player_y_curr) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}
	else {
		if (player_y_curr < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x0700 - player_y_curr);
			scroll_y -= tmp1;
			high_byte(player_y_curr) = high_byte(player_y_curr) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(player_y_curr);
		}

		
		if (player_y_curr > 0xF000){ // change y scroll (upward)
			tmp1 = MSB(player_y_curr - 0xF000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(player_y_curr) = high_byte(player_y_curr) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}


    set_scroll_x(scroll_x);
 //   set_scroll_y(scroll_y);

}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
