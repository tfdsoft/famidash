
#define SPR_BANK_00 0x1C

//attempt to comment
#define CUBE_MODE 				0X00
#define SHIP_MODE 				0X01
#define BALL_MODE 				0X02
#define UFO_MODE 				0X03
#define ROBOT_MODE 				0X04
#define BLUE_ORB 				0X05
#define PINK_ORB 				0X06
#define COIN 					0X07
#define GRAVITY_DOWN_PORTAL 			0X08
#define GRAVITY_UP_PORTAL 			0X09
#define YELLOW_PAD_DOWN 			0X0A
#define YELLOW_ORB 				0X0B
#define YELLOW_PAD_UP	 			0X0C
#define GRAVITY_PAD_DOWN 			0X0D
#define GRAVITY_PAD_UP	 			0X0E
#define LEVEL_END_TRIGGER 			0X0F
#define GRAVITY_DOWN_UPWARDS_PORTAL 		0X10
#define GRAVITY_DOWN_DOWNWARDS_PORTAL 		0X11
#define GRAVITY_UP_UPWARDS_PORTAL 		0X12
#define GRAVITY_UP_DOWNWARDS_PORTAL 		0X13
#define SPEED_05_PORTAL		 		0X14
#define SPEED_10_PORTAL		 		0X15
#define SPEED_20_PORTAL		 		0X16
#define SPIDER_MODE		 		0X17
#define GRAVITY_UP_INVISIBLE_PORTAL		0XFB
#define GRAVITY_DOWN_INVISIBLE_PORTAL		0XFC
#define GRAVITY_PAD_DOWN_INVISIBLE		0XFD
#define GRAVITY_PAD_UP_INVISIBLE		0XFE
#define NOSPRITE				0XFF

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
    else if (type == CUBE_MODE) return 0x2f; // portal
    else if (type == SHIP_MODE) return 0x2f; // portal
    else if (type == BALL_MODE) return 0x2f; // portal
    else if (type == UFO_MODE) return 0x2f; // portal
    else if (type == ROBOT_MODE) return 0x2f; // portal
    else if (type == SPIDER_MODE) return 0x2f; // portal
    else if (type == BLUE_ORB) return 0x0f; // blue orb
    else if (type == PINK_ORB) return 0x0f; // pink jump orb
    else if (type == COIN) return 0x17; // COIN

    else if (type == GRAVITY_DOWN_PORTAL) return 0x2F;
    else if (type == GRAVITY_UP_PORTAL) return 0x2F;

    else if (type == SPEED_05_PORTAL) return 0x1f; // 0.5 speed portal
    else if (type == SPEED_10_PORTAL) return 0x1f; // 0.5 speed portal
    else if (type == SPEED_20_PORTAL) return 0x1f; // 0.5 speed portal
    // pads
    else if (type == YELLOW_PAD_DOWN) return 0x07; // yellow jump pad
    else if (type == YELLOW_ORB) return 0x0f; // yellow jump orb
    else if (type == YELLOW_PAD_UP) return 0x07; // yellow jump pad Upside Down
    else if (type == GRAVITY_PAD_DOWN) return 0x04; // Gravity Pad
    else if (type == GRAVITY_PAD_UP) return 0x04; // Gravity Pad Upside Down

    // triggers
    else if (type == LEVEL_END_TRIGGER) {			//end trigger on load
        gameState = 0x03; 
        pal_fade_to(4,0); 	    
    }	   

    else if (type == GRAVITY_DOWN_UPWARDS_PORTAL || type == GRAVITY_DOWN_DOWNWARDS_PORTAL || type == GRAVITY_UP_UPWARDS_PORTAL || type == GRAVITY_UP_DOWNWARDS_PORTAL || type == GRAVITY_UP_INVISIBLE_PORTAL || type == GRAVITY_DOWN_INVISIBLE_PORTAL ) return 0x1f;
    
    return 0;
}



