extern volatile unsigned char VRAM_UPDATE;
#pragma zpsym ("VRAM_UPDATE")

#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")

void state_lvldone() {
#define current_state tmp2
#define sprite_0_y tmp3
#define delay_spr_0 tmp4
#define delay_timer tmpptr1
#define top_scroll scroll_x
    ppu_off();

	delay_spr_0 = 0x20;

	current_state = 0;

	// Set palettes back to natural colors since we aren't fading back in
	pal_bright(4);

    pal_bg((char *)paletteMenu);
    pal_spr((char *)paletteMenu);

	mmc3_set_8kb_chr(20);

	// Make an a nametable for the chain
    vram_adr(NAMETABLE_A);
	vram_fill(0xfe, 0x3c0);
	vram_fill(0x00, 0x3f);
	// vertical increment: draw the chains
	vram_inc(1);
    vram_adr(NTADR_A(5, 0));
	vram_fill(0xae, 30);
    vram_adr(NTADR_A(26, 0));
	vram_fill(0xae, 30);

	// Make an empty nametable for the scroll split
    vram_adr(NAMETABLE_B);
	vram_inc(0);
	vram_fill(0xfe, 0x3c0);
	vram_fill(0x00, 0x3f);
    
	// Copy the level done screen to the bot left and right nametable
    vram_adr(NAMETABLE_C);
    vram_unrle(leveldone);

	// Change the text attributes for the press to return
    vram_adr(0x2be1);
	vram_fill(0xff, 0x6);

    vram_adr(NAMETABLE_D);
    vram_unrle(leveldone);

#include "../defines/endlevel_charmap.h"
	multi_vram_buffer_horz((const char*)menutext3,sizeof(menutext3)-1,NTADR_C(6, 16));
	multi_vram_buffer_horz((const char*)menutext4,sizeof(menutext4)-1,NTADR_C(8, 18));
	multi_vram_buffer_horz((const char*)attemptstext,sizeof(attemptstext)-1,NTADR_C(7, 19));
	
	tmp1 = 0;
	tmpptr1 = NULL;

	TOTALCOINSONES = 0;
	TOTALCOINSTENS = 0;
	TOTALATTEMPTSHUNDREDS = 0;
	TOTALATTEMPTSTHOUSANDS = 0;
	
	TOTALCOINSTEMP = attempts;
	
	while (TOTALCOINSTEMP > 9) {
		TOTALCOINSTENS++;
		TOTALCOINSTEMP = TOTALCOINSTEMP - 10;
		if (TOTALCOINSTENS == 10) {
			TOTALCOINSTENS = 0;
			TOTALATTEMPTSHUNDREDS++;
		}
		if (TOTALATTEMPTSHUNDREDS == 10) {
			TOTALATTEMPTSHUNDREDS = 0;
			TOTALATTEMPTSTHOUSANDS++;
		}
	}
	TOTALCOINSONES = TOTALCOINSTEMP;

	if (TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xd0+TOTALATTEMPTSTHOUSANDS, NTADR_C(16,19));
	if (TOTALATTEMPTSHUNDREDS || TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xd0+TOTALATTEMPTSHUNDREDS, NTADR_C(17,19));
	if (TOTALATTEMPTSHUNDREDS || TOTALCOINSTENS || TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xd0+TOTALCOINSTENS, NTADR_C(18,19));
	one_vram_buffer(0xd0+TOTALCOINSONES, NTADR_C(19,19));	
	
	LEVELCOMPLETE[level] = 1;
	
	if (coins & COIN_1) coin1_obtained[level] = 1;
	if (coins & COIN_2) coin2_obtained[level] = 1;
	if (coins & COIN_3) coin3_obtained[level] = 1;

	
	if (!coins) {
		tmp1 = sizeof(coins0) - 1;
		tmpptr1 = (unsigned char*)coins0;
	} else if ((coins & 7) == 7) {
		tmp1 = sizeof(coins3) - 1;
		tmpptr1 = (unsigned char*)coins3;
	} else if (((coins & COIN_1) && (coins & COIN_2)) || ((coins & COIN_2) && (coins & COIN_3)) || ((coins & COIN_1) && (coins & COIN_3))) {
		tmp1 = sizeof(coins2) - 1;
		tmpptr1 = (unsigned char*)coins2;
	} else if (coins & COIN_1 || coins & COIN_2 || coins & COIN_3) {
		tmp1 = sizeof(coins1) - 1;
		tmpptr1 = (unsigned char*)coins1;
	}
	if (tmp1) multi_vram_buffer_horz((const char*)tmpptr1,tmp1,NTADR_C(17,18));
	flush_vram_update2();

	// Set the start of the scroll to the top nametable
	// so we can scroll it down (so the screen comes up)
    top_scroll = 0x00;

	// setup sprite zero at the very bottom of the screen for now
	sprite_0_y = 0xee;
	POKE(0x200, sprite_0_y);
	POKE(0x201, 0x02); // Use the second tile in the BG side which is pure black
	POKE(0x202, 0x02); // second palette
	POKE(0x203, 0);

    set_scroll_x(0);
    set_scroll_y(top_scroll);

//	one_vram_buffer(0xD0+coins, NTADR_A(12,9));

    ppu_on_all();



	sfx_play(sfx_level_complete, 0);

	while (1) {
		// Rather hacky, but when doing sprite zero at the bottom of the screen we DON'T 
		// want to skip a frame, so we re-enable NMI and then if NMI happens during the frame
		// we don't have a lag frame by skipping it.
		if (VRAM_UPDATE == 1) {
        	ppu_wait_nmi();
		}
		// force re-enable NMI every frame.
		VRAM_UPDATE = 1;

		music_update();

		// wait for sprite zero hit
		if (current_state > 0 && current_state < 3) {
			xy_split(0x100, scroll_y);
		}

 		// read the first controller
		pad[0] = pad_poll(0);
		pad_new[0] = get_pad_new(0);
		
		// Move the sprite zero hit to the new location
		POKE(0x200, sprite_0_y);

		switch (current_state) {
		case 0:
			// Scroll the screen top bar up a bit
			top_scroll += 2;
			set_scroll_y(top_scroll);
			if (top_scroll >= 31) {
				scroll_y = 256 + 208 - 1;
				current_state = 1;
			}
			break;
		case 1:
			// keep scrolling up, but have sprite zero follow now
			sprite_0_y -= 2;
			top_scroll += 2;
			set_scroll_y(top_scroll);
			// Play the level complete noise
			// if (top_scroll == 115) {
			// }
			if (top_scroll > 151) {
				current_state = 2;
			}
			break;
		case 2:
			// keep scrolling up, but change the scroll split Y
			// so it starts to "unravel"
			sprite_0_y -= 2;
			top_scroll += 2;
			scroll_y -= 4;
			set_scroll_y(top_scroll);
			if (top_scroll == 240) {
				set_scroll_x(0);
				set_scroll_y(0x100);
				current_state = 3;
			}
			break;
		case 3:
			// Draw the level stat text
			current_state = 4;

			break;
		case 4:

			if (pad_new[0] & PAD_START){
				// pal_bg((char *)paletteDefault);
				// pal_spr((char *)paletteDefaultSP);
				sfx_play(sfx_exit_level, 0);
				music_update();
				gameState = 1;
				menuselection = 0;
				return;
			}
			break;
		}
	}
#undef current_state
#undef sprite_0_y
#undef delay_spr_0
#undef delay_timer
#undef top_scroll
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
