#include "irq.h"


void setup_basic_interrupt(uint8_t reload_value, void* func_ptr){
    // it would be *really* unfortunate if an interrupt
    // fired while we were still setting it up, so let's
    // disable them.
    __asm__("sei");

    irq_reload_value = reload_value;
    irq_ptr = func_ptr;

    __asm__("cli");
}

void setup_advanced_interrupt(
    uint8_t reload_value, void* func_ptr, uint32_t args){

    // it would be *really* unfortunate if an interrupt
    // fired while we were still setting it up, so let's
    // disable them.
    __asm__("sei");

    irq_reload_value = reload_value;
    irq_ptr = func_ptr;

    irq_args = args;

    __asm__("cli");
}