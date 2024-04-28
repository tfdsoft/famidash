#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void wave_movement(void){

	if(!(pad[controllingplayer] & PAD_A)) {
		if(!mini){
			if(!player_gravity[currplayer]){
				if(player_vel_y[currplayer] > CUBE_MAX_FALLSPEED){
					player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
				} else player_vel_y[currplayer] = CUBE_MAX_FALLSPEED/2;
			}
			else{
				if(player_vel_y[currplayer] < -CUBE_MAX_FALLSPEED){
					player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
				} else player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED/2;
			}
		}
		else {
			if(!player_gravity[currplayer]){
				if(player_vel_y[currplayer] > CUBE_MAX_FALLSPEED){
					player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
				} else player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
			}
			else{
				if(player_vel_y[currplayer] < -CUBE_MAX_FALLSPEED){
					player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
				} else player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
			}
		}		
	}

	player_y[currplayer] += player_vel_y[currplayer];
	
	Generic.x = high_byte(player_x[currplayer]);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	Generic.y = high_byte(player_y[currplayer]);
	
	if(!player_gravity[currplayer]){
//		if(bg_coll_D()){ // check collision below
//			high_byte(player_y[currplayer]) -= eject_D;
//			player_vel_y[currplayer] = 0;

			if(pad[controllingplayer] & PAD_A) {
				//player_gravity[currplayer] = 1;
					if (mini) player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
					else player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED/2;
				//	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
	//			high_byte(player_y[currplayer]) -= eject_U;
	//			player_vel_y[currplayer] = 0;
			}
//		}
	} else {
		//if(bg_coll_U()){ // check collision above
		//	high_byte(player_y[currplayer]) -= eject_U;
		//	player_vel_y[currplayer] = 0;

			if(pad[controllingplayer] & PAD_A) {
//				player_gravity[currplayer] = 0;
					if (mini) player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
					else player_vel_y[currplayer] = CUBE_MAX_FALLSPEED/2;
				//	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same

		//		high_byte(player_y[currplayer]) -= eject_D;
				
		//		player_vel_y[currplayer] = 0;


			}
		//} 
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same

	if (player_vel_y[currplayer] != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
