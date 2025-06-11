#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")
#pragma code-name(push, "XCD_BANK_00")

extern void load_next_sprite(uint8_t slot);
extern void check_spr_objects();
void init_sprites();

void dual_cap_check();
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
	0x34,	0x34,	0x34,	0x34,	0x34,	0x12,	0x12,	SPBH,	// 00 - 07
	0x28,	0x28,	0x03,	0x12,	0x03,	0x03,	0x03,	SPBH,	// 08 - 0F
	0x0e,	0x0e,	0x0e,	0x0e,	0x24,	0x24,	0x24,	0x34,	// 10 - 17
	0x34,	0x34,	SPBH,	SPBH,	SPBH,	SPBH,	SPBH,	0x12,	// 18 - 1F
	0x24,	0x24,	0x34,	0x34,	0x34,	0x03,	0x03,	0x12,	// 20 - 27
	0x12,	0x12,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	// 28 - 2F
	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	// 30 - 37
	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	DECO,	// 38 - 3F
	DECO,	DECO,	DECO,	DECO,	0x12,	0x12,	0x12,	DECO,	// 40 - 47
	DECO,	DECO,	DECO,	0x34,	0x12,	0x12,	0x30,	SPBH,	// 48 - 4F
	0x12,	0x12,	0x03,	0x03,	0x12,	0x12,	0x03,	0x03,	// 50 - 57
	0x34,	0x10,	SPBH,	0x12,	0x12,	0x12,	0x12,	0x34,	// 58 - 5F
	0x34,	0x34,	0x34,	0x34,	0x34,	0x02,	0x10,	SPBH,	// 60 - 67
	0x10,	SPBH,	0x34,	0x34,	0x34,	0x20,	0x08,	SPBH,	// 68 - 6F
	SPBH,	SPBH,	SPBH,	SPBH,	SPBH,	0x10,	SPBH,	0x10,	// 70 - 77
	SPBH,	0x12,	0x00,	0x00,	0x00,	0x00,	SPBH,	0x00,	// 78 - 7F
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// 80 - 87
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	0x00,	COLR,	// 88 - 8F
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// 90 - 97
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	0x00,	COLR,	// 98 - 9F
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// A0 - A7
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	COLR,	OUTL,	// A8 - AF
	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	// B0 - B7
	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	OUTL,	// B8 - BF
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// C0 - C7
	COLR,	COLR,	COLR,	COLR,	COLR,	0x00,	0x00,	COLR,	// C8 - CF
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// D0 - D7
	COLR,	COLR,	COLR,	COLR,	COLR,	SPBH,	SPBH,	KNDO,	// D8 - DF
	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	COLR,	// E0 - E7
	COLR,	COLR,	COLR,	COLR,	COLR,	SPBH,	KNDO,	KNDO,	// E8 - EF
	SPBH,	SPBH,	SPBH,	SPBH,	SPBH,	SPBH,	0x10,	0x10,	// F0 - F7
	0x10,	0x10,	0x1F,	0x10,	0x10,	0x03,	0x03,	0x00,	// F8 - FF
};

uint8_t sprite_widths[]={
	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 00 - 07
	0x0e,	0x0e,	0x0F,	0x10,	0x0F,	0x0F,	0x0F,	0x10,	// 08 - 0F
	0x28,	0x28,	0x28,	0x28,	0x10,	0x10,	0x10,	0x10,	// 10 - 17
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
	0x30,	0x30,	0x10,	0x10,	0x10,	0x10,	0x08,	0x10,	// 68 - 6F
	0x10,	0x10,	0x10,	0x10,	0x10,	0x30,	0x30,	0x30,	// 70 - 77
	0x30,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	// 78 - 7F
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
	0x10,	0x08,	0x1B,	0x10,	0x10,	0x0E,	0x0E,	0x10,	// F8 - FF
};

// Offset goes for x to the rigth and for y down, for moving it in the other direction, put a negative value (0x80-0xff) 

uint8_t sprite_x_offset[]={
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 00 - 07
	0x01,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 08 - 0F
	0x04,	0x04,	0x04,	0x04,	0x00,	0x00,	0x00,	0x00,	// 10 - 17
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
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x04,	0x00,	// 68 - 6F
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
	0x00,	0x08,	-0x07,	0x00,	0x00,	0x00,	0x00,	0x00,	// F8 - FF
};

