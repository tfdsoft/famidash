#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void cube_movement(void){
// handle y

// gravity[currplayer]
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){

	if(!mini){
		if(!currplayer_gravity){
			if(currplayer_vel_y > CUBE_MAX_FALLSPEED){
				currplayer_vel_y = CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y += CUBE_GRAVITY;
		}
		else{
			if(currplayer_vel_y < -CUBE_MAX_FALLSPEED){
				currplayer_vel_y = -CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y -= CUBE_GRAVITY;
		}
	}
	else {
		if(!currplayer_gravity){
			if(currplayer_vel_y > MINI_CUBE_MAX_FALLSPEED){
				currplayer_vel_y = MINI_CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y += MINI_CUBE_GRAVITY;
		}
		else{
			if(currplayer_vel_y < -MINI_CUBE_MAX_FALLSPEED){
				currplayer_vel_y = -MINI_CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y -= MINI_CUBE_GRAVITY;
		}
	}		
	currplayer_y += currplayer_vel_y;
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	
	if(!currplayer_gravity){
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) -= eject_D;
			low_byte(currplayer_y) = 0;
			currplayer_vel_y = 0;
		}
	} else {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) -= eject_U;
			low_byte(currplayer_y) = 0;
			currplayer_vel_y = 0;
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same

	if (currplayer_vel_y != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}

	if (gamemode == 0 && currplayer_vel_y == 0){
		//if(bg_coll_D2()) {
			cube_data[currplayer] &= 1;				
			if(pad[controllingplayer] & PAD_A) {
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
	else if (gamemode == 4 && (currplayer_vel_y == 0 || currplayer_vel_y == CUBE_GRAVITY || currplayer_vel_y == MINI_CUBE_GRAVITY || currplayer_vel_y == -CUBE_GRAVITY || currplayer_vel_y == -MINI_CUBE_GRAVITY)){
		cube_data[currplayer] &= 1;				
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
	
	else if (gamemode == 4 && robotjumptime[currplayer]) {
			cube_data[currplayer] = 0;
			if (robotjumptime[currplayer]) robotjumptime[currplayer]--;
			if(pad[controllingplayer] & PAD_A) {
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
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
