#pragma code-name(push, "LVL_BANK_15")
#pragma data-name(push, "LVL_BANK_15")
#pragma rodata-name(push, "LVL_BANK_15")

void cube_movement(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){

	if(!mini){
		if(!gravity){
			if(player.vel_y > CUBE_MAX_FALLSPEED){
				player.vel_y = CUBE_MAX_FALLSPEED;
			} else player.vel_y += CUBE_GRAVITY;
		}
		else{
			if(player.vel_y < -CUBE_MAX_FALLSPEED){
				player.vel_y = -CUBE_MAX_FALLSPEED;
			} else player.vel_y -= CUBE_GRAVITY;
		}
	}
	else {
		if(!gravity){
			if(player.vel_y > MINI_CUBE_MAX_FALLSPEED){
				player.vel_y = MINI_CUBE_MAX_FALLSPEED;
			} else player.vel_y += MINI_CUBE_GRAVITY;
		}
		else{
			if(player.vel_y < -MINI_CUBE_MAX_FALLSPEED){
				player.vel_y = -MINI_CUBE_MAX_FALLSPEED;
			} else player.vel_y -= MINI_CUBE_GRAVITY;
		}
	}		
	player.y += player.vel_y;
	
	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	
		if(!gravity){
			if(bg_coll_D()){ // check collision below
			if(!bg_coll_R())    high_byte(player.y) -= eject_D;
			player.vel_y = 0;
		}
			
		}
		if(gravity){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				if(!bg_coll_R()) high_byte(player.y) -= eject_U;
				player.vel_y = 0;
			}
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same

	if (player.vel_y != 0){
		if(pad_new & PAD_A) {
			cube_data = 2;
		}
	}

	if (gamemode == 0 &&  (player.vel_y == 0 || player.vel_y == CUBE_GRAVITY || player.vel_y == -CUBE_GRAVITY || player.vel_y == MINI_CUBE_GRAVITY || player.vel_y == -MINI_CUBE_GRAVITY)){
		//if(bg_coll_D2()) {
			cube_data = 0;				
			if(pad & PAD_A) {
				if (!gravity) {
					if (!mini) player.vel_y = JUMP_VEL; // JUMP
					else player.vel_y = MINI_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player.vel_y = JUMP_VEL^0xFFFF; // JUMP
					else player.vel_y = MINI_JUMP_VEL^0xFFFF; // JUMP
				}
			
			}
	}
	else if (gamemode == 4 && (player.vel_y == 0 || player.vel_y == CUBE_GRAVITY || player.vel_y == MINI_CUBE_GRAVITY || player.vel_y == -CUBE_GRAVITY || player.vel_y == -MINI_CUBE_GRAVITY)){
		cube_data = 0;				
		if(pad_new & PAD_A) {
			if (!gravity) {
				if (!mini) player.vel_y = ROBOT_JUMP_VEL; // JUMP
				else player.vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) player.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else player.vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
			}
			robotjumptime = ROBOT_JUMP_TIME;
			robotjumpframe = 1;
		}
	}
	
	else if (gamemode == 4 && robotjumptime) {
			cube_data = 0;
			if (robotjumptime) robotjumptime--;
			if(pad & PAD_A) {
				if (robotjumpframe) robotjumpframe++;
				if ( robotjumpframe > 3 ) robotjumpframe = 3;
				if (!gravity) {
					if (!mini) player.vel_y = ROBOT_JUMP_VEL; // JUMP
					else player.vel_y = ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else player.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
			}
			else { robotjumptime = 0; robotjumpframe = 0; }
	}
	else if (gamemode == 4 && player.vel_y != 0){		
			robotjumpframe = 3;
	}
}	