uint8_t sprite_y_offset[]={
	-0x02,	-0x02,	-0x02,	-0x02,	-0x02,	-0x01,	-0x01,	0x00,	// 00 - 07
	0x04,	0x04,	0x05,	-0x01,	0x00,	0x05,	0x00,	0x00,	// 08 - 0F
	0x01,	0x01,	0x01,	0x01,	-0x02,	-0x02,	-0x02,	-0x02,	// 10 - 17
	-0x02,	-0x02,	0x00,	0x00,	0x00,	0x00,	0x00,	-0x01,	// 18 - 1F
	-0x02,	-0x02,	-0x02,	-0x02,	-0x02,	0x05,	0x00,	-0x01,	// 20 - 27
	-0x01,	-0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 28 - 2F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 30 - 37
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 38 - 3F
	0x00,	0x00,	0x00,	0x00,	-0x01,	-0x01,	-0x01,	0x00,	// 40 - 47
	0x00,	0x00,	0x00,	-0x02,	0x00,	-0x01,	-0x01,	0x00,	// 48 - 4F
	-0x01,	-0x01,	0x05,	0x00,	-0x01,	-0x01,	0x05,	0x00,	// 50 - 57
	-0x02,	0x00,	0x00,	-0x01,	-0x01,	-0x01,	-0x01,	-0x02,	// 58 - 5F
	-0x02,	-0x02,	-0x02,	-0x02,	-0x02,	0x00,	0x00,	0x00,	// 60 - 67
	0x00,	0x00,	-0x02,	-0x02,	-0x02,	0x00,	0x04,	0x00,	// 68 - 6F
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 70 - 77
	0x00,	-0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	// 78 - 7F
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
	0x00,	0x00,	-0x07,	0x00,	0x00,	0x05,	0x02,	0x00,	// F8 - FF
};

void animate_coin_1();

void animate_coin_2();

void animate_coin_3();

void clear_slope_stuff() {
	currplayer_was_on_slope_counter = 0;
	currplayer_slope_frames = 0;
	currplayer_slope_type = 0;
	currplayer_last_slope_type = 0;
}

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
			case GRAVITY_13_PORTAL_INVIS:
				gravity_mod = 1;
				killSprite_return0;
			case GRAVITY_12_PORTAL_INVIS:
				gravity_mod = 2;
				killSprite_return0;
			case GRAVITY_23_PORTAL_INVIS:
				gravity_mod = 3;
				killSprite_return0;
			case GRAVITY_2X_PORTAL_INVIS:
				gravity_mod = 4;
				killSprite_return0;
			case GRAVITY_1X_PORTAL_INVIS:
				gravity_mod = 0;
				killSprite_return0;
		#endif
		case FORCED_FREECAM_ON:
			nocamlockforced = 1;
			killSprite_return0;
		case FORCED_FREECAM_OFF:
			nocamlockforced = 0;
			killSprite_return0;
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

		case INVIS_TELEPORT_PORTAL_DOWNWARDS_EXIT:
		case INVIS_TELEPORT_PORTAL_UPWARDS_EXIT:	
		case TELEPORT_PORTAL_DOWNWARDS_EXIT:
		case TELEPORT_PORTAL_UPWARDS_EXIT:		
			teleport_output = activesprites_realy[index] + 0x10;
			return 0x10;

		case TELEPORT_PORTAL_EXIT:
			teleport_output = activesprites_realy[index] + 0x10;
			return 0x30;

		case COIN1:
			if (coin1_obtained[level]) {
				activesprites_type[index] = COINGOTTEN1;
			}
		case COINGOTTEN1:
			if (coin1_timer) {
				animate_coin_1();
			}      
			return 0x10;

		case COIN2:
			if (coin2_obtained[level]) {
				activesprites_type[index] = COINGOTTEN2;
			}

		case COINGOTTEN2:
			if (coin2_timer) {
				animate_coin_2();
			}
			return 0x10;

		case COIN3:
			if (coin3_obtained[level]) {
				activesprites_type[index] = COINGOTTEN3;
			}

		case COINGOTTEN3:
			#ifdef fingerdash
				if (level == fingerdash && minicoins != 10) {
					activesprites_type[index] = 0xFF;
					return 0x10;
				}
			#endif
			if (coin3_timer) {
				animate_coin_3();
			}
			return 0x10; 

		case LEVEL_END_TRIGGER:
			gameState = STATE_LVLDONE; 
			
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

void common_dash_orb_routine() {
	if (gamemode == GAMEMODE_UFO || gamemode == GAMEMODE_SPIDER) {
		if (currplayer_vel_y != 0) invert_gravity(currplayer_gravity);
	}
	else invert_gravity(currplayer_gravity);
}

#define yellow_orb  0x00 << 3
#define yellow_pad  0x01 << 3
#define pink_orb    0x02 << 3
#define pink_pad    0x03 << 3
#define red_orb     0x04 << 3
#define ylw_bigger  0x05 << 3
#define black_orb   0x06 << 3
#define ylw_smaller 0x07 << 3
#define red_pad     0x08 << 3

