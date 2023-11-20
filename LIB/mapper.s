;
; MMC3 Mapper registers, for use with the functions below
; 
.define MMC3_REG_BANK_SELECT $8000
.define MMC3_REG_BANK_DATA $8001
.define MMC3_REG_MIRRORING $a000
.define MMC3_REG_PRG_RAM_PROTECT $a001
.define MMC3_REG_IRQ_LATCH $c000
.define MMC3_REG_IRQ_RELOAD $c001
.define MMC3_REG_IRQ_DISABLE $e000
.define MMC3_REG_IRQ_ENABLE $e001

.define MMC3_MIRRORING_VERTICAL 0
.define MMC3_MIRRORING_HORIZONTAL 1

.define MMC3_REG_SEL_2KB_CHR_0 %00000000
.define MMC3_REG_SEL_2KB_CHR_1 %00000001 
.define MMC3_REG_SEL_1KB_CHR_0 %00000010
.define MMC3_REG_SEL_1KB_CHR_1 %00000011
.define MMC3_REG_SEL_1KB_CHR_2 %00000100 
.define MMC3_REG_SEL_1KB_CHR_3 %00000101
.define MMC3_REG_SEL_PRG_BANK_0 %00000110
.define MMC3_REG_SEL_PRG_BANK_1 %00000111

.define MMC3_REG_SEL_CHR_MODE_A %00000000
.define MMC3_REG_SEL_CHR_MODE_B %10000000
.define MMC3_REG_SEL_PRG2_C000 %00000000
.define MMC3_REG_SEL_PRG2_8000 %01000000

; Values for which banks to load
.define MMC3_REG_CONTROL_DEFAULT #%11100

.segment "ZEROPAGE"
    ; Used to track whether a register write was interrupted, so we can try again if needed.
    ; alexmush comment:
    ; not anymore, just used for the PRG mode
    mmc3ChrInversionSetting: .res 1
.segment "BSS"
    mmc3PRG1Bank: .res 1    ;because famistudio updates

.segment "CODE_2"
    mmc3_internal_set_bank:
        tay
        txa
        ora mmc3ChrInversionSetting
        sta MMC3_REG_BANK_SELECT
        sty MMC3_REG_BANK_DATA
        rts

    _mmc3_pop_prg_bank_1:
        LDX mmc3PRG1Bank
        LDA #MMC3_REG_SEL_PRG_BANK_1
        ora mmc3ChrInversionSetting
        sta MMC3_REG_BANK_SELECT
        STX MMC3_REG_BANK_DATA
        rts
    .export _mmc3_pop_prg_bank_1

    ; Store mirroring value to mmc3 register
    mmc3_set_prg_bank_0:
    _mmc3_set_prg_bank_0:
        ldx #MMC3_REG_SEL_PRG_BANK_0
        jmp mmc3_internal_set_bank
    .export _mmc3_set_prg_bank_0

    mmc3_set_prg_bank_1:
    _mmc3_set_prg_bank_1:
        STA mmc3PRG1Bank
    mmc3_tmp_prg_bank_1:
    _mmc3_tmp_prg_bank_1:
        ldx #MMC3_REG_SEL_PRG_BANK_1
        jmp mmc3_internal_set_bank
    .export _mmc3_set_prg_bank_1, _mmc3_tmp_prg_bank_1

    mmc3_set_2kb_chr_bank_0:
    _mmc3_set_2kb_chr_bank_0:
        ldx #MMC3_REG_SEL_2KB_CHR_0
        jmp mmc3_internal_set_bank
    .export _mmc3_set_2kb_chr_bank_0

    mmc3_set_2kb_chr_bank_1:
    _mmc3_set_2kb_chr_bank_1:
        ldx #MMC3_REG_SEL_2KB_CHR_1
        jmp mmc3_internal_set_bank
    .export _mmc3_set_2kb_chr_bank_1

    mmc3_set_1kb_chr_bank_0:
    _mmc3_set_1kb_chr_bank_0:
        ldx #MMC3_REG_SEL_1KB_CHR_0
        jmp mmc3_internal_set_bank
    .export _mmc3_set_1kb_chr_bank_0

    mmc3_set_1kb_chr_bank_1:
    _mmc3_set_1kb_chr_bank_1:
        ldx #MMC3_REG_SEL_1KB_CHR_1
        jmp mmc3_internal_set_bank
    .export _mmc3_set_1kb_chr_bank_1

    mmc3_set_1kb_chr_bank_2:
    _mmc3_set_1kb_chr_bank_2:
        ldx #MMC3_REG_SEL_1KB_CHR_2
        jmp mmc3_internal_set_bank
    .export _mmc3_set_1kb_chr_bank_2

    mmc3_set_1kb_chr_bank_3:
    _mmc3_set_1kb_chr_bank_3:
        ldx #MMC3_REG_SEL_1KB_CHR_3
        jmp mmc3_internal_set_bank
    .export _mmc3_set_1kb_chr_bank_3

    mmc3_set_mirroring:
    _mmc3_set_mirroring:
        sta MMC3_REG_MIRRORING
        rts
    .export _mmc3_set_mirroring

    initialize_mapper:
        lda #(MMC3_REG_SEL_CHR_MODE_A | MMC3_REG_SEL_PRG2_8000)
        sta mmc3ChrInversionSetting

        lda #%10000000
        sta MMC3_REG_PRG_RAM_PROTECT

        lda #0
        jsr mmc3_set_prg_bank_0
        lda #1
        sta MMC3_REG_MIRRORING  ; Set mirroring to horizontal
        jmp mmc3_set_prg_bank_1
