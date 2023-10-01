/*	example code for cc65, for NES
 *  Scrolling Right with metatile system
 *	, basic platformer
 *	using neslib
 *	Doug Fraker 2018
 */	
 

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" // holds our metasprite data
#include "famidash.h"



	
	
void main (void) {
	
	ppu_off(); // screen off
	ppu_mask(0x00);
	// load the palettes
	pal_bg(palette_bg);
	pal_spr(palette_sp);

	// use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

	set_vram_buffer(); // do at least once
	
	load_room();

	song = 0;
	music_play(song);

	ppu_on_all(); // turn on screen
	
	

	cube_rotate = 0;
	while (1){
		// infinite loop
		ppu_wait_nmi(); // wait till beginning of the frame
		bg_coll_death();
		
		

		pad1 = pad_poll(0); // read the first controller
		pad1_new = get_pad_new(0);
		movement();
		set_scroll_x(scroll_x);
		set_scroll_y(scroll_y);
		draw_screen_R();
		draw_sprites();
		gray_line();
	}
}













void load_room(void){
	set_data_pointer(Rooms[0]);
	set_mt_pointer(metatiles1);
	for(y=0; ;y+=0x20){
		for(x=0; ;x+=0x20){
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (x == 0xe0) break;
		}
		if (y == 0xe0) break;
	}
	
	
	
	// a little bit in the next room
	set_data_pointer(Rooms[1]);
	for(y=0; ;y+=0x20){
		x = 0;
		address = get_ppu_addr(1, x, y);
		index = (y & 0xf0);
		buffer_4_mt(address, index); // ppu_address, index to the data
		flush_vram_update2();
		if (y == 0xe0) break;
	}
	

	// copy the room to the collision map
	// the second one should auto-load with the scrolling code
	memcpy (c_map, Rooms[0], 240);
}





void draw_sprites(void){
	// clear all sprites from sprite buffer
	oam_clear();
	
	temp_x = high_byte(Cube.x);
	if(temp_x > 0xfc) temp_x = 1;
	if(temp_x == 0) temp_x = 1;
	// draw 1 CUBE
	cube_rotate += 0x68;
	if (high_byte(cube_rotate) > 0x05) cube_rotate = 0;
	oam_meta_spr(temp_x, high_byte(Cube.y), CUBE[high_byte(cube_rotate)]);
}
	


	
	
void movement(void){
	
// handle x

	old_x = Cube.x;
	
	Cube.vel_x = CUBE_SPEED;
	/*
	if(pad1 & PAD_LEFT){
		direction = LEFT;
		
        if(Cube.vel_x >= DECEL){
            Cube.vel_x -= DECEL;
        }
        else if(Cube.vel_x > 0){
            Cube.vel_x = 0;
        }
		else {
			Cube.vel_x -= ACCEL;
			if(Cube.vel_x < -MAX_SPEED) Cube.vel_x = -MAX_SPEED;
		}
	}
	else if (pad1 & PAD_RIGHT){
		
		direction = RIGHT;

		if(Cube.vel_x <= DECEL){
            Cube.vel_x += DECEL;
        }
        else if(Cube.vel_x < 0){
            Cube.vel_x = 0;
        }
		else {
			Cube.vel_x += ACCEL;
			if(Cube.vel_x >= MAX_SPEED) Cube.vel_x = MAX_SPEED;
		}
	}
	else { // nothing pressed
		if(Cube.vel_x >= ACCEL) Cube.vel_x -= ACCEL;
		else if(Cube.vel_x < -ACCEL) Cube.vel_x += ACCEL;
		else Cube.vel_x = 0;
	}
	*/
	Cube.x += Cube.vel_x;
	
	if(Cube.x > 0xf000) { // too far, don't wrap around
        
        if(old_x >= 0x8000){
            Cube.x = 0xf000; // max right
        }
        else{
            Cube.x = 0x0000; // max left
        }
        
		Cube.vel_x = 0;
	} 
	


	Generic.x = high_byte(Cube.x); // this is much faster than passing a pointer to Cube
	Generic.y = high_byte(Cube.y);
	Generic.width = CUBE_WIDTH;
	Generic.height = CUBE_HEIGHT;
	
    if(Cube.vel_x < 0){
        if(bg_coll_L() ){ // check collision left
            high_byte(Cube.x) = high_byte(Cube.x) - eject_L;
            Cube.vel_x = 0;
            if(Cube.x > 0xf000) {
                // no wrap around
                Cube.x = 0xf000;
            }
        }
    }
    else if(Cube.vel_x > 0){
        if(bg_coll_R() ){ // check collision right
            high_byte(Cube.x) = high_byte(Cube.x) - eject_R;
            Cube.vel_x = 0;
            if(Cube.x > 0xf000) {
                // no wrap around
                Cube.x = 0x0000;
            }
        }
    }
    // skip collision if vel = 0
    
	
// handle y

// gravity

	// Cube.vel_y is signed
	if(Cube.vel_y < 0x400){
		Cube.vel_y += GRAVITY;
}
	else{
		Cube.vel_y = 0x400; // consistent
	}
	Cube.y += Cube.vel_y;
	
	Generic.x = high_byte(Cube.x);
	Generic.y = high_byte(Cube.y);
	
    if(Cube.vel_y > 0){
        if(bg_coll_D()){ // check collision below
            high_byte(Cube.y) = high_byte(Cube.y) - eject_D;
            Cube.y &= 0xff00;
            if(Cube.vel_y > 0) {
                Cube.vel_y = 0;
            }

        }
    }
    else if(Cube.vel_y < 0){
        if(bg_coll_U() ){ // check collision above
            high_byte(Cube.y) = high_byte(Cube.y) - eject_U;
            Cube.vel_y = 0;
        }
    }
    
	// check collision down a little lower than CUBE
	Generic.y = high_byte(Cube.y); // the rest should be the same
	
	if(bg_coll_D2()) {
        if(pad1 & PAD_A) {
			Cube.vel_y = JUMP_VEL; // JUMP
		}
		cube_rotate = 0x0000;
	}
	
	// do we need to load a new collision map? (scrolled into a new room)
	if((scroll_x & 0xff) < 4){
		if(!map_loaded){
			new_cmap();
			map_loaded = 1; // only do once
		}
		
	}
	else{
		map_loaded = 0;
	}
	
// scroll
	temp5 = Cube.x;
	if (Cube.x > MAX_RIGHT){
		temp1 = (Cube.x - MAX_RIGHT) >> 8;
        if (temp1 > 3) temp1 = 3; // max scroll change
		scroll_x += temp1;
		high_byte(Cube.x) = high_byte(Cube.x) - temp1;
	}

	if(scroll_x >= MAX_SCROLL) {
		scroll_x = MAX_SCROLL; // stop scrolling right, end of level

		reset_level();


		/*	
		Cube.x = temp5; // but allow the x position to go all the way right
		if(high_byte(Cube.x) >= 0xf1) {
			Cube.x = 0xf100;
		}
		*/
	}
}	



