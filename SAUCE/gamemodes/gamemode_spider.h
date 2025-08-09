
CODE_BANK_PUSH("XCD_BANK_01")

void cube_vel_stuff();
void spider_eject();
void common_gravity_routine();
void spider_movement(){

	tmpfallspeed = SPIDER_MAX_FALLSPEED(currplayer_table_idx);
	tmpgravity = SPIDER_GRAVITY(currplayer_table_idx);

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
		if(((controllingplayer->press_a || controllingplayer->press_up) || cube_data[currplayer] & 2) && currplayer_vel_y == 0 && !orbed[currplayer]) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 0b11111101);	
			jumps++;
			currplayer_gravity = GRAVITY_UP;
			update_currplayer_table_idx();
			spider_up_wait();
			high_byte(currplayer_y) -= eject_U;
			currplayer_vel_y = 0;
		}
}	
	else {
		if(((controllingplayer->press_a || controllingplayer->press_up) || cube_data[currplayer] & 2) && currplayer_vel_y == 0 && !orbed[currplayer]) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 0b11111101);
			jumps++;
			currplayer_gravity = GRAVITY_DOWN;
			update_currplayer_table_idx();
			spider_down_wait();
			high_byte(currplayer_y) -= eject_D;
			currplayer_vel_y = 0;
		}
	}		
	

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame

/*	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 2;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}		*/   									//this seemed to be unused??

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
#define LEFT_POS tmp7
#define RIGHT_POS tmp9
void spider_up_wait() {
	LEFT_POS = Generic.x + low_word(scroll_x) + 3;
	RIGHT_POS = Generic.x + low_word(scroll_x) + Generic.width - 3;
	do {
		high_byte(currplayer_y) -= 0x08;
		crossPRGBankJump0(process_y_scroll);
		if (high_byte(currplayer_y) <= 0x07){ // && scroll_y <= min_scroll_y
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
			break;
		}
		Generic.y = high_byte(currplayer_y); // the rest should be the same
	} while (!bg_coll_U_spider());
}			

void spider_down_wait() {
	LEFT_POS = Generic.x + low_word(scroll_x) + 3;
	RIGHT_POS = Generic.x + low_word(scroll_x) + Generic.width - 3;
	do {
		high_byte(currplayer_y) += 0x08;
		crossPRGBankJump0(process_y_scroll);
		Generic.y = high_byte(currplayer_y); // the rest should be the same
	} while (!bg_coll_D_spider());
}				
#undef LEFT_POS
#undef RIGHT_POS
CODE_BANK_POP()
