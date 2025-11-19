#include "assets.h"

#include "include.h"

__attribute__((leaf)) __asm__(
    ".section .init.100,\"ax\",@progbits \n"
    ".globl clearRAM \n"
    "clearRAM: \n"
        "lda #0 \n"
        "tax \n"
    "1: \n"
        "sta  $00,x \n"
        "sta $100,x \n"
        "sta $200,x \n"
        "sta $300,x \n"
        "sta $400,x \n"
        "sta $500,x \n"
        "sta $600,x \n"
        "sta $700,x \n"
        "inx \n"
        "bne 1b \n"

    // end of clearRAM

    ".section .init.280,\"ax\",@progbits \n"
        "lda #0 \n"
        "sta __rc2 \n"
        "sta __rc3 \n"
        "jsr set_vram_buffer \n"

    ".section .init.300,\"ax\",@progbits \n"
        // make sure the irq doesn't trigger itself
        "lda #255 \n"
        "sta irq_table+0 \n"
        "sta irq_table+6 \n"
        
        "lda #<irq_basic \n"
        "ldx #>irq_basic \n"
        "sta irq_table+1 \n"
        "stx irq_table+2 \n"
        "sta irq_table+7 \n"
        "stx irq_table+8 \n"

        "lda #$37 \n"
        "jsr set_prg_a000 \n"

        "lda #$01 \n"
        "tax \n"
        "dex \n"
        "ldy #$a0 \n"
        "jsr famistudio_init \n"

        "lda #$c0\n"
        "sta $4017\n" // disable apu frame counter irq



        //"ldx #$00 \n"
        //"tax \n"
        //"dex \n"
        //"ldy #$a0 \n"
        //"jsr famistudio_sfx_init \n"
);

int main(void){

    PPU.control = PPU_CTRL_VAR = 0b10100000;
    PPU.mask = PPU_MASK_VAR = 0b00000110;
    ppu_off(); // turn off everything

    disable_irq();

    // clear oam buffer
    oam_clear();

    // clear palette
    //pal_bg((const char *)0x120);
    pal_bright(0);
    
    set_chr_a12_inversion(CHR_A12_INVERT);

    // clear chr
    set_chr_default();
    vram_adr(0x0000);
    vram_fill(0,0x2000);

    banked_call(extra_code_bank, state_ramcheck); 

    set_vram_buffer();

    ppu_on_spr();

    set_wram_mode(WRAM_ON);

    loaded_bg_set = 0xff;
    loaded_g_set = 0xff;
    background_set = ground_set = 0;


    while(1){
        __asm__("sei");
        pal_bright(0);
        ppu_off();
        oam_clear();
        set_chr_default();
        flush_irq();
        vram_adr(0);

        switch(gamestate){
            // when in doubt, go back to startup
            default: 
                banked_call(extra_code_bank, state_startup); 
                //state_startup();
                break;

            //
            //  CREDITS-RELATED STUFF
            //
            case 0x00:
                banked_call(extra_code_bank, state_credits);
                //state_menu();
                break;
                
            //
            //  MENU-RELATED STUFF
            //
            case 0x10:
                banked_call(extra_code_bank, state_menu);
                break;
            case 0x11:
                banked_call(extra_code_bank, state_levelselect);
                break;

            case 0x14:
                banked_call(sound_test_bank, state_soundtest);
                break;

            //
            //  GAME-RELATED STUFF
            //  (in prg_rom_fixed_lo, do not use banked_call())
            //
            case 0x20:
                state_game();
                break;

            //
            //  DEBUG STUFF
            //
            /*case 0xf0:
                banked_call(extra_code_bank, state_bankexplorer);
                break;*/
        }
    }
    //APU.sprite.dma;
}