__attribute__((interrupt)) void nmi(){
    // oh yeah just a heads up:
    // llvm-mos needs to push EVERY. SINGLE.
    // VIRTUAL. REGISTER.
    // this is gonna take almost a full scanline
    // to do, so whatever you put in here
    // needs to be extra speedy.


    PPU.mask = 0; // disable rendering

    // send the sprites in!
    PPU.sprite.address = 0x00;
    APU.sprite.dma = 0x02;
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

        PPU.vram.data = PAL_BG_PTR[PAL_BUF[0]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[5]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[6]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[7]];

        PPU.vram.data = PAL_BG_PTR[PAL_BUF[0]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[9]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[10]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[11]];

        PPU.vram.data = PAL_BG_PTR[PAL_BUF[0]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[13]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[14]];
        PPU.vram.data = PAL_BG_PTR[PAL_BUF[15]];
    }

    //
    // everything else i need
    // goes below here...
    //








    PPU.status; // read ppu status. thanks llvm-mos!
    PPU.scroll = SCROLL_X;
    PPU.scroll = SCROLL_Y;
    PPU.control = PPU_CTRL_VAR;
    
    FRAME_COUNT_NOW++; // increase frame count
    PPU.mask = PPU_MASK_VAR; // re-set PPU.mask
}
