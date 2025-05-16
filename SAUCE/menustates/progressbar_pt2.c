// To be merged into progressbar.c

#define BAR_TILES 20
#define CENTER_TILES BAR_TILES - 2
#define BAR_MAX 100
#define NUMBER_PER_TILES BAR_MAX / BAR_TILES
void draw_progress_bar() {
	#define nametable_A !(level & 1)
	
	drawBarFlag--;

	if (tmp7 >= NUMBER_PER_TILES) {
		if (nametable_A) {
			one_vram_buffer(0x8c, NTADR_A(tmp1, tmp2));
		} else {
			one_vram_buffer(0x8c, NTADR_B(tmp1, tmp2));
		}
		high_byte(tmp6) = (tmp7 >= BAR_MAX ? BAR_MAX - NUMBER_PER_TILES : tmp7);

		
		high_byte(tmpA) = 0;
		do {
			high_byte(tmp6) -= NUMBER_PER_TILES;
			high_byte(tmpA) += 1;
		} while (high_byte(tmp6) >= NUMBER_PER_TILES);
		
		if (nametable_A) {
			one_vram_buffer_horz_repeat(0x6b, high_byte(tmpA), NTADR_A(tmp1 + 1, tmp2));
			one_vram_buffer_horz_repeat(0x02, BAR_TILES - high_byte(tmpA), NTADR_A(tmp1 + high_byte(tmpA), tmp2));
		} else {
			one_vram_buffer_horz_repeat(0x6b, high_byte(tmpA), NTADR_B(tmp1 + 1, tmp2));
			one_vram_buffer_horz_repeat(0x02, BAR_TILES - high_byte(tmpA), NTADR_B(tmp1 + high_byte(tmpA), tmp2));
		}
	} else {
		if (nametable_A) {
			one_vram_buffer(0x7c, NTADR_A(tmp1, tmp2));
			one_vram_buffer_horz_repeat(0x02, CENTER_TILES, NTADR_A(tmp1 + 1, tmp2));
		} else {
			one_vram_buffer(0x7c, NTADR_B(tmp1, tmp2));
			one_vram_buffer_horz_repeat(0x02, CENTER_TILES, NTADR_B(tmp1 + 1, tmp2));
		}
	}
	
	if (tmp7 >= BAR_MAX) {
		if (nametable_A) {
			one_vram_buffer(0x8d, NTADR_A(tmp1 + (BAR_TILES - 1), tmp2));
		} else {
			one_vram_buffer(0x8d, NTADR_B(tmp1 + (BAR_TILES - 1), tmp2));
		}
	} else {
		if (nametable_A) {
			one_vram_buffer(0x7d, NTADR_A(tmp1 + (BAR_TILES - 1), tmp2));
		} else {
			one_vram_buffer(0x7d, NTADR_B(tmp1 + (BAR_TILES - 1), tmp2));
		}
	}
	#undef nametable_A
}

#define TOTAL_PIXELS 8 * BAR_TILES // 8 * 20 = 160
#define PIXELS_PER_UNIT (TOTAL_PIXELS * 10) / (BAR_MAX) // (1600 / 100) = 1.6 | multiplied by 10 because of no floats
#define PIXELS_PER_PERCENTAGE (PIXELS_PER_UNIT * 256) / 10 // 1.6 * 256 = 409.6

void calculate_sprite_pos() {
	high_byte(tmp5) = tmp1;
	low_byte(tmp5) = 0;
	tmp3 = 1;

	if (tmp7 != 0) {
		do {
			tmp3++;
			tmp5 += PIXELS_PER_PERCENTAGE;
		} while (tmp3 < tmp7);
	}

	tmp1 = high_byte(tmp5);
}