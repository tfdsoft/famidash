/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
// void set_tile_banks();
void __fastcall__ movement();
void __fastcall__ movement2();
void mouse_and_cursor();
extern uint8_t famistudio_song_speed;
const uint8_t BG_Table[]={
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x1A,
	0x1B,
	0x1C
};

const uint8_t G_Table[]={
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x2A,
	0x2B,
	0x2C
};



void x_minus_15();
void y_minus_15();
void x_plus_15();
void y_plus_15();
void runthecolls();
void set_player_banks();
void gameboy_check();

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;

void decrement_was_on_slope() {

}


void state_game(){

}

void runthecolls() {

}				


void mouse_and_cursor() {
	if (mouse.connected) {
		if (mouse.left || mouse.right || mouse.x != prev_mouse_x || mouse.y != prev_mouse_y) mouse_timer = 120;
		if (mouse.right_press) joypad1.press_b = true;
		if (mouse.right) joypad1.b = true;
		if (!(kandoframecnt & 0x07)) mouseframe += mouseframe == 7 ? -7 : 1;
		if (kandoframecnt > 0xFC) kandoframecnt = 0;
		if (gameState != 2) { if (mouse_timer) oam_spr(mouse.x, mouse.y - 1, (0xA1 + (2*mouseframe)), 2); }

		prev_mouse_x = mouse.x;
		prev_mouse_y = mouse.y;
	}
}
