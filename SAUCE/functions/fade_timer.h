
CODE_BANK_PUSH("XCD_BANK_00")

void check_fade_timer(){
    if (gnd_palette_transition_timer > 0) {
        gnd_palette_transition_timer--;
        swapbyte(PAL_BUF[original_gnd_palette_idx_0], original_gnd_palette_color_0);
        swapbyte(PAL_BUF[original_gnd_palette_idx_1], original_gnd_palette_color_1);
    }
    if (bg_palette_transition_timer > 0) {
        bg_palette_transition_timer--;
        swapbyte(PAL_BUF[original_bg_palette_idx_0], original_bg_palette_color_0);
        swapbyte(PAL_BUF[original_bg_palette_idx_1], original_bg_palette_color_1);
        swapbyte(PAL_BUF[original_bg_palette_idx_2], original_bg_palette_color_2);
    } 
}

CODE_BANK_POP()
