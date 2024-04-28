#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void ball_movement(void){
// handle y

// player_gravity[currplayer]
	// player_vel_y[currplayer] is signed

	#define player_vel_y_currplayer (short)tmp5
	#define uplayer_vel_y_currplayer tmp5
	uplayer_vel_y_currplayer = player_vel_y[currplayer];

	if(!mini){
		if(!player_gravity[currplayer]){
			if(player_vel_y_currplayer > CUBE_MAX_FALLSPEED){
				uplayer_vel_y_currplayer = CUBE_MAX_FALLSPEED;
			} else uplayer_vel_y_currplayer += BALL_GRAVITY;
		}
		else{
			if(player_vel_y_currplayer < -CUBE_MAX_FALLSPEED){
				uplayer_vel_y_currplayer = -CUBE_MAX_FALLSPEED;
			} else uplayer_vel_y_currplayer -= BALL_GRAVITY;
		}
	}
	else {
		if(!player_gravity[currplayer]){
			if(player_vel_y_currplayer > MINI_CUBE_MAX_FALLSPEED){
				uplayer_vel_y_currplayer = MINI_CUBE_MAX_FALLSPEED;
			} else uplayer_vel_y_currplayer += MINI_BALL_GRAVITY;
		}
		else{
			if(player_vel_y_currplayer < -MINI_CUBE_MAX_FALLSPEED){
				uplayer_vel_y_currplayer = -MINI_CUBE_MAX_FALLSPEED;
			} else uplayer_vel_y_currplayer -= MINI_BALL_GRAVITY;
		}
	}	
	
	
	player_y[currplayer] += player_vel_y_currplayer;

	Generic.x = high_byte(player_x[currplayer]);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (player_gravity[currplayer]) {
		Generic.y = high_byte(player_y[currplayer]) - 1;
	} else {
		Generic.y = high_byte(player_y[currplayer]) + 1;
	}

	if (pad_new[controllingplayer] & PAD_A) cube_data[currplayer] |= 2;	

	if(high_byte(uplayer_vel_y_currplayer) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_U;
			uplayer_vel_y_currplayer = 0;
			cube_data[currplayer] &= 1;			//fix for orb
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
		    high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_D;
		    uplayer_vel_y_currplayer = 0;
			cube_data[currplayer] &= 1;		    //fix for orb
		}
	}

	if ((pad[controllingplayer] & PAD_A) && (kandotemp2[currplayer] == 0) && player_vel_y_currplayer == 0){
		player_gravity[currplayer] ^= 0x01;
		kandotemp2[currplayer] = 1;
		switch (player_gravity[currplayer]){
			case 0x00: uplayer_vel_y_currplayer = 0x6F; break;
			case 0x01: uplayer_vel_y_currplayer = -0x6F; break;
		}
	}
	if(kandotemp2[currplayer] == 1){
		if (!(pad[controllingplayer] & PAD_A)){
			cube_data[currplayer] &= 1;
			kandotemp2[currplayer] = 0;			
		}
	}

	player_vel_y[currplayer] = player_vel_y_currplayer;
	#undef player_vel_y_currplayer
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
