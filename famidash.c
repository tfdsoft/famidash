/*	example code for cc65, for NES
 *  Scrolling Right with metatile system
 *	, basic platformer
 *	using neslib
 *	Doug Fraker 2018
 */	
 

#include "include.h"


	
	
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
	
	
	gamemode = 0x01;
	cube_rotate = 0x80;
	while (1){
		// infinite loop
		ppu_wait_nmi(); // wait till beginning of the frame

		pad1 = pad_poll(0); // read the first controller
		pad1_new = get_pad_new(0);


		if (gamemode & 0x01) cube_movement();
		else if (gamemode & 0x02) ship_movement();

		check_spr_objects(); // see which objects are on screen
			
		sprite_collisions();

		bg_coll_death();
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
	
	
	/*
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
	*/

	// copy the room to the collision map
	// the second one should auto-load with the scrolling code
	memcpy (c_map, Rooms[0], 240);

	sprite_obj_init();
}








void draw_sprites(void){
	// clear all sprites from sprite buffer
	oam_clear();
	
	


	// OBJECTS
	for(index = 0; index < MAX_OBJ; ++index){
		index2 = obj_type[index];
		if(index2 & 0x30) continue;
		temp_y = obj_y[index];
		if(temp_y == TURN_OFF) continue;
        if(!obj_active[index]) continue;
        temp_x = obj_x[index];
		if(temp_x > 0xf0) continue;
		if(temp_y < 0xf0) {
			oam_meta_spr(temp_x, temp_y, Portals[index2]);
		}
	}





	// CUBE
	// draw the cube last so that the cube appears behind portals
	temp_x = high_byte(Cube.x);
	if(temp_x > 0xfc) temp_x = 1;
	if(temp_x == 0) temp_x = 1;
	if (gamemode & 0x01) {
		oam_meta_spr(temp_x, high_byte(Cube.y)-1, CUBE[high_byte(cube_rotate)]);
		
		
		if (gravity) cube_rotate -= CUBE_GRAVITY;
		else cube_rotate += CUBE_GRAVITY;
			
		if (cube_rotate > 0x05FF) cube_rotate -= 0x0600;
		if (cube_rotate < 0x0000) cube_rotate += 0x0600;
	}
	if (gamemode & 0x02){
		oam_meta_spr(temp_x, high_byte(Cube.y)-1, SHIP[high_byte(cube_rotate)]);


		cube_rotate = 0x047F - Cube.vel_y;
	}	
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
	scroll_x = 0;
	load_room();
	Cube.x = 0x0000;
	Cube.y = 0xb400;
	gravity = 0x00;
	gamemode = 0x01;
	Cube.vel_x = 0;
	Cube.vel_y = 0;
	cube_data = 0;
	music_stop();
	ppu_on_all();
	music_play(song);
}







char bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist
	temp5 = Generic.x + scroll_x + (Generic.width >> 1);
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height>> 1);
	if(bg_collision_sub() & COL_DEATH) cube_data = 0x01;

	if(cube_data & 0x01) { reset_level(); sfx_play(SFX_DEATH, 0);}
}









char bg_coll_orbs() {
	if (cube_data & CUBE_ORBJUMP && pad1 & PAD_A) {

		// top left corner
		temp5 = Generic.x + scroll_x;
		temp_x = (char)temp5; // low byte
    	temp_room = temp5 >> 8; // high byte
		temp_y = Generic.y;
		if(bg_collision_sub() & COL_YEL_ORB) return 1;


		// top right corner
		temp5 = Generic.x + scroll_x + Generic.width;
		temp_x = (char)temp5; // low byte
    	temp_room = temp5 >> 8; // high byte
		if(bg_collision_sub() & COL_YEL_ORB) return 1;


		// bottom left corner
		temp5 = Generic.x + scroll_x;
		temp_x = (char)temp5; // low byte
    	temp_room = temp5 >> 8; // high byte
		temp_y = Generic.y + Generic.height;
		if(bg_collision_sub() & COL_YEL_ORB) return 1;


		// bottom right corner
		temp5 = Generic.x + scroll_x + Generic.width;
		temp_x = (char)temp5; // low byte
    	temp_room = temp5 >> 8; // high byte
		if(bg_collision_sub() & COL_YEL_ORB) return 1;

		return 0;
	}
	if (pad1_new & PAD_A) cube_data = CUBE_ORBJUMP;
}

