void ship_movement(void){
	
// handle x

	old_x = Cube.x;
	
	Cube.vel_x = CUBE_SPEED;
	/*
	if(pad1 & PAD_LEFT){
		direction = LEFT;
		
        if(Cube.vel_x >= DECEL){
            Cube.vel_x -= DECEL;
        }
        else if(Cube.vel_x > 0){
            Cube.vel_x = 0;
        }
		else {
			Cube.vel_x -= ACCEL;
			if(Cube.vel_x < -MAX_SPEED) Cube.vel_x = -MAX_SPEED;
		}
	}
	else if (pad1 & PAD_RIGHT){
		
		direction = RIGHT;

		if(Cube.vel_x <= DECEL){
            Cube.vel_x += DECEL;
        }
        else if(Cube.vel_x < 0){
            Cube.vel_x = 0;
        }
		else {
			Cube.vel_x += ACCEL;
			if(Cube.vel_x >= MAX_SPEED) Cube.vel_x = MAX_SPEED;
		}
	}
	else { // nothing pressed
		if(Cube.vel_x >= ACCEL) Cube.vel_x -= ACCEL;
		else if(Cube.vel_x < -ACCEL) Cube.vel_x += ACCEL;
		else Cube.vel_x = 0;
	}
	*/
	Cube.x += Cube.vel_x;
	
	if(Cube.x > 0xf000) { // too far, don't wrap around
        
        if(old_x >= 0xf000){
            Cube.x = 0xf000; // max right
        }
        else{
            Cube.x = 0x0000; // max left
        }
        
		Cube.vel_x = 0;
	} 
	


	Generic.x = high_byte(Cube.x); // this is much faster than passing a pointer to Cube
	Generic.y = high_byte(Cube.y);
	Generic.width = CUBE_WIDTH;
	Generic.height = CUBE_HEIGHT;
	
    if(Cube.vel_x < 0){
        if(bg_coll_L() ){ // check collision left
            high_byte(Cube.x) = high_byte(Cube.x) - eject_L;
            Cube.vel_x = 0;
            if(Cube.x > 0xf000) {
                // no wrap around
                Cube.x = 0xf000;
            }
        }
    }
    else if(Cube.vel_x > 0){
        if(bg_coll_R() ){ // check collision right
            high_byte(Cube.x) = high_byte(Cube.x) - eject_R;
            Cube.vel_x = 0;
            if(Cube.x > 0xf000) {
                // no wrap around
                Cube.x = 0x0000;
            }
        }
    }
    // skip collision if vel = 0
    
	
// handle y

// gravity
	orbjump();
	padjump();
	// Cube.vel_y is signed

	if(pad1_new & PAD_B) {
		if(gravity) {
			gravity = 0;
		}
		else {
			gravity = 1;
		}
	}
	
	if(!gravity) {

	if(Cube.vel_y < SHIP_MAX_FALLSPEED) Cube.vel_y += SHIP_GRAVITY;
	else Cube.vel_y = SHIP_MAX_FALLSPEED; // consistent


	if(Cube.vel_y > SHIP_MAX_GOUPSPEED) {}
	else Cube.vel_y = SHIP_MAX_GOUPSPEED; // consistent
	Cube.y += Cube.vel_y;
	}

	else {

	if(Cube.vel_y > SHIP_MAX_FALLSPEEDG) Cube.vel_y += SHIP_GRAVITYG;
	else Cube.vel_y = SHIP_MAX_FALLSPEEDG; // consistent


	if(Cube.vel_y < SHIP_MAX_GOUPSPEEDG) {}
	else Cube.vel_y = SHIP_MAX_GOUPSPEEDG; // consistent
	Cube.y += Cube.vel_y;
	}



	
	Generic.x = high_byte(Cube.x);
	Generic.y = high_byte(Cube.y);
	
    if(Cube.vel_y > 0){
        if(bg_coll_D()){ // check collision below
            high_byte(Cube.y) = high_byte(Cube.y) - eject_D;
            Cube.vel_y = 0;
            

        }
    }
    else if(Cube.vel_y < 0){
        if(bg_coll_U()){ // check collision above
        	high_byte(Cube.y) = high_byte(Cube.y) - eject_U;
        	Cube.vel_y = 0;
			
        }
    }
    if(pad1 & PAD_A) {

	if(!gravity) {
		Cube.vel_y -= SHIP_GRAVITY; // fly
		Cube.vel_y -= SHIP_GRAVITY;
	}
	else {
		Cube.vel_y -= -SHIP_GRAVITY; // fly
		Cube.vel_y -= -SHIP_GRAVITY;
	}
	
	}

	
	// do we need to load a new collision map? (scrolled into a new room)
	if((scroll_x & 0xff) < 4){
		if(!map_loaded){
			new_cmap();
			map_loaded = 1; // only do once
		}
		
	}
	else{
		map_loaded = 0;
	}
	
// scroll
	temp5 = Cube.x;
	if (Cube.x > MAX_RIGHT){
		temp1 = (Cube.x - MAX_RIGHT) >> 8;
        if (temp1 > 3) temp1 = 3; // max scroll change
		scroll_x += temp1;
		high_byte(Cube.x) = high_byte(Cube.x) - temp1;
	}

	if(scroll_x >= MAX_SCROLL) {
		scroll_x = MAX_SCROLL; // stop scrolling right, end of level

		reset_level();


		/*	
		Cube.x = temp5; // but allow the x position to go all the way right
		if(high_byte(Cube.x) >= 0xf1) {
			Cube.x = 0xf100;
		}
		*/
	}
	
}	