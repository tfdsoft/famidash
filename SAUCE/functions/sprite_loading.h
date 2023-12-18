void load_next_sprite(void){
    mmc3_tmp_prg_bank_1(0x0C);
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
    // portals
    if (type < 0x0A) return 0x2f;

    // pads
    if (type == 0x0A) return 0x07; // jump pad
    if (type == 0x0B) return 0x0f; // jump ring


    // triggers
    if (type == 0x0f) return 0x5f;
    if (type & 0x30) return 0x5f;
}

void sprite_collide_lookup(unsigned char type){
    // portals
    if (type & 0x30){
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
    if (type == 0x0B && cube_data == 0x02) {
        cube_data = 0x00;
        if (gravity) player.vel_y = JUMP_VEL^0xFFFF; else player.vel_y = JUMP_VEL;
    }

    switch (type){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7: gamemode = 0x01<<type; break;

        case 8: gravity = 0x00; break;
        case 9: gravity = 0x01; break;
        case 0x0A:
            if (gravity) player.vel_y = PAD_HEIGHT_YELLOW^0xFFFF;
            else player.vel_y = PAD_HEIGHT_YELLOW;
            break;
        case 0x0F: 
            gameState = 0x03; 
            pal_fade_to(4,0); 
            break;
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
                sprite_collide_lookup(tmp4);
            }
        }
    }
}