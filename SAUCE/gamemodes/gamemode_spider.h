#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void spider_movement(void){
// handle y

// player_gravity_curr
	// player_vel_y_curr is signed
	//if(player_vel_y_curr < 0x400){

	if(!mini){
		if(!player_gravity_curr){
			if(player_vel_y_curr > CUBE_MAX_FALLSPEED){
				player_vel_y_curr = CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += CUBE_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= CUBE_GRAVITY;
		}
	}
	else {
		if(!player_gravity_curr){
			if(player_vel_y_curr > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y_curr += player_vel_y_curr;
	
	Generic.x = high_byte(player_x_curr);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (player_gravity_curr) {
		Generic.y = high_byte(player_y_curr) - 2;
	} else {
		Generic.y = high_byte(player_y_curr) + 1;
	}
	
	if(!player_gravity_curr){
		if(bg_coll_D()){ // check collision below
			high_byte(player_y_curr) -= eject_D;
			player_vel_y_curr = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				player_gravity_curr = 1;
				do {
					player_y_curr -= 0x800;
					Generic.y = high_byte(player_y_curr); // the rest should be the same
				} while (!bg_coll_U());
				high_byte(player_y_curr) -= eject_U;
				player_vel_y_curr = 0;
			}
		}
	} else {
		if(bg_coll_U()){ // check collision above
			high_byte(player_y_curr) -= eject_U + 1;
			player_vel_y_curr = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				player_gravity_curr = 0;
				do {
					player_y_curr += 0x800;
					Generic.y = high_byte(player_y_curr); // the rest should be the same
				} while (!bg_coll_D());

				high_byte(player_y_curr) -= eject_D;
				
				player_vel_y_curr = 0;


			}
		} 
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y_curr); // the rest should be the same

	if (player_vel_y_curr != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}
}	
/*
void spider_movement2(void){
// handle y

// player_gravity_curr
	// player_vel_y_curr is signed
	//if(player_vel_y_curr < 0x400){

	if(!mini){
		if(player_gravity_curr){
			if(player_vel_y_curr > CUBE_MAX_FALLSPEED){
				player_vel_y_curr = CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += CUBE_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= CUBE_GRAVITY;
		}
	}
	else {
		if(player_gravity_curr){
			if(player_vel_y_curr > MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -MINI_CUBE_MAX_FALLSPEED){
				player_vel_y_curr = -MINI_CUBE_MAX_FALLSPEED;
			} else player_vel_y_curr -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y_curr += player_vel_y_curr;
	player_x_curr = player_x_curr;
	Generic.x = high_byte(player_x_curr);
	Generic.y = high_byte(player_y_curr);
	
		if(player_gravity_curr){
			if(bg_coll_D() && !bg_coll_R()){ // check collision below
			    high_byte(player_y_curr) -= eject_D;
			}
			if(bg_coll_D())    player_vel_y_curr = 0;
			
		}
		if(!player_gravity_curr){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				high_byte(player_y_curr) -= eject_U;
			}
			if(bg_coll_U())    player_vel_y_curr = 0;
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y_curr); // the rest should be the same

	if (player_vel_y_curr != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data2 = 2;
		}
	}
	if ( player_vel_y_curr == 0 || player_vel_y_curr == CUBE_MAX_FALLSPEED || player_vel_y_curr == -CUBE_MAX_FALLSPEED ) {
		if (!twoplayer) {
			if (!player_gravity_curr) {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity_curr = 1;
					cube_data2 = 0;
					while (!bg_coll_U()) {
						if (!mini) player_y_curr -= 0x700;
						else player_y_curr -= 0x400;
						Generic.y = high_byte(player_y_curr); // the rest should be the same
					}
					high_byte(player_y_curr) -= eject_U;
					player_vel_y_curr = 0;
					
				}
			}
			
			else {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity_curr = 0;
					cube_data2 = 0;
					while (!bg_coll_D()) {
						if (!mini) player_y_curr += 0x700;
						else player_y_curr += 0x400;					
						Generic.y = high_byte(player_y_curr); // the rest should be the same
					}
					high_byte(player_y_curr) -= eject_D;
					player_vel_y_curr = 0;


				}
			}
		}
		else {
			if (!player_gravity_curr) {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity_curr = 1;
					cube_data2 = 0;
					while (!bg_coll_U()) {
						if (!mini) player_y_curr -= 0x700;
						else player_y_curr -= 0x400;
						Generic.y = high_byte(player_y_curr); // the rest should be the same
					}
					high_byte(player_y_curr) -= eject_U;
					player_vel_y_curr = 0;
					
				}
			}
			
			else {
				if(pad_new[controllingplayer] & PAD_A) {
		//			player_gravity_curr = 0;
					cube_data2 = 0;
					while (!bg_coll_D()) {
						if (!mini) player_y_curr += 0x700;
						else player_y_curr += 0x400;					
						Generic.y = high_byte(player_y_curr); // the rest should be the same
					}
					high_byte(player_y_curr) -= eject_D;
					player_vel_y_curr = 0;


				}
			}
		}			
	}
}	
*/
#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
