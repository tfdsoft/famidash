#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")
#pragma code-name(push, "XCD_BANK_00")

extern void load_next_sprite(uint8_t slot);
extern void check_spr_objects(void);
void init_sprites();

void spider_up_wait();
void spider_down_wait();
extern char bg_coll_U();
extern char bg_coll_D();
void 	retrofireballclear();
void settrailstuff();

const unsigned char OUTLINES[]={
		0x30,
		0x11,
		0x12,
		0x13,
		0x14,
		0x15,
		0x16,
		0x27,
		0x28,
		0x29,
		0x2A,
		0x2B,
		0x2C,
		0x21,
		0x17,
		0x0F
};

#define OUTL    0xFC
#define COLR    0xFD
#define DECO    0xFE
#ifdef FLAG_KANDO_FUN_STUFF
#define	KNDO	0xFF
#else
#define KNDO	0x00
#endif
#define SPBH    0xFF

uint8_t sprite_heights[]={
	0x30,	0x30,	0x30,	0x30,	0x30,	0x10,	0x10,	SPBH,	// 00 - 07
	0x30,	0x30,	0x03,	0x10,	0x03,	0x03,	0x03,	SPBH,	// 08 - 0F
	0x0B,	0x0B,	0x0B,	0x0B,	0x20,	0x20,	0x20,	0x30,	// 10 - 17
	0x30,	0x30,	SPBH,	SPBH,	SPBH,	SPBH,	SPBH,	0x10,	// 18 - 1F
	0x20,	0x20,	0x30,	0x30,	0x30,	0x03,	0x03,	0x10,	// 20 - 27
	0x10,	0x10,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	// 28 - 2F
	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	// 30 - 37
	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	// 38 - 3F
	DECO,	DECO,	DECO,	DECO,	0x10,	0x10,	0x10,	DECO,	// 40 - 47
	DECO,	DECO,	DECO,	0x30,	0x10,	0x10,	0x30,	SPBH,	// 48 - 4F
	0x10,	0x10,	0x03,	0x03,	0x10,	0x10,	0x03,	0x03,	// 50 - 57
	0x30,	0x10,	SPBH,	0x10,	0x10,	0x10,	0x10,	0x30,	// 58 - 5F
	0x30,	0x30,	0x30,	0x30,	0x30,	0x02,	0x10,	SPBH,	// 60 - 67
	0x10,	SPBH,	0x30,	0x30,	0x30,	0x00,	0x00,	0x00,	// 68 - 6F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 70 - 77
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 78 - 7F
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// 80 - 87
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	0x00,	COLR,	// 88 - 8F
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// 90 - 97
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	0x00,	0x00,	// 98 - 9F
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// A0 - A7
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	0x00,	0x00,	// A8 - AF
	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	// B0 - B7
	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	// B8 - BF
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// C0 - C7
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	0x00,	COLR,	// C8 - CF
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// D0 - D7
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	SPBH,	KNDO,	// D8 - DF
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// E0 - E7
	COLR,	COLR,	COLR,	COLR,	COLR,	0x10,	KNDO,	KNDO,	// E8 - EF
	SPBH,	SPBH,	SPBH,	SPBH,	SPBH,	SPBH,	0x10,	0x10,	// F0 - F7
	0x10,	0x10,	0x10,	0x10,	0x10,	0x03,	0x03,	0x00,	// F8 - FF
};

uint8_t sprite_widths[]={
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 00 - 07
	0x07,	0x07,	0x0F,	0x10,	0x0F,	0x0F,	0x0F,	0x10,	// 08 - 0F
	0x2E,	0x2E,	0x2E,	0x2E,	0x10,	0x10,	0x10,	0x10,	// 10 - 17
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 18 - 1F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x0F,	0x0F,	0x10,	// 20 - 27
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 28 - 2F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 30 - 37
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 38 - 3F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 40 - 47
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 48 - 4F
	0x10,	0x10,	0x0F,	0x0F,	0x10,	0x10,	0x0F,	0x0F,	// 50 - 57
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 58 - 5F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x0E,	0x30,	0x30,	// 60 - 67
	0x30,	0x30,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 68 - 6F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 70 - 77
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 78 - 7F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 80 - 87
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 88 - 8F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 90 - 97
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 98 - 9F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// A0 - A7
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// A8 - AF
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// B0 - B7
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// B8 - BF
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// C0 - C7
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// C8 - CF
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// D0 - D7
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// D8 - DF
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// E0 - E7
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// E8 - EF
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// F0 - F7
	0x10,	0x10,	0x10,	0x10,	0x10,	0x0E,	0x10,	0x10,	// F8 - FF
};

