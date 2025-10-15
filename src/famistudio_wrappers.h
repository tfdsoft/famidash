static unsigned char music_bank;
//unsigned char prev_bank;
unsigned char current_bank, song_count;

void music_play(unsigned char s){
    
    unsigned char prev_bank = get_prg_a000();
    current_bank = music_bank_0;
    song_count = 0;

    // ok so we need to figure out what bank the
    // requested song is in.

    set_prg_a000(current_bank);
    __attribute__((leaf)) __asm__ volatile (
        "tsx \n"
        "1: \n" // bank_loop
        "pha \n"
        "sec \n"
        "sbc $a000 \n"
        "bcc 1f \n"
        "txs \n"
        "tay \n"
        "inc __prg_a000 \n"
        "lda __prg_a000 \n"
        "jsr set_prg_a000 \n"
        "tsx \n"
        "tya \n"
        "sec \n"
        "bcs 1b \n"
        "1: \n"
        "pla \n"
        "ldx __prg_a000 \n"
        :"=a"(song_count),"=x"(music_bank)
        :"a"(s)
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

void sfx_play(unsigned char index, unsigned char channel){
    unsigned char prev_bank = get_prg_a000();
    set_prg_a000(sfx_bank);
    famistudio_sfx_init(0xa000);
    famistudio_sfx_play(index,channel);
    set_prg_a000(prev_bank);
}