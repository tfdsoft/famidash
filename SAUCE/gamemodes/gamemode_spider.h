#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void spider_movement(void){
// handle y

// currplayer_gravity
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){
	max_fallspeed_big = CUBE_MAX_FALLSPEED;
	max_fallspeed_mini = MINI_CUBE_MAX_FALLSPEED;
	gravity_big = CUBE_GRAVITY;
	gravity_mini = MINI_CUBE_GRAVITY;

	common_gravity_routine();

	Generic.x = high_byte(currplayer_x);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 2;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}
	
	if(!currplayer_gravity){
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) -= eject_D;
			currplayer_vel_y = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				currplayer_gravity = 1;
				do {
					high_byte(currplayer_y) -= 0x08;
					Generic.y = high_byte(currplayer_y); // the rest should be the same
				} while (!bg_coll_U());
				high_byte(currplayer_y) -= eject_U;
				currplayer_vel_y = 0;
			}
		}
	} else {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) -= eject_U + 1;
			currplayer_vel_y = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				currplayer_gravity = 0;
				do {
					high_byte(currplayer_y) += 0x08;
					Generic.y = high_byte(currplayer_y); // the rest should be the same
				} while (!bg_coll_D());

				high_byte(currplayer_y) -= eject_D;
				
				currplayer_vel_y = 0;


			}
		} 
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same

	if (currplayer_vel_y != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			uint8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);
		}
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