// Offset goes for x to the rigth and for y down, for moving it in the other direction, put a negative value (0x80-0xff) 

uint8_t sprite_x_offset[]={
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 00 - 07
	0x06,	0x06,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 08 - 0F
	0x02,	0x02,	0x02,	0x02,	0x00,	0x00,	0x00,	0x00,	// 10 - 17
	0x08,	0x08,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 18 - 1F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 20 - 27
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 28 - 2F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 30 - 37
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 38 - 3F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 40 - 47
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 48 - 4F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 50 - 57
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 58 - 5F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 60 - 67
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 68 - 6F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 70 - 77
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 78 - 7F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 80 - 87
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 88 - 8F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 90 - 97
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 98 - 9F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// A0 - A7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// A8 - AF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// B0 - B7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// B8 - BF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// C0 - C7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// C8 - CF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// D0 - D7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// D8 - DF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// E0 - E7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// E8 - EF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// F0 - F7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// F8 - FF
};

uint8_t sprite_y_offset[]={
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 00 - 07
	0x00,	0x00,	0x05,	0x00,	0x00,	0x05,	0x00,	0x00,	// 08 - 0F
	0x00,	0x06,	0x00,	0x06,	0x00,	0x00,	0x00,	0x00,	// 10 - 17
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 18 - 1F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x05,	0x00,	0x00,	// 20 - 27
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 28 - 2F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 30 - 37
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 38 - 3F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 40 - 47
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 48 - 4F
	0x00,	0x00,	0x05,	0x00,	0x00,	0x00,	0x05,	0x00,	// 50 - 57
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 58 - 5F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 60 - 67
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 68 - 6F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 70 - 77
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 78 - 7F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 80 - 87
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 88 - 8F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 90 - 97
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 98 - 9F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// A0 - A7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// A8 - AF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// B0 - B7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// B8 - BF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// C0 - C7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// C8 - CF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// D0 - D7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// D8 - DF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// E0 - E7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// E8 - EF
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// F0 - F7
	0x00,	0x00,	0x00,	0x00,	0x00,	0x05,	0x00,	0x00,	// F8 - FF
};

void animate_coin_1();

void animate_coin_2();

void animate_coin_3();



char sprite_load_special_behavior(){

	#define killSprite_return0 activesprites_type[index] = 0xFF; return 0

	#define type tmp4
/*
	//	color fading code
	if ((type >= 0x80) && (type < 0xF0)){                //COLOR TRIGGERS ON LOADING    was type & 0x30 and tmp2 = (type & 0x3f)-10 for spots 0x10-0x70
		if (!discomode) tmp2 = (type & 0x3F);                        
		else { 
			return 0x00;
		}
		tmp3 = oneShadeDarker(tmp2);
		if (type >= 0xC0) {
			original_gnd_palette_idx_0 = 5;
			original_gnd_palette_idx_1 = 6;
			original_gnd_palette_color_0 = PAL_BUF[5];
			original_gnd_palette_color_1 = PAL_BUF[6];
			pal_col(5, tmp3);
			pal_col(6, tmp2);
			lastgcolortype = type;
			gnd_palette_transition_timer = current_transition_timer_length;
		} else {
			original_bg_palette_idx_0 = 0;
			original_bg_palette_idx_1 = 1;
			original_bg_palette_idx_2 = 9;
			original_bg_palette_color_0 = PAL_BUF[0];
			original_bg_palette_color_1 = PAL_BUF[1];
			original_bg_palette_color_2 = PAL_BUF[9];
			pal_col(0, tmp2);
			pal_col(1, tmp3);
			pal_col(9, tmp3);
			lastbgcolortype = type;
			bg_palette_transition_timer = current_transition_timer_length;
		}
		pal_set_update();
		activesprites_type[index] = 0xFF; 
		return 0x00;
	}
	else if (type == 0xFA) {
				current_transition_timer_length = ((0xb0 - low_byte(Generic2.y)) >> 3) & 0x1e; // force it to be even
				activesprites_type[index] = 0xFF;
	}
	*/

	switch(type) {
		#ifdef FLAG_KANDO_FUN_STUFF	
			case DEATH_CHANCE: 
				if ((newrand() & 63) == (newrand() & 63)) {
					idx8_store(cube_data, currplayer, cube_data[currplayer] | 1);
				}
				triggers_hit[0]++;
				if (triggers_hit[0] == 10) { triggers_hit[0] = 0; triggers_hit[1]++; }
				if (triggers_hit[1] == 10) { triggers_hit[1] = 0; triggers_hit[2]++; }
				triggers++;
				killSprite_return0;
			case MASK_SPRITES_ON:
				disco_sprites = 1;
				killSprite_return0;
			case MASK_SPRITES_OFF:
				disco_sprites = 0;
				killSprite_return0;
		#endif
		case X_SCROLL_SETTING:
			if (!cam_seesaw) {
				target_x_scroll_stop = (activesprites_realy[index] & 0xF0) << 8;
				killSprite_return0;
			}
			return 0;

		case SLOWMODE_ON:
			slowmode = 1;
			killSprite_return0;
		case SLOWMODE_OFF:
			slowmode = 0;
			killSprite_return0;

		case FORCED_TRAILS_ON:
			forced_trails = 1;
			killSprite_return0;
		case FORCED_TRAILS_OFF:
		case PLAYER_TRAILS_OFF:
			forced_trails = 0;
			killSprite_return0;
		case PLAYER_TRAILS_ON:
			forced_trails = 2;
			killSprite_return0;

		case TELEPORT_SQUARE_EXIT:
			teleport_output = activesprites_realy[index];
			return 0x0f;

		case TELEPORT_PORTAL_DOWNWARDS_EXIT:
		case TELEPORT_PORTAL_UPWARDS_EXIT:		
		case TELEPORT_PORTAL_EXIT:
			teleport_output = activesprites_realy[index] + 0x10;
			return 0x2f;

		case COIN1:
			if (coin1_obtained[level]) {
				activesprites_type[index] = COINGOTTEN1;
			}
		case COINGOTTEN1:
            if (coin1_timer) {
                animate_coin_1();
            }      
			return 0x17;

		case COIN2:
			if (coin2_obtained[level]) {
				activesprites_type[index] = COINGOTTEN2;
			}

		case COINGOTTEN2:
	        if (coin2_timer) {
                animate_coin_2();
            }
			return 0x17;

		case COIN3:
			if (coin3_obtained[level]) {
				activesprites_type[index] = COINGOTTEN3;
			}

		case COINGOTTEN3:
	        if (coin3_timer) {
                animate_coin_3();
            }
			return 0x17; 

		case LEVEL_END_TRIGGER:
			gameState = 0x03; 
			
	}
	return 0;

	#undef type

//	#undef killSprite_return0
}

