__attribute__((retain)) unsigned char chr_load_in_progress;

__attribute__((noinline)) void donut_decompress_vram(const uint8_t * data, uint8_t bank){
    
    __attribute__((leaf)) __asm__ volatile (
        "lda __prg_a000 \n"
        "pha \n"
        "txa \n"
        "jsr set_prg_a000 \n"
        :
        :"x"(bank)
        :"a","y","p"
    );
    
    __attribute__((leaf)) __asm__ volatile (
        "stx __rc2 \n"
        "sty __rc3 \n" // high byte will never be zero
        "sty chr_load_in_progress \n"
        "jsr donut_block \n"
        "lda #0 \n"
        "sta chr_load_in_progress \n"

        "pla \n"
        "jsr set_prg_a000"
        :
        :"x"(low_byte(data)),"y"(high_byte(data))
        :"a","p","rc2","rc3"
    );
}