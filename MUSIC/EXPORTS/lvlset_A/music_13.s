; This file is for the FamiStudio Sound Engine and was generated by FamiStudio
; Project uses FamiTracker tempo, you must set FAMISTUDIO_USE_FAMITRACKER_TEMPO = 1.
; Project uses delayed notes or cuts, you must set FAMISTUDIO_USE_FAMITRACKER_DELAYED_NOTES_OR_CUTS = 1.
; Volume track is used, you must set FAMISTUDIO_USE_VOLUME_TRACK = 1.
; Duty Cycle effect is used, you must set FAMISTUDIO_USE_DUTYCYCLE_EFFECT = 1.
; Project has DPCM bank-switching enabled in the project settings, you must set FAMISTUDIO_USE_DPCM_BANKSWITCHING = 1 and implement bank switching.

.if FAMISTUDIO_CFG_C_BINDINGS
.export _music_data_famidash_music13=music_data_famidash_music13
.endif

music_data_famidash_music13:
	.byte 1
	.word @instruments
	.word @samples-5
; The DPCM aligner used to be here
; 01 : The Challenge
	.word @song1ch0
	.word @song1ch1
	.word @song1ch2
	.word @song1ch3
	.word @song1ch4
	.word 337,281

.export music_data_famidash_music13
.global FAMISTUDIO_DPCM_PTR

@instruments:
	.word @env5,@env3,@env20,@env0 ; 00 : hat
	.word @env7,@env21,@env17,@env0 ; 01 : kick
	.word @env2,@env13,@env17,@env10 ; 02 : triangle drums
	.word @env19,@env4,@env17,@env0 ; 03 : tight triangle snare
	.word @env22,@env3,@env1,@env0 ; 04 : cymbal
	.word @env16,@env18,@env17,@env0 ; 05 : clap
	.word @env11,@env3,@env17,@env0 ; 06 : rel hats
	.word @env24,@env8,@env1,@env0 ; 07 : funny drums
	.word @env6,@env13,@env15,@env0 ; 08 : TClead
	.word @env23,@env13,@env12,@env14 ; 09 : TClead 1

@env0:
	.byte $00,$c0,$7f,$00,$02
@env1:
	.byte $c1,$c0,$00,$01
@env2:
	.byte $00,$c9,$c8,$c7,$c6,$c6,$c5,$c5,$c4,$00,$08
@env3:
	.byte $bd,$c0,$00,$01
@env4:
	.byte $e3,$e2,$e1,$e0,$00,$03
@env5:
	.byte $00,$c8,$c4,$c2,$c0,$00,$04
@env6:
	.byte $00,$ce,$cd,$cc,$cb,$ca,$c8,$c7,$c5,$03,$c4,$c3,$03,$c2,$06,$c1,$05,$c0,$00,$11
@env7:
	.byte $00,$cd,$c9,$c5,$c2,$c1,$c0,$00,$06
@env8:
	.byte $c6,$cc,$ca,$cc,$00,$03
@env9:
	.byte $00,$cf,$7f,$00,$02
@env10:
	.byte $80,$bf,$f1,$00,$02
@env11:
	.byte $00,$c8,$c6,$c5,$c5,$c4,$c4,$c3,$02,$c2,$02,$c1,$02,$c0,$00,$0d
@env12:
	.byte $c0,$c1,$c2,$00,$00
@env13:
	.byte $c0,$7f,$00,$01
@env14:
	.byte $00,$be,$7f,$00,$02
@env15:
	.byte $c0,$c2,$c1,$00,$02
@env16:
	.byte $00,$cf,$ca,$cc,$ca,$c9,$c8,$c6,$c5,$c4,$c2,$c1,$c0,$00,$0c
@env17:
	.byte $7f,$00,$00
@env18:
	.byte $bc,$c1,$c0,$00,$02
@env19:
	.byte $00,$cf,$03,$c0,$00,$03
@env20:
	.byte $c0,$c1,$00,$00
@env21:
	.byte $c9,$cf,$00,$01
@env22:
	.byte $18,$cf,$ce,$cd,$cc,$cb,$ca,$c9,$c8,$c8,$c7,$c7,$c6,$02,$c5,$c5,$c4,$02,$c3,$03,$c2,$c2,$00,$15,$c2,$c2,$c1,$03,$c0,$00,$1c
@env23:
	.byte $00,$cc,$cb,$c9,$c7,$c7,$c6,$c5,$04,$c4,$c3,$03,$c2,$06,$c1,$05,$c0,$00,$10
@env24:
	.byte $00,$cf,$ce,$cc,$cb,$ca,$c7,$c6,$c5,$c5,$c6,$c8,$c9,$c8,$c7,$c5,$c4,$c3,$c3,$c2,$c2,$c1,$c1,$c0,$00,$17

