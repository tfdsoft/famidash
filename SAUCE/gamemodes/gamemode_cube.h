#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void cube_movement(void){
// handle y

// gravity[currplayer]
	// player_vel_y_curr is signed
	//if(player_vel_y_curr < 0x400){

	if(!mini){
		if(!player_gravity_curr){
			if(player_vel_y_curr > CUBE_MAX_FALLSPEED){
				player_vel_y_curr = CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += CUBE_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= CUBE_GRAVITY;
		}
	}
	else {
		if(!player_gravity_curr){
			if(player_vel_y_curr > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y_curr += player_vel_y_curr;
	Generic.x = high_byte(player_x_curr);
	Generic.y = high_byte(player_y_curr);
	
	if(!player_gravity_curr){
		if(bg_coll_D()){ // check collision below
			high_byte(player_y_curr) -= eject_D;
			low_byte(player_y_curr) = 0;
			player_vel_y_curr = 0;
		}
	} else {
		if(bg_coll_U()){ // check collision above
			high_byte(player_y_curr) -= eject_U;
			low_byte(player_y_curr) = 0;
			player_vel_y_curr = 0;
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y_curr); // the rest should be the same

	if (player_vel_y_curr != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}

	if (gamemode == 0 && player_vel_y_curr == 0){
		//if(bg_coll_D2()) {
			cube_data[currplayer] &= 1;				
			if(pad[controllingplayer] & PAD_A) {
				if (!player_gravity_curr) {
					if (!mini) player_vel_y_curr = JUMP_VEL; // JUMP
					else player_vel_y_curr = MINI_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player_vel_y_curr = JUMP_VEL^0xFFFF; // JUMP
					else player_vel_y_curr = MINI_JUMP_VEL^0xFFFF; // JUMP
				}
			
			}
	}
	else if (gamemode == 4 && (player_vel_y_curr == 0 || player_vel_y_curr == CUBE_GRAVITY || player_vel_y_curr == MINI_CUBE_GRAVITY || player_vel_y_curr == -CUBE_GRAVITY || player_vel_y_curr == -MINI_CUBE_GRAVITY)){
		cube_data[currplayer] &= 1;				
		if(pad_new[controllingplayer] & PAD_A) {
			if (!player_gravity_curr) {
				if (!mini) player_vel_y_curr = ROBOT_JUMP_VEL; // JUMP
				else player_vel_y_curr = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) player_vel_y_curr = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else player_vel_y_curr = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
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
				if (!player_gravity_curr) {
					if (!mini) player_vel_y_curr = ROBOT_JUMP_VEL; // JUMP
					else player_vel_y_curr = ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player_vel_y_curr = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else player_vel_y_curr = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
			}
			else { robotjumptime[currplayer] = 0; robotjumpframe[0] = 0; }
	}
	else if (gamemode == 4 && player_vel_y_curr != 0){		
			robotjumpframe[0] = 3;
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
