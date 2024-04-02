//extern int SPRITE_BANK;

#define SPR_BANK_00 0x1C


void load_next_sprite(void){
    mmc3_tmp_prg_bank_1(SPR_BANK_00);
    if (sprite_data[spr_index<<3] == TURN_OFF) return;
    tmp3 = sprite_data[(spr_index<<3)+0];  low_byte(activesprites_x[spr_index % max_loaded_sprites]) = tmp3; 
    tmp3 = sprite_data[(spr_index<<3)+1]; high_byte(activesprites_x[spr_index % max_loaded_sprites]) = tmp3; 
    tmp3 = sprite_data[(spr_index<<3)+2];  low_byte(activesprites_y[spr_index % max_loaded_sprites]) = tmp3;
    tmp3 = sprite_data[(spr_index<<3)+3]; high_byte(activesprites_y[spr_index % max_loaded_sprites]) = tmp3;
    tmp3 = sprite_data[(spr_index<<3)+4]; activesprites_type[spr_index % max_loaded_sprites] = tmp3;
    // unused byte 5
    // unused byte 6 
    // unused byte 7


    tmp3 = activesprites_x[spr_index]; activesprites_realx[spr_index % max_loaded_sprites] = tmp3;
    tmp3 = activesprites_y[spr_index]; activesprites_realy[spr_index % max_loaded_sprites] = tmp3;

    //gray_line();
    mmc3_pop_prg_bank_1();
    ++spr_index;
}



void init_sprites(void){
    mmc3_set_prg_bank_1(SPR_BANK_00);
    sprite_data = (unsigned char *) sprite_list[level];

    spr_index = 0;
    while (spr_index < max_loaded_sprites){
        if (sprite_data[spr_index<<3] == TURN_OFF) break;
        load_next_sprite();
    }
}


char get_position(void){
    tmp5 -= scroll_x;
    if (high_byte(tmp5) == 0xff) {
        load_next_sprite();
        return 0;
    }
    tmp6 -= scroll_y;
    temp_x = tmp5 & 0x00ff;
    temp_y = tmp6 & 0x00ff;
    if (high_byte(tmp5)) return 0;
    if (high_byte(tmp6)) return 0;
    return 1;
}

void check_spr_objects(void){
    for (index = 0; index < max_loaded_sprites; ++index){
        activesprites_active[index] = 0;
        
        low_byte(tmp5) = low_byte(activesprites_x[index]);
        high_byte(tmp5) = high_byte(activesprites_x[index]);
        low_byte(tmp6) = low_byte(activesprites_y[index]);
        high_byte(tmp6) = high_byte(activesprites_y[index]);

        activesprites_active[index] = get_position();
        activesprites_realx[index] = temp_x;
        activesprites_realy[index] = temp_y;
    }
}

char sprite_height_lookup(unsigned char type){
    if (type == 0xFF) { }
    else if (type & 0x30){				//COLOR TRIGGERS ON LOADING
        tmp2 = (type & 0x3f)-0x10;
        if (type & 0xC0){
            pal_col(6, tmp2);
            if (tmp2-0x10 & 0xC0) pal_col(5, 0x0f);
            else pal_col(5, (tmp2-0x10));
        } else {
            pal_col(0, tmp2);
            if (tmp2-0x10 & 0xC0) pal_col(1, 0x0f);
            else pal_col(1, (tmp2-0x10));
        }
        
    }

    // portals
    if (type == 0x05) return 0x0f; // blue orb
    if (type == 0x06) return 0x0f; // pink jump orb
    if (type == 0x07) return 0x17; // coin

    if (type < 0x0A) return 0x20;

    // pads
    if (type == 0x0A) return 0x07; // yellow jump pad
    if (type == 0x0B) return 0x0f; // yellow jump orb
    if (type == 0x0C) return 0x07; // yellow jump pad Upside Down
    if (type == 0x0D) return 0x07; // Gravity Pad
    if (type == 0x0E) return 0x07; // Gravity Pad Upside Down

    // triggers
    if (type == 0x0f) return 0x5f;
    if (type & 0x30) return 0x5f;
    
    
}

void sprite_collide_lookup(){
    // portals
    if (tmp4 == 0xFF) {	
    
    }
    else if (tmp4 == 0x0B && cube_data == 0x02) {		//orb
        cube_data = 0x00;
        if (gravity) player.vel_y = JUMP_VEL^0xFFFF; else player.vel_y = JUMP_VEL;
    }

    else if (tmp4 == 0x07) {					//coin
	    coins++;
//	    famistudio_sfx_play(sfx_click, 0);			//test sfx
	activesprites_type[index] = 0xFF;		//make coin disappear here
    }

    else if (tmp4 == 5)  {
	    if (cube_data == 2) {			//blue orb
		cube_data = 0x00;
		gravity ^= 0x01;
        if (!gravity) player.vel_y = PAD_HEIGHT_YELLOW^0xFFFF;
        else player.vel_y = PAD_HEIGHT_YELLOW;
	    }
    } 

    else if (tmp4 == 6) {
	if (cube_data == 2) {		//nest it so that the next else-if for tmp4 doesn't trigger
		cube_data = 0x00;
		if (gravity) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
		else player.vel_y = PAD_HEIGHT_PINK;
	}
    }
    else if (tmp4 < 8) gamemode = tmp4;
    else if (tmp4 < 10) gravity = tmp4 - 8;
    else if (tmp4 == 0x0A || tmp4 == 0x0C) {
        if (gravity) player.vel_y = PAD_HEIGHT_YELLOW^0xFFFF;
        else player.vel_y = PAD_HEIGHT_YELLOW;
    } 
    else if (tmp4 == 0x0D || tmp4 == 0x0E) {			//gravity pads
	    gravity ^= 0x01;				//flip gravity
	    player.vel_y = -(player.vel_y);		//launch up right away OMGZ IT WORKS
    }
    else if (tmp4 == 0x0F) {
        gameState = 0x03; 
        pal_fade_to(4,0); 
    }
}

void sprite_collide(){

    Generic.x = high_byte(player.x);
    Generic.y = high_byte(player.y);
    Generic.width = CUBE_WIDTH;
    Generic.height = CUBE_HEIGHT;

    Generic2.width = 0x0f;
    for (index = 0; index < max_loaded_sprites; ++index){
        tmp3 = activesprites_active[index];
        if (tmp3){
            tmp4 = activesprites_type[index];
            tmp2 = sprite_height_lookup(tmp4);
            Generic2.height = tmp2;

            Generic2.x = activesprites_realx[index];
            Generic2.y = activesprites_realy[index];
            
            if (check_collision(&Generic, &Generic2)) {
                sprite_collide_lookup();
            }
        }
    }
}