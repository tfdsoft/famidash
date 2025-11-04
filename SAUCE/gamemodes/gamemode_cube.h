
CODE_BANK_PUSH(MOVEMENT_BANK)

void slope_jump_check();
void x_movement_coll();
void common_gravity_routine();
void cube_eject();
void slope_vel();
void cube_movement(){
// handle y

// gravity[currplayer]
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){

	tmpfallspeed = CUBE_MAX_FALLSPEED(currplayer_table_idx);
	tmpgravity = CUBE_GRAVITY(currplayer_table_idx);

	if (max_fallspeed == 0x07) {
			tmpfallspeed += DASH_END_VEL_RESET(currplayer_table_idx);
	}

	common_gravity_routine();

	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	
	
	cube_eject();
	

	if (bigboi) {

		Generic.x += 15;

		cube_eject();

		Generic.y -= 15;

		cube_eject();		
		
		Generic.x -= 15;
		
		cube_eject();

	}

	else {
		if (longmode) {

			Generic.x += 15;
			
			cube_eject();
		}
		
		if (tallmode) {
			Generic.x = high_byte(currplayer_x);
			Generic.y -= 15;
			
			cube_eject();
		}		
	}	
	// check collision down a little lower than CUBE
	Generic.x = high_byte(currplayer_x); // the rest should be the same
	Generic.y = high_byte(currplayer_y); // the rest should be the same




	if ((gamemode == GAMEMODE_CUBE && currplayer_vel_y == 0 && dashing[currplayer] == 0) || (gamemode == GAMEMODE_CUBE && (kandokidshack == 9 && dashing[currplayer] == 0)) || gamemode == GAMEMODE_NINJA){		//cube
		//if(bg_coll_D2()) {

			if (gamemode == GAMEMODE_NINJA && currplayer_vel_y == 0) ninjajumps[currplayer] = 3; //ninja jump reset

			if (gamemode != GAMEMODE_NINJA) idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);				
			
			else {
				if (ninjajumps[currplayer]) idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
			}

			if((controllingplayer->hold & (PAD_A | PAD_UP)) && (!jblocked[currplayer] && !fblocked[currplayer] && !kandokidshack && gamemode == GAMEMODE_CUBE)) {			//no jblock - hold A to buffer jump
				if (!orbed[currplayer]) {
					jumps++;

					currplayer_vel_y = JUMP_VEL(currplayer_table_idx); // JUMP

					slope_jump_check();

				}
			
			}
			else if((controllingplayer->press & (PAD_A | PAD_UP)) && (jblocked[currplayer] || fblocked[currplayer] || kandokidshack || (gamemode == GAMEMODE_NINJA && ninjajumps[currplayer]))) {		//jblock making you release and press A again to jump
				jumps++;

				currplayer_vel_y = JUMP_VEL(currplayer_table_idx); // JUMP

				slope_jump_check();

				if (gamemode == GAMEMODE_NINJA) { idx8_dec(ninjajumps, currplayer); }
			
			}
	} else if (gamemode == GAMEMODE_ROBOT) {
		
		if (controllingplayer->press & (PAD_A | PAD_UP)) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0b100);	
		}


		if ((!retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer] && dashing[currplayer] == 0 && cube_data[currplayer] & 4) || (dashing[currplayer] == 0 && kandokidshack == 9)){		//robot
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);			
			if((controllingplayer->hold & (PAD_A | PAD_UP)) && !orbed[currplayer]) {
				jumps++;
				currplayer_vel_y = ROBOT_JUMP_VEL(currplayer_table_idx); // JUMP

				// robotjumptime[currplayer] = ROBOT_JUMP_TIME[framerate]
				__A__ = ROBOT_JUMP_TIME[framerate], __asm__("pha");
				idx8_store(robotjumptime, currplayer, (__asm__("pla"), __A__));
				robotjumpframe[0] = 1;
			}
		}
		
		else if (retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer] && dashing[currplayer] == 0 && cube_data[currplayer] & 4) {		//jim
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);		
			if((controllingplayer->hold & (PAD_A | PAD_UP)) && !orbed[currplayer]) {
				jumps++;
				currplayer_vel_y = ROBOT_JUMP_VEL(currplayer_table_idx); // JUMP
				
				// robotjumptime[currplayer] = ROBOT_JUMP_TIME[framerate]
				__A__ = ROBOT_JUMP_TIME[framerate], __asm__("pha");
				idx8_store(robotjumptime, currplayer, (__asm__("pla"), __A__));
				robotjumpframe[0] = 1;
			}
		}
		
		else if (robotjumptime[currplayer] && !hblocked[currplayer]) {
			
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 0b11111011);	
				cube_data[currplayer] = 0;
				if (robotjumptime[currplayer]) idx8_dec(robotjumptime, currplayer); 
				if((controllingplayer->hold & (PAD_A | PAD_UP)) && !jblocked[currplayer] && !orbed[currplayer]) {	
					jumps++;
					if (robotjumpframe[0]) robotjumpframe[0]++;
					if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
					currplayer_vel_y = ROBOT_JUMP_VEL(currplayer_table_idx); // JUMP
				}	
				else if((controllingplayer->press & (PAD_A | PAD_UP)) && jblocked[currplayer] && !orbed[currplayer]) {	
					jumps++;
					if (robotjumpframe[0]) robotjumpframe[0]++;
					if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
					currplayer_vel_y = ROBOT_JUMP_VEL(currplayer_table_idx); // JUMP
				}
				else { 
					robotjumptime[currplayer] = 0; robotjumpframe[0] = 0; 
				}
		}
		else if (currplayer_vel_y != 0){		
				robotjumpframe[0] = 3;
		}
	}
	fblocked[currplayer] = 0;
	hblocked[currplayer] = 0;
	jblocked[currplayer] = 0;