const short heights[] = {
//	cube    ship    ball     ufo    robot   spider  wave    swing
	0x590,  0x450,  0x410,  0x3B0,  0x590,  0x440,  0x000,  0x3A0, // yellow orb
	0x7C0,  0x3C0,  0x4F0,  0x330,  0x8B0,  0x500,  0x000,  0x450, // yellow pad
	0x3D0,  0x200,  0x330,  0x220,  0x450,  0x350,  0x000,  0x2D0, // pink orb
	0x510,  0x270,  0x360,  0x250,  0x550,  0x350,  0x000,  0x360, // pink pad
	0x750,  0x5D0,  0x550,  0x510,  0x750,  0x500,  0x000,  0x4D0, // red orb
	0x590,  0x590,  0x5D0,  0x590,  0x590,  0x590,  0x000,  0x5D0, // yellow orb bigger
   -0x990, -0x990, -0x970, -0x990, -0x990, -0x990,  0x000, -0x970, // black orb
	0x540,  0x540,  0x472,  0x4B0,  0x770,  0x4B0,  0x000,  0x472, // yellow orb smaller
	0x9F0,  0x620,  0x630,  0x400,  0xA50,  0x690,  0x000,  0x660, // red pad		
};

const short mini_heights[] = {
//      cube    ship    ball     ufo    robot   spider  wave    swing
	0x4D0,  0x4A0,  0x450,  0x3D0,  0x470,  0x350,  0x000,  0x2A0, // yellow orb
	0x680,  0x430,  0x4D0,  0x3A0,  0x730,  0x400,  0x000,  0x340, // yellow pad
	0x350,  0x1E0,  0x350,  0x1B0,  0x370,  0x230,  0x000,  0x1F0, // pink orb
	0x3F0,  0x1E0,  0x390,  0x150,  0x350,  0x350,  0x000,  0x220, // pink pad
	0x650,  0x670,  0x500,  0x550,  0x650,  0x470,  0x000,  0x350, // red orb
	0x590,  0x590,  0x560,  0x590,  0x590,  0x590,  0x000,  0x560, // yellow orb bigger
   -0x990, -0x990, -0x970, -0x990, -0x990, -0x990,  0x000, -0x970, // black orb
	0x540,  0x540,  0x472,  0x4B0,  0x770,  0x4B0,  0x000,  0x472, // yellow orb smaller
	0x830,  0x6C0,  0x5B0,  0x550,  0x8D0,  0x550,  0x000,  0x3A0, // red pad	
};

#define table_offset tmp3
#define collided tmp4

// Load the player velocity from the height table
static unsigned int __fastcall__ sprite_gamemode_y_adjust() {
	if (!retro_mode) __A__ = (gamemode | table_offset) << 1;
	else if (retro_mode && gamemode == GAMEMODE_ROBOT) __A__ = (0 | table_offset) << 1;
	else __A__ = (gamemode | table_offset) << 1;
	__asm__("tay");
	if (currplayer_mini) {
		__AX__ = (__asm__ ("lda %v,y", mini_heights), __asm__ ("ldx %v+1,y", mini_heights),__AX__);
	} else {
		__AX__ = (__asm__ ("lda %v,y", heights),__asm__ ("ldx %v+1,y", heights),__AX__);
	}
	do_if_bit7_clr_mem(currplayer_gravity, {__AX__ ^= 0xffff; __AX__ += 1;});
	return __AX__;
}

