#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void ufo_movement(void){
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
			if(player_vel_y[currplayer] > MINI_UFO_MAX_FALLSPEED){
				player_vel_y[currplayer] = MINI_UFO_MAX_FALLSPEED;
			} else player_vel_y[currplayer] += MINI_CUBE_GRAVITY;
		}
		else{
			if(player_vel_y[currplayer] < -MINI_UFO_MAX_FALLSPEED){
				player_vel_y[currplayer] = -MINI_UFO_MAX_FALLSPEED;
			} else player_vel_y[currplayer] -= MINI_CUBE_GRAVITY;
		}
	}		
	player_y[currplayer] += player_vel_y[currplayer];
	Generic.x = high_byte(player_x[currplayer]);
	Generic.y = high_byte(player_y[currplayer]);
	
	if(high_byte(player_vel_y[currplayer]) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(player_y[currplayer]) -= eject_U;
			player_vel_y[currplayer] = 0;
		}
	} else {
		if(bg_coll_D()){ // check collision below
			high_byte(player_y[currplayer]) -= eject_D - 1;
			player_vel_y[currplayer] = 0;
		}
	}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same

//	if (player_vel_y[currplayer] != 0){
//		if(pad_new[controllingplayer] & PAD_A) {
//			cube_data = 2;
//		}
//	}

	
	if (player_gravity[currplayer]){
			//if(bg_coll_U2()) {
		//		cube_data = 0;
				if(pad_new[controllingplayer] & PAD_A) {
					if (!mini) player_vel_y[currplayer] = 	UFO_JUMP_VEL^0xFFFF; // JUMP
					else player_vel_y[currplayer] = MINI_UFO_JUMP_VEL^0xFFFF; // JUMP
				}
			//}
	} else {
			//if(bg_coll_D2()) {
			//	cube_data = 0;				
				if(pad_new[controllingplayer] & PAD_A) {
					if (!mini) player_vel_y[currplayer] = 	UFO_JUMP_VEL; // JUMP
					else player_vel_y[currplayer] = MINI_UFO_JUMP_VEL; // JUMP
				}
			//}
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
