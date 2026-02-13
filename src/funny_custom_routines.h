/*
 *  CUSTOM FUNCTION HEADER
 *  for any custom library functions you write in assembly,
 *  make sure it has a prototype here. the compiler will
 *  find it in your .s file, and let you use it in your C
 *  code. 
*/


// IRQ ONLY: DO NOT CALL
void custom_irq_that_updates_scroll();
void custom_irq_that_updates_chr_bank();
void custom_irq_that_updates_chr_and_x_scroll();