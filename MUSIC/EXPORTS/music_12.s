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
.export _music_data_famidash_music12=music_data_famidash_music12
.endif

music_data_famidash_music12:
	.byte 4
	.word @instruments
	.word @samples-5
; 00 : retray
	.word @song0ch0
	.word @song0ch1
	.word @song0ch2
	.word @song0ch3
	.word @song0ch4
	.word 286,238
; 01 : Dry Out
	.word @song1ch0
	.word @song1ch1
	.word @song1ch2
	.word @song1ch3
	.word @song1ch4
	.word 296,247
; 02 : Jumper
	.word @song2ch0
	.word @song2ch1
	.word @song2ch2
	.word @song2ch3
	.word @song2ch4
	.word 366,305
; The DPCM aligner used to be here
; 04 : Problematic
	.word @song4ch0
	.word @song4ch1
	.word @song4ch2
	.word @song4ch3
	.word @song4ch4
	.word 262,218

.export music_data_famidash_music12
.global FAMISTUDIO_DPCM_PTR

@instruments:
	.word @env9,@env7,@env29,@env0 ; 00 : hat
	.word @env17,@env19,@env2,@env0 ; 01 : snare
	.word @env1,@env18,@env20,@env0 ; 02 : echo
	.word @env36,@env18,@env20,@env0 ; 03 : blank instant decay
	.word @env11,@env30,@env20,@env0 ; 04 : kick
	.word @env16,@env7,@env20,@env0 ; 05 : rel hats
	.word @env15,@env18,@env20,@env0 ; 06 : blank
	.word @env33,@env18,@env26,@env0 ; 07 : Instrument 4
	.word @env37,@env18,@env20,@env0 ; 08 : triangle pluck 2
	.word @env16,@env18,@env20,@env0 ; 09 : Instrument 2
	.word @env31,@env7,@env2,@env0 ; 0a : cymbal
	.word @env3,@env18,@env21,@env0 ; 0b : sample
	.word @env15,@env18,@env4,@env0 ; 0c : electroman lead
	.word @env10,@env18,@env20,@env0 ; 0d : clutterfunk sax
	.word @env14,@env18,@env20,@env0 ; 0e : DMC: drums + bass
	.word @env24,@env18,@env20,@env0 ; 0f : Instrument 1
	.word @env27,@env35,@env21,@env0 ; 10 : octave arp
	.word @env13,@env18,@env5,@env0 ; 11 : endgame lead
	.word @env27,@env18,@env20,@env0 ; 12 : quiet bass
	.word @env12,@env18,@env20,@env0 ; 13 : 02 but tri
	.word @env32,@env18,@env22,@env0 ; 14 : shift string

@env0:
	.byte $00,$c0,$7f,$00,$02
@env1:
	.byte $00,$cb,$c7,$c5,$c4,$c3,$c2,$c2,$c1,$c1,$c0,$c5,$c4,$c3,$c3,$c2,$c2,$c1,$c1,$c0,$00,$13
@env2:
	.byte $c1,$c0,$00,$01
@env3:
	.byte $00,$c9,$c8,$c7,$c6,$c6,$c5,$c5,$c4,$00,$08
@env4:
	.byte $c2,$c1,$03,$c0,$02,$c0,$00,$01
@env5:
	.byte $c2,$c2,$c0,$00,$00
@env6:
	.byte $c0,$c3,$c8,$cc,$00,$00
@env7:
	.byte $bd,$c0,$00,$01
@env8:
	.byte $c0,$c4,$c9,$cc,$00,$00
@env9:
	.byte $00,$c8,$c4,$c2,$c0,$00,$04
@env10:
	.byte $05,$ce,$cf,$00,$02,$cc,$c8,$c5,$c2,$c0,$00,$09
@env11:
	.byte $00,$cd,$c9,$c5,$c2,$c1,$c0,$00,$06
@env12:
	.byte $00,$c4,$02,$c5,$02,$c6,$02,$c0,$c5,$03,$c4,$03,$c0,$00,$0c
@env13:
	.byte $00,$cf,$cd,$cb,$c7,$c7,$ca,$00,$06
@env14:
	.byte $00,$cf,$7f,$00,$02
@env15:
	.byte $04,$cf,$00,$01,$ca,$c6,$c4,$c2,$c0,$00,$08
@env16:
	.byte $00,$c8,$c6,$c5,$c5,$c4,$c4,$c3,$02,$c2,$02,$c1,$02,$c0,$00,$0d
@env17:
	.byte $00,$cd,$cb,$c8,$c6,$c5,$c4,$c3,$c2,$c1,$c1,$c0,$00,$0b
@env18:
	.byte $c0,$7f,$00,$01
@env19:
	.byte $c6,$cc,$00,$01
@env20:
	.byte $7f,$00,$00
@env21:
	.byte $c2,$7f,$00,$00
@env22:
	.byte $c1,$c2,$c1,$c0,$00,$00
@env23:
	.byte $c0,$c5,$c8,$cc,$00,$00
@env24:
	.byte $00,$c3,$c6,$c5,$c5,$c4,$c4,$c3,$02,$c2,$02,$c1,$02,$c0,$00,$0d
@env25:
	.byte $00,$c0,$bb,$b8,$b7,$b9,$bd,$c3,$c7,$c9,$c8,$c5,$00,$01
@env26:
	.byte $c1,$7f,$00,$00
@env27:
	.byte $00,$c9,$c7,$c5,$00,$03
@env28:
	.byte $c0,$c0,$cc,$00,$00
@env29:
	.byte $c0,$c1,$00,$00
@env30:
	.byte $c9,$cf,$00,$01
@env31:
	.byte $18,$cf,$ce,$cd,$cc,$cb,$ca,$c9,$c8,$c8,$c7,$c7,$c6,$02,$c5,$c5,$c4,$02,$c3,$03,$c2,$c2,$00,$15,$c2,$c2,$c1,$03,$c0,$00,$1c
@env32:
	.byte $08,$c4,$c5,$c6,$08,$c5,$00,$05,$c5,$04,$c4,$07,$c3,$05,$c2,$02,$c1,$02,$c0,$00,$12
@env33:
	.byte $0b,$cf,$ca,$ca,$c9,$02,$c8,$02,$c7,$00,$08,$c7,$c5,$c3,$c2,$c1,$c0,$00,$10
@env34:
	.byte $00,$c0,$bf,$02,$c0,$c0,$c1,$c1,$c1,$00,$01
