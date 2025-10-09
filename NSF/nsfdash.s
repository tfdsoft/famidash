; void __fastcall__ music_play(uint8_t song);
.segment "CODE_2"

.import _options, FIRST_MUSIC_BANK

.export _music_play
.proc _music_play  

	; CONFIGURATION:
	; If the following value is set and valid, it will be used
	; as the pointer to famistudio_init in all banks. If it
	; isn't, then music_pointers_lo, hi and song count tables
	; are needed for proper operation.
	constInitPtr = $A000

	.ifndef constInitPtr
		constInitPtr = 0
	.endif
	useConstInitPtr = (constInitPtr >= $6000)

    ; bit _options ; sets N flag to bit 7 of _options without affecting A  
    ; bpl musicon
    ; rts  
; musicon:  
    LDY #<FIRST_MUSIC_BANK
    tsx
bank_loop:
    PHA
    SEC
    SBC music_counts-FIRST_MUSIC_BANK, Y
    BCC found_bank
    INY
    TXS ;Act as if no PHA happened
    BCS bank_loop  ; BRA
found_bank:
    TYA
    JSR mmc3_tmp_prg_bank_1
    CPY current_song_bank
    BEQ :+
    ;If different bank than before reinitalize FS
        STY	current_song_bank
		.if useConstInitPtr
			LDX #<constInitPtr
			LDY #>constInitPtr
		.else
			LDX music_data_locations_lo-FIRST_MUSIC_BANK, Y
			LDA	music_data_locations_hi-FIRST_MUSIC_BANK, Y
			TAY
		.endif
        LDA NTSC_MODE
        JSR famistudio_init
    :
    PLA
    JSR famistudio_music_play
    
    JMP _mmc3_pop_prg_bank_1

; Tables currently generated manually

.if .not(useConstInitPtr)
music_data_locations_lo:
	.out "shit"
	.byte <music_data_famidash_music1, <music_data_famidash_music2, <music_data_famidash_music3, <music_data_famidash_music4, <music_data_famidash_music5
music_data_locations_hi:
	.byte >music_data_famidash_music1, >music_data_famidash_music2, >music_data_famidash_music3, >music_data_famidash_music4, >music_data_famidash_music5
.endif
music_counts:
	.byte 2, 3, 3, 4, $FF ;last bank is marked with an FF to always stop bank picking
.endproc


.proc famistudio_init_for_sfx
	; CONFIGURATION:
	; If the following value is set and valid, it will be used
	; as the pointer to famistudio_init in all banks. If it
	; isn't, then music_pointers_lo, hi and song count tables
	; are needed for proper operation.
	constInitPtr = $A000

	.ifndef constInitPtr
		constInitPtr = 0
	.endif
	useConstInitPtr = (constInitPtr >= $6000)
	
	
	LDA #<FIRST_MUSIC_BANK
	JSR mmc3_tmp_prg_bank_1
	
	.if useConstInitPtr
		LDX #<constInitPtr
		LDY #>constInitPtr
	.else
		LDX #<music_data_famidash_music1
		LDY #>music_data_famidash_music1
	.endif
	LDA NTSC_MODE
	JSR famistudio_init
	
	JMP _mmc3_pop_prg_bank_1
.endproc

.segment "CODE_2"

.import _disable_dpcm_bankswitch
.proc famistudio_dpcm_bank_callback
	; ldx _disable_dpcm_bankswitch
	; beq :+
	; 	sec
	; 	rts
	; :
	clc
	adc #<FIRST_DMC_BANK
	jmp mmc3_set_prg_bank_0
.endproc


; void __fastcall__ sfx_play(uint8_t sfx_index, uint8_t channel);
.segment "CODE_2"

.import _options

.export __sfx_play
.proc __sfx_play  
    ; x = sfx
	; a = channel

    ; bit _options ; bit 6 is copied to the overflow flag  
    ; bvc play  
    ; rts  
; play:    
	tay

	lda	mmc3PRG1Bank
	pha
	lda #<.bank(sounds)
    jsr mmc3_set_prg_bank_1

	tya
    jsr famistudio_sfx_play

	pla
	jmp mmc3_set_prg_bank_1
.endproc

; void music_update();
.segment "CODE_2"

.export _music_update
.proc _music_update
    LDA current_song_bank
    JSR mmc3_tmp_prg_bank_1
    JSR famistudio_update
    JMP _mmc3_pop_prg_bank_1
.endproc
; Because i JMPed, the routine is over


; void __fastcall__ playPCM(uint8_t sample);
.segment "CODE_2"

.export _playPCM
.proc _playPCM
PCM_ptr = ptr1
    ; A = Sample
	tay
	ldx	NTSC_MODE
	bne :+
		clc
		adc #(SampleRate_PAL-SampleRate_NTSC)
	:
	tax
	lda SampleRate_NTSC, x
    sta tmp1
	ldx Bank, y

    ;enable DMC but disable DPCM
    lda #%00000000
    sta FAMISTUDIO_APU_DMC_FREQ
    lda #%00001011
    sta FAMISTUDIO_APU_SND_CHN
    lda #0
	sta PCM_ptr
    sta FAMISTUDIO_APU_DMC_LEN
    lda #%00011011
    sta FAMISTUDIO_APU_SND_CHN
    ; mute sqs+noi
    lda #$30
    sta FAMISTUDIO_APU_NOISE_VOL
    lda #%00110000
    sta FAMISTUDIO_APU_PL1_VOL
    sta FAMISTUDIO_APU_PL2_VOL
    ;init pcm
;    lda #<GeometryDashPCM
 ;   sta PCM_ptr
 ;   ldx #<.bank(GeometryDashPCM)
 	ldy #0

    ;play pcm
@RestartPtr:
    lda #>$C000
    sta PCM_ptr+1
@LoadBank:
    txa
    jsr mmc3_set_prg_bank_0
    inx
@LoadSample:
    lda tmp1	; 3
	sec			; 2
@Delay:
	sbc #1		;	5n cycles
	bcs @Delay	;__
	; 	beq	@noburn	; 2/3
	; 7x jsr BurnCycles	; 26
	; @noburn:
	; 	php			;
	; 	plp			;
	; 	php			;	17
	; 	plp			;
	; 	bit PCM_ptr	;__
	;	old code: if smp == 0 - 22 cycles, if not - 204 cycles
	;	new: 
	
    lda (PCM_ptr),y
    beq @DoneWithPCM
    sta $4011
    iny
    bne @LoadSample
    inc PCM_ptr+1
    lda PCM_ptr+1
    cmp #>($c000+$2000)
    bcc @LoadSample
    jmp @RestartPtr
@DoneWithPCM:
    lda #%00011111
    sta FAMISTUDIO_APU_SND_CHN
    lda #<FIRST_DMC_BANK
	jmp mmc3_set_prg_bank_0

; BurnCycles:	; 6 for JSR
;     php	;	7
;     plp	;__
;     php	;	7
;     plp	;__
;     rts	;	6

Bank:
    .byte <.bank(GeometryDashPCMA)
    .byte <.bank(GeometryDashPCMB)

SampleRate_NTSC:	; Also applies to Dendy, as it is derived from the CPU speed
	.byte 3		;(22-5+1)/5-1
	.byte 40	;((NTSC Clock / 8000)-5+1)/5-1
SampleRate_PAL:
	.byte 2
	.byte 37	;((PAL Clock / 8000)-5+1)/5-1
.endproc
