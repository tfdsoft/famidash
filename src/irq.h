#define IRQ_LATCH   (*(unsigned char*) 0xc000)
#define IRQ_RELOAD  (*(unsigned char*) 0xc001)
#define IRQ_DISABLE (*(unsigned char*) 0xe000)
#define IRQ_ENABLE  (*(unsigned char*) 0xe001)

extern void *irq_ptr;
extern uint8_t irq_reload_value, irq_count;

extern void irq_basic();