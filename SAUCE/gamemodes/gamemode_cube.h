void cube_movement(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){
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
	player.y += player.vel_y;
	
	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	
	
		if(player.vel_y > 0 && !gravity){
			if(bg_coll_D()){ // check collision below
			    high_byte(player.y) = high_byte(player.y) - eject_D;
			    player.vel_y = 0;
			}
		}
		if(player.vel_y < 0 && gravity){
			if(bg_coll_U() ){ // check collision above
				high_byte(player.y) = high_byte(player.y) - eject_U;
				player.vel_y = 0;
			}
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same
	
	if (gravity){
		if (player.vel_y <= 0){
			if(bg_coll_U2()) {
				if(pad & PAD_A) {
					player.vel_y = JUMP_VEL^0xFFFF; // JUMP
				}
			}
		}
	} else {
		if (player.vel_y >= 0){
			if(bg_coll_D2()) {
				if(pad & PAD_A) {
					player.vel_y = JUMP_VEL; // JUMP
				}
			}
		}
	}
}	