static void sprite_gamemode_main() {
	if (controllingplayer->a || controllingplayer->up) {
		if (gamemode == BALL_MODE) ball_switched[currplayer] = 1;
		if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
			if (gamemode == ROBOT_MODE) orbed[currplayer] = 1;
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
			settrailstuff();
			clear_slope_stuff();

			switch (collided) {
			case BLUE_ORB:
				if (!activesprites_activated[index]) {
				invert_gravity(currplayer_gravity); invert_gravity(player_gravity[0]); invert_gravity(player_gravity[1]);
				dual_cap_check();
				if (gamemode != BALL_MODE) {
					currplayer_vel_y = (!currplayer_gravity) ? -PAD_HEIGHT_BLUE : PAD_HEIGHT_BLUE;
				} else {
					currplayer_vel_y = (!currplayer_gravity) ? -ORB_BALL_HEIGHT_BLUE : ORB_BALL_HEIGHT_BLUE;
				}
				}
				break;
			case GREEN_ORB:
				if (!activesprites_activated[index]) {
				invert_gravity(currplayer_gravity); invert_gravity(player_gravity[0]); invert_gravity(player_gravity[1]);
				dual_cap_check();
				currplayer_vel_y = sprite_gamemode_y_adjust();
				}
				break;
			case DASH_GRAVITY_ORB:
				if (!dashing[currplayer]) { 
					common_dash_orb_routine();
				}
				//intentional leak
			case DASH_ORB:
				currplayer_vel_y = 0;
				dashing[currplayer] = 1;
				break;
			case DASH_GRAVITY_ORB_45DEG_UP:
				if (!dashing[currplayer]) {
					common_dash_orb_routine();
				}				
				//intentional leak
			case DASH_ORB_45DEG_UP:
				currplayer_vel_y = -currplayer_vel_x;
				dashing[currplayer] = 2;
				break;
			case DASH_GRAVITY_ORB_45DEG_DOWN:
				if (!dashing[currplayer]) {
					common_dash_orb_routine();
				}				
				//intentional leak
			case DASH_ORB_45DEG_DOWN:
				currplayer_vel_y = currplayer_vel_x;
				dashing[currplayer] = 3;
				break;
			case DASH_GRAVITY_ORB_UPWARDS:
				if (!dashing[currplayer]) {
					common_dash_orb_routine();
				}			
				//intentional leak
			case DASH_ORB_UPWARDS:
				currplayer_vel_y = currplayer_vel_x * 4;
				//currplayer_vel_x = 0;
				dashing[currplayer] = 4;
				break;
			case DASH_GRAVITY_ORB_DOWNWARDS:
				if (!dashing[currplayer]) {
					common_dash_orb_routine();
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
			if (!activesprites_activated[index]) {
				invert_gravity(currplayer_gravity); invert_gravity(player_gravity[0]); invert_gravity(player_gravity[1]);
				dual_cap_check();
				if (gamemode != BALL_MODE) {
					currplayer_vel_y = (!currplayer_gravity) ? -PAD_HEIGHT_BLUE : PAD_HEIGHT_BLUE;
				} else {
					currplayer_vel_y = (!currplayer_gravity) ? -ORB_BALL_HEIGHT_BLUE : ORB_BALL_HEIGHT_BLUE;
				}
			}
			break;
		case GREEN_ORB:
			if (!activesprites_activated[index]) {
			invert_gravity(currplayer_gravity); invert_gravity(player_gravity[0]); invert_gravity(player_gravity[1]);
			dual_cap_check();
		//	if (currplayer_gravity && currplayer_vel_y < 0x670) currplayer_vel_y = 0x670;
		//	else if (!currplayer_gravity && currplayer_vel_y > -0x670) currplayer_vel_y = -0x670;
			currplayer_vel_y = sprite_gamemode_y_adjust();	
			}			
			break;
		case DASH_GRAVITY_ORB:
			if (!dashing[currplayer]) {
				common_dash_orb_routine();
			}
			//intentional leak
		case DASH_ORB:
			currplayer_vel_y = 0;
			dashing[currplayer] = 1;
			break;
		case DASH_GRAVITY_ORB_45DEG_UP:
			if (!dashing[currplayer]) {
				common_dash_orb_routine();
			}
			//intentional leak
		case DASH_ORB_45DEG_UP:
			currplayer_vel_y = -currplayer_vel_x;
			dashing[currplayer] = 2;
			break;	
		case DASH_GRAVITY_ORB_45DEG_DOWN:
			if (!dashing[currplayer]) {
				common_dash_orb_routine();
			}
			//intentional leak
		case DASH_ORB_45DEG_DOWN:
			currplayer_vel_y = currplayer_vel_x;
			dashing[currplayer] = 3;
			break;		
		case DASH_GRAVITY_ORB_UPWARDS:
			if (!dashing[currplayer]) {
				common_dash_orb_routine();
			}
			//intentional leak
		case DASH_ORB_UPWARDS:
			currplayer_vel_y = currplayer_vel_x;
			currplayer_vel_x = 0;
			dashing[currplayer] = 4;
			break;	
		case DASH_GRAVITY_ORB_DOWNWARDS:
			if (!dashing[currplayer]) {
				common_dash_orb_routine();
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

#define PORTAL_TO_TOP_DIFF 0x38


void sprite_collide_lookup() {

	static void * const sprite_collide_jump_table_0[] = {
		&&spcl_cube,	&&spcl_shipufo,	&&spcl_ball,	&&spcl_shipufo,	// 0x00 - 0x03
		&&spcl_robot,	&&spcl_orb_cmn,	&&spcl_pinkorb,	&&spcl_coin_1,	// 0x04 - 0x07
		&&spcl_gvdn_pt,	&&spcl_gvup_pt,	&&spcl_ylw_pad,	&&spcl_ylw_orb,	// 0x08 - 0x0B
		&&spcl_ylw_pad,	&&spcl_gvdn_pd,	&&spcl_gvup_pd,	&&spcl_default,	// 0x0C - 0x0F
		&&spcl_gvdn_pt,	&&spcl_gvdn_pt,	&&spcl_gvup_pt,	&&spcl_gvup_pt,	// 0x10 - 0x13
		&&spcl_spd_05,	&&spcl_spd_10,	&&spcl_spd_20,	&&spcl_spider,	// 0x14 - 0x17
		&&spcl_mini_pt,	&&spcl_grow_pt,	&&spcl_coin_2,	&&spcl_coin_3,	// 0x18 - 0x1B
		&&spcl_coin_1,	&&spcl_coin_2,	&&spcl_coin_3,	&&spcl_ylw_big,	// 0x1C - 0x1F
		&&spcl_spd_30,	&&spcl_spd_40,	&&spcl_dual_pt,	&&spcl_sngl_pt,	// 0x20 - 0x23
		&&spcl_wave,	&&spcl_pinkpad,	&&spcl_pinkpad,	&&spcl_grn_orb,	// 0x24 - 0x27
		&&spcl_red_orb,	&&spcl_ylw_sml,	&&spcl_default,	&&spcl_default,	// 0x28 - 0x2B
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x2C - 0x2F
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x30 - 0x33
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x34 - 0x37
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x38 - 0x3B
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x3C - 0x3F
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x40 - 0x43
		&&spcl_blckorb,	&&spcl_orb_cmn,	&&spcl_orb_cmn,	&&spcl_default,	// 0x44 - 0x47
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_swing,	// 0x48 - 0x4B
		&&spcl_orb_cmn,	&&spcl_orb_cmn,	&&spcl_tlpt_pt,	&&spcl_default,	// 0x4C - 0x4F
		&&spcl_orb_cmn,	&&spcl_orb_cmn,	&&spcl_red_pad,	&&spcl_red_pad,	// 0x50 - 0x53
		&&spcl_sporbup,	&&spcl_sporbdn,	&&spcl_sppadup,	&&spcl_sppaddn,	// 0x54 - 0x57
		&&spcl_ninja,	&&spcl_tlpt_sq,	&&spcl_default,	&&spcl_orb_cmn,	// 0x58 - 0x5B
		&&spcl_orb_cmn,	&&spcl_orb_cmn,	&&spcl_orb_cmn,	&&spcl_gv13_pt,	// 0x5C - 0x5F
		&&spcl_gv12_pt,	&&spcl_gv23_pt,	&&spcl_gv2x_pt,	&&spcl_gv1x_pt,	// 0x60 - 0x63
		&&spcl_rndmode,	&&spcl_grn_pad,	&&spcl_tlpt_pt,	&&spcl_default,	// 0x64 - 0x67
		&&spcl_tlpt_pt,	&&spcl_default,	&&spcl_tall_pt,	&&spcl_long_pt,	// 0x68 - 0x6B
		&&spcl_bigmode,	&&spcl_spdslow,	&&spcl_minicoi,	&&spcl_invi_on,	// 0x6C - 0x6F
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x70 - 0x73
		&&spcl_default,	&&spcl_tlpt_pt,	&&spcl_default,	&&spcl_tlpt_pt,	// 0x74 - 0x77
		&&spcl_default,	&&spcl_wht_orb,	&&spcl_default,	&&spcl_default,	// 0x78 - 0x7B
		&&spcl_default,	&&spcl_default,	&&spcl_invioff //,	&&spcl_invioff	// 0x7C - 0x7F
	};
	static void * const sprite_collide_jump_table_1[] = {
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x80 - 0x83
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x84 - 0x87
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x88 - 0x8B
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x8C - 0x8F
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x90 - 0x93
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x94 - 0x97
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x98 - 0x9B
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0x9C - 0x9F
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xA0 - 0xA3
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xA4 - 0xA7
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xA8 - 0xAB
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xAC - 0xAF
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xB0 - 0xB3
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xB4 - 0xB7
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xB8 - 0xBB
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xBC - 0xBF
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xC0 - 0xC3
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xC4 - 0xC7
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xC8 - 0xCB
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xCC - 0xCF
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xD0 - 0xD3
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xD4 - 0xD7
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xD8 - 0xDB
		// &&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xDC - 0xDF
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xE0 - 0xE3
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xE4 - 0xE7
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xE8 - 0xEB
		&&spcl_default,	&&spcl_tlpt_pt,	&&spcl_default,	&&spcl_default,	// 0xEC - 0xEF
		&&spcl_default,	&&spcl_default,	&&spcl_default,	&&spcl_default,	// 0xF0 - 0xF3
		&&spcl_default,	&&spcl_default,	&&spcl_f_block,	&&spcl_j_block,	// 0xF4 - 0xF7
		&&spcl_h_block,	&&spcl_s_block,	&&spcl_d_block,	&&spcl_gvup_pt,	// 0xF8 - 0xFB
		&&spcl_gvdn_pt,	&&spcl_gvdn_pd,	&&spcl_gvup_pd,	&&spcl_default,	// 0xFC - 0xFF
	};
	if (activesprites_activated[index] && !dual && !(options & platformer))
		return;
	
	// Instead of the giant ass switch : case that used to be here
	if (collided < 0x80)
		goto *sprite_collide_jump_table_0[collided];
	else if (collided >= 0xE0)
		jumpInTableWithOffset(sprite_collide_jump_table_1, collided, (0xE0 - 0x80));

	spcl_default:
		return;

	// Gamemode portals
	
	spcl_wht_orb:
		if ((gamemode == GAMEMODE_CUBE || gamemode == GAMEMODE_BALL || gamemode == GAMEMODE_ROBOT || gamemode == GAMEMODE_NINJA || gamemode == GAMEMODE_SPIDER || gamemode >= GAMEMODE_SWING) && cube_data[currplayer] & 0x02) {
			if ((controllingplayer->a || controllingplayer->up)) {
				idx8_store(cube_data,currplayer,cube_data[currplayer] | 0x01);
			}
		} else {
			if (controllingplayer->press_a || controllingplayer->press_up) {	
				idx8_store(cube_data,currplayer,cube_data[currplayer] | 0x01);
			}
		}
		return;
	
	spcl_invi_on:
		player_invis = 1;
		return;
	
	spcl_invioff:
		player_invis = 0;
		return;
	
	spcl_cube:
		orbactive = 0;
		exitPortalTimer = 10;
		if (gamemode == GAMEMODE_WAVE) currplayer_vel_y = 0;
		if (retro_mode) gamemode = GAMEMODE_ROBOT;
		else gamemode = GAMEMODE_CUBE;
		return;
	
	spcl_shipufo:
		settrailstuff();
		currplayer_vel_y /= 2;
		// intentional leak
	spcl_ball:
		if (!dual || twoplayer) target_scroll_y = (lohi_arr16_load(activesprites_y, index) - PORTAL_TO_TOP_DIFF);
		if (gamemode == GAMEMODE_WAVE) currplayer_vel_y /= 2;
		gamemode = collided;
		activesprites_activated[index] = 1;
		return;

	spcl_robot:
		exitPortalTimer = 10;
		if (gamemode == GAMEMODE_WAVE) currplayer_vel_y /= 2;
		gamemode = GAMEMODE_ROBOT;
		retrofireballclear();
		return;

	spcl_spider:
		if (gamemode == GAMEMODE_WAVE) currplayer_vel_y = 0;
		gamemode = GAMEMODE_SPIDER;
		retrofireballclear();		
		if (!dual || twoplayer) target_scroll_y = (lohi_arr16_load(activesprites_y, index) - PORTAL_TO_TOP_DIFF);		
		return;

	spcl_wave:
		settrailstuff();		
		gamemode = GAMEMODE_WAVE;
		retrofireballclear();		
		if (!dual || twoplayer) target_scroll_y = (lohi_arr16_load(activesprites_y, index) - PORTAL_TO_TOP_DIFF);		
		return;

	spcl_swing:
		settrailstuff();
		if (gamemode == GAMEMODE_WAVE) currplayer_vel_y = 0;
		gamemode = GAMEMODE_SWING;
		retrofireballclear();		
		if (!dual || twoplayer) target_scroll_y = (lohi_arr16_load(activesprites_y, index) - PORTAL_TO_TOP_DIFF);	
		return;

	spcl_ninja:
		#ifdef FLAG_KANDO_FUN_STUFF
			if (gamemode == GAMEMODE_WAVE) currplayer_vel_y = 0;		
			gamemode = GAMEMODE_NINJA;
		#endif
		return;

	spcl_rndmode:
		#ifdef FLAG_KANDO_FUN_STUFF
			if (!dual || twoplayer) target_scroll_y = (lohi_arr16_load(activesprites_y, index) - PORTAL_TO_TOP_DIFF);
			if (gamemode == GAMEMODE_WAVE) currplayer_vel_y = 0;		
			gamemode = newrand() & 7;
			idx8_inc(activesprites_activated, index);
		#endif
		return;

	spcl_minicoi:
		minicoins++;
		activesprites_type[index] = 0xFF;
		return;

	// Non-Gamemode portals 
	// - Gravity portals
	spcl_gvdn_pt:
		if (!currplayer_gravity) 
			return;
		currplayer_gravity = GRAVITY_DOWN;
		goto spcl_gvity_portal_common;
	
	spcl_gvup_pt:
		if (currplayer_gravity)
			return;
		currplayer_gravity = GRAVITY_UP;
		// intentional leak
	spcl_gvity_portal_common:
		settrailstuff();
		currplayer_vel_y /= 2;
		robotjumptime[currplayer] = 0;
		idx8_inc(activesprites_activated, index);
		return;
	
	// - Speed portals
	spcl_spd_05: speed = 1; return;
	spcl_spd_10: speed = 0; return;
	spcl_spd_20: speed = 2; return;
	spcl_spd_30: speed = 3; return;
	spcl_spd_40: speed = 4; return;
	spcl_spdslow: speed = 5; return;

	// - Gravity portals
	spcl_gv1x_pt:
		#ifdef FLAG_KANDO_FUN_STUFF
			gravity_mod = 0;
		#endif
		return;

	spcl_gv13_pt:
		#ifdef FLAG_KANDO_FUN_STUFF
			gravity_mod = 1;
		#endif
		return;

	spcl_gv12_pt:
		#ifdef FLAG_KANDO_FUN_STUFF
			gravity_mod = 2;
		#endif
		return;

	spcl_gv23_pt:
		#ifdef FLAG_KANDO_FUN_STUFF
			gravity_mod = 3;
		#endif
		return;

	spcl_gv2x_pt:
		#ifdef FLAG_KANDO_FUN_STUFF
			gravity_mod = 4;
		#endif
		return;

	// - Size portals
	spcl_mini_pt:
		currplayer_mini = 1;
		mini[0] = 1;
		mini[1] = 1;
		return;

	spcl_grow_pt:
		currplayer_mini = 0;
		mini[0] = 0;
		mini[1] = 0;
		return;

	// - Kando size portals
	spcl_tall_pt:
		#ifdef FLAG_KANDO_FUN_STUFF
			tallmode = 1;
		#endif
		return;

	spcl_long_pt:
		#ifdef FLAG_KANDO_FUN_STUFF
			longmode = 1;
		#endif
		return;

	spcl_bigmode:
		#ifdef FLAG_KANDO_FUN_STUFF
			bigboi = 1;
		#endif
		return;

	// - Doubling portals
	spcl_dual_pt:
		if (!activesprites_activated[index]) {
			dual = 1;
			target_scroll_y = (lohi_arr16_load(activesprites_y, index) - PORTAL_TO_TOP_DIFF);
			if (twoplayer) { player_gravity[1] = player_gravity[0] ^ 0xFF;  }
			else { 
				player_x[1] = player_x[0]; player_y[1] = currplayer_y;
				player_gravity[1] = currplayer_gravity ^ 0xFF;
				player_vel_y[1] = -currplayer_vel_y; mini[1] = mini[0];
			}
			// activesprites_type[index] = 0xFF;
			activesprites_activated[index] = 1;
		}
		return;
	
	spcl_sngl_pt:
		if (!activesprites_activated[index]) {
			if (!twoplayer) { dual = 0; player_y[0] = currplayer_y; player_gravity[0] = currplayer_gravity; player_vel_y[0] = currplayer_vel_y; }
			else { player_gravity[1] = player_gravity[0]; }
			activesprites_activated[index] = 1;

			tallmode = 0;
			longmode = 0;
			bigboi = 0;
			// activesprites_type[index] = 0xFF;
			exitPortalTimer = 10;
		}
		return;
	
	// - Teleport portals (and square)
	spcl_tlpt_sq:
		if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
			currplayer_vel_y = 0;
			orbed[currplayer] = 1;
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
	spcl_tlpt_pt:
			high_byte(currplayer_y) = teleport_output;
		}
		return;

	// Alphabet blocks
	spcl_s_block:
		if (dashing[currplayer]){
			dashing[currplayer] = 0; orbed[currplayer] = 1;
		}
		return;
	spcl_h_block: hblocked[currplayer] = 1; return;
	spcl_j_block: jblocked[currplayer] = 1; return;
	spcl_d_block: dblocked[currplayer] = 1; return;
	spcl_f_block: fblocked[currplayer] = 1; return;

	// Coins
	spcl_coin_1:
		if (practice_point_count) return;
		coins |= COIN_1;
		coin1_timer = 1;
		coin1_speed = 0x0200;
		goto spcl_coin_common;

	spcl_coin_2:
		if (practice_point_count) return;
		coins |= COIN_2;
		coin2_timer = 1;
		coin2_speed = 0x0200;
		goto spcl_coin_common;

	spcl_coin_3:
		if (practice_point_count) return;
		coins |= COIN_3;
		coin3_timer = 1;
		coin3_speed = 0x0200;
		// intentional leak
	spcl_coin_common:
		sfx_play(sfx_coin, 0);
		animating = 1;
		return;
	

	// collided with a pad
	spcl_ylw_pad:
		clear_slope_stuff();
		settrailstuff();
		table_offset = yellow_pad;
		currplayer_vel_y = sprite_gamemode_y_adjust();
		//idx8_inc(activesprites_activated, index);	
		return;
	spcl_pinkpad:
		clear_slope_stuff();
		settrailstuff();
		table_offset = pink_pad;
		currplayer_vel_y = sprite_gamemode_y_adjust();
		//idx8_inc(activesprites_activated, index);	
		return;
	spcl_red_pad:
		clear_slope_stuff();
		settrailstuff();
		table_offset = red_pad;
		currplayer_vel_y = sprite_gamemode_y_adjust();
		//idx8_inc(activesprites_activated, index);	
		return;

	spcl_grn_pad:
		invert_gravity(currplayer_gravity);
		if (currplayer_gravity && currplayer_vel_y < 0x670) currplayer_vel_y = 0x670;
		else if (!currplayer_gravity && currplayer_vel_y > -0x670) currplayer_vel_y = -0x670;
		idx8_inc(activesprites_activated, index);
		return;
	
	spcl_gvdn_pd:
		clear_slope_stuff();
		if (!currplayer_gravity) { 
			settrailstuff();
			currplayer_gravity = GRAVITY_UP;				//flip gravity
			currplayer_vel_y = PAD_HEIGHT_BLUE;
			//invincible_counter = 3;
		}
		idx8_inc(activesprites_activated, index);	
		return;
	
	spcl_gvup_pd:
		clear_slope_stuff();
		if (currplayer_gravity) { 	
			settrailstuff();
			currplayer_gravity = GRAVITY_DOWN;				//flip gravity
			currplayer_vel_y = -PAD_HEIGHT_BLUE;
			//invincible_counter = 3;				
		}
		idx8_inc(activesprites_activated, index);	
		return;

	// Spider orbs and pads
	spcl_sporbup:
		if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
	spcl_sppadup:
			high_byte(currplayer_y) -= eject_D;
			currplayer_vel_y = 0;
			currplayer_gravity = GRAVITY_UP;
			crossPRGBankJump0(spider_up_wait);
			high_byte(currplayer_y) -= eject_U;
			currplayer_vel_y = 0;	
			orbed[currplayer] = 1;
			idx8_inc(activesprites_activated, index);
		}
		return;
	spcl_sporbdn:
		if ((cube_data[currplayer] & 2) || controllingplayer->press_a || controllingplayer->press_up) {
			idx8_store(cube_data, currplayer, cube_data[currplayer] & 1);
	spcl_sppaddn:
			high_byte(currplayer_y) -= eject_U + 1;
			currplayer_vel_y = 0;
			currplayer_gravity = GRAVITY_DOWN;
			crossPRGBankJump0(spider_down_wait);
			high_byte(currplayer_y) -= eject_D;
			currplayer_vel_y = 0;
			orbed[currplayer] = 1;
			idx8_inc(activesprites_activated, index);
		}
		return;

	spcl_ylw_orb:
		table_offset = yellow_orb;
		//intentional leak
		goto spcl_orb_cmn;
	spcl_grn_orb:
	#ifdef FLAG_KANDO_FUN_STUFF		
		table_offset = yellow_orb;
		goto spcl_orb_cmn;
	#else
		return;
	#endif

	spcl_ylw_big:
		table_offset = ylw_bigger;
		goto spcl_orb_cmn;

	spcl_ylw_sml:
		table_offset = ylw_smaller;
		goto spcl_orb_cmn;

	spcl_pinkorb:
		table_offset = pink_orb;
		goto spcl_orb_cmn;

	spcl_blckorb:
		table_offset = black_orb;
		goto spcl_orb_cmn;

	spcl_red_orb:
		table_offset = red_orb;
		// intentional leak

	spcl_orb_cmn:
		ufo_orbed = 1;			
		if (gamemode == GAMEMODE_CUBE || gamemode == GAMEMODE_BALL || gamemode == GAMEMODE_ROBOT || gamemode == GAMEMODE_NINJA || gamemode == GAMEMODE_SPIDER || gamemode >= GAMEMODE_SWING) {
			sprite_gamemode_main();
		} else {
			sprite_gamemode_controller_check();
		}
		return;
}

#undef table_offset
#undef collided

void sprite_collide(){
	if (gamemode != GAMEMODE_WAVE) {
		Generic.width = currplayer_mini ? MINI_CUBE_WIDTH : CUBE_WIDTH;
		Generic.height = currplayer_mini ? MINI_CUBE_HEIGHT : CUBE_HEIGHT; 
	} else {
		Generic.width = currplayer_mini ? MINI_WAVE_WIDTH : WAVE_WIDTH;
		Generic.height = currplayer_mini ? MINI_CUBE_HEIGHT : CUBE_HEIGHT;
	}

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
					
					if (tmp4 == 0x9F) {
						pal_col(0, color1);
						pal_col(1, oneShadeDarker(color1)); 
						pal_col(9, oneShadeDarker(color1)); 
						lastbgcolortype = tmp4;
					}						
					
					else if (tmp4 == 0xAE) {
						pal_col(6, color2);
						pal_col(5, oneShadeDarker(color2)); 
						lastgcolortype = tmp4;
					}
					else if (tmp4 >= 0xC0){
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

					if (tmp4 == 0xAF) outline_color = color1;
					else outline_color = idx8_load(OUTLINES, tmp4 & 0x0F);
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
	if (gamemode != GAMEMODE_WAVE) {
		Generic.width = currplayer_mini ? MINI_CUBE_WIDTH : CUBE_WIDTH; 
	} else {
		Generic.width = currplayer_mini ? MINI_WAVE_WIDTH : WAVE_WIDTH;
	}
	Generic.height = currplayer_mini ? MINI_CUBE_HEIGHT : CUBE_HEIGHT;
}


void settrailstuff() {
	if (forced_trails != 2 && !orbactive) {
		orbactive = 1;
	}
}

void retrofireballclear() {
	if (retro_mode) {
		memfill(jimsheatballalive, 0, sizeof(jimsheatballalive));		
	}
}			

void dual_cap_check() {
	if (dual && !twoplayer) {
		if (currplayer == 0) {
			if (player_vel_y[1] > 0x250) player_vel_y[1] = 0x250;
			if (player_vel_y[1] < -0x250) player_vel_y[1] = -0x250;
		}
		else {
			if (player_vel_y[0] > 0x250) player_vel_y[0] = 0x250;
			if (player_vel_y[0] < -0x250) player_vel_y[0] = -0x250;
		}					
	}
}				

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
