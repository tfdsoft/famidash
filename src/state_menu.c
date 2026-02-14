banked(startup_bank.data) const u8 pal_title[32]={ 
    0x11,0x0f,0x01,0x30,
    0x11,0x0f,0x2a,0x39,
    0x11,0x01,0x11,0x30,
    0x11,0x0f,0x21,0x31,
    
    0x11,0x0f,0x10,0x30,
    0x11,0x0f,0x2a,0x28,
    0x11,0x28,0x17,0x0f,
    0x11,0x0f,0x21,0x31,
};

banked(startup_bank.data) const u8 nt_title[374]={
0x02,0x01,0x02,0x3f,0x00,0x02,0x87,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,
0x89,0x82,0x83,0x82,0x8b,0x8c,0x8d,0x00,0x02,0x0f,0x90,0x91,0x92,0x93,0x94,0x95,
0x96,0x97,0x98,0x99,0x92,0x93,0x9a,0x9b,0x9c,0x9d,0x00,0x02,0x0f,0xa0,0xa1,0xa2,
0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xa2,0xa3,0xaa,0xab,0xac,0xad,0x00,0x02,0x0f,
0x8a,0x02,0x0f,0x00,0x02,0x4f,0xc8,0xca,0xcc,0xce,0x00,0x00,0xc0,0xc2,0xc4,0xc6,
0x00,0x00,0xc8,0xca,0xcc,0xce,0x00,0x02,0x0f,0xc9,0xcb,0xcd,0xcf,0x00,0x00,0xc1,
0xc3,0xc5,0xc7,0x00,0x00,0xd0,0xd2,0xd4,0xcf,0x00,0x02,0x0f,0xe8,0xea,0xec,0xee,
0x00,0x00,0xe0,0xe2,0xe4,0xe6,0x00,0x00,0xe8,0xd3,0xd5,0xee,0x00,0x02,0x0f,0xe9,
0xeb,0xed,0xef,0x00,0x00,0xe1,0xe3,0xe5,0xe7,0x00,0x00,0xe9,0xeb,0xed,0xef,0x00,
0x02,0xc7,0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xc0,0xc2,0xc4,0xc6,0xc8,0xca,
0xcc,0xce,0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xc0,0xc2,0xc4,0xc6,0xc8,0xca,
0xcc,0xce,0xc1,0xc3,0xc5,0xc7,0xc9,0xcb,0xcd,0xcf,0xc1,0xc3,0xc5,0xc7,0xc9,0xcb,
0xcd,0xcf,0xc1,0xc3,0xc5,0xc7,0xc9,0xcb,0xcd,0xcf,0xc1,0xc3,0xc5,0xc7,0xc9,0xcb,
0xcd,0xcf,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,
0xdc,0xde,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,
0xdc,0xde,0xd1,0xd3,0xd5,0xd7,0xd9,0xdb,0xdd,0xdf,0xd1,0xd3,0xd5,0xd7,0xd9,0xdb,
0xdd,0xdf,0xd1,0xd3,0xd5,0xd7,0xd9,0xdb,0xdd,0xdf,0xd1,0xd3,0xd5,0xd7,0xd9,0xdb,
0xdd,0xdf,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,
0xec,0xee,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,
0xec,0xee,0xe1,0xe3,0xe5,0xe7,0xe9,0xeb,0xed,0xef,0xe1,0xe3,0xe5,0xe7,0xe9,0xeb,
0xed,0xef,0xe1,0xe3,0xe5,0xe7,0xe9,0xeb,0xed,0xef,0xe1,0xe3,0xe5,0xe7,0xe9,0xeb,
0xed,0xef,0x01,0x02,0x3f,0x00,0x02,0x09,0x50,0x02,0x03,0x00,0x02,0x03,0x05,0x02,
0x03,0x00,0x02,0x03,0x55,0x44,0x11,0x55,0x00,0x02,0x09,0xa0,0x02,0x07,0xaa,0x02,
0x07,0x00,0x02,0x07,0x02,0x00
};