char bg_coll_L(void){
    // check 2 points on the left side
    temp5 = Generic.x + scroll_x;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    
    eject_L = temp_x | 0xf0;
    temp_y = Generic.y + 2;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp_y = Generic.y + Generic.height;
    temp_y -= 2;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_R(void){
    // check 2 points on the right side
    temp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    

	temp_y = Generic.y + (Generic.height>>1); // this checks for a thing called *middle point collision* and kills you if you're inside a wall
	if(bg_collision_sub() & COL_ALL) crashed = 1; return 1;
	
    return 0;
}

char bg_coll_U(void){
    // check 2 points on the top side
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    
    temp_y = Generic.y;
    eject_U = temp_y & 0xf0;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_D(void){

    // check 2 points on the bottom side
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    
    temp_y = Generic.y + Generic.height;
    
    if((temp_y & 0x0f) > 3) return 0; // bug fix
    // so we don't snap to those platforms
    // don't fall too fast, or might miss it.
    
    eject_D = (temp_y + 1) & 0x0f;
    
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    
    if(bg_collision_sub() & COL_ALL) return 1; 

    return 0; 
}

char bg_coll_D2(void){
    // check 2 points on the bottom side
    // a little lower, for jumping
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    
    temp_y = Generic.y + Generic.height;
    temp_y += 2;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
    
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}




char bg_collision_sub(void){
    if(temp_y >= 0xf0) return 0;
    
	coordinates = (temp_x >> 4) + (temp_y & 0xf0);
    // we just need 4 bits each from x and y
	
	map = temp_room&1; // high byte
	if(!map){
		collision = c_map[coordinates];
	}
	else{
		collision = c_map2[coordinates];
	}
	
    return is_solid[collision];
}



void draw_screen_R(void){
	// scrolling to the right, draw metatiles as we go
	pseudo_scroll_x = scroll_x + 0xF8;
	
	temp1 = pseudo_scroll_x >> 8;
	
	set_data_pointer(Rooms[temp1]);
	nt = temp1 & 1;
	x = pseudo_scroll_x & 0xff;
	
	switch(scroll_count){
		case 0:
			address = get_ppu_addr(nt, x, 0);
			index = 0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0x20);
			index = 0x20 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		case 1:
			address = get_ppu_addr(nt, x, 0x40);
			index = 0x40 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0x60);
			index = 0x60 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		case 2:
			address = get_ppu_addr(nt, x, 0x80);
			index = 0x80 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0xa0);
			index = 0xa0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		case 3:
			address = get_ppu_addr(nt, x, 0xc0);
			index = 0xc0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0xe0);
			index = 0xe0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
	}


	++scroll_count;
	scroll_count &= 3; //mask off top bits, keep it 0-3
}



void new_cmap(void){
	// copy a new collision map to one of the 2 c_map arrays
	room = ((scroll_x >> 8) +1); //high byte = room, one to the right
	
	map = room & 1; //even or odd?
	if(!map){
		memcpy (c_map, Rooms[room], 240);
	}
	else{
		memcpy (c_map2, Rooms[room], 240);
	}
}



void reset_level(void) {

	ppu_off(); // reset the level when you get to this point, and change this later
	load_room();
	scroll_x = 0;
	Cube.x = 0x0000;
	Cube.y = 0xb400;
	Cube.vel_x = 0;
	Cube.vel_y = 0;
	crashed = 0;
	music_stop();
	ppu_on_all();
	music_play(song);
}



char bg_coll_death(void) {


	// top left corner
	temp5 = Generic.x + scroll_x + (Generic.width/2);
	--temp5;--temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height/2);
	--temp_y;--temp_y;
	if(bg_collision_sub() & COL_DEATH) crashed = 1;




	// top right corner
	temp5 = Generic.x + scroll_x + (Generic.width/2);
	++temp5;++temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height/2);
	--temp_y;--temp_y;
	if(bg_collision_sub() & COL_DEATH) crashed = 1;




	// bottom left corner
	temp5 = Generic.x + scroll_x + (Generic.width/2);
	--temp5;--temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height/2);
	++temp_y;++temp_y;
	if(bg_collision_sub() & COL_DEATH) crashed = 1;




	// bottom right corner
	temp5 = Generic.x + scroll_x + (Generic.width/2);
	++temp5;++temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height/2);
	++temp_y;++temp_y;
	if(bg_collision_sub() & COL_DEATH) crashed = 1;


	if(crashed & 0x01) reset_level();
}