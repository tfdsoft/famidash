
u8 get_metatile_at(u8 x, u16 y){
    return collision_map_0[grid16((x>>4),(y>>4))];
}



static void check_player_collision_x(struct Player* player){
    player->pos.x.full += player->speed.x;
    if(get_metatile_at(player->pos.x.lo,player->pos.y.word)){
        player->pos.x.full -= player->speed.x;

        if(player->speed.x < 0) player->pos.x.lo &= 0xf8; else player->pos.x.lo |= 0x07;
    }
}

static u8 check_player_collision_y(struct Player* player){
    player->pos.y.full += player->speed.y;
    u8 tmp = get_metatile_at(player->pos.x.lo,player->pos.y.word);
    if(tmp){
        player->pos.y.full -= player->speed.y;

        if(player->speed.y < 0) player->pos.y.lo &= 0xf8; else player->pos.y.lo |= 0x07;
        player->speed.y = 0;
    }
    return tmp;
}



void move_player(struct Player* player){
    //#define collision_byte (*(u8*)(sram_buffer+2016+30))

    u8 collision_byte;

    player->speed.y += phys_gravity[0];
    if(player->speed.y > 0x0700) player->speed.y = 0x0700;
    //if(player->speed.y > 0) {
    collision_byte = check_player_collision_y(player);
        if(joypad1.a) 
            player->speed.y = phys_jumpvel[0];
    //}

    
    

    player->speed.x = 0;
    if(joypad1.left) {
        player->speed.x = -phys_speed[0];
    }
    if(joypad1.right) {
        player->speed.x = phys_speed[0];
    }
    check_player_collision_x(player);


    #define left_side_scroll_bounds 0x60
    u16 tmp = (player->pos.x.word - Camera.x.word);
    if(tmp < left_side_scroll_bounds){
        Camera.x.word = player->pos.x.word - left_side_scroll_bounds;
    }
    #undef left_side_scroll_bounds

    #define right_side_scroll_bounds 0x80
    tmp = (player->pos.x.word - Camera.x.word);
    if(tmp >= right_side_scroll_bounds){
        Camera.x.word = player->pos.x.word - right_side_scroll_bounds;
    }
    #undef right_side_scroll_bounds
}