banked(startup_bank.data) const u8 mspr_title[]={
    // everything in this table is shifted to the left by
    // one pixel due to *the problematic line.*

    // small button sprites
    87, 184, 0xf5, 1,
    95, 184, 0xf7, 1,
    119, 184, 0xf1, 1,
    127, 184, 0xf3, 1, // this line is problematic.
    151, 184, 0xf9, 1,
    159, 184, 0xfb, 1,

    // ROBTOP text
    7, 200, 0x41, 2,  // r/t
    15, 200, 0x43, 2, // o/f
    23, 200, 0x45, 2, // b/d
    31, 200, 0x47, 2, // t/s
    39, 200, 0x49, 2, // o/o
    47, 200, 0x4b, 2, // p/f
    55, 200, 0x4d, 2, //  /t

    // large button sprites (the blue parts)
    // (top)
    116, 101, 0xd7, 0b00100011,
    130, 101, 0xd7, 0b00100011,
    70, 102, 0xd7, 0b00100011,
    80, 102, 0xd7, 0b00100011,
    166, 102, 0xd7, 0b00100011,
    176, 102, 0xd7, 0b00100011,

    // (bottom)
    116, 108, 0xd7, 0b00100011,
    130, 108, 0xd7, 0b00100011,
    70, 106, 0xd7, 0b00100011,
    80, 106, 0xd7, 0b00100011,
    166, 106, 0xd7, 0b00100011,
    176, 106, 0xd7, 0b00100011,
 
    0x80 // end of data
};

banked(startup_bank.data) const u8 mspr_selectarrow[]={
    0, 0,  0x5f,   0b00000000,
    8,  0,  0x5f,   0b01000000,
    0x80
};

banked(startup_bank.data) const u8 mspr_selectbox[]={
    0, 0,  0x4f,   0b00000000,
    8,  0,  0x4f,   0b01000000,
    0x80
};

banked(startup_bank.data) const u16 mspr_select_pos[]={
    0x5078, // play
    0x50a8, // community
    0xb858, // settings
    0xb878, // music
    0xb898, // help
    0x5048, // icon kit
};
#define menu_button_count (sizeof(mspr_select_pos)>>1)

banked(startup_bank.data) const u8 menu_irq_table[] = {
    15,
    0x60,0x81, //1 lo/hi bytes of function goes here
    3,
    0x10,

    78,
    0x60,0x81, //6 lo/hi bytes of function goes here
    5,
    7,

    78,
    0x60,0x81, //11 lo/hi bytes of function goes here
    5,
    8,
    0, //15 x scroll goes here

    255, // end of table
};

