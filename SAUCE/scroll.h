void do_the_scroll_thing(){
    scroll_x += CUBE_SPEED_X1;
    set_scroll_x(high_byte(scroll_x));

    
    if (pad & PAD_UP) --scroll_y;
    if (pad & PAD_DOWN) ++scroll_y;
    while (scroll_y > 0xEF) --scroll_y;
    while (scroll_y < 0x10) ++scroll_y;
    set_scroll_y(scroll_y);
    
}