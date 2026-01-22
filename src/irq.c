#include "irq.h"

__attribute__((noinline)) void flush_irq(){
    __asm__("sei \n nop \n");

    // we don't want interrupts firing while writing to
    // the table, so disable them
    irq_table[0] = 255;
    irq_count = 0;
    
    ppu_wait_nmi();
}

void disable_irq(){
    __asm__("sei \n nop \n");
    IRQ_DISABLE = 0;
}

void enable_irq(){
    __asm__("cli");
    //PPU.control = PPU_CTRL_VAR;
    ppu_wait_nmi();
}


__attribute__((noinline)) void add_basic_interrupt(
    uint8_t reload_value, void* func_ptr
){
    IRQ(irq_count).reload = reload_value;
    IRQ(irq_count).func_ptr = func_ptr;

    // reload value of 255 to catch the last interrupt
    IRQ((irq_count+1)).reload = 255;

    irq_count++;
}

__attribute__((noinline)) void add_advanced_interrupt(
    uint8_t reload_value, void* func_ptr, uint32_t args
){
    IRQ(irq_count).reload = reload_value;
    IRQ(irq_count).func_ptr = func_ptr;
    IRQ(irq_count).arg0 = low_byte(args);
    IRQ(irq_count).arg1 = high_byte(args);
    IRQ(irq_count).arg2 = third_byte(args);

    // reload value of 255 to catch the last interrupt
    IRQ((irq_count+1)).reload = 255;

    irq_count++;
}