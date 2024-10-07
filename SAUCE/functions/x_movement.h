
CODE_BANK_PUSH("XCD_BANK_02")

const unsigned short speed_table[] = {
	CUBE_SPEED_X1, CUBE_SPEED_X05, CUBE_SPEED_X2, CUBE_SPEED_X3, CUBE_SPEED_X4
};


void x_movement(){
    // handle x

	old_x = currplayer_x;
	
	currplayer_vel_x = speed_table[speed & 0x7F];
	
	if (dashing[currplayer] == 4 || dashing[currplayer] == 5) {	
		if (currplayer_y < 0x0600 && scroll_y == min_scroll_y){
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
		}
		return; 
	}

	if (gamemode == 0x06) { // wave
		if (mini) {
			Generic.width = MINI_WAVE_WIDTH;
			Generic.height = MINI_WAVE_HEIGHT;
		} else {
			Generic.width = WAVE_WIDTH;
			Generic.height = WAVE_HEIGHT;
		}
	} else {
		if (!mini) {
			Generic.width = CUBE_WIDTH;
			Generic.height = CUBE_HEIGHT;
		} else {
			Generic.width = MINI_CUBE_WIDTH;
			Generic.height = MINI_CUBE_HEIGHT;
		}   
	}

	Generic.x = high_byte(currplayer_x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(currplayer_y);

	if (!(options & platformer)) {
		if ((controllingplayer->left) && !twoplayer && DEBUG_MODE) currplayer_x -= currplayer_vel_x;
		else currplayer_x += currplayer_vel_x;
	} else {
		// leave the col calls first so it executes and checks against spike collision
		tmp7 = bg_coll_R();
		tmp8 = bg_coll_L();

		if (!tmp7 && (controllingplayer->right)) currplayer_x += currplayer_vel_x;
		else if (!tmp8 && controllingplayer->left && currplayer_x > 0x1000) currplayer_x -= currplayer_vel_x;
		else currplayer_vel_x = 0;


		if (tmp7 && (controllingplayer->right)) {
			tmp7 = high_byte(currplayer_x) + low_word(scroll_x);
			high_byte(currplayer_x) -= ((tmp7 + 4) & 0x07) - 4 + mini; // if mini put it a pixel left-er
		}
		else if (tmp8 && (controllingplayer->left)) {
			tmp8 = high_byte(currplayer_x) + low_word(scroll_x);
			high_byte(currplayer_x) -= ((tmp8 + 4) & 0x07) - 4;
		} 
	}

	if(currplayer_x > 0xf000) { // too far, don't wrap around
        if(old_x >= 0xf000){
            currplayer_x = 0xf000; // max right
        } else{
            currplayer_x = 0x0000; // max left
        }
		currplayer_vel_x = 0;
	} 


	if (currplayer_y < 0x0600 && scroll_y <= min_scroll_y){
		idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
	}
	

	else if (!(controllingplayer->a)) idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
}


CODE_BANK_POP();
