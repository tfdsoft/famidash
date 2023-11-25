void init_sprites(void){
    sprite_data = sprite_list[level];

    spr_index = 0;
    while (spr_index < max_loaded_sprites || sprite_data[spr_index<<3] == TURN_OFF){
        tmp3 = sprite_data[(spr_index<<3)]; activesprites_y[spr_index] = tmp3; 
        tmp3 = sprite_data[(spr_index<<3)+1]; activesprites_x[spr_index] = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+2]; low_byte(activesprites_screen[spr_index]) = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+3]; high_byte(activesprites_screen[spr_index]) = tmp3;
        tmp3 = sprite_data[(spr_index<<3)+4]; activesprites_type[spr_index] = tmp3;
        // unused byte 5
        // unused byte 6
        // unused byte 7
        gray_line();
        ++spr_index;
    }
}

void sprite_collide(){
    
}