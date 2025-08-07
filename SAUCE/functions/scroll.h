
CODE_BANK_PUSH("XCD_BANK_04")


#define player0_x currplayer_x
#define player1_x player_x[1]

#define player0_y currplayer_y
#define player1_y player_y[1]

void process_x_scroll() {
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
		if (curr_x_scroll_stop < target_x_scroll_stop) curr_x_scroll_stop += 0x200;
		else if (curr_x_scroll_stop > target_x_scroll_stop) curr_x_scroll_stop -= 0x200;		
	} else {
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
	} else if (player0_x < 0x0200){ // change x scroll
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
}


void process_y_scroll() {
	if ((!dual || twoplayer) && (gamemode == GAMEMODE_CUBE || gamemode == GAMEMODE_ROBOT || gamemode == GAMEMODE_NINJA || nocamlock || nocamlockforced)) {
			if (exitPortalTimer) exitPortalTimer--;
			if (player0_y < 0x4000 && 
				(scroll_y >= min_scroll_y && (scroll_y_subpx || scroll_y != min_scroll_y))
				){
				// change y scroll (upward)
				cc65_ptr1 = 0x4000 - player0_y;
				if (exitPortalTimer) {
					cc65_tmp1 = (11 - exitPortalTimer);
					if (MSB(cc65_ptr1) >= cc65_tmp1) cc65_ptr1 = (cc65_tmp1) << 8;
				}
				scroll_y_subpx -= LSB(cc65_ptr1);
				do_if_borrow({++high_byte(cc65_ptr1);});
				scroll_y = sub_scroll_y(MSB(cc65_ptr1), scroll_y);

				player0_y = player1_y = 0x4000;	// This is how actual compensation does it anyway
			}
			cap_scroll_y_at_top();

			if (scroll_y < 0x2EF && high_byte(player0_y) >= MSB(0xA000)){
				// change y scroll (downward)
				cc65_ptr1 = player0_y - 0xA000;
				if (exitPortalTimer) {
					cc65_tmp1 = (11 - exitPortalTimer);
					if (MSB(cc65_ptr1) >= cc65_tmp1) cc65_ptr1 = (cc65_tmp1) << 8;
				}
				scroll_y_subpx += LSB(cc65_ptr1);
				do_if_carry({++high_byte(cc65_ptr1);});
				scroll_y = add_scroll_y(MSB(cc65_ptr1), scroll_y);

				player0_y = player1_y = 0xA000;	// This is how actual compensation does it anyway
			}
			cap_scroll_y_at_bottom();
	} else {			//ship stuff
		if (low_byte(target_scroll_y) >= 0xf0) {
			target_scroll_y += 0x10;
		}
		if (target_scroll_y > scroll_y) {
			scroll_y = add_scroll_y(2, scroll_y);
			high_byte(player0_y) -= 2;
			high_byte(player1_y) -= 2;	// !!TODO
		}
		if (target_scroll_y < scroll_y) {
			scroll_y = sub_scroll_y(2, scroll_y);
			
			high_byte(player0_y) += 2;
			high_byte(player1_y) += 2;	// !!TODO
		}
		cap_scroll_y_at_top();
		cap_scroll_y_at_bottom();
	}
}

void do_the_scroll_thing(){
	process_x_scroll();
	process_y_scroll();

    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}

CODE_BANK_POP()
