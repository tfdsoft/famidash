; This file is for the FamiStudio Sound Engine and was generated by FamiStudio
; Project uses FamiTracker tempo, you must set FAMISTUDIO_USE_FAMITRACKER_TEMPO = 1.
; Project uses release notes, you must set FAMISTUDIO_USE_RELEASE_NOTES = 1.
; Volume track is used, you must set FAMISTUDIO_USE_VOLUME_TRACK = 1.
; Fine pitch track is used, you must set FAMISTUDIO_USE_PITCH_TRACK = 1.
; Slide notes are used, you must set FAMISTUDIO_USE_SLIDE_NOTES = 1.
; Vibrato effect is used, you must set FAMISTUDIO_USE_VIBRATO = 1.
; Arpeggios are used, you must set FAMISTUDIO_USE_ARPEGGIO = 1.
; Duty Cycle effect is used, you must set FAMISTUDIO_USE_DUTYCYCLE_EFFECT = 1.
; Project has DPCM bank-switching enabled in the project settings, you must set FAMISTUDIO_USE_DPCM_BANKSWITCHING = 1 and implement bank switching.

.if FAMISTUDIO_CFG_C_BINDINGS
.export _music_data_famidash_music13=music_data_famidash_music13
.endif

music_data_famidash_music13:
	.byte 3
	.word @instruments
	.word @samples-5
; 00 : Can't Let Go
	.word @song0ch0
	.word @song0ch1
	.word @song0ch2
	.word @song0ch3
	.word @song0ch4
	.word 348,290
; 01 : Menu Theme
	.word @song1ch0
	.word @song1ch1
	.word @song1ch2
	.word @song1ch3
	.word @song1ch4
	.word 264,220
; The DPCM aligner used to be here
; 03 : Pyrophoric
	.word @song3ch0
	.word @song3ch1
	.word @song3ch2
	.word @song3ch3
	.word @song3ch4
	.word 245,204

.export music_data_famidash_music13
.global FAMISTUDIO_DPCM_PTR

@instruments:
	.word @env5,@env4,@env27,@env0 ; 00 : hat
	.word @env6,@env28,@env22,@env0 ; 01 : kick
	.word @env17,@env21,@env2,@env0 ; 02 : snare
	.word @env26,@env18,@env22,@env0 ; 03 : triangle pluck 4
	.word @env20,@env18,@env22,@env0 ; 04 : triangle pluck
	.word @env33,@env18,@env22,@env0 ; 05 : blank instant decay
	.word @env30,@env4,@env2,@env0 ; 06 : cymbal
	.word @env1,@env18,@env22,@env0 ; 07 : echo
	.word @env15,@env18,@env22,@env0 ; 08 : blank
	.word @env25,@env18,@env22,@env0 ; 09 : quiet bass
	.word @env19,@env18,@env22,@env0 ; 0a : infernoplex_piano
	.word @env11,@env18,@env22,@env0 ; 0b : DMC: drums + bass
	.word @env25,@env32,@env23,@env0 ; 0c : octave arp
	.word @env16,@env4,@env22,@env0 ; 0d : rel hats
	.word @env36,@env18,@env24,@env0 ; 0e : death moon lead
	.word @env3,@env18,@env22,@env14 ; 0f : triangle drums

@env0:
	.byte $00,$c0,$7f,$00,$02
@env1:
	.byte $00,$cb,$c7,$c5,$c4,$c3,$c2,$c2,$c1,$c1,$c0,$c5,$c4,$c3,$c3,$c2,$c2,$c1,$c1,$c0,$00,$13
@env2:
	.byte $c1,$c0,$00,$01
@env3:
	.byte $00,$c9,$c8,$c7,$c6,$c6,$c5,$c5,$c4,$00,$08
@env4:
	.byte $bd,$c0,$00,$01
@env5:
	.byte $00,$c8,$c4,$c2,$c0,$00,$04
@env6:
	.byte $00,$cd,$c9,$c5,$c2,$c1,$c0,$00,$06
