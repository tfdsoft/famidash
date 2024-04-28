#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void ufo_movement(void){
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
			if(player_vel_y_curr > MINI_UFO_MAX_FALLSPEED){
				player_vel_y_curr = MINI_UFO_MAX_FALLSPEED;
			} else player_vel_y_curr += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y_curr < -MINI_UFO_MAX_FALLSPEED){
				player_vel_y_curr = -MINI_UFO_MAX_FALLSPEED;
			} else player_vel_y_curr -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y_curr += player_vel_y_curr;
	Generic.x = high_byte(player_x_curr);
	Generic.y = high_byte(player_y_curr);
	if (mini) {
		if (high_byte(player_vel_y_curr)) Generic.y -= 1;
		else Generic.y += 1;
	}
	
	if(high_byte(player_vel_y_curr) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(player_y_curr) -= eject_U + 1;
			player_vel_y_curr = 0;
		}
	} else {
		if(bg_coll_D()){ // check collision below
			high_byte(player_y_curr) -= eject_D - 1;
			player_vel_y_curr = 0;
		}
	}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y_curr); // the rest should be the same

//	if (player_vel_y_curr != 0){
//		if(pad_new[controllingplayer] & PAD_A) {
//			cube_data = 2;
//		}
//	}

	
	if (player_gravity_curr){
			//if(bg_coll_U2()) {
		//		cube_data = 0;
				if(pad_new[controllingplayer] & PAD_A) {
					if (!mini) player_vel_y_curr = 	UFO_JUMP_VEL^0xFFFF; // JUMP
					else player_vel_y_curr = MINI_UFO_JUMP_VEL^0xFFFF; // JUMP
				}
			//}
	} else {
			//if(bg_coll_D2()) {
			//	cube_data = 0;				
				if(pad_new[controllingplayer] & PAD_A) {
					if (!mini) player_vel_y_curr = 	UFO_JUMP_VEL; // JUMP
					else player_vel_y_curr = MINI_UFO_JUMP_VEL; // JUMP
				}
			//}
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
