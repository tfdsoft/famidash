
banked(fixed.func)
__attribute__((noinline))
void unpack_icon_firstframe(const u8* data, u8 bank){

    
    __attribute__((leaf)) __asm__ volatile(
        "tax \n"
        "lda __prg_a000 \n"
        "pha \n"
        "txa \n"
        "jsr set_prg_a000 \n"

        "ldx #0 \n"
        "jsr donut_decompress_block \n"
        :
        :"a"(bank),[addr]"r"(data)
        :"x","y","p","rc5","rc6","rc7","rc8","rc9","rc10","rc11","rc12","rc13","rc14","rc15","rc16","rc17","rc18","rc19","rc20"
    );

    for(u8 i=0; i<64; i++){
        PPU.vram.data = ((u8*)0x110)[i];
    }

    __attribute__((leaf)) __asm__ volatile(
        "pla \n"
        "jsr set_prg_a000 \n"
    );
}