@env7:
	.byte $00,$c0,$bf,$be,$be,$bf,$c1,$c2,$c2,$c1,$00,$01
@env8:
	.byte $c0,$c4,$c7,$00,$00
@env9:
	.byte $00,$c0,$c0,$bf,$03,$c0,$c0,$c1,$03,$c0,$00,$01
@env10:
	.byte $00,$c0,$b9,$b4,$b3,$b6,$bc,$c4,$ca,$cd,$cc,$c7,$00,$01
@env11:
	.byte $00,$cf,$7f,$00,$02
@env12:
	.byte $c0,$c7,$cc,$00,$00
@env13:
	.byte $c0,$c2,$c7,$00,$00
@env14:
	.byte $80,$bf,$f1,$00,$02
@env15:
	.byte $04,$cf,$00,$01,$ca,$c6,$c4,$c2,$c0,$00,$08
@env16:
	.byte $00,$c8,$c6,$c5,$c5,$c4,$c4,$c3,$02,$c2,$02,$c1,$02,$c0,$00,$0d
@env17:
	.byte $00,$cd,$cb,$c8,$c6,$c5,$c4,$c3,$c2,$c1,$c1,$c0,$00,$0b
@env18:
	.byte $c0,$7f,$00,$01
@env19:
	.byte $00,$ce,$02,$cd,$cd,$cc,$cc,$cb,$cb,$ca,$c9,$c9,$c8,$c7,$c6,$c5,$c3,$00,$10
@env20:
	.byte $00,$cf,$c0,$00,$02
@env21:
	.byte $c6,$cc,$00,$01
@env22:
	.byte $7f,$00,$00
@env23:
	.byte $c2,$7f,$00,$00
@env24:
	.byte $c1,$7f,$00,$00
@env25:
	.byte $00,$c9,$c7,$c5,$00,$03
@env26:
	.byte $00,$cf,$03,$c0,$00,$03
@env27:
	.byte $c0,$c1,$00,$00
@env28:
	.byte $c9,$cf,$00,$01
@env29:
	.byte $c0,$c0,$c3,$00,$00
@env30:
	.byte $18,$cf,$ce,$cd,$cc,$cb,$ca,$c9,$c8,$c8,$c7,$c7,$c6,$02,$c5,$c5,$c4,$02,$c3,$03,$c2,$c2,$00,$15,$c2,$c2,$c1,$03,$c0,$00,$1c
@env31:
	.byte $c0,$c0,$c5,$00,$00
@env32:
	.byte $c0,$c0,$cc,$cc,$00,$00
@env33:
	.byte $00,$cf,$cf,$cb,$c8,$c5,$c3,$c2,$c1,$c0,$00,$09
@env34:
	.byte $c0,$c5,$c9,$00,$00
@env35:
	.byte $c0,$c5,$ca,$00,$00
@env36:
	.byte $00,$cf,$ca,$c9,$c8,$c7,$c6,$c6,$c5,$00,$08
@env37:
	.byte $c0,$c5,$c7,$00,$00

@samples:
	.byte $11+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 00 fdbass A# (Pitch:15)
	.byte $23+.lobyte(FAMISTUDIO_DPCM_PTR),$45,$0f,$40,$00 ; 01 fdbass B (Pitch:15)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0c,$40,$00 ; 02 fdbass C (Pitch:12)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0d,$40,$00 ; 03 fdbass C (Pitch:13)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0e,$40,$00 ; 04 fdbass C (Pitch:14)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 05 fdbass C (Pitch:15)
	.byte $47+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 06 fdbass C# (Pitch:15)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0c,$40,$00 ; 07 fdbass D (Pitch:12)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0f,$40,$00 ; 08 fdbass D (Pitch:15)
	.byte $6b+.lobyte(FAMISTUDIO_DPCM_PTR),$2b,$0e,$40,$00 ; 09 fdkick (Pitch:14)
	.byte $00+.lobyte(FAMISTUDIO_DPCM_PTR),$41,$0f,$34,$00 ; 0a snare (Pitch:15)

