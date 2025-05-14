

void draw_progress_bar();
void draw_full_progress_bar();
void draw_percentage();

/*
	all 8 bit tmps:

	tmp1 : x
	tmp2 : y
	tmp3 : offset into sprite table
	tmp4 : needed inside the transitions
	tmp7 : percentage
	
	free 8 bit tmps inside calls:
	- tmp8
	damn...

	technically i can use the low byte of 16 bits tmps
*/
void draw_both_progress_bars() {
	
		// Normal level completeness stuff
		tmp7 = level_completeness_normal[level];
		hexToDec(tmp7);
		tmp1 = 112;		// x
		if (tmp4) {
			tmp1 += tmp8 + 1;
		} else {
			tmp1 -= tmp8;
		}
		
		tmp2 = 127;		// y
		tmp3 = 0;		// offset
		draw_percentage();	

		tmp1 = 6; 		// x
		tmp2 = 16;		// y
		low_byte(tmp6) = 1; 		// index
		draw_full_progress_bar();
		
	
		// Practice level completeness stuff
		tmp7 = level_completeness_practice[level];
		hexToDec(tmp7);
		tmp1 = 112;		// x
		if (tmp4) {
			tmp1 += tmp8 + 1;
		} else {
			tmp1 -= tmp8;
		}
		tmp2 = 151;		// y
		tmp3 = 0;		// offset
		draw_percentage();	

		tmp1 = 6; 		// x
		tmp2 = 19;		// y
		low_byte(tmp6) = 2; 		// index
		draw_full_progress_bar();

		
}
void calculate_sprite_pos();
void draw_bar_sprites() {
	#define temp_save animating
	// Put percentage mask
	tmp3 = 0;
	tmp1--; // left 1 tile

	// convert tile cords into sprite cords (basically multiply by 8 aka shift left 3 times)
	tmp1 = (tmp1 << 3) + 1;
	temp_save = tmp1;
	tmp2 = (tmp2 << 3) - 1;
	if (tmp4) {
		tmp1 += tmp8 + 1;
	} else {
		tmp1 -= tmp8;
	}
	crossPRGBankJump0(put_progress_bar_sprite);
	tmp1++;
	tmp3 = 3;
	crossPRGBankJump0(put_progress_bar_sprite);

	tmp1 = 206;
	if (tmp4) {
		tmp1 += tmp8 + 1;
	} else {
		tmp1 -= tmp8;
	}
	tmp3 = 4;
	crossPRGBankJump0(put_progress_bar_sprite);
	tmp1 = temp_save;
	crossPRGBankJump0(calculate_sprite_pos);
	
	if (tmp4) {
		tmp1 += tmp8 + 1;
	} else {
		tmp1 -= tmp8;
	}
	
	tmp3 = low_byte(tmp6);
	crossPRGBankJump0(put_progress_bar_sprite);
	temp_save = 0;
}

void draw_full_progress_bar() {
	if (drawBarFlag) crossPRGBankJump0(draw_progress_bar);
	// end tmp3 need

	// tmp5 is now used for the temporary sprite x pos with subpixels
	draw_bar_sprites();
	// end tmp5 usage
}

void draw_level_progress() {
	update_level_completeness();
	hexToDec(__A__);
	tmp1 = 116;		// x
	tmp2 = 0;		// y
	tmp3 = 25;		// offset
	draw_percentage();	
}

void draw_percentage() {
	if (hexToDecOutputBuffer[2]) { 				  
		high_byte(tmp6) = hexToDecOutputBuffer[2]; // number
		crossPRGBankJump0(put_number);
	}

	if (hexToDecOutputBuffer[2] | hexToDecOutputBuffer[1]) {
		tmp1 += 8;					    		   // x
		high_byte(tmp6) = hexToDecOutputBuffer[1]; // number
		crossPRGBankJump0(put_number);
	}

	tmp1 += 8;					   			   // x
	high_byte(tmp6) = hexToDecOutputBuffer[0]; // number
	crossPRGBankJump0(put_number);

	tmp1 += 8;					    // x
	high_byte(tmp6) = 10; 			// percentage
	crossPRGBankJump0(put_number);
}
