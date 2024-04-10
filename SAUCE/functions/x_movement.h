#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")

void x_movement(){
    // handle x

	old_x = player.x;
	switch (speed) {
		case 0: 	player.x += CUBE_SPEED_X1; break;
		case 1:		player.x += CUBE_SPEED_X05; break;
		case 2:		player.x += CUBE_SPEED_X2; break;
	}
	
	if(player.x > 0xf000) { // too far, don't wrap around
        if(old_x >= 0xf000){
            player.x = 0xf000; // max right
        }else{
            player.x = 0x0000; // max left
        }
		player.vel_x = 0;
	} 
	
	Generic.x = high_byte(player.x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(player.y);


	if (!mini) {
    Generic.width = CUBE_WIDTH;
    Generic.height = CUBE_HEIGHT;
	}
	
	else {
    Generic.width = MINI_CUBE_WIDTH;
    Generic.height = MINI_CUBE_HEIGHT;
	}   

	if (player.y < 0x0600){
		cube_data |= 0x01;	//DIE if player goes too high
	};
	
	// no L/R collision required, since that is accounted for with the death script
	
	if (bg_coll_R()) cube_data |= 0x01; // turns out, this is needed to temporarily fix zipping
	if (pad_new & PAD_A) cube_data |= 0x02;
}
#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)


#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")

void x_movement2(){
    // handle x

	old_x = player2.x;
	switch (speed) {
		case 0: 	player2.x += CUBE_SPEED_X1; break;
		case 1:		player2.x += CUBE_SPEED_X05; break;
		case 2:		player2.x += CUBE_SPEED_X2; break;
	}
	
	if(player2.x > 0xf000) { // too far, don't wrap around
        if(old_x >= 0xf000){
            player2.x = 0xf000; // max right
        }else{
            player2.x = 0x0000; // max left
        }
		player2.vel_x = 0;
	} 
	
	Generic.x = high_byte(player2.x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(player2.y);


	if (!mini) {
    Generic.width = CUBE_WIDTH;
    Generic.height = CUBE_HEIGHT;
	}
	
	else {
    Generic.width = MINI_CUBE_WIDTH;
    Generic.height = MINI_CUBE_HEIGHT;
	}   

	if (player2.y < 0x0600){
//		cube_data |= 0x01;	//DIE if player goes too high
	};
	
	// no L/R collision required, since that is accounted for with the death script
	
	if (bg_coll_R()) cube_data |= 0x01; // turns out, this is needed to temporarily fix zipping
	if (pad_new & PAD_A) cube_data |= 0x02;
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