//jim's shit
	if (retro_mode && !dual) {
		if (controllingplayer->press_b && !practice_point_count) {
			tmp9 = 0;
			do {
				if (!jimsheatballalive[tmp9]) {
					jimsheatballframe[tmp9] = 0;
					jimsheatballalive[tmp9] = 1;
					if (controllingplayer->up) idx16_store_NOC(jimsheatball_vel_y, tmp9, JIMSHEATBALL_JUMP_VEL_d4x7(framerate));
					else idx16_store_NOC(jimsheatball_vel_y, tmp9, JIMSHEATBALL_JUMP_VEL(framerate));
					idx16_store_NOC(jimsheatballx, tmp9, high_byte(old_x));
					idx16_store_hi_NOC(jimsheatbally, tmp9, high_byte(player_y[0]));
					break;
				}
			} while (++tmp9 < MAX_FIREBALLS);

		}
	}
// done with jims shit	
// jims heat bomb:
	idx16_store_NOC(player_x, currplayer, currplayer_x);
	idx16_store_NOC(player_y, currplayer, currplayer_y);
	idx16_store_NOC(player_vel_x, currplayer, currplayer_vel_x);
	idx16_store_NOC(player_vel_y, currplayer, currplayer_vel_y);
	player_gravity[currplayer] = currplayer_gravity;

	if (retro_mode) {
		tmp9 = 0;
		do {
			if (jimsheatballalive[tmp9]) {

					
				currplayer_x = jimsheatballx[tmp9 & 0x7F];
				currplayer_y = jimsheatbally[tmp9 & 0x7F];
				currplayer_vel_x = jimsheatball_vel_x[tmp9 & 0x7F];
				currplayer_vel_y = jimsheatball_vel_y[tmp9 & 0x7F];
				currplayer_gravity = GRAVITY_DOWN;
				update_currplayer_table_idx();

				if(currplayer_vel_y > JIMSHEATBALL_MAX_FALLSPEED(framerate)){
					currplayer_vel_y += -JIMSHEATBALL_GRAVITY(framerate);
				} else currplayer_vel_y += JIMSHEATBALL_GRAVITY(framerate);
				currplayer_y += currplayer_vel_y;
				
				Generic.x = high_byte(currplayer_x);
				Generic.y = high_byte(currplayer_y);
				
			if (!(kandoframecnt & 3)) {
			//	x_movement_coll();
				if(bg_coll_D()){ // check collision below
					high_byte(currplayer_y) -= eject_D;
					low_byte(currplayer_y) = 0;
					currplayer_vel_y = JIMSHEATBALL_JUMP_VEL(framerate);
				}
			}
				if (cube_data[currplayer] & 1) { idx8_store(cube_data, currplayer, cube_data[currplayer] & 2); }
				idx16_store_NOC(jimsheatballx, tmp9, currplayer_x);
				idx16_store_NOC(jimsheatbally, tmp9, currplayer_y);
				idx16_store_NOC(jimsheatball_vel_x, tmp9, currplayer_vel_x);
				idx16_store_NOC(jimsheatball_vel_y, tmp9, currplayer_vel_y);
			}	
		} while (++tmp9 < MAX_FIREBALLS);
	}
	currplayer_x = player_x[currplayer & 0x7F];
	currplayer_y = player_y[currplayer & 0x7F];
	currplayer_vel_x = player_vel_x[currplayer & 0x7F];
	currplayer_vel_y = player_vel_y[currplayer & 0x7F];
	currplayer_gravity = player_gravity[currplayer];
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	update_currplayer_table_idx();
}	


