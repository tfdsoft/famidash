
#define SPR_BANK_00 0x1C

//attempt to comment
#define cubemode 				0x00
#define shipmode 				0x01
#define ballmode 				0x02
#define ufomode 				0x03
#define unusedmode 				0x04
#define blue_orb 				0x05
#define pink_orb 				0x06
#define coin 					0x07
#define gravity_down_portal 			0x08
#define gravity_up_portal 			0x09
#define yellow_pad_down 			0x0A
#define yellow_orb 				0x0B
#define yellow_pad_up	 			0x0C
#define gravity_pad_down 			0x0D
#define gravity_pad_up	 			0x0E
#define level_end_Trigger 			0x0F
#define gravity_down_upwards_portal 		0x10
#define gravity_down_downwards_portal 		0x11
#define gravity_up_upwards_portal 		0x12
#define gravity_up_downwards_portal 		0x13
#define speed_05_portal		 		0x14
#define speed_10_portal		 		0x15
#define speed_20_portal		 		0x16
#define gravity_up_invisible_portal		0xFB
#define gravity_down_invisible_portal		0xFC
#define gravity_pad_down_invisible		0xFD
#define gravity_pad_up_invisible		0xFE
#define nosprite				0xFF

extern void load_next_sprite(void);

extern void check_spr_objects(void);

void init_sprites(void){
    mmc3_set_prg_bank_1(SPR_BANK_00);
    sprite_data = (unsigned char *) sprite_list[level];

    spr_index = 0;
    while (spr_index < max_loaded_sprites){
        if (sprite_data[spr_index<<3] == TURN_OFF) break;
        load_next_sprite();
    }
}

__fastcall__ char sprite_height_lookup(unsigned char type){

    if (type == 0xFF) { return 0; }		//disappearing sprite

    else if (type == 0xFD || type == 0xFE) return 0x07;	//invisible blue pads
    else if (type == 0xFC || type == 0xFB) return 0x0F;	//horizontal down gravity portal

    else if ((type >= 0x80) && (type < 0xF0)){                //COLOR TRIGGERS ON LOADING    was type & 0x30 and tmp2 = (type & 0x3f)-10 for spots 0x10-0x70
		tmp2 = (type & 0x3F);                        
		if (type >= 0xC0){
		    pal_col(6, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(5, 0x0f); 
			activesprites_type[index] = 0xFF; 
		    } else { 
			pal_col(5, (tmp2-0x10)); 
			activesprites_type[index] = 0xFF; 
		    }
		} else {
		    pal_col(0, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(1, 0x0f); 
			activesprites_type[index] = 0xFF; 
		    } else { 
			pal_col(1, (tmp2-0x10)); 
			activesprites_type[index] = 0xFF;
		    }
		}
		return 0x00;
    }

    // portals
    else if (type == cubemode) return 0x2f; // portal
    else if (type == shipmode) return 0x2f; // portal
    else if (type == ballmode) return 0x2f; // portal
    else if (type == ufomode) return 0x2f; // portal
    else if (type == 0x04) return 0x2f; // unused portal
    else if (type == blue_orb) return 0x0f; // blue orb
    else if (type == pink_orb) return 0x0f; // pink jump orb
    else if (type == coin) return 0x17; // coin

    else if (type == gravity_down_portal) return 0x2F;
    else if (type == gravity_up_portal) return 0x2F;

    else if (type == speed_05_portal) return 0x1f; // 0.5 speed portal
    else if (type == speed_10_portal) return 0x1f; // 0.5 speed portal
    else if (type == speed_20_portal) return 0x1f; // 0.5 speed portal
    // pads
    else if (type == yellow_pad_down) return 0x07; // yellow jump pad
    else if (type == yellow_orb) return 0x0f; // yellow jump orb
    else if (type == yellow_pad_up) return 0x07; // yellow jump pad Upside Down
    else if (type == gravity_pad_down) return 0x04; // Gravity Pad
    else if (type == gravity_pad_up) return 0x04; // Gravity Pad Upside Down

    // triggers
    else if (type == level_end_Trigger) {			//end trigger on load
        gameState = 0x03; 
        pal_fade_to(4,0); 	    
    }	   

    else if (type == gravity_down_upwards_portal || type == gravity_down_downwards_portal || type == gravity_up_upwards_portal || type == gravity_up_downwards_portal || type == gravity_up_invisible_portal || type == gravity_down_invisible_portal ) return 0x1f;
    
    return 0;
}



