#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void wave_movement(void){

	if(!mini){
		if(currplayer_gravity){
			currplayer_vel_y = -currplayer_vel_x;
		}
		else{
			currplayer_vel_y = currplayer_vel_x;
		}
	}
	else {
		if(currplayer_gravity){
			currplayer_vel_y = -(currplayer_vel_x << 1);
		}
		else{
			currplayer_vel_y = currplayer_vel_x << 1;
		}
	}		
	
	if (pad[controllingplayer] & PAD_A) currplayer_vel_y = -currplayer_vel_y;

	currplayer_y += currplayer_vel_y;
	
	Generic.x = high_byte(currplayer_x);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	Generic.y = high_byte(currplayer_y);
	
	
	bg_coll_U();

	bg_coll_D();


	Generic.y = high_byte(currplayer_y);

	if (currplayer_vel_y != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] |= 2;
		}
	}
}	

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
