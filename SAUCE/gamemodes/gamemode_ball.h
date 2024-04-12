#pragma code-name(push, "LVL_BANK_15")
#pragma data-name(push, "LVL_BANK_15")
#pragma rodata-name(push, "LVL_BANK_15")


void ball_movement(void){
// handle y

// gravity
	// player.vel_y is signed

	if (!mini) {
		if(!gravity){
			player.vel_y += BALL_GRAVITY;
		}
		else{
			player.vel_y -= BALL_GRAVITY;
		}
		if(player.vel_y > CUBE_MAX_FALLSPEED) player.vel_y = CUBE_MAX_FALLSPEED;
		if(player.vel_y < -CUBE_MAX_FALLSPEED) player.vel_y = -CUBE_MAX_FALLSPEED;
	}
	else {
		if(!gravity){
			player.vel_y += MINI_BALL_GRAVITY;
		}
		else{
			player.vel_y -= MINI_BALL_GRAVITY;
		}
		if(player.vel_y > CUBE_MAX_FALLSPEED) player.vel_y = MINI_CUBE_MAX_FALLSPEED;
		if(player.vel_y < -CUBE_MAX_FALLSPEED) player.vel_y = -MINI_CUBE_MAX_FALLSPEED;
	}
	
	
	player.y += player.vel_y;

	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	
	
	if(high_byte(player.vel_y) & 0x80){
		if(bg_coll_U()  && !bg_coll_R() ){ // check collision above
			high_byte(player.y) = high_byte(player.y) - eject_U;
			player.vel_y = 0;
			cube_data = 0;			//fix for orb
		}
	}
	else{
		if(bg_coll_D() && !bg_coll_R() ){ // check collision below
		    high_byte(player.y) = high_byte(player.y) - eject_D;
		    player.vel_y = 0;
			cube_data = 0;		    //fix for orb
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same
	

	if ((pad & PAD_A) && (kandotemp2 == 0) && (player.vel_y == 0)){
		gravity ^= 0x01;
		kandotemp2 = 1;
		switch (gravity){
			case 0x00: player.vel_y = 0x6F; break;
			case 0x01: player.vel_y = -0x6F; break;
			}
	}
	if(kandotemp2 == 1){
		if ((pad & PAD_A) == 0){
			kandotemp2 = 0;			
		}
	}
}

void ball_movement2(void){
// handle y

// gravity
	// player.vel_y is signed

	if (!mini) {
		if(gravity){
			player2.vel_y += BALL_GRAVITY;
		}
		else{
			player2.vel_y -= BALL_GRAVITY;
		}
		if(player2.vel_y > CUBE_MAX_FALLSPEED) player2.vel_y = CUBE_MAX_FALLSPEED;
		if(player2.vel_y < -CUBE_MAX_FALLSPEED) player2.vel_y = -CUBE_MAX_FALLSPEED;
	}
	else {
		if(gravity){
			player2.vel_y += MINI_BALL_GRAVITY;
		}
		else{
			player2.vel_y -= MINI_BALL_GRAVITY;
		}
		if(player2.vel_y > CUBE_MAX_FALLSPEED) player2.vel_y = MINI_CUBE_MAX_FALLSPEED;
		if(player2.vel_y < -CUBE_MAX_FALLSPEED) player2.vel_y = -MINI_CUBE_MAX_FALLSPEED;
	}
	
	
	player2.y += player2.vel_y;
	player2.x = player.x;	
	Generic.x = high_byte(player2.x);
	Generic.y = high_byte(player2.y);
	
	
//	if(high_byte(player2.vel_y) & 0x80){
		if(bg_coll_U()  && !bg_coll_R() ){ // check collision above
			high_byte(player2.y) = high_byte(player2.y) - eject_U;
			player2.vel_y = 0;
			cube_data = 0;			//fix for orb
		}
//	}
//	else{
		if(bg_coll_D() && !bg_coll_R() ){ // check collision below
		    high_byte(player2.y) = high_byte(player2.y) - eject_D;
		    player2.vel_y = 0;
			cube_data = 0;		    //fix for orb
		}
//	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player2.y); // the rest should be the same
	
	if (!twoplayer) {
		if ((pad & PAD_A) && (kandotemp5 == 0) && (player2.vel_y == 0)){
			gravity ^= 0x01;
			kandotemp5 = 1;
			switch (gravity){
				case 0x00: player2.vel_y = 0x6F; break;
				case 0x01: player2.vel_y = -0x6F; break;
				}
		}
		if(kandotemp5 == 1){
			if ((pad & PAD_A) == 0){
				kandotemp5 = 0;			//makes sure the ball doesn't allow you to hold A while changing gravity
			}					//and instantly change back when it lands while holding the initial A press. You must release A to make this 0.
		}
	}
	else {
		if ((pad2 & PAD_A) && (kandotemp5 == 0) && (player2.vel_y == 0)){
			gravity ^= 0x01;
			kandotemp5 = 1;
			switch (gravity){
				case 0x00: player2.vel_y = 0x6F; break;
				case 0x01: player2.vel_y = -0x6F; break;
				}
		}
		if(kandotemp5 == 1){
			if ((pad2 & PAD_A) == 0){
				kandotemp5 = 0;			//makes sure the ball doesn't allow you to hold A while changing gravity
			}					//and instantly change back when it lands while holding the initial A press. You must release A to make this 0.
		}
	}		
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
