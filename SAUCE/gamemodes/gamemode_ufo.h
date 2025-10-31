
CODE_BANK_PUSH(MOVEMENT_BANK)
void bigboi_stuff();
void ufo_ship_eject();
void common_gravity_routine();
void ufo_movement(){

	tmpfallspeed = UFO_MAX_FALLSPEED(currplayer_table_idx);
	tmpgravity = UFO_GRAVITY(currplayer_table_idx);
	common_gravity_routine();

		


	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);

	ufo_ship_eject();

	bigboi_stuff(); 
	
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);

	// check collision down a little lower than UFO
//	Generic.y = high_byte(currplayer_y); // the rest should be the same


	if((controllingplayer->press & (PAD_A | PAD_UP)) && !ufo_orbed[currplayer]) {
		currplayer_vel_y = UFO_JUMP_VEL(currplayer_table_idx); // JUMP
		jumps++;
	}
	ufo_orbed[currplayer] = 0;
}	

void bigboi_stuff() {
	if (bigboi) {
			Generic.y -= 15;
			ufo_ship_eject();
		
			Generic.x += 15;
			ufo_ship_eject();

			Generic.y += 15;
			ufo_ship_eject();
	}
	else {
		if (tallmode) {
			Generic.y = high_byte(currplayer_y) - 15;
			ufo_ship_eject();
		}	
		if (longmode) {
			Generic.x += 15;
			Generic.y = high_byte(currplayer_y);
			ufo_ship_eject();
		}	
	}	
}	

CODE_BANK_POP()
