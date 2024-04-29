#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void ball_movement(void){
// handle y

	// currplayer_gravity
	// currplayer_vel_y is signed

	if(!mini){
		if(!currplayer_gravity){
			if(currplayer_vel_y > CUBE_MAX_FALLSPEED){
				currplayer_vel_y = CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y += BALL_GRAVITY;
		}
		else{
			if(currplayer_vel_y < -CUBE_MAX_FALLSPEED){
				currplayer_vel_y = -CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y -= BALL_GRAVITY;
		}
	}
	else {
		if(!currplayer_gravity){
			if(currplayer_vel_y > MINI_CUBE_MAX_FALLSPEED){
				currplayer_vel_y = MINI_CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y += MINI_BALL_GRAVITY;
		}
		else{
			if(currplayer_vel_y < -MINI_CUBE_MAX_FALLSPEED){
				currplayer_vel_y = -MINI_CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y -= MINI_BALL_GRAVITY;
		}
	}	
	
	
	currplayer_y += currplayer_vel_y;

	Generic.x = high_byte(currplayer_x);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 1;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}

	if (pad_new[controllingplayer] & PAD_A) cube_data[currplayer] |= 2;	

	if(high_byte(currplayer_vel_y) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U;
			currplayer_vel_y = 0;
			cube_data[currplayer] &= 1;			//fix for orb
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
		    high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
		    currplayer_vel_y = 0;
			cube_data[currplayer] &= 1;		    //fix for orb
		}
	}

	if ((pad[controllingplayer] & PAD_A) && (kandotemp2[currplayer] == 0) && currplayer_vel_y == 0){
		currplayer_gravity ^= 0x01;
		kandotemp2[currplayer] = 1;
		switch (currplayer_gravity){
			case 0x00: currplayer_vel_y = 0x6F; break;
			case 0x01: currplayer_vel_y = -0x6F; break;
		}
	}
	if(kandotemp2[currplayer] == 1){
		if (!(pad[controllingplayer] & PAD_A)){
			cube_data[currplayer] &= 1;
			kandotemp2[currplayer] = 0;			
		}
	}

	currplayer_vel_y = currplayer_vel_y;
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
