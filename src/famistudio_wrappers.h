static unsigned char music_bank;

void music_play(unsigned char song){
    
    unsigned char prev_bank = get_prg_a000();
    unsigned char current_bank = music_bank_0;
    unsigned char song_count = 0;

    // ok so we need to figure out what bank the
    // requested song is in.

    set_prg_a000(current_bank);
    __attribute__((leaf)) __asm__ volatile (
        "tsx \n"
        ".bank_loop: \n"
        "pha \n"
        "sec \n"
        "sbc $a000 \n"
        "bcc .found_bank \n"
        "txs \n"
        "tay \n"
        "inc __prg_a000 \n"
        "lda __prg_a000 \n"
        "jsr set_prg_a000 \n"
        "tya \n"
        "sec \n"
        "bcs .bank_loop \n"
        ".found_bank: \n"
        "pla \n"
        "ldx __prg_a000 \n"
        :"=a"(song_count),"=x"(music_bank)
        :"a"(song)
        :"y","p"
    );
    famistudio_init(1,0xa000);
    famistudio_music_play(song_count);
    
    set_prg_a000(prev_bank);
}

void music_update(){
    unsigned char prev_bank = get_prg_a000();
    set_prg_a000(music_bank);
    famistudio_update();
    set_prg_a000(prev_bank);
}