void animate_coin_1() {    
    idx8_store(activesprites_y_lo, index, activesprites_y_lo[index] - high_byte(coin1_speed));
    coin1_speed -= 0x0040;
    coin1_timer++;

    if (coin1_timer == 40) {
        activesprites_type[index] = 0xFF;
        animating = 0;
    }	 
}


void animate_coin_2() {
    idx8_store(activesprites_y_lo, index, activesprites_y_lo[index] - high_byte(coin2_speed));
    coin2_speed -= 0x0040;
    coin2_timer++;

    if (coin2_timer == 40) {
        activesprites_type[index] = 0xFF;
        animating = 0;
    }	 
}


void animate_coin_3() {
    idx8_store(activesprites_y_lo, index, activesprites_y_lo[index] - high_byte(coin3_speed));
    coin3_speed -= 0x0040;
    coin3_timer++;

    if (coin3_timer == 40) {
        activesprites_type[index] = 0xFF;
        animating = 0;
    }	 
}

#define yellow_orb 0x00 << 3
#define yellow_pad 0x01 << 3
#define pink_orb   0x02 << 3
#define pink_pad   0x03 << 3
#define red_orb    0x04 << 3
#define ylw_bigger 0x05 << 3
#define black_orb  0x06 << 3
#define ylw_smaller 0x07 << 3
#define red_pad 0x08 << 3

const short heights[] = {
//	cube    ship    ball     ufo    robot   spider  wave   swing
	0x590,  0x590,  0x410,  0x350,  0x590,  0x440,  0x000, 0x000, // yellow orb
	0x7C0,  0x450,  0x4B0,  0x320,  0x8B0,  0x500,  0x000, 0x000, // yellow pad
	0x3D0,  0x590,  0x330,  0x590,  0x450,  0x350,  0x000, 0x000, // pink orb
	0x510,  0x510,  0x38A,  0x510,  0x510,  0x510,  0x000, 0x000, // pink pad
	0x750,  0x700,  0x550,  0x750,  0x750,  0x500,  0x000, 0x000, // red orb
	0x590,  0x590,  0x5D0,  0x590,  0x590,  0x590,  0x000, 0x000, // yellow orb bigger
       -0x990, -0x990, -0x970, -0x990, -0x990, -0x990,  0x000, 0x000, // black orb
	0x540,  0x540,  0x472,  0x4B0,  0x770,  0x4B0,  0x000, 0x000, // yellow orb smaller
	0x950,  0x3200,  0x6B0,  0x370,  0xA50,  0x4B0,  0x000, 0x000, // red pad		
};