@env35:
	.byte $c0,$c0,$cc,$cc,$00,$00
@env36:
	.byte $00,$cf,$cf,$cb,$c8,$c5,$c3,$c2,$c1,$c0,$00,$09
@env37:
	.byte $00,$cf,$cf,$c0,$00,$03

@samples:
	.byte $00+.lobyte(FAMISTUDIO_DPCM_PTR),$a8,$0b,$40,$02 ; 00 BSV (Pitch:11)
	.byte $2a+.lobyte(FAMISTUDIO_DPCM_PTR),$7f,$0c,$40,$02 ; 01 BSV_1 (Pitch:12)
	.byte $11+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 02 fdbass A# (Pitch:15)
	.byte $23+.lobyte(FAMISTUDIO_DPCM_PTR),$45,$0f,$40,$00 ; 03 fdbass B (Pitch:15)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0a,$40,$00 ; 04 fdbass C (Pitch:10)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0c,$40,$00 ; 05 fdbass C (Pitch:12)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0e,$40,$00 ; 06 fdbass C (Pitch:14)
	.byte $35+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 07 fdbass C (Pitch:15)
	.byte $47+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0b,$40,$00 ; 08 fdbass C# (Pitch:11)
	.byte $47+.lobyte(FAMISTUDIO_DPCM_PTR),$47,$0f,$40,$00 ; 09 fdbass C# (Pitch:15)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$08,$40,$00 ; 0a fdbass D (Pitch:8)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0a,$40,$00 ; 0b fdbass D (Pitch:10)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0b,$40,$00 ; 0c fdbass D (Pitch:11)
	.byte $59+.lobyte(FAMISTUDIO_DPCM_PTR),$46,$0f,$40,$00 ; 0d fdbass D (Pitch:15)
	.byte $6b+.lobyte(FAMISTUDIO_DPCM_PTR),$2b,$0e,$40,$00 ; 0e fdkick (Pitch:14)
	.byte $0f+.lobyte(FAMISTUDIO_DPCM_PTR),$38,$0f,$40,$01 ; 0f is a (Pitch:15)
	.byte $2c+.lobyte(FAMISTUDIO_DPCM_PTR),$6d,$0f,$40,$01 ; 10 machine (Pitch:15)
	.byte $48+.lobyte(FAMISTUDIO_DPCM_PTR),$7e,$0b,$40,$01 ; 11 MUSIC_PCM_DS-geo (Pitch:11)
	.byte $5f+.lobyte(FAMISTUDIO_DPCM_PTR),$7a,$0a,$40,$02 ; 12 one (Pitch:10)
	.byte $00+.lobyte(FAMISTUDIO_DPCM_PTR),$41,$0f,$34,$00 ; 13 snare (Pitch:15)
	.byte $00+.lobyte(FAMISTUDIO_DPCM_PTR),$39,$0f,$40,$01 ; 14 this (Pitch:15)
	.byte $68+.lobyte(FAMISTUDIO_DPCM_PTR),$58,$0a,$40,$01 ; 15 three (Pitch:10)
	.byte $1e+.lobyte(FAMISTUDIO_DPCM_PTR),$37,$0f,$40,$01 ; 16 time (Pitch:15)
	.byte $4a+.lobyte(FAMISTUDIO_DPCM_PTR),$52,$0a,$40,$02 ; 17 two (Pitch:10)

@song0ch0:
	.byte $46, $06
@song0ch0loop:
	.byte $9f, $84, $19, $81, $00, $99, $9f, $9f, $76, $4f, $01
@song0ref15:
	.byte $9a
@song0ref16:
	.byte $1d, $45, $1d, $81, $45, $81, $22, $45, $22, $45, $25, $45, $20, $81, $45, $81, $78, $4f, $01
@song0ref35:
	.byte $22
@song0ref36:
	.byte $81, $45, $81, $22, $45, $20, $45, $22, $81, $45, $81, $22, $81, $45, $81, $7a, $4f, $01
@song0ref54:
	.byte $22, $45, $25, $81, $45, $81, $22, $45, $20, $81, $45, $81, $20, $81, $45, $81, $7b
@song0ref71:
	.byte $22, $45, $25, $81, $45, $81, $20, $45, $22, $81, $45, $81, $22, $81, $45, $81, $7c
	.byte $41, $10
	.word @song0ref16
	.byte $7d
	.byte $41, $10
	.word @song0ref35
	.byte $7e
	.byte $41, $10
	.word @song0ref54
	.byte $7f
	.byte $41, $10
	.word @song0ref71
	.byte $41, $10
	.word @song0ref16
	.byte $20
	.byte $41, $0f
	.word @song0ref36
	.byte $41, $10
	.word @song0ref54
	.byte $41, $10
	.word @song0ref71
	.byte $41, $10
	.word @song0ref16
	.byte $20
	.byte $41, $0f
	.word @song0ref36
	.byte $41, $10
	.word @song0ref54
	.byte $49, .lobyte(@env25), .hibyte(@env25), $22, $45, $9a, $25, $81, $45, $81, $20, $45, $22, $81, $45, $81, $50, $e9, $2e
	.byte $3a, $81, $49, .lobyte(@env0), .hibyte(@env0), $4a, $00, $81
@song0ref153:
	.byte $49, .lobyte(@env34), .hibyte(@env34), $1d, $81, $9a, $29, $81, $00, $81, $22, $81, $22, $81, $25, $81, $29, $81, $00
	.byte $81, $20
	.byte $41, $0f
	.word @song0ref36
	.byte $41, $10
	.word @song0ref54
	.byte $41, $10
	.word @song0ref71
	.byte $41, $11
	.word @song0ref153
	.byte $41, $0f
	.word @song0ref36
	.byte $41, $10
	.word @song0ref54
	.byte $41, $10
	.word @song0ref71
	.byte $a2, $22, $00, $29, $81, $00, $81, $25, $00, $22, $00, $25, $00, $29, $81, $00, $81, $9a, $20
	.byte $41, $0f
	.word @song0ref36
	.byte $41, $10
	.word @song0ref54
	.byte $41, $10
	.word @song0ref71
@song0ref223:
	.byte $84, $22, $81, $29, $85, $22, $81, $22, $81, $25, $81, $29, $85, $20, $85, $22, $81, $20, $81, $22, $85, $22, $85, $22
	.byte $81, $25, $85, $22, $81, $20, $85, $20, $85, $22, $81, $25, $85, $20, $81, $22, $85, $22, $85, $00, $9d, $9f, $9f, $9f
	.byte $42
	.word @song0ch0loop
