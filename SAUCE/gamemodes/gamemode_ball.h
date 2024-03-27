void ball_movement(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){
	if(!gravity){
		player.vel_y += CUBE_GRAVITY;
	}
	else{
		player.vel_y -= CUBE_GRAVITY;
	}

    if(player.vel_y > CUBE_MAX_FALLSPEED) player.vel_y = CUBE_MAX_FALLSPEED;
    if(player.vel_y < -CUBE_MAX_FALLSPEED) player.vel_y = -CUBE_MAX_FALLSPEED;

	player.y += player.vel_y;
	
	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	
	
	if(high_byte(player.vel_y) & 0x80){
		if(bg_coll_U() ){ // check collision above
			high_byte(player.y) = high_byte(player.y) - eject_U;
			player.vel_y = 0;
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
		    high_byte(player.y) = high_byte(player.y) - eject_D;
		    player.vel_y = 0;
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same
	

	if ((pad & PAD_A) && (kandotemp2 == 0) && (player.vel_y == 0)){
		gravity ^= 0x01;
		kandotemp2 = 1;
	}
	if(kandotemp2 == 1){
		if ((pad & PAD_A) == 0){
			kandotemp2 = 0;			
		}
	}
}