const short mini_heights[] = {
//      cube    ship    ball     ufo    robot   spider  wave   swing
	0x4D0,  0x4D0,  0x410,  0x3D0,  0x530,  0x4D0,  0x000, 0x000, // yellow orb
	0x6C0,  0x470,  0x4F0,  0x3A0,  0x730,  0x400,  0x000, 0x310, // yellow pad
	0x350,  0x4D0,  0x500,  0x4D0,  0x350,  0x4D0,  0x000, 0x000, // pink orb
	0x3F0,  0x1E0,  0x390,  0x1B0,  0x350,  0x350,  0x000, 0x1F0, // pink pad
	0x750,  0x700,  0x600,  0x750,  0x850,  0x500,  0x000, 0x000, // red orb
	0x590,  0x590,  0x560,  0x590,  0x590,  0x590,  0x000, 0x000, // yellow orb bigger
       -0x990, -0x990, -0x970, -0x990, -0x990, -0x990,  0x000, 0x000, // black orb
	0x540,  0x540,  0x472,  0x4B0,  0x770,  0x4B0,  0x000, 0x000, // yellow orb smaller
	0x830,  0x6C0,  0x5B0,  0x550,  0x8D0,  0x550,  0x000, 0x3D0, // red pad	
};

#define table_offset tmp3
#define collided tmp4

// Load the player velocity from the height table
static unsigned int __fastcall__ sprite_gamemode_y_adjust() {
	if (!retro_mode) __A__ = (gamemode | table_offset) << 1;
	else if (retro_mode && gamemode == 4) __A__ = (0 | table_offset) << 1;
	else __A__ = (gamemode | table_offset) << 1;
	__asm__("tay");
	if (currplayer_mini) {
		__AX__ = (__asm__ ("lda %v,y", mini_heights), __asm__ ("ldx %v+1,y", mini_heights),__AX__);
	} else {
		__AX__ = (__asm__ ("lda %v,y", heights),__asm__ ("ldx %v+1,y", heights),__AX__);
	}
	// Use y here for the conditional, otherwise the compiler overwrites A
	__asm__("ldy %v", currplayer_gravity); 
	do_if_zero({__AX__ ^= 0xffff; __AX__ += 1;});
	return __AX__;
}

static void sprite_gamemode_main() {
	if (controllingplayer->a || controllingplayer->up) {	
		if (gamemode == BALL_MODE) kandotemp2[currplayer] = 1;
		if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
			settrailstuff();

			switch (collided) {
			case BLUE_ORB:
				if (gamemode == 3 || gamemode == 5) {
					if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
				}
				else currplayer_gravity ^= 0x01;
				if (gamemode != BALL_MODE) {
					currplayer_vel_y = (!currplayer_gravity) ? PAD_HEIGHT_BLUE^0xFFFF : PAD_HEIGHT_BLUE;
				} else {
					currplayer_vel_y = (!currplayer_gravity) ? ORB_BALL_HEIGHT_BLUE^0xFFFF : ORB_BALL_HEIGHT_BLUE;
				}
				break;
			case GREEN_ORB:
				if (gamemode == 3 || gamemode == 5) {
					if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
				}
				else currplayer_gravity ^= 0x01;
				currplayer_vel_y = sprite_gamemode_y_adjust();
				break;
			case DASH_GRAVITY_ORB:
				if (!dashing[currplayer]) { 
					if (gamemode == 3 || gamemode == 5) {
						if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
					}
					else currplayer_gravity ^= 0x01;
				}
				//intentional leak
			case DASH_ORB:
				currplayer_vel_y = 0;
				dashing[currplayer] = 1;
				break;
			case DASH_GRAVITY_ORB_45DEG_UP:
				if (!dashing[currplayer]) {
					if (gamemode == 3 || gamemode == 5) {
						if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
					}
					else currplayer_gravity ^= 0x01;
				}				
				//intentional leak
			case DASH_ORB_45DEG_UP:
				currplayer_vel_y = -currplayer_vel_x;
				dashing[currplayer] = 2;
				break;
			case DASH_GRAVITY_ORB_45DEG_DOWN:
				if (!dashing[currplayer]) {
					if (gamemode == 3 || gamemode == 5) {
						if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
					}
					else currplayer_gravity ^= 0x01;
				}				
				//intentional leak
			case DASH_ORB_45DEG_DOWN:
				currplayer_vel_y = currplayer_vel_x;
				dashing[currplayer] = 3;
				break;
			case DASH_GRAVITY_ORB_UPWARDS:
				if (!dashing[currplayer]) {
					if (gamemode == 3 || gamemode == 5) {
						if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
					}
					else currplayer_gravity ^= 0x01;
				}			
				//intentional leak
			case DASH_ORB_UPWARDS:
				currplayer_vel_y = currplayer_vel_x * 4;
				//currplayer_vel_x = 0;
				dashing[currplayer] = 4;
				break;
			case DASH_GRAVITY_ORB_DOWNWARDS:
				if (!dashing[currplayer]) {
					if (gamemode == 3 || gamemode == 5) {
						if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
					}
					else currplayer_gravity ^= 0x01;
				}			
				//intentional leak
			case DASH_ORB_DOWNWARDS:
				currplayer_vel_y = -currplayer_vel_x * 4;
				//currplayer_vel_x = 0;
				dashing[currplayer] = 5;
				break;
			default:
				currplayer_vel_y = sprite_gamemode_y_adjust();
				//break;
			};
		idx8_inc(activesprites_activated, index);			
		}
	}
}

