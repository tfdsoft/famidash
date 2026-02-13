#include "famistudio_llvmmos.h"

extern u8 se_music_bank;

__attribute__((noinline)) void se_music_play(u8 s){
    
    //push_prg_a000();
    __asm__(
        "lda __prg_a000 \n"
        "pha \n"
    );

    //u8 prev_bank = get_prg_a000();
    //current_bank = music_bank_0;
    u8 song_count = 0;

    // ok so we need to figure out what bank the
    // requested song is in.
    set_prg_a000(music_bank_0);

    //if(s > 0){
    //s++;
    
    __attribute__((leaf)) __asm__ volatile (

        "1: \n" // bank_loop
            "tsx \n"
            "pha \n"
            "sec \n"
            "sbc $a000 \n"

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

        :"=a"(song_count),"=x"(se_music_bank)
        :"a"(s)
        :"y","p"
    );
    
    famistudio_init(1,0xa000);
    famistudio_music_play(song_count);

    __asm__(
        "pla \n"
        "jsr set_prg_a000 \n"
    );
}

__attribute__((noinline)) void se_music_update(){
    __asm__(
        "lda __prg_a000 \n"
        "pha \n"
    );
    set_prg_a000(se_music_bank);
    famistudio_update();
    __asm__(
        "pla \n"
        "jsr set_prg_a000 \n"
    );
}

__attribute__((noinline)) void se_sfx_play(u8 index, u8 channel){
    __asm__(
        "lda __prg_a000 \n"
        "pha \n"
    );
    set_prg_a000(61);
    famistudio_sfx_init(0xa000);
    famistudio_sfx_play(index,channel);
    __asm__(
        "pla \n"
        "jsr set_prg_a000 \n"
    );
}

