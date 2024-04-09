void cube_movement(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){

//	if(!mini){
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
//	}
//	else {
//		if(!gravity){
//			if(player.vel_y > MINI_CUBE_MAX_FALLSPEED){
//				player.vel_y = MINI_CUBE_MAX_FALLSPEED;
//			} else player.vel_y += MINI_CUBE_GRAVITY;
//		}
//		else{
//			if(player.vel_y < -MINI_CUBE_MAX_FALLSPEED){
//				player.vel_y = -MINI_CUBE_MAX_FALLSPEED;
//			} else player.vel_y -= MINI_CUBE_GRAVITY;
//		}
//	}		
	player.y += player.vel_y;
	
	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	
		if(!gravity){
			if(bg_coll_D() && !bg_coll_R()){ // check collision below
			    high_byte(player.y) -= eject_D;
			}
			if(bg_coll_D())    player.vel_y = 0;
			
		}
		if(gravity){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				high_byte(player.y) -= eject_U;
				player.vel_y = 0;
			}
			if(bg_coll_U())    player.vel_y = 0;
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same

	if (player.vel_y != 0){
		if(pad_new & PAD_A) {
			cube_data = 2;
		}
	}

	if (gamemode == 0 && player.vel_y == 0){
		//if(bg_coll_D2()) {
			cube_data = 0;				
			if(pad & PAD_A) {
				if (!gravity) {
					if (!mini) player.vel_y = JUMP_VEL; // JUMP
					else player.vel_y = MINIJUMP_VEL; // JUMP
				}
				else {
					if (!mini) player.vel_y = JUMP_VEL^0xFFFF; // JUMP
					else player.vel_y = MINIJUMP_VEL^0xFFFF; // JUMP
				}
			
			}
	}
	else if (gamemode == 4 && player.vel_y == 0){
		cube_data = 0;				
		if((pad_new & PAD_A) && bg_coll_D()) {
			if (!gravity) {
				if (!mini) player.vel_y = ROBOT_JUMP_VEL; // JUMP
				else player.vel_y = ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) player.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else player.vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
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

