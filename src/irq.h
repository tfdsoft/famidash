#define IRQ_LATCH   (*(unsigned char*) 0xc000)
#define IRQ_RELOAD  (*(unsigned char*) 0xc001)
#define IRQ_DISABLE (*(unsigned char*) 0xe000)
#define IRQ_ENABLE  (*(unsigned char*) 0xe001)

struct __irq_table {
    uint8_t reload;
    uint8_t *func_ptr;
    uint8_t arg0;
    uint8_t arg1;
    uint8_t arg2;
};

extern void *irq_ptr;
extern uint8_t irq_count, irq_table_offset;
extern uint8_t irq_table[31];

struct __irq_table {
    uint8_t reload;
    uint8_t *func_ptr;
    uint8_t arg0;
    uint8_t arg1;
    uint8_t arg2;
};


extern void irq_basic();
extern void irq_set_x_scroll();
extern void irq_set_chr();
extern void irq_set_chr_and_scroll();
//extern void irq_enable_sprites();



#define IRQ(n) (*(volatile struct __irq_table *)(irq_table + (n*6)))