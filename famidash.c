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
	cube_rotate = 0;
	while (1){
		// infinite loop
		ppu_wait_nmi(); // wait till beginning of the frame

		pad1 = pad_poll(0); // read the first controller
		pad1_new = get_pad_new(0);


		if (gamemode & 0x00) cube_movement();
		else if (gamemode & 0x01) ship_movement();



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
}








void draw_sprites(void){
	// clear all sprites from sprite buffer
	oam_clear();
	
	temp_x = high_byte(Cube.x);
	if(temp_x > 0xfc) temp_x = 1;
	if(temp_x == 0) temp_x = 1;
	// draw 1 CUBE
	if (gamemode & 0x00) {
		cube_rotate += 0x70;
		if (high_byte(cube_rotate) > 0x05) cube_rotate = 0;
		oam_meta_spr(temp_x, high_byte(Cube.y)-1, CUBE[high_byte(cube_rotate)]);
	}
	if (gamemode & 0x01){
		cube_rotate = 0x0480 - Cube.vel_y;
		oam_meta_spr(temp_x, high_byte(Cube.y)-1, SHIP[high_byte(cube_rotate)]);
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
	Cube.vel_x = 0;
	Cube.vel_y = 0;
	cube_data = 0;
	music_stop();
	ppu_on_all();
	music_play(song);
}







char bg_coll_death(void) {


	// top left corner
	temp5 = Generic.x + scroll_x + (Generic.width >> 1);
	--temp5;--temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height>> 1);
	--temp_y;--temp_y;
	if(bg_collision_sub() & COL_DEATH) cube_data = 0x01;


	// top right corner
	temp5 = Generic.x + scroll_x + (Generic.width >> 1);
	++temp5;++temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	if(bg_collision_sub() & COL_DEATH) cube_data = 0x01;


	// bottom left corner
	temp5 = Generic.x + scroll_x + (Generic.width >> 1);
	--temp5;--temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	temp_y = Generic.y + (Generic.height >> 1);
	++temp_y;++temp_y;
	if(bg_collision_sub() & COL_DEATH) cube_data = 0x01;


	// bottom right corner
	temp5 = Generic.x + scroll_x + (Generic.width >> 1);
	++temp5;++temp5;
	temp_x = (char)temp5; // low byte
    temp_room = temp5 >> 8; // high byte
	if(bg_collision_sub() & COL_DEATH) cube_data = 0x01;


	if(cube_data & 0x01) reset_level();
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
		Cube.vel_y = JUMP_VEL;
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
		Cube.vel_y = YEL_PAD_HEIGHT;
	}

}





void update_colors() {

	

}