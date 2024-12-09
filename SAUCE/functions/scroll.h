
CODE_BANK_PUSH("XCD_BANK_02")


#define player0_x currplayer_x
#define player1_x player_x[1]

#define player0_y currplayer_y
#define player1_y player_y[1]
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

	if (player0_x > curr_x_scroll_stop){ // change x scroll
		tmp1 = MSB(player0_x - curr_x_scroll_stop);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(player0_x) = high_byte(player0_x) - tmp1;
		high_byte(player1_x) = high_byte(player1_x) - tmp1;
	}
	else if (player0_x < 0x0200){ // change x scroll
		tmp1 = MSB(player0_x + 0x0200);
		scroll_x = scroll_x - tmp1;
		if (tmp1) {
			if (tmp1 > parallax_scroll_x) {	// sorta yoda notation
				parallax_scroll_x += 144;
			}
			parallax_scroll_x -= tmp1 - 1;
		}
		
		high_byte(player0_x) = high_byte(player0_x) + tmp1;
		high_byte(player1_x) = high_byte(player1_x) + tmp1;
	}


	
	
	
	
	if ((!dual || twoplayer) && (gamemode == GAMEMODE_CUBE || gamemode == GAMEMODE_ROBOT || nocamlock)) {
			if (exitPortalTimer) exitPortalTimer--;
			if (player0_y < 0x4000 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
				tmp1 = MSB(0x4000 - player0_y);
				if (exitPortalTimer && tmp1 >= (11 - exitPortalTimer)) tmp1 = 11 - exitPortalTimer;
				scroll_y = sub_scroll_y(tmp1, scroll_y);

				high_byte(player0_y) = high_byte(player0_y) + tmp1;
				high_byte(player1_y) = high_byte(player1_y) + tmp1;
			}
			cap_scroll_y_at_top();

			
			if (high_byte(player0_y) >= MSB(0xA000)){ // change y scroll (upward)
				tmp1 = MSB(player0_y - 0xA000);
				if (exitPortalTimer && tmp1 >= (11 - exitPortalTimer)) tmp1 = 11 - exitPortalTimer;
				scroll_y = add_scroll_y(tmp1, scroll_y);
				if (high_byte(scroll_y) < MSB(0x300)) {
					high_byte(player0_y) = high_byte(player0_y) - tmp1;
					high_byte(player1_y) = high_byte(player1_y) - tmp1;
				}
			}
			if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
	}
	else {			//ship stuff
		if (high_byte(target_scroll_y) >= 0xf0) {
			target_scroll_y += 0x10;
		}
		if (target_scroll_y > scroll_y) {
			scroll_y = add_scroll_y(2, scroll_y);
			high_byte(player0_y) -= 2;
			high_byte(player1_y) -= 2;
		}
		if (target_scroll_y < scroll_y) {
			scroll_y = sub_scroll_y(2, scroll_y);
			
			high_byte(player0_y) += 2;
			high_byte(player1_y) += 2;
		}
		cap_scroll_y_at_top();
		while (scroll_y > 0x2EF) {		//down
			scroll_y = sub_scroll_y(1, scroll_y);
			high_byte(player0_y) += 1;
			high_byte(player1_y) += 1;
		}
	}

    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}

CODE_BANK_POP()