void orbjump() {
	bg_coll_orbs();
	if (bg_coll_orbs() && cube_data & CUBE_ORBJUMP) {
		if (gravity) Cube.vel_y = JUMP_VEL^0xFFFF;
		else Cube.vel_y = JUMP_VEL;
		cube_data = 0x00;
	}
}


char bg_coll_pads() {

	// left
	temp5 = Generic.x + scroll_x;
	++temp5; ++temp5;
	temp_x = (char)temp5; // low byte
	temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height>>1);
	if(bg_collision_sub() & COL_YEL_PAD) return 1;

	// right
	temp5 = Generic.x + scroll_x + Generic.width;
	--temp5; --temp5;
	temp_x = (char)temp5; // low byte
	temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height>>1);
	if(bg_collision_sub() & COL_YEL_PAD) return 1;
	
	return 0;
}


void padjump() {
	bg_coll_pads();
	if (bg_coll_pads()) {
		if (gravity) Cube.vel_y = YEL_PAD_HEIGHT^0xFFFF;
		else Cube.vel_y = YEL_PAD_HEIGHT;
	}
}





void update_colors() {

	
}


void check_spr_objects(void){
	Generic2.x = high_byte(Cube.x);
	// mark each object "active" if they are, and get the screen x
	
	for(index = 0; index < MAX_OBJ; ++index){
		obj_active[index] = 0; //default to zero
		if(obj_y[index] != TURN_OFF){
			high_byte(temp5) = obj_room[index];
			low_byte(temp5) = obj_actual_x[index];
			obj_active[index] = get_position();
			obj_x[index] = temp_x; // screen x coords
		}
	}
}



char get_position(void){
	// is it in range ? return 1 if yes
	
	temp5 -= scroll_x;
	temp_x = temp5 & 0xff;
	if(high_byte(temp5)) return 0;
	return 1;
}




