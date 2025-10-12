.segment .string(FAMISTUDIO_CA65_CODE_SEGMENT)
famistudio_dpcm_bank_callback:
    ldx #%11000111
    stx $8000
    sta $8001
    rts