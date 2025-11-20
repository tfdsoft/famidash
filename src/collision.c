




putinbank(fixed_lo.collision)
uint8_t get_metatile(uint8_t x, uint16_t y){
    uint8_t tmp = coll_buffer[(y&0xfff0)+(x>>4)];
    return tmp;
}


putinbank(fixed_lo.collision)
uint8_t check_coll_point(uint8_t x, uint16_t y){
    uint8_t tmp = get_metatile(x,y);
    return tmp;
}


putinbank(fixed_lo.collision)
void run_player_collision(){

    // Y COLLISION
    player_speed_y += phys_gravity[0];
    if(player_speed_y > 0x700) player_speed_y = 0x700;
    if(player_speed_y < -0x700) player_speed_y = -0x700;
    
    if((player1_hold & PAD_A) && player.prop.can_jump){
        player_speed_y = phys_jumpvel[0];
    }

    player.y.int24 += player_speed_y;
    if(
        (player_speed_y > 0) && 
        get_metatile((player.x.lo), (player.y.word + player.height))
    ){
        player_speed_y = 0;
        player.y.lo &= 0xf0;
        player.prop.can_jump = 1;
    } else {
        player.prop.can_jump = 0;
    }


    // X COLLISION
    player_speed_x = phys_speed[player.prop.speed];

    player.x.int24 += player_speed_x;


}