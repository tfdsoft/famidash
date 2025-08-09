
CODE_BANK_PUSH("XCD_BANK_01")

void ball_eject();
void common_gravity_routine();
void ball_movement(){
// handle y

	// currplayer_gravity
	// currplayer_vel_y is signed

//	if ((controllingplayer->press_a) && currplayer_vel_y != 0) idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);

	if (gamemode == GAMEMODE_SWING) {
		tmpfallspeed = SWING_MAX_FALLSPEED(currplayer_table_idx);
		tmpgravity = SWING_GRAVITY(currplayer_table_idx);
		common_gravity_routine();
	} else {		
		tmpfallspeed = BALL_MAX_FALLSPEED(currplayer_table_idx);
		tmpgravity = BALL_GRAVITY(currplayer_table_idx);
		common_gravity_routine();
	}
	
	Generic.x = high_byte(currplayer_x);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 1;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}

	//if (controllingplayer->press_a || controllingplayer->press_up) idx8_store(cube_data, currplayer, cube_data[currplayer] | 2);	

	ball_eject();

	if (bigboi) {
			Generic.y -= 15;

			ball_eject();
		
			Generic.x += 15;
			
			ball_eject();
		
			Generic.y += 15;

			ball_eject();
	}
	else {
		if (tallmode) {
			
			// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
			Generic.y -= 15;

			ball_eject();
		}	
		if (longmode) {
			
			Generic.x += 15;

			// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
			Generic.y = high_byte(currplayer_y);

			ball_eject();
		}
	}

	Generic.y = high_byte(currplayer_y);
	Generic.x = high_byte(currplayer_x);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 1;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}

	if (gamemode == GAMEMODE_BALL) {
		if (((controllingplayer->a || controllingplayer->up)) && (ball_switched[currplayer] == 0) && currplayer_vel_y == 0){
			jumps++;
			invert_gravity(currplayer_gravity);
			update_currplayer_table_idx();
			ball_switched[currplayer] = 1;
			currplayer_vel_y = BALL_SWITCH_VEL(currplayer_table_idx);
			bg_coll_floor_spikes();
		}
		if(ball_switched[currplayer]){
			if (!(controllingplayer->hold & (PAD_A | PAD_UP))){
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
				ball_switched[currplayer] = 0;			
			}
		}
	}
	else {
		if ((controllingplayer->press_a || controllingplayer->press_up) && !ufo_orbed){
			invert_gravity(currplayer_gravity);
			update_currplayer_table_idx();
			bg_coll_floor_spikes();
		}
	}		
	ufo_orbed = 0;
}

void ball_eject() {
	
		//if(high_byte(currplayer_vel_y) & 0x80){
			if(bg_coll_U()){ // check collision above
				high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U;
				currplayer_vel_y = 0;
				orbactive = 0;
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);			//fix for orb
			}
		//}
		//else{
			if(bg_coll_D()){ // check collision below
			    high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
			    currplayer_vel_y = 0;
				orbactive = 0;
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);		    //fix for orb
			}
		//}		

}	

CODE_BANK_POP()