@song0ch1:
@song0ch1loop:
	.byte $84, $1d, $85, $77, $1d, $85, $75, $1d, $85, $72, $1d, $85, $7f, $20, $85, $77, $20, $85, $75, $20, $85, $72, $20, $85
	.byte $7f, $22, $85, $77, $22, $85, $75, $22, $85, $72, $22, $85, $7f, $22, $85, $75, $22, $85, $7f, $22, $85, $22, $85, $75
	.byte $4e, $fe
	.byte $41, $10
	.word @song0ref15
	.byte $77
	.byte $41, $10
	.word @song0ref35
	.byte $79
	.byte $41, $20
	.word @song0ref54
	.byte $75, $4e, $fe
	.byte $41, $10
	.word @song0ref16
	.byte $77
	.byte $41, $10
	.word @song0ref35
	.byte $79
	.byte $41, $20
	.word @song0ref54
	.byte $75, $4e, $fe
	.byte $41, $10
	.word @song0ref16
	.byte $77
	.byte $41, $10
	.word @song0ref35
	.byte $79
	.byte $41, $20
	.word @song0ref54
	.byte $7f
	.byte $41, $10
	.word @song0ref16
	.byte $20
	.byte $41, $0f
	.word @song0ref36
	.byte $22, $45, $25, $81, $45, $81, $22, $45, $20, $81, $00, $81, $20, $81, $45, $81, $49, .lobyte(@env25), .hibyte(@env25)
	.byte $22, $81, $9a, $25, $81, $00, $81, $20, $81, $22, $81, $00, $81, $50, $e9, $2e, $3a, $81, $49, .lobyte(@env0), .hibyte(@env0)
	.byte $4a, $00, $81
@song0ref415:
	.byte $1d, $45, $29, $81, $45, $81, $22, $45, $22, $45, $25, $45, $29, $81, $45, $81, $20, $81, $45, $81, $22, $45, $20, $45
	.byte $50, $e9, $2e, $3a, $81, $00, $81, $22, $81, $45, $81, $22, $45, $25, $81, $45, $81, $22, $45, $50, $e2, $2c, $3c, $81
	.byte $00, $81, $20, $81, $45, $81
	.byte $41, $10
	.word @song0ref71
	.byte $41, $30
	.word @song0ref415
	.byte $41, $10
	.word @song0ref71
	.byte $41, $30
	.word @song0ref415
	.byte $41, $10
	.word @song0ref71
	.byte $41, $2f
	.word @song0ref223
	.byte $42
	.word @song0ch1loop
@song0ch2:
@song0ch2loop:
	.byte $8e
@song0ref492:
	.byte $1d, $81, $00, $81, $90, $1d, $00, $83, $1d, $00, $83, $1d, $00, $83, $8e, $20, $81, $00, $81, $90, $20, $00, $83, $20
	.byte $00, $83, $20, $00, $83, $8e, $22, $81, $00, $81, $90, $22, $00, $83, $22, $00, $83, $22, $00, $83, $8e, $22, $81, $00
	.byte $81, $90, $22, $00, $83, $8e, $22, $81, $00, $81, $22, $81, $00, $81
	.byte $41, $36
	.word @song0ref492
	.byte $41, $36
	.word @song0ref492
	.byte $41, $36
	.word @song0ref492
	.byte $41, $2a
	.word @song0ref492
	.byte $89, $22, $81, $00, $81, $22, $81, $00, $81
	.byte $41, $36
	.word @song0ref492
	.byte $41, $36
	.word @song0ref492
	.byte $41, $36
	.word @song0ref492
	.byte $41, $36
	.word @song0ref492
	.byte $9f, $9f, $9f, $9f, $42
	.word @song0ch2loop
@song0ch3:
@song0ch3loop:
	.byte $9f, $9f, $9f, $9f, $9f, $9f, $9f, $9f, $9f, $9f, $9f, $9f, $94, $40, $0a, $83, $45
@song0ref612:
	.byte $92, $40, $0a, $81, $88, $40, $01, $81, $40, $01, $81
@song0ref623:
	.byte $40, $01, $81, $92, $40, $0a, $81, $88, $40, $01, $81, $94, $40, $0a, $83, $45, $92, $40, $0a, $81, $88, $40, $01, $81
	.byte $40, $01, $81, $00, $81, $92, $40, $0a, $81, $00, $81, $78
@song0ref659:
	.byte $40, $0a, $81, $88, $40, $01, $81, $92, $40, $0a, $81, $88, $40, $01, $81, $92, $40, $0a, $81, $88, $40, $01, $75, $81
	.byte $92, $40, $0a, $81, $88, $40, $01, $81, $40, $01, $81, $40, $01, $81
	.byte $41, $15
	.word @song0ref612
	.byte $41, $25
	.word @song0ref623
	.byte $00, $9d, $7f, $94
@song0ref707:
	.byte $40, $0a, $83, $45, $00, $85, $82, $03, $81, $00, $89, $94
@song0ref719:
	.byte $40, $0a, $83, $45, $00, $85, $82, $03, $81, $00
@song0ref729:
	.byte $89, $94, $40, $0a, $83, $45, $00, $85, $82, $03, $81, $00, $81, $94, $40, $0a, $83, $45
	.byte $41, $1a
	.word @song0ref707
	.byte $41, $0d
	.word @song0ref729
	.byte $40, $0a, $83, $45, $00, $85, $82, $03, $81, $00, $89, $94, $21, $85, $74, $21, $85, $73, $21, $83, $72, $81, $21, $85
	.byte $7f
	.byte $41, $15
	.word @song0ref719
	.byte $40, $0a, $83, $45, $00, $85, $82, $03, $81, $00, $89, $94, $40, $0a, $85, $92, $01, $81, $88, $40, $01, $81, $7b, $92
	.byte $01, $81, $88, $40, $01, $81, $92, $01, $81, $88, $40, $01, $81, $78, $92
	.byte $41, $10
	.word @song0ref659
	.byte $78, $92
	.byte $41, $10
	.word @song0ref659
	.byte $00, $9d, $9f, $9f, $9f, $9f, $42
	.word @song0ch3loop
@song0ch4:
@song0ch4loop:
	.byte $0b, $9d, $05, $9d, $0c, $9d, $0c, $8d