void cube_movement2(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){

	if(!mini){
		if(gravity){
			if(player2.vel_y > CUBE_MAX_FALLSPEED){
				player2.vel_y = CUBE_MAX_FALLSPEED;
			} else player2.vel_y += CUBE_GRAVITY;
		}
		else{
			if(player2.vel_y < -CUBE_MAX_FALLSPEED){
				player2.vel_y = -CUBE_MAX_FALLSPEED;
			} else player2.vel_y -= CUBE_GRAVITY;
		}
	}
	else {
		if(gravity){
			if(player2.vel_y > MINI_CUBE_MAX_FALLSPEED){
				player2.vel_y = MINI_CUBE_MAX_FALLSPEED;
			} else player2.vel_y += MINI_CUBE_GRAVITY;
		}
		else{
			if(player2.vel_y < -MINI_CUBE_MAX_FALLSPEED){
				player2.vel_y = -MINI_CUBE_MAX_FALLSPEED;
			} else player2.vel_y -= MINI_CUBE_GRAVITY;
		}
	}		
	player2.y += player2.vel_y;

	player2.x = player.x;
	
	Generic.x = high_byte(player2.x);
	Generic.y = high_byte(player2.y);
	
		if(gravity){
			if(bg_coll_D()){ // check collision below
				if(!bg_coll_R())    high_byte(player2.y) -= eject_D;
				player2.vel_y = 0;
		}
			
		}
		if(!gravity){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				if(!bg_coll_R()) high_byte(player2.y) -= eject_U;
				player2.vel_y = 0;
			}
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player2.y); // the rest should be the same
	if (!twoplayer) {
		if (player2.vel_y != 0){
			if(pad_new & PAD_A) {
				cube_data2 = 2;
			}
		}
	}
	else {
		if (player2.vel_y != 0){
			if(pad_new2 & PAD_A) {
				cube_data2 = 2;
			}
		}
	}		

	if (gamemode == 0 && (player2.vel_y == 0 )){ //|| player2.vel_y == CUBE_GRAVITY || player2.vel_y == -CUBE_GRAVITY || player2.vel_y == MINI_CUBE_GRAVITY || player2.vel_y == -MINI_CUBE_GRAVITY
		//if(bg_coll_D2()) {
			cube_data2 = 0;				
			if (!twoplayer) {
				if(pad & PAD_A) {
					if (gravity) {
						if (!mini) player2.vel_y = JUMP_VEL; // JUMP
						else player2.vel_y = MINI_JUMP_VEL; // JUMP
					}
					else {
						if (!mini) player2.vel_y = JUMP_VEL^0xFFFF; // JUMP
						else player2.vel_y = MINI_JUMP_VEL^0xFFFF; // JUMP
					}
				}
			}
			else {
				if(pad & PAD_A) {
					if (gravity) {
						if (!mini) player2.vel_y = JUMP_VEL; // JUMP
						else player2.vel_y = MINI_JUMP_VEL; // JUMP
					}
					else {
						if (!mini) player2.vel_y = JUMP_VEL^0xFFFF; // JUMP
						else player2.vel_y = MINI_JUMP_VEL^0xFFFF; // JUMP
					}
				}
			}
	}
	else if (gamemode == 4 && (player2.vel_y == 0 )){ // || player2.vel_y == CUBE_GRAVITY || player2.vel_y == MINI_CUBE_GRAVITY || player2.vel_y == -CUBE_GRAVITY || player2.vel_y == -MINI_CUBE_GRAVITY
		cube_data2 = 0;				
		if (!twoplayer) {
			if(pad_new & PAD_A) {
				if (gravity) {
					if (!mini) player2.vel_y = ROBOT_JUMP_VEL; // JUMP
					else player2.vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player2.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else player2.vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
				robotjumptime2 = ROBOT_JUMP_TIME;
				robotjumpframe2 = 1;
			}
		}
		else {
			if(pad_new2 & PAD_A) {
				if (gravity) {
					if (!mini) player2.vel_y = ROBOT_JUMP_VEL; // JUMP
					else player2.vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) player2.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else player2.vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
				robotjumptime2 = ROBOT_JUMP_TIME;
				robotjumpframe2 = 1;
			}
		}			
	}
	
	else if (gamemode == 4 && robotjumptime2) {
			cube_data2 = 0;
			if (robotjumptime2) robotjumptime2--;
			if (!twoplayer) {
				if(pad & PAD_A) {
					if (robotjumpframe2) robotjumpframe2++;
					if ( robotjumpframe2 > 3 ) robotjumpframe2 = 3;
					if (gravity) {
						if (!mini) player2.vel_y = ROBOT_JUMP_VEL; // JUMP
						else player2.vel_y = ROBOT_JUMP_VEL; // JUMP
					}
					else {
						if (!mini) player2.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
						else player2.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					}
				}
			else { robotjumptime2 = 0; robotjumpframe2 = 0; }
			}
			else {
				if(pad2 & PAD_A) {
					if (robotjumpframe2) robotjumpframe2++;
					if ( robotjumpframe2 > 3 ) robotjumpframe2 = 3;
					if (gravity) {
						if (!mini) player2.vel_y = ROBOT_JUMP_VEL; // JUMP
						else player2.vel_y = ROBOT_JUMP_VEL; // JUMP
					}
					else {
						if (!mini) player2.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
						else player2.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					}
				}
			else { robotjumptime2 = 0; robotjumpframe2 = 0; }
			}
	}
	else if (gamemode == 4 && player2.vel_y != 0){		
			robotjumpframe2 = 3;
	}
}	


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
