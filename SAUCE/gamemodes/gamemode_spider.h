#pragma code-name(push, "LVL_BANK_15")
#pragma data-name(push, "LVL_BANK_15")
#pragma rodata-name(push, "LVL_BANK_15")


void spider_movement(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){

	if(!mini){
		if(!gravity){
			if(player.vel_y > CUBE_MAX_FALLSPEED){
				player.vel_y = CUBE_MAX_FALLSPEED;
			} else player.vel_y += CUBE_GRAVITY;
		}
		else{
			if(player.vel_y < -CUBE_MAX_FALLSPEED){
				player.vel_y = -CUBE_MAX_FALLSPEED;
			} else player.vel_y -= CUBE_GRAVITY;
		}
	}
	else {
		if(!gravity){
			if(player.vel_y > MINI_CUBE_MAX_FALLSPEED){
				player.vel_y = MINI_CUBE_MAX_FALLSPEED;
			} else player.vel_y += MINI_CUBE_GRAVITY;
		}
		else{
			if(player.vel_y < -MINI_CUBE_MAX_FALLSPEED){
				player.vel_y = -MINI_CUBE_MAX_FALLSPEED;
			} else player.vel_y -= MINI_CUBE_GRAVITY;
		}
	}		
	player.y += player.vel_y;
	
	Generic.x = high_byte(player.x);
	Generic.y = high_byte(player.y);
	
		if(!gravity){
			if(bg_coll_D() && !bg_coll_R()){ // check collision below
			    high_byte(player.y) -= eject_D;
			}
			if(bg_coll_D())    player.vel_y = 0;
			
		}
		if(gravity){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				high_byte(player.y) -= eject_U;
			}
			if(bg_coll_U())    player.vel_y = 0;
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player.y); // the rest should be the same

	if (player.vel_y != 0){
		if(pad_new & PAD_A) {
			cube_data = 2;
		}
	}


	if ( player.vel_y == 0 || player.vel_y == CUBE_MAX_FALLSPEED || player.vel_y == -CUBE_MAX_FALLSPEED ) {
		if (!gravity) {
			if(pad_new & PAD_A) {
				gravity = 1;
				while (!bg_coll_U()) {
					if (!mini) player.y -= 0x700;
					else player.y -= 0x400;
					Generic.y = high_byte(player.y); // the rest should be the same
				}
				if (!mini) high_byte(player.y) -= eject_U;
				else high_byte(player.y) -= eject_U*3;
				player.vel_y = 0;
				
			}
		}
		
		else {
			if(pad_new & PAD_A) {
				gravity = 0;
				while (!bg_coll_D()) {
					if (!mini) player.y += 0x700;
					else player.y += 0x400;
					Generic.y = high_byte(player.y); // the rest should be the same
				}
				if (!mini) high_byte(player.y) -= eject_D;
				else high_byte(player.y) -= eject_D*3;
				player.vel_y = 0;


			}
		}
	}
}	

void spider_movement2(void){
// handle y

// gravity
	// player.vel_y is signed
	//if(player.vel_y < 0x400){

	if(!mini){
		if(gravity){
			if(player2.vel_y > CUBE_MAX_FALLSPEED){
				player2.vel_y = CUBE_MAX_FALLSPEED;
			} else player2.vel_y += CUBE_GRAVITY;
		}
		else{
			if(player2.vel_y < -CUBE_MAX_FALLSPEED){
				player2.vel_y = -CUBE_MAX_FALLSPEED;
			} else player2.vel_y -= CUBE_GRAVITY;
		}
	}
	else {
		if(gravity){
			if(player2.vel_y > MINI_CUBE_MAX_FALLSPEED){
				player2.vel_y = MINI_CUBE_MAX_FALLSPEED;
			} else player2.vel_y += MINI_CUBE_GRAVITY;
		}
		else{
			if(player2.vel_y < -MINI_CUBE_MAX_FALLSPEED){
				player2.vel_y = -MINI_CUBE_MAX_FALLSPEED;
			} else player2.vel_y -= MINI_CUBE_GRAVITY;
		}
	}		
	player2.y += player2.vel_y;
	player2.x = player.x;
	Generic.x = high_byte(player2.x);
	Generic.y = high_byte(player2.y);
	
		if(gravity){
			if(bg_coll_D() && !bg_coll_R()){ // check collision below
			    high_byte(player2.y) -= eject_D;
			}
			if(bg_coll_D())    player2.vel_y = 0;
			
		}
		if(!gravity){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				high_byte(player2.y) -= eject_U;
			}
			if(bg_coll_U())    player2.vel_y = 0;
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player2.y); // the rest should be the same

	if (player2.vel_y != 0){
		if(pad_new & PAD_A) {
			cube_data = 2;
		}
	}
	if ( player2.vel_y == 0 || player2.vel_y == CUBE_MAX_FALLSPEED || player2.vel_y == -CUBE_MAX_FALLSPEED ) {
		if (!gravity) {
			if(pad_new & PAD_A) {
	//			gravity = 1;
				while (!bg_coll_U()) {
					if (!mini) player2.y -= 0x700;
					else player2.y -= 0x400;
					Generic.y = high_byte(player2.y); // the rest should be the same
				}
				high_byte(player2.y) -= eject_U;
				player2.vel_y = 0;
				
			}
		}
		
		else {
			if(pad_new & PAD_A) {
	//			gravity = 0;
				while (!bg_coll_D()) {
					if (!mini) player2.y += 0x700;
					else player2.y += 0x400;					
					Generic.y = high_byte(player2.y); // the rest should be the same
				}
				high_byte(player2.y) -= eject_D;
				player2.vel_y = 0;


			}
		}
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
