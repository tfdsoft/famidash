
static u8 get_metatile_at(u8 x, u16 y){
    return collision_map_0[grid16((x>>4),(y>>4))];
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
struct Metatile_Attr check_collision_point(struct Player* player, s8 extra_x, s8 extra_y){
    u8 x = player->pos.x.lo + extra_x;
    u16 y = player->pos.y.word + extra_y;

    //u8 metatile = ;

    // special cases!
    switch ((get_metatile_at(x,y) & 0xf0)>>4) {
        case 0:
            return (struct Metatile_Attr){0b0000,0,0};
        case 1:
            return (struct Metatile_Attr){0b1111,0,2};
            break;
        default:
            break;
    }

    struct Metatile_Attr attributes = metatiles_collision[get_metatile_at(x,y)];
    

    u8 collide_mask = 0;
    // get top/bottom
    if((y & 0x08)==0) collide_mask |= 0b1100;
    else collide_mask |= 0b0011;
    // get left/right side
    if((x & 0x08)==0) collide_mask &= 0b1010;
    else collide_mask &= 0b0101;
    if((attributes.collision & collide_mask)){
        return attributes;
    } 

    //attributes.collision = 0;
    return (struct Metatile_Attr){0b0000,0,0};
}



u8 check_collision_LR(struct Player* player, s8 extra_x){
    //u8 x = player->pos.x.lo + extra_x;
    //u16 y = player->pos.y.word;
    struct Metatile_Attr metatile;

    metatile = check_collision_point(player, extra_x, 0);
    if(metatile.collision) return 1+metatile.type;
    metatile = check_collision_point(player, extra_x, (player->size.height >> 1));
    if(metatile.collision) return 1+metatile.type;
    metatile = check_collision_point(player, extra_x, player->size.height);
    if(metatile.collision) return 1+metatile.type;

    return 0;
}

u8 check_collision_UD(struct Player* player, s8 extra_y){
    //u8 x = player->pos.x.lo;
    //u16 y = player->pos.y.word + extra_y;
    struct Metatile_Attr metatile;

    __asm__("brk \n .byte $ea");
    metatile = check_collision_point(player, 0, extra_y);
    if(metatile.collision) return 1;
    metatile = check_collision_point(player, (player->size.width >> 1), extra_y);
    if(metatile.collision) return 1;
    metatile = check_collision_point(player, player->size.width, extra_y);
    if(metatile.collision) return 1;

    return 0;
}


void move_player(struct Player* player){
    struct Metatile_Attr collision_value;

    player->speed.y += phys_gravity[0];
    if(player->speed.y > 0x700) player->speed.y = 0x700;

    

    if(joypad1.up) player->speed.y = -0x400;
    player->pos.y.full += player->speed.y;
    
    if(1){ // used to encase the collision value

        if(player->speed.y > 0){
            u8 collision_value = check_collision_UD(player, player->size.height);
            if(collision_value){
                player->pos.y.lo &= 0xf8;
                player->speed.y = 0;
                if(joypad1.a) player->speed.y = phys_jumpvel[0];
            }
        } else {
            u8 collision_value = check_collision_UD(player, 0);
            if(collision_value){
                player->pos.y.lo = 1+(player->pos.y.lo | 0x07);
                player->speed.y = 0;
            }
        }
    }
    
    


    player->speed.x = 0;
    if(joypad1.left) player->speed.x = -phys_speed[0];
    if(joypad1.right) 
    player->speed.x = phys_speed[0];
    
    player->pos.x.full += player->speed.x;
    //collision_value = check_collision_point(player, (player->size.width >>1), (player->size.height >>1));
    //if(collision_value.type == 2) {
    //    //player->properties.is_dead = 1;
    //}
    if(1){
        if(player->speed.x > 0){
            u8 collision_value = check_collision_LR(player, player->size.width);
            if(collision_value) { // right
                player->pos.x.lo &= 0xf8;
                player->speed.x = 0;
            }
        } else {
            u8 collision_value = check_collision_LR(player, 0);
            if(collision_value) { // left
                player->pos.x.word = 1+(player->pos.x.word | 0x0007);
                player->speed.x = 0;
            }
        }
        
    }



    #define left_side_scroll_bounds 0x40
    u16 tmp = (player->pos.x.word - Camera.x.word);
    if(tmp < left_side_scroll_bounds){
        Camera.x.word = player->pos.x.word - left_side_scroll_bounds;
        if(Camera.x.hi & 0x80) Camera.x.word = 0;
    }
    #undef left_side_scroll_bounds

    #define right_side_scroll_bounds 0x60
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