@song0ch0:
	.byte $46, $06
@song0ref3:
	.byte $4e, $00, $4f, $02, $8e
@song0ref8:
	.byte $29, $85, $29, $85, $2c, $85, $2c, $85
@song0ref16:
	.byte $2c, $81, $27, $85, $27, $85, $25, $81, $22, $81, $25, $81, $25, $85, $25, $85, $29, $85, $29, $81, $29, $81, $22, $81
	.byte $27, $85, $27, $85, $25, $81, $2c, $81, $2b, $81
	.byte $41, $24
	.word @song0ref8
	.byte $2e, $81, $2c, $81, $2b, $81, $4e, $00, $4f, $02
	.byte $41, $2a
	.word @song0ref8
	.byte $41, $24
	.word @song0ref8
	.byte $2e, $81, $2c, $81, $2b, $81, $29, $9d, $4f, $01, $85, $74, $4e, $01, $90
@song0ref84:
	.byte $11, $85, $11, $85, $11, $85, $14, $85, $0f, $85, $00, $81, $0f, $85, $00, $81, $16, $85, $0d, $85, $0d, $85, $0d, $85
	.byte $0d, $85, $0f, $85, $00, $81, $0f, $85, $00, $81, $14, $4f, $01, $85, $4e, $01
	.byte $41, $24
	.word @song0ref84
	.byte $4e, $01
	.byte $41, $23
	.word @song0ref84
	.byte $85
	.byte $41, $1e
	.word @song0ref84
	.byte $1b, $85, $00, $81, $14, $7f
	.byte $41, $2a
	.word @song0ref3
	.byte $29, $85, $29, $85, $2c, $85, $2c, $81, $2c, $81
	.byte $41, $1c
	.word @song0ref16
	.byte $2e, $81, $2c, $81, $2b, $81, $4e, $00, $4f, $02
	.byte $41, $2a
	.word @song0ref8
	.byte $29, $85, $29, $85, $2c, $85, $2c, $81, $2c, $81
	.byte $41, $1c
	.word @song0ref16
	.byte $2e, $81, $2c, $81, $2b, $81, $4e, $00, $4f, $02
	.byte $41, $2a
	.word @song0ref8
	.byte $29, $85, $29, $85, $2c, $85, $2c, $81, $2c, $81
	.byte $41, $1c
	.word @song0ref16
	.byte $2e, $81, $2c, $81, $2b, $81, $4e, $00, $4f, $02, $29, $85, $44, $00
@song0ch1:
@song0ref225:
	.byte $92
@song0ref226:
	.byte $05, $95, $08, $85, $03, $89, $03, $91, $01, $9d, $03, $89, $03, $91, $05, $95, $08, $85, $03, $89, $03, $91, $01, $9d
	.byte $03, $89, $03, $91
	.byte $41, $1c
	.word @song0ref226
	.byte $05, $85, $00, $95, $7a, $90, $11, $83
@song0ref265:
	.byte $77, $81, $7a, $11, $43, $11, $81, $77, $81, $7a, $11, $43, $11, $81, $77, $81, $7a, $50, $d2, $1d, $20, $43, $14, $81
	.byte $77, $81, $7a, $50, $51, $20, $1b, $43, $0f, $83, $00, $81, $0f, $85, $00, $70, $0f, $7a, $50, $95, $1b, $22, $43, $16
	.byte $81, $77, $81, $7a, $50, $7f, $22, $19, $43, $0d, $81, $77, $81, $7a, $0d, $43, $0d, $81, $77, $81, $7a, $0d, $43, $0d
	.byte $81, $77, $81, $7a, $0d, $43, $0d, $81, $77, $81, $7a, $50, $d9, $19, $1b, $43, $0f, $83, $00, $81, $0f, $85, $00, $70
	.byte $0f, $7a, $50, $af, $1b, $20, $43, $14, $81, $77, $81, $7a, $50, $2e, $20, $1d, $43, $11, $81
	.byte $41, $3a
	.word @song0ref265
	.byte $41, $3a
	.word @song0ref265
	.byte $41, $2e
	.word @song0ref265
	.byte $70, $0f, $7a, $50, $80, $1b, $27, $43, $1b, $83, $00, $70, $1b, $7a, $50, $50, $27, $20, $43, $14, $81, $77, $81, $7a
	.byte $50, $2e, $20, $1d, $43, $11, $81
	.byte $41, $3a
	.word @song0ref265
	.byte $41, $3a
	.word @song0ref265
	.byte $41, $3a
	.word @song0ref265
	.byte $41, $37
	.word @song0ref265
	.byte $7f
	.byte $41, $1c
	.word @song0ref225
	.byte $05, $85, $44, $00
