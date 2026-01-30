
CODE_BANK_PUSH(MOVEMENT_BANK)
void ufo_ship_eject();
void common_gravity_routine();
void ufo_movement(){

	tmpfallspeed = UFO_MAX_FALLSPEED(currplayer_table_idx);
	tmpgravity = UFO_GRAVITY(currplayer_table_idx);
	common_gravity_routine();

		


	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);

	ufo_ship_eject();

	
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


CODE_BANK_POP()
