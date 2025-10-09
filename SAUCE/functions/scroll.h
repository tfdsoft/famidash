
CODE_BANK_PUSH("XCD_BANK_02")

void do_the_scroll_thing(){
	switch (cam_seesaw) {
		case 1:
			if (curr_x_scroll_stop < 0xD000) target_x_scroll_stop = 0xD000;
			else cam_seesaw = 2;
			break;
		case 2:
			if (curr_x_scroll_stop > 0x1000) target_x_scroll_stop = 0x1000;
			else cam_seesaw = 1;
			break;
	}


	if (!kandodebugmode) {
		if (curr_x_scroll_stop < target_x_scroll_stop) curr_x_scroll_stop += 0x80;
		else if (curr_x_scroll_stop > target_x_scroll_stop) curr_x_scroll_stop -= 0x80;		
	}
	else {
		if (curr_x_scroll_stop < target_x_scroll_stop) curr_x_scroll_stop += 0x180;
		else if (curr_x_scroll_stop > target_x_scroll_stop) curr_x_scroll_stop -= 0x180;		
	}		

	if (currplayer_x > curr_x_scroll_stop){ // change x scroll
		tmp1 = MSB(currplayer_x - curr_x_scroll_stop);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(currplayer_x) = high_byte(currplayer_x) - tmp1;
	}
	else if (currplayer_x < 0x0200){ // change x scroll
		tmp1 = MSB(currplayer_x + 0x0200);
		scroll_x = scroll_x - tmp1;
		if (tmp1) {
			if (tmp1 > parallax_scroll_x) {	// sorta yoda notation
				parallax_scroll_x += 144;
			}
			parallax_scroll_x -= tmp1 - 1;
		}
		high_byte(currplayer_x) = high_byte(currplayer_x) + tmp1;
	}


	
	
	
	
	if (gamemode == 0 || gamemode == 4 || nocamlock) {
		if (!dual) {
			if (currplayer_y < 0x4000 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
				tmp1 = MSB(0x4000 - currplayer_y);
				scroll_y = sub_scroll_y(tmp1, scroll_y);

				high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
			}
			cap_scroll_y_at_top();

			
			if (high_byte(currplayer_y) >= MSB(0xA000)){ // change y scroll (upward)
				tmp1 = MSB(currplayer_y - 0xA000);
				scroll_y = add_scroll_y(tmp1, scroll_y);
				if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
			}
			if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
		}
		else {
			if (currplayer_y < 0x0700 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
				tmp1 = MSB(0x0700 - currplayer_y);
				scroll_y = sub_scroll_y(tmp1, scroll_y);
				high_byte(currplayer_y) += tmp1;
			}
			cap_scroll_y_at_top();

			
			if (high_byte(currplayer_y) >= MSB(0xF000)){ // change y scroll (upward)
				tmp1 = MSB(currplayer_y - 0xF000);
				scroll_y = add_scroll_y(tmp1, scroll_y);
				if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
			}
			if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
		}
	}
	else {			//ship stuff
		if (target_scroll_y > scroll_y + 0x20) {
			scroll_y = add_scroll_y(2, scroll_y);
			high_byte(currplayer_y) -= 2;
		}
		if (target_scroll_y < scroll_y + 0x20) {
			scroll_y = sub_scroll_y(2, scroll_y);
			high_byte(currplayer_y) += 2;
		}
		cap_scroll_y_at_top();
		while (scroll_y > 0x2EF) {		//down
			scroll_y = sub_scroll_y(1, scroll_y);
			high_byte(currplayer_y) += 1;
		}
	}

    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}
void do_the_scroll_thing2(){

    
	if (currplayer_x > curr_x_scroll_stop){ // change x scroll
		tmp1 = MSB(currplayer_x - curr_x_scroll_stop);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(currplayer_x) = high_byte(currplayer_x) - tmp1;
	}


	if (!dual) {
		if (currplayer_y < 0x4000 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
			tmp1 = MSB(0x4000 - currplayer_y);
			scroll_y = sub_scroll_y(tmp1, scroll_y);
			high_byte(currplayer_y) += tmp1;
		}
		cap_scroll_y_at_top();

		
		if (high_byte(currplayer_y) >= MSB(0xA000)){ // change y scroll (upward)
			tmp1 = MSB(currplayer_y - 0xA000);
			scroll_y = add_scroll_y(tmp1, scroll_y);
			if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
		}
		if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
	}
	else {
		if (currplayer_y < 0x0700 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
			tmp1 = MSB(0x0700 - currplayer_y);
			scroll_y = sub_scroll_y(tmp1, scroll_y);
			high_byte(currplayer_y) += tmp1;
		}
		cap_scroll_y_at_top();

		
		if (high_byte(currplayer_y) >= MSB(0xF000)){ // change y scroll (upward)
			tmp1 = MSB(currplayer_y - 0xF000);
			scroll_y = add_scroll_y(tmp1, scroll_y);
			if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
		}
		if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
	}


    set_scroll_x(scroll_x);
 //   set_scroll_y(scroll_y);

}

CODE_BANK_POP()
