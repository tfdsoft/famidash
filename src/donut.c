__attribute__((retain)) unsigned char chr_load_in_progress;

__attribute__((noinline)) void donut_decompress_vram(const uint8_t * data, uint8_t bank){
    
    push_prg_a000();
    set_prg_a000(bank);
    
    __attribute__((leaf)) __asm__ volatile (
        "stx __rc2 \n"
        "sty __rc3 \n" // high byte will never be zero
        "sty chr_load_in_progress \n"
        "jsr donut_block \n"
        "lda #0 \n"
        "sta chr_load_in_progress \n"
        :
        :"x"(low_byte(data)),"y"(high_byte(data))
        :"a","p","rc2","rc3"
    );

    pop_prg_a000();
}