@song0ref846:
	.byte $0c, $85, $0c, $85, $0b, $85, $0b, $85, $0b, $85, $0b, $85, $05, $85, $05, $85, $05, $85, $05, $85, $0c, $85, $0c, $85
	.byte $0c, $85, $0c, $85, $0c, $85, $0c, $85
	.byte $41, $20
	.word @song0ref846
	.byte $41, $20
	.word @song0ref846
	.byte $41, $1c
	.word @song0ref846
	.byte $00, $9d
@song0ref889:
	.byte $0f, $81
@song0ref891:
	.byte $0c, $81, $0c, $81, $0c, $81, $14, $81, $0c, $81, $0c, $81, $0c, $81
@song0ref905:
	.byte $0f, $81, $06, $81, $06, $81, $06, $81, $14, $81, $06, $81, $06, $81, $06, $81, $0f, $81, $05, $81, $05, $81, $05, $81
	.byte $14, $81, $05, $81, $0f, $81, $05, $81
	.byte $41, $12
	.word @song0ref889
	.byte $41, $2e
	.word @song0ref891
	.byte $41, $10
	.word @song0ref889
	.byte $00, $9d
	.byte $41, $20
	.word @song0ref905
	.byte $41, $10
	.word @song0ref889
	.byte $00, $9d, $9f, $9f, $9f, $9f, $9f, $9f, $9f, $42
	.word @song0ch4loop
@song1ch0:
	.byte $46, $06, $4f, $02, $84
@song1ref6:
	.byte $12, $12, $1e, $1e, $1c, $1c, $19, $19, $83, $15, $15, $14, $14, $10, $10, $12, $12, $81, $1c, $1c, $81, $19, $19, $83
	.byte $0d, $0d, $10, $10, $14, $14, $12, $12, $1c, $1c, $1e, $1e, $19, $19, $83, $14, $14, $15, $15, $17, $17, $1c, $1c, $81
	.byte $1e, $1e, $81, $19, $19, $83, $1e, $1e, $15, $15, $14, $14, $4f, $02
	.byte $41, $3c
	.word @song1ref6
	.byte $4f, $02
	.byte $41, $3c
	.word @song1ref6
	.byte $4f, $02
	.byte $41, $3c
	.word @song1ref6
	.byte $12, $12, $9b, $00, $83, $73, $8c, $50, $7f, $1e, $12
@song1ref92:
	.byte $43, $06, $71, $83, $73, $06, $43, $06, $71, $83, $73, $06, $43, $06, $50, $80, $12, $1e, $43, $12, $71, $83, $73, $12
	.byte $43, $12, $50, $7f, $1e, $10, $81, $71, $43, $04, $81, $73, $04, $43, $04, $71, $83, $73, $04, $43, $04, $50, $80, $10
	.byte $1c, $43, $10, $71, $83, $73, $10, $43, $10, $50, $7f, $1c, $0d, $81, $71, $43, $01, $81, $73, $01, $43, $01, $71, $83
	.byte $73, $01, $43, $01, $50, $80, $0d, $19, $81, $71, $43, $0d, $81, $73, $0d, $43, $0d, $50, $7f, $19, $10, $43, $04, $71
	.byte $83, $73, $04, $43, $04, $71, $83, $73, $50, $80, $10, $15, $43, $09, $71, $83, $73, $50, $17, $15, $14, $43, $08, $83
	.byte $50, $33, $14, $12
	.byte $41, $33
	.word @song1ref92
@song1ref219:
	.byte $7f, $84, $12, $12, $1e, $1e, $1c, $1c, $19, $19, $73, $8c, $06, $71, $83, $73, $06, $81, $12, $81, $71, $81, $7f, $84
	.byte $12, $12, $73, $8c, $12, $7f, $84, $1c, $1c, $71, $81, $7f, $19, $19, $73, $8c, $04, $71, $83, $73, $04, $81, $10, $81
	.byte $71, $81, $7f, $84, $12, $12, $1c, $1c, $1e, $1e, $19, $19, $73, $8c, $01, $71, $83, $73, $01, $81, $0d, $81, $71, $81
	.byte $7f, $84, $1c, $1c, $73, $8c, $0d, $7f, $84, $1e, $1e, $71, $81, $7f, $19, $19, $73, $8c, $04, $71, $83, $73, $09, $81
	.byte $71, $83, $73, $08
	.byte $41, $3b
	.word @song1ref219
	.byte $77
@song1ref323:
	.byte $4f, $00, $12, $81, $4f, $01, $83, $4f, $02, $83, $4f, $01, $83, $4f, $00, $15, $81, $4f, $01, $14, $81, $4f, $02, $86
	.byte $10, $81, $4f, $01, $8c, $14, $81, $4f, $00, $12, $81, $4f, $01, $83, $4f, $02, $83, $4f, $01, $19, $81, $4f, $00, $83
	.byte $4f, $01, $0d, $81, $4f, $02, $86, $10, $81, $4f, $01, $8c, $14, $81, $4f, $00, $12, $81, $4f, $01, $83, $4f, $02, $83
	.byte $4f, $01, $0d, $81, $4f, $00, $10, $81, $4f, $01, $12, $81, $4f, $02, $86, $15, $81, $4f, $01, $8c, $17, $81, $4f, $00
	.byte $12, $81, $4f, $01, $83, $4f, $02, $83, $4f, $01, $19, $81, $4f, $00, $1e, $81, $4f, $01, $83, $4f, $02, $86, $15, $81
	.byte $4f, $01, $8c, $14, $81
	.byte $41, $35
	.word @song1ref323
	.byte $7f, $4f, $02, $84
@song1ref455:
	.byte $12, $12, $1e, $1e, $1c, $1c, $19, $19, $85, $77, $21, $81, $20, $81, $1c, $7f, $12, $12, $81, $1c, $1c, $81, $19, $19
	.byte $81, $77, $25, $85, $19, $81, $1c, $7f, $12, $12, $1c, $1c, $1e, $1e, $19, $19, $81, $77, $19, $81, $1c, $81, $1e, $81
	.byte $21, $7f, $1c, $1c, $81, $1e, $1e, $81, $19, $19, $81, $77, $25, $81, $2a, $85, $21, $7f, $4f, $02
	.byte $41, $3a
	.word @song1ref455
	.byte $87, $44, $00
@song1ch1:
	.byte $7c, $a4
