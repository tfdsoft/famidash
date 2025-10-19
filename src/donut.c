__attribute__((retain)) unsigned char chr_load_in_progress;

__attribute__((noinline)) void donut_decompress_vram(const uint8_t * data){
    __attribute__((leaf)) __asm__ volatile (
        "sta __rc2 \n"
        "stx __rc3 \n" // x will never be zero
        "stx chr_load_in_progress \n"
        "jsr donut_block \n"
        "lda #0 \n"
        "sta chr_load_in_progress"
        :
        :"a"(low_byte(data)),"x"(high_byte(data))
        :"y","p","rc2","rc3"
    );
}