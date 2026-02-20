void state_game() {
    se_play_sample((pcm_playsound_01+0x2000),sample_bank_2,1);
    __asm__("cli");
    //se_wait_frames(20);

    //se_vram_donut_decompress();




    se_turn_on_rendering();
    //se_fade_palette_to(0,4);
    se_set_palette_brightness_all(4);

    while(1){
        se_wait_vsync();

        if(joypad1.press_b) {gamestate = 0xff; break;}
    }
}