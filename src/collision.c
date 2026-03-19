
static u8 get_metatile_at(u8 x, u16 y){
    return collision_map_0[grid16((x>>4),(y>>4))];
}


static u8 get_collision_at_point(u8 x, u16 y){

}

/*
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
}*/

u8 check_collision_LR(struct Player* player, s8 extra_x){
    u8 x = player->pos.x.lo + extra_x;
    u16 y = player->pos.y.word;

    if(get_metatile_at(x,y)) return 1;
    if(get_metatile_at(x,y+15)) return 1;

    return 0;
}

u8 check_collision_UD(struct Player* player, s8 extra_y){
    u8 x = player->pos.x.lo;
    u16 y = player->pos.y.word + extra_y;

    if(get_metatile_at(x,y)) return 1;
    if(get_metatile_at(x+15,y)) return 1;

    return 0;
}


void move_player(struct Player* player){

    player->speed.y += phys_gravity[0];
    if(player->speed.y > 0x700) player->speed.y = 0x700;

    //common_gravity_routine


    player->pos.y.full += player->speed.y;
    if(check_collision_UD(player, 0)){
        player->pos.y.lo = 1+(player->pos.y.lo | 0x07);
        player->speed.y = 0;
    }
    if(check_collision_UD(player, 16)){
        player->pos.y.lo &= 0xf8;
        player->speed.y = 0;
        if(joypad1.a) player->speed.y = phys_jumpvel[0];
    }
    if(joypad1.up) player->speed.y = phys_jumpvel[0];
    


    player->speed.x = 0;
    if(joypad1.left) player->speed.x = -phys_speed[0];
    if(joypad1.right) player->speed.x = phys_speed[0];
    
    player->pos.x.full += player->speed.x;
    if(check_collision_LR(player, 0)) { // left
        player->pos.x.word = 1+(player->pos.x.word | 0x0007);
        player->speed.x = 0;
    }
    if(check_collision_LR(player, 15)) { // left
        player->pos.x.lo &= 0xf8;
        player->speed.x = 0;
    }



    #define left_side_scroll_bounds 0x60
    u16 tmp = (player->pos.x.word - Camera.x.word);
    if(tmp < left_side_scroll_bounds){
        Camera.x.word = player->pos.x.word - left_side_scroll_bounds;
        if(Camera.x.hi & 0x80) Camera.x.word = 0;
    }
    #undef left_side_scroll_bounds

    #define right_side_scroll_bounds 0x80
    if(tmp >= right_side_scroll_bounds){
        Camera.x.word = player->pos.x.word - right_side_scroll_bounds;
    }
    #undef right_side_scroll_bounds

    #define top_side_scroll_bounds 0x60
    tmp = (player->pos.y.word - Camera.y.word);
    if(tmp < top_side_scroll_bounds){
        Camera.y.word = player->pos.y.word - top_side_scroll_bounds;
        if(Camera.y.hi & 0x80) Camera.y.word = 0;
    }
    #undef top_side_scroll_bounds

    #define bottom_side_scroll_bounds 0x80
    //tmp += 0x30;
    if(tmp >= bottom_side_scroll_bounds){
        Camera.y.word = player->pos.y.word - bottom_side_scroll_bounds;
        if((Camera.y.word > (active_lvl.height<<4) - 0xc0)) {
            Camera.y.word = (active_lvl.height<<4) - 0xc0;
        }
    }
    #undef bottom_side_scroll_bounds
}