@song1ref532:
	.byte $06, $9d, $04, $9d, $01, $9d, $04, $9d, $06, $9d, $04, $9d, $01, $9d, $04, $9d
	.byte $41, $10
	.word @song1ref532
	.byte $06, $8d, $00, $8d, $78, $8c, $06, $81
@song1ref559:
	.byte $73, $83, $78, $06, $43, $06, $73, $83, $78, $06, $43, $06, $50, $80, $12, $1e, $43, $12, $73, $83, $78, $12, $43, $12
	.byte $50, $7f, $1e, $10, $81, $73, $43, $04, $81, $78, $04, $43, $04, $73, $83, $78, $04, $43, $04, $50, $80, $10, $1c, $43
	.byte $10, $73, $83, $78, $10, $43, $10, $50, $7f, $1c, $0d, $81, $73, $43, $01, $81, $78, $01, $43, $01, $73, $83, $78, $01
	.byte $43, $01, $50, $80, $0d, $19, $81, $73, $43, $0d, $81, $78, $0d, $43, $0d, $50, $7f, $19, $10, $43, $04, $73, $83, $78
	.byte $04, $43, $04, $73, $83, $78, $50, $80, $10, $15, $43, $09, $73, $83, $78, $50, $17, $15, $14, $43, $08, $50, $6b, $14
	.byte $10, $43, $04, $50, $c7, $10, $12, $43, $06
	.byte $41, $37
	.word @song1ref559
	.byte $41, $37
	.word @song1ref559
	.byte $41, $37
	.word @song1ref559
	.byte $41, $37
	.word @song1ref559
	.byte $41, $35
	.word @song1ref559
	.byte $7f, $4f, $02, $84
@song1ref707:
	.byte $1e, $8d, $21, $81, $20, $81, $1c, $81, $20, $81, $1e, $89, $25, $85, $19, $81, $1c, $81, $20, $81, $1e, $89, $19, $81
	.byte $1c, $81, $1e, $81, $21, $81, $23, $81, $1e, $89, $25, $81, $2a, $85, $21, $81, $20, $81, $4f, $02
	.byte $41, $2a
	.word @song1ref707
	.byte $1e, $85, $44, $00
@song1ch2:
	.byte $ff, $ff, $ff, $ff, $9f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $87, $44, $00
@song1ch3:
	.byte $ff, $ff
@song1ref778:
	.byte $88, $14, $81, $8a, $1f, $80, $21, $88, $14, $81, $80, $1f, $81, $88, $14, $81, $8a, $1f, $80, $21, $88, $14, $81, $80
	.byte $1f, $81
	.byte $41, $10
	.word @song1ref778
	.byte $41, $10
	.word @song1ref778
	.byte $41, $10
	.word @song1ref778
	.byte $88
@song1ref814:
	.byte $14, $81, $14, $81, $14, $81, $14, $81, $14, $81, $14, $81, $14, $81, $14, $81
	.byte $41, $10
	.word @song1ref814
	.byte $41, $10
	.word @song1ref814
	.byte $41, $10
	.word @song1ref814
	.byte $8f, $71, $9c, $20, $81, $72, $81, $73, $81, $74, $81, $76, $81, $78, $81, $7c, $81, $7f
@song1ref857:
	.byte $88, $14, $89, $14, $81, $82, $14, $8d, $88, $14, $83, $14, $83, $14, $81, $82, $14, $8d, $88, $14, $89, $14, $81, $82
	.byte $14, $8d, $88, $14, $83, $14, $83, $14, $81, $82, $14, $8d
	.byte $41, $1c
	.word @song1ref857
	.byte $41, $1c
	.word @song1ref857
	.byte $41, $1c
	.word @song1ref857
	.byte $41, $1c
	.word @song1ref857
	.byte $41, $1c
	.word @song1ref857
@song1ref908:
	.byte $88, $14, $89, $14, $81, $82, $14, $8d, $88, $14, $83, $14, $83, $82, $14, $91, $88, $14, $89, $14, $81, $82, $14, $8d
	.byte $88, $14, $83, $14, $83, $82, $14, $91
	.byte $41, $18
	.word @song1ref908
	.byte $87, $44, $00
@song1ch4:
	.byte $ff, $ff
@song1ref949:
	.byte $0f, $85, $0f, $85, $0f, $85, $0f, $85, $0f, $85, $0f, $85, $0f, $85, $0f, $85
	.byte $41, $10
	.word @song1ref949
@song1ref968:
	.byte $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81
	.byte $41, $10
	.word @song1ref968
	.byte $41, $10
	.word @song1ref968
	.byte $41, $10
	.word @song1ref968
	.byte $9f
@song1ref994:
	.byte $0f, $89, $0f, $81, $14, $8d, $0f, $83, $0f, $83, $0f, $81, $14, $8d, $0f, $89, $0f, $81, $14, $8d, $0f, $83, $0f, $83
	.byte $0f, $81, $14, $8d
	.byte $41, $1c
	.word @song1ref994
	.byte $41, $1c
	.word @song1ref994
	.byte $41, $1c
	.word @song1ref994
	.byte $41, $1c
	.word @song1ref994
	.byte $41, $1c
	.word @song1ref994
@song1ref1037:
	.byte $0f, $89, $0f, $81, $14, $8d, $0f, $83, $0f, $83, $14, $91, $0f, $89, $0f, $81, $14, $8d, $0f, $83, $0f, $83, $14, $91
	.byte $41, $18
	.word @song1ref1037
	.byte $87, $44, $00
@song2ch0:
	.byte $46, $08, $4f, $01, $92, $2a, $83, $9e
@song2ref9:
	.byte $2a, $81, $2a, $26, $81, $2d, $26, $81, $32, $2b, $81, $2d, $2a, $81, $2d, $83, $2a, $2d, $81, $26, $2a, $83, $2a, $81
	.byte $2a, $26, $81, $2d, $32, $81, $2d, $2b, $81, $2a, $28, $83, $26, $87, $4f, $02, $26, $4f, $02, $2a, $83
	.byte $41, $1e
	.word @song2ref9
	.byte $34, $36, $81, $37, $36, $81, $32, $34, $81, $32, $34, $81, $36, $74, $8c, $32, $81, $45, $7f, $9e