void sprite_collide_lookup(){
    // portals
    if (tmp4 == nosprite) { }
    
    else if (tmp4 <= 3) gamemode = tmp4;			//game mode portals
    else if (tmp4 == yellow_orb) {		//yellow orb
	if (gamemode == cubemode || gamemode == ballmode) {
		if (cube_data == 2) {					
			cube_data = 0x00;
			if (gravity) player.vel_y = JUMP_VEL^0xFFFF; else player.vel_y = JUMP_VEL;
		}
	}
	else if (gamemode == shipmode || gamemode == ufomode) {
		if (pad_new & PAD_A) {	
			cube_data = 0x00;
			if (gravity) player.vel_y = JUMP_VEL^0xFFFF; else player.vel_y = JUMP_VEL;
		}
	}
    }
    else if (tmp4 == coin) {					//coin
	    coins++;
//	    famistudio_sfx_play(sfx_click, 0);			//test sfx
	activesprites_type[index] = 0xFF;		//make coin disappear here
    }

    else if (tmp4 == blue_orb)  {				//blue orb
	if (gamemode == cubemode || gamemode == ballmode) {
		if (cube_data == 2) {			
			cube_data = 0x00;
			gravity ^= 0x01;
			if (!gravity) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
			else player.vel_y = PAD_HEIGHT_PINK;
		}
	}
	else if (gamemode == shipmode || gamemode == ufomode) {
		if (pad_new & PAD_A) {
			cube_data = 0x00;
			gravity ^= 0x01;
			if (!gravity) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
			else player.vel_y = PAD_HEIGHT_PINK;
		}
	} 
    }

	else if (tmp4 == speed_05_portal) speed = 1;
	else if (tmp4 == speed_10_portal) speed = 0;
	else if (tmp4 == speed_20_portal) speed = 2;
	

    else if (tmp4 == pink_orb) {
	if (cube_data == 2) {		//nest it so that the next else-if for tmp4 doesn't trigger
		cube_data = 0x00;
		if (gravity) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
		else player.vel_y = PAD_HEIGHT_PINK;
	}
    }
    else if (tmp4 == gravity_down_portal || tmp4 == gravity_down_upwards_portal || tmp4 == gravity_down_downwards_portal || tmp4 == gravity_down_invisible_portal) { 
	if (gravity) {
	    gravity = 0; 
	    if (player.vel_y > -0x0200) player.vel_y = -0x0200; 
	    else if (player.vel_y > -0x0400) player.vel_y = -0x0400; 
	}
    }
    else if (tmp4 == gravity_up_portal || tmp4 == gravity_up_upwards_portal || tmp4 == gravity_up_downwards_portal || tmp4 == gravity_up_invisible_portal ) { 
	if (!gravity) {
	    gravity = 1; 
	    if (player.vel_y < 0x0200) player.vel_y = 0x0200; 
	    else if (player.vel_y > 0x0400) player.vel_y = 0x0400; 
	}
    }

    else if (tmp4 == yellow_pad_down || tmp4 == yellow_pad_up) {				//yellow pads
        if (gravity) player.vel_y = PAD_HEIGHT_YELLOW^0xFFFF;
        else player.vel_y = PAD_HEIGHT_YELLOW;
    } 
    else if (tmp4 == gravity_pad_down) {			//gravity pads bottom
	    if (!gravity) { 
		gravity = 0x01;				//flip gravity
		if (player.vel_y == 0) player.vel_y = PAD_HEIGHT_BLUE^0xFFFF;	
		else player.vel_y = 0;		//launch up right away OMGZ IT WORKS
	    }
    }
    else if (tmp4 == gravity_pad_up) {			//gravity pads top
	    if (gravity) { 
		gravity = 0x00;				//flip gravity
		if (player.vel_y == 0) player.vel_y = PAD_HEIGHT_BLUE;	
		else player.vel_y = -(player.vel_y);		//launch up right away OMGZ IT WORKS
	    }
    }
//    else if (tmp4 == 0x0F) {
//        gameState = 0x03; 
//        pal_fade_to(4,0); 
//    }
    
    else if (tmp4 == gravity_pad_down_invisible) {			//gravity pads bottom
	    if (!gravity) { 
		gravity = 0x01;				//flip gravity
		if (player.vel_y == 0) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
		else player.vel_y = 0;		//launch up right away OMGZ IT WORKS
	    }
    }
    else if (tmp4 == gravity_pad_up_invisible) {			//gravity pads top
	    if (gravity) { 
		gravity = 0x00;				//flip gravity
		if (player.vel_y == 0) player.vel_y = PAD_HEIGHT_PINK;
		else player.vel_y = 0;		//launch up right away OMGZ IT WORKS
	    }
    }    
}

void sprite_collide(){

    Generic.x = high_byte(player.x);
    Generic.y = high_byte(player.y);

	if (!mini) {
    Generic.width = CUBE_WIDTH;
    Generic.height = CUBE_HEIGHT;
	}
	
	else {
    Generic.width = MINI_CUBE_WIDTH;
    Generic.height = MINI_CUBE_HEIGHT;
	}    
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
                sprite_collide_lookup();
            }
        }
    }
}