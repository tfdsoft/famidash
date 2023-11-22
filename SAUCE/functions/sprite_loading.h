void init_sprites(void){
    sprite_data  = sprite_list[level];

    tmp1=0;

    while (tmp1 < 8){
        tmp3 = sprite_data[(tmp1<<3)]; activesprites_y[tmp1] = tmp3;
        tmp3 = sprite_data[(tmp1<<3)+1]; activesprites_x[tmp1] = tmp3;
        tmp3 = sprite_data[(tmp1<<3)+2]; low_byte(activesprites_screen[tmp1]) = tmp3;
        tmp3 = sprite_data[(tmp1<<3)+3]; high_byte(activesprites_screen[tmp1]) = tmp3;
        tmp3 = sprite_data[(tmp1<<3)+4]; activesprites_type[tmp1] = tmp3;

        ++ tmp1;
    }
}