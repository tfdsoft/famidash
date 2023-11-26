void init_sprites(void){
    sprite_data = (unsigned char *) sprite_list[level];

    spr_index = 0;
    while (spr_index < max_loaded_sprites){
        if (sprite_data[spr_index<<3] == TURN_OFF) break;

        tmp3 = sprite_data[(spr_index<<3)]; low_byte(activesprites_y[spr_index]) = tmp3; 
        tmp3 = sprite_data[(spr_index<<3)+1]; activesprites_x[spr_index] = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+2]; low_byte(activesprites_screen[spr_index]) = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+3]; high_byte(activesprites_screen[spr_index]) = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+4]; activesprites_type[spr_index] = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+5]; high_byte(activesprites_y[spr_index]) = tmp3; 
        // unused byte 6
        // unused byte 7
        gray_line();
        ++spr_index;
    }
}

void check_spr_objects(void){
    for (index = 0; index < max_loaded_sprites; ++index){
        tmp5 = (low_byte(activesprites_screen[index]) << 8) + activesprites_x[index];
    }
}







char sprite_height_lookup(unsigned char type){
    if (type & 0x30) return 0xff;
}


void sprite_collide(){

    Generic.x = high_byte(player.x);
    Generic.y = high_byte(player.y);
    Generic.width = CUBE_WIDTH;
    Generic.height = CUBE_HEIGHT;

    Generic2.width = 0x0f;
    for (index = 0; index < max_loaded_sprites; ++index){
        tmp4 = activesprites_type[index];
        Generic2.height = sprite_height_lookup(tmp4);

    }
}