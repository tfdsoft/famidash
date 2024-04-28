#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void ship_movement(void){
// handle y

// player_gravity_curr
	// player_vel_y_curr is signed
	//if(player_vel_y_curr < 0x400){
	if(!mini) {
		if(!player_gravity_curr) {
			player_vel_y_curr += SHIP_GRAVITY;
		}
		else {
			player_vel_y_curr -= SHIP_GRAVITY;
		}
		if(player_vel_y_curr > SHIP_MAX_FALLSPEED) player_vel_y_curr = SHIP_MAX_FALLSPEED;
		if(player_vel_y_curr < -SHIP_MAX_FALLSPEED) player_vel_y_curr = -SHIP_MAX_FALLSPEED;

	}
	else {
		if(!player_gravity_curr) {
			player_vel_y_curr += MINI_SHIP_GRAVITY;
		}
		else {
			player_vel_y_curr -= MINI_SHIP_GRAVITY;
		}
		if(player_vel_y_curr > MINI_SHIP_MAX_FALLSPEED) player_vel_y_curr = MINI_SHIP_MAX_FALLSPEED;
		if(player_vel_y_curr < -MINI_SHIP_MAX_FALLSPEED) player_vel_y_curr = -MINI_SHIP_MAX_FALLSPEED;
	}
		
		

	player_y_curr += player_vel_y_curr;
	
	Generic.x = high_byte(player_x_curr);
	Generic.y = high_byte(player_y_curr);
	if (mini) {
		if (high_byte(player_vel_y_curr)) Generic.y -= 1;
		else Generic.y += 1;
	}
	
	
	if(high_byte(player_vel_y_curr) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(player_y_curr) = high_byte(player_y_curr) - eject_U - 1;
			player_vel_y_curr = 0;
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
		    high_byte(player_y_curr) = high_byte(player_y_curr) - eject_D + 1;
		    player_vel_y_curr = 0;
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(player_y_curr); // the rest should be the same
	

	if(pad[controllingplayer] & PAD_A) {
		if (!mini) {
			if (!player_gravity_curr){
			    player_vel_y_curr -= SHIP_GRAVITY<<1;
				} else {
			    player_vel_y_curr += SHIP_GRAVITY<<1;
			}
		}
		else {
			if (!player_gravity_curr){
			    player_vel_y_curr -= MINI_SHIP_GRAVITY<<1;
				} else {
			    player_vel_y_curr += MINI_SHIP_GRAVITY<<1;
			}
		}
	}	
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
