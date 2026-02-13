// the lifeblood of the engine. don't remove these lines.
#include <nes.h>


#include "sniperengine/sniperengine.h"
#include "ines_header.h"
#include "assets.c"
#include "ram.h"

#include "funny_custom_routines.h"
#include "physics.h"
#include "parallax.c"

#include "state_startup.c"
#include "state_menu.c"


int main(void) {
    PPU.control = se_ppu_ctrl_var = 0b10100000;
    PPU.mask = se_ppu_mask_var = 0b00000110;
    PPU.status;
    se_init(1); // byte passed indicates A12 inversion value

    //disable_irq();

    // clear oam buffer
    se_clear_sprites();

    se_set_palette_brightness_all(0);

    set_prg_a000(music_bank_0);
    famistudio_init(1,0xa000);

    se_post_nmi_ptr = se_music_update;

    se_clear_palette();

    while(1){
        __asm__("sei");
        se_set_palette_brightness_all(0);
        se_turn_off_rendering();
        se_clear_sprites();
        se_memory_fill(se_irq_table,0,32);
        __asm__("dec se_irq_table");
        set_chr_bank(0,0);
        set_chr_bank(1,2);
        set_chr_bank(2,4);
        set_chr_bank(3,5);
        set_chr_bank(4,6);
        set_chr_bank(5,7);

        switch (gamestate){

            // when in doubt, go back to startup
            default:
                jsrfar_noargs(startup_bank, state_startup);
                break;

            //
            //  CREDITS STUFF
            //
            case 0x01:
                jsrfar_noargs(startup_bank, state_credits);
                break;

            //
            //  MENU-RELATED STUFF
            //
            case 0x10:
                jsrfar_noargs(startup_bank, state_menu);
                break;

            case 0xff:
                jsrfar_noargs(60,thegreet_message);
                break;
        }
        //se_post_nmi_ptr = nofunction;
        se_irq_ptr = nofunction;
        se_irq_table[0]=255;
        se_irq_table[1]=60; // location 0x60 (rts)
        se_irq_table[2]=81; // of the identity table
    }
}