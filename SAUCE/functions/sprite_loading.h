void init_sprites(void){
    sprite_data  = sprite_list[level];

    tmp1=0;

    while (tmp1 < max_loaded_sprites){
        tmp3 = sprite_data[(tmp1<<3)]; activesprites_y[tmp1] = tmp3; 
        tmp3 = sprite_data[(tmp1<<3)+1]; activesprites_x[tmp1] = tmp3;
        tmp3 = sprite_data[(tmp1<<3)+2]; low_byte(activesprites_screen[tmp1]) = tmp3;
        tmp3 = sprite_data[(tmp1<<3)+3]; high_byte(activesprites_screen[tmp1]) = tmp3;
        tmp3 = sprite_data[(tmp1<<3)+4]; activesprites_type[tmp1] = tmp3;
        // unused byte 5
        // unused byte 6
        // unused byte 7
        gray_line();

        ++ tmp1;
    }
}