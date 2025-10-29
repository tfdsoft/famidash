#include "irq.h"


void setup_basic_interrupt(uint8_t reload_value, void* func_ptr){
    // it would be *really* unfortunate if an interrupt
    // fired while we were still setting it up, so let's
    // disable them on the cpu side...
    __asm__("sei");

    irq_reload_value = reload_value;
    irq_ptr = func_ptr;

    // ...and then re-enable once finished.
    __asm__("cli");
}