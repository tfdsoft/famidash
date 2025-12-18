static uint8_t music_bank;
//uint8_t prev_bank;
uint8_t current_bank, song_count;
extern uint8_t famistudio_song_speed;

__attribute__((noinline)) void music_play(uint8_t s){
    
    __attribute__((leaf)) __asm__ volatile (
        "lda __prg_a000 \n"
        "pha"
        :
        :
        :"a","x","y","p"
    );

    //uint8_t prev_bank = get_prg_a000();
    current_bank = music_bank_0;
    song_count = 0;

    // ok so we need to figure out what bank the
    // requested song is in.
    set_prg_a000(current_bank);

    //if(s > 0){
    if(s == 255) s++;
    
    __attribute__((leaf)) __asm__ volatile (

        "1: \n" // bank_loop
        "tsx \n"
        "pha \n"
        "sec \n"
        "sbc $a000 \n"
        
        //"clc\n" // add 1 since the exporter doesn't
        //"adc #$01\n" // account for the dpcm aligner

        "bcc 1f \n"
        "txs \n"
        "tay \n"
        "inc __prg_a000 \n"
        "lda __prg_a000 \n"
        "jsr set_prg_a000 \n"
        "tya \n"

        "sec \n"
        "bcs 1b \n" // bra

        "1: \n"
        "pla \n"
        "ldx __prg_a000 \n"

        :"=a"(song_count),"=x"(music_bank)
        :"a"(s)
        :"y","p"
    );
        //famistudio_init(1,0xa000);
        //famistudio_music_play(song_count);
    /*} else {
        song_count = 0;
        //famistudio_init(1,0xa000);
        //famistudio_music_play(0);
    }*/
    
    famistudio_init(1,0xa000);
    famistudio_music_play(song_count);

    pop_prg_a000();
}

__attribute__((noinline)) void music_update(){
    push_prg_a000();
    set_prg_a000(music_bank);
    famistudio_update();
    pop_prg_a000();
}

__attribute__((noinline)) void sfx_play(uint8_t index, uint8_t channel){
    push_prg_a000();
    set_prg_a000(sfx_bank);
    famistudio_sfx_init(0xa000);
    famistudio_sfx_play(index,channel);
    pop_prg_a000();
}