@song0ch2:
	.byte $96
@song0ref442:
	.byte $11, $95, $14, $85, $0f, $89, $0f, $91, $0d, $9d, $0f, $89, $0f, $91, $11, $95, $14, $85, $0f, $89, $0f, $91, $0d, $9d
	.byte $0f, $89, $0f, $91
	.byte $41, $1c
	.word @song0ref442
	.byte $00, $9d
	.byte $41, $1c
	.word @song0ref442
	.byte $41, $1c
	.word @song0ref442
	.byte $41, $1c
	.word @song0ref442
	.byte $41, $1c
	.word @song0ref442
	.byte $41, $1c
	.word @song0ref442
	.byte $11, $85, $44, $00
@song0ch3:
	.byte $ff, $ff
@song0ref497:
	.byte $82, $14, $81, $80, $1f, $81, $84, $14, $81, $80, $1f, $81, $82, $14, $81, $80, $1f, $81, $84, $14, $81, $80, $1f, $81
	.byte $82, $14, $81, $80, $1f, $81, $84, $14, $81, $80, $1f, $81, $82, $14, $81, $80, $1f, $81, $84, $14, $81, $80, $1f, $81
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $84, $14, $81, $82, $14, $81, $14, $81, $84, $14, $81, $82, $14, $81, $14, $81, $84, $14, $14, $14, $14
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $1d
	.word @song0ref497
	.byte $15, $15, $16
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $41, $20
	.word @song0ref497
	.byte $00, $fd, $ff, $87, $44, $00
@song0ch4:
	.byte $ff, $ff
@song0ref635:
	.byte $0a, $81, $04, $81, $0b, $81, $04, $81, $0a, $81, $04, $81, $0b, $81, $05, $81, $0a, $81, $08, $81, $0b, $81, $08, $81
	.byte $0a, $81, $08, $81, $0b, $81, $08, $81, $0a, $81, $03, $81, $0b, $81, $03, $81, $0a, $81, $03, $81, $0b, $81, $03, $81
	.byte $0a, $81, $08, $81, $0b, $81, $08, $81, $0a, $81, $08, $81, $0b, $81, $08, $81
	.byte $41, $40
	.word @song0ref635
	.byte $0b, $81, $0a, $81, $0a, $81, $0b, $81, $0a, $81, $0a, $81, $0b, $0b, $0b, $0b
	.byte $41, $40
	.word @song0ref635
	.byte $41, $40
	.word @song0ref635
	.byte $41, $40
	.word @song0ref635
	.byte $41, $3d
	.word @song0ref635
	.byte $0b, $0b, $0b
	.byte $41, $40
	.word @song0ref635
	.byte $41, $40
	.word @song0ref635
	.byte $41, $40
	.word @song0ref635
	.byte $41, $40
	.word @song0ref635
	.byte $00, $fd, $ff, $87, $44, $00
@song1ch0:
	.byte $46, $06
@song1ch0loop:
	.byte $85, $8e
@song1ref6:
	.byte $31, $9d, $31, $9d, $31, $9d, $31, $97, $85, $31, $9d, $31, $9d, $31, $9d, $31, $97, $85
	.byte $41, $0e
	.word @song1ref6
	.byte $b7, $42
	.word @song1ch0loop
@song1ch1:
@song1ch1loop:
	.byte $98