static void sprite_gamemode_controller_check() {
	if (controllingplayer->press_a || controllingplayer->press_up) {	
		idx8_store(cube_data, currplayer, cube_data[currplayer] & 0x01);
		settrailstuff();
		switch (collided) {
		case BLUE_ORB:
			if (gamemode == 3 || gamemode == 5) {
				if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
			}
			else currplayer_gravity ^= 0x01;
			currplayer_vel_y = (!currplayer_gravity) ? PAD_HEIGHT_BLUE^0xFFFF : PAD_HEIGHT_BLUE;
			break;
		case GREEN_ORB:
			if (gamemode == 3 || gamemode == 5) {
				if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
			}
			else currplayer_gravity ^= 0x01;
		//	if (currplayer_gravity && currplayer_vel_y < 0x670) currplayer_vel_y = 0x670;
		//	else if (!currplayer_gravity && currplayer_vel_y > -0x670) currplayer_vel_y = -0x670;
			currplayer_vel_y = sprite_gamemode_y_adjust();			
			break;
		case DASH_GRAVITY_ORB:
			if (!dashing[currplayer]) {
				if (gamemode == 3 || gamemode == 5) {
					if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
				}
				else currplayer_gravity ^= 0x01;
			}
			//intentional leak
		case DASH_ORB:
			currplayer_vel_y = 0;
			dashing[currplayer] = 1;
			break;
		case DASH_GRAVITY_ORB_45DEG_UP:
			if (!dashing[currplayer]) {
				if (gamemode == 3 || gamemode == 5) {
					if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
				}
				else currplayer_gravity ^= 0x01;
			}
			//intentional leak
		case DASH_ORB_45DEG_UP:
			currplayer_vel_y = -currplayer_vel_x;
			dashing[currplayer] = 2;
			break;	
		case DASH_GRAVITY_ORB_45DEG_DOWN:
			if (!dashing[currplayer]) {
				if (gamemode == 3 || gamemode == 5) {
					if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
				}
				else currplayer_gravity ^= 0x01;
			}
			//intentional leak
		case DASH_ORB_45DEG_DOWN:
			currplayer_vel_y = currplayer_vel_x;
			dashing[currplayer] = 3;
			break;		
		case DASH_GRAVITY_ORB_UPWARDS:
			if (!dashing[currplayer]) {
				if (gamemode == 3 || gamemode == 5) {
					if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
				}
				else currplayer_gravity ^= 0x01;
			}
			//intentional leak
		case DASH_ORB_UPWARDS:
			currplayer_vel_y = currplayer_vel_x;
			currplayer_vel_x = 0;
			dashing[currplayer] = 4;
			break;	
		case DASH_GRAVITY_ORB_DOWNWARDS:
			if (!dashing[currplayer]) {
				if (gamemode == 3 || gamemode == 5) {
					if (currplayer_vel_y != 0) currplayer_gravity ^= 1;
				}
				else currplayer_gravity ^= 0x01;
			}
			//intentional leak
		case DASH_ORB_DOWNWARDS:
			currplayer_vel_y = -currplayer_vel_x;
			currplayer_vel_x = 0;
			dashing[currplayer] = 5;
			break;
		default:
			currplayer_vel_y = sprite_gamemode_y_adjust();
			//break;
		};
	idx8_inc(activesprites_activated, index);
	}
}

