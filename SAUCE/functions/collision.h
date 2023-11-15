char bg_collision_sub(void){
    // THIS DOESN'T READ FROM THE UPPER COLLISION MAP FSR
    // I CAN'T FIGURE THIS OUT PLEASE HELP
    
    
    
    if(temp_y >= 0xf0) return 0;
        
	coordinates = (temp_x >> 4) + (temp_y & 0xf0);
    // we just need 4 bits each from x and y
	
    tmp3 = temp_room&1; // high byte
    if (tmp3 && coordinates >= 0xc0) return COL_ALL;
    if (tmp3 & 1)
        collision = collisionMap1[coordinates];
    else
        collision = collisionMap0[coordinates];
	

    return is_solid[collision];
}



char bg_coll_L(void){
    // check 2 points on the left side
    tmp5 = Generic.x + scroll_x;
    temp_x = (char)tmp5; // low byte

    eject_L = temp_x | 0xf0;
	tmp1 = Generic.y + 2;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    if(bg_collision_sub() & COL_ALL) return 1;
    
    tmp1 = Generic.y + Generic.height;
    tmp1 -= 2;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_R(void){
    // check 2 points on the right side
	tmp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)tmp5; // low byte

    eject_R = (temp_x + 1) & 0x0f;
	tmp1 = Generic.y + 2;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    if(bg_collision_sub() & COL_ALL) return 1;
    
    tmp1 = Generic.y + Generic.height;
    tmp1 -= 2;
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_U(void){
    // check 2 points on the top side
    tmp5 = Generic.x + scroll_x;
    temp_x = (char)tmp5; // low byte
    
	tmp1 = Generic.y;
	tmp5 = add_scroll_y(tmp1, scroll_y); 
    temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    eject_U = temp_y | 0xf0;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    tmp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)tmp5; // low byte
    
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_D(void){
    // check 2 points on the bottom side
	tmp5 = Generic.x + scroll_x;
    temp_x = (char)tmp5; // low byte
    
	tmp1 = Generic.y + Generic.height;
	tmp5 = add_scroll_y(tmp1, scroll_y);
    temp_y = (char)tmp5; // low byte
	temp_room = tmp5 >> 8; // high byte
    eject_D = (temp_y + 1) & 0x0f;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    tmp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)tmp5; // low byte
    
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}



char bg_coll_D2(void){
    // check 2 points on the bottom side
    // a little lower, for jumping
    tmp5 = Generic.x + scroll_x;
    temp_x = (char)tmp5; // low byte

    tmp1 = Generic.y + Generic.height;
	tmp5 = add_scroll_y(tmp1, scroll_y);
    temp_y = (char)tmp5; // low byte
    temp_room = tmp5 >> 8; // high byte
    ++temp_y;
    if(bg_collision_sub() & COL_ALL) {cube_rotate = 0x0080; return 1;}

    tmp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)tmp5; // low byte
    
    if(bg_collision_sub() & COL_ALL) {cube_rotate = 0x0080; return 1;}
    
	

    return 0;
}

char bg_coll_U2(void){
    // check 2 points on the bottom side
    // a little lower, for jumping
    tmp5 = Generic.x + scroll_x;
    temp_x = (char)tmp5; // low byte

    tmp1 = Generic.y;
	tmp5 = add_scroll_y(tmp1, scroll_y);
    temp_y = (char)tmp5; // low byte
    temp_room = tmp5 >> 8; // high byte
    --temp_y;
    if(bg_collision_sub() & COL_ALL) {cube_rotate = 0x0080; return 1;}

    tmp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)tmp5; // low byte
    
    if(bg_collision_sub() & COL_ALL) {cube_rotate = 0x0080; return 1;}
    
	

    return 0;
}



char bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist
	tmp5 = Generic.x + scroll_x + (Generic.width >> 1);
	temp_x = (char)tmp5; // low byte

	tmp1 = Generic.y + (Generic.width >> 1);
	tmp5 = add_scroll_y(tmp1, scroll_y);
    temp_y = (char)tmp5; // low byte
	if(bg_collision_sub() ) cube_data = 0x01;

	if(cube_data & 0x01) reset_level();
}