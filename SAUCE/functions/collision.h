char bg_collision_sub(void){
    if(temp_y >= 0xf0) return 0;
        
	coordinates = (temp_x >> 4) + (temp_y & 0xf0);
    // we just need 4 bits each from x and y
	
    tmp3 = temp_room&1; // high byte
    if (tmp3 && coordinates >= 0xc0) return COL_ALL;
    if (tmp3 == 0)
        collision = collisionMap0[coordinates];
    else
        collision = collisionMap1[coordinates];
	

    return is_solid[collision];
}



char bg_coll_L(void){
    // check 2 points on the left side
    tmp5 = Generic.x + low2bytes(scroll_x);
    temp_x = (char)tmp5; // low byte

    eject_L = temp_x | 0xf0;
	tmp1 = Generic.y + 2;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    if(bg_collision_sub() & COL_BOTTOM || bg_collision_sub() & COL_TOP) return 0;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    tmp1 = Generic.y + Generic.height;
    tmp1 -= 2;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    if(bg_collision_sub() & COL_BOTTOM || bg_collision_sub() & COL_TOP) return 0;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_R(void){
    // check 2 points on the right side
	tmp5 = Generic.x + low2bytes(scroll_x) + Generic.width +1;
    temp_x = (char)tmp5; // low byte

	tmp1 = Generic.y + (Generic.height >> 1);
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    if(bg_collision_sub() & COL_BOTTOM || bg_collision_sub() & COL_TOP) return 0;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_U(void){
	// check 2 points on the bottom side
	tmp5 = Generic.x + low2bytes(scroll_x) -1;
	temp_x = (char)tmp5; // low byte

	tmp1 = Generic.y-1;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
	eject_U = temp_y | 0xf0;

	if(!gravity) {
		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_BOTTOM) return 1;

		tmp5 = Generic.x + low2bytes(scroll_x) + Generic.width +1;
		temp_x = (char)tmp5; // low byte

		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_BOTTOM) return 1;
	}
	else {
		if(bg_collision_sub() & COL_TOP) {
			tmp1 = Generic.y+7;
			tmp5 = add_scroll_y(tmp1, scroll_y);
			temp_y = (char)tmp5; // low byte
			temp_room = tmp5 >> 8; // high byte
			eject_U = temp_y | 0xf0;			
			if(bg_collision_sub() & COL_TOP) return 1;
		}
		
		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_BOTTOM) return 1;

		tmp5 = Generic.x + low2bytes(scroll_x) + Generic.width +1;
		temp_x = (char)tmp5; // low byte

		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_BOTTOM) return 1;
	}

	return 0;
	
}

char bg_coll_D(void){
	// check 2 points on the bottom side
	tmp5 = Generic.x + low2bytes(scroll_x) -1;
	temp_x = (char)tmp5; // low byte

	if (!mini) tmp1 = Generic.y + Generic.height;
	else tmp1 = Generic.y + Generic.height+8;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
	eject_D = (temp_y + 1) & 0x0f;

	if(!gravity) {
		if(bg_collision_sub() & COL_BOTTOM) {
			if (!mini) tmp1 = Generic.y + (Generic.height/2);
			else tmp1 = Generic.y + ((Generic.height+8)/2);
			tmp5 = add_scroll_y(tmp1, scroll_y);
			temp_y = (char)tmp5; // low byte
			temp_room = tmp5 >> 8; // high byte
			eject_D = (temp_y + 1) & 0x0f;	 
			if(bg_collision_sub() & COL_BOTTOM) return 1;
		}


		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_TOP) return 1;

		tmp5 = Generic.x + low2bytes(scroll_x) + Generic.width +1;
		temp_x = (char)tmp5; // low byte


		if(bg_collision_sub() & COL_BOTTOM) {
			if (!mini) tmp1 = Generic.y + (Generic.height/2);
			else tmp1 = Generic.y + ((Generic.height+8)/2);
			tmp5 = add_scroll_y(tmp1, scroll_y);
			temp_y = (char)tmp5; // low byte
			temp_room = tmp5 >> 8; // high byte
			eject_D = (temp_y + 1) & 0x0f;	 
			if(bg_collision_sub() & COL_BOTTOM) return 1;
		} 
		
		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_TOP) return 1;
	
	}
	else {
		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_BOTTOM) return 1;

		tmp5 = Generic.x + low2bytes(scroll_x) + Generic.width +1;
		temp_x = (char)tmp5; // low byte

		if(bg_collision_sub() & COL_ALL || bg_collision_sub() & COL_BOTTOM) return 1;
	}
	
	return 0;
}






void bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist
	tmp5 = Generic.x + low2bytes(scroll_x) + (Generic.width >> 1)-1;
	temp_x = (char)tmp5; // low byte

	tmp1 = Generic.y + (Generic.width >> 1);
	tmp5 = add_scroll_y(tmp1, scroll_y);
    temp_y = (char)tmp5; // low byte
    temp_room = tmp5 >> 8; // high byte

	if(bg_collision_sub() ) cube_data = 0x01;

    
	++temp_x; // low byte

    if(bg_collision_sub() ) cube_data = 0x01;
    

	if(!DEBUG_MODE && cube_data & 0x01) reset_level();
}