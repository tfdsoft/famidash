void cube_movement(void){
	
// handle x

	old_x = player.x;
	
	player.vel_x = CUBE_SPEED_X1;
	/*
	if(pad & PAD_LEFT){
		direction = LEFT;
		
        if(player.vel_x >= DECEL){
            player.vel_x -= DECEL;
        }
        else if(player.vel_x > 0){
            player.vel_x = 0;
        }
		else {
			player.vel_x -= ACCEL;
			if(player.vel_x < -MAX_SPEED) player.vel_x = -MAX_SPEED;
		}
	}
	else if (pad & PAD_RIGHT){
		
		direction = RIGHT;

		if(player.vel_x <= DECEL){
            player.vel_x += DECEL;
        }
        else if(player.vel_x < 0){
            player.vel_x = 0;
        }
		else {
			player.vel_x += ACCEL;
			if(player.vel_x >= MAX_SPEED) player.vel_x = MAX_SPEED;
		}
	}
	else { // nothing pressed
		if(player.vel_x >= ACCEL) player.vel_x -= ACCEL;
		else if(player.vel_x < -ACCEL) player.vel_x += ACCEL;
		else player.vel_x = 0;
	}
	*/
	player.x += player.vel_x;
	
	if(player.x > 0xf000) { // too far, don't wrap around
        
        if(old_x >= 0xf000){
            player.x = 0xf000; // max right
        }
        else{
            player.x = 0x0000; // max left
        }
        
		player.vel_x = 0;
	} 
	


	Generic.x = high_byte(player.x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(player.y);
	Generic.width = CUBE_WIDTH;
	Generic.height = CUBE_HEIGHT;
	
    if(player.vel_x < 0){
        if(bg_coll_L() ){ // check collision left
            high_byte(player.x) = high_byte(player.x) - eject_L;
            player.vel_x = 0;
            if(player.x > 0xf000) {
                // no wrap around
                player.x = 0xf000;
            }
        }
    }
    else if(player.vel_x > 0){
        if(bg_coll_R() ){ // check collision right
            high_byte(player.x) = high_byte(player.x) - eject_R;
            player.vel_x = 0;
            if(player.x > 0xf000) {
                // no wrap around
                player.x = 0x0000;
            }
        }
    }
    // skip collision if vel = 0
    
	
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
	//}
	//else{
	//	player.vel_y = 0x400; // consistent
	//}
	player.y += player.vel_y;
	
	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	

		if(player.vel_y > 0){
			if(bg_coll_D()){ // check collision below
			    high_byte(player.y) = high_byte(player.y) - eject_D;
			    player.vel_y = 0;
			}
		}
		else if(player.vel_y < 0){
			if(bg_coll_U() ){ // check collision above
				high_byte(player.y) = high_byte(player.y) - eject_U;
				player.vel_y = 0;
			}
		}

	
	

	
	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same
	
	if (!gravity){
		if(bg_coll_D2()) {
    	    if(pad & PAD_A) {
				player.vel_y = JUMP_VEL; // JUMP
			}
		}
		
	} else {
		if(bg_coll_U2()) {
    	    if(pad & PAD_A) {
				player.vel_y = JUMP_VEL^0xFFFF; // JUMP
			}
		}
	}

	if(pad_new & PAD_B) {
		if(gravity) {
			gravity = 0;
		}
		else {
			gravity = 1;
		}
	}
	do_the_scroll_thing();
}	

