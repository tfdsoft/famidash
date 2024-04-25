#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void ship_movement(void){
// handle y

// player_gravity[currplayer]
	// player_vel_y[currplayer] is signed
	//if(player_vel_y[currplayer] < 0x400){
	if(!mini) {
		if(!player_gravity[currplayer]) {
			player_vel_y[currplayer] += SHIP_GRAVITY;
		}
		else {
			player_vel_y[currplayer] -= SHIP_GRAVITY;
		}
		if(player_vel_y[currplayer] > SHIP_MAX_FALLSPEED) player_vel_y[currplayer] = SHIP_MAX_FALLSPEED;
		if(player_vel_y[currplayer] < -SHIP_MAX_FALLSPEED) player_vel_y[currplayer] = -SHIP_MAX_FALLSPEED;

	}
	else {
		if(!player_gravity[currplayer]) {
			player_vel_y[currplayer] += MINI_SHIP_GRAVITY;
		}
		else {
			player_vel_y[currplayer] -= MINI_SHIP_GRAVITY;
		}
		if(player_vel_y[currplayer] > MINI_SHIP_MAX_FALLSPEED) player_vel_y[currplayer] = MINI_SHIP_MAX_FALLSPEED;
		if(player_vel_y[currplayer] < -MINI_SHIP_MAX_FALLSPEED) player_vel_y[currplayer] = -MINI_SHIP_MAX_FALLSPEED;
	}
		
		

	player_y[currplayer] += player_vel_y[currplayer];
	
	Generic.x = high_byte(player_x[currplayer]);
	Generic.y = high_byte(player_y[currplayer]);
	
	
	if(high_byte(player_vel_y[currplayer]) & 0x80){
		if(bg_coll_U() && !bg_coll_R() ){ // check collision above
			high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_U;
			player_vel_y[currplayer] = 0;
		}
	}
	else{
		if(bg_coll_D() && !bg_coll_R() ){ // check collision below
		    high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_D + 1;
		    player_vel_y[currplayer] = 0;
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y[currplayer]); // the rest should be the same
	

	if(pad[controllingplayer] & PAD_A) {
		if (!mini) {
			if (!player_gravity[currplayer]){
			    player_vel_y[currplayer] -= SHIP_GRAVITY<<1;
				} else {
			    player_vel_y[currplayer] += SHIP_GRAVITY<<1;
			}
		}
		else {
			if (!player_gravity[currplayer]){
			    player_vel_y[currplayer] -= MINI_SHIP_GRAVITY<<1;
				} else {
			    player_vel_y[currplayer] += MINI_SHIP_GRAVITY<<1;
			}
		}
	}	
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
