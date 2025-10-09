
CODE_BANK_PUSH("XCD_BANK_01")

void wave_eject();
void wave_movement(void){

	if (!dashing[currplayer]) {
		
		currplayer_vel_y = !mini ? (currplayer_gravity ? -currplayer_vel_x : currplayer_vel_x) : (currplayer_gravity ? -(currplayer_vel_x << 1) : (currplayer_vel_x << 1));
		
		if (controllingplayer->a) currplayer_vel_y = -currplayer_vel_y;

		if (controllingplayer->press_a) jumps++;

		if (!slope_frames && !was_on_slope_counter) {
			currplayer_y += currplayer_vel_y;
		} else {
			currplayer_vel_y = 0;
		}

	}	
	else if (dashing[currplayer] == 2) { currplayer_vel_y = -currplayer_vel_x; currplayer_y += currplayer_vel_y; }
	else if (dashing[currplayer] == 3) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else if (dashing[currplayer] == 4) { currplayer_vel_y = currplayer_vel_x; currplayer_y -= currplayer_vel_y; }	
	else if (dashing[currplayer] == 5) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else currplayer_vel_y = 1;

	Generic.x = high_byte(currplayer_x);
	
	// this literally offsets the collision down 2 pixel for the vel reset to happen every frame instead of each other frame
	Generic.y = high_byte(currplayer_y) + ((high_byte(currplayer_vel_y) & 0x80) ? 2 : -2);
	
	

	wave_eject();
	
	if (bigboi) {
		Generic.y -= 15;
		wave_eject();		
		Generic.x += 15;
		wave_eject();		
		Generic.y += 15;
		wave_eject();		
	}
	
	else {
		if (longmode) {
			Generic.x += 15;
			wave_eject();				
		}
		if (tallmode) {
			Generic.x = high_byte(currplayer_x);
			Generic.y -= 15;
			wave_eject();				
		}
	}

	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);

	if (currplayer_vel_y != 0 && !slope_type){
		if(controllingplayer->press_a) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);
		}
	}
	
}	



void wave_eject() {
	if(high_byte(currplayer_vel_y) & 0x80){
		if (bg_coll_U()) {
			if(dblocked[currplayer]){ // check collision above
				high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U;
				currplayer_vel_y = 0;
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);			
			} else {
				idx8_store(cube_data, currplayer, cube_data[currplayer] | 1);		
			}
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
			if (dblocked[currplayer]) {
				high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
				currplayer_vel_y = 0;
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);		    
			} else {
				idx8_store(cube_data, currplayer, cube_data[currplayer] | 1);		
			}
		}
	}
}

CODE_BANK_POP()