@samples:
	.byte $00+.lobyte(FAMISTUDIO_DPCM_PTR),$a8,$0b,$40,$02 ; 00 BSV (Pitch:11)
	.byte $2a+.lobyte(FAMISTUDIO_DPCM_PTR),$7f,$0c,$40,$02 ; 01 BSV_1 (Pitch:12)
	.byte $11+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 02 fdbass A# (Pitch:15)
	.byte $23+.lobyte(FAMISTUDIO_DPCM_PTR),$45,$0f,$40,$00 ; 03 fdbass B (Pitch:15)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0d,$40,$00 ; 04 fdbass C (Pitch:13)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 05 fdbass C (Pitch:15)
	.byte $47+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 06 fdbass C# (Pitch:15)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0b,$40,$00 ; 07 fdbass D (Pitch:11)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0c,$40,$00 ; 08 fdbass D (Pitch:12)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0f,$40,$00 ; 09 fdbass D (Pitch:15)
	.byte $6b+.lobyte(FAMISTUDIO_DPCM_PTR),$2b,$0e,$40,$00 ; 0a fdkick (Pitch:14)
	.byte $0f+.lobyte(FAMISTUDIO_DPCM_PTR),$38,$0f,$40,$01 ; 0b is a (Pitch:15)
	.byte $2c+.lobyte(FAMISTUDIO_DPCM_PTR),$6d,$0f,$40,$01 ; 0c machine (Pitch:15)
	.byte $48+.lobyte(FAMISTUDIO_DPCM_PTR),$7e,$0b,$40,$01 ; 0d MUSIC_PCM_DS-geo (Pitch:11)
	.byte $4a+.lobyte(FAMISTUDIO_DPCM_PTR),$7a,$0a,$40,$02 ; 0e one (Pitch:10)
	.byte $00+.lobyte(FAMISTUDIO_DPCM_PTR),$41,$0f,$34,$00 ; 0f snare (Pitch:15)
	.byte $00+.lobyte(FAMISTUDIO_DPCM_PTR),$39,$0f,$40,$01 ; 10 this (Pitch:15)
	.byte $68+.lobyte(FAMISTUDIO_DPCM_PTR),$58,$0a,$40,$01 ; 11 three (Pitch:10)
	.byte $1e+.lobyte(FAMISTUDIO_DPCM_PTR),$37,$0f,$40,$01 ; 12 time (Pitch:15)
	.byte $69+.lobyte(FAMISTUDIO_DPCM_PTR),$52,$0a,$40,$02 ; 13 two (Pitch:10)

; The DPCM aligner used to be here
@song1ch0:
	.byte $46, $06, $77, $4f, $00, $90
@song1ref7:
	.byte $1f, $81, $1f, $81, $20, $81, $1f, $81, $20, $81, $1f, $81, $22, $81, $24, $81, $4f, $00
	.byte $41, $10
	.word @song1ref7
@song1ref28:
	.byte $4f, $03
@song1ref30:
	.byte $1f, $81, $1f, $81, $20, $81, $1f, $81, $24, $81, $20, $81, $1f, $81, $20, $81, $4f, $02
@song1ref48:
	.byte $1f, $81, $1f, $81, $26, $81, $27, $81, $2b, $81, $27, $81, $26, $81, $20, $81, $4f, $00
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $00
	.byte $41, $10
	.word @song1ref7
	.byte $41, $10
	.word @song1ref28
	.byte $4f, $01
	.byte $41, $0c
	.word @song1ref48
	.byte $27, $81, $2b, $81, $4f, $00
	.byte $41, $10
	.word @song1ref7
@song1ref91:
	.byte $4f, $02
@song1ref93:
	.byte $1f, $81, $1f, $1f, $20, $81, $1f, $81, $20, $81, $1f, $81, $16, $85
	.byte $41, $18
	.word @song1ref28
	.byte $27, $81, $26, $81, $27, $81, $26, $81, $4f, $00
	.byte $41, $10
	.word @song1ref7
	.byte $41, $0e
	.word @song1ref91
	.byte $41, $10
	.word @song1ref28
	.byte $4f, $01
	.byte $41, $0c
	.word @song1ref48
	.byte $27, $81, $27, $27, $4f, $00
	.byte $41, $10
	.word @song1ref7
	.byte $41, $0e
	.word @song1ref91
	.byte $41, $10
	.word @song1ref28
	.byte $4f, $01
	.byte $41, $0c
	.word @song1ref48
	.byte $27, $81, $27, $27, $44, $00
@song1ch1:
	.byte $77, $4f, $03, $92
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $03
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $02
	.byte $41, $10
	.word @song1ref30
	.byte $4f, $01
	.byte $41, $10
	.word @song1ref48
	.byte $4f, $03
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $03
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $02
	.byte $41, $10
	.word @song1ref30
	.byte $4f, $00
	.byte $41, $0c
	.word @song1ref48
	.byte $27, $81, $2b, $81, $4f, $03
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $01
	.byte $41, $0e
	.word @song1ref93
	.byte $4f, $02
	.byte $41, $10
	.word @song1ref30
	.byte $4f, $00, $1f, $81, $1f, $81, $26, $81, $27, $81, $27, $81, $26, $81, $27, $81, $26, $81, $4f, $03
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $01
	.byte $41, $0e
	.word @song1ref93
	.byte $4f, $02
	.byte $41, $10
	.word @song1ref30
	.byte $4f, $00
	.byte $41, $0c
	.word @song1ref48
	.byte $27, $81, $27, $27, $4f, $03
	.byte $41, $10
	.word @song1ref7
	.byte $4f, $01
	.byte $41, $0e
	.word @song1ref93
	.byte $4f, $02
	.byte $41, $10
	.word @song1ref30
	.byte $4f, $00
	.byte $41, $0c
	.word @song1ref48
	.byte $27, $81, $27, $27, $44, $00
