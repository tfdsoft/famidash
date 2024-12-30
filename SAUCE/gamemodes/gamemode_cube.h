
CODE_BANK_PUSH("XCD_BANK_01")

void x_movement_coll();
void common_gravity_routine();
void cube_eject();
void slope_vel();
void cube_movement(void){
// handle y

// gravity[currplayer]
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){

	if (retro_mode) { if (gamemode == GAMEMODE_CUBE) gamemode = GAMEMODE_ROBOT; }



	fallspeed_big = CUBE_MAX_FALLSPEED;
	fallspeed_mini = MINI_CUBE_MAX_FALLSPEED;
	gravity_big = CUBE_GRAVITY;
	gravity_mini = MINI_CUBE_GRAVITY;
	common_gravity_routine();

	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	
	if (gameState != 0) {
	
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
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);				

			if (gamemode == GAMEMODE_NINJA && currplayer_vel_y == 0) ninjajumps[currplayer] = 3; //ninja jump reset
			if((controllingplayer->a || controllingplayer->up) && (!jblocked[currplayer] && !fblocked[currplayer] && !kandokidshack && gamemode == GAMEMODE_CUBE)) {			//no jblock - hold A to buffer jump
				if (!orbed[currplayer]) {
					jumps++;

					if (!currplayer_mini) currplayer_vel_y = currplayer_gravity ? -JUMP_VEL : JUMP_VEL; // JUMP
					else currplayer_vel_y = currplayer_gravity ? -MINI_JUMP_VEL : MINI_JUMP_VEL; // JUMP


					if (make_cube_jump_higher) {
						if ((currplayer_slope_type & SLOPE_DEGREES_MASK) != SLOPE_22DEG) {
							currplayer_vel_y += (currplayer_gravity ? 0x80 : -0x80);
						}
						make_cube_jump_higher = 0;
					}
				}
			
			}
			else if((controllingplayer->press_a || controllingplayer->press_up) && (jblocked[currplayer] || fblocked[currplayer] || kandokidshack || (gamemode == GAMEMODE_NINJA && ninjajumps[currplayer]))) {		//jblock making you release and press A again to jump
				jumps++;

				if (!currplayer_mini) currplayer_vel_y = currplayer_gravity ? -JUMP_VEL : JUMP_VEL; // JUMP
				else currplayer_vel_y = currplayer_gravity ? -MINI_JUMP_VEL : MINI_JUMP_VEL; // JUMP

				if (make_cube_jump_higher) {
					if ((currplayer_slope_type & SLOPE_DEGREES_MASK) != SLOPE_22DEG) {
						currplayer_vel_y += (currplayer_gravity ? 0x80 : -0x80);
					}
					make_cube_jump_higher = 0;
				}

				if (gamemode == GAMEMODE_NINJA) { idx8_dec(ninjajumps, currplayer); }
			
			}
	} else if (gamemode == GAMEMODE_ROBOT) {
		
		if (controllingplayer->press_a || controllingplayer->press_up) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0b100);	
		}

		
		if ((!retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer] && dashing[currplayer] == 0 && cube_data[currplayer] & 4) || (dashing[currplayer] == 0 && kandokidshack == 9)){		//robot
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);					
			if((controllingplayer->a || controllingplayer->up) && !orbed[currplayer]) {
				jumps++;
				if (!currplayer_mini) currplayer_vel_y = currplayer_gravity ? -ROBOT_JUMP_VEL : ROBOT_JUMP_VEL; // JUMP
				else currplayer_vel_y = currplayer_gravity ? -MINI_ROBOT_JUMP_VEL : MINI_ROBOT_JUMP_VEL; // JUMP

				robotjumptime[currplayer] = ROBOT_JUMP_TIME;
				robotjumpframe[0] = 1;
			}
		}
		
		else if (retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer] && dashing[currplayer] == 0 && cube_data[currplayer] & 4) {		//jim
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);		
			if((controllingplayer->a || controllingplayer->up) && !jblocked[currplayer] && !orbed[currplayer]) {
				jumps++;
				if (!currplayer_gravity) {
					if (!currplayer_mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!currplayer_mini) currplayer_vel_y = -ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = -MINI_ROBOT_JUMP_VEL; // JUMP
				}
				robotjumptime[currplayer] = ROBOT_JUMP_TIME;
				robotjumpframe[0] = 1;
			}
			else if((controllingplayer->a || controllingplayer->up) && jblocked[currplayer] && !orbed[currplayer]) {	
				jumps++;
				if (!currplayer_gravity) {
					if (!currplayer_mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!currplayer_mini) currplayer_vel_y = -ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = -MINI_ROBOT_JUMP_VEL; // JUMP
				}
				robotjumptime[currplayer] = ROBOT_JUMP_TIME;
				robotjumpframe[0] = 1;
			}
		}
		
		else if (robotjumptime[currplayer] && !hblocked[currplayer]) {
			
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 0b11111011);	
				cube_data[currplayer] = 0;
				if (robotjumptime[currplayer]) idx8_dec(robotjumptime, currplayer); 
				if((controllingplayer->a || controllingplayer->up) && !jblocked[currplayer] && !orbed[currplayer]) {	
					jumps++;
					if (robotjumpframe[0]) robotjumpframe[0]++;
					if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
					if (!currplayer_gravity) {
						if (!currplayer_mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
						else currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					}
					else {
						if (!currplayer_mini) currplayer_vel_y = -ROBOT_JUMP_VEL; // JUMP
						else currplayer_vel_y = -ROBOT_JUMP_VEL; // JUMP
					}
				}	
				else if((controllingplayer->press_a || controllingplayer->press_up) && jblocked[currplayer] && !orbed[currplayer]) {	
					jumps++;
					if (robotjumpframe[0]) robotjumpframe[0]++;
					if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
					if (!currplayer_gravity) {
						if (!currplayer_mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
						else currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					}
					else {
						if (!currplayer_mini) currplayer_vel_y = -ROBOT_JUMP_VEL; // JUMP
						else currplayer_vel_y = -ROBOT_JUMP_VEL; // JUMP
					}
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
					jimsheatballalive[tmp9] = 1;
					if (controllingplayer->up) idx16_store_NOC(jimsheatball_vel_y, tmp9, (JIMSHEATBALL_JUMP_VEL / 4) * 7);
					else idx16_store_NOC(jimsheatball_vel_y, tmp9, JIMSHEATBALL_JUMP_VEL);
					idx16_store_NOC(jimsheatballx, tmp9, high_byte(old_x));
					idx16_store_hi_NOC(jimsheatbally, tmp9, high_byte(player_y[0]));
					jimsheatballframe[tmp9] = 0;
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

				if(currplayer_vel_y > JIMSHEATBALL_MAX_FALLSPEED){
					currplayer_vel_y += -JIMSHEATBALL_GRAVITY;
				} else currplayer_vel_y += JIMSHEATBALL_GRAVITY;
				currplayer_y += currplayer_vel_y;
				
				Generic.x = high_byte(currplayer_x);
				Generic.y = high_byte(currplayer_y);
				
			if (!(kandoframecnt & 3)) {
			//	x_movement_coll();
				if(bg_coll_D()){ // check collision below
					high_byte(currplayer_y) -= eject_D;
					low_byte(currplayer_y) = 0;
					currplayer_vel_y = JIMSHEATBALL_JUMP_VEL;
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
	}
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
}	


void common_gravity_routine() {
	register int16_t tempvel;
	register uint8_t temp_gr;
	if (!dashing[currplayer]) {
		temp_gr = currplayer_gravity;
		if(!currplayer_gravity ? ((!currplayer_mini ? fallspeed_big : fallspeed_mini) < currplayer_vel_y) : (-(!currplayer_mini ? fallspeed_big : fallspeed_mini) > currplayer_vel_y)){
			temp_gr = !temp_gr; 
		}
		tempvel = !currplayer_mini ? (temp_gr ? -gravity_big : gravity_big) : (temp_gr ? -gravity_mini : gravity_mini);
			switch (gravity_mod) {
				case 0: break;
				case 1: tempvel /= 3; break;
				case 2: __AX__ = (tempvel); __AX__ /= 2; tempvel = __AX__; break;
				case 3: tempvel = (tempvel / 3 * 2); break;
				case 4: tempvel *= 2; break;
			};
		currplayer_vel_y += tempvel;
		currplayer_y += currplayer_vel_y;
	}
	
	
	else if (dashing[currplayer] == 2) { currplayer_vel_y = -currplayer_vel_x; currplayer_y += currplayer_vel_y; }
	else if (dashing[currplayer] == 3) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else if (dashing[currplayer] == 4) { currplayer_vel_y = currplayer_vel_x*2; currplayer_y -= currplayer_vel_y; }	
	else if (dashing[currplayer] == 5) { currplayer_vel_y = currplayer_vel_x*2; currplayer_y += currplayer_vel_y; }	
	else currplayer_vel_y = 1;
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
				if (fblocked[currplayer]) currplayer_gravity = GRAVITY_DOWN;
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
				if (fblocked[currplayer]) currplayer_gravity = GRAVITY_UP;			
			}
		}
	//}	
}		

CODE_BANK_POP()
