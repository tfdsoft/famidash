
CODE_BANK_PUSH("CODE")

void slope_vel() {
	switch (tmp8 & SLOPE_DEGREES_MASK) {
		case SLOPE_22DEG:
			tmp5 = currplayer_vel_x >> 1;
			break;
		case SLOPE_45DEG:
			tmp5 = currplayer_vel_x;
			break;
		case SLOPE_66DEG:
			tmp5 = (currplayer_vel_x << 1); 	
	}
}

void apply_slope_vel() {
	tmp8 = currplayer_slope_type;
	slope_vel();
	if ((currplayer_slope_type & SLOPE_RISING)) {
		if ((currplayer_slope_type & SLOPE_UPSIDEDOWN)) {
			currplayer_vel_y = tmp5;
		} else {
			currplayer_vel_y = -tmp5;
		}
	} else {
		if ((currplayer_slope_type & SLOPE_UPSIDEDOWN)) {
			currplayer_vel_y = -tmp5;
		} else {
			currplayer_vel_y = tmp5;
		}
	}
}

void x_movement_coll() {
  mmc3_set_prg_bank_1(GET_BANK(bg_coll_R));

	if (currplayer_slope_frames) {
		currplayer_slope_frames -= 1;
		if (currplayer_slope_type) {
		// we we're on an slope and now we aren't, so push the player upwards a bit
			apply_slope_vel();
		}
	}
	
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	// no L/R collision required, since that is accounted for with the death script
	if (high_byte(currplayer_x) > 0x10) {
		bg_coll_floor_spikes(); // check for spikes at the left of the player (fixes standing on spikes)
		if (bg_coll_R()) {
			if (!(options & platformer) && !force_platformer) {idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);}
			else {currplayer_vel_x = 0; }
		}
	}
  
}

void x_movement(){
  mmc3_set_prg_bank_1(GET_BANK(bg_coll_R));
    // handle x

	old_x = currplayer_x;
	
	currplayer_vel_x = ind16BE_load_NOC(CUBE_SPEED(framerate), speed);
	
//	if (controllingplayer->hold & PAD_LEFT) currplayer_vel_x = 0;
	
	if (dashing[currplayer] == 4 || dashing[currplayer] == 5) {	
		if (currplayer_y < 0x0600 && scroll_y == min_scroll_y){
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
		}
		//return; 
	}

	if (gamemode == GAMEMODE_WAVE) { // wave
		Generic.width = WAVE_WIDTH;
		Generic.height = WAVE_HEIGHT;
	} else {
		Generic.width = CUBE_WIDTH[currplayer_mini];
		Generic.height = CUBE_HEIGHT[currplayer_mini];
	}

	Generic.x = high_byte(currplayer_x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(currplayer_y);

	if (!(options & platformer) && !force_platformer) {
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
			high_byte(currplayer_x) -= ((tmp7 + 4) & 0x07) - 4 + currplayer_mini; // if mini put it a pixel left-er
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


	if (!wrap_mode) {
		if (currplayer_y < 0x0600 && !dual && !twoplayer){
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
		}
		

		else if (!(controllingplayer->hold & (PAD_A | PAD_UP))) idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
	}
	else {
		if (currplayer_y < 0x0600 && !dual && !twoplayer){
			currplayer_y = 0xF900;
		}		
		else if (currplayer_y > 0xF900 && !dual && !twoplayer){
			currplayer_y = 0x0600;
		}		
		else if (!(controllingplayer->hold & (PAD_A | PAD_UP))) idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
	}
}


CODE_BANK_POP()
