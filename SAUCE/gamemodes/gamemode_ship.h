
CODE_BANK_PUSH(MOVEMENT_BANK)

void bigboi_stuff();
void ufo_ship_eject();

void is_player_falling() {
	tmp1 = (currplayer_gravity ? (currplayer_vel_y < 0) : (currplayer_vel_y > 0));
}

void ship_movement(){
	is_player_falling();

	tmp2 = (controllingplayer->hold & (PAD_A | PAD_UP)) != 0; // input

	if (tmp2) { // holding
		tmpgravity = SHIP_GRAVITY_BASE(currplayer_table_idx);
	} else if (
		!tmp2 && // not holding
		!tmp1 // not falling
	){
		tmpgravity = SHIP_GRAVITY_AFTER_HOLD(currplayer_table_idx);
	} else {
		tmpgravity = SHIP_GRAVITY(currplayer_table_idx);
	}

	if (tmp2 && // holding
		tmp1 // falling
	){
		tmpgravity = SHIP_GRAVITY_HOLD_FALL(currplayer_table_idx);
	}

	if (tmp2 ^ (currplayer_gravity ? 1 : 0)) {
		tmpgravity = -tmpgravity;
	}

	// This because it is bigger and its needed
	tmpfallspeed = 0x4443;

	common_gravity_routine();

	// Sorry alex but cc65 didn't want to cooperate and i almost go crazy
	if (currplayer_gravity) {
		if(currplayer_vel_y < -0x0369) currplayer_vel_y = -0x0369;
		if(currplayer_vel_y > 0x0443) currplayer_vel_y = 0x0443;
	} else {
		if(currplayer_vel_y < -0x0443) currplayer_vel_y = -0x0443;
		if(currplayer_vel_y > 0x0369) currplayer_vel_y = 0x0369;
	}

	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);

	
	ufo_ship_eject();

	bigboi_stuff();
}

void ufo_ship_eject() {
	//if (!currplayer_was_on_slope_counter || currplayer_slope_type & SLOPE_UPSIDEDOWN) {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U - 1;
			currplayer_vel_y = 0;
		}
	//}
	//if (!currplayer_was_on_slope_counter || !(currplayer_slope_type & SLOPE_UPSIDEDOWN)) {
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
			currplayer_vel_y = 0;
		}
	//}
}	

CODE_BANK_POP()