@song2ref77:
	.byte $36, $81, $36, $37, $81, $37, $36, $81, $36, $32, $81, $32, $36, $81, $36, $37, $81, $37, $39, $81, $39, $32, $81, $32
	.byte $41, $12
	.word @song2ref77
	.byte $30, $81, $31, $32, $81, $32
	.byte $41, $18
	.word @song2ref77
	.byte $41, $12
	.word @song2ref77
	.byte $30, $81, $31, $32, $81, $32
	.byte $41, $18
	.word @song2ref77
	.byte $41, $15
	.word @song2ref77
	.byte $3e, $81, $3e, $3c, $81, $3c, $3b, $81, $3b
@song2ref137:
	.byte $39, $81, $39, $37, $81, $36, $37, $81, $36, $37, $81, $36, $34, $81, $2d, $32, $81, $32, $36, $81, $36, $37, $81, $37
	.byte $41, $0e
	.word @song2ref137
	.byte $32, $7d, $4f, $01, $81, $75, $81, $7f
@song2ref172:
	.byte $2a, $2b, $81, $2a, $2b, $81, $2d, $83, $32, $2d, $81, $2b, $2a, $83, $2b, $81, $2a, $26, $81, $2a, $26, $81
	.byte $41, $0d
	.word @song2ref172
	.byte $81, $2d, $2b, $81, $2a, $2b, $81, $2d, $26, $81
	.byte $41, $16
	.word @song2ref172
	.byte $41, $11
	.word @song2ref172
	.byte $2b, $81, $2d, $26, $81
	.byte $41, $16
	.word @song2ref172
	.byte $41, $11
	.word @song2ref172
	.byte $2b, $81, $2d, $26, $81
	.byte $41, $16
	.word @song2ref172
	.byte $2a, $2b, $81, $2a, $2b, $81, $2d, $83, $32, $36, $81, $37, $36, $81, $32, $34, $81, $32, $34, $81, $36, $84, $32
@song2ref255:
	.byte $00, $a0, $1a, $00, $83, $1a, $00, $1a, $00, $81, $1a, $1e, $00, $81, $1e, $00, $1f, $1e, $00, $1e, $00, $81, $1e, $1f
	.byte $00, $81, $1f, $00, $21, $00, $81, $1f, $00, $81, $1f, $21, $00, $81, $21, $00, $26, $25, $00, $21, $00, $81, $21, $84
	.byte $0e
	.byte $41, $27
	.word @song2ref255
	.byte $25, $00, $81, $21, $00, $81, $21, $9e
@song2ref315:
	.byte $32, $87, $2b, $83, $2d, $81, $00, $81, $32, $83, $37, $83, $36, $81, $2b, $34, $83
	.byte $41, $0e
	.word @song2ref315
	.byte $37, $39, $83
	.byte $41, $11
	.word @song2ref315
	.byte $41, $0e
	.word @song2ref315
	.byte $37, $39, $83, $4f, $00, $a6
@song2ref350:
	.byte $26, $83, $2b, $83, $2a, $83, $28, $83, $26, $83, $2b, $83, $2a, $83, $28, $83, $26, $83, $2b, $83, $2a, $83, $28, $83
	.byte $2d, $83, $2b, $83, $2a, $83, $25, $83, $4f, $00
	.byte $41, $20
	.word @song2ref350
	.byte $92, $26, $83, $00, $87, $44, $00
@song2ch1:
	.byte $78, $4f, $02, $86
@song2ref399:
	.byte $0e, $74, $15, $78, $1a, $0e, $74, $15, $78, $1a, $0e, $74, $15, $78, $1a, $0e, $74, $15, $78, $1a, $12, $74, $15, $78
	.byte $1e, $12, $74, $15, $78, $1e, $12, $74, $15, $78, $1e, $12, $74, $15, $78, $1e, $13, $74, $17, $78, $1f, $13, $74, $17
	.byte $78, $1f, $13, $74, $17, $78, $1f, $13, $74, $17, $78, $1f, $15, $74, $19, $78, $21, $15, $74, $19, $78, $21, $15, $74
	.byte $19, $78, $21, $15, $74, $19, $78, $21, $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $4f, $02
	.byte $41, $30
	.word @song2ref399
	.byte $41, $0d
	.word @song2ref399
	.byte $74, $1a, $78, $1e, $12, $74, $1a, $78, $1e, $12, $74, $1a, $78, $1e, $12, $74, $1a, $78, $1e, $7a, $a8, $26, $81, $45
	.byte $2b, $81, $45, $2a, $81, $45, $28, $81, $45, $2d, $81, $45, $2b, $81, $45, $2a, $81, $45, $25, $81, $45, $26, $81, $45
	.byte $89, $44, $00
@song2ch2:
	.byte $df, $df, $df, $df, $df, $df, $00, $81, $9c
@song2ref613:
	.byte $1a, $00, $81, $1a, $00, $81, $1a, $00, $81, $1a, $00, $81, $1e, $00, $81, $1e, $00, $81, $1e, $00, $81, $1e, $00, $81
	.byte $1f, $00, $81, $1f, $00, $81, $1f, $00, $81, $1f, $00, $81, $21, $00, $81, $21, $00, $81, $21, $00, $81, $21, $00, $81
	.byte $41, $30
	.word @song2ref613
	.byte $41, $30
	.word @song2ref613
	.byte $41, $2e
	.word @song2ref613
@song2ref670:
	.byte $1a, $81, $00, $8f, $1a, $1e, $81, $00, $8f, $1e, $1f, $81, $00, $8f, $1f, $21, $81, $00, $91
	.byte $41, $13
	.word @song2ref670
	.byte $41, $13
	.word @song2ref670
	.byte $41, $13
	.word @song2ref670
	.byte $41, $13
	.word @song2ref670
	.byte $41, $13
	.word @song2ref670
	.byte $0e, $83, $00, $87, $44, $00
@song2ch3:
	.byte $7c, $96, $1f, $7a, $83, $74, $81, $71, $81, $70, $d5, $df, $7c, $1f, $7a, $83, $7f
@song2ref728:
	.byte $80
@song2ref729:
	.byte $22, $81, $22, $22, $81, $22, $22, $81, $22, $8a, $22, $83, $80, $22, $81, $22, $22, $81, $22, $22, $81, $22, $8a, $22
	.byte $83
	.byte $41, $15
	.word @song2ref728
	.byte $81, $80, $22
	.byte $41, $16
	.word @song2ref729
	.byte $41, $11
	.word @song2ref728
	.byte $82, $16, $81, $80, $22
@song2ref771:
	.byte $7c, $96, $1f, $7a, $83, $7f