@song1ref33:
	.byte $0d, $9d, $0b, $9d, $0a, $9d, $09, $8b, $0b, $8f
	.byte $41, $0a
	.word @song1ref33
	.byte $41, $0a
	.word @song1ref33
	.byte $41, $0a
	.word @song1ref33
	.byte $42
	.word @song1ch1loop
@song1ch2:
@song1ch2loop:
	.byte $86
@song1ref57:
	.byte $25, $25
@song1ref59:
	.byte $31, $88, $31, $86, $2c, $88, $2c, $81, $86, $2b, $88, $2b, $86, $2a, $88, $2a, $86, $28, $88, $28, $86, $25, $28, $2a
	.byte $23, $23
	.byte $41, $0e
	.word @song1ref59
	.byte $22, $22
	.byte $41, $0e
	.word @song1ref59
	.byte $21, $21
	.byte $41, $0e
	.word @song1ref59
	.byte $41, $12
	.word @song1ref57
	.byte $41, $0e
	.word @song1ref59
	.byte $22, $22
	.byte $41, $0e
	.word @song1ref59
	.byte $21, $21
	.byte $41, $0e
	.word @song1ref59
	.byte $41, $12
	.word @song1ref57
	.byte $41, $0e
	.word @song1ref59
	.byte $22, $22
	.byte $41, $0e
	.word @song1ref59
	.byte $21, $21
	.byte $41, $0e
	.word @song1ref59
	.byte $41, $12
	.word @song1ref57
	.byte $41, $0e
	.word @song1ref59
	.byte $22, $22
	.byte $41, $0e
	.word @song1ref59
	.byte $9f, $42
	.word @song1ch2loop
@song1ch3:
@song1ch3loop:
@song1ref146:
	.byte $82, $14, $80, $23, $21, $23, $84, $14, $80, $23, $21, $82, $14, $80, $1f, $82, $14, $14, $80, $23, $84, $14, $80, $23
	.byte $21, $23, $82, $14, $80, $23, $82, $14, $80, $23, $84, $14, $80, $23, $82, $14, $84, $14, $80, $1f, $82, $14, $14, $80
	.byte $23, $84, $14, $16, $16, $16
	.byte $41, $20
	.word @song1ref146
	.byte $41, $20
	.word @song1ref146
	.byte $41, $20
	.word @song1ref146
	.byte $41, $20
	.word @song1ref146
	.byte $41, $20
	.word @song1ref146
	.byte $41, $20
	.word @song1ref146
	.byte $41, $11
	.word @song1ref146
	.byte $81, $14, $85, $14, $81, $14, $85, $9a, $20, $81, $20, $81, $42
	.word @song1ch3loop
@song1ch4:
@song1ch4loop:
@song1ref237:
	.byte $0a, $85, $0b, $83, $0a, $81, $0a, $0a, $81, $0b, $85, $0a, $81, $0a, $81, $0b, $81, $0a, $0b, $81, $0a, $0a, $81, $0b
	.byte $0b, $0b, $0b
	.byte $41, $1b
	.word @song1ref237
	.byte $41, $1b
	.word @song1ref237
	.byte $41, $1b
	.word @song1ref237
	.byte $41, $1b
	.word @song1ref237
	.byte $41, $1b
	.word @song1ref237
	.byte $41, $1b
	.word @song1ref237
	.byte $41, $0e
	.word @song1ref237
	.byte $85, $0a, $81, $0a, $85, $0a, $81, $0a, $81, $42
	.word @song1ch4loop
; The DPCM aligner used to be here
@song3ch0:
	.byte $46, $03, $9c
@song3ref4:
	.byte $14, $85, $08, $81, $20, $81, $0f, $81, $0d, $81, $16, $85, $14, $85, $08, $85, $12, $85, $14, $81, $0d, $81, $0b, $85
	.byte $10, $81, $0b, $81, $19, $85, $17, $85, $49, .lobyte(@env10), .hibyte(@env10), $16, $81, $49, .lobyte(@env0), .hibyte(@env0)
	.byte $4a, $83, $9c, $12, $85, $0a, $85, $0d, $81, $0f, $81
	.byte $41, $1f
	.word @song3ref4
