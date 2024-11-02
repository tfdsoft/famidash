
CODE_BANK_PUSH("XCD_BANK_01")

void ufo_ship_eject();
void common_gravity_routine();
void ufo_movement(void){

	fallspeed_big = UFO_MAX_FALLSPEED;
	fallspeed_mini = MINI_UFO_MAX_FALLSPEED;
	gravity_big = UFO_GRAVITY;
	gravity_mini = MINI_UFO_GRAVITY;
	common_gravity_routine();

		


	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);

	ufo_ship_eject();

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
			Generic.y -= 15;

			ufo_ship_eject();
		}
		if (longmode) {
			Generic.x += 15;
			Generic.y = high_byte(currplayer_y);

			ufo_ship_eject();
		}
	}
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);

	// check collision down a little lower than UFO
//	Generic.y = high_byte(currplayer_y); // the rest should be the same


	if(controllingplayer->press_a || controllingplayer->press_up) {
		if (!mini) currplayer_vel_y = 	UFO_JUMP_VEL^(0x0000-currplayer_gravity); // JUMP
		else currplayer_vel_y = MINI_UFO_JUMP_VEL^(0x0000-currplayer_gravity); // JUMP
		jumps++;
	}

}	

CODE_BANK_POP()