void common_gravity_routine() {
	register int16_t tmpaccel;
	tmp1 = dashing[currplayer];
	if (!tmp1) {
		tmpaccel = tmpgravity;
		if((!currplayer_gravity ? currplayer_vel_y > tmpfallspeed : currplayer_vel_y < tmpfallspeed)){
			tmpaccel = -tmpaccel;
		}
		switch (gravity_mod) {
			case 0: break;
			case 1: tmpaccel /= 3; break;
			case 2: tmpaccel /= 2; break;
			case 3: tmpaccel = (tmpaccel / 3 * 2); break;
			case 4: tmpaccel *= 2; break;
		};
		currplayer_vel_y += tmpaccel;
	} else if (tmp1 == 2) {
		currplayer_vel_y = -currplayer_vel_x;
	} else if (tmp1 == 3) {
		currplayer_vel_y = currplayer_vel_x;
	} else if (tmp1 == 4) {
		currplayer_vel_y = currplayer_vel_x*2;
		currplayer_y -= currplayer_vel_y;
		return;
	} else if (tmp1 == 5) {
		currplayer_vel_y = currplayer_vel_x*2;
	} else {
		currplayer_vel_y = currplayer_gravity ? -1 : 1;
		return;
	}
	currplayer_y += currplayer_vel_y;
}


void cube_eject() {
	//if (!currplayer_was_on_slope_counter || currplayer_slope_type & SLOPE_UPSIDEDOWN) {
		if(!currplayer_gravity || (currplayer_gravity && (hblocked[currplayer] | fblocked[currplayer]))){
			if(bg_coll_D()){ // check collision below
				high_byte(currplayer_y) -= eject_D;
				low_byte(currplayer_y) = 0;
				if (!hblocked[currplayer]) {
					currplayer_vel_y = 0;
				} else {
					currplayer_vel_y = 0xffff;
				}
				orbactive = 0;
				if (fblocked[currplayer]) {
					currplayer_gravity = GRAVITY_DOWN;
					update_currplayer_table_idx();
				}
			}
		} 
	//}
	//if (!currplayer_was_on_slope_counter || !(currplayer_slope_type & SLOPE_UPSIDEDOWN)) {
		if (currplayer_gravity || (!currplayer_gravity && (hblocked[currplayer] | fblocked[currplayer]))) {
			if(bg_coll_U()){ // check collision above
				high_byte(currplayer_y) -= eject_U;
				low_byte(currplayer_y) = 0;
				if (!hblocked[currplayer]) {
					currplayer_vel_y = 0;
				} else {
					currplayer_vel_y = 1;
				}
				orbactive = 0;
				if (fblocked[currplayer]) {
					currplayer_gravity = GRAVITY_UP;
					update_currplayer_table_idx();
				}
			}
		}
	//}	
}		

void slope_jump_check() {
	if (make_cube_jump_higher) {
		if ((currplayer_slope_type & SLOPE_DEGREES_MASK) != SLOPE_22DEG) {
			currplayer_vel_y += MAKE_CUBE_JUMP_HIGHER(currplayer_table_idx);
		}
		make_cube_jump_higher = 0;
	}
}

CODE_BANK_POP()
