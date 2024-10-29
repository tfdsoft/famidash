
CODE_BANK_PUSH("XCD_BANK_01")

void cube_vel_stuff();
void spider_eject();
void common_gravity_routine();
void spider_movement(void){

	fallspeed_big = SPIDER_MAX_FALLSPEED;
	fallspeed_mini = MINI_SPIDER_MAX_FALLSPEED;
	gravity_big = SPIDER_GRAVITY;
	gravity_mini = MINI_SPIDER_GRAVITY;

	common_gravity_routine();

	Generic.x = high_byte(currplayer_x);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 2;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}
	
	spider_eject();
	
	if (!currplayer_gravity) {
		if(controllingplayer->press_a && currplayer_vel_y == 0) {
			jumps++;
			currplayer_gravity = 1;
			do {
				high_byte(currplayer_y) -= 0x08;
				crossPRGBankJump0(do_the_scroll_thing);				
				if (currplayer_y < 0x0600 && scroll_y <= min_scroll_y){
					idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
					break;
				}
				Generic.y = high_byte(currplayer_y); // the rest should be the same
			} while (!bg_coll_U());
			high_byte(currplayer_y) -= eject_U;
			currplayer_vel_y = 0;
		}
}	
	else {
		if(controllingplayer->press_a && currplayer_vel_y == 0) {
			jumps++;
			currplayer_gravity = 0;
			do {
				high_byte(currplayer_y) += 0x08;
				crossPRGBankJump0(do_the_scroll_thing);				
				
				Generic.y = high_byte(currplayer_y); // the rest should be the same
			} while (!bg_coll_D());

			high_byte(currplayer_y) -= eject_D;
			
			currplayer_vel_y = 0;


		}
	}		
	

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 2;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}		

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same


}	



void spider_eject() {
	if(!currplayer_gravity){
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) -= eject_D;
			currplayer_vel_y = 0;


		}
	} else {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) -= eject_U + 1;
			currplayer_vel_y = 0;

		} 
	}
}

void spider_up_wait() {
	do {
		high_byte(currplayer_y) -= 0x08;
		crossPRGBankJump0(do_the_scroll_thing);
		if (currplayer_y < 0x0600 && scroll_y <= min_scroll_y){
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
			break;
		}
		Generic.y = high_byte(currplayer_y); // the rest should be the same
	} while (!bg_coll_U());
}			

void spider_down_wait() {
	do {
		high_byte(currplayer_y) += 0x08;
		crossPRGBankJump0(do_the_scroll_thing);
		Generic.y = high_byte(currplayer_y); // the rest should be the same
	} while (!bg_coll_D());
}				

CODE_BANK_POP()