void sprite_collisions(void){

	Generic.x = high_byte(Cube.x);
	Generic.y = high_byte(Cube.y);
	Generic.width = CUBE_WIDTH;
	Generic.height = CUBE_HEIGHT;
	
	for(index = 0; index < MAX_OBJ; ++index){
		if(obj_active[index]){

			Generic2.width = PORTAL_WIDTH;

			if(obj_type[index] & 0x30) Generic2.height = TRIGGER_HEIGHT;
			else Generic2.height = PORTAL_HEIGHT;

			Generic2.x = obj_x[index];
			Generic2.y = obj_y[index];

			if(check_collision(&Generic, &Generic2)){
				switch (obj_type[index]) {
				default:
					break;
					
				case PORTAL_GAMEMODE_CUBE:
					gamemode = 0x01;
					break;

				case PORTAL_GAMEMODE_SHIP:
					gamemode = 0x02;
					break;

				case PORTAL_GRAVITY_DOWN:
					gravity = 0x00;
					break;

				case PORTAL_GRAVITY_UP:
					gravity = 0x01;
					break;

				// COLOR TRIGGERS (this is very lengthy)
				// Background Color Triggers
				// dark
				case TRIG_BG_DR:
					pal_col(COL_BG, 0x06);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DO:
					pal_col(COL_BG, 0x07);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DY:
					pal_col(COL_BG, 0x08);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DG0:
					pal_col(COL_BG, 0x09);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DG1: 
					pal_col(COL_BG, 0x0A);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DT: 
					pal_col(COL_BG, 0x0B);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DB0: 
					pal_col(COL_BG, 0x0C);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DB1:
					pal_col(COL_BG, 0x01);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DI: 
					pal_col(COL_BG, 0x02);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DV: 
					pal_col(COL_BG, 0x03);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DP: 
					pal_col(COL_BG, 0x04);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DM: 
					pal_col(COL_BG, 0x05);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_DGRAY: 
					pal_col(COL_BG, 0x00);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_BLACK: 
					pal_col(COL_BG, 0x0F);
					pal_col(COL_BG_TILES, 0x0F);
					obj_y[index] = TURN_OFF;
					break;
				// mid
				case TRIG_BG_R:
					pal_col(COL_BG, 0x16);
					pal_col(COL_BG_TILES, 0x06);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_O:
					pal_col(COL_BG, 0x17);
					pal_col(COL_BG_TILES, 0x07);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_Y:
					pal_col(COL_BG, 0x18);
					pal_col(COL_BG_TILES, 0x08);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_G0:
					pal_col(COL_BG, 0x19);
					pal_col(COL_BG_TILES, 0x09);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_G1: 
					pal_col(COL_BG, 0x1A);
					pal_col(COL_BG_TILES, 0x0A);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_T: 
					pal_col(COL_BG, 0x1B);
					pal_col(COL_BG_TILES, 0x0B);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_B0: 
					pal_col(COL_BG, 0x1C);
					pal_col(COL_BG_TILES, 0x0C);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_B1:
					pal_col(COL_BG, 0x11);
					pal_col(COL_BG_TILES, 0x01);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_I: 
					pal_col(COL_BG, 0x12);
					pal_col(COL_BG_TILES, 0x02);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_V: 
					pal_col(COL_BG, 0x13);
					pal_col(COL_BG_TILES, 0x03);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_P: 
					pal_col(COL_BG, 0x14);
					pal_col(COL_BG_TILES, 0x04);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_M: 
					pal_col(COL_BG, 0x15);
					pal_col(COL_BG_TILES, 0x05);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_GRAY: 
					pal_col(COL_BG, 0x10);
					pal_col(COL_BG_TILES, 0x00);
					obj_y[index] = TURN_OFF;
					break;

				// light
				case TRIG_BG_LR:
					pal_col(COL_BG, 0x26);
					pal_col(COL_BG_TILES, 0x06);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LO:
					pal_col(COL_BG, 0x27);
					pal_col(COL_BG_TILES, 0x07);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LY:
					pal_col(COL_BG, 0x28);
					pal_col(COL_BG_TILES, 0x08);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LG0:
					pal_col(COL_BG, 0x29);
					pal_col(COL_BG_TILES, 0x09);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LG1: 
					pal_col(COL_BG, 0x2A);
					pal_col(COL_BG_TILES, 0x0A);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LT: 
					pal_col(COL_BG, 0x2B);
					pal_col(COL_BG_TILES, 0x0B);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LB0: 
					pal_col(COL_BG, 0x2C);
					pal_col(COL_BG_TILES, 0x0C);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LB1:
					pal_col(COL_BG, 0x21);
					pal_col(COL_BG_TILES, 0x01);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LI: 
					pal_col(COL_BG, 0x22);
					pal_col(COL_BG_TILES, 0x02);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LV: 
					pal_col(COL_BG, 0x23);
					pal_col(COL_BG_TILES, 0x03);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LP: 
					pal_col(COL_BG, 0x24);
					pal_col(COL_BG_TILES, 0x04);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_LM: 
					pal_col(COL_BG, 0x25);
					pal_col(COL_BG_TILES, 0x05);
					obj_y[index] = TURN_OFF;
					break;
				case TRIG_BG_WHITE: 
					pal_col(COL_BG, 0x30);
					pal_col(COL_BG_TILES, 0x00);
					obj_y[index] = TURN_OFF;
					break;
				//if(obj_type[index] == OBJ_END);
				}
			}
		}
	}
}

void sprite_obj_init(void){

	pointer = obj_list[level];
	for(index = 0,index2 = 0;index < MAX_OBJ; ++index){
		
		obj_x[index] = 0;

		temp1 = pointer[index2]; // get a byte of data
		obj_y[index] = temp1;
		
		if(temp1 == TURN_OFF) break;

		++index2;
		
		obj_active[index] = 0;

		
		temp1 = pointer[index2]; // get a byte of data
		obj_room[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; // get a byte of data
		obj_actual_x[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; // get a byte of data
		obj_type[index] = temp1;
		
		++index2;
	}
	
	for(++index;index < MAX_OBJ; ++index){
		obj_y[index] = TURN_OFF;
	}
}