@song3ref58:
	.byte $81, $19, $81, $16, $85, $12, $85, $14, $85, $0d, $81, $0f, $81
	.byte $41, $2b
	.word @song3ref4
	.byte $41, $1f
	.word @song3ref4
	.byte $41, $0d
	.word @song3ref58
	.byte $41, $2b
	.word @song3ref4
	.byte $41, $1f
	.word @song3ref4
	.byte $41, $0d
	.word @song3ref58
@song3ref89:
	.byte $10, $85, $08, $81, $20, $81, $12, $81, $14, $81, $17, $85, $0a, $81, $0f, $81, $12, $85, $16, $85, $19, $81, $1b, $81
	.byte $41, $12
	.word @song3ref4
	.byte $17, $81, $19, $81
	.byte $41, $18
	.word @song3ref89
	.byte $12, $85, $06, $81, $1e, $81, $0f, $81, $0d, $81, $17, $85, $19, $85, $0a, $85, $12, $85, $17, $81, $19, $81
	.byte $41, $2b
	.word @song3ref4
	.byte $41, $1f
	.word @song3ref4
	.byte $41, $0d
	.word @song3ref58
	.byte $20, $85, $1e, $81, $20, $81, $1d, $85, $1b, $85, $19, $85, $17, $85, $16, $85, $12, $85, $14, $85, $00, $81, $14, $85
	.byte $14, $81, $12, $85, $14, $85, $00, $85, $50, $58, $2e, $14, $89, $00, $81, $ff, $44, $00
@song3ch1:
	.byte $ff, $ff, $bf, $4b, .lobyte(@env8), .hibyte(@env8), $94, $1c, $83, $00, $83, $4d, $1c, $83, $00, $8b, $4b, .lobyte(@env34)
	.byte .hibyte(@env34), $19, $83, $00
@song3ref219:
	.byte $4d, $19, $81, $4b, .lobyte(@env35), .hibyte(@env35)
@song3ref225:
	.byte $19, $83, $00, $8b
@song3ref229:
	.byte $bf, $4b, .lobyte(@env8), .hibyte(@env8), $1c, $83, $00, $83, $4d, $1c, $83, $00, $8b, $4b, .lobyte(@env34), .hibyte(@env34)
	.byte $19, $83, $00, $4b, .lobyte(@env37), .hibyte(@env37), $19, $81, $4b, .lobyte(@env31), .hibyte(@env31)
	.byte $41, $10
	.word @song3ref225
	.byte $41, $14
	.word @song3ref219
	.byte $4b, .lobyte(@env31), .hibyte(@env31), $19, $83, $00, $8b, $e7, $4b, .lobyte(@env31), .hibyte(@env31), $1b, $85, $4b
	.byte .lobyte(@env29), .hibyte(@env29), $1b, $81, $4b, .lobyte(@env31), .hibyte(@env31), $1b, $85, $00, $81, $df, $4b, .lobyte(@env13)
	.byte .hibyte(@env13), $19, $85, $4d, $19, $85, $4b, .lobyte(@env12), .hibyte(@env12), $19, $85, $00, $85
	.byte $41, $0c
	.word @song3ref229
	.byte $41, $14
	.word @song3ref219
	.byte $4b, .lobyte(@env31), .hibyte(@env31), $19, $83, $00, $8b, $ef, $4b, .lobyte(@env12), .hibyte(@env12), $20, $83, $45
	.byte $87, $81, $00, $fb, $44, $00
@song3ch2:
	.byte $ff, $ff, $90
