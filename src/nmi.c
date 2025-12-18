__attribute__((retain)) unsigned char automatic_fs_updates = 0;
unsigned char nmi_in_progress;


// TODO: convert this to asm


__attribute__((interrupt_norecurse)) void nmi(){
    nmi_in_progress++;
    // oh yeah just a heads up:
    // llvm-mos needs to push EVERY. SINGLE.
    // VIRTUAL. REGISTER.
    // this is gonna take almost a full scanline
    // to do, so whatever you put in here
    // needs to be extra speedy.
    
    
    // if rendering is off, do not access vram
    if ((PPU_MASK_VAR & 0b00011000)) {
        // send the palette in!
        if(VRAM_UPDATE){
            PPU.mask=0;
            if(PAL_UPDATE){
                PAL_UPDATE = 0;

                PPU.status;
                PPU.vram.address = 0x3f;
                PPU.vram.address = 0x00;
                
                // unrolled for THE SPEED
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[0]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[1]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[2]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[3]];

                PPU.vram.data = PAL_BG_PTR[PAL_BUF[4]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[5]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[6]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[7]];

                PPU.vram.data = PAL_BG_PTR[PAL_BUF[8]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[9]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[10]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[11]];

                PPU.vram.data = PAL_BG_PTR[PAL_BUF[12]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[13]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[14]];
                PPU.vram.data = PAL_BG_PTR[PAL_BUF[15]];


                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[0]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[17]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[18]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[19]];

                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[20]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[21]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[22]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[23]];

                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[24]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[25]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[26]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[27]];

                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[28]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[29]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[30]];
                PPU.vram.data = PAL_SPR_PTR[PAL_BUF[31]];
            }

            if(NAME_UPD_ENABLE){
                VRAM_UPDATE = 0;
                flush_vram_update2();
            }

            PPU.vram.address = 0;
            PPU.vram.address = 0;

            PPU.status; // read ppu status. thanks llvm-mos!
            PPU.scroll = SCROLL_X;
            PPU.scroll = SCROLL_Y;
            PPU.control = PPU_CTRL_VAR;
            PPU.mask = PPU_MASK_VAR; // re-set PPU.mask
            oam_and_readjoypad();
        }

        
        irq_count = 0;
        irq_table_offset = 0;
        IRQ_DISABLE = 0;
        IRQ_LATCH = irq_table[0];
        IRQ_RELOAD = irq_table[0];
        IRQ_ENABLE = irq_table[0];
        PPU.status;
        __attribute__((leaf))__asm__ volatile ("cli");
    }
    PPU.mask = PPU_MASK_VAR; // re-set PPU.mask
    FRAME_CNT++; // increase frame count

    __attribute__((leaf))__asm__ volatile(
        "lda automatic_fs_updates \n"
        "beq 1f \n" // skip the following check if false

        "lda #0 \n"
        "sta automatic_fs_updates \n"
        "lda __prg_a000 \n"
        "pha \n"
        "jsr music_update \n"
        "pla \n"
        "sta __prg_a000 \n"
        "jsr set_prg_a000 \n"
        "inc automatic_fs_updates \n"

        "1: \n"
    );
    
    /*if(automatic_fs_updates) {
        push_prg_a000();
        automatic_fs_updates = 0;
        //music_update();
        automatic_fs_updates++;
        pop_prg_a000();
    }*/

}




//__attribute__((interrupt_norecurse)) void irq(){
//
//}