// Set the first 8kb prg bank
void __fastcall__ mmc3_set_prg_bank_0(uint8_t bank);
// Set the second 8kb prg bank
void __fastcall__ mmc3_set_prg_bank_1(uint8_t bank);
// Set the first 2kb chr bank
void __fastcall__ mmc3_set_2kb_chr_bank_0(uint8_t bank);
// Set the second 2kb chr bank
void __fastcall__ mmc3_set_2kb_chr_bank_1(uint8_t bank);
// Set the first 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_0(uint8_t bank);
// Set the second 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_1(uint8_t bank);
// Set the third 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_2(uint8_t bank);
// Set the fourth 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_3(uint8_t bank);

// extern uint8_t MMC3_MIRRORING_VERTICAL;
// extern uint8_t MMC3_MIRRORING_HORIZONTAL;

// #define mmc3_set_mirroring(direction); \
// __asm__("LDA #%s", direction); \
// __asm__("STA MMC3_REG_MIRRORING");


extern uint8_t xargs[4];

void _mmc3_set_8kb_chr() {
    // bg
    mmc3_set_1kb_chr_bank_0(xargs[0]);
    mmc3_set_1kb_chr_bank_1(++xargs[0]);
    mmc3_set_1kb_chr_bank_2(++xargs[0]);
    mmc3_set_1kb_chr_bank_3(++xargs[0]);
	// sprites
	mmc3_set_2kb_chr_bank_0(xargs[0]+2);
    mmc3_set_2kb_chr_bank_1(xargs[0]+4);
}

#define mmc3_set_8kb_chr(bank) (xargs[0] = bank, _mmc3_set_8kb_chr())




extern uint8_t irqTable[32];
extern uint8_t irqTableIdx;

// Turns off MMC3 irqs and resets the irqTableIdx
void mmc3_disable_irq();


// This points an array to the IRQ system 
// Also turns ON the system
void set_irq_ptr(const uint8_t * address);


// Check if it's safe to write to the irq array
// returns 0xff if done, zero if not done
// if the irq pointer is pointing to 0xff it is
// safe to edit.
uint8_t is_irq_done();




// quick and easily write an irq table in ROM to the irq table in SRAM
void write_irq_table(const uint8_t * data);

// edit bytes in the table. useful for scrolling.
void _edit_irq_table(uint16_t args);
#define edit_irq_table(byte, offset) (_edit_irq_table(byte|(offset<<8)))



#define irqtable_ppuctrl 0xf0
#define irqtable_ppustatus 0xf1

#define irqtable_hscroll 0xf5
#define irqtable_ppuaddr 0xf6

#define irqtable_chr0 0xf7
#define irqtable_chr1 0xf8
#define irqtable_chr2 0xf9
#define irqtable_chr3 0xfa
#define irqtable_chr4 0xfb
#define irqtable_chr5 0xfc

#define irqtable_wait 0xfd
#define irqtable_timedwait 0xfe
#define irqtable_end 0xff


