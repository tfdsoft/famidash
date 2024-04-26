#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")

const unsigned short speed_table[] = {
	CUBE_SPEED_X1, CUBE_SPEED_X05, CUBE_SPEED_X2, CUBE_SPEED_X3, CUBE_SPEED_X4
};


void x_movement(){
    // handle x

	old_x = player_x[currplayer];
	

	player_vel_x[currplayer] = speed_table[speed];
	player_x[currplayer] += player_vel_x[currplayer];

	if(player_x[currplayer] > 0xf000) { // too far, don't wrap around
        if(old_x >= 0xf000){
            player_x[currplayer] = 0xf000; // max right
        }else{
            player_x[currplayer] = 0x0000; // max left
        }
		player_vel_x[currplayer] = 0;
	} 
	
	Generic.x = high_byte(player_x[currplayer]); // this is much faster than passing a pointer to player
	Generic.y = high_byte(player_y[currplayer]);


	if (!mini) {
    Generic.width = CUBE_WIDTH;
    Generic.height = CUBE_HEIGHT;
	}
	
	else {
    Generic.width = MINI_CUBE_WIDTH;
    Generic.height = MINI_CUBE_HEIGHT;
	}   

	if (player_y[currplayer] < 0x0600){
		cube_data[currplayer] |= 0x01;	//DIE if player goes too high
	};
	
	// no L/R collision required, since that is accounted for with the death script
	
	if (high_byte(player_x[currplayer]) > 0x10 && bg_coll_R()) cube_data[currplayer] |= 0x01; // turns out, this is needed to temporarily fix zipping
	if (pad_new[controllingplayer] & PAD_A) cube_data[currplayer] |= 0x02;
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
