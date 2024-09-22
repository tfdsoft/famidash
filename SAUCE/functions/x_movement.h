#pragma code-name(push, "XCD_BANK_02")
#pragma data-name(push, "XCD_BANK_02")
#pragma rodata-name(push, "XCD_BANK_02")

const unsigned short speed_table[] = {
	CUBE_SPEED_X1, CUBE_SPEED_X05, CUBE_SPEED_X2, CUBE_SPEED_X3, CUBE_SPEED_X4
};


void x_movement(){
    // handle x

	old_x = currplayer_x;
	
	currplayer_vel_x = speed_table[speed & 0x7F];
	
	if (dashing[currplayer] == 4 || dashing[currplayer] == 5) {	
		if (currplayer_y < 0x0600 && scroll_y == min_scroll_y){
			idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
		}
		return; 
	}

	if (gamemode == 0x06) { // wave
		if (mini) {
			Generic.width = MINI_WAVE_WIDTH;
			Generic.height = MINI_WAVE_HEIGHT;
		} else {
			Generic.width = WAVE_WIDTH;
			Generic.height = WAVE_HEIGHT;
		}
	} else {
		if (!mini) {
			Generic.width = CUBE_WIDTH;
			Generic.height = CUBE_HEIGHT;
		} else {
			Generic.width = MINI_CUBE_WIDTH;
			Generic.height = MINI_CUBE_HEIGHT;
		}   
	}

	Generic.x = high_byte(currplayer_x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(currplayer_y);

	if (!(options & platformer)) {
		if ((pad[0] & PAD_LEFT) && !twoplayer && DEBUG_MODE) currplayer_x -= currplayer_vel_x;
		else currplayer_x += currplayer_vel_x;
	} else {
		// leave the col calls first so it executes and checks against spike collision
		tmp7 = bg_coll_R();
		tmp8 = bg_coll_L();

		if (!tmp7 && (pad[currplayer] & PAD_RIGHT)) currplayer_x += currplayer_vel_x;
		else if (!tmp8 && pad[currplayer] & PAD_LEFT && currplayer_x > 0x1000) currplayer_x -= currplayer_vel_x;
		else currplayer_vel_x = 0;


		if (tmp7 && (pad[currplayer] & PAD_RIGHT)) {
			tmp7 = high_byte(currplayer_x) + low_word(scroll_x);
			high_byte(currplayer_x) -= ((tmp7 + 4) & 0x07) - 4 + mini; // if mini put it a pixel left-er
		}
		else if (tmp8 && (pad[currplayer] & PAD_LEFT)) {
			tmp8 = high_byte(currplayer_x) + low_word(scroll_x);
			high_byte(currplayer_x) -= ((tmp8 + 4) & 0x07) - 4;
		} 
	}

	if(currplayer_x > 0xf000) { // too far, don't wrap around
        if(old_x >= 0xf000){
            currplayer_x = 0xf000; // max right
        } else{
            currplayer_x = 0x0000; // max left
        }
		currplayer_vel_x = 0;
	} 


	if (currplayer_y < 0x0600 && scroll_y <= min_scroll_y){
		idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
	}
	

	else if (!(pad[controllingplayer] & PAD_A)) idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
}




void __fastcall__ mouse_clear(void) {
  p_left = false;
  p_right = false;
  mouse.left.press = false;
  mouse.left.click = false;
  mouse.right.press = false;
  mouse.right.click = false;
}

void __fastcall__ mouse_init(uint8_t x, uint8_t y) {
  mouse_clear();
  mouse.x = x;
  mouse.y = y;
}

void __fastcall__ mouse_update(void) {
  // Latch the data by turning the latch on and off
  POKE(LATCH_PORT, 1);
  POKE(LATCH_PORT, 0);

  // Wait 2 CPU cycles
  __asm__("nop");

  // Read 32 bits from the mouse into the report array using unrolled loops
  // NOTE: Each read should take at least 14 CPU cycles and there should be
  //       at least 28 CPU cycles between the 2nd and 3rd bytes.

  // Get the first byte
  #define LOOP_CODE(_i) \
    __asm__("LDA %w", MOUSE_PORT); \
    __asm__("LSR A"); \
    __asm__("ROL %v+0", report); \
    __asm__("NOP"); \
    __asm__("NOP");
  LOOP(8);
  #undef LOOP_CODE

  // Get the second byte
  #define LOOP_CODE(_i) \
    __asm__("LDA %w", MOUSE_PORT); \
    __asm__("LSR A"); \
    __asm__("ROL %v+1", report); \
    __asm__("NOP"); \
    __asm__("NOP");
  LOOP(8);
  #undef LOOP_CODE

  // Wait a few more CPU cycles for
  // Hyperkin mouse compatibility
  __asm__("nop"); __asm__("nop");

  // Set mouse connection state
  if ((report[1] & 0x0F) != 0x01) {
    mouse.connected = false;
    return; // - - - - - - - - - - - - - - - - - - -
  }

  // Get the third byte
  #define LOOP_CODE(_i) \
    __asm__("LDA %w", MOUSE_PORT); \
    __asm__("LSR A"); \
    __asm__("ROL %v+2", report); \
    __asm__("NOP"); \
    __asm__("NOP");
  LOOP(8);
  #undef LOOP_CODE

  // Get the fourth byte
  #define LOOP_CODE(_i) \
    __asm__("LDA %w", MOUSE_PORT); \
    __asm__("LSR A"); \
    __asm__("ROL %v+3", report); \
    __asm__("NOP"); \
    __asm__("NOP");
  LOOP(8);
  #undef LOOP_CODE

  // Extract button states
  mouse.left.press = (report[1] >> 6) & 0x01;
  mouse.right.press = (report[1] >> 7) & 0x01;

  // Set left-click state
  mouse.left.click = (mouse.left.press && !p_left);
  p_left = mouse.left.press;

  // Set right-click state
  mouse.right.click = (mouse.right.press && !p_right);
  p_right = mouse.right.press;

  // Convert vertical displacement to two's complement
  y_velocity = report[2] & 0x7F;
  if (report[2] & 0x80) {
    y_velocity = -y_velocity;
  }

  // Convert horizontal displacement to two's complement
  x_velocity = report[3] & 0x7F;
  if (report[3] & 0x80) {
    x_velocity = -x_velocity;
  }

  // At this point, x_velocity and y_velocity contain the displacement values
  // mouse.left and mouse.right contain the button states (1 = pressed, 0 = not pressed)

  // Update the cursor X position
  if (x_velocity) {
	  mouse_timer = 120;
    new_x = mouse.x + x_velocity;
    if (x_velocity > 0) {
      mouse.x = new_x < MAX_X && new_x > mouse.x ? new_x : MAX_X;
    }
    else {
      mouse.x = new_x > MIN_X && new_x < mouse.x ? new_x : MIN_X;
    }
  }

  // Update the cursor Y position
  if (y_velocity) {
	  mouse_timer = 120;
    new_y = mouse.y + y_velocity;
    if (y_velocity > 0) {
      mouse.y = new_y < MAX_Y && new_y > mouse.y ? new_y : MAX_Y;
    }
    else {
      mouse.y = new_y > MIN_Y && new_y < mouse.y ? new_y : MIN_Y;
    }
  }

  // Set mouse connection state
  mouse.connected = true;
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