@song3ref333:
	.byte $14, $bd, $10, $9d, $12, $9d, $14, $bd, $10, $9d, $12, $9d, $14, $8d, $2c, $8d, $2f, $85, $2e, $85, $2a, $8d, $2c, $95
	.byte $33, $95, $31, $8d, $2c, $2e, $8b, $00, $85, $2c, $85, $00, $95, $25, $81, $27, $81, $2a, $2c, $83, $2f, $85, $2e, $85
	.byte $2c, $85, $2a, $85, $25, $85, $2c, $2e, $8b, $2c, $8d, $2e, $85, $2f, $85, $00, $85, $2e, $85, $2f, $85, $31, $83, $00
	.byte $31, $33, $93, $2c, $95, $2a, $8d, $2c, $8d, $2e, $85, $2f, $85, $31, $8d, $33, $85, $36, $83, $00, $36, $38, $83, $49
	.byte .lobyte(@env9), .hibyte(@env9), $87, $49, .lobyte(@env7), .hibyte(@env7), $8d, $00, $49, .lobyte(@env0), .hibyte(@env0)
	.byte $4a, $90, $38, $81, $33, $81, $31, $81, $2c, $81, $33, $81, $31, $81, $2c, $81, $27, $81
	.byte $41, $0c
	.word @song3ref333
	.byte $20, $85, $22, $85, $25, $85, $23, $85, $25, $85, $27, $85, $2a, $85, $22, $85, $20, $85, $00, $81, $20, $83, $00, $20
	.byte $81, $1e, $85, $9e, $31, $81, $2f, $2d, $29, $81, $25, $81, $00, $8d, $ff, $44, $00
@song3ch3:
	.byte $ff, $72, $8a, $22, $81, $71, $22, $81, $22, $81, $22, $81, $74, $22, $81, $72, $22, $81, $22, $81, $22, $81, $76, $22
	.byte $81, $73, $22, $81, $22, $81, $22, $81, $78, $22, $81, $74, $22, $81, $22, $81, $22, $81, $7a, $22, $81, $75, $22, $81
	.byte $22, $81, $22, $81, $7c, $22, $81, $76, $22, $81, $22, $81, $22, $81, $7e, $22, $81, $77, $22, $81, $22, $81, $22, $81
	.byte $7f, $22, $81, $78, $22, $81, $7f, $94, $22, $85
@song3ref585:
	.byte $8a
@song3ref586:
	.byte $22, $85, $22, $85, $22, $85, $22, $85, $22, $85, $22, $85
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $22, $85, $22, $85, $8c, $20, $8d
	.byte $41, $0c
	.word @song3ref585
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $8c, $20, $8d
	.byte $41, $0c
	.word @song3ref585
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $8c, $20, $8d
	.byte $41, $0c
	.word @song3ref585
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $41, $0c
	.word @song3ref586
	.byte $8c, $1e, $9b, $00, $20, $9b, $00, $9f, $80, $16, $00, $16, $16, $16, $00, $16, $00, $8c, $1d, $8d, $45, $81, $00, $f9
	.byte $44, $00
@song3ch4:
	.byte $ff
@song3ref696:
	.byte $0a, $85, $00, $85, $0a, $85, $00, $85, $0a, $85, $00, $85
	.byte $41, $0c
	.word @song3ref696
	.byte $41, $0c
	.word @song3ref696
@song3ref714:
	.byte $0b, $85, $00, $81, $0a, $85, $00, $81, $0a, $85, $0b, $85, $00, $85, $0a, $85, $00, $85
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref714
@song3ref738:
	.byte $0b, $85, $0a, $81, $0a, $0a, $0a, $85, $0b, $85, $0b, $81, $0a, $81, $0a, $81, $0a, $81, $0a, $85, $00, $85
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref714
	.byte $41, $16
	.word @song3ref738
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref714
	.byte $41, $16
	.word @song3ref738
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref714
	.byte $41, $12
	.word @song3ref738
	.byte $0b, $85, $0a, $85, $0b, $85, $0a, $81, $0a, $0a, $0a, $85, $0b, $81, $0a, $81, $0b, $81, $0a, $81, $0a, $81, $0a, $81
	.byte $0a, $89, $0a, $85, $0a, $81, $0a, $85, $0a, $85, $00, $85, $0b, $85, $00, $85, $ff, $44, $00
