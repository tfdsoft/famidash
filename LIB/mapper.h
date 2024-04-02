// Set the first 8kb prg bank
void __fastcall__ mmc3_set_prg_bank_0(unsigned char bank);
// Set the second 8kb prg bank
void __fastcall__ mmc3_set_prg_bank_1(unsigned char bank);
// Set the first 2kb chr bank
void __fastcall__ mmc3_set_2kb_chr_bank_0(unsigned char bank);
// Set the second 2kb chr bank
void __fastcall__ mmc3_set_2kb_chr_bank_1(unsigned char bank);
// Set the first 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_0(unsigned char bank);
// Set the second 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_1(unsigned char bank);
// Set the third 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_2(unsigned char bank);
// Set the fourth 1kb chr bank
void __fastcall__ mmc3_set_1kb_chr_bank_3(unsigned char bank);

// extern unsigned char MMC3_MIRRORING_VERTICAL;
// extern unsigned char MMC3_MIRRORING_HORIZONTAL;

// #define mmc3_set_mirroring(direction); \
// __asm__("LDA #%s", direction); \
// __asm__("STA MMC3_REG_MIRRORING");

void __fastcall__ mmc3_tmp_prg_bank_1(unsigned char bank);

void __fastcall__ mmc3_pop_prg_bank_1();

void __fastcall__ mmc3_set_8kb_chr(unsigned char i) {
	// bg
    mmc3_set_1kb_chr_bank_0(i);
    mmc3_set_1kb_chr_bank_1(i+1);
    mmc3_set_1kb_chr_bank_2(i+2);
    mmc3_set_1kb_chr_bank_3(i+3);
	// sprites
	mmc3_set_2kb_chr_bank_0(i+4);
    mmc3_set_2kb_chr_bank_1(i+6);
}