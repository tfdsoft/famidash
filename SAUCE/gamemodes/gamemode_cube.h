#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void cube_movement(void){
// handle y

// gravity[currplayer]
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){

	if ((pad_new[controllingplayer] & PAD_A) && currplayer_vel_y != 0) uint8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);

	if (!dashing[currplayer]) {
		if(!mini){
			if(!currplayer_gravity){
				if(currplayer_vel_y > CUBE_MAX_FALLSPEED){
					currplayer_vel_y += -CUBE_GRAVITY;
				} else currplayer_vel_y += CUBE_GRAVITY;
			}
			else{
				if(currplayer_vel_y < -CUBE_MAX_FALLSPEED){
					currplayer_vel_y -= -CUBE_GRAVITY;
				} else currplayer_vel_y -= CUBE_GRAVITY;
			}
		}
		else {
			if(!currplayer_gravity){
				if(currplayer_vel_y > MINI_CUBE_MAX_FALLSPEED){
					currplayer_vel_y += -MINI_CUBE_GRAVITY;
				} else currplayer_vel_y += MINI_CUBE_GRAVITY;
			}
			else{
				if(currplayer_vel_y < -MINI_CUBE_MAX_FALLSPEED){
					currplayer_vel_y -= -MINI_CUBE_GRAVITY;
				} else currplayer_vel_y -= MINI_CUBE_GRAVITY;
			}
		}		
		currplayer_y += currplayer_vel_y;
	}
	else if (dashing[currplayer] == 2) { currplayer_vel_y = -currplayer_vel_x; currplayer_y += currplayer_vel_y; }
	else if (dashing[currplayer] == 3) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else currplayer_vel_y = 1;

	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	
	if(!currplayer_gravity || (currplayer_gravity && hblocked[currplayer])){
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) -= eject_D;
			low_byte(currplayer_y) = 0;
			currplayer_vel_y = 0;
		}
	} if (currplayer_gravity || (!currplayer_gravity && hblocked[currplayer])) {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) -= eject_U;
			low_byte(currplayer_y) = 0;
			currplayer_vel_y = 0;
		}
	}
	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same

//	if (currplayer_vel_y != 0){
//		if(pad_new[controllingplayer] & PAD_A) {
//			cube_data[currplayer] |= 2;
//		}
//	}

	if (gamemode == 0 && currplayer_vel_y == 0 && dashing[currplayer] == 0){		//cube
		//if(bg_coll_D2()) {
			uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);				
			if(pad[controllingplayer] & PAD_A && !jblocked[currplayer]) {			//no jblock - hold A to buffer jump
				if (!currplayer_gravity) {
					if (!mini) currplayer_vel_y = JUMP_VEL; // JUMP
					else currplayer_vel_y = MINI_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) currplayer_vel_y = JUMP_VEL^0xFFFF; // JUMP
					else currplayer_vel_y = MINI_JUMP_VEL^0xFFFF; // JUMP
				}
			
			}
			else if(pad_new[controllingplayer] & PAD_A && jblocked[currplayer]) {		//jblock making you release and press A again to jump
				if (!currplayer_gravity) {
					if (!mini) currplayer_vel_y = JUMP_VEL; // JUMP
					else currplayer_vel_y = MINI_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) currplayer_vel_y = JUMP_VEL^0xFFFF; // JUMP
					else currplayer_vel_y = MINI_JUMP_VEL^0xFFFF; // JUMP
				}
			
			}
	}
	else if (gamemode == 4 && !retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer]){		//robot
		uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);				
		if(pad_new[controllingplayer] & PAD_A) {
			if (!currplayer_gravity) {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
			}
			robotjumptime[currplayer] = ROBOT_JUMP_TIME;
			robotjumpframe[0] = 1;
		}
	}
	
	else if (gamemode == 4 && retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer]){		//jim
		uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);				
		if(pad[controllingplayer] & PAD_A && !jblocked[currplayer]) {
			if (!currplayer_gravity) {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
			}
			robotjumptime[currplayer] = ROBOT_JUMP_TIME;
			robotjumpframe[0] = 1;
		}
		else if(pad_new[controllingplayer] & PAD_A && jblocked[currplayer]) {
			if (!currplayer_gravity) {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
			}
			robotjumptime[currplayer] = ROBOT_JUMP_TIME;
			robotjumpframe[0] = 1;
		}
	}
	
	else if (gamemode == 4 && robotjumptime[currplayer] && !hblocked[currplayer]) {
			cube_data[currplayer] = 0;
			if (robotjumptime[currplayer]) uint8_dec(robotjumptime, currplayer); 
			if(pad[controllingplayer] & PAD_A && !jblocked[currplayer]) {
				if (robotjumpframe[0]) robotjumpframe[0]++;
				if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
				if (!currplayer_gravity) {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
			}	
			else if(pad_new[controllingplayer] & PAD_A && jblocked[currplayer]) {
				if (robotjumpframe[0]) robotjumpframe[0]++;
				if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
				if (!currplayer_gravity) {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
			}
			else { robotjumptime[currplayer] = 0; robotjumpframe[0] = 0; }
	}
	else if (gamemode == 4 && currplayer_vel_y != 0){		
			robotjumpframe[0] = 3;
	}
	
	hblocked[currplayer] = 0;
	jblocked[currplayer] = 0;
//jim's shit
	if (retro_mode) {
		if (pad_new[currplayer] & PAD_B && !has_practice_point) {
			if (!jimsheatballalive[0]) {
				jimsheatballalive[0] = 1;
				jimsheatballx[0] = high_byte(old_x);
				jimsheatbally[0] = high_byte(player_y[0]);
				jimsheatballframe[0] = 0;
			}
			else if (!jimsheatballalive[1]) {
				jimsheatballalive[1] = 1;
				jimsheatballx[1] = high_byte(old_x);
				jimsheatbally[1] = high_byte(player_y[0]);
				jimsheatballframe[1] = 0;
			}

		}
	}
// done with jims shit	
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
