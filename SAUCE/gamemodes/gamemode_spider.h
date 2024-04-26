#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void spider_movement(void){
// handle y

// player_gravity[currplayer]
	// player_vel_y[currplayer] is signed
	//if(player_vel_y[currplayer] < 0x400){

	if(!mini){
		if(!player_gravity[currplayer]){
			if(player_vel_y[currplayer] > CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += CUBE_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= CUBE_GRAVITY;
		}
	}
	else {
		if(!player_gravity[currplayer]){
			if(player_vel_y[currplayer] > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y[currplayer] += player_vel_y[currplayer];
	
	Generic.x = high_byte(player_x[currplayer]);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	Generic.y = high_byte(player_y[currplayer]);
	
	if(!player_gravity[currplayer]){
		if(bg_coll_D()){ // check collision below
			high_byte(player_y[currplayer]) -= eject_D;
			player_vel_y[currplayer] = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				player_gravity[currplayer] = 1;
				do {
					player_y[currplayer] -= 0x800;
					Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
				} while (!bg_coll_U());
				high_byte(player_y[currplayer]) -= eject_U;
				player_vel_y[currplayer] = 0;
			}
		}
	} else {
		if(bg_coll_U()){ // check collision above
			high_byte(player_y[currplayer]) -= eject_U;
			player_vel_y[currplayer] = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				player_gravity[currplayer] = 0;
				do {
					player_y[currplayer] += 0x800;
					Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
				} while (!bg_coll_D());

				high_byte(player_y[currplayer]) -= eject_D;
				
				player_vel_y[currplayer] = 0;


			}
		} 
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same

	if (player_vel_y[currplayer] != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}
}	
/*
void spider_movement2(void){
// handle y

// player_gravity[currplayer]
	// player_vel_y[currplayer] is signed
	//if(player_vel_y[currplayer] < 0x400){

	if(!mini){
		if(player_gravity[currplayer]){
			if(player_vel_y[currplayer] > CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += CUBE_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= CUBE_GRAVITY;
		}
	}
	else {
		if(player_gravity[currplayer]){
			if(player_vel_y[currplayer] > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y[currplayer] = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y[currplayer] += player_vel_y[currplayer];
	player_x[currplayer] = player_x[currplayer];
	Generic.x = high_byte(player_x[currplayer]);
	Generic.y = high_byte(player_y[currplayer]);
	
		if(player_gravity[currplayer]){
			if(bg_coll_D() && !bg_coll_R()){ // check collision below
			    high_byte(player_y[currplayer]) -= eject_D;
			}
			if(bg_coll_D())    player_vel_y[currplayer] = 0;
			
		}
		if(!player_gravity[currplayer]){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				high_byte(player_y[currplayer]) -= eject_U;
			}
			if(bg_coll_U())    player_vel_y[currplayer] = 0;
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same

	if (player_vel_y[currplayer] != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data2 = 2;
		}
	}
	if ( player_vel_y[currplayer] == 0 || player_vel_y[currplayer] == CUBE_MAX_FALLSPEED || player_vel_y[currplayer] == -CUBE_MAX_FALLSPEED ) {
		if (!twoplayer) {
			if (!player_gravity[currplayer]) {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity[currplayer] = 1;
					cube_data2 = 0;
					while (!bg_coll_U()) {
						if (!mini) player_y[currplayer] -= 0x700;
						else player_y[currplayer] -= 0x400;
						Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
					}
					high_byte(player_y[currplayer]) -= eject_U;
					player_vel_y[currplayer] = 0;
					
				}
			}
			
			else {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity[currplayer] = 0;
					cube_data2 = 0;
					while (!bg_coll_D()) {
						if (!mini) player_y[currplayer] += 0x700;
						else player_y[currplayer] += 0x400;					
						Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
					}
					high_byte(player_y[currplayer]) -= eject_D;
					player_vel_y[currplayer] = 0;


				}
			}
		}
		else {
			if (!player_gravity[currplayer]) {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity[currplayer] = 1;
					cube_data2 = 0;
					while (!bg_coll_U()) {
						if (!mini) player_y[currplayer] -= 0x700;
						else player_y[currplayer] -= 0x400;
						Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
					}
					high_byte(player_y[currplayer]) -= eject_U;
					player_vel_y[currplayer] = 0;
					
				}
			}
			
			else {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity[currplayer] = 0;
					cube_data2 = 0;
					while (!bg_coll_D()) {
						if (!mini) player_y[currplayer] += 0x700;
						else player_y[currplayer] += 0x400;					
						Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
					}
					high_byte(player_y[currplayer]) -= eject_D;
					player_vel_y[currplayer] = 0;


				}
			}
		}			
	}
}	
*/
#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