@song2ref777:
	.byte $82, $14, $81, $80, $22, $22, $81, $22, $82, $14, $81, $80, $22, $8a, $22, $81, $80, $22, $82, $14, $81, $80, $22, $22
	.byte $81, $22, $82, $14, $81, $80, $22, $8a, $22, $81, $80, $22
	.byte $41, $18
	.word @song2ref777
	.byte $41, $18
	.word @song2ref777
	.byte $41, $15
	.word @song2ref777
	.byte $41, $1a
	.word @song2ref771
	.byte $41, $18
	.word @song2ref777
	.byte $41, $18
	.word @song2ref777
	.byte $41, $15
	.word @song2ref777
	.byte $41, $1a
	.word @song2ref771
	.byte $41, $18
	.word @song2ref777
	.byte $41, $18
	.word @song2ref777
	.byte $41, $15
	.word @song2ref777
	.byte $41, $1a
	.word @song2ref771
	.byte $41, $18
	.word @song2ref777
	.byte $41, $18
	.word @song2ref777
	.byte $41, $15
	.word @song2ref777
	.byte $41, $1a
	.word @song2ref771
	.byte $41, $18
	.word @song2ref777
	.byte $41, $18
	.word @song2ref777
	.byte $41, $15
	.word @song2ref777
	.byte $41, $1a
	.word @song2ref771
	.byte $41, $18
	.word @song2ref777
	.byte $41, $15
	.word @song2ref777
	.byte $78, $22, $81, $22, $7a, $22, $81, $22, $7b, $22, $81, $22, $22, $81, $22, $7c, $22, $81, $22, $7f, $22, $81, $22, $22
	.byte $81, $22, $82, $14, $83, $7c, $96, $1f, $7a, $83, $74, $81, $71, $81, $70, $85, $44, $00
@song2ch4:
	.byte $0f, $dd, $df, $0f, $dd, $d1, $0f, $0f, $83
@song2ref931:
	.byte $14, $83, $0f, $83, $14, $81, $0f, $83, $0f, $14, $83, $0f, $83, $14, $81, $0f, $83, $0f
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $41, $12
	.word @song2ref931
	.byte $14, $ad, $14, $83, $0f, $8d, $44, $00
; The DPCM aligner used to be here
@song4ch0:
	.byte $46, $06, $74, $4b, .lobyte(@env23), .hibyte(@env23), $8c, $20, $9d, $4b, .lobyte(@env6), .hibyte(@env6), $24, $9d
	.byte $4b, .lobyte(@env8), .hibyte(@env8), $21, $9d, $4b, .lobyte(@env23), .hibyte(@env23), $20, $9d, $4d, $20, $9d, $4b
	.byte .lobyte(@env6), .hibyte(@env6), $24, $9d, $4b, .lobyte(@env8), .hibyte(@env8), $21, $9d, $4b, .lobyte(@env23), .hibyte(@env23)
	.byte $20, $9d
@song4ref43:
	.byte $76, $4b, .lobyte(@env28), .hibyte(@env28), $4f, $00, $0d, $83, $00, $4d, $0d, $83, $00, $4b, .lobyte(@env18), .hibyte(@env18)
	.byte $4c, $98, $14, $79, $19, $00, $1c, $00, $14, $19, $1c, $75, $8c, $50, $2e, $19, $14, $81, $00, $50, $2e, $19, $14, $81
	.byte $00, $50, $2e, $19, $14, $81, $7b, $50, $10, $27, $20
@song4ref94:
	.byte $85, $4b, .lobyte(@env23), .hibyte(@env23), $14, $83, $00, $74, $4b, .lobyte(@env28), .hibyte(@env28), $0d, $83, $00
	.byte $4d, $0d, $83, $00, $4b, .lobyte(@env18), .hibyte(@env18), $4c, $98, $14, $79, $19, $00, $1c, $00, $14, $18, $14, $4b
	.byte .lobyte(@env6), .hibyte(@env6), $8c, $19, $8b, $00, $4d, $18, $8b, $00
	.byte $41, $16
	.word @song4ref43
	.byte $7b, $50, $06, $38, $31
	.byte $41, $18
	.word @song4ref94
	.byte $41, $2f
	.word @song4ref43
	.byte $41, $16
	.word @song4ref43
	.byte $7b, $50, $06, $38, $31
	.byte $41, $18
	.word @song4ref94
	.byte $9f, $9f, $9f, $9f, $9f, $9f, $9f, $9f, $87, $44, $00
@song4ch1:
@song4ref174:
	.byte $4b, .lobyte(@env28), .hibyte(@env28), $86, $20, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18), $4c, $84, $20, $00
	.byte $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $20, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18), $4c, $84, $20
	.byte $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $25, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18), $4c, $84
	.byte $25, $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $24, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18), $4c
	.byte $84, $24, $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $20, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18)
	.byte $4c, $84, $20, $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $20, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18)
	.byte $4c, $84, $20, $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $24, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18)
	.byte $4c, $84, $24, $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $21, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18)
	.byte $4c, $84, $21, $00, $7f
	.byte $41, $10
	.word @song4ref174
@song4ref297:
	.byte $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $27, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18), $4c, $84, $27
	.byte $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $25, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18), $4c, $84
	.byte $25, $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $24, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18), $4c
	.byte $84, $24, $00, $7f, $4b, .lobyte(@env28), .hibyte(@env28), $86, $21, $81, $7c, $4b, .lobyte(@env18), .hibyte(@env18)
	.byte $4c, $84, $21, $00, $7f
	.byte $41, $20
	.word @song4ref174
	.byte $7f
	.byte $41, $10
	.word @song4ref174
	.byte $41, $10
	.word @song4ref297
	.byte $4e, $00, $4b, .lobyte(@env8), .hibyte(@env8), $4f, $00, $8c
@song4ref376:
	.byte $1c, $83, $00, $4d, $1c, $83, $00, $4b, .lobyte(@env18), .hibyte(@env18), $4c, $4f, $02, $86, $14, $7f, $4e, $01, $19
	.byte $00, $1c, $00, $14, $19, $1c, $7c, $4e, $00, $8c, $50, $2e, $19, $14, $81, $00, $50, $2e, $19, $14, $81, $00, $50, $2e
	.byte $19, $14, $81, $00, $85, $79, $4e, $02, $4f, $01, $50, $08, $33, $2c
