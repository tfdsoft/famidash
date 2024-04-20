#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void cube_movement(void){
// handle y

// gravity[currplayer]
	// player_vel_y[currplayer] is signed
	//if(player_vel_y[currplayer] < 0x400){

	if(!mini){
		if(!player_gravity[currplayer]){
			if(player_vel_y[currplayer] > CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += CUBE_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= CUBE_GRAVITY;
		}
	}
	else {
		if(!player_gravity[currplayer]){
			if(player_vel_y[currplayer] > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y[currplayer] += player_vel_y[currplayer];
	
	Generic.x = high_byte(player_x[currplayer]);
	Generic.y = high_byte(player_y[currplayer]);
	
		if(!player_gravity[currplayer]){
			if(bg_coll_D()){ // check collision below
			if(!bg_coll_R())    high_byte(player_y[currplayer]) -= eject_D;
			player_vel_y[currplayer] = 0;
		}
			
		}
		if(player_gravity[currplayer]){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				if(!bg_coll_R()) high_byte(player_y[currplayer]) -= eject_U;
				player_vel_y[currplayer] = 0;
			}
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same

	if (player_vel_y[currplayer] != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}

	if (gamemode == 0 &&  (player_vel_y[currplayer] == 0 || player_vel_y[currplayer] == CUBE_GRAVITY || player_vel_y[currplayer] == -CUBE_GRAVITY || player_vel_y[currplayer] == MINI_CUBE_GRAVITY || player_vel_y[currplayer] == -MINI_CUBE_GRAVITY)){
		//if(bg_coll_D2()) {
			cube_data[currplayer] &= 1;				
			if(pad[controllingplayer] & PAD_A) {
				if (!player_gravity[currplayer]) {
					if (!mini) player_vel_y[currplayer] = JUMP_VEL; // JUMP
					else player_vel_y[currplayer] = MINI_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player_vel_y[currplayer] = JUMP_VEL^0xFFFF; // JUMP
					else player_vel_y[currplayer] = MINI_JUMP_VEL^0xFFFF; // JUMP
				}
			
			}
	}
	else if (gamemode == 4 && (player_vel_y[currplayer] == 0 || player_vel_y[currplayer] == CUBE_GRAVITY || player_vel_y[currplayer] == MINI_CUBE_GRAVITY || player_vel_y[currplayer] == -CUBE_GRAVITY || player_vel_y[currplayer] == -MINI_CUBE_GRAVITY)){
		cube_data[currplayer] &= 1;				
		if(pad_new[controllingplayer] & PAD_A) {
			if (!player_gravity[currplayer]) {
				if (!mini) player_vel_y[currplayer] = ROBOT_JUMP_VEL; // JUMP
				else player_vel_y[currplayer] = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) player_vel_y[currplayer] = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else player_vel_y[currplayer] = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
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
				if (!player_gravity[currplayer]) {
					if (!mini) player_vel_y[currplayer] = ROBOT_JUMP_VEL; // JUMP
					else player_vel_y[currplayer] = ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player_vel_y[currplayer] = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else player_vel_y[currplayer] = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
			}
			else { robotjumptime[currplayer] = 0; robotjumpframe[0] = 0; }
	}
	else if (gamemode == 4 && player_vel_y[currplayer] != 0){		
			robotjumpframe[0] = 3;
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