#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")
void sprite_collide_lookup(){
    // portals
    if (tmp4 == NOSPRITE) { }
    
    else if (tmp4 <= 4) { gamemode = tmp4; robotjumptime = 0; }			//game mode portals
    else if (tmp4 == SPIDER_MODE) gamemode = tmp4; 			//game mode portals
    
    
    else if (tmp4 == YELLOW_ORB) {		//yellow orb
	if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
		if (cube_data == 2) {					
			cube_data = 0x00;
			if (gravity) player.vel_y = JUMP_VEL^0xFFFF; else player.vel_y = JUMP_VEL;
		}
	}
	else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
		if (pad_new & PAD_A) {	
			cube_data = 0x00;
			if (gravity) player.vel_y = JUMP_VEL^0xFFFF; else player.vel_y = JUMP_VEL;
		}
	}
    }
    else if (tmp4 == COIN) {					//COIN
	    coins++;
//	    famistudio_sfx_play(sfx_click, 0);			//test sfx
	activesprites_type[index] = 0xFF;		//make COIN disappear here
    }

    else if (tmp4 == BLUE_ORB)  {				//blue orb
	if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE || gamemode == SPIDER_MODE) {
		if (cube_data == 2) {			
			cube_data = 0x00;
			gravity ^= 0x01;
			if (!gravity) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
			else player.vel_y = PAD_HEIGHT_PINK;
		}
	}
	else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
		if (pad_new & PAD_A) {
			cube_data = 0x00;
			gravity ^= 0x01;
			if (!gravity) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
			else player.vel_y = PAD_HEIGHT_PINK;
		}
	} 
    }

	else if (tmp4 == SPEED_05_PORTAL) speed = 1;
	else if (tmp4 == SPEED_10_PORTAL) speed = 0;
	else if (tmp4 == SPEED_20_PORTAL) speed = 2;
	

    else if (tmp4 == PINK_ORB) {
	if (cube_data == 2) {		//nest it so that the next else-if for tmp4 doesn't trigger
		cube_data = 0x00;
		if (gravity) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
		else player.vel_y = PAD_HEIGHT_PINK;
	}
    }
    else if (tmp4 == GRAVITY_DOWN_PORTAL || tmp4 == GRAVITY_DOWN_UPWARDS_PORTAL || tmp4 == GRAVITY_DOWN_DOWNWARDS_PORTAL || tmp4 == GRAVITY_DOWN_INVISIBLE_PORTAL) { 
	if (gravity) {
	    gravity = 0; 
	 //   if (player.vel_y > -0x0200) player.vel_y = -0x0200; 
	   // else 
		   if (player.vel_y < -0x0400) player.vel_y = -0x0400; 
	}
    }
    else if (tmp4 == GRAVITY_UP_PORTAL || tmp4 == GRAVITY_UP_UPWARDS_PORTAL || tmp4 == GRAVITY_UP_DOWNWARDS_PORTAL || tmp4 == GRAVITY_UP_INVISIBLE_PORTAL ) { 
	if (!gravity) {
	    gravity = 1; 
	    //if (player.vel_y < 0x0200) player.vel_y = 0x0200; 
//	    else
		    if (player.vel_y > 0x0400) player.vel_y = 0x0400; 
	}
    }

    else if (tmp4 == YELLOW_PAD_DOWN || tmp4 == YELLOW_PAD_UP) {				//yellow pads
        if (gravity) player.vel_y = PAD_HEIGHT_YELLOW^0xFFFF;
        else player.vel_y = PAD_HEIGHT_YELLOW;
    } 
    else if (tmp4 == GRAVITY_PAD_DOWN) {			//gravity pads bottom
	    if (!gravity) { 
		gravity = 0x01;				//flip gravity
		if (player.vel_y == 0) player.vel_y = PAD_HEIGHT_BLUE^0xFFFF;	
		else player.vel_y = 0;		//launch up right away OMGZ IT WORKS
	    }
    }
    else if (tmp4 == GRAVITY_PAD_UP) {			//gravity pads top
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
    
    else if (tmp4 == GRAVITY_PAD_DOWN_INVISIBLE) {			//gravity pads bottom
	    if (!gravity) { 
		gravity = 0x01;				//flip gravity
		if (player.vel_y == 0) player.vel_y = PAD_HEIGHT_PINK^0xFFFF;
		else player.vel_y = 0;		//launch up right away OMGZ IT WORKS
	    }
    }
    else if (tmp4 == GRAVITY_PAD_UP_INVISIBLE) {			//gravity pads top
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

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
