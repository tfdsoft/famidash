void ship_movement(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){
	if(!mini) {
		if(!gravity) {
			player.vel_y += SHIP_GRAVITY;
		}
		else {
			player.vel_y -= SHIP_GRAVITY;
		}
		if(player.vel_y > SHIP_MAX_FALLSPEED) player.vel_y = SHIP_MAX_FALLSPEED;
		if(player.vel_y < -SHIP_MAX_FALLSPEED) player.vel_y = -SHIP_MAX_FALLSPEED;

	}
	else {
		if(!gravity) {
			player.vel_y += MINI_SHIP_GRAVITY;
		}
		else {
			player.vel_y -= MINI_SHIP_GRAVITY;
		}
		if(player.vel_y > MINI_SHIP_MAX_FALLSPEED) player.vel_y = MINI_SHIP_MAX_FALLSPEED;
		if(player.vel_y < -MINI_SHIP_MAX_FALLSPEED) player.vel_y = -MINI_SHIP_MAX_FALLSPEED;
	}
		
		

	player.y += player.vel_y;
	
	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	
	
	if(high_byte(player.vel_y) & 0x80){
		if(bg_coll_U() && !bg_coll_R() ){ // check collision above
			high_byte(player.y) = high_byte(player.y) - eject_U;
			player.vel_y = 0;
		}
	}
	else{
		if(bg_coll_D() && !bg_coll_R() ){ // check collision below
		    high_byte(player.y) = high_byte(player.y) - eject_D;
		    player.vel_y = 0;
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same
	

	if(pad & PAD_A) {
		if (!mini) {
			if (!gravity){
			    player.vel_y -= SHIP_GRAVITY<<1;
				} else {
			    player.vel_y += SHIP_GRAVITY<<1;
			}
		}
		else {
			if (!gravity){
			    player.vel_y -= MINI_SHIP_GRAVITY<<1;
				} else {
			    player.vel_y += MINI_SHIP_GRAVITY<<1;
			}
		}
	}	
}