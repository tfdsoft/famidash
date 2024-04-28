#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void ball_movement(void){
// handle y

	// player_gravity_curr
	// player_vel_y_curr is signed

	if(!mini){
		if(!player_gravity_curr){
			if(player_vel_y_curr > CUBE_MAX_FALLSPEED){
				player_vel_y_curr = CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += BALL_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= BALL_GRAVITY;
		}
	}
	else {
		if(!player_gravity_curr){
			if(player_vel_y_curr > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += MINI_BALL_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= MINI_BALL_GRAVITY;
		}
	}	
	
	
	player_y_curr += player_vel_y_curr;

	Generic.x = high_byte(player_x_curr);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (player_gravity_curr) {
		Generic.y = high_byte(player_y_curr) - 1;
	} else {
		Generic.y = high_byte(player_y_curr) + 1;
	}

	if (pad_new[controllingplayer] & PAD_A) cube_data[currplayer] |= 2;	

	if(high_byte(player_vel_y_curr) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(player_y_curr) = high_byte(player_y_curr) - eject_U;
			player_vel_y_curr = 0;
			cube_data[currplayer] &= 1;			//fix for orb
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
		    high_byte(player_y_curr) = high_byte(player_y_curr) - eject_D;
		    player_vel_y_curr = 0;
			cube_data[currplayer] &= 1;		    //fix for orb
		}
	}

	if ((pad[controllingplayer] & PAD_A) && (kandotemp2[currplayer] == 0) && player_vel_y_curr == 0){
		player_gravity_curr ^= 0x01;
		kandotemp2[currplayer] = 1;
		switch (player_gravity_curr){
			case 0x00: player_vel_y_curr = 0x6F; break;
			case 0x01: player_vel_y_curr = -0x6F; break;
		}
	}
	if(kandotemp2[currplayer] == 1){
		if (!(pad[controllingplayer] & PAD_A)){
			cube_data[currplayer] &= 1;
			kandotemp2[currplayer] = 0;			
		}
	}

	player_vel_y_curr = player_vel_y_curr;
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
