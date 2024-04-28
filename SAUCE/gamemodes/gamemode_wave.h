#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void wave_movement(void){

	if(!mini){
		if(player_gravity_curr){
			player_vel_y_curr = -player_vel_x_curr;
		}
		else{
			player_vel_y_curr = player_vel_x_curr;
		}
	}
	else {
		if(player_gravity_curr){
			player_vel_y_curr = -(player_vel_x_curr << 1);
		}
		else{
			player_vel_y_curr = player_vel_x_curr << 1;
		}
	}		
	
	if (pad[controllingplayer] & PAD_A) player_vel_y_curr = -player_vel_y_curr;

	player_y_curr += player_vel_y_curr;
	
	Generic.x = high_byte(player_x_curr);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	Generic.y = high_byte(player_y_curr);
	
	
	bg_coll_U();

	bg_coll_D();


	Generic.y = high_byte(player_y_curr);

	if (player_vel_y_curr != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
