void spider_movement(void){
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

	if (!gravity) {
		if(pad_new & PAD_A) {
			gravity = 1;
			while (!bg_coll_U() && player.y > 0x650) {
				player.y += 0x20;
			}
			high_byte(player.y) -= eject_D;
			player.vel_y = 0;
			
		}
	}
	
	else {
		if(pad_new & PAD_A) {
			gravity = 0;
				high_byte(player.y) -= CUBE_MAX_FALLSPEED*3;

		}
	}
	
}	