@song1ch2:
	.byte $84, $25, $81, $00, $81, $86, $01, $81
@song1ref299:
	.byte $8a, $1d
@song1ref301:
	.byte $81, $84, $25, $81, $00, $81, $86, $01, $81, $00, $81, $84, $25, $81, $00, $81, $86, $01, $81, $8a, $18
	.byte $41, $0f
	.word @song1ref301
	.byte $8a, $1b
	.byte $41, $10
	.word @song1ref301
	.byte $41, $0f
	.word @song1ref301
	.byte $41, $11
	.word @song1ref299
	.byte $41, $0f
	.word @song1ref301
	.byte $8a, $1b
	.byte $41, $10
	.word @song1ref301
	.byte $41, $0f
	.word @song1ref301
	.byte $41, $11
	.word @song1ref299
	.byte $41, $0f
	.word @song1ref301
	.byte $8a, $1b
	.byte $41, $10
	.word @song1ref301
	.byte $41, $0f
	.word @song1ref301
	.byte $41, $11
	.word @song1ref299
	.byte $41, $0f
	.word @song1ref301
	.byte $8a, $1b
	.byte $41, $10
	.word @song1ref301
	.byte $41, $0f
	.word @song1ref301
	.byte $41, $11
	.word @song1ref299
	.byte $41, $0f
	.word @song1ref301
	.byte $8a, $1b
	.byte $41, $10
	.word @song1ref301
	.byte $41, $09
	.word @song1ref301
	.byte $44, $00
@song1ch3:
	.byte $7d
@song1ref393:
	.byte $82, $28, $81, $79, $8c, $2f, $81, $7d, $8e, $2f, $81, $80, $2f, $81, $79, $8c, $2f, $81, $7d, $80, $2f, $81, $8e, $2f
	.byte $81, $80, $2f, $81
	.byte $41, $10
	.word @song1ref393
	.byte $41, $10
	.word @song1ref393
	.byte $41, $10
	.word @song1ref393
	.byte $41, $10
	.word @song1ref393
	.byte $41, $10
	.word @song1ref393
	.byte $41, $10
	.word @song1ref393
	.byte $41, $10
	.word @song1ref393
	.byte $88, $20, $81, $80, $2f, $81, $48, $0a, $88, $2d, $00, $83, $80, $2f, $81, $82, $28, $81
@song1ref460:
	.byte $48, $0a, $88, $2d, $00, $80, $2f, $81
@song1ref468:
	.byte $82, $28, $81, $80, $2f, $81, $48, $0a, $88, $2d, $00, $82, $28, $81, $80, $2f, $81, $82, $28, $81, $7b, $48, $0a, $88
	.byte $2d, $00, $83
	.byte $41, $0c
	.word @song1ref468
	.byte $41, $10
	.word @song1ref460
	.byte $41, $10
	.word @song1ref460
	.byte $41, $10
	.word @song1ref460
	.byte $48, $0a, $88, $2d, $00, $83
	.byte $41, $0c
	.word @song1ref468
	.byte $41, $10
	.word @song1ref460
	.byte $41, $10
	.word @song1ref460
	.byte $41, $10
	.word @song1ref460
	.byte $48, $0a, $88, $2d, $00, $83
	.byte $41, $0c
	.word @song1ref468
	.byte $41, $10
	.word @song1ref460
	.byte $48, $0a, $88, $2d, $00, $80, $2f, $81, $44, $00
@song1ch4:
@song1ref548:
	.byte $0b, $85, $10, $85, $0b, $85, $10, $85, $0b, $85, $10, $85
	.byte $41, $0c
	.word @song1ref548
	.byte $41, $0c
	.word @song1ref548
	.byte $41, $0c
	.word @song1ref548
	.byte $41, $0c
	.word @song1ref548
	.byte $0b, $85, $10, $85
@song1ref576:
	.byte $05, $85, $10, $81, $05
@song1ref581:
	.byte $81, $0b, $85, $10, $85, $08, $85, $10, $81, $08, $81, $0b, $85, $10, $00, $83, $09, $85, $10, $81, $09
	.byte $41, $10
	.word @song1ref581
	.byte $41, $1a
	.word @song1ref576
	.byte $41, $10
	.word @song1ref581
	.byte $41, $1a
	.word @song1ref576
	.byte $41, $0e
	.word @song1ref581
	.byte $10, $10, $10, $44, $00
