unsigned char automatic_fs_updates = 0;
unsigned char nmi_prev_bank;

__attribute__((interrupt_norecurse)) void nmi(){
    
    // oh yeah just a heads up:
    // llvm-mos needs to push EVERY. SINGLE.
    // VIRTUAL. REGISTER.
    // this is gonna take almost a full scanline
    // to do, so whatever you put in here
    // needs to be extra speedy.

    
    // if rendering is off, do not access vram
    if ((PPU_MASK_VAR & 0b00011000)) {

        // send the sprites in!
        //PPU.sprite.address = 0x00;
        //APU.sprite.dma = 0x02;
        // why ricoh put the OAM DMA register on 
        // the APU and not the PPU is beyond me

        // send the palette in!
        if(PAL_UPDATE){
            PAL_UPDATE = 0;

            PPU.status;
            PPU.vram.address = 0x3f;
            PPU.vram.address = 0x00;
            
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


            PPU.vram.data = PAL_BG_PTR[PAL_BUF[0]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[17]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[18]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[19]];

            PPU.vram.data = PAL_BG_PTR[PAL_BUF[20]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[21]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[22]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[23]];

            PPU.vram.data = PAL_BG_PTR[PAL_BUF[24]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[25]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[26]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[27]];

            PPU.vram.data = PAL_BG_PTR[PAL_BUF[28]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[29]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[30]];
            PPU.vram.data = PAL_BG_PTR[PAL_BUF[31]];
        }

         
        //
        // everything else i need
        // goes below here...
        //

        
        
        oam_and_readjoypad();
        //PPU.status; // read ppu status. thanks llvm-mos!
        //PPU.scroll = SCROLL_X;
        //PPU.scroll = SCROLL_Y;
        //PPU.control = PPU_CTRL_VAR;
    }
    PPU.mask = PPU_MASK_VAR; // re-set PPU.mask
    FRAME_CNT++; // increase frame count
    
    //pad_poll(0);
    //bruh.joemom++; 

    
    if(automatic_fs_updates) {
        nmi_prev_bank = get_prg_a000();
        //__attribute__((leaf)) __asm__ volatile (
        //    "lda __prg_a000 \n"
        //    "pha \n"
        //);
        music_update();
        //__attribute__((leaf)) __asm__ volatile (
        //    "pla \n"
        //    "jsr set_prg_a000 \n"
        //);
        set_prg_a000(nmi_prev_bank);
    }

}




//__attribute__((interrupt_norecurse)) void irq(){
//
//}