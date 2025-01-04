
CODE_BANK_PUSH("XCD_BANK_01")

void ball_eject();
void common_gravity_routine();
void ball_movement(void){
// handle y

	// currplayer_gravity
	// currplayer_vel_y is signed

//	if ((controllingplayer->press_a) && currplayer_vel_y != 0) idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);

	if (gamemode == GAMEMODE_SWING) {

		fallspeed_big = SWING_MAX_FALLSPEED;
		fallspeed_mini = MINI_SWING_MAX_FALLSPEED;
		gravity_big = SWING_GRAVITY;
		gravity_mini = MINI_SWING_GRAVITY;
		common_gravity_routine();

		


	}
	else {		
		fallspeed_big = BALL_MAX_FALLSPEED;
		fallspeed_mini = MINI_BALL_MAX_FALLSPEED;
		gravity_big = BALL_GRAVITY;
		gravity_mini = MINI_BALL_GRAVITY;
		common_gravity_routine();

		



	}
	
	Generic.x = high_byte(currplayer_x);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 1;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}

	if (controllingplayer->press_a || controllingplayer->press_up) idx8_store(cube_data, currplayer, cube_data[currplayer] | 2);	

	ball_eject();
/*
	if (bigboi) {
			Generic.y -= 15;

			ball_eject();
		
			Generic.x += 15;
			
			ball_eject();
		
			Generic.y += 15;

			ball_eject();
	}
	else {
		if (tallmode) {
			
			// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
			Generic.y -= 15;

			ball_eject();
		}	
		if (longmode) {
			
			Generic.x += 15;

			// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
			Generic.y = high_byte(currplayer_y);

			ball_eject();
		}
	}
*/
	Generic.y = high_byte(currplayer_y);
	Generic.x = high_byte(currplayer_x);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 1;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}
	#define BALL_SWITCH_VEL 0x200
	#define MINI_BALL_SWITCH_VEL 0x120
	if (gamemode == GAMEMODE_BALL) {
		if (((controllingplayer->a || controllingplayer->up)) && (ball_switched[currplayer] == 0) && currplayer_vel_y == 0){
			jumps++;
			invert_gravity(currplayer_gravity);
			ball_switched[currplayer] = 1;
			switch (currplayer_gravity){
				case GRAVITY_DOWN: currplayer_vel_y = currplayer_mini ? MINI_BALL_SWITCH_VEL : BALL_SWITCH_VEL; break;
				case GRAVITY_UP: currplayer_vel_y = currplayer_mini ? -MINI_BALL_SWITCH_VEL : -BALL_SWITCH_VEL; break;
			}
			bg_coll_floor_spikes();
		}
		if(ball_switched[currplayer]){
			if (!(controllingplayer->hold & (PAD_A | PAD_UP))){
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
				ball_switched[currplayer] = 0;			
			}
		}
	}
	else {
		if ((controllingplayer->press_a || controllingplayer->press_up) && !ufo_orbed){
			invert_gravity(currplayer_gravity);
			bg_coll_floor_spikes();
		}
	}		
	ufo_orbed = 0;
}

void ball_eject() {
	
		//if(high_byte(currplayer_vel_y) & 0x80){
			if(bg_coll_U()){ // check collision above
				high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U;
				currplayer_vel_y = 0;
				orbactive = 0;
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);			//fix for orb
			}
		//}
		//else{
			if(bg_coll_D()){ // check collision below
			    high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
			    currplayer_vel_y = 0;
				orbactive = 0;
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);		    //fix for orb
			}
		//}		

}	

CODE_BANK_POP()