banked(startup_bank.func)
void state_menu() {
    unsigned char menu_color = 0x11;
    unsigned short interrupt_scroll = 0;
    unsigned short scroll_bank = 0;
    signed char selection = 0;

    famistudio_music_stop();
    // enable music
    se_post_nmi_ptr = se_music_update;

    // load parallax background
    se_vram_address(0x1000);
    set_chr_bank(0,0x10);
    set_chr_bank(1,0x12);
    
    if(loaded_bg_set != background_set){
        se_vram_donut_decompress(chr_bg[background_set], chr_bank_2);
        vram_generate_parallax(background_set);
        loaded_bg_set = background_set;
    }

    set_chr_bank(2,4);
    set_chr_bank(3,5);
    set_chr_bank(4,6);
    set_chr_bank(5,7);

    // load menu stuff
    se_vram_address(0x000);
    se_vram_donut_decompress(chr_menu_global, chr_bank_0);
    se_vram_donut_decompress(chr_menu_font_pusab, chr_bank_0);
    se_vram_donut_decompress(chr_menu_famidash, chr_bank_0);
    se_vram_donut_decompress(chr_menu_buttons, chr_bank_0);

    // load ground
    set_chr_bank(0,0x8);
    se_vram_donut_decompress(chr_g[ground_set], chr_bank_3);
    // the "robtop/tfdsoft" text is there
    se_vram_donut_decompress(chr_menu_robtop, chr_bank_0);

    // set second sprite bank to the big buttons
    set_chr_bank(1,0x6);
    
    // set second bg bank to parallax
    set_chr_bank(3,0x10);

    // clear tilemap
    se_vram_address(0x2000);
    se_memory_fill((void*)0x2007,0,0x800);

    // write the parallax tilemap
    se_vram_address(0x2000);
    vram_write_parallax(background_set);

    // write the title screen tilemap
    se_vram_address(0x2000);
    se_vram_unrle(nt_title,1);
    se_vram_unrle(nt_title,0);

    

    se_set_palette_all(pal_title);

    se_memory_copy(
        (void*)se_irq_table,
        (void*)menu_irq_table,
        sizeof(menu_irq_table)
    );
    se_write_function_to_irq_table(
        custom_irq_that_updates_chr_bank,1
    );
    se_write_function_to_irq_table(
        custom_irq_that_updates_chr_bank,6
    );
    se_write_function_to_irq_table(
        custom_irq_that_updates_chr_and_x_scroll,11
    );
    __asm__("cli");
    
    // run once before fading in
    se_clear_sprites();
    se_draw_metasprite(1,0,mspr_title);

    se_string_vram_buffer("2.0", nametable_address_A(20,9));

    #ifdef FLAG_ISDEMO
        se_string_vram_buffer(str_demo, nametable_address_A(1,3));
        se_one_vram_buffer(FLAG_ISDEMO, nametable_address_A(6,3));
    #endif

    se_turn_on_rendering();
    se_fade_palette_to(1,4);

    // for some reason, the compiler
    // absolutely REFUSES to put an
    // lda #0 before running this, so
    // do it manually here (if song is 0)
    //__asm__("lda #0"); 
    //if(!famistudio_song_speed) {
    se_music_play(saved_menu_theme);
    //}

    
    //interrupt_scroll = 0;
    while(1){
        se_wait_vsync();
        //scroll(0,0);
        se_clear_sprites();

        interrupt_scroll += phys_speed[1];
        se_irq_table[15] = hi(interrupt_scroll);

        scroll_bank += (phys_speed[1] >> 3);
        if(hi(scroll_bank) >= loaded_bg_width) hi(scroll_bank) = 0;
        se_irq_table[4] = (hi(scroll_bank)+0x10);
        


        if((se_frame_count & 0x3f) < 5) {

            if(se_frame_count & 0x1) menu_color -= 1;
            else menu_color += 1;

            if(menu_color >= 0x1d) menu_color = 0x11;
            if(menu_color == 0x10) menu_color = 0x1c;

            se_set_palette_color(0, menu_color);
            se_set_palette_color(2, menu_color-0x10);
            se_set_palette_color(9, menu_color-0x10);
            se_set_palette_color(10, menu_color);
        }



        
        
        if((selection >= 2) && (selection < 5)){
            se_draw_metasprite(
                lo(mspr_select_pos[selection]),
                hi(mspr_select_pos[selection]),
                mspr_selectbox
            );
        } else {
            se_draw_metasprite(
                lo(mspr_select_pos[selection]),
                hi(mspr_select_pos[selection]),
                mspr_selectarrow
            );
        }

        // the fact that i can use a metasprite for
        // EVERYTHING on the menu is bloody brilliant
        se_draw_metasprite(1,0,mspr_title); // one to the right
                                    // so i can put sprites at
                                    // x = 128
        
        if(joypad1.press_right) selection++;
        if(joypad1.press_left) selection--;

        if(joypad1.press_down) selection += (menu_button_count>>1);
        if(joypad1.press_up) selection -= (menu_button_count>>1);

        if(selection >= ((u8)menu_button_count)) {
            selection -= menu_button_count;
        }
        if(selection < 0) {
            selection += menu_button_count;
        }

        if(joypad1.press_b) {
            break;
        }

        if(joypad1.press_a) {
            switch(selection){
                case 0: // play
                    gamestate = 0x11;
                    break;
                /*case 1: // community
                    break;
                case 2: // settings
                    break;*/
                case 3: // music
                    gamestate = 0x14;
                    break;
                /*case 4: // help
                    break;
                case 5: // icon kit
                    break;*/
                default:
                    se_sfx_play(sfx_gold01,0);
            }
            se_fade_palette_to(4,0);
            break;
        }
        //if(player1_pressed & PAD_SELECT) {
        //    gamestate = 0xf0;
        //    break;
        //}
    }
    __asm__("sei");
    
}



