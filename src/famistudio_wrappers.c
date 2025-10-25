static uint8_t music_bank;
//uint8_t prev_bank;
uint8_t current_bank, song_count;

/*__attribute__((noinline, retain)) 
void music_play(volatile uint8_t song) {
    __attribute__((leaf)) __asm__ volatile (
        "jsr _music_play \n"
        :
        :"a"(s)
        :"x","y","p"
    );
}*/

#define play_song_zero() \
__attribute__((leaf)) __asm__ volatile ( \
    "lda #0 \n" \
    "jsr music_play \n" \
    : \
    : \
    :"a","x","y","p" \
);

__attribute__((noinline, retain)) 
    void music_play(uint8_t s){
    
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
        "clc \n"// set borrow, due to the export
                // script not accounting for the
                // dpcm aligner
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

    __attribute__((leaf)) __asm__ volatile (
        "pla \n"
        "jsr set_prg_a000 \n"
        :
        :
        :"a","x","y","p"
    );
}

__attribute__((noinline)) void music_update(){
    uint8_t prev_bank = get_prg_a000();
    set_prg_a000(music_bank);
    famistudio_update();
    set_prg_a000(prev_bank);
}

__attribute__((noinline)) void sfx_play(uint8_t index, uint8_t channel){
    uint8_t prev_bank = get_prg_a000();
    set_prg_a000(sfx_bank);
    famistudio_sfx_init(0xa000);
    famistudio_sfx_play(index,channel);
    set_prg_a000(prev_bank);
}

