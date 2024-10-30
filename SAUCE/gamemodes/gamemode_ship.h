
CODE_BANK_PUSH("XCD_BANK_01")

void ufo_ship_eject();
void ship_movement(void){

	fallspeed_big = SHIP_MAX_FALLSPEED;
	fallspeed_mini = MINI_SHIP_MAX_FALLSPEED;
	gravity_big = SHIP_GRAVITY;
	gravity_mini = MINI_SHIP_GRAVITY;
	common_gravity_routine();

	if(currplayer_vel_y > (!mini ? fallspeed_big : fallspeed_mini)) currplayer_vel_y -= (!mini ? gravity_big : gravity_mini);
	if(currplayer_vel_y < (!mini ? -fallspeed_big : -fallspeed_mini)) currplayer_vel_y += (!mini ? gravity_big : gravity_mini);


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
			Generic.y = high_byte(currplayer_y) - 15;
			ufo_ship_eject();
		}	
		if (longmode) {
			Generic.x += 15;
			Generic.y = high_byte(currplayer_y);
			ufo_ship_eject();
		}	
	}		

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same
	Generic.x = high_byte(currplayer_x); // the rest should be the same
	
	if (controllingplayer->press_a) jumps++;

	if(controllingplayer->a) {
		if (!mini) {
			if (!currplayer_gravity){
			    currplayer_vel_y -= SHIP_GRAVITY<<1;
				} else {
			    currplayer_vel_y += SHIP_GRAVITY<<1;
			}
		}
		else {
			if (!currplayer_gravity){
			    currplayer_vel_y -= MINI_SHIP_GRAVITY<<1;
				} else {
			    currplayer_vel_y += MINI_SHIP_GRAVITY<<1;
			}
		}
	}	
}

void ufo_ship_eject() {
	if(bg_coll_U()){ // check collision above
		high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U;
		currplayer_vel_y = 0;
	}
	if(bg_coll_D()){ // check collision below
		high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
		currplayer_vel_y = 0;
	}
}	

CODE_BANK_POP()