void sprite_collide_lookup() {

	if (!activesprites_activated[index] || dual || options & platformer) {
		switch (collided) {
		case DUAL_PORTAL:
	//		if (!activesprites_activated[index]) {
				dual = 1;
				if (twoplayer) { player_gravity[1] = player_gravity[0] ^ 1;  }
				else { player_x[1] = player_x[0]; player_y[1] = currplayer_y; player_gravity[1] = !currplayer_gravity; player_vel_y[1] = -currplayer_vel_y; }
				activesprites_type[index] = 0xFF;
	//		}
			return;
		case SINGLE_PORTAL:
	//		if (!activesprites_activated[index]) {
				if (!twoplayer) { dual = 0; player_y[0] = currplayer_y; player_gravity[0] = currplayer_gravity; player_vel_y[0] = currplayer_vel_y; }
				else { player_gravity[1] = player_gravity[0]; }

				tallmode = 0;
				longmode = 0;
				bigboi = 0;
				activesprites_type[index] = 0xFF;
	//		}
			return;
		case TELEPORT_PORTAL_EXIT:
		case TELEPORT_SQUARE_EXIT:
		case NOSPRITE:
			return;
		
		// Portal game mode switches
		case S_BLOCK: dashing[currplayer] = 0; orbed[currplayer] = 1; return;
		case H_BLOCK: hblocked[currplayer] = 1; return;
		case J_BLOCK: jblocked[currplayer] = 1; return;
		case D_BLOCK: dblocked[currplayer] = 1; return;
		case F_BLOCK: fblocked[currplayer] = 1; return;
#ifdef FLAG_KANDO_FUN_STUFF
		case TALLBOI_MODE_ENTER: tallmode = 1; return;
		case LONGBOI_MODE_ENTER: longmode = 1; return;
		case BIGBOI_MODE_ENTER: bigboi = 1; return;
		case GRAVITY_1X_PORTAL: gravity_mod = 0; return;
		case GRAVITY_13_PORTAL: gravity_mod = 1; return;
		case GRAVITY_12_PORTAL: gravity_mod = 2; return;
		case GRAVITY_23_PORTAL: gravity_mod = 3; return;
		case GRAVITY_2X_PORTAL: gravity_mod = 4; return;
#endif
		case CUBE_MODE:
			orbactive = 0;
			if (gamemode == 6) currplayer_vel_y = 0;
			if (retro_mode) gamemode = 4;
			else gamemode = 0;
			return;    

		case SHIP_MODE:
		case UFO_MODE:
			settrailstuff();
			
		case BALL_MODE:
			target_scroll_y = (uint16SepArrLoad(activesprites_y, index) - 0x10);
	//		target_scroll_y -= 0x10;
		case ROBOT_MODE:
			if (gamemode == 6) currplayer_vel_y = 0;
			gamemode = collided;
			retrofireballclear();
			//robotjumptime[currplayer] = 0;
			return;
		case TELEPORT_SQUARE_ENTER:
			if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
				currplayer_vel_y = 0;
				orbed[currplayer] = 1;
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
		case TELEPORT_PORTAL_UPWARDS_ENTER:
		case TELEPORT_PORTAL_DOWNWARDS_ENTER:
		case TELEPORT_PORTAL_ENTER_EXTENSION:
		case TELEPORT_PORTAL_ENTER:
				high_byte(currplayer_y) = teleport_output;
				//idx8_inc(activesprites_activated, index);
			}
			return;
		case SPIDER_MODE:
			if (gamemode == 6) currplayer_vel_y = 0;
			gamemode = 5;
			retrofireballclear();		
			target_scroll_y = (uint16SepArrLoad(activesprites_y, index) - 0x10);		
			return;
		case WAVE_MODE:
			settrailstuff();
			//if (gamemode == 6) currplayer_vel_y = 0;			
			gamemode = 6;
			retrofireballclear();		
			target_scroll_y = (uint16SepArrLoad(activesprites_y, index) - 0x10);		
			return;
		case SWING_MODE:
			settrailstuff();
			if (gamemode == 6) currplayer_vel_y = 0;
			gamemode = 7;
			retrofireballclear();		
			target_scroll_y = (uint16SepArrLoad(activesprites_y, index) - 0x10);	
			return;
#ifdef FLAG_KANDO_FUN_STUFF
		case NINJA_MODE:
			if (gamemode == 6) currplayer_vel_y = 0;		
			gamemode = 8;
			return;
		case RANDOM_MODE_PORTAL:
			target_scroll_y = (uint16SepArrLoad(activesprites_y, index) - 0x10);
			if (gamemode == 6) currplayer_vel_y = 0;		
			gamemode = newrand() & 7;
			idx8_inc(activesprites_activated, index);
			return;
#endif
		case MINI_PORTAL:
			currplayer_mini = 1;
			return;
		case GROWTH_PORTAL:
			currplayer_mini = 0;
			return;
		case GREEN_PAD:
			currplayer_gravity ^= 1;
			if (currplayer_gravity && currplayer_vel_y < 0x670) currplayer_vel_y = 0x670;
			else if (!currplayer_gravity && currplayer_vel_y > -0x670) currplayer_vel_y = -0x670;

			idx8_inc(activesprites_activated, index);
			return;


		// collided with non game mode portals 

		case GRAVITY_DOWN_PORTAL:
		case GRAVITY_DOWN_UPWARDS_PORTAL:
		case GRAVITY_DOWN_DOWNWARDS_PORTAL:
		case GRAVITY_DOWN_INVISIBLE_PORTAL:  
			if (currplayer_gravity) {
				
				settrailstuff();
				currplayer_gravity = 0; 
				if (currplayer_vel_y < -0x0290) currplayer_vel_y = -0x0290; 
				robotjumptime[currplayer] = 0;
				idx8_inc(activesprites_activated, index);
			}
			return;
		case GRAVITY_UP_PORTAL:
		case GRAVITY_UP_UPWARDS_PORTAL:
		case GRAVITY_UP_DOWNWARDS_PORTAL:
		case GRAVITY_UP_INVISIBLE_PORTAL:
			if (!currplayer_gravity) {
				
				settrailstuff();
				currplayer_gravity = 1; 
				if (currplayer_vel_y > 0x0290) currplayer_vel_y = 0x0290; 
				robotjumptime[currplayer] = 0;
				idx8_inc(activesprites_activated, index);	
			}
			return;

		// collided with coin
		case COIN1:
		case COINGOTTEN1:
			if (!has_practice_point) {
				coins |= COIN_1;
			sfx_play(sfx_coin, 0);
				coin1_timer = 1;
				coin1_speed = 0x0200;
				animating = 1;		
			}
			return;
		case COIN2:
		case COINGOTTEN2:
			if (!has_practice_point) {
				coins |= COIN_2;
		       sfx_play(sfx_coin, 0);
				coin2_timer = 1;
				coin2_speed = 0x0200;
				animating = 1;		
			}
			return;
		case COIN3:
		case COINGOTTEN3:
			if (!has_practice_point) {
				coins |= COIN_3;
			sfx_play(sfx_coin, 0);
				coin3_timer = 1;
				coin3_speed = 0x0200;
				animating = 1;		
			}
			return;

		// collided with speed trigger
		case SPEED_05_PORTAL:
			speed = 1;
			return;
		case SPEED_10_PORTAL:
			speed = 0;
			return;
		case SPEED_20_PORTAL:
			speed = 2;
			return;
		case SPEED_30_PORTAL:
			speed = 3;
			return;
		case SPEED_40_PORTAL:
			speed = 4;
			return;

		case SPIDER_ORB_UP:
			if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
		case SPIDER_PAD_UP:
				high_byte(currplayer_y) -= eject_D;
				currplayer_vel_y = 0;
				currplayer_gravity = 1;
				crossPRGBankJump0(spider_up_wait);
				high_byte(currplayer_y) -= eject_U;
				currplayer_vel_y = 0;	
				orbed[currplayer] = 1;
				idx8_inc(activesprites_activated, index);
			}
			return;
		case SPIDER_ORB_DOWN:
			if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
				idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
		case SPIDER_PAD_DOWN:
				high_byte(currplayer_y) -= eject_U + 1;
				currplayer_vel_y = 0;
				currplayer_gravity = 0;
				crossPRGBankJump0(spider_down_wait);
				high_byte(currplayer_y) -= eject_D;
				currplayer_vel_y = 0;
				orbed[currplayer] = 1;
				idx8_inc(activesprites_activated, index);
			}
			return;

		// collided with a pad
		case YELLOW_PAD_DOWN:
		case YELLOW_PAD_UP:
			settrailstuff();
			table_offset = yellow_pad;
			currplayer_vel_y = sprite_gamemode_y_adjust();
			//idx8_inc(activesprites_activated, index);	
			return;
		case PINK_PAD_DOWN:
		case PINK_PAD_UP:
			settrailstuff();
			table_offset = pink_pad;
			currplayer_vel_y = sprite_gamemode_y_adjust();
			//idx8_inc(activesprites_activated, index);	
			return;
		case RED_PAD_DOWN:
		case RED_PAD_UP:
			settrailstuff();
			table_offset = red_pad;
			currplayer_vel_y = sprite_gamemode_y_adjust();
			//idx8_inc(activesprites_activated, index);	
			return;

		case GRAVITY_PAD_DOWN:
		case GRAVITY_PAD_DOWN_INVISIBLE:
			if (!currplayer_gravity) { 
				settrailstuff();
				currplayer_gravity = 0x01;				//flip gravity
				currplayer_vel_y = PAD_HEIGHT_BLUE;
				//invincible_counter = 3;
			}
			idx8_inc(activesprites_activated, index);	
			return;
		
		case GRAVITY_PAD_UP:
		case GRAVITY_PAD_UP_INVISIBLE:
			if (currplayer_gravity) { 	
				settrailstuff();
				currplayer_gravity = 0x00;				//flip gravity
				currplayer_vel_y = PAD_HEIGHT_BLUE^0xFFFF;
				//invincible_counter = 3;				
			}
			idx8_inc(activesprites_activated, index);	
			return;

		// collided with an orb



		case YELLOW_ORB:
			table_offset = 0;
			//intentional leak
		case DASH_ORB:
		case DASH_GRAVITY_ORB:
		case DASH_ORB_UPWARDS:
		case DASH_GRAVITY_ORB_UPWARDS:
		case DASH_ORB_DOWNWARDS:
		case DASH_GRAVITY_ORB_DOWNWARDS:
		case DASH_ORB_45DEG_UP:
		case DASH_GRAVITY_ORB_45DEG_UP:
		case DASH_ORB_45DEG_DOWN:
		case DASH_GRAVITY_ORB_45DEG_DOWN:
		case BLUE_ORB:
			break;

		case YELLOW_ORB_BIGGER:
			table_offset = ylw_bigger;
			break;
		case YELLOW_ORB_SMALLER:
			table_offset = ylw_smaller;
			break;

		case PINK_ORB:
			table_offset = pink_orb;
			break;

		case BLACK_ORB:
			table_offset = black_orb;
			break;

		case RED_ORB:
			table_offset = red_orb;
			break;
