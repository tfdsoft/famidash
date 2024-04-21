#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void ball_movement(void){
// handle y

// player_gravity[currplayer]
	// player_vel_y[currplayer] is signed

	if(!mini){
		if(!player_gravity[currplayer]){
			if(player_vel_y[currplayer] > CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += BALL_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= BALL_GRAVITY;
		}
	}
	else {
		if(!player_gravity[currplayer]){
			if(player_vel_y[currplayer] > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += MINI_BALL_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= MINI_BALL_GRAVITY;
		}
	}	
	
	
	player_y[currplayer] += player_vel_y[currplayer];

	Generic.x = high_byte(player_x[currplayer]);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (player_gravity[currplayer]) {
		Generic.y = high_byte(player_y[currplayer]) - 1;
	} else {
		Generic.y = high_byte(player_y[currplayer]) +  1;
	}



	if (pad_new[controllingplayer] & PAD_A) cube_data[currplayer] |= 2;	

	
	if(high_byte(player_vel_y[currplayer]) & 0x80){
		if(bg_coll_U()  && !bg_coll_R() ){ // check collision above
			high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_U- 1;
			player_vel_y[currplayer] = 0;
			cube_data[currplayer] &= 1;			//fix for orb
		}
	}
	else{
		if(bg_coll_D() && !bg_coll_R() ){ // check collision below
		    high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_D + 1;
		    player_vel_y[currplayer] = 0;
			cube_data[currplayer] &= 1;		    //fix for orb
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same

	if ((pad[controllingplayer] & PAD_A) && (kandotemp2[currplayer] == 0) && (player_vel_y[currplayer] == 0) && !bg_coll_R()){
		player_gravity[currplayer] ^= 0x01;
		kandotemp2[currplayer] = 1;
		switch (player_gravity[currplayer]){
			case 0x00: player_vel_y[currplayer] = 0x6F; break;
			case 0x01: player_vel_y[currplayer] = -0x6F; break;
			}
	}
	if(kandotemp2[currplayer] == 1){
		if (!(pad[controllingplayer] & PAD_A)){
			cube_data[currplayer] &= 1;
			kandotemp2[currplayer] = 0;			
		}
	}
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