@song4ref433:
	.byte $85, $7c, $4e, $00, $4b, .lobyte(@env8), .hibyte(@env8), $4f, $00, $1c, $83, $00, $4d, $1c, $83, $00, $4b, .lobyte(@env18)
	.byte .hibyte(@env18), $4c, $4f, $02, $86, $14, $7f, $4e, $01, $19, $00, $1c, $00, $14, $18, $14, $79, $4e, $00, $4f, $03
	.byte $8c, $09, $8d, $08, $8d, $7c, $4e, $00, $4b, .lobyte(@env8), .hibyte(@env8), $4f, $00
	.byte $41, $18
	.word @song4ref376
	.byte $79, $4e, $02, $4f, $01, $50, $03, $44, $3d
	.byte $41, $13
	.word @song4ref433
	.byte $7c, $4e, $00, $4b, .lobyte(@env8), .hibyte(@env8), $4f, $00
	.byte $41, $2c
	.word @song4ref376
	.byte $7c, $4e, $00, $4b, .lobyte(@env8), .hibyte(@env8), $4f, $00
	.byte $41, $18
	.word @song4ref376
	.byte $79, $4e, $02, $4f, $01, $50, $03, $44, $3d
	.byte $41, $13
	.word @song4ref433
	.byte $7f, $4b, .lobyte(@env28), .hibyte(@env28)
@song4ref538:
	.byte $86, $19, $7c, $4d, $84, $19, $7f, $4d, $86, $18, $7c, $4d, $84, $18, $7f, $4d, $86, $1c, $7c, $4d, $84, $1c, $7f, $4d
	.byte $86, $18, $7c, $4d, $84, $18, $7f, $4d, $86, $1b, $7c, $4d, $84, $1b, $7f, $4d, $86, $19, $7c, $4d, $84, $19, $7f, $4d
	.byte $86, $15, $7c, $4d, $84, $15, $7f, $4d, $86, $14, $7c, $4d, $84, $14, $7f, $4d, $86, $18, $7c, $4d, $84, $18, $7f, $4d
	.byte $86, $14, $7c, $4d, $84, $14, $7f, $4d, $86, $19, $7c, $4d, $84, $19, $7f, $4d, $86, $14, $7c, $4d, $84, $14, $7f, $4d
	.byte $86, $1b, $7c, $4d, $84, $1b, $7f, $4d, $86, $14, $7c, $4d, $84, $14, $7f, $4d, $86, $1c, $7c, $4d, $84, $1c, $7f, $4d
	.byte $86, $18, $7c, $4d, $84, $18, $7f, $4d
	.byte $41, $20
	.word @song4ref538
	.byte $7f, $4d
	.byte $41, $20
	.word @song4ref538
	.byte $7f, $4d
	.byte $41, $20
	.word @song4ref538
	.byte $00, $85, $44, $00
@song4ch2:
	.byte $8c, $14, $9d, $18, $9d, $15, $9d, $14, $9d, $14, $9d, $18, $9d, $15, $9d, $14, $9d, $a2
@song4ref702:
	.byte $19, $00, $19, $00, $19, $00, $19, $00, $19, $00, $19, $00, $19, $00, $19, $00, $14, $00, $14, $00, $14, $00, $14, $00
	.byte $14, $00, $14, $00, $14, $00, $14, $00
	.byte $41, $20
	.word @song4ref702
	.byte $41, $20
	.word @song4ref702
	.byte $41, $20
	.word @song4ref702
	.byte $41, $20
	.word @song4ref702
	.byte $41, $20
	.word @song4ref702
	.byte $41, $20
	.word @song4ref702
	.byte $41, $20
	.word @song4ref702
	.byte $9c
@song4ref756:
	.byte $19, $85, $25, $00, $83, $17, $85, $23, $00, $83, $14, $85, $20, $00, $83, $18, $85, $27, $00, $83
	.byte $41, $14
	.word @song4ref756
	.byte $41, $14
	.word @song4ref756
	.byte $19, $8d, $17, $8d, $14, $8d, $18, $8d, $00, $85, $44, $00
@song4ch3:
	.byte $94, $21, $8d, $00, $8d, $9f, $9f, $9f, $9f, $9f, $88, $1a, $81, $1a, $81, $1a, $81, $1a, $81, $1a, $81, $1a, $81, $1a
	.byte $81, $1a, $81, $1a, $1a, $1a, $1a, $1a, $1a, $1a, $1a, $82, $21, $22, $21, $22, $21, $22, $21, $22, $94
@song4ref840:
	.byte $1d, $81, $80, $22, $22, $82, $21, $00, $80, $22, $22, $88, $19, $00, $80, $22, $22, $82, $21, $80, $22, $22, $22, $88
	.byte $19, $00, $80, $22, $22, $82, $21, $00, $80, $22, $22, $88, $19, $00, $80, $22, $22, $82, $21, $80, $22, $94, $1f, $81
	.byte $41, $20
	.word @song4ref840
	.byte $41, $20
	.word @song4ref840
	.byte $41, $20
	.word @song4ref840
	.byte $41, $20
	.word @song4ref840
	.byte $41, $20
	.word @song4ref840
	.byte $41, $20
	.word @song4ref840
	.byte $41, $20
	.word @song4ref840
	.byte $1e, $95, $00, $85, $9f, $9f, $9b, $22, $81, $21, $8d, $00, $8d, $9f, $9f, $9f, $21, $85, $44, $00
@song4ch4:
	.byte $9f, $9f, $9f, $9f, $9f, $9f, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $81, $0f, $0f
	.byte $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f
@song4ref968:
	.byte $0f, $81, $06, $81, $14, $81, $06, $81, $0f, $81, $06, $81, $14, $81, $06, $81, $0f, $81, $05, $81, $14, $81, $05, $81
	.byte $0f, $81, $05, $81, $14, $81, $05, $81
	.byte $41, $20
	.word @song4ref968
	.byte $41, $20
	.word @song4ref968
	.byte $41, $20
	.word @song4ref968
	.byte $41, $20
	.word @song4ref968
	.byte $41, $20
	.word @song4ref968
	.byte $41, $20
	.word @song4ref968
	.byte $41, $20
	.word @song4ref968
@song4ref1021:
	.byte $06, $85, $08, $00, $83, $09, $85, $03, $00, $83, $05, $85, $07, $00, $83, $0d, $85, $0e, $00, $83
	.byte $41, $14
	.word @song4ref1021
	.byte $41, $14
	.word @song4ref1021
	.byte $06, $8d, $09, $8d, $05, $8d, $0d, $8d, $00, $85, $44, $00
