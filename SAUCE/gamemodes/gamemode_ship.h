
CODE_BANK_PUSH("XCD_BANK_01")

#if !__VS_SYSTEM
void bigboi_stuff();
#endif
void ufo_ship_eject();
void ship_movement(){

	fallspeed_big = SHIP_MAX_FALLSPEED;
	fallspeed_mini = MINI_SHIP_MAX_FALLSPEED;
	gravity_big = SHIP_GRAVITY;
	gravity_mini = MINI_SHIP_GRAVITY;
	#if !__VS_SYSTEM
	if (controllingplayer->a || controllingplayer->up) {
		gravity_big = (gravity_big / 5) * 6;
		gravity_mini = (gravity_mini / 5) * 6;
	}
	#endif
	common_gravity_routine();

	if(currplayer_vel_y > (!currplayer_mini ? fallspeed_big : fallspeed_mini)) currplayer_vel_y -= (!mini ? gravity_big : gravity_mini);
	if(currplayer_vel_y < (!currplayer_mini ? -fallspeed_big : -fallspeed_mini)) currplayer_vel_y += (!mini ? gravity_big : gravity_mini);


	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	
	ufo_ship_eject();

	#if !__VS_SYSTEM
	bigboi_stuff();
	#else
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
	#endif

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same
	Generic.x = high_byte(currplayer_x); // the rest should be the same
	
	if(controllingplayer->a || controllingplayer->up) {
		if (!currplayer_mini) {
			if (!currplayer_gravity){
				#if !__VS_SYSTEM
			    currplayer_vel_y -= gravity_big<<1;
				} else {
			    currplayer_vel_y += gravity_big<<1;
			    #else
			    currplayer_vel_y -= SHIP_GRAVITY<<1;
				} else {
			    currplayer_vel_y += SHIP_GRAVITY<<1;
			    #endif
			}
		}
		else {
			if (!currplayer_gravity){
				#if !__VS_SYSTEM
			    currplayer_vel_y -= gravity_mini<<1;
				} else {
			    currplayer_vel_y += gravity_mini<<1;
			    #else
			    currplayer_vel_y -= MINI_SHIP_GRAVITY<<1;
				} else {
			    currplayer_vel_y += MINI_SHIP_GRAVITY<<1;
			    #endif
			}
		}
	}	
}

void ufo_ship_eject() {
	//if (!currplayer_was_on_slope_counter || currplayer_slope_type & SLOPE_UPSIDEDOWN) {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U - 1;
			currplayer_vel_y = 0;
		}
	//}
	//if (!currplayer_was_on_slope_counter || !(currplayer_slope_type & SLOPE_UPSIDEDOWN)) {
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
			currplayer_vel_y = 0;
		}
	//}
}	

CODE_BANK_POP()
