void init_sprites(void){
    sprite_data = (unsigned char *) sprite_list[level];

    spr_index = 0;

    
    while (spr_index < max_loaded_sprites){
        if (sprite_data[spr_index<<3] == TURN_OFF) break;
        mmc3_tmp_prg_bank_1(0x0C);
        tmp3 = sprite_data[(spr_index<<3)+0];  low_byte(activesprites_x[spr_index]) = tmp3; 
        tmp3 = sprite_data[(spr_index<<3)+1]; high_byte(activesprites_x[spr_index]) = tmp3; 
        tmp3 = sprite_data[(spr_index<<3)+2];  low_byte(activesprites_y[spr_index]) = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+3]; high_byte(activesprites_y[spr_index]) = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+4]; activesprites_type[spr_index] = tmp3;
        // unused byte 5
        // unused byte 6
        // unused byte 7


        tmp3 = activesprites_x[spr_index]; activesprites_realx[spr_index] = tmp3;
        tmp3 = activesprites_y[spr_index]; activesprites_realy[spr_index] = tmp3;

        gray_line();
        mmc3_pop_prg_bank_1();
        ++spr_index;
    }
}


char get_position(void){
    tmp5 -= scroll_x;
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
    // portals
    if (type == 0) return 0x2f;
    if (type & 0x07) return 0x2f;

    // pads
    if (type == 0x0A) return 0x07; // jump pad
    if (type == 0x0B) return 0x0f; // jump ring

    // triggers
    if (type & 0x30) return 0xff;
}

void sprite_collide_lookup(unsigned char type){
    // portals
    if (type == 0) gamemode = 0x01;
    if (type & 0x07 && !(type & 0xF8)) gamemode = 0x01<<type;
    switch (type){
        case 0x0A:
            if (gravity) player.vel_y = PAD_HEIGHT_YELLOW^0xFFFF;
            else player.vel_y = PAD_HEIGHT_YELLOW;
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
            Generic2.height = sprite_height_lookup(tmp4);

            Generic2.x = activesprites_realx[index];
            Generic2.y = activesprites_realy[index];
            
            if (check_collision(&Generic, &Generic2)) {
                tmp4 = activesprites_type[index];
                sprite_collide_lookup(tmp4);
            }
        }
    }
}