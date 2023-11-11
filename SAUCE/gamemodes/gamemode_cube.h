void cube_movement(void){
	// handle x
	old_x = player.x;
	
	if(pad & PAD_LEFT){
		player.vel_x = -CUBE_SPEED_X1;
	}
	else if (pad & PAD_RIGHT){
		player.vel_x = CUBE_SPEED_X1;
	}
	else { // nothing pressed
		player.vel_x = 0;
	}
	
	player.x += player.vel_x;
	
	if(player.x > 0xf100) { // too far, don't wrap around
        
        if(old_x >= 0x8000){
            player.x = 0xf100; // max right
        }
        else{
            player.x = 0x0000; // max left
        }
        
	} 
	
	
	Generic.x = player.x >> 8; // the collision routine needs an 8 bit value
	Generic.y = player.y >> 8;
	Generic.width = 15;
	Generic.height = 15;
	
	if(player.vel_x < 0){ // going left
		if(bg_coll_L() ){ // check collision left
            high_byte(player.x) = high_byte(player.x) - eject_L;
            
        }
	}
	else if(player.vel_x > 0){ // going right
		if(bg_coll_R() ){ // check collision right
            high_byte(player.x) = high_byte(player.x) - eject_R;
            
        }
	}
	// else 0, skip it
	
	
	
	// handle y
	old_y = player.y;

	if(pad & PAD_UP){
		player.vel_y = -CUBE_SPEED_X1;
	}
	else if (pad & PAD_DOWN){
		player.vel_y = CUBE_SPEED_X1;
	}
	else { // nothing pressed
		player.vel_y = 0;
	}

	player.y += player.vel_y;
	
	if(player.y > 0xe100) { // too far, don't wrap around
        
        if(old_y >= 0x8000){
            player.y = 0xe100; // max down
        }
        else{
            player.y = 0x0000; // max up
        }
        
	} 
	
	Generic.x = player.x >> 8; // the collision routine needs an 8 bit value
	Generic.y = player.y >> 8;
//	Generic.width = HERO_WIDTH; // already is this
//	Generic.height = HERO_HEIGHT;
	
	if(player.vel_y < 0){ // going up
		if(bg_coll_U() ){ // check collision left
            high_byte(player.y) = high_byte(player.y) - eject_U;
            
        }
	}
	else if(player.vel_y > 0){ // going down
		if(bg_coll_D() ){ // check collision right
            high_byte(player.y) = high_byte(player.y) - eject_D;
            
        }
	}
	// else 0, skip it
	
	
	
	// scroll
	do_the_scroll_thing();
}	