#ifdef FLAG_KANDO_FUN_STUFF		
		case GREEN_ORB:
			table_offset = yellow_orb;
			break;
#endif
		default:
			return;
		};
		
		if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
			sprite_gamemode_main();
		} else {
			sprite_gamemode_controller_check();
		}
	
		return;
	}
}

#undef table_offset
#undef collided

void sprite_collide(){
	Generic.width = currplayer_mini ? MINI_CUBE_WIDTH : CUBE_WIDTH;
	Generic.height = currplayer_mini ? MINI_CUBE_HEIGHT : CUBE_HEIGHT;

	Generic.x = high_byte(currplayer_x) + 1;
	Generic.y = high_byte(currplayer_y) + (byte(0x10 - Generic.height) >> 1);

	index = 0;

	do {
		tmp3 = activesprites_active[index];
		if (tmp3){
			tmp4 = activesprites_type[index];

			tmp2 = sprite_heights[tmp4];
			tmp9 = sprite_widths[tmp4];
			switch (tmp2) {

				case DECO:
					if (twoplayer || !viseffects) activesprites_type[index] = 0xFF;
					continue;

				case COLR:
					if (discomode) {
						activesprites_type[index] = 0xFF; continue;
					}
					tmp2 = (tmp4 & 0x3F);
					
					if (tmp2 == 0x20) tmp2 = 0x30;
					
					if (tmp4 >= 0xC0){
						pal_col(6, tmp2);
						pal_col(5, oneShadeDarker(tmp2)); 
						lastgcolortype = tmp4;
					} else {
						pal_col(0, tmp2);
						pal_col(1, oneShadeDarker(tmp2)); 
						pal_col(9, oneShadeDarker(tmp2)); 
						lastbgcolortype = tmp4;
					}
					pal_set_update();
					activesprites_type[index] = 0xFF;
					// intentional leak
				case 0:
					continue;
				
				case OUTL:
					outline_color = idx8_load(OUTLINES, tmp4 & 0x0F);
					activesprites_type[index] = 0xFF;
					continue;

				case SPBH:
					if ((tmp2 = sprite_load_special_behavior()) == 0) continue;
			}
			Generic2.height = tmp2;	
			Generic2.width  = tmp9;

			Generic2.x = activesprites_realx[index] + sprite_x_offset[tmp4];
			Generic2.y = activesprites_realy[index] + sprite_y_offset[tmp4];
			
			if (check_collision()) {
				sprite_collide_lookup();
			}
		}
	} while (++index < max_loaded_sprites);

	Generic.height = currplayer_mini ? MINI_CUBE_HEIGHT : CUBE_HEIGHT;
}


void settrailstuff() {
	if (forced_trails != 2 && !orbactive) {
		orbactive = 1;
	}
}

void retrofireballclear(void) {
	if (retro_mode) {
		memfill(jimsheatballalive, 0, sizeof(jimsheatballalive));		
	}
}			

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
