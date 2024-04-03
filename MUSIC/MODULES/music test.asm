; Dn-FamiTracker exported music data: music_master.dnm
;

; Module header
	.word ft_song_list
	.word ft_instrument_list
	.word ft_sample_list
	.word ft_samples
	.word ft_groove_list
	.byte 1 ; flags
	.word 3600 ; NTSC speed
	.word 3000 ; PAL speed

; Instrument pointer list
ft_instrument_list:
	.word ft_inst_0
	.word ft_inst_1
	.word ft_inst_2
	.word ft_inst_3
	.word ft_inst_4
	.word ft_inst_5
	.word ft_inst_6
	.word ft_inst_7
	.word ft_inst_8
	.word ft_inst_9
	.word ft_inst_10
	.word ft_inst_11
	.word ft_inst_12
	.word ft_inst_13
	.word ft_inst_14
	.word ft_inst_15
	.word ft_inst_16
	.word ft_inst_17
	.word ft_inst_18
	.word ft_inst_19
	.word ft_inst_20
	.word ft_inst_21
	.word ft_inst_22
	.word ft_inst_23
	.word ft_inst_24

; Instruments
ft_inst_0:
	.byte 0
	.byte $01
	.word ft_seq_2a03_40

ft_inst_1:
	.byte 0
	.byte $11
	.word ft_seq_2a03_35
	.word ft_seq_2a03_14

ft_inst_2:
	.byte 0
	.byte $11
	.word ft_seq_2a03_10
	.word ft_seq_2a03_14

ft_inst_3:
	.byte 0
	.byte $01
	.word ft_seq_2a03_0

ft_inst_4:
	.byte 0
	.byte $01
	.word ft_seq_2a03_50

ft_inst_5:
	.byte 0
	.byte $11
	.word ft_seq_2a03_55
	.word ft_seq_2a03_9

ft_inst_6:
	.byte 0
	.byte $11
	.word ft_seq_2a03_45
	.word ft_seq_2a03_19

ft_inst_7:
	.byte 0
	.byte $03
	.word ft_seq_2a03_15
	.word ft_seq_2a03_1

ft_inst_8:
	.byte 0
	.byte $03
	.word ft_seq_2a03_20
	.word ft_seq_2a03_6

ft_inst_9:
	.byte 0
	.byte $03
	.word ft_seq_2a03_25
	.word ft_seq_2a03_21

ft_inst_10:
	.byte 0
	.byte $03
	.word ft_seq_2a03_50
	.word ft_seq_2a03_21

ft_inst_11:
	.byte 0
	.byte $05
	.word ft_seq_2a03_35
	.word ft_seq_2a03_2

ft_inst_12:
	.byte 0
	.byte $13
	.word ft_seq_2a03_55
	.word ft_seq_2a03_11
	.word ft_seq_2a03_14

ft_inst_13:
	.byte 0
	.byte $01
	.word ft_seq_2a03_60

ft_inst_14:
	.byte 0
	.byte $01
	.word ft_seq_2a03_70

ft_inst_15:
	.byte 0
	.byte $01
	.word ft_seq_2a03_75

ft_inst_16:
	.byte 0
	.byte $01
	.word ft_seq_2a03_170

ft_inst_17:
	.byte 0
	.byte $01
	.word ft_seq_2a03_175

ft_inst_18:
	.byte 0
	.byte $03
	.word ft_seq_2a03_30
	.word ft_seq_2a03_21

ft_inst_19:
	.byte 0
	.byte $01
	.word ft_seq_2a03_165

ft_inst_20:
	.byte 0
	.byte $01
	.word ft_seq_2a03_150

ft_inst_21:
	.byte 0
	.byte $11
	.word ft_seq_2a03_160
	.word ft_seq_2a03_59

ft_inst_22:
	.byte 0
	.byte $11
	.word ft_seq_2a03_180
	.word ft_seq_2a03_64

ft_inst_23:
	.byte 0
	.byte $03
	.word ft_seq_2a03_185
	.word ft_seq_2a03_61

ft_inst_24:
	.byte 0
	.byte $03
	.word ft_seq_2a03_190
	.word ft_seq_2a03_66

; Sequences
ft_seq_2a03_0:
	.byte $10, $FF, $00, $00, $03, $06, $05, $05, $04, $04, $03, $03, $02, $02, $02, $01, $01, $01, $01, $00
ft_seq_2a03_1:
	.byte $02, $FF, $00, $00, $06, $0F
ft_seq_2a03_2:
	.byte $02, $01, $00, $00, $00, $60
ft_seq_2a03_6:
	.byte $02, $FF, $00, $00, $06, $09
ft_seq_2a03_9:
	.byte $01, $FF, $00, $00, $03
ft_seq_2a03_10:
	.byte $0F, $FF, $00, $00, $0A, $07, $05, $03, $02, $01, $01, $00, $02, $02, $01, $01, $01, $00, $00
ft_seq_2a03_11:
	.byte $04, $00, $00, $00, $00, $00, $0C, $0C
ft_seq_2a03_14:
	.byte $01, $FF, $00, $00, $02
ft_seq_2a03_15:
	.byte $06, $FF, $00, $00, $0A, $07, $04, $02, $01, $00
ft_seq_2a03_19:
	.byte $01, $FF, $00, $00, $00
ft_seq_2a03_20:
	.byte $0B, $FF, $00, $00, $0D, $09, $07, $05, $04, $03, $02, $02, $01, $01, $00
ft_seq_2a03_21:
	.byte $02, $FF, $00, $00, $FC, $00
ft_seq_2a03_25:
	.byte $04, $FF, $00, $00, $08, $04, $02, $00
ft_seq_2a03_30:
	.byte $20, $FF, $19, $00, $0F, $0E, $0D, $0C, $0B, $0A, $09, $08, $08, $07, $07, $06, $06, $06, $05, $05
	.byte $04, $04, $04, $03, $03, $03, $03, $02, $02, $02, $02, $01, $01, $01, $01, $00
ft_seq_2a03_35:
	.byte $08, $FF, $00, $00, $09, $08, $07, $06, $06, $05, $05, $04
ft_seq_2a03_40:
	.byte $01, $FF, $00, $00, $0F
ft_seq_2a03_45:
	.byte $14, $FF, $00, $00, $04, $04, $04, $05, $05, $05, $06, $06, $06, $05, $05, $05, $05, $05, $04, $04
	.byte $04, $04, $04, $00
ft_seq_2a03_50:
	.byte $10, $FF, $00, $00, $08, $06, $05, $05, $04, $04, $03, $03, $03, $02, $02, $02, $01, $01, $01, $00
ft_seq_2a03_55:
	.byte $03, $FF, $00, $00, $09, $07, $05
ft_seq_2a03_59:
	.byte $02, $00, $00, $00, $01, $02
ft_seq_2a03_60:
	.byte $02, $FF, $00, $00, $0F, $00
ft_seq_2a03_61:
	.byte $03, $00, $00, $00, $FC, $01, $00
ft_seq_2a03_64:
	.byte $02, $00, $00, $00, $01, $00
ft_seq_2a03_66:
	.byte $03, $FF, $00, $00, $FC, $01, $00
ft_seq_2a03_70:
	.byte $05, $FF, $00, $00, $0F, $0F, $0F, $0F, $00
ft_seq_2a03_75:
	.byte $17, $FF, $0C, $00, $01, $02, $03, $03, $04, $04, $04, $04, $04, $04, $04, $03, $03, $03, $03, $02
	.byte $02, $02, $01, $01, $01, $01, $00
ft_seq_2a03_150:
	.byte $07, $FF, $02, $00, $0C, $0F, $0C, $08, $05, $02, $00
ft_seq_2a03_160:
	.byte $13, $FF, $0C, $00, $02, $03, $04, $04, $04, $04, $04, $04, $04, $04, $03, $03, $03, $03, $03, $02
	.byte $02, $02, $01
ft_seq_2a03_165:
	.byte $1C, $FF, $00, $00, $07, $06, $06, $05, $04, $04, $03, $03, $03, $03, $03, $03, $02, $02, $02, $02
	.byte $02, $02, $02, $01, $01, $01, $01, $01, $01, $01, $01, $00
ft_seq_2a03_170:
	.byte $06, $FF, $01, $00, $0F, $0B, $08, $05, $02, $00
ft_seq_2a03_175:
	.byte $0A, $FF, $00, $00, $0F, $0F, $0F, $0D, $0A, $08, $06, $03, $01, $00
ft_seq_2a03_180:
	.byte $13, $FF, $0C, $00, $03, $04, $05, $05, $05, $05, $05, $05, $05, $05, $04, $04, $04, $04, $04, $03
	.byte $03, $03, $02
ft_seq_2a03_185:
	.byte $03, $00, $00, $00, $0F, $0D, $0B
ft_seq_2a03_190:
	.byte $0C, $FF, $00, $00, $0F, $0D, $0B, $0A, $09, $08, $06, $05, $04, $02, $01, $00

; DPCM instrument list (pitch, sample index)
ft_sample_list:
	.byte 5, 63, 0
	.byte 6, 63, 0
	.byte 15, 0, 0
	.byte 7, 63, 3
	.byte 7, 63, 6
	.byte 8, 63, 3
	.byte 8, 63, 6
	.byte 9, 63, 0
	.byte 9, 63, 3
	.byte 10, 63, 0
	.byte 10, 63, 3
	.byte 10, 63, 6
	.byte 11, 63, 3
	.byte 11, 63, 6
	.byte 12, 63, 0
	.byte 12, 63, 3
	.byte 12, 63, 6
	.byte 13, 63, 9
	.byte 13, 63, 0
	.byte 13, 63, 3
	.byte 13, 63, 6
	.byte 14, 63, 0
	.byte 14, 63, 3
	.byte 14, 63, 6
	.byte 15, 63, 12
	.byte 15, 63, 9
	.byte 15, 63, 0
	.byte 15, 63, 6
	.byte 15, 63, 15
	.byte 15, 41, 18

; DPCM samples list (location, size, bank)
ft_samples:
	.byte <((ft_sample_0 - $C000) >> 6), 63, <.bank(ft_sample_0)
	.byte <((ft_sample_1 - $C000) >> 6), 62, <.bank(ft_sample_1)
	.byte <((ft_sample_2 - $C000) >> 6), 63, <.bank(ft_sample_2)
	.byte <((ft_sample_3 - $C000) >> 6), 63, <.bank(ft_sample_3)
	.byte <((ft_sample_4 - $C000) >> 6), 62, <.bank(ft_sample_4)
	.byte <((ft_sample_5 - $C000) >> 6), 37, <.bank(ft_sample_5)
	.byte <((ft_sample_6 - $C000) >> 6), 65, <.bank(ft_sample_6)

; Groove list
ft_groove_list:
	.byte $00
; Grooves (size, terms)

; Song pointer list
ft_song_list:
	.word ft_song_0
	.word ft_song_1
	.word ft_song_2
	.word ft_song_3
	.word ft_song_4
	.word ft_song_5
	.word ft_song_6
	.word ft_song_7
	.word ft_song_8
	.word ft_song_9
	.word ft_song_10
	.word ft_song_11
	.word ft_song_12
	.word ft_song_13
	.word ft_song_14
	.word ft_song_15
	.word ft_song_16
	.word ft_song_17
	.word ft_song_18
	.word ft_song_19
	.word ft_song_20
	.word ft_song_21
	.word ft_song_22
	.word ft_song_23
	.word ft_song_24
	.word ft_song_25
	.word ft_song_26
	.word ft_song_27
	.word ft_song_28
	.word ft_song_29
	.word ft_song_30
	.word ft_song_31

; Song info
ft_song_0:
	.word ft_s0_frames
	.byte 15	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 160	; tempo
	.byte 0	; groove position
	.byte 3	; initial bank

ft_song_1:
	.word ft_s1_frames
	.byte 13	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 142	; tempo
	.byte 0	; groove position
	.byte 3	; initial bank

ft_song_2:
	.word ft_s2_frames
	.byte 17	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 163	; tempo
	.byte 0	; groove position
	.byte 3	; initial bank

ft_song_3:
	.word ft_s3_frames
	.byte 14	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 145	; tempo
	.byte 0	; groove position
	.byte 3	; initial bank

ft_song_4:
	.word ft_s4_frames
	.byte 6	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 141	; tempo
	.byte 0	; groove position
	.byte 3	; initial bank

ft_song_5:
	.word ft_s5_frames
	.byte 16	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 170	; tempo
	.byte 0	; groove position
	.byte 4	; initial bank

ft_song_6:
	.word ft_s6_frames
	.byte 17	; frame count
	.byte 48	; pattern length
	.byte 8	; speed
	.byte 175	; tempo
	.byte 0	; groove position
	.byte 4	; initial bank

ft_song_7:
	.word ft_s7_frames
	.byte 9	; frame count
	.byte 32	; pattern length
	.byte 6	; speed
	.byte 143	; tempo
	.byte 0	; groove position
	.byte 4	; initial bank

ft_song_8:
	.word ft_s8_frames
	.byte 14	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 140	; tempo
	.byte 0	; groove position
	.byte 4	; initial bank

ft_song_9:
	.word ft_s9_frames
	.byte 1	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_10:
	.word ft_s10_frames
	.byte 6	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 140	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_11:
	.word ft_s11_frames
	.byte 10	; frame count
	.byte 24	; pattern length
	.byte 8	; speed
	.byte 130	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_12:
	.word ft_s12_frames
	.byte 1	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_13:
	.word ft_s13_frames
	.byte 8	; frame count
	.byte 16	; pattern length
	.byte 6	; speed
	.byte 128	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_14:
	.word ft_s14_frames
	.byte 1	; frame count
	.byte 128	; pattern length
	.byte 3	; speed
	.byte 127	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_15:
	.word ft_s15_frames
	.byte 1	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_16:
	.word ft_s16_frames
	.byte 4	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 135	; tempo
	.byte 0	; groove position
	.byte 5	; initial bank

ft_song_17:
	.word ft_s17_frames
	.byte 1	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 6	; initial bank

ft_song_18:
	.word ft_s18_frames
	.byte 5	; frame count
	.byte 32	; pattern length
	.byte 6	; speed
	.byte 148	; tempo
	.byte 0	; groove position
	.byte 6	; initial bank

ft_song_19:
	.word ft_s19_frames
	.byte 15	; frame count
	.byte 48	; pattern length
	.byte 8	; speed
	.byte 135	; tempo
	.byte 0	; groove position
	.byte 6	; initial bank

ft_song_20:
	.word ft_s20_frames
	.byte 2	; frame count
	.byte 64	; pattern length
	.byte 3	; speed
	.byte 112	; tempo
	.byte 0	; groove position
	.byte 6	; initial bank

ft_song_21:
	.word ft_s21_frames
	.byte 2	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 129	; tempo
	.byte 0	; groove position
	.byte 6	; initial bank

ft_song_22:
	.word ft_s22_frames
	.byte 129	; frame count
	.byte 32	; pattern length
	.byte 5	; speed
	.byte 214	; tempo
	.byte 0	; groove position
	.byte 7	; initial bank

ft_song_23:
	.word ft_s23_frames
	.byte 4	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 128	; tempo
	.byte 0	; groove position
	.byte 8	; initial bank

ft_song_24:
	.word ft_s24_frames
	.byte 4	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 129	; tempo
	.byte 0	; groove position
	.byte 8	; initial bank

ft_song_25:
	.word ft_s25_frames
	.byte 32	; frame count
	.byte 32	; pattern length
	.byte 6	; speed
	.byte 162	; tempo
	.byte 0	; groove position
	.byte 8	; initial bank

ft_song_26:
	.word ft_s26_frames
	.byte 2	; frame count
	.byte 32	; pattern length
	.byte 6	; speed
	.byte 162	; tempo
	.byte 0	; groove position
	.byte 9	; initial bank

ft_song_27:
	.word ft_s27_frames
	.byte 38	; frame count
	.byte 32	; pattern length
	.byte 3	; speed
	.byte 140	; tempo
	.byte 0	; groove position
	.byte 9	; initial bank

ft_song_28:
	.word ft_s28_frames
	.byte 19	; frame count
	.byte 64	; pattern length
	.byte 3	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 9	; initial bank

ft_song_29:
	.word ft_s29_frames
	.byte 1	; frame count
	.byte 64	; pattern length
	.byte 11	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 9	; initial bank

ft_song_30:
	.word ft_s30_frames
	.byte 1	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 9	; initial bank

ft_song_31:
	.word ft_s31_frames
	.byte 1	; frame count
	.byte 64	; pattern length
	.byte 6	; speed
	.byte 150	; tempo
	.byte 0	; groove position
	.byte 9	; initial bank


;
; Pattern and frame data for all songs below
;

; Bank 1
ft_s0_frames:
	.word ft_s0f0
	.word ft_s0f1
	.word ft_s0f2
	.word ft_s0f3
	.word ft_s0f4
	.word ft_s0f5
	.word ft_s0f6
	.word ft_s0f7
	.word ft_s0f8
	.word ft_s0f9
	.word ft_s0f10
	.word ft_s0f11
	.word ft_s0f12
	.word ft_s0f13
	.word ft_s0f14
ft_s0f0:
	.word ft_s0p1c0, ft_s0p0c0, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s0f1:
	.word ft_s0p1c0, ft_s0p0c0, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s0f2:
	.word ft_s0p1c0, ft_s0p1c1, ft_s0p3c2, ft_s0p2c3, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s0f3:
	.word ft_s0p1c0, ft_s0p1c1, ft_s0p3c2, ft_s0p2c3, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s0f4:
	.word ft_s0p0c0, ft_s0p2c1, ft_s0p0c2, ft_s0p3c3, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s0f5:
	.word ft_s0p1c0, ft_s0p1c1, ft_s0p1c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f6:
	.word ft_s0p1c0, ft_s0p1c1, ft_s0p2c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f7:
	.word ft_s0p1c0, ft_s0p1c1, ft_s0p1c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f8:
	.word ft_s0p1c0, ft_s0p1c1, ft_s0p2c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f9:
	.word ft_s0p0c0, ft_s0p0c0, ft_s0p1c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f10:
	.word ft_s0p0c0, ft_s0p0c0, ft_s0p2c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f11:
	.word ft_s0p0c0, ft_s0p0c0, ft_s0p1c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f12:
	.word ft_s0p0c0, ft_s0p0c0, ft_s0p2c2, ft_s0p4c3, ft_s0p2c4
	.byte $03, $03, $03, $03, $03
ft_s0f13:
	.word ft_s0p4c0, ft_s0p4c1, ft_s0p0c2, ft_s0p0c2, ft_s0p3c4
	.byte $03, $03, $03, $03, $03
ft_s0f14:
	.word ft_s0p5c0, ft_s0p5c1, ft_s0p0c2, ft_s0p0c2, ft_s0p3c4
	.byte $03, $03, $03, $03, $03
; Bank 1
ft_s0p0c0:
	.byte $7F, $3F

; Bank 2
ft_s0p0c2:
	.byte $00, $3F

; Bank 2
ft_s0p1c0:
	.byte $E2, $93, $02, $FF, $31, $01, $82, $00, $FF, $38, $80, $20, $F3, $31, $E2, $FF, $31, $80, $20, $F3
	.byte $38, $E2, $FF, $38, $80, $20, $F3, $31, $E2, $FF, $31, $80, $20, $F3, $38, $E2, $FF, $38, $80, $20
	.byte $F3, $31, $E2, $FF, $31, $80, $20, $F3, $38, $E2, $FF, $38, $80, $20, $F3, $31, $E2, $FF, $2C, $80
	.byte $20, $F3, $38, $E2, $FF, $33, $80, $20, $F3, $2C, $E2, $FF, $2C, $80, $20, $F3, $33, $E2, $FF, $33
	.byte $80, $20, $F3, $2C, $E2, $FF, $2C, $80, $20, $F3, $33, $E2, $FF, $33, $80, $20, $F3, $2C, $E2, $FF
	.byte $2C, $80, $20, $F3, $33, $E2, $FF, $33, $80, $20, $F3, $2C, $E2, $FF, $2E, $80, $20, $F3, $33, $E2
	.byte $FF, $35, $80, $20, $F3, $2E, $E2, $FF, $2E, $80, $20, $F3, $35, $E2, $FF, $35, $80, $20, $F3, $2E
	.byte $E2, $FF, $2E, $80, $20, $F3, $35, $E2, $FF, $35, $80, $20, $F3, $2E, $E2, $FF, $2E, $80, $20, $F3
	.byte $35, $E2, $FF, $35, $80, $20, $F3, $2E, $E2, $FF, $2A, $80, $20, $F3, $35, $E2, $FF, $31, $80, $20
	.byte $F3, $2A, $E2, $FF, $2A, $80, $20, $F3, $31, $E2, $FF, $31, $80, $20, $F3, $2A, $E2, $FF, $2A, $80
	.byte $20, $F3, $31, $E2, $FF, $31, $80, $20, $F3, $2A, $E2, $FF, $2A, $80, $20, $F3, $31, $E2, $FF, $31
	.byte $83, $80, $20, $F3, $2A, $00

; Bank 2
ft_s0p1c1:
	.byte $82, $0F, $E5, $19, $14, $16, $83, $12, $0F

; Bank 2
ft_s0p1c2:
	.byte $82, $00, $EE, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $3D, $ED, $3D, $EE
	.byte $3D, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $3D, $3D, $ED, $3D, $EE, $3C, $ED, $3C, $EE, $3C
	.byte $ED, $3C, $EE, $3C, $3C, $ED, $3C, $EE, $3C, $3C, $ED, $3C, $EE, $3C, $ED, $3C, $EE, $3C, $3C, $3D
	.byte $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $3D, $ED, $3D, $EE, $3D, $3D, $ED, $3D
	.byte $EE, $3D, $ED, $3D, $EE, $3D, $3D, $3D, $ED, $3D, $EE, $3F, $ED, $3F, $EE, $3F, $ED, $3F, $EE, $3F
	.byte $3F, $ED, $3F, $EE, $3F, $3F, $ED, $3F, $EE, $3F, $ED, $3F, $EE, $3F, $83, $3F, $00

; Bank 2
ft_s0p2c1:
	.byte $7F, $0E, $87, $01, $00, $30

; Bank 2
ft_s0p2c2:
	.byte $82, $00, $EE, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $3D, $ED, $3D, $EE
	.byte $3D, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $3D, $3D, $ED, $3D, $EE, $3C, $ED, $3C, $EE, $3C
	.byte $ED, $3C, $EE, $3C, $3C, $ED, $3C, $EE, $3C, $3C, $ED, $3C, $EE, $3C, $ED, $3C, $EE, $3C, $3C, $3D
	.byte $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $ED, $3D, $EE, $3D, $3D, $ED, $3D, $EE, $3D, $3D, $ED, $3D
	.byte $EE, $3D, $ED, $3D, $EE, $3D, $3D, $3D, $ED, $3D, $EE, $3F, $ED, $3F, $EE, $3F, $ED, $3F, $EE, $3F
	.byte $3F, $ED, $3F, $EE, $3F, $41, $ED, $41, $EE, $41, $ED, $41, $EE, $41, $83, $41, $00

; Bank 2
ft_s0p2c3:
	.byte $E7, $11, $01, $E9, $1E, $01, $82, $00, $E8, $11, $7F, $E9, $1E, $20, $E7, $11, $E9, $20, $83, $1E
	.byte $01, $82, $00, $E8, $11, $7F, $E9, $1E, $20, $83, $E7, $11, $01, $E9, $1E, $01, $82, $00, $E8, $11
	.byte $7F, $E9, $1E, $20, $E7, $11, $E9, $20, $83, $1E, $01, $82, $00, $E8, $11, $7F, $E9, $1E, $20, $83
	.byte $E7, $11, $01, $E9, $1E, $01, $82, $00, $E8, $11, $7F, $E9, $1E, $20, $E7, $11, $E9, $20, $83, $1E
	.byte $01, $82, $00, $E8, $11, $7F, $E9, $1E, $20, $83, $E7, $11, $01, $E9, $1E, $01, $82, $00, $E8, $11
	.byte $7F, $E9, $1E, $20, $E7, $11, $E9, $20, $83, $1E, $01, $82, $00, $E8, $11, $7F, $E9, $1E, $83, $20
	.byte $00

; Bank 2
ft_s0p2c4:
	.byte $82, $01, $1D, $0F, $1E, $0F, $1D, $0F, $1E, $0F, $1D, $0A, $1E, $0A, $1D, $0A, $1E, $0A, $1D, $0C
	.byte $1E, $0C, $1D, $0C, $1E, $0C, $1D, $08, $1E, $08, $1D, $08, $1E, $83, $08, $01

; Bank 2
ft_s0p3c2:
	.byte $EB, $27, $00, $7F, $02, $2E, $01, $7F, $01, $27, $00, $7F, $02, $2E, $01, $7F, $01, $27, $00, $7F
	.byte $02, $2E, $01, $7F, $01, $27, $00, $7F, $02, $2E, $01, $7F, $01, $27, $00, $7F, $02, $2E, $01, $7F
	.byte $01, $27, $00, $7F, $02, $2E, $01, $7F, $01, $27, $00, $7F, $02, $2E, $01, $7F, $01, $27, $00, $7F
	.byte $02, $2E, $01, $7F, $01

; Bank 2
ft_s0p3c3:
	.byte $00, $07, $82, $00, $E0, $F1, $1C, $F2, $00, $F3, $00, $F5, $00, $F7, $00, $FA, $00, $FC, $00, $83
	.byte $FF, $00, $30

; Bank 2
ft_s0p3c4:
	.byte $82, $01, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0A, $0A, $0A, $0A, $0A, $0A, $0A, $0C, $0C
	.byte $0C, $0C, $0C, $0C, $0C, $0C, $0C, $08, $08, $08, $08, $08, $08, $83, $08, $01

; Bank 2
ft_s0p4c0:
	.byte $82, $02, $E3, $FF, $3D, $3D, $3D, $3D, $3D, $3D, $3C, $3C, $3C, $3C, $83, $3C, $01, $82, $02, $3D
	.byte $3D, $3D, $3D, $3D, $3D, $3F, $3F, $3F, $3F, $83, $3F, $01

; Bank 2
ft_s0p4c1:
	.byte $00, $00, $82, $02, $E4, $91, $81, $31, $31, $31, $31, $31, $31, $30, $30, $30, $30, $83, $30, $01
	.byte $82, $02, $31, $31, $31, $31, $31, $31, $33, $33, $33, $33, $83, $E3, $3F, $00

; Bank 2
ft_s0p4c3:
	.byte $E7, $FF, $11, $01, $E9, $1E, $01, $E8, $11, $01, $82, $00, $E9, $1E, $20, $E7, $11, $E9, $20, $83
	.byte $1E, $01, $E8, $11, $01, $E9, $1E, $00, $20, $00, $E7, $11, $01, $E9, $1E, $01, $E8, $11, $01, $82
	.byte $00, $E9, $1E, $20, $E7, $11, $E9, $20, $83, $1E, $01, $E8, $11, $01, $E9, $1E, $00, $20, $00, $E7
	.byte $11, $01, $E9, $1E, $01, $E8, $11, $01, $82, $00, $E9, $1E, $20, $E7, $11, $E9, $20, $83, $1E, $01
	.byte $E8, $11, $01, $E9, $1E, $00, $20, $00, $E7, $11, $01, $E9, $1E, $01, $E8, $11, $01, $82, $00, $E9
	.byte $1E, $20, $E7, $11, $E9, $20, $83, $1E, $01, $E8, $11, $01, $E9, $1E, $00, $20, $00

; Bank 2
ft_s0p5c0:
	.byte $82, $02, $E3, $3D, $3D, $3D, $3D, $3D, $3D, $3C, $3C, $3C, $3C, $83, $3C, $01, $82, $02, $3D, $3D
	.byte $3D, $3D, $3D, $3D, $3F, $3F, $3F, $41, $83, $41, $01

; Bank 2
ft_s0p5c1:
	.byte $00, $00, $82, $02, $E4, $31, $31, $31, $31, $31, $31, $30, $30, $30, $30, $83, $30, $01, $82, $02
	.byte $31, $31, $31, $31, $31, $31, $33, $33, $33, $35, $83, $88, $00, $35, $00

; Bank 2
ft_s1_frames:
	.word ft_s1f0
	.word ft_s1f1
	.word ft_s1f2
	.word ft_s1f3
	.word ft_s1f4
	.word ft_s1f5
	.word ft_s1f6
	.word ft_s1f7
	.word ft_s1f8
	.word ft_s1f9
	.word ft_s1f10
	.word ft_s1f11
	.word ft_s1f12
ft_s1f0:
	.word ft_s1p0c0, ft_s1p0c1, ft_s1p0c2, ft_s1p0c3, ft_s1p0c4
	.byte $03, $03, $03, $03, $03
ft_s1f1:
	.word ft_s1p0c0, ft_s1p0c1, ft_s0p0c2, ft_s1p1c3, ft_s1p0c4
	.byte $03, $03, $03, $03, $03
ft_s1f2:
	.word ft_s1p1c0, ft_s1p1c1, ft_s1p2c2, ft_s1p2c3, ft_s1p1c4
	.byte $03, $03, $03, $03, $03
ft_s1f3:
	.word ft_s1p1c0, ft_s1p1c1, ft_s1p3c2, ft_s1p3c3, ft_s1p2c4
	.byte $03, $03, $03, $03, $03
ft_s1f4:
	.word ft_s1p1c0, ft_s1p1c1, ft_s1p4c2, ft_s1p2c3, ft_s1p3c4
	.byte $03, $03, $03, $03, $03
ft_s1f5:
	.word ft_s1p1c0, ft_s1p1c1, ft_s1p5c2, ft_s1p4c3, ft_s1p4c4
	.byte $03, $03, $03, $03, $03
ft_s1f6:
	.word ft_s1p2c0, ft_s1p2c1, ft_s1p6c2, ft_s1p5c3, ft_s1p5c4
	.byte $03, $03, $03, $03, $03
ft_s1f7:
	.word ft_s1p2c0, ft_s1p3c1, ft_s1p7c2, ft_s1p6c3, ft_s1p6c4
	.byte $03, $03, $03, $03, $03
ft_s1f8:
	.word ft_s1p2c0, ft_s1p3c1, ft_s1p4c2, ft_s1p2c3, ft_s1p3c4
	.byte $03, $03, $03, $03, $03
ft_s1f9:
	.word ft_s1p2c0, ft_s1p3c1, ft_s1p4c2, ft_s1p3c3, ft_s1p3c4
	.byte $03, $03, $03, $03, $03
ft_s1f10:
	.word ft_s1p3c0, ft_s1p4c1, ft_s1p8c2, ft_s1p7c3, ft_s1p7c4
	.byte $03, $03, $03, $03, $03
ft_s1f11:
	.word ft_s1p4c0, ft_s1p5c1, ft_s1p7c2, ft_s1p3c3, ft_s1p3c4
	.byte $03, $03, $03, $03, $03
ft_s1f12:
	.word ft_s0p0c0, ft_s0p0c0, ft_s1p9c2, ft_s1p8c3, ft_s1p8c4
	.byte $03, $03, $03, $03, $03
; Bank 2
ft_s1p0c0:
	.byte $E2, $92, $FF, $33, $03, $2F, $07, $82, $03, $38, $36, $34, $2F, $83, $31, $01, $33, $01, $33, $03
	.byte $2F, $07, $34, $03, $31, $03, $2F, $01, $31, $01, $36, $03, $34, $01, $33, $01

; Bank 2
ft_s1p0c1:
	.byte $E2, $92, $F7, $3F, $03, $3B, $07, $82, $03, $44, $42, $40, $3B, $83, $3D, $01, $3F, $01, $3F, $03
	.byte $3B, $07, $40, $03, $3D, $03, $3B, $01, $3D, $01, $42, $03, $40, $01, $3F, $01

; Bank 2
ft_s1p0c2:
	.byte $EB, $38, $03, $7F, $3B

; Bank 2
ft_s1p0c3:
	.byte $82, $00, $E0, $FA, $1C, $F9, $00, $F8, $00, $F7, $00, $83, $F6, $1B, $01, $F5, $00, $01, $82, $03
	.byte $F4, $1A, $F3, $19, $F2, $18, $17, $F1, $16, $15, $83, $F0, $14, $1F

; Bank 2
ft_s1p0c4:
	.byte $82, $01, $16, $0A, $16, $0A, $16, $0A, $16, $0A, $12, $06, $12, $06, $12, $06, $12, $06, $14, $08
	.byte $14, $08, $14, $08, $14, $08, $19, $0D, $19, $0D, $19, $0D, $19, $83, $0D, $01

; Bank 2
ft_s1p1c0:
	.byte $82, $01, $80, $20, $91, $7F, $F4, $33, $F1, $34, $F4, $2F, $F1, $33, $2F, $F4, $33, $38, $F1, $33
	.byte $F4, $36, $F1, $38, $F4, $34, $F1, $36, $F4, $2F, $F1, $34, $F4, $31, $83, $33, $00, $7F, $00, $82
	.byte $01, $33, $F1, $31, $F4, $2F, $F1, $33, $31, $F4, $34, $33, $F1, $34, $F4, $31, $F1, $34, $F4, $2F
	.byte $31, $36, $F1, $2F, $F4, $34, $83, $33, $01

; Bank 2
ft_s1p1c1:
	.byte $80, $20, $91, $81, $F4, $33, $01, $8E, $37, $F2, $2C, $01, $8A, $F4, $2F, $01, $8E, $37, $F2, $2C
	.byte $03, $82, $01, $8A, $F4, $33, $38, $8E, $37, $F2, $2C, $8A, $F4, $36, $8E, $38, $F2, $2C, $8A, $F4
	.byte $34, $8E, $38, $F2, $2C, $8A, $F4, $2F, $8E, $38, $F2, $2C, $8A, $F4, $31, $83, $33, $00, $7F, $00
	.byte $33, $01, $8E, $47, $F2, $2A, $01, $8A, $F4, $2F, $01, $8E, $47, $F2, $2A, $03, $82, $01, $8A, $F4
	.byte $34, $33, $8E, $47, $F2, $2A, $8A, $F4, $31, $8E, $59, $F2, $2A, $8A, $F4, $2F, $31, $36, $8E, $59
	.byte $F2, $2A, $8A, $F4, $34, $83, $33, $01

; Bank 2
ft_s1p1c3:
	.byte $00, $1F, $E0, $F1, $20, $07, $F2, $1F, $07, $F2, $1E, $03, $F3, $00, $03, $F4, $1D, $01, $F5, $00
	.byte $01, $82, $00, $F6, $00, $F7, $00, $F8, $00, $83, $F9, $00, $00

; Bank 2
ft_s1p1c4:
	.byte $82, $01, $1D, $16, $1E, $16, $16, $16, $1E, $16, $12, $12, $1E, $12, $12, $12, $1E, $12, $14, $14
	.byte $1E, $14, $14, $14, $1E, $14, $19, $19, $1E, $19, $19, $19, $1E, $83, $19, $01

; Bank 2
ft_s1p2c0:
	.byte $80, $20, $F3, $33, $00, $F4, $00, $00, $7F, $01, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $7F
	.byte $F4, $00, $9B, $03, $33, $9B, $03, $33, $F3, $38, $F4, $00, $83, $36, $01, $82, $00, $F3, $00, $F4
	.byte $7F, $9B, $03, $36, $9B, $03, $36, $F3, $34, $F4, $00, $83, $33, $01, $F3, $2F, $00, $F4, $00, $02
	.byte $82, $00, $F3, $31, $F4, $00, $33, $9B, $03, $00, $F3, $33, $F4, $00, $83, $7F, $01, $F3, $2F, $00
	.byte $F4, $00, $02, $82, $00, $F3, $7F, $F4, $00, $9B, $03, $34, $9B, $03, $34, $F3, $33, $F4, $00, $83
	.byte $31, $01, $82, $00, $F3, $31, $F4, $00, $9B, $03, $31, $9B, $03, $31, $F3, $2F, $F4, $00, $83, $31
	.byte $01, $F3, $36, $00, $F4, $00, $02, $82, $00, $F3, $34, $F4, $00, $33, $83, $9B, $03, $00, $00

; Bank 2
ft_s1p2c1:
	.byte $80, $20, $F4, $33, $00, $F4, $00, $00, $7F, $01, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $7F
	.byte $F4, $00, $9B, $03, $33, $9B, $03, $33, $F3, $38, $F4, $00, $83, $36, $01, $82, $00, $F3, $00, $8E
	.byte $38, $F1, $2C, $8A, $F4, $36, $9B, $03, $36, $F3, $34, $F4, $00, $83, $33, $01, $F3, $2F, $00, $F4
	.byte $00, $02, $82, $00, $F3, $31, $F4, $00, $33, $9B, $03, $00, $F3, $33, $F4, $00, $83, $8E, $47, $F1
	.byte $2A, $01, $8A, $F3, $2F, $00, $F4, $00, $02, $8E, $47, $F1, $2A, $01, $82, $00, $8A, $F4, $34, $9B
	.byte $03, $34, $F3, $33, $F4, $00, $83, $31, $01, $82, $00, $F3, $31, $F4, $00, $9B, $03, $31, $9B, $03
	.byte $31, $F3, $2F, $F4, $00, $83, $31, $01, $F3, $36, $00, $F4, $00, $02, $82, $00, $F3, $34, $F4, $00
	.byte $33, $83, $9B, $03, $00, $00

; Bank 2
ft_s1p2c2:
	.byte $E0, $8C, $60, $38, $00, $8A, $20, $0E, $1C, $0F, $1E, $0F, $23, $0F

; Bank 2
ft_s1p2c3:
	.byte $82, $00, $E0, $FA, $1D, $F9, $00, $F8, $00, $F7, $00, $E8, $FF, $12, $E0, $F3, $1B, $EA, $FF, $1E
	.byte $E0, $F2, $1B, $EA, $FF, $1E, $E0, $F1, $1A, $82, $01, $EA, $FF, $1E, $E8, $12, $EA, $1E, $1E, $1E
	.byte $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12
	.byte $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $83, $EA, $1E, $01

; Bank 2
ft_s1p2c4:
	.byte $82, $01, $16, $16, $1E, $16, $16, $16, $1E, $16, $12, $12, $1E, $12, $12, $12, $1E, $12, $14, $14
	.byte $1E, $14, $14, $14, $1E, $14, $19, $19, $1E, $19, $19, $19, $1E, $83, $19, $01

; Bank 2
ft_s1p3c0:
	.byte $80, $20, $8E, $0C, $F3, $33, $00, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31
	.byte $F4, $00, $33, $7F, $F3, $2F, $F4, $00, $33, $7F, $F3, $31, $83, $F4, $00, $02, $F3, $2F, $00, $F4
	.byte $00, $02, $82, $00, $F3, $31, $F4, $00, $2F, $7F, $F3, $31, $F4, $00, $36, $7F, $F3, $33, $83, $F4
	.byte $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31, $F4, $00, $2F, $7F, $F3, $33, $F4, $00
	.byte $36, $7F, $F3, $31, $83, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $00, $33, $01, $82, $00, $9B, $05
	.byte $F3, $36, $9B, $05, $F4, $36, $9B, $05, $36, $9B, $05, $36, $F3, $34, $F4, $00, $33, $83, $7F, $00

; Bank 2
ft_s1p3c1:
	.byte $80, $20, $F4, $33, $00, $F4, $00, $00, $8E, $37, $F2, $2C, $01, $8A, $F3, $2F, $00, $F4, $00, $02
	.byte $8E, $37, $F2, $2C, $01, $82, $00, $8A, $33, $9B, $03, $33, $F3, $38, $F4, $00, $83, $36, $01, $82
	.byte $00, $F3, $00, $8E, $38, $F2, $2C, $8A, $F4, $36, $9B, $03, $36, $F3, $34, $F4, $00, $83, $33, $01
	.byte $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31, $F4, $00, $33, $9B, $03, $00, $F3, $33, $F4, $00
	.byte $83, $8E, $47, $F2, $2A, $01, $8A, $F3, $2F, $00, $F4, $00, $02, $8E, $47, $F2, $2A, $01, $82, $00
	.byte $8A, $F4, $34, $9B, $03, $34, $F3, $33, $F4, $00, $83, $31, $01, $82, $00, $F3, $31, $F4, $00, $9B
	.byte $03, $31, $9B, $03, $31, $F3, $2F, $F4, $00, $83, $31, $01, $F3, $36, $00, $F4, $00, $02, $82, $00
	.byte $F3, $34, $F4, $00, $33, $83, $9B, $03, $00, $00

; Bank 2
ft_s1p3c2:
	.byte $82, $0F, $E0, $20, $1C, $1E, $83, $23, $0F

; Bank 2
ft_s1p3c3:
	.byte $82, $01, $EA, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA
	.byte $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E
	.byte $1E, $E8, $12, $EA, $1E, $83, $1D, $00, $E0, $F4, $1D, $00, $F5, $00, $01, $82, $00, $F6, $00, $F7
	.byte $00, $FF, $00, $83, $F9, $00, $00

; Bank 2
ft_s1p3c4:
	.byte $82, $01, $1D, $16, $1E, $16, $1D, $16, $1E, $16, $1D, $12, $1E, $12, $1D, $12, $1E, $12, $1D, $14
	.byte $1E, $14, $1D, $14, $1E, $14, $1D, $19, $1E, $19, $1D, $19, $1E, $83, $19, $01

; Bank 2
ft_s1p4c0:
	.byte $80, $20, $8E, $CC, $F3, $33, $00, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31
	.byte $F4, $00, $33, $7F, $F3, $2F, $F4, $00, $33, $7F, $F3, $31, $83, $F4, $00, $02, $F3, $2F, $00, $F4
	.byte $00, $02, $82, $00, $F3, $31, $F4, $00, $2F, $7F, $F3, $31, $F4, $00, $36, $7F, $F3, $33, $83, $F4
	.byte $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31, $F4, $00, $2F, $7F, $F3, $33, $F4, $00
	.byte $36, $7F, $F3, $31, $83, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $00, $33, $01, $82, $00, $9B, $05
	.byte $F3, $36, $9B, $05, $F4, $36, $9B, $05, $36, $9B, $05, $36, $F3, $34, $F4, $00, $33, $83, $7F, $00

; Bank 2
ft_s1p4c1:
	.byte $80, $20, $F3, $33, $00, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31, $F4, $00
	.byte $33, $7F, $F3, $2F, $F4, $00, $33, $7F, $F3, $31, $83, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $02
	.byte $82, $00, $F3, $31, $F4, $00, $2F, $8E, $38, $F2, $2C, $8A, $F3, $31, $F4, $00, $36, $8E, $38, $F2
	.byte $2C, $8A, $F3, $33, $83, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31, $F4, $00
	.byte $2F, $8E, $47, $F2, $2A, $8A, $F3, $33, $F4, $00, $36, $8E, $47, $F2, $2A, $8A, $F3, $31, $83, $F4
	.byte $00, $02, $F3, $2F, $00, $F4, $00, $00, $33, $01, $82, $00, $9B, $05, $F3, $36, $9B, $05, $F4, $36
	.byte $9B, $05, $36, $9B, $05, $36, $F3, $34, $F4, $00, $33, $83, $8E, $59, $F2, $2A, $00

; Bank 2
ft_s1p4c2:
	.byte $EB, $2C, $00, $E0, $20, $02, $EB, $2C, $00, $E0, $20, $02, $EB, $2C, $00, $E0, $20, $02, $EB, $2C
	.byte $00, $E0, $20, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0
	.byte $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02
	.byte $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $23, $02, $EB, $2C
	.byte $00, $E0, $23, $02, $23, $03, $23, $03

; Bank 2
ft_s1p4c3:
	.byte $82, $00, $E0, $FA, $1C, $F9, $00, $F8, $00, $F7, $00, $E8, $FF, $12, $E0, $F3, $1B, $EA, $FF, $1E
	.byte $E0, $F2, $1B, $EA, $FF, $1E, $E0, $F1, $1A, $82, $01, $EA, $FF, $1E, $E8, $12, $EA, $1E, $1E, $1E
	.byte $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $1E, $1E, $E8, $12
	.byte $EA, $1E, $1E, $1E, $E8, $12, $EA, $1E, $83, $1D, $00, $E0, $F4, $1D, $00, $F5, $00, $01, $82, $00
	.byte $E8, $FF, $12, $E0, $F7, $1D, $FF, $00, $83, $F9, $00, $00

; Bank 2
ft_s1p4c4:
	.byte $82, $01, $1D, $16, $1E, $16, $1D, $16, $1E, $16, $1D, $12, $1E, $12, $1D, $12, $1E, $12, $1D, $14
	.byte $1E, $14, $1D, $14, $1E, $14, $19, $0D, $19, $0D, $19, $0D, $82, $00, $1E, $1D, $1D, $83, $1D, $00

; Bank 2
ft_s1p5c1:
	.byte $80, $20, $8A, $F3, $33, $00, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31, $F4
	.byte $00, $33, $8E, $37, $F2, $2C, $8A, $F3, $2F, $F4, $00, $33, $8E, $37, $F2, $2C, $8A, $F3, $31, $83
	.byte $F4, $00, $02, $F3, $2F, $00, $F4, $00, $02, $82, $00, $F3, $31, $F4, $00, $2F, $8E, $38, $F2, $2C
	.byte $8A, $F3, $31, $F4, $00, $36, $8E, $38, $F2, $2C, $8A, $F3, $33, $83, $F4, $00, $02, $F3, $2F, $00
	.byte $F4, $00, $02, $82, $00, $F3, $31, $F4, $00, $2F, $8E, $47, $F2, $2A, $8A, $F3, $33, $F4, $00, $36
	.byte $8E, $47, $F2, $2A, $8A, $F3, $31, $83, $F4, $00, $02, $F3, $2F, $00, $F4, $00, $00, $33, $01, $82
	.byte $00, $9B, $05, $F3, $36, $9B, $05, $F4, $36, $9B, $05, $36, $9B, $05, $36, $F3, $34, $F4, $00, $33
	.byte $83, $8E, $59, $F2, $2A, $00

; Bank 2
ft_s1p5c2:
	.byte $EB, $2C, $00, $E0, $20, $02, $EB, $2C, $00, $E0, $20, $02, $EB, $2C, $00, $E0, $20, $02, $EB, $2C
	.byte $00, $E0, $20, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0
	.byte $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02
	.byte $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02, $82, $00, $EB, $2C, $E0, $23, $EB, $2C
	.byte $E0, $23, $EB, $2C, $E0, $23, $EB, $2C, $E0, $23, $EB, $2C, $E0, $23, $EB, $2C, $E0, $23, $EB, $2C
	.byte $2C, $2C, $83, $2C, $00

; Bank 2
ft_s1p5c3:
	.byte $82, $00, $E0, $F8, $1C, $F7, $00, $F6, $00, $F5, $00, $E8, $FF, $12, $E0, $F4, $1B, $83, $F3, $00
	.byte $01, $E8, $FF, $12, $01, $12, $00, $12, $00, $12, $01, $82, $00, $12, $12, $E0, $FA, $1C, $F9, $00
	.byte $F8, $00, $F7, $00, $E7, $FF, $11, $E0, $F3, $1B, $EA, $FF, $1E, $E0, $F2, $1B, $E7, $FF, $11, $E0
	.byte $F1, $1A, $82, $01, $EA, $FF, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7
	.byte $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7
	.byte $11, $83, $EA, $1E, $01

; Bank 2
ft_s1p5c4:
	.byte $1E, $03, $1E, $03, $1E, $01, $1E, $00, $1E, $00, $1E, $01, $1E, $00, $1E, $00, $82, $01, $1D, $12
	.byte $1D, $12, $1D, $12, $1D, $12, $1D, $14, $1D, $14, $1D, $14, $1D, $14, $1D, $19, $1D, $19, $1D, $19
	.byte $1D, $83, $19, $01

; Bank 2
ft_s1p6c2:
	.byte $EB, $27, $00, $7F, $02, $27, $00, $7F, $02, $82, $00, $27, $7F, $27, $27, $27, $7F, $27, $27, $2C
	.byte $83, $E0, $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0
	.byte $1C, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02
	.byte $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $23, $02, $EB, $2C, $00, $E0, $23, $02, $EB, $2C
	.byte $00, $E0, $23, $02, $EB, $2C, $00, $E0, $23, $02

; Bank 2
ft_s1p6c3:
	.byte $82, $01, $E7, $FF, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7
	.byte $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7
	.byte $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $83, $EA, $1E
	.byte $03, $1E, $03, $1E, $01

; Bank 2
ft_s1p6c4:
	.byte $82, $01, $1D, $16, $1D, $16, $1D, $16, $1D, $16, $1D, $12, $1D, $12, $1D, $12, $1D, $12, $1D, $14
	.byte $1D, $14, $1D, $14, $1D, $14, $1D, $19, $1D, $83, $19, $03, $19, $03, $19, $01

; Bank 2
ft_s1p7c2:
	.byte $EB, $2C, $00, $E0, $20, $02, $EB, $2C, $00, $E0, $20, $02, $EB, $2C, $00, $E0, $20, $02, $EB, $2C
	.byte $00, $E0, $20, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0
	.byte $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02
	.byte $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $23, $02, $EB, $2C
	.byte $00, $E0, $23, $02, $82, $01, $7F, $23, $7F, $83, $23, $01

; Bank 2
ft_s1p7c3:
	.byte $82, $00, $E0, $F8, $1C, $F7, $00, $F6, $00, $F5, $00, $83, $F4, $1B, $01, $F3, $00, $01, $F2, $1A
	.byte $03, $F1, $19, $03, $82, $00, $FA, $1C, $F9, $00, $F8, $00, $F7, $00, $E7, $FF, $11, $E0, $F3, $1B
	.byte $EA, $FF, $1E, $E0, $F2, $1B, $E7, $FF, $11, $E0, $F1, $1A, $82, $01, $EA, $FF, $1E, $E7, $11, $EA
	.byte $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA
	.byte $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $83, $EA, $1E, $01

; Bank 2
ft_s1p7c4:
	.byte $1D, $0F, $82, $01, $1D, $12, $1D, $12, $1D, $12, $1D, $12, $1D, $14, $1D, $14, $1D, $14, $1D, $14
	.byte $1D, $19, $1D, $19, $1D, $19, $1D, $83, $19, $01

; Bank 2
ft_s1p8c2:
	.byte $EB, $27, $00, $7F, $0E, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0
	.byte $1C, $02, $EB, $2C, $00, $E0, $1C, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02
	.byte $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $1E, $02, $EB, $2C, $00, $E0, $23, $02, $EB, $2C
	.byte $00, $E0, $23, $02, $EB, $2C, $00, $E0, $23, $02, $EB, $2C, $00, $E0, $23, $02

; Bank 2
ft_s1p8c3:
	.byte $82, $00, $E0, $F8, $1C, $F7, $00, $F6, $00, $F5, $00, $83, $F4, $1B, $01, $F3, $00, $01, $F2, $1A
	.byte $03, $F1, $19, $02, $88, $00, $00, $30

; Bank 2
ft_s1p8c4:
	.byte $1D, $3F

; Bank 2
ft_s1p9c2:
	.byte $EB, $27, $00, $7F, $3E

; Bank 2
ft_s2_frames:
	.word ft_s2f0
	.word ft_s2f1
	.word ft_s2f2
	.word ft_s2f3
	.word ft_s2f4
	.word ft_s2f5
	.word ft_s2f6
	.word ft_s2f7
	.word ft_s2f8
	.word ft_s2f9
	.word ft_s2f10
	.word ft_s2f11
	.word ft_s2f12
	.word ft_s2f13
	.word ft_s2f14
	.word ft_s2f15
	.word ft_s2f16
ft_s2f0:
	.word ft_s2p0c0, ft_s2p10c1, ft_s0p0c2, ft_s2p4c3, ft_s2p0c4
	.byte $03, $03, $03, $03, $03
ft_s2f1:
	.word ft_s2p1c0, ft_s2p11c1, ft_s0p0c2, ft_s2p5c3, ft_s2p1c4
	.byte $03, $03, $03, $03, $03
ft_s2f2:
	.word ft_s2p2c0, ft_s2p12c1, ft_s2p10c2, ft_s2p6c3, ft_s2p8c4
	.byte $03, $03, $03, $03, $03
ft_s2f3:
	.word ft_s2p3c0, ft_s2p13c1, ft_s2p11c2, ft_s2p7c3, ft_s2p2c4
	.byte $03, $03, $03, $03, $03
ft_s2f4:
	.word ft_s2p4c0, ft_s2p1c1, ft_s2p1c2, ft_s2p1c3, ft_s2p3c4
	.byte $03, $03, $03, $03, $03
ft_s2f5:
	.word ft_s2p5c0, ft_s2p2c1, ft_s2p2c2, ft_s2p2c3, ft_s2p4c4
	.byte $03, $03, $03, $03, $03
ft_s2f6:
	.word ft_s2p6c0, ft_s2p3c1, ft_s2p10c2, ft_s2p6c3, ft_s2p5c4
	.byte $03, $03, $03, $03, $03
ft_s2f7:
	.word ft_s2p7c0, ft_s2p4c1, ft_s2p10c2, ft_s2p6c3, ft_s2p6c4
	.byte $03, $03, $03, $03, $03
ft_s2f8:
	.word ft_s2p8c0, ft_s2p5c1, ft_s2p1c2, ft_s2p1c3, ft_s2p7c4
	.byte $03, $03, $03, $03, $03
ft_s2f9:
	.word ft_s2p9c0, ft_s2p6c1, ft_s2p6c2, ft_s2p1c3, ft_s2p11c4
	.byte $03, $03, $03, $03, $03
ft_s2f10:
	.word ft_s2p10c0, ft_s2p7c1, ft_s2p7c2, ft_s2p1c3, ft_s2p12c4
	.byte $03, $03, $03, $03, $03
ft_s2f11:
	.word ft_s2p9c0, ft_s2p8c1, ft_s2p7c2, ft_s2p1c3, ft_s2p13c4
	.byte $03, $03, $03, $03, $03
ft_s2f12:
	.word ft_s2p14c0, ft_s2p14c1, ft_s2p10c2, ft_s2p6c3, ft_s2p8c4
	.byte $03, $03, $03, $03, $03
ft_s2f13:
	.word ft_s2p14c0, ft_s2p14c1, ft_s2p11c2, ft_s2p7c3, ft_s2p2c4
	.byte $03, $03, $03, $03, $03
ft_s2f14:
	.word ft_s2p11c0, ft_s2p1c1, ft_s2p1c2, ft_s2p1c3, ft_s2p3c4
	.byte $03, $03, $03, $03, $03
ft_s2f15:
	.word ft_s2p12c0, ft_s2p2c1, ft_s2p2c2, ft_s2p2c3, ft_s2p4c4
	.byte $03, $03, $03, $03, $03
ft_s2f16:
	.word ft_s2p13c0, ft_s2p3c1, ft_s2p12c2, ft_s2p10c3, ft_s2p9c4
	.byte $03, $03, $03, $03, $03
; Bank 3
ft_s2p0c0:
	.byte $80, $20, $8E, $37, $F1, $1B, $03, $F2, $00, $01, $F3, $00, $01, $82, $00, $F4, $00, $F5, $00, $F6
	.byte $00, $F7, $00, $F8, $00, $FA, $00, $FC, $00, $83, $FF, $00, $30

; Bank 3
ft_s2p0c4:
	.byte $00, $0E, $87, $01, $00, $30

; Bank 3
ft_s2p1c0:
	.byte $E2, $8A, $FF, $3F, $05, $46, $01, $49, $03, $4B, $09, $42, $01, $44, $03, $46, $03, $3F, $05, $46
	.byte $01, $49, $03, $4B, $01, $44, $07, $4B, $01, $4E, $03, $50, $03

; Bank 3
ft_s2p1c1:
	.byte $E5, $FF, $0F, $03, $7F, $01, $16, $01, $19, $03, $1B, $01, $0A, $02, $7F, $00, $0A, $01, $7F, $01
	.byte $11, $01, $14, $03, $16, $03, $0F, $02, $7F, $00, $0F, $01, $16, $01, $19, $03, $1B, $01, $14, $02
	.byte $7F, $00, $14, $01, $7F, $01, $1B, $01, $1E, $03, $20, $03

; Bank 3
ft_s2p1c2:
	.byte $EB, $29, $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01
	.byte $29, $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01, $29
	.byte $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01, $29, $00
	.byte $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01

; Bank 3
ft_s2p1c3:
	.byte $82, $01, $E7, $11, $E9, $1E, $E8, $11, $E9, $1E, $E7, $11, $11, $E8, $11, $E9, $1E, $E7, $11, $E9
	.byte $1E, $E8, $11, $E9, $1E, $E7, $11, $11, $E8, $11, $E9, $1E, $E7, $11, $E9, $1E, $E8, $11, $E9, $1E
	.byte $E7, $11, $11, $E8, $11, $E9, $1E, $E7, $11, $E9, $1E, $E8, $11, $E9, $1E, $E7, $11, $11, $E8, $11
	.byte $83, $E9, $1E, $01

; Bank 3
ft_s2p1c4:
	.byte $82, $0F, $1D, $1D, $1D, $83, $1D, $0F

; Bank 3
ft_s2p2c0:
	.byte $E2, $3F, $05, $46, $01, $49, $03, $4B, $09, $42, $01, $44, $03, $46, $03, $3F, $03, $3F, $01, $46
	.byte $01, $49, $03, $4B, $01, $44, $03, $44, $03, $4B, $01, $4E, $03, $50, $03

; Bank 3
ft_s2p2c1:
	.byte $E5, $0F, $02, $7F, $00, $0F, $01, $16, $01, $19, $03, $1B, $01, $0A, $02, $7F, $00, $0A, $01, $7F
	.byte $01, $11, $01, $14, $03, $16, $03, $82, $01, $0F, $0F, $7F, $12, $12, $7F, $14, $14, $7F, $16, $16
	.byte $7F, $83, $19, $03, $1A, $03

; Bank 3
ft_s2p2c2:
	.byte $EB, $29, $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01
	.byte $29, $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01, $31
	.byte $01, $29, $00, $7F, $02, $31, $01, $29, $00, $7F, $02, $31, $01, $29, $00, $7F, $02, $31, $01, $29
	.byte $00, $7F, $02, $31, $01, $29, $00, $7F, $00, $31, $01, $29, $00, $7F, $00

; Bank 3
ft_s2p2c3:
	.byte $82, $01, $E7, $11, $E9, $1E, $E8, $11, $E9, $1E, $E7, $11, $11, $E8, $11, $E9, $1E, $E7, $11, $E9
	.byte $1E, $E8, $11, $E9, $1E, $E7, $11, $11, $E8, $11, $E9, $1E, $E8, $11, $E7, $11, $EA, $1F, $E8, $11
	.byte $E7, $11, $EA, $1F, $E8, $11, $E7, $11, $EA, $1F, $E8, $11, $E7, $11, $EA, $1F, $E8, $11, $E7, $11
	.byte $E8, $11, $83, $E7, $11, $01

; Bank 3
ft_s2p2c4:
	.byte $82, $01, $05, $05, $05, $05, $05, $05, $05, $05, $01, $01, $01, $01, $01, $01, $01, $01, $05, $05
	.byte $05, $05, $05, $05, $05, $0A, $83, $7F, $0F

; Bank 3
ft_s2p3c0:
	.byte $E2, $8A, $FF, $3F, $05, $46, $01, $49, $03, $4B, $01, $3A, $03, $3A, $03, $41, $01, $44, $03, $46
	.byte $03, $3F, $03, $3F, $01, $46, $01, $49, $03, $4B, $01, $44, $03, $44, $03, $4B, $01, $4E, $03, $50
	.byte $03

; Bank 3
ft_s2p3c1:
	.byte $E5, $1B, $05, $16, $00, $0F, $00, $7F, $04, $E2, $F5, $4B, $01, $82, $03, $46, $44, $46, $41, $3F
	.byte $83, $3A, $05, $3D, $03, $3F, $03, $46, $01, $38, $01, $3F, $03, $38, $01, $3F, $03, $38, $00

; Bank 3
ft_s2p3c4:
	.byte $82, $01, $FF, $05, $05, $05, $0C, $0F, $0F, $11, $01, $01, $01, $01, $07, $0A, $0A, $0C, $0C, $05
	.byte $05, $05, $0C, $0F, $0F, $11, $0A, $0A, $0A, $0A, $11, $14, $14, $16, $83, $16, $01

; Bank 3
ft_s2p4c0:
	.byte $E1, $27, $01, $7F, $03, $2E, $01, $31, $03, $33, $01, $22, $02, $7F, $00, $22, $01, $7F, $01, $29
	.byte $01, $2C, $03, $2E, $03, $27, $02, $7F, $00, $27, $01, $2E, $01, $31, $03, $33, $01, $2C, $02, $7F
	.byte $00, $2C, $01, $7F, $01, $33, $01, $36, $03, $38, $02, $8C, $1F, $00, $00

; Bank 3
ft_s2p4c1:
	.byte $00, $02, $E2, $F5, $3F, $05, $46, $03, $49, $01, $82, $03, $46, $44, $46, $49, $4B, $83, $52, $05
	.byte $49, $03, $4B, $03, $52, $03, $52, $01, $82, $00, $52, $50, $4E, $4B, $49, $46, $44, $42, $83, $3F
	.byte $00

; Bank 3
ft_s2p4c3:
	.byte $E0, $F1, $17, $03, $F2, $00, $01, $F3, $00, $01, $82, $00, $F4, $00, $F5, $00, $F6, $00, $F7, $00
	.byte $F8, $00, $FA, $00, $FC, $00, $83, $FE, $00, $30

; Bank 3
ft_s2p4c4:
	.byte $82, $01, $05, $05, $05, $0C, $0F, $0F, $11, $01, $01, $01, $01, $07, $0A, $0A, $0C, $0C, $05, $83
	.byte $05, $03, $08, $01, $08, $03, $0A, $01, $0A, $03, $0C, $01, $0C, $03, $0F, $03, $10, $03

; Bank 3
ft_s2p5c0:
	.byte $E1, $8A, $27, $02, $7F, $00, $27, $01, $2E, $01, $31, $03, $33, $01, $22, $02, $7F, $00, $22, $01
	.byte $7F, $01, $29, $01, $2C, $03, $2E, $02, $8C, $1F, $2E, $00, $82, $01, $8A, $27, $27, $7F, $2A, $2A
	.byte $7F, $2C, $2C, $7F, $2E, $2E, $7F, $83, $80, $20, $F7, $31, $03, $32, $03

; Bank 3
ft_s2p5c1:
	.byte $FF, $7F, $21, $82, $01, $E2, $FF, $44, $44, $3F, $3F, $38, $38, $36, $36, $38, $38, $F7, $38, $F3
	.byte $38, $F1, $38, $83, $FF, $7F, $03

; Bank 3
ft_s2p5c3:
	.byte $82, $01, $E7, $FF, $11, $EA, $20, $1E, $20, $1E, $20, $1E, $20, $E7, $11, $EA, $20, $1E, $20, $1E
	.byte $20, $1E, $20, $E7, $11, $EA, $20, $1E, $20, $1E, $20, $1E, $20, $E7, $11, $EA, $20, $1E, $20, $1E
	.byte $20, $1E, $83, $20, $01

; Bank 3
ft_s2p5c4:
	.byte $05, $05, $0C, $01, $7F, $05, $01, $07, $07, $01, $7F, $07, $05, $05, $0C, $01, $7F, $05, $0A, $07
	.byte $11, $01, $7F, $07

; Bank 3
ft_s2p6c0:
	.byte $80, $20, $33, $03, $F5, $00, $01, $8C, $0A, $F2, $00, $01, $F1, $00, $00, $8A, $7F, $00, $E2, $FF
	.byte $4B, $01, $82, $03, $46, $44, $46, $41, $3F, $83, $3A, $05, $3D, $03, $3F, $03, $46, $01, $38, $01
	.byte $3F, $03, $38, $01, $3F, $03, $42, $03

; Bank 3
ft_s2p6c1:
	.byte $00, $21, $82, $01, $E2, $44, $44, $3F, $3F, $38, $38, $42, $42, $44, $44, $F7, $44, $F3, $44, $F1
	.byte $44, $83, $FF, $7F, $03

; Bank 3
ft_s2p6c2:
	.byte $EB, $29, $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01
	.byte $29, $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $83, $31, $01, $7F, $01, $29
	.byte $00, $7F, $02, $31, $01, $7F, $01, $82, $00, $29, $7F, $29, $7F, $82, $01, $31, $7F, $80, $20, $9B
	.byte $03, $3F, $9B, $02, $4B, $9B, $03, $3F, $9B, $02, $4B, $9B, $03, $3F, $9B, $02, $4B, $9B, $03, $3F
	.byte $83, $9B, $02, $4B, $01

; Bank 3
ft_s2p6c3:
	.byte $82, $01, $E8, $20, $EA, $1E, $1C, $1E, $1C, $1E, $1C, $1E, $E7, $11, $EA, $1E, $1C, $1E, $1C, $1E
	.byte $1C, $E7, $11, $11, $EA, $1E, $1C, $1E, $1C, $1E, $1C, $1E, $E7, $11, $EA, $1E, $1C, $1E, $1C, $1E
	.byte $1C, $83, $E7, $11, $01

; Bank 3
ft_s2p6c4:
	.byte $05, $05, $0C, $01, $7F, $05, $01, $07, $07, $01, $7F, $07, $05, $05, $0C, $01, $7F, $05, $05, $07
	.byte $82, $01, $11, $7F, $0F, $11, $83, $0F, $01

; Bank 3
ft_s2p7c0:
	.byte $E2, $3F, $05, $46, $03, $49, $01, $82, $03, $46, $44, $46, $49, $4B, $83, $52, $05, $49, $03, $4B
	.byte $03, $52, $03, $52, $01, $52, $01, $82, $00, $4E, $4B, $49, $46, $44, $42, $3F, $3D, $3A, $83, $36
	.byte $00

; Bank 3
ft_s2p7c1:
	.byte $00, $21, $82, $01, $E2, $44, $44, $3F, $3F, $38, $3D, $3E, $3F, $38, $38, $F7, $38, $F3, $38, $F1
	.byte $38, $83, $FF, $7F, $03

; Bank 3
ft_s2p7c2:
	.byte $82, $01, $80, $20, $9B, $03, $3F, $9B, $02, $4B, $9B, $03, $3F, $9B, $02, $4B, $9B, $03, $3F, $9B
	.byte $02, $4B, $9B, $03, $3F, $9B, $02, $4B, $9B, $03, $3F, $9B, $02, $49, $9B, $03, $3D, $9B, $02, $49
	.byte $9B, $03, $3A, $9B, $02, $49, $9B, $03, $33, $9B, $02, $49, $9B, $03, $3C, $9B, $02, $48, $9B, $03
	.byte $3C, $9B, $02, $48, $9B, $03, $3C, $9B, $02, $48, $9B, $03, $3D, $9B, $03, $3E, $9B, $03, $3F, $9B
	.byte $02, $48, $9B, $03, $3F, $9B, $02, $48, $9B, $03, $3F, $9B, $02, $48, $9B, $03, $3F, $83, $9B, $02
	.byte $48, $01

; Bank 3
ft_s2p7c3:
	.byte $82, $01, $E7, $11, $EA, $1E, $1C, $1E, $1C, $1E, $1C, $1E, $E7, $11, $EA, $1E, $1C, $1E, $1C, $1E
	.byte $1C, $E7, $11, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $E7, $11, $EA, $1E, $83, $E7
	.byte $11, $0B, $11, $03

; Bank 3
ft_s2p7c4:
	.byte $05, $03, $0C, $01, $7F, $03, $05, $01, $0F, $01, $7F, $01, $05, $03, $0F, $01, $7F, $03, $05, $01
	.byte $0E, $01, $7F, $01, $0A, $03, $0E, $01, $7F, $03, $0A, $01, $11, $01, $7F, $01, $05, $03, $0A, $01
	.byte $7F, $03, $05, $01, $0E, $01, $7F, $01

; Bank 3
ft_s2p8c0:
	.byte $E2, $33, $02, $93, $03, $00, $00, $82, $01, $80, $20, $8E, $7C, $F7, $33, $F3, $00, $8E, $7C, $F7
	.byte $33, $8E, $7A, $F7, $33, $F3, $00, $8E, $7A, $F7, $33, $F3, $00, $8E, $5A, $F7, $33, $F3, $00, $8E
	.byte $5A, $F7, $33, $F3, $00, $8E, $59, $F7, $33, $F3, $00, $83, $8E, $59, $F7, $33, $13, $F5, $00, $01
	.byte $F3, $00, $03, $F1, $00, $03, $F7, $7F, $03

; Bank 3
ft_s2p8c1:
	.byte $00, $21, $82, $01, $E2, $44, $44, $3F, $3F, $38, $38, $42, $42, $44, $44, $38, $44, $38, $38, $83
	.byte $2C, $01

; Bank 3
ft_s2p8c4:
	.byte $82, $01, $05, $05, $05, $05, $05, $05, $05, $05, $01, $01, $01, $01, $01, $01, $01, $01, $05, $05
	.byte $05, $05, $05, $05, $05, $0A, $0A, $0A, $0A, $0A, $0A, $0A, $0A, $83, $0A, $01

; Bank 3
ft_s2p9c0:
	.byte $00, $03, $82, $01, $80, $20, $8E, $7C, $F7, $33, $F3, $00, $8E, $7C, $F7, $33, $8E, $7A, $F7, $33
	.byte $F3, $00, $8E, $7A, $F7, $33, $F3, $00, $8E, $5A, $F7, $33, $F3, $00, $8E, $5A, $F7, $33, $F3, $00
	.byte $8E, $5F, $F7, $33, $F3, $00, $83, $8E, $4C, $F7, $38, $13, $F5, $00, $01, $F3, $00, $03, $F1, $00
	.byte $03, $F7, $7F, $03

; Bank 3
ft_s2p9c4:
	.byte $11, $06, $88, $00, $00, $38

; Bank 3
ft_s2p10c0:
	.byte $00, $03, $82, $01, $80, $20, $8E, $7C, $F7, $33, $F3, $00, $8E, $7C, $F7, $33, $F3, $00, $83, $7F
	.byte $17, $82, $01, $8E, $5C, $F7, $33, $F3, $00, $8E, $5C, $F7, $33, $F3, $00, $83, $7F, $13

; Bank 3
ft_s2p10c1:
	.byte $80, $20, $F1, $27, $03, $F2, $00, $01, $F3, $00, $01, $82, $00, $F4, $00, $F5, $00, $F6, $00, $F7
	.byte $00, $F8, $00, $FA, $00, $FC, $00, $83, $FF, $00, $30

; Bank 3
ft_s2p10c2:
	.byte $EB, $29, $00, $9B, $04, $7F, $0E, $29, $00, $7F, $0C, $29, $00, $7F, $00, $29, $00, $7F, $0E, $29
	.byte $00, $7F, $0C, $29, $00, $7F, $00

; Bank 3
ft_s2p10c3:
	.byte $E8, $11, $3F

; Bank 3
ft_s2p11c0:
	.byte $EC, $33, $01, $7F, $03, $3A, $00, $7F, $00, $3D, $02, $7F, $00, $3F, $00, $7F, $00, $2E, $02, $7F
	.byte $00, $2E, $01, $7F, $01, $35, $00, $7F, $00, $38, $02, $7F, $00, $3A, $02, $7F, $00, $33, $02, $82
	.byte $00, $7F, $33, $7F, $3A, $7F, $83, $3D, $02, $7F, $00, $3F, $00, $7F, $00, $38, $02, $7F, $00, $38
	.byte $01, $7F, $01, $3F, $00, $7F, $00, $42, $02, $7F, $00, $44, $02, $7F, $00

; Bank 3
ft_s2p11c1:
	.byte $80, $20, $8E, $37, $F4, $1B, $02, $E2, $8A, $F5, $3F, $05, $46, $01, $49, $03, $4B, $09, $42, $01
	.byte $44, $03, $46, $03, $3F, $05, $46, $01, $49, $03, $4B, $01, $44, $07, $4B, $01, $4E, $03, $50, $00

; Bank 3
ft_s2p11c2:
	.byte $EB, $29, $00, $7F, $0E, $29, $00, $7F, $0C, $29, $00, $7F, $00, $29, $00, $7F, $02, $29, $00, $7F
	.byte $02, $29, $00, $7F, $02, $29, $00, $7F, $02, $29, $00, $7F, $0A, $29, $00, $7F, $02

; Bank 3
ft_s2p11c4:
	.byte $05, $03, $0C, $01, $7F, $03, $05, $01, $0F, $01, $7F, $01, $05, $03, $0F, $01, $7F, $03, $05, $01
	.byte $0E, $01, $7F, $01, $0A, $03, $0E, $01, $7F, $03, $0A, $01, $11, $01, $7F, $01, $11, $03, $0A, $01
	.byte $7F, $03, $08, $01, $0A, $01, $7F, $01

; Bank 3
ft_s2p12c0:
	.byte $EC, $33, $01, $7F, $01, $82, $00, $33, $7F, $3A, $7F, $83, $3D, $02, $7F, $00, $3F, $00, $7F, $00
	.byte $2E, $02, $7F, $00, $2E, $01, $7F, $01, $35, $00, $7F, $00, $38, $02, $7F, $00, $3A, $02, $35, $00
	.byte $33, $00, $7F, $00, $33, $01, $7F, $01, $36, $00, $7F, $00, $36, $01, $7F, $01, $38, $00, $7F, $00
	.byte $38, $01, $7F, $01, $3A, $00, $7F, $00, $3A, $01, $7F, $01, $3D, $03, $3E, $03

; Bank 3
ft_s2p12c1:
	.byte $00, $02, $E2, $F5, $3F, $05, $46, $01, $49, $03, $4B, $09, $42, $01, $44, $03, $46, $03, $3F, $03
	.byte $3F, $01, $46, $01, $49, $03, $4B, $01, $44, $03, $44, $03, $4B, $01, $4E, $03, $50, $00

; Bank 3
ft_s2p12c2:
	.byte $EB, $31, $01, $7F, $3D

; Bank 3
ft_s2p12c4:
	.byte $05, $03, $0C, $01, $7F, $03, $05, $01, $0F, $01, $7F, $01, $05, $03, $0F, $01, $7F, $03, $05, $01
	.byte $0E, $01, $7F, $01, $0A, $03, $0E, $01, $7F, $03, $0A, $01, $0E, $01, $10, $01, $11, $03, $0A, $01
	.byte $7F, $09

; Bank 3
ft_s2p13c0:
	.byte $EC, $3F, $05, $3A, $00, $33, $38

; Bank 3
ft_s2p13c1:
	.byte $00, $02, $E2, $F5, $3F, $05, $46, $01, $49, $03, $4B, $01, $3A, $03, $3A, $03, $41, $01, $44, $03
	.byte $46, $03, $3F, $03, $3F, $01, $46, $01, $49, $03, $4B, $01, $44, $03, $44, $03, $4B, $01, $4E, $03
	.byte $50, $00

; Bank 3
ft_s2p13c4:
	.byte $05, $03, $0C, $01, $7F, $03, $03, $01, $0F, $01, $7F, $01, $05, $03, $0F, $01, $7F, $03, $05, $01
	.byte $0E, $01, $7F, $01, $0A, $03, $0E, $01, $7F, $03, $0A, $01, $11, $01, $7F, $01, $11, $03, $0A, $01
	.byte $7F, $03, $08, $01, $0A, $01, $7F, $01

; Bank 3
ft_s2p14c0:
	.byte $E2, $8A, $FF, $27, $05, $2E, $01, $31, $03, $33, $01, $22, $03, $22, $03, $29, $01, $2C, $03, $2E
	.byte $03, $27, $03, $27, $01, $2E, $01, $31, $03, $33, $01, $2C, $03, $2C, $03, $33, $01, $36, $03, $38
	.byte $03

; Bank 3
ft_s2p14c1:
	.byte $00, $02, $E2, $F3, $27, $05, $2E, $01, $31, $03, $33, $01, $22, $03, $22, $03, $29, $01, $2C, $03
	.byte $2E, $03, $27, $03, $27, $01, $2E, $01, $31, $03, $33, $01, $2C, $03, $2C, $03, $33, $01, $36, $03
	.byte $38, $00

; Bank 3
ft_s3_frames:
	.word ft_s3f0
	.word ft_s3f1
	.word ft_s3f2
	.word ft_s3f3
	.word ft_s3f4
	.word ft_s3f5
	.word ft_s3f6
	.word ft_s3f7
	.word ft_s3f8
	.word ft_s3f9
	.word ft_s3f10
	.word ft_s3f11
	.word ft_s3f12
	.word ft_s3f13
ft_s3f0:
	.word ft_s3p0c0, ft_s3p0c1, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s3f1:
	.word ft_s3p0c0, ft_s3p0c1, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s3f2:
	.word ft_s3p0c0, ft_s3p0c1, ft_s0p0c2, ft_s3p2c3, ft_s3p2c4
	.byte $03, $03, $03, $03, $03
ft_s3f3:
	.word ft_s3p0c0, ft_s3p0c1, ft_s0p0c2, ft_s3p3c3, ft_s3p3c4
	.byte $03, $03, $03, $03, $03
ft_s3f4:
	.word ft_s3p1c0, ft_s3p1c1, ft_s0p0c2, ft_s3p4c3, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
ft_s3f5:
	.word ft_s3p2c0, ft_s3p2c1, ft_s0p0c2, ft_s3p5c3, ft_s3p5c4
	.byte $03, $03, $03, $03, $03
ft_s3f6:
	.word ft_s3p2c0, ft_s3p2c1, ft_s0p0c2, ft_s3p5c3, ft_s3p5c4
	.byte $03, $03, $03, $03, $03
ft_s3f7:
	.word ft_s3p5c0, ft_s3p2c1, ft_s0p0c2, ft_s3p5c3, ft_s3p5c4
	.byte $03, $03, $03, $03, $03
ft_s3f8:
	.word ft_s3p5c0, ft_s3p2c1, ft_s0p0c2, ft_s3p5c3, ft_s3p5c4
	.byte $03, $03, $03, $03, $03
ft_s3f9:
	.word ft_s3p3c0, ft_s3p2c1, ft_s0p0c2, ft_s3p5c3, ft_s3p5c4
	.byte $03, $03, $03, $03, $03
ft_s3f10:
	.word ft_s3p3c0, ft_s3p2c1, ft_s0p0c2, ft_s3p5c3, ft_s3p5c4
	.byte $03, $03, $03, $03, $03
ft_s3f11:
	.word ft_s3p4c0, ft_s3p3c1, ft_s0p0c2, ft_s3p6c3, ft_s3p6c4
	.byte $03, $03, $03, $03, $03
ft_s3f12:
	.word ft_s3p4c0, ft_s3p3c1, ft_s0p0c2, ft_s3p6c3, ft_s3p6c4
	.byte $03, $03, $03, $03, $03
ft_s3f13:
	.word ft_s0p0c2, ft_s3p4c1, ft_s3p4c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
; Bank 3
ft_s3p0c0:
	.byte $82, $00, $E2, $FF, $1E, $1E, $2A, $2A, $28, $28, $25, $83, $25, $02, $82, $00, $21, $21, $20, $20
	.byte $1C, $1C, $1E, $83, $1E, $01, $28, $00, $28, $01, $25, $00, $25, $02, $82, $00, $19, $19, $1C, $1C
	.byte $20, $20, $1E, $1E, $28, $28, $2A, $2A, $25, $83, $25, $02, $82, $00, $20, $20, $21, $21, $23, $23
	.byte $28, $83, $28, $01, $2A, $00, $2A, $01, $25, $00, $25, $02, $82, $00, $2A, $2A, $21, $21, $20, $83
	.byte $20, $00

; Bank 3
ft_s3p0c1:
	.byte $82, $01, $E5, $FF, $12, $12, $12, $12, $12, $12, $12, $12, $10, $10, $10, $10, $10, $10, $10, $10
	.byte $0D, $0D, $0D, $0D, $0D, $0D, $0D, $0D, $10, $10, $10, $10, $10, $10, $10, $83, $10, $01

; Bank 3
ft_s3p1c0:
	.byte $E2, $1E, $00, $1E, $3E

; Bank 3
ft_s3p1c1:
	.byte $E5, $12, $07, $7F, $06, $87, $01, $00, $30

; Bank 3
ft_s3p2c0:
	.byte $00, $02, $80, $20, $F3, $12, $00, $12, $00, $F1, $00, $01, $F3, $12, $00, $12, $00, $F1, $00, $01
	.byte $82, $00, $F3, $12, $12, $F3, $1E, $1E, $83, $F1, $00, $01, $82, $00, $F3, $1E, $1E, $F3, $10, $10
	.byte $83, $F1, $00, $01, $F3, $10, $00, $10, $00, $F1, $00, $01, $82, $00, $F3, $10, $10, $F3, $1C, $1C
	.byte $83, $F1, $00, $01, $82, $00, $F3, $1C, $1C, $F3, $0D, $0D, $83, $F1, $00, $01, $F3, $0D, $00, $0D
	.byte $00, $F1, $00, $01, $82, $00, $F3, $0D, $0D, $F3, $19, $19, $83, $F1, $00, $01, $82, $00, $F3, $19
	.byte $19, $F3, $10, $10, $83, $F1, $00, $01, $F3, $10, $00, $10, $00, $F1, $00, $01, $F3, $15, $00, $15
	.byte $00, $F1, $00, $01, $F3, $14, $00

; Bank 3
ft_s3p2c1:
	.byte $80, $20, $F8, $12, $00, $12, $00, $F3, $00, $01, $F8, $12, $00, $12, $00, $F3, $00, $01, $82, $00
	.byte $F8, $12, $12, $F8, $1E, $1E, $83, $F3, $00, $01, $82, $00, $F8, $1E, $1E, $F8, $10, $10, $83, $F3
	.byte $00, $01, $F8, $10, $00, $10, $00, $F3, $00, $01, $82, $00, $F8, $10, $10, $F8, $1C, $1C, $83, $F3
	.byte $00, $01, $82, $00, $F8, $1C, $1C, $F8, $0D, $0D, $83, $F3, $00, $01, $F8, $0D, $00, $0D, $00, $F3
	.byte $00, $01, $82, $00, $F8, $0D, $0D, $F8, $19, $19, $83, $F3, $00, $01, $82, $00, $F8, $19, $19, $F8
	.byte $10, $10, $83, $F3, $00, $01, $F8, $10, $00, $10, $00, $F3, $00, $01, $F8, $15, $00, $15, $00, $F3
	.byte $00, $01, $82, $00, $F8, $14, $14, $F8, $10, $83, $10, $00

; Bank 3
ft_s3p2c3:
	.byte $E7, $11, $01, $EA, $1C, $00, $E9, $1E, $00, $E7, $11, $01, $E9, $1C, $01, $E7, $11, $01, $EA, $1C
	.byte $00, $E9, $1E, $00, $E7, $11, $01, $E9, $1C, $01, $E7, $11, $01, $EA, $1C, $00, $E9, $1E, $00, $E7
	.byte $11, $01, $E9, $1C, $01, $E7, $11, $01, $EA, $1C, $00, $E9, $1E, $00, $E7, $11, $01, $E9, $1C, $01
	.byte $E7, $11, $01, $EA, $1C, $00, $E9, $1E, $00, $E7, $11, $01, $E9, $1C, $01, $E7, $11, $01, $EA, $1C
	.byte $00, $E9, $1E, $00, $E7, $11, $01, $E9, $1C, $01, $E7, $11, $01, $EA, $1C, $00, $E9, $1E, $00, $E7
	.byte $11, $01, $E9, $1C, $01, $E7, $11, $01, $EA, $1C, $00, $E9, $1E, $00, $E7, $11, $01, $E9, $1C, $01

; Bank 3
ft_s3p2c4:
	.byte $82, $03, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $83, $1D, $03

; Bank 3
ft_s3p3c0:
	.byte $82, $01, $80, $20, $F7, $1E, $00, $80, $22, $00, $80, $20, $00, $21, $20, $80, $22, $1C, $80, $20
	.byte $20, $1E, $00, $80, $22, $00, $80, $20, $25, $00, $19, $80, $22, $1C, $80, $20, $20, $1E, $00, $80
	.byte $22, $00, $80, $20, $19, $1C, $1E, $80, $22, $21, $80, $20, $23, $1E, $00, $80, $22, $00, $80, $20
	.byte $25, $2A, $00, $80, $22, $21, $83, $80, $20, $20, $01

; Bank 3
ft_s3p3c1:
	.byte $E2, $FF, $2A, $07, $82, $01, $2D, $2C, $28, $2C, $83, $2A, $05, $31, $03, $25, $01, $28, $01, $2C
	.byte $01, $2A, $05, $82, $01, $25, $28, $2A, $2D, $2F, $83, $2A, $05, $31, $01, $36, $03, $2D, $01, $2C
	.byte $01

; Bank 3
ft_s3p3c3:
	.byte $82, $01, $E7, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11
	.byte $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $83, $11, $01

; Bank 3
ft_s3p3c4:
	.byte $82, $01, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D
	.byte $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $83, $1D, $01

; Bank 3
ft_s3p4c0:
	.byte $82, $00, $E2, $FF, $1E, $1E, $2A, $2A, $28, $28, $25, $83, $25, $03, $F7, $2D, $01, $2C, $01, $28
	.byte $00, $FF, $1E, $00, $1E, $01, $28, $00, $28, $01, $25, $00, $25, $01, $F7, $31, $03, $25, $01, $82
	.byte $00, $28, $FF, $1E, $1E, $28, $28, $2A, $2A, $25, $82, $01, $25, $F7, $25, $28, $2A, $83, $2D, $00
	.byte $FF, $28, $00, $28, $01, $2A, $00, $2A, $01, $25, $00, $25, $01, $F7, $31, $01, $36, $03, $2D, $00

; Bank 3
ft_s3p4c1:
	.byte $E2, $2A, $3F

; Bank 3
ft_s3p4c2:
	.byte $00, $02, $88, $00, $00, $3C

; Bank 3
ft_s3p4c3:
	.byte $00, $07, $E0, $F1, $1D, $01, $82, $00, $F2, $00, $F3, $00, $F4, $00, $F6, $00, $F8, $00, $83, $FC
	.byte $00, $30

; Bank 3
ft_s3p5c0:
	.byte $82, $00, $E2, $FF, $1E, $FF, $1E, $FF, $2A, $FF, $2A, $FF, $28, $FF, $28, $FF, $25, $FF, $25, $80
	.byte $20, $F3, $12, $83, $F1, $00, $01, $82, $00, $F3, $12, $12, $F3, $1E, $1E, $F1, $00, $E2, $FF, $1E
	.byte $FF, $1E, $80, $20, $F3, $1E, $E2, $FF, $28, $FF, $28, $F1, $00, $FF, $25, $FF, $25, $80, $20, $F3
	.byte $10, $83, $F1, $00, $01, $82, $00, $F3, $10, $10, $F3, $1C, $1C, $F1, $00, $E2, $FF, $1E, $FF, $1E
	.byte $FF, $28, $FF, $28, $FF, $2A, $FF, $2A, $FF, $25, $FF, $25, $80, $20, $F3, $0D, $83, $F1, $00, $01
	.byte $82, $00, $F3, $0D, $0D, $F3, $19, $19, $F1, $00, $E2, $FF, $28, $FF, $28, $80, $20, $F3, $19, $E2
	.byte $FF, $2A, $FF, $2A, $F1, $00, $FF, $25, $FF, $25, $80, $20, $F3, $10, $83, $F1, $00, $01, $F3, $15
	.byte $00, $15, $00, $F1, $00, $01, $F3, $14, $00

; Bank 3
ft_s3p5c3:
	.byte $E7, $FF, $11, $05, $FF, $11, $01, $E8, $11, $07, $E7, $11, $02, $FF, $11, $02, $FF, $11, $01, $E8
	.byte $11, $07, $E7, $FF, $11, $05, $FF, $11, $01, $E8, $11, $07, $E7, $11, $02, $FF, $11, $02, $FF, $11
	.byte $01, $E8, $11, $07

; Bank 3
ft_s3p5c4:
	.byte $1D, $05, $1D, $01, $1E, $07, $1D, $02, $1D, $02, $1D, $01, $1E, $07, $1D, $05, $1D, $01, $1E, $07
	.byte $1D, $02, $1D, $02, $1D, $01, $1E, $07

; Bank 3
ft_s3p6c3:
	.byte $E7, $FF, $11, $05, $FF, $11, $01, $E8, $11, $07, $E7, $11, $02, $11, $02, $E8, $11, $09, $E7, $FF
	.byte $11, $05, $FF, $11, $01, $E8, $11, $07, $E7, $11, $02, $11, $02, $E8, $11, $09

; Bank 3
ft_s3p6c4:
	.byte $1D, $05, $1D, $01, $1E, $07, $1D, $02, $1D, $02, $1E, $09, $1D, $05, $1D, $01, $1E, $07, $1D, $02
	.byte $1D, $02, $1E, $09

; Bank 3
ft_s4_frames:
	.word ft_s4f0
	.word ft_s4f1
	.word ft_s4f2
	.word ft_s4f3
	.word ft_s4f4
	.word ft_s4f5
ft_s4f0:
	.word ft_s4p1c0, ft_s4p1c1, ft_s4p0c2, ft_s4p0c3, ft_s1p8c4
	.byte $03, $03, $03, $03, $03
ft_s4f1:
	.word ft_s4p1c0, ft_s4p2c1, ft_s0p0c2, ft_s4p1c3, ft_s1p8c4
	.byte $03, $04, $03, $03, $03
ft_s4f2:
	.word ft_s4p2c0, ft_s4p3c1, ft_s0p0c2, ft_s4p2c3, ft_s4p2c4
	.byte $04, $04, $03, $04, $04
ft_s4f3:
	.word ft_s4p3c0, ft_s4p3c1, ft_s0p0c2, ft_s4p3c3, ft_s4p3c4
	.byte $04, $04, $03, $04, $04
ft_s4f4:
	.word ft_s4p4c0, ft_s4p4c1, ft_s0p0c2, ft_s4p4c3, ft_s4p4c4
	.byte $04, $04, $03, $04, $04
ft_s4f5:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
; Bank 3
ft_s4p0c2:
	.byte $E0, $8C, $10, $33, $17, $7F, $27

; Bank 3
ft_s4p0c3:
	.byte $80, $24, $FF, $1C, $07, $7E, $2F, $82, $00, $EF, $F0, $1C, $F5, $00, $F8, $00, $FB, $00, $80, $24
	.byte $1C, $FA, $00, $FC, $00, $83, $EF, $FF, $1C, $00

; Bank 3
ft_s4p1c0:
	.byte $82, $01, $80, $20, $93, $01, $F8, $27, $7E, $27, $25, $83, $9B, $04, $27, $00, $9B, $04, $27, $00
	.byte $82, $01, $2A, $29, $2C, $2E, $82, $00, $7E, $9B, $04, $2E, $2E, $7E, $82, $01, $2C, $2E, $31, $30
	.byte $2C, $2E, $7E, $2E, $2C, $83, $9B, $04, $2E, $00, $2E, $00, $82, $01, $30, $31, $30, $2C, $82, $00
	.byte $9B, $04, $2E, $9B, $04, $2E, $2E, $7E, $83, $2C, $01, $9B, $04, $2E, $00, $9B, $04, $2E, $00, $2C
	.byte $01, $2E, $01, $30, $01

; Bank 3
ft_s4p1c1:
	.byte $EF, $93, $01, $8A, $FD, $1B, $00, $FA, $00, $00, $F7, $00, $01, $FD, $00, $00, $FA, $00, $00, $F7
	.byte $00, $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01
	.byte $FD, $16, $00, $FA, $00, $00, $F7, $00, $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01, $FD, $00
	.byte $00, $FA, $00, $00, $F7, $00, $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01, $FD, $22, $00, $FA
	.byte $00, $00, $F7, $00, $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01, $FD, $00, $00, $FA, $00, $00
	.byte $F7, $00, $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01, $FD, $20, $00, $FA, $00, $00, $F7, $00
	.byte $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01, $FD, $00, $00, $FA, $00, $00, $F7, $00, $01, $FD
	.byte $00, $00, $FA, $00, $00, $F7, $00, $01

; Bank 3
ft_s4p1c3:
	.byte $80, $24, $1C, $07, $7E, $33, $82, $00, $EF, $F0, $1C, $F5, $00, $F8, $00, $83, $FB, $00, $00

; Bank 4
ft_s4p2c0:
	.byte $82, $01, $80, $20, $93, $00, $F8, $27, $7E, $27, $25, $83, $9B, $04, $27, $00, $9B, $04, $27, $00
	.byte $82, $01, $2A, $29, $2C, $2E, $82, $00, $7E, $9B, $04, $2E, $2E, $7E, $82, $01, $2C, $2E, $31, $30
	.byte $2C, $2E, $7E, $2E, $2C, $83, $9B, $04, $2E, $00, $2E, $00, $82, $01, $30, $31, $30, $2C, $82, $00
	.byte $9B, $04, $2E, $9B, $04, $2E, $2E, $7E, $83, $2C, $01, $9B, $04, $2E, $00, $9B, $04, $2E, $00, $2C
	.byte $01, $2E, $01, $30, $01

; Bank 4
ft_s4p2c1:
	.byte $80, $2C, $93, $01, $8A, $FD, $1B, $00, $FA, $00, $00, $F9, $00, $01, $FD, $00, $00, $FA, $00, $00
	.byte $F9, $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00
	.byte $01, $FD, $16, $00, $FA, $00, $00, $F9, $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00, $01, $FD
	.byte $00, $00, $FA, $00, $00, $F9, $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00, $01, $FD, $22, $00
	.byte $FA, $00, $00, $F9, $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00, $01, $FD, $00, $00, $FA, $00
	.byte $00, $F9, $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00, $01, $FD, $20, $00, $FA, $00, $00, $F9
	.byte $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00, $01, $FD, $00, $00, $FA, $00, $00, $F9, $00, $01
	.byte $FD, $00, $00, $FA, $00, $00, $F9, $00, $01

; Bank 4
ft_s4p2c3:
	.byte $80, $24, $FF, $1C, $03, $80, $30, $1B, $03, $1B, $03, $1B, $01, $1B, $01, $1B, $03, $1B, $01, $1B
	.byte $01, $80, $2E, $1B, $03, $80, $30, $1B, $01, $1B, $01, $80, $24, $1C, $03, $80, $30, $1B, $03, $80
	.byte $24, $1C, $03, $1C, $01, $80, $30, $1B, $01, $80, $24, $1C, $03, $80, $30, $1B, $03, $1B, $03, $1B
	.byte $01, $1B, $00, $1B, $00

; Bank 4
ft_s4p2c4:
	.byte $1D, $1F, $1D, $07, $1D, $03, $1D, $03, $1D, $0F

; Bank 4
ft_s4p3c0:
	.byte $82, $01, $80, $20, $93, $00, $F8, $27, $7E, $27, $25, $83, $9B, $04, $27, $00, $9B, $04, $27, $00
	.byte $82, $01, $2A, $29, $2C, $2E, $82, $00, $7E, $9B, $04, $2E, $2E, $7E, $82, $01, $2C, $2E, $31, $30
	.byte $2C, $2E, $7E, $2E, $2C, $83, $9B, $04, $2E, $00, $2E, $00, $82, $01, $30, $31, $30, $2C, $82, $00
	.byte $9B, $04, $2E, $9B, $04, $2E, $2E, $7E, $83, $2C, $01, $82, $00, $9B, $04, $2E, $9B, $04, $2C, $9B
	.byte $04, $2E, $9B, $04, $2C, $83, $2E, $01, $30, $01

; Bank 4
ft_s4p3c1:
	.byte $80, $2C, $8E, $CC, $FF, $1B, $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $00, $00, $FD
	.byte $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $16, $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02
	.byte $FF, $00, $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $22, $00, $FD, $00, $02, $FF, $00
	.byte $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $20, $00, $FD
	.byte $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02

; Bank 4
ft_s4p3c3:
	.byte $80, $24, $FF, $1C, $03, $80, $30, $1B, $03, $1B, $03, $1B, $01, $80, $24, $1C, $01, $1C, $03, $80
	.byte $30, $1B, $01, $1B, $01, $80, $2E, $1B, $03, $80, $30, $1B, $01, $1B, $01, $80, $24, $1C, $03, $80
	.byte $30, $1B, $03, $80, $24, $1C, $03, $1C, $01, $1C, $01, $1C, $03, $1C, $03, $1C, $03, $1C, $01, $80
	.byte $30, $1B, $00, $1B, $00

; Bank 4
ft_s4p3c4:
	.byte $1D, $0D, $1D, $01, $1D, $0F, $1D, $07, $1D, $03, $1D, $01, $1D, $01, $1D, $03, $1D, $03, $1D, $01
	.byte $1D, $01, $82, $00, $1D, $1D, $1D, $83, $1D, $00

; Bank 4
ft_s4p4c0:
	.byte $F8, $00, $01, $F7, $00, $02, $F6, $00, $03, $F5, $00, $04, $F4, $00, $05, $F2, $00, $05, $F1, $00
	.byte $05, $7F, $1F

; Bank 4
ft_s4p4c1:
	.byte $80, $2C, $8E, $CC, $FF, $20, $00, $FD, $00, $02, $FF, $00, $00, $FD, $00, $02, $FF, $00, $00, $FD
	.byte $00, $02, $FF, $00, $00, $FD, $00, $02, $82, $00, $FF, $00, $FE, $00, $FD, $00, $FC, $00, $FB, $00
	.byte $FA, $00, $F9, $00, $F8, $00, $F7, $00, $F6, $00, $F5, $00, $F4, $00, $F3, $00, $F2, $00, $F1, $00
	.byte $F0, $00, $83, $7F, $1F

; Bank 4
ft_s4p4c3:
	.byte $00, $13, $82, $01, $80, $20, $F0, $1C, $F2, $00, $F4, $00, $F6, $00, $82, $00, $F8, $00, $FA, $00
	.byte $FC, $00, $FE, $00, $83, $80, $24, $86, $06, $FF, $1C, $1F

; Bank 4
ft_s4p4c4:
	.byte $82, $00, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $83, $1D
	.byte $2F

; Bank 4
ft_s5_frames:
	.word ft_s5f0
	.word ft_s5f1
	.word ft_s5f2
	.word ft_s5f3
	.word ft_s5f4
	.word ft_s5f5
	.word ft_s5f6
	.word ft_s5f7
	.word ft_s5f8
	.word ft_s5f9
	.word ft_s5f10
	.word ft_s5f11
	.word ft_s5f12
	.word ft_s5f13
	.word ft_s5f14
	.word ft_s5f15
ft_s5f0:
	.word ft_s5p1c0, ft_s5p1c1, ft_s5p1c2, ft_s0p0c0, ft_s0p0c0
	.byte $04, $04, $04, $03, $03
ft_s5f1:
	.word ft_s5p2c0, ft_s5p1c1, ft_s5p1c2, ft_s0p0c0, ft_s0p0c0
	.byte $04, $04, $04, $03, $03
ft_s5f2:
	.word ft_s5p1c0, ft_s5p1c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f3:
	.word ft_s5p2c0, ft_s5p1c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f4:
	.word ft_s5p3c0, ft_s5p3c1, ft_s0p0c0, ft_s5p2c3, ft_s5p2c4
	.byte $04, $04, $03, $04, $04
ft_s5f5:
	.word ft_s5p4c0, ft_s5p4c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f6:
	.word ft_s5p4c0, ft_s5p4c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f7:
	.word ft_s5p4c0, ft_s5p4c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f8:
	.word ft_s5p5c0, ft_s5p5c1, ft_s5p1c2, ft_s5p3c3, ft_s5p3c4
	.byte $04, $04, $04, $04, $04
ft_s5f9:
	.word ft_s5p1c0, ft_s5p4c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f10:
	.word ft_s5p6c0, ft_s5p4c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f11:
	.word ft_s5p1c0, ft_s5p4c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f12:
	.word ft_s5p6c0, ft_s5p4c1, ft_s5p1c2, ft_s5p1c3, ft_s5p1c4
	.byte $04, $04, $04, $04, $04
ft_s5f13:
	.word ft_s5p1c0, ft_s5p1c1, ft_s5p1c2, ft_s0p0c0, ft_s0p0c0
	.byte $04, $04, $04, $03, $03
ft_s5f14:
	.word ft_s5p6c0, ft_s5p1c1, ft_s5p1c2, ft_s0p0c0, ft_s0p0c0
	.byte $04, $04, $04, $03, $03
ft_s5f15:
	.word ft_s5p1c0, ft_s5p1c1, ft_s5p2c2, ft_s0p0c0, ft_s0p0c0
	.byte $04, $04, $04, $03, $03
; Bank 4
ft_s5p1c0:
	.byte $82, $03, $E2, $92, $FF, $35, $35, $38, $38, $83, $38, $01, $33, $03, $33, $03, $31, $01, $2E, $01
	.byte $31, $01, $31, $03, $31, $03, $35, $03, $35, $01, $35, $01, $2E, $01, $33, $03, $33, $03, $31, $01
	.byte $38, $01, $37, $01

; Bank 4
ft_s5p1c1:
	.byte $E5, $8A, $FF, $11, $0B, $14, $03, $0F, $05, $0F, $09, $0D, $0F, $0F, $05, $0F, $09

; Bank 4
ft_s5p1c2:
	.byte $E0, $1D, $0B, $20, $03, $1B, $05, $1B, $09, $19, $0F, $1B, $05, $1B, $09

; Bank 4
ft_s5p1c3:
	.byte $82, $01, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11
	.byte $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11
	.byte $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11
	.byte $E9, $1C, $E8, $11, $83, $E9, $1C, $01

; Bank 4
ft_s5p1c4:
	.byte $82, $01, $1D, $13, $1E, $13, $1D, $13, $1E, $16, $1D, $11, $1E, $11, $1D, $11, $1E, $11, $1D, $0F
	.byte $1E, $0F, $1D, $0F, $1E, $0F, $1D, $11, $1E, $11, $1D, $11, $1E, $83, $11, $01

; Bank 4
ft_s5p2c0:
	.byte $82, $03, $E2, $35, $35, $38, $38, $83, $38, $01, $33, $03, $33, $03, $31, $01, $2E, $01, $31, $01
	.byte $31, $03, $31, $03, $35, $03, $35, $01, $35, $01, $2E, $01, $33, $03, $33, $03, $3A, $01, $38, $01
	.byte $37, $01

; Bank 4
ft_s5p2c2:
	.byte $E0, $1D, $02, $88, $00, $00, $3C

; Bank 4
ft_s5p2c3:
	.byte $82, $01, $E8, $11, $E7, $11, $11, $E8, $11, $E7, $11, $11, $83, $E8, $11, $00, $11, $00, $11, $00
	.byte $11, $30

; Bank 4
ft_s5p2c4:
	.byte $82, $01, $1E, $1D, $1D, $1E, $1D, $1D, $83, $1E, $00, $1E, $00, $1E, $00, $1E, $30

; Bank 4
ft_s5p3c0:
	.byte $E2, $35, $0E, $87, $01, $00, $30

; Bank 4
ft_s5p3c1:
	.byte $E5, $11, $03, $7F, $3B

; Bank 4
ft_s5p3c3:
	.byte $82, $01, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11
	.byte $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11
	.byte $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11, $E9, $1C, $E8, $11, $E9, $1C, $E7, $11
	.byte $E9, $1C, $82, $00, $E8, $11, $12, $12, $83, $13, $00

; Bank 4
ft_s5p3c4:
	.byte $82, $01, $1D, $13, $1E, $13, $1D, $13, $1E, $16, $1D, $11, $1E, $11, $1D, $11, $1E, $11, $1D, $0F
	.byte $1E, $0F, $1D, $0F, $1E, $0F, $1D, $11, $1E, $11, $1D, $11, $82, $00, $1E, $1E, $1E, $83, $1E, $00

; Bank 4
ft_s5p4c0:
	.byte $00, $02, $82, $03, $80, $24, $91, $7F, $F4, $1D, $1D, $1D, $20, $1B, $83, $7F, $01, $1B, $03, $7F
	.byte $01, $82, $03, $22, $19, $19, $19, $19, $1B, $83, $7F, $01, $1B, $03, $7F, $01, $20, $00

; Bank 4
ft_s5p4c1:
	.byte $80, $24, $8D, $3F, $FA, $1D, $02, $F7, $00, $00, $FA, $1D, $02, $F7, $00, $00, $FA, $1D, $02, $F7
	.byte $00, $00, $FA, $20, $02, $F7, $00, $00, $FA, $1B, $03, $7F, $01, $1B, $03, $7F, $00, $1B, $00, $FA
	.byte $22, $02, $F7, $00, $00, $FA, $19, $02, $F7, $00, $00, $FA, $19, $02, $F7, $00, $00, $FA, $19, $02
	.byte $F7, $00, $00, $FA, $19, $02, $F7, $00, $00, $FA, $1B, $03, $7F, $01, $1B, $03, $7F, $01, $FA, $20
	.byte $02, $F7, $00, $00

; Bank 4
ft_s5p5c0:
	.byte $00, $02, $82, $03, $80, $24, $F4, $1D, $1D, $1D, $20, $1B, $83, $7F, $01, $1B, $03, $7F, $01, $82
	.byte $03, $22, $19, $19, $19, $19, $1B, $83, $7F, $01, $27, $03, $7F, $01, $20, $00

; Bank 4
ft_s5p5c1:
	.byte $80, $24, $FA, $1D, $02, $F7, $00, $00, $FA, $1D, $02, $F7, $00, $00, $FA, $1D, $02, $F7, $00, $00
	.byte $FA, $20, $02, $F7, $00, $00, $FA, $1B, $03, $7F, $01, $1B, $03, $7F, $01, $FA, $22, $02, $F7, $00
	.byte $00, $FA, $19, $02, $F7, $00, $00, $FA, $19, $02, $F7, $00, $00, $FA, $19, $02, $F7, $00, $00, $FA
	.byte $19, $02, $F7, $00, $00, $FA, $1B, $03, $7F, $01, $27, $03, $7F, $01, $FA, $20, $02, $F7, $00, $00

; Bank 4
ft_s5p6c0:
	.byte $E2, $FF, $35, $03, $35, $03, $38, $03, $38, $01, $38, $01, $38, $01, $33, $03, $33, $03, $31, $01
	.byte $2E, $01, $31, $01, $31, $03, $31, $03, $35, $03, $35, $01, $35, $01, $2E, $01, $33, $03, $33, $03
	.byte $3A, $01, $38, $01, $37, $01

; Bank 4
ft_s6_frames:
	.word ft_s6f0
	.word ft_s6f1
	.word ft_s6f2
	.word ft_s6f3
	.word ft_s6f4
	.word ft_s6f5
	.word ft_s6f6
	.word ft_s6f7
	.word ft_s6f8
	.word ft_s6f9
	.word ft_s6f10
	.word ft_s6f11
	.word ft_s6f12
	.word ft_s6f13
	.word ft_s6f14
	.word ft_s6f15
	.word ft_s6f16
ft_s6f0:
	.word ft_s6p0c0, ft_s6p0c1, ft_s6p0c2, ft_s6p0c3, ft_s6p0c4
	.byte $04, $04, $04, $04, $04
ft_s6f1:
	.word ft_s6p1c0, ft_s6p0c1, ft_s6p0c2, ft_s6p1c2, ft_s6p1c2
	.byte $04, $04, $04, $04, $04
ft_s6f2:
	.word ft_s6p2c0, ft_s6p0c1, ft_s6p0c2, ft_s6p2c3, ft_s6p0c4
	.byte $04, $04, $04, $04, $04
ft_s6f3:
	.word ft_s6p2c0, ft_s6p0c1, ft_s6p0c2, ft_s6p3c3, ft_s6p2c4
	.byte $04, $04, $04, $04, $04
ft_s6f4:
	.word ft_s6p4c0, ft_s6p0c1, ft_s6p1c2, ft_s6p4c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f5:
	.word ft_s6p3c0, ft_s6p0c1, ft_s6p1c2, ft_s6p5c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f6:
	.word ft_s6p5c0, ft_s6p0c1, ft_s6p4c2, ft_s6p4c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f7:
	.word ft_s6p6c0, ft_s6p0c1, ft_s6p4c2, ft_s6p5c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f8:
	.word ft_s6p6c0, ft_s6p0c1, ft_s6p4c2, ft_s6p4c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f9:
	.word ft_s6p7c0, ft_s6p0c1, ft_s6p4c2, ft_s6p5c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f10:
	.word ft_s6p8c0, ft_s6p0c1, ft_s6p6c2, ft_s6p4c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f11:
	.word ft_s6p9c0, ft_s6p0c1, ft_s6p6c2, ft_s6p5c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f12:
	.word ft_s6p10c0, ft_s6p0c1, ft_s6p6c2, ft_s6p4c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f13:
	.word ft_s6p10c0, ft_s6p0c1, ft_s6p6c2, ft_s6p5c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f14:
	.word ft_s6p11c0, ft_s6p0c1, ft_s6p6c2, ft_s6p4c3, ft_s6p3c4
	.byte $04, $04, $04, $04, $04
ft_s6f15:
	.word ft_s6p11c0, ft_s6p1c1, ft_s6p6c2, ft_s6p6c3, ft_s6p4c4
	.byte $04, $04, $04, $04, $04
ft_s6f16:
	.word ft_s6p12c0, ft_s6p2c1, ft_s6p9c2, ft_s6p0c3, ft_s6p5c4
	.byte $04, $04, $04, $04, $04
; Bank 4
ft_s6p0c0:
	.byte $E4, $91, $7D, $93, $01, $FF, $36, $02, $E3, $36, $01, $36, $00, $32, $01, $39, $00, $32, $01, $3E
	.byte $00, $36, $01, $39, $00, $36, $01, $39, $02, $36, $00, $39, $01, $32, $00, $36, $02, $36, $01, $36
	.byte $00, $32, $01, $39, $00, $3E, $01, $39, $00, $37, $01, $36, $00, $34, $02, $32, $04, $93, $02, $32
	.byte $00

; Bank 4
ft_s6p0c1:
	.byte $82, $00, $80, $22, $91, $7D, $93, $02, $F8, $1A, $F4, $21, $F8, $26, $F8, $1A, $F4, $21, $F8, $26
	.byte $F8, $1A, $F4, $21, $F8, $26, $F8, $1A, $F4, $21, $F8, $26, $F8, $1E, $F4, $21, $F8, $2A, $F8, $1E
	.byte $F4, $21, $F8, $2A, $F8, $1E, $F4, $21, $F8, $2A, $F8, $1E, $F4, $21, $F8, $2A, $F8, $1F, $F4, $23
	.byte $F8, $2B, $F8, $1F, $F4, $23, $F8, $2B, $F8, $1F, $F4, $23, $F8, $2B, $F8, $1F, $F4, $23, $F8, $2B
	.byte $F8, $21, $F4, $25, $F8, $2D, $F8, $21, $F4, $25, $F8, $2D, $F8, $21, $F4, $25, $F8, $2D, $F8, $21
	.byte $F4, $25, $83, $F8, $2D, $00

; Bank 4
ft_s6p0c2:
	.byte $91, $7D, $7F, $2F

; Bank 4
ft_s6p0c3:
	.byte $E1, $FC, $1C, $00, $FA, $00, $01, $F4, $00, $00, $F1, $00, $00, $F0, $00, $2A

; Bank 4
ft_s6p0c4:
	.byte $1D, $2F

; Bank 4
ft_s6p1c0:
	.byte $E4, $93, $02, $36, $02, $36, $01, $36, $00, $32, $01, $39, $00, $32, $01, $3E, $00, $36, $01, $39
	.byte $00, $36, $01, $39, $02, $36, $00, $39, $01, $32, $00, $36, $02, $36, $01, $36, $00, $32, $01, $39
	.byte $00, $3E, $01, $40, $00, $42, $01, $43, $00, $42, $01, $3E, $00, $40, $01, $3E, $00, $40, $01, $42
	.byte $00

; Bank 4
ft_s6p1c1:
	.byte $E2, $FF, $1A, $01, $26, $00, $1A, $01, $26, $00, $1A, $01, $26, $00, $1A, $01, $26, $00, $1E, $01
	.byte $2A, $00, $1E, $01, $2A, $00, $1E, $01, $2A, $00, $1E, $01, $2A, $00, $82, $02, $39, $43, $42, $40
	.byte $45, $43, $42, $83, $3D, $02

; Bank 4
ft_s6p1c2:
	.byte $00, $2F

; Bank 4
ft_s6p2c0:
	.byte $E4, $3E, $01, $E2, $3E, $00, $42, $01, $42, $00, $43, $01, $43, $00, $42, $01, $42, $00, $3E, $01
	.byte $3E, $00, $42, $01, $42, $00, $43, $01, $43, $00, $45, $01, $45, $00, $3E, $01, $3E, $00, $42, $01
	.byte $42, $00, $43, $01, $43, $00, $42, $01, $42, $00, $3E, $01, $3E, $00, $42, $01, $42, $00, $43, $01
	.byte $43, $00, $3C, $01, $3D, $00

; Bank 4
ft_s6p2c1:
	.byte $E2, $3E, $2F

; Bank 4
ft_s6p2c3:
	.byte $E1, $FC, $1C, $00, $FA, $00, $01, $E9, $FF, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $1F, $01, $1F
	.byte $00, $EA, $1F, $02, $E9, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $EA, $1F, $02
	.byte $E9, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $EA, $1F, $02, $E9, $1F, $01, $1F
	.byte $00, $1F, $01, $1F, $00, $1F, $01, $1F, $00

; Bank 4
ft_s6p2c4:
	.byte $00, $28, $97, $02, $1D, $00, $97, $02, $1D, $02, $97, $04, $1E, $02

; Bank 4
ft_s6p3c0:
	.byte $E2, $4A, $01, $4A, $00, $48, $01, $48, $00, $47, $01, $47, $00, $45, $01, $45, $00, $43, $01, $42
	.byte $00, $43, $01, $42, $00, $43, $01, $42, $00, $40, $01, $39, $00, $3E, $01, $3E, $00, $42, $01, $42
	.byte $00, $43, $01, $43, $00, $45, $01, $45, $00, $43, $01, $42, $00, $43, $01, $42, $00, $43, $01, $42
	.byte $00, $40, $01, $3E, $00

; Bank 4
ft_s6p3c3:
	.byte $EA, $1F, $01, $E9, $1F, $00, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $EA, $1F
	.byte $02, $E9, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $EA, $1F, $02, $E9, $1F, $01
	.byte $1F, $00, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $EA, $1F, $02, $E9, $1F, $01, $1F, $00, $1F, $01
	.byte $1F, $00, $E8, $13, $01, $E9, $1F, $00

; Bank 4
ft_s6p3c4:
	.byte $97, $02, $1D, $02, $97, $04, $1E, $01, $97, $02, $1D, $02, $97, $02, $1D, $00, $97, $04, $1E, $02
	.byte $97, $02, $1D, $02, $97, $04, $1E, $01, $97, $02, $1D, $02, $97, $02, $1D, $00, $97, $04, $1E, $02
	.byte $97, $02, $1D, $02, $97, $04, $1E, $01, $97, $02, $1D, $02, $97, $02, $1D, $00, $97, $04, $1E, $02
	.byte $97, $02, $1D, $02, $97, $04, $1E, $01, $97, $02, $1D, $02, $97, $02, $1D, $00, $97, $04, $1E, $02

; Bank 4
ft_s6p4c0:
	.byte $E2, $3E, $01, $3E, $00, $42, $01, $42, $00, $43, $01, $43, $00, $42, $01, $42, $00, $3E, $01, $3E
	.byte $00, $42, $01, $42, $00, $43, $01, $43, $00, $45, $01, $45, $00, $3E, $01, $3E, $00, $42, $01, $42
	.byte $00, $43, $01, $43, $00, $42, $01, $42, $00, $3E, $01, $3E, $00, $42, $01, $42, $00, $43, $01, $43
	.byte $00, $45, $01, $45, $00

; Bank 4
ft_s6p4c2:
	.byte $7F, $01, $E0, $1A, $00, $7F, $01, $1A, $00, $7F, $01, $1A, $00, $7F, $01, $1A, $00, $7F, $01, $1E
	.byte $00, $7F, $01, $1E, $00, $7F, $01, $1E, $00, $7F, $01, $1E, $00, $7F, $01, $1F, $00, $7F, $01, $1F
	.byte $00, $7F, $01, $1F, $00, $7F, $01, $1F, $00, $7F, $01, $21, $00, $7F, $01, $21, $00, $7F, $01, $21
	.byte $00, $7F, $01, $21, $00

; Bank 4
ft_s6p4c3:
	.byte $E1, $FC, $1C, $00, $FA, $00, $01, $E8, $FF, $13, $01, $E9, $1F, $00, $1F, $01, $1F, $00, $E8, $13
	.byte $01, $E9, $1F, $00, $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01, $1F, $00
	.byte $E8, $13, $01, $E9, $1F, $00, $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01
	.byte $1F, $00, $E8, $13, $01, $E9, $1F, $00, $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00
	.byte $1F, $01, $1F, $00, $E8, $13, $01, $E9, $1F, $00

; Bank 4
ft_s6p4c4:
	.byte $96, $4F, $1D, $02, $1E, $01, $1D, $02, $1D, $00, $1E, $02, $1D, $02, $1E, $01, $1D, $02, $1D, $00
	.byte $1E, $17, $1E, $02

; Bank 4
ft_s6p5c0:
	.byte $FD, $00, $00, $F5, $00, $00, $E3, $FF, $36, $00, $37, $01, $36, $00, $37, $01, $39, $02, $3E, $00
	.byte $39, $01, $37, $00, $36, $02, $37, $01, $36, $00, $32, $01, $36, $00, $32, $01, $36, $00, $37, $01
	.byte $36, $00, $37, $01, $39, $02, $3E, $00, $39, $01, $37, $00, $36, $01, $39, $00, $37, $01, $36, $00
	.byte $37, $01, $39, $00

; Bank 4
ft_s6p5c3:
	.byte $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01, $1F, $00, $E8, $13, $01, $E9
	.byte $1F, $00, $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01, $1F, $00, $E8, $13
	.byte $01, $E9, $1F, $00, $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01, $1F, $00
	.byte $E8, $13, $01, $E9, $1F, $00, $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01
	.byte $1F, $00, $E8, $13, $01, $E9, $1F, $00

; Bank 4
ft_s6p5c4:
	.byte $1D, $06, $88, $00, $00, $28

; Bank 4
ft_s6p6c0:
	.byte $E3, $32, $01, $36, $00, $37, $01, $36, $00, $37, $01, $39, $02, $3E, $00, $39, $01, $37, $00, $36
	.byte $02, $37, $01, $36, $00, $32, $01, $36, $00, $32, $01, $36, $00, $37, $01, $36, $00, $37, $01, $39
	.byte $02, $3E, $00, $39, $01, $37, $00, $36, $02, $37, $01, $36, $00, $37, $01, $39, $00

; Bank 4
ft_s6p6c2:
	.byte $E0, $1A, $01, $7F, $08, $1A, $00, $1E, $01, $7F, $08, $1E, $00, $1F, $01, $7F, $08, $1F, $00, $21
	.byte $01, $7F, $09

; Bank 4
ft_s6p6c3:
	.byte $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01, $1F, $00, $E8, $13, $01, $E9
	.byte $1F, $00, $EA, $1F, $01, $E9, $1F, $00, $E8, $13, $01, $E9, $1F, $00, $1F, $01, $1F, $00, $E8, $13
	.byte $01, $E9, $1F, $00, $F8, $1F, $01, $1F, $00, $FA, $1F, $01, $1F, $00, $FB, $1F, $01, $1F, $00, $1F
	.byte $01, $1F, $00, $FC, $1F, $01, $1F, $00, $FF, $1F, $01, $1F, $00, $1F, $01, $1F, $00, $E8, $13, $02

; Bank 4
ft_s6p7c0:
	.byte $E3, $32, $01, $36, $00, $37, $01, $36, $00, $37, $01, $39, $02, $3E, $00, $39, $01, $37, $00, $36
	.byte $02, $37, $01, $36, $00, $32, $01, $36, $00, $32, $01, $36, $00, $37, $01, $36, $00, $37, $01, $39
	.byte $02, $3E, $00, $42, $01, $43, $00, $42, $01, $3E, $00, $40, $01, $3E, $00, $40, $01, $42, $00

; Bank 4
ft_s6p8c0:
	.byte $E2, $3E, $00, $7F, $00, $EC, $26, $00, $7F, $02, $26, $00, $7F, $00, $26, $00, $7F, $01, $26, $00
	.byte $2A, $00, $7F, $01, $82, $00, $2A, $7F, $2B, $2A, $7F, $2A, $83, $7F, $01, $2A, $00, $2B, $00, $7F
	.byte $01, $2B, $00, $7F, $00, $2D, $00, $7F, $01, $2B, $00, $7F, $01, $2B, $00, $2D, $00, $7F, $01, $82
	.byte $00, $2D, $7F, $32, $31, $7F, $2D, $83, $7F, $01, $2D, $00

; Bank 4
ft_s6p9c0:
	.byte $E2, $1A, $00, $7F, $00, $EC, $26, $00, $7F, $02, $26, $00, $7F, $00, $26, $00, $7F, $01, $26, $00
	.byte $2A, $00, $7F, $01, $82, $00, $2A, $7F, $2B, $2A, $7F, $2A, $83, $7F, $01, $2A, $00, $2B, $00, $7F
	.byte $01, $2B, $00, $7F, $00, $2D, $00, $7F, $01, $2B, $00, $7F, $01, $2B, $00, $2D, $00, $7F, $01, $2D
	.byte $00, $7F, $00, $31, $00, $7F, $01, $2D, $00, $7F, $01, $2D, $00

; Bank 4
ft_s6p9c2:
	.byte $E0, $1A, $02, $7F, $2C

; Bank 4
ft_s6p10c0:
	.byte $E3, $3E, $04, $37, $02, $39, $01, $7F, $01, $3E, $02, $43, $02, $42, $01, $37, $00, $40, $02, $3E
	.byte $04, $37, $02, $39, $01, $7F, $01, $3E, $02, $43, $02, $42, $01, $43, $00, $45, $02

; Bank 4
ft_s6p11c0:
	.byte $82, $02, $E6, $32, $37, $36, $34, $32, $37, $36, $34, $32, $37, $36, $34, $39, $37, $36, $83, $31
	.byte $02

; Bank 4
ft_s6p12c0:
	.byte $E4, $32, $02, $7F, $2C

; Bank 4
ft_s7_frames:
	.word ft_s7f0
	.word ft_s7f1
	.word ft_s7f2
	.word ft_s7f3
	.word ft_s7f4
	.word ft_s7f5
	.word ft_s7f6
	.word ft_s7f7
	.word ft_s7f8
ft_s7f0:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p1c3, ft_s7p0c0
	.byte $04, $04, $04, $04, $04
ft_s7f1:
	.word ft_s7p1c0, ft_s7p1c1, ft_s7p0c0, ft_s7p2c3, ft_s7p1c4
	.byte $04, $04, $04, $04, $04
ft_s7f2:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p2c3, ft_s7p1c4
	.byte $04, $04, $04, $04, $04
ft_s7f3:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p2c3, ft_s7p1c4
	.byte $04, $04, $04, $04, $04
ft_s7f4:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p2c3, ft_s7p2c4
	.byte $04, $04, $04, $04, $04
ft_s7f5:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p2c3, ft_s7p1c4
	.byte $04, $04, $04, $04, $04
ft_s7f6:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p2c3, ft_s7p1c4
	.byte $04, $04, $04, $04, $04
ft_s7f7:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p2c3, ft_s7p1c4
	.byte $04, $04, $04, $04, $04
ft_s7f8:
	.word ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p3c3, ft_s7p2c4
	.byte $04, $04, $04, $04, $04
; Bank 4
ft_s7p0c0:
	.byte $00, $1F

; Bank 4
ft_s7p1c0:
	.byte $EF, $93, $02, $F8, $2C, $00, $FC, $00, $00, $FE, $00, $05, $7E, $07, $F8, $2F, $00, $FC, $00, $02
	.byte $2A, $03, $36, $05, $7E, $01

; Bank 4
ft_s7p1c1:
	.byte $00, $07, $EF, $93, $02, $F8, $33, $00, $FC, $00, $00, $FE, $00, $05, $7E, $01, $F2, $2E, $00, $F6
	.byte $00, $00, $F8, $7E, $01, $F2, $2F, $00, $F6, $00, $00, $F8, $7E, $07

; Bank 4
ft_s7p1c3:
	.byte $82, $00, $E0, $F6, $1C, $1B, $1A, $19, $18, $83, $17, $03, $82, $00, $18, $19, $1A, $1B, $83, $1C
	.byte $01, $87, $01, $00, $10

; Bank 4
ft_s7p1c4:
	.byte $16, $02, $16, $02, $16, $01, $19, $02, $19, $02, $19, $01, $1B, $02, $1B, $02, $1B, $01, $1C, $02
	.byte $1C, $02, $1C, $01

; Bank 4
ft_s7p2c3:
	.byte $00, $01, $E9, $FF, $1A, $01, $1D, $00, $1C, $00, $1A, $03, $82, $00, $1A, $20, $1D, $1C, $83, $1A
	.byte $03, $1A, $01, $E3, $1A, $00, $E9, $1C, $00, $1A, $03, $1A, $00, $19, $00, $17, $01, $1A, $01

; Bank 4
ft_s7p2c4:
	.byte $1B, $02, $1B, $02, $1B, $01, $19, $02, $19, $02, $19, $01, $18, $02, $18, $02, $18, $01, $16, $02
	.byte $16, $02, $16, $01

; Bank 4
ft_s7p3c3:
	.byte $00, $17, $E8, $11, $00, $11, $01, $11, $01, $11, $00, $11, $00, $11, $00

; Bank 4
ft_s8_frames:
	.word ft_s8f0
	.word ft_s8f1
	.word ft_s8f2
	.word ft_s8f3
	.word ft_s8f4
	.word ft_s8f5
	.word ft_s8f6
	.word ft_s8f7
	.word ft_s8f8
	.word ft_s8f9
	.word ft_s8f10
	.word ft_s8f11
	.word ft_s8f12
	.word ft_s8f13
ft_s8f0:
	.word ft_s8p0c0, ft_s8p0c1, ft_s8p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $05, $05, $05, $03, $03
ft_s8f1:
	.word ft_s8p0c0, ft_s8p0c1, ft_s8p0c2, ft_s8p1c3, ft_s0p0c2
	.byte $05, $05, $05, $05, $03
ft_s8f2:
	.word ft_s8p1c0, ft_s8p1c1, ft_s8p1c2, ft_s8p2c3, ft_s1p8c4
	.byte $05, $05, $05, $05, $03
ft_s8f3:
	.word ft_s8p1c0, ft_s8p1c1, ft_s8p2c2, ft_s8p3c3, ft_s8p2c4
	.byte $05, $05, $05, $05, $05
ft_s8f4:
	.word ft_s8p2c0, ft_s8p2c1, ft_s8p3c2, ft_s8p4c3, ft_s8p3c4
	.byte $05, $05, $05, $05, $05
ft_s8f5:
	.word ft_s8p1c0, ft_s8p1c1, ft_s8p4c2, ft_s8p5c3, ft_s8p4c4
	.byte $05, $05, $05, $05, $05
ft_s8f6:
	.word ft_s8p1c0, ft_s8p1c1, ft_s8p4c2, ft_s8p6c3, ft_s8p4c4
	.byte $05, $05, $05, $05, $05
ft_s8f7:
	.word ft_s8p1c0, ft_s8p3c1, ft_s8p5c2, ft_s8p5c3, ft_s8p5c4
	.byte $05, $05, $05, $05, $05
ft_s8f8:
	.word ft_s8p1c0, ft_s8p3c1, ft_s8p5c2, ft_s8p6c3, ft_s8p5c4
	.byte $05, $05, $05, $05, $05
ft_s8f9:
	.word ft_s8p2c0, ft_s8p2c1, ft_s8p3c2, ft_s8p4c3, ft_s8p3c4
	.byte $05, $05, $05, $05, $05
ft_s8f10:
	.word ft_s8p3c0, ft_s8p3c1, ft_s8p5c2, ft_s8p5c3, ft_s8p5c4
	.byte $05, $05, $05, $05, $05
ft_s8f11:
	.word ft_s8p4c0, ft_s8p3c1, ft_s8p5c2, ft_s8p6c3, ft_s8p5c4
	.byte $05, $05, $05, $05, $05
ft_s8f12:
	.word ft_s8p3c0, ft_s8p3c1, ft_s8p5c2, ft_s8p5c3, ft_s8p5c4
	.byte $05, $05, $05, $05, $05
ft_s8f13:
	.word ft_s8p6c0, ft_s8p4c1, ft_s8p6c2, ft_s8p7c3, ft_s8p6c4
	.byte $05, $05, $05, $05, $05
; Bank 5
ft_s8p0c0:
	.byte $82, $01, $80, $20, $F6, $2C, $F2, $2B, $F6, $2C, $24, $F2, $2C, $F6, $24, $F2, $24, $F6, $24, $27
	.byte $F2, $24, $F6, $27, $27, $F2, $27, $F6, $2C, $F2, $27, $F6, $2B, $29, $F2, $2B, $F6, $29, $27, $F2
	.byte $29, $F6, $27, $F2, $27, $F6, $24, $25, $24, $25, $2B, $F2, $25, $F6, $2B, $F2, $2B, $83, $F6, $2B
	.byte $01

; Bank 5
ft_s8p0c1:
	.byte $82, $0F, $80, $20, $91, $81, $F3, $1D, $18, $19, $83, $1B, $0F

; Bank 5
ft_s8p0c2:
	.byte $E0, $1D, $0F, $18, $0F, $19, $17, $1B, $07

; Bank 5
ft_s8p1c0:
	.byte $82, $01, $80, $20, $8E, $0C, $F6, $2C, $F2, $2B, $F6, $2C, $24, $F2, $2C, $F6, $24, $F2, $24, $F6
	.byte $24, $27, $F2, $24, $F6, $27, $27, $F2, $27, $F6, $2C, $F2, $27, $F6, $2B, $29, $F2, $2B, $F6, $29
	.byte $27, $F2, $29, $F6, $27, $F2, $27, $F6, $24, $25, $24, $25, $2B, $F2, $25, $F6, $2B, $F2, $2B, $83
	.byte $F6, $2B, $01

; Bank 5
ft_s8p1c1:
	.byte $82, $03, $80, $20, $91, $81, $F5, $11, $11, $11, $11, $0C, $0C, $0C, $0C, $0D, $0D, $0D, $0D, $0D
	.byte $0D, $0F, $83, $0F, $03

; Bank 5
ft_s8p1c2:
	.byte $EB, $27, $01, $E0, $11, $0D, $0C, $0F, $0D, $17, $E1, $0F, $07

; Bank 5
ft_s8p1c3:
	.byte $00, $1F, $E0, $F1, $1D, $0B, $F2, $00, $06, $F3, $00, $04, $F4, $00, $01, $82, $00, $F5, $00, $F6
	.byte $00, $F7, $00, $F8, $00, $F9, $00, $83, $FA, $00, $00

; Bank 5
ft_s8p2c0:
	.byte $82, $01, $80, $20, $F2, $2B, $F5, $00, $F2, $00, $F5, $00, $F1, $00, $F4, $00, $F1, $00, $83, $F4
	.byte $00, $00, $87, $01, $00, $00, $F1, $00, $01, $F3, $00, $01, $F1, $00, $01, $F2, $00, $29

; Bank 5
ft_s8p2c1:
	.byte $80, $20, $0F, $03, $0F, $03, $F4, $0F, $03, $0F, $0B, $F2, $0F, $03, $0F, $23

; Bank 5
ft_s8p2c2:
	.byte $E0, $11, $0F, $0C, $0F, $0D, $17, $E1, $0F, $07

; Bank 5
ft_s8p2c3:
	.byte $82, $00, $E0, $1C, $F9, $00, $F8, $00, $F7, $00, $83, $F6, $1B, $01, $F5, $00, $01, $F4, $1A, $03
	.byte $F3, $19, $03, $F2, $19, $03, $82, $00, $E4, $F7, $19, $F5, $19, $19, $19, $F7, $19, $F5, $19, $19
	.byte $19, $F7, $19, $F5, $19, $19, $19, $F7, $19, $F5, $19, $19, $19, $F7, $19, $F5, $19, $19, $19, $F7
	.byte $19, $F5, $19, $19, $19, $F7, $19, $F5, $19, $19, $19, $F7, $19, $F5, $19, $19, $19, $F7, $19, $F5
	.byte $19, $19, $19, $F7, $19, $F5, $19, $19, $19, $F7, $19, $F5, $19, $19, $83, $19, $00

; Bank 5
ft_s8p2c4:
	.byte $82, $03, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $82, $01, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E
	.byte $82, $00, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $83, $1E, $00

; Bank 5
ft_s8p3c0:
	.byte $80, $20, $8E, $0C, $F6, $29, $02, $F4, $00, $00, $F6, $27, $01, $24, $00, $F4, $00, $00, $F6, $29
	.byte $02, $F4, $00, $00, $F6, $27, $01, $24, $00, $F4, $00, $00, $F6, $24, $02, $F4, $00, $00, $F6, $20
	.byte $01, $1D, $00, $F4, $00, $00, $F6, $24, $02, $F4, $00, $00, $F6, $20, $01, $1D, $00, $F4, $00, $00
	.byte $F6, $29, $02, $F4, $00, $00, $F6, $27, $01, $24, $00, $F4, $00, $00, $F6, $20, $01, $24, $00, $F4
	.byte $00, $00, $F6, $25, $01, $20, $00, $F4, $00, $00, $F6, $27, $02, $F4, $00, $00, $F6, $00, $02, $F4
	.byte $00, $00, $F6, $29, $02, $F4, $00, $00, $F6, $27, $02, $F4, $00, $00

; Bank 5
ft_s8p3c1:
	.byte $80, $20, $91, $81, $F5, $11, $03, $8E, $C0, $29, $01, $8A, $11, $01, $11, $03, $8E, $C0, $29, $01
	.byte $8A, $11, $01, $0C, $03, $8E, $C0, $24, $01, $8A, $0C, $01, $0C, $03, $8E, $C0, $24, $01, $8A, $0C
	.byte $01, $0D, $03, $8E, $C0, $25, $01, $8A, $0D, $01, $0D, $03, $8E, $C0, $25, $01, $8A, $0D, $01, $0D
	.byte $03, $8E, $C0, $25, $01, $8A, $0D, $01, $0F, $03, $8E, $C0, $27, $01, $8A, $0F, $01

; Bank 5
ft_s8p3c2:
	.byte $EB, $27, $00, $80, $20, $8C, $1F, $1B, $01, $8C, $0F, $00, $08, $7F, $33

; Bank 5
ft_s8p3c3:
	.byte $82, $00, $E4, $F8, $19, $F6, $19, $19, $19, $F8, $19, $F6, $19, $19, $19, $F9, $19, $F7, $19, $19
	.byte $19, $F9, $19, $F7, $19, $19, $19, $FA, $1A, $F8, $1A, $1A, $1A, $FA, $1A, $F8, $1A, $1A, $1A, $FA
	.byte $1A, $F8, $1A, $1A, $1A, $FA, $1A, $F8, $1A, $1A, $1A, $FB, $1A, $F9, $1A, $1A, $1A, $FB, $1B, $F9
	.byte $1B, $1B, $1B, $FC, $1B, $FA, $1B, $1B, $1B, $FC, $1B, $FA, $1B, $1B, $1B, $FD, $1C, $FB, $1C, $1C
	.byte $1C, $FD, $1C, $FB, $1C, $1C, $1C, $FE, $1D, $FC, $1D, $1D, $1D, $FF, $1D, $FD, $1D, $FE, $1D, $83
	.byte $1D, $00

; Bank 5
ft_s8p3c4:
	.byte $1D, $05, $1E, $01, $1E, $00, $1E, $01, $82, $00, $1E, $1D, $1E, $1E, $83, $1E, $30

; Bank 5
ft_s8p4c0:
	.byte $80, $20, $8E, $0C, $F6, $29, $02, $F4, $00, $00, $F6, $27, $01, $E0, $2C, $00, $F4, $00, $00, $80
	.byte $20, $F6, $29, $02, $F4, $00, $00, $F6, $27, $01, $24, $00, $F4, $00, $00, $F6, $24, $02, $F4, $00
	.byte $00, $F6, $20, $01, $1D, $00, $F4, $00, $00, $F6, $24, $02, $F4, $00, $00, $F6, $20, $01, $1D, $00
	.byte $F4, $00, $00, $F6, $29, $02, $F4, $00, $00, $F6, $27, $01, $24, $00, $F4, $00, $00, $F6, $20, $01
	.byte $24, $00, $F4, $00, $00, $F6, $25, $01, $20, $00, $F4, $00, $00, $F6, $27, $02, $F4, $00, $00, $F6
	.byte $00, $02, $F4, $00, $00, $F6, $29, $02, $F4, $00, $00, $F6, $27, $02, $F4, $00, $00

; Bank 5
ft_s8p4c1:
	.byte $80, $20, $91, $81, $F5, $11, $03, $8E, $C0, $29, $01, $8A, $11, $01, $11, $03, $8E, $C0, $F4, $29
	.byte $01, $8A, $11, $01, $0C, $03, $8E, $C0, $24, $01, $8A, $0C, $01, $F3, $0C, $03, $8E, $C0, $24, $01
	.byte $8A, $0C, $01, $0D, $03, $8E, $C0, $F2, $25, $01, $8A, $0D, $01, $0D, $03, $8E, $C0, $25, $01, $8A
	.byte $0D, $01, $0D, $03, $8E, $C0, $F1, $25, $01, $8A, $0D, $01, $0F, $03, $8E, $C0, $27, $01, $8A, $0F
	.byte $00, $88, $00, $00, $00

; Bank 5
ft_s8p4c2:
	.byte $E0, $8A, $1D, $0F, $18, $0F, $19, $17, $1B, $07

; Bank 5
ft_s8p4c3:
	.byte $EA, $FF, $1D, $00, $E0, $F3, $1C, $03, $F2, $00, $00, $E8, $F7, $12, $01, $82, $00, $12, $12, $F9
	.byte $00, $12, $E7, $1C, $E8, $FA, $12, $12, $83, $12, $30

; Bank 5
ft_s8p4c4:
	.byte $82, $01, $1D, $13, $1D, $13, $1D, $13, $1D, $13, $1D, $0E, $1D, $0E, $1D, $0E, $1D, $0E, $1D, $0F
	.byte $1D, $0F, $1D, $0F, $1D, $0F, $1D, $0F, $1D, $0F, $1D, $11, $1D, $83, $11, $01

; Bank 5
ft_s8p5c2:
	.byte $E0, $8A, $1D, $03, $EB, $27, $00, $E0, $1D, $02, $1D, $03, $EB, $27, $00, $E0, $1D, $02, $18, $03
	.byte $EB, $27, $00, $E0, $18, $02, $18, $03, $EB, $27, $00, $E0, $18, $02, $19, $03, $EB, $27, $00, $E0
	.byte $19, $02, $19, $03, $EB, $27, $00, $E0, $19, $02, $19, $03, $EB, $27, $00, $E0, $19, $02, $1B, $03
	.byte $EB, $27, $00, $E0, $1B, $02

; Bank 5
ft_s8p5c3:
	.byte $EA, $FF, $1D, $00, $E0, $F5, $1C, $02, $F6, $1B, $03, $F4, $1A, $01, $EA, $FF, $1D, $00, $FB, $1D
	.byte $00, $E0, $F3, $19, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E0, $F2, $19, $01, $EA, $FF, $1D, $00
	.byte $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E7, $FF, $20, $01, $EA, $FF, $1D
	.byte $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E7, $FF, $20, $01, $EA, $FF
	.byte $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E7, $FF, $20, $01, $EA
	.byte $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E7, $FF, $20, $01
	.byte $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E7, $FF, $20
	.byte $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB, $1D, $00

; Bank 5
ft_s8p5c4:
	.byte $82, $01, $1D, $13, $1E, $13, $1D, $13, $1E, $13, $1D, $0E, $1E, $0E, $1D, $0E, $1E, $0E, $1D, $0F
	.byte $1E, $0F, $1D, $0F, $1E, $0F, $1D, $0F, $1E, $0F, $1D, $11, $1E, $83, $11, $01

; Bank 5
ft_s8p6c0:
	.byte $80, $20, $8E, $0C, $F6, $29, $02, $F4, $00, $00, $F6, $27, $01, $24, $00, $F4, $00, $00, $F6, $29
	.byte $02, $F4, $00, $00, $F5, $27, $01, $24, $00, $F3, $00, $00, $F5, $24, $02, $F3, $00, $00, $F5, $20
	.byte $01, $1D, $00, $F3, $00, $00, $F4, $24, $02, $F3, $00, $00, $F4, $20, $01, $1D, $00, $F3, $00, $00
	.byte $F4, $29, $02, $F2, $00, $00, $F3, $27, $01, $24, $00, $F2, $00, $00, $F3, $20, $01, $24, $00, $F1
	.byte $00, $00, $F2, $25, $01, $20, $00, $F1, $00, $00, $F2, $27, $02, $F1, $00, $00, $F2, $00, $02, $F0
	.byte $00, $00, $F1, $29, $02, $F0, $00, $00, $F1, $27, $02, $F0, $00, $00

; Bank 5
ft_s8p6c2:
	.byte $EB, $27, $00, $E0, $1D, $0E, $18, $0F, $19, $17, $1B, $07

; Bank 5
ft_s8p6c3:
	.byte $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB, $1D
	.byte $00, $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00, $FB
	.byte $1D, $00, $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D, $00
	.byte $FB, $1D, $00, $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF, $1D
	.byte $00, $FB, $1D, $00, $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA, $FF
	.byte $1D, $00, $FB, $1D, $00, $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01, $EA
	.byte $FF, $1D, $00, $FB, $1D, $00, $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12, $01
	.byte $EA, $FF, $1D, $00, $FB, $1D, $00, $E7, $FF, $20, $01, $EA, $FF, $1D, $00, $FB, $1D, $00, $E8, $12
	.byte $01, $EA, $FF, $1D, $00, $FB, $1D, $00

; Bank 5
ft_s8p6c4:
	.byte $1D, $00, $07, $3E

; Bank 5
ft_s8p7c3:
	.byte $EA, $FF, $1D, $00, $E0, $F3, $1C, $03, $F2, $00, $05, $F1, $00, $04, $1D, $07, $7F, $27

; Bank 5
ft_s9_frames:
	.word ft_s9f0
ft_s9f0:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
; Bank 5
ft_s10_frames:
	.word ft_s10f0
	.word ft_s10f1
	.word ft_s10f2
	.word ft_s10f3
	.word ft_s10f4
	.word ft_s10f5
ft_s10f0:
	.word ft_s10p0c0, ft_s10p0c1, ft_s10p0c2, ft_s10p0c3, ft_s0p0c0
	.byte $05, $05, $05, $05, $03
ft_s10f1:
	.word ft_s10p1c0, ft_s10p1c1, ft_s10p0c2, ft_s10p1c3, ft_s10p1c4
	.byte $05, $05, $05, $05, $05
ft_s10f2:
	.word ft_s10p2c0, ft_s10p2c1, ft_s10p1c2, ft_s10p2c3, ft_s10p2c4
	.byte $05, $05, $05, $05, $05
ft_s10f3:
	.word ft_s10p1c0, ft_s10p1c1, ft_s10p2c2, ft_s10p3c3, ft_s10p1c4
	.byte $05, $05, $05, $05, $05
ft_s10f4:
	.word ft_s10p2c0, ft_s10p3c1, ft_s10p2c2, ft_s10p3c3, ft_s10p2c4
	.byte $05, $05, $05, $05, $05
ft_s10f5:
	.word ft_s10p3c0, ft_s10p4c1, ft_s10p3c2, ft_s10p4c3, ft_s10p3c4
	.byte $05, $05, $05, $05, $05
; Bank 5
ft_s10p0c0:
	.byte $80, $28, $8A, $FA, $20, $00, $7F, $00, $1F, $00, $7F, $3C

; Bank 5
ft_s10p0c1:
	.byte $8A, $7F, $00, $80, $28, $F2, $20, $00, $7F, $00, $9B, $04, $1F, $3C

; Bank 5
ft_s10p0c2:
	.byte $8A, $7F, $3F

; Bank 5
ft_s10p0c3:
	.byte $80, $28, $93, $00, $F2, $1A, $00, $F4, $1B, $00, $F6, $1C, $00, $E4, $87, $01, $FA, $1C, $3C

; Bank 5
ft_s10p1c0:
	.byte $80, $28, $F8, $18, $00, $7E, $02, $F8, $1F, $00, $7E, $02, $F8, $1E, $00, $7E, $02, $F8, $1F, $00
	.byte $7E, $02, $F8, $18, $00, $7E, $02, $E4, $8B, $04, $FC, $38, $01, $8A, $00, $09, $80, $28, $F8, $18
	.byte $00, $7E, $02, $1F, $00, $7E, $02, $1E, $00, $7E, $02, $1F, $00, $7E, $02, $20, $00, $7E, $01, $82
	.byte $00, $80, $22, $1E, $80, $28, $1F, $7E, $20, $7E, $1F, $83, $7E, $02, $F4, $1F, $00, $7E, $02

; Bank 5
ft_s10p1c1:
	.byte $8A, $00, $03, $82, $01, $EA, $FA, $30, $30, $F7, $30, $30, $F4, $30, $30, $83, $F1, $30, $03, $E3
	.byte $8B, $04, $FC, $29, $01, $8A, $00, $0D, $E4, $8B, $14, $F8, $31, $00, $7F, $06, $31, $00, $7F, $06
	.byte $31, $00, $8A, $7F, $06, $80, $28, $8E, $39, $FA, $28, $00, $7E, $02

; Bank 5
ft_s10p1c2:
	.byte $00, $2F, $EB, $25, $00, $7F, $01, $25, $00, $7F, $05, $25, $00, $7F, $01, $25, $00, $7F, $01

; Bank 5
ft_s10p1c3:
	.byte $EA, $FF, $1A, $01, $E9, $1A, $01, $1D, $00, $1C, $00, $1A, $03, $82, $00, $1A, $20, $1D, $1C, $83
	.byte $1A, $03, $1A, $01, $E3, $FD, $1A, $00, $E9, $FF, $1C, $00, $1A, $03, $1A, $00, $19, $00, $17, $01
	.byte $1A, $03, $1A, $01, $1D, $00, $1C, $00, $1A, $03, $82, $00, $1A, $20, $1D, $1C, $83, $1A, $03, $1A
	.byte $01, $1D, $00, $1C, $00, $1A, $03, $1A, $00, $19, $00, $17, $01, $1A, $01

; Bank 5
ft_s10p1c4:
	.byte $F4, $0E, $03, $0E, $02, $0E, $00, $F4, $00, $00, $F4, $00, $00, $F5, $0E, $03, $0E, $01, $0A, $03
	.byte $0A, $02, $09, $02, $09, $03, $09, $01, $0E, $03, $0E, $02, $0E, $02, $0E, $03, $0E, $01, $0A, $03
	.byte $0A, $02, $0F, $02, $0F, $03, $0C, $01

; Bank 5
ft_s10p2c0:
	.byte $80, $28, $F8, $18, $00, $7E, $02, $1F, $00, $7E, $02, $1E, $00, $7E, $02, $1F, $00, $7E, $02, $18
	.byte $00, $7E, $02, $E4, $8B, $04, $FC, $38, $01, $8A, $00, $09, $80, $28, $F8, $18, $00, $7E, $02, $1F
	.byte $00, $7E, $02, $1E, $00, $7E, $02, $1F, $00, $7E, $02, $20, $00, $7E, $01, $82, $00, $1F, $1B, $7E
	.byte $1A, $7E, $18, $83, $7E, $06

; Bank 5
ft_s10p2c1:
	.byte $00, $03, $E4, $8B, $14, $F8, $31, $00, $7F, $06, $31, $00, $8A, $7F, $06, $E3, $8B, $04, $FC, $29
	.byte $01, $8A, $00, $0D, $E4, $8B, $14, $F8, $31, $00, $7F, $06, $31, $00, $7F, $06, $2E, $00, $8A, $7F
	.byte $0A

; Bank 5
ft_s10p2c2:
	.byte $EB, $25, $00, $7F, $01, $82, $00, $25, $3D, $7F, $25, $83, $7F, $04, $82, $00, $3D, $7F, $25, $7F
	.byte $25, $83, $7F, $01, $82, $00, $25, $3D, $7F, $25, $83, $7F, $04, $3D, $00, $7F, $02, $25, $00, $7F
	.byte $01, $82, $00, $25, $3D, $7F, $25, $83, $7F, $04, $82, $00, $3D, $7F, $25, $7F, $25, $83, $7F, $01
	.byte $82, $00, $25, $3D, $7F, $25, $83, $7F, $03, $82, $00, $25, $3D, $7F, $25, $83, $7F, $00

; Bank 5
ft_s10p2c3:
	.byte $E9, $17, $01, $1A, $01, $1D, $00, $1C, $00, $1A, $03, $82, $00, $1A, $20, $1D, $1C, $83, $1A, $03
	.byte $1A, $01, $E3, $FD, $1A, $00, $E9, $FF, $1C, $00, $1A, $03, $1A, $00, $19, $00, $EA, $1A, $01, $E9
	.byte $1A, $03, $1A, $01, $1D, $00, $1C, $00, $1A, $03, $82, $00, $1A, $20, $1D, $1C, $83, $1A, $01, $82
	.byte $00, $E7, $FF, $15, $80, $28, $F6, $18, $17, $E7, $FF, $15, $80, $28, $F4, $15, $F3, $14, $F2, $13
	.byte $F1, $00, $F2, $00, $F3, $1A, $E7, $FF, $15, $80, $28, $F5, $1C, $F6, $1D, $E7, $FF, $15, $80, $28
	.byte $F8, $1F, $83, $F9, $20, $00

; Bank 5
ft_s10p2c4:
	.byte $0E, $03, $0E, $02, $0E, $02, $0E, $03, $0E, $01, $0A, $03, $0A, $02, $09, $02, $09, $03, $09, $01
	.byte $0E, $03, $0E, $02, $0E, $02, $0E, $03, $0E, $01, $0A, $03, $82, $02, $0A, $02, $02, $83, $02, $02

; Bank 5
ft_s10p3c0:
	.byte $80, $28, $F8, $18, $00, $7E, $06, $F6, $18, $00, $7E, $04, $ED, $24, $01, $80, $28, $F4, $18, $00
	.byte $7E, $01, $ED, $24, $03, $24, $00, $80, $28, $F2, $18, $00, $7E, $00, $EE, $F5, $3C, $01, $48, $01
	.byte $3C, $01, $82, $07, $48, $3C, $80, $28, $8B, $04, $F3, $0E, $83, $8B, $11, $00, $07

; Bank 5
ft_s10p3c1:
	.byte $00, $03, $E4, $8B, $14, $F8, $31, $00, $7F, $06, $31, $00, $8A, $7F, $06, $E3, $8B, $04, $FC, $29
	.byte $01, $8A, $00, $05, $82, $01, $EA, $FA, $30, $F7, $30, $F4, $30, $F1, $30, $83, $E4, $8B, $14, $F8
	.byte $31, $00, $7F, $06, $31, $00, $7F, $06, $2E, $00, $8A, $7F, $0A

; Bank 5
ft_s10p3c2:
	.byte $00, $0F, $ED, $0C, $00, $0C, $00, $0C, $00, $EE, $0C, $01, $ED, $0C, $00, $82, $01, $EE, $0C, $0C
	.byte $E0, $0C, $18, $0C, $83, $18, $00, $7F, $06, $8B, $04, $12, $03, $8B, $14, $00, $02, $8C, $AF, $00
	.byte $00, $8B, $04, $0E, $07, $8B, $11, $00, $07

; Bank 5
ft_s10p3c3:
	.byte $E7, $FF, $15, $01, $82, $00, $E9, $1A, $E7, $15, $E8, $11, $E9, $1C, $83, $E7, $15, $03, $82, $00
	.byte $E9, $1A, $20, $E8, $11, $E9, $1C, $83, $E7, $15, $01, $15, $01, $82, $00, $E9, $1A, $E7, $15, $E8
	.byte $11, $E9, $1C, $83, $E7, $15, $03, $E9, $1A, $00, $19, $00, $E8, $11, $01, $E9, $1A, $01, $E7, $15
	.byte $01, $82, $00, $E9, $1A, $E7, $15, $E8, $11, $E9, $1C, $83, $E7, $15, $03, $82, $00, $E9, $1A, $20
	.byte $E8, $11, $E9, $1C, $83, $E7, $15, $01, $15, $01, $82, $00, $E9, $1A, $E7, $15, $E8, $11, $E9, $1C
	.byte $83, $E7, $15, $03, $E9, $1A, $00, $E7, $15, $00, $E8, $11, $01, $E7, $15, $01

; Bank 5
ft_s10p3c4:
	.byte $0E, $19, $02, $01, $0E, $01, $02, $01, $0E, $0F, $02, $0F

; Bank 5
ft_s10p4c1:
	.byte $00, $0F, $ED, $F8, $18, $00, $18, $00, $18, $00, $18, $01, $18, $00, $18, $01, $18, $00, $F8, $00
	.byte $00, $EC, $0C, $01, $18, $01, $0C, $01, $18, $00, $F1, $00, $02, $F7, $7F, $02, $ED, $18, $00, $18
	.byte $03, $18, $01, $18, $01, $E0, $8B, $04, $0E, $07, $80, $28, $8B, $11, $00, $07

; Bank 5
ft_s10p4c3:
	.byte $00, $01, $E9, $1D, $03, $1D, $03, $1D, $03, $1D, $01, $82, $00, $EA, $20, $20, $E9, $1D, $EA, $20
	.byte $E9, $1D, $ED, $1D, $E9, $1D, $83, $1D, $02, $1D, $03, $1D, $03, $1D, $03, $1D, $01, $82, $00, $EA
	.byte $20, $20, $E9, $1D, $EA, $20, $E9, $1D, $ED, $1D, $E9, $1D, $1D, $80, $28, $F1, $11, $12, $F2, $13
	.byte $14, $F3, $15, $16, $F4, $17, $18, $F5, $19, $1A, $F6, $1B, $1C, $F7, $1D, $1E, $F8, $1F, $83, $F9
	.byte $20, $00

; Bank 5
ft_s11_frames:
	.word ft_s11f0
	.word ft_s11f1
	.word ft_s11f2
	.word ft_s11f3
	.word ft_s11f4
	.word ft_s11f5
	.word ft_s11f6
	.word ft_s11f7
	.word ft_s11f8
	.word ft_s11f9
ft_s11f0:
	.word ft_s11p1c0, ft_s11p0c1, ft_s11p0c1, ft_s11p0c1, ft_s11p0c4
	.byte $05, $05, $05, $05, $05
ft_s11f1:
	.word ft_s11p2c0, ft_s11p0c1, ft_s11p0c1, ft_s11p0c1, ft_s11p0c4
	.byte $05, $05, $05, $05, $05
ft_s11f2:
	.word ft_s11p1c0, ft_s11p1c1, ft_s11p0c1, ft_s11p0c1, ft_s11p0c4
	.byte $05, $05, $05, $05, $05
ft_s11f3:
	.word ft_s11p2c0, ft_s11p2c1, ft_s11p0c1, ft_s11p0c1, ft_s11p0c4
	.byte $05, $05, $05, $05, $05
ft_s11f4:
	.word ft_s11p1c0, ft_s11p1c1, ft_s11p0c1, ft_s11p0c1, ft_s11p1c4
	.byte $05, $05, $05, $05, $05
ft_s11f5:
	.word ft_s11p2c0, ft_s11p2c1, ft_s11p0c1, ft_s11p1c3, ft_s11p1c4
	.byte $05, $05, $05, $05, $05
ft_s11f6:
	.word ft_s11p3c0, ft_s11p3c1, ft_s11p0c4, ft_s11p2c3, ft_s11p2c4
	.byte $05, $05, $05, $05, $05
ft_s11f7:
	.word ft_s11p4c0, ft_s11p4c1, ft_s11p0c4, ft_s11p2c3, ft_s11p2c4
	.byte $05, $05, $05, $05, $05
ft_s11f8:
	.word ft_s11p3c0, ft_s11p3c1, ft_s11p0c4, ft_s11p2c3, ft_s11p2c4
	.byte $05, $05, $05, $05, $05
ft_s11f9:
	.word ft_s11p5c0, ft_s11p5c1, ft_s11p0c4, ft_s11p2c3, ft_s11p2c4
	.byte $05, $05, $05, $05, $05
; Bank 5
ft_s11p0c1:
	.byte $7F, $17

; Bank 5
ft_s11p0c4:
	.byte $00, $17

; Bank 5
ft_s11p1c0:
	.byte $E2, $32, $02, $32, $01, $32, $00, $35, $01, $32, $01, $32, $00, $34, $00, $35, $02, $32, $01, $32
	.byte $00, $34, $01, $32, $01, $32, $00, $30, $00

; Bank 5
ft_s11p1c1:
	.byte $E4, $32, $02, $32, $01, $32, $00, $35, $01, $32, $01, $32, $00, $34, $00, $32, $02, $32, $01, $32
	.byte $00, $34, $00, $35, $00, $32, $01, $32, $00, $30, $00

; Bank 5
ft_s11p1c3:
	.byte $00, $0B, $E0, $F1, $1C, $02, $F2, $00, $01, $82, $00, $F3, $00, $F4, $00, $F5, $00, $F7, $00, $F9
	.byte $00, $FB, $00, $83, $FF, $00, $00

; Bank 5
ft_s11p1c4:
	.byte $82, $00, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B
	.byte $0B, $0B, $0B, $0B, $0B, $83, $0B, $00

; Bank 5
ft_s11p2c0:
	.byte $E2, $32, $02, $32, $01, $32, $00, $35, $01, $32, $01, $32, $00, $34, $00, $30, $02, $32, $01, $32
	.byte $00, $37, $01, $35, $01, $32, $00, $34, $00

; Bank 5
ft_s11p2c1:
	.byte $E4, $32, $02, $32, $01, $32, $00, $35, $00, $34, $00, $32, $01, $32, $00, $34, $00, $32, $02, $32
	.byte $01, $32, $00, $37, $01, $82, $00, $35, $30, $32, $83, $34, $00

; Bank 5
ft_s11p2c3:
	.byte $82, $00, $E7, $11, $EA, $1C, $1C, $E8, $11, $EA, $1C, $1C, $E7, $11, $EA, $1C, $1C, $E8, $11, $EA
	.byte $1C, $1C, $E7, $11, $EA, $1C, $1C, $E8, $11, $EA, $1C, $1C, $E7, $11, $EA, $1C, $1C, $E8, $11, $EA
	.byte $1C, $83, $1C, $00

; Bank 5
ft_s11p2c4:
	.byte $82, $00, $1D, $04, $04, $1E, $04, $04, $1D, $04, $04, $1E, $04, $7E, $1D, $04, $04, $1E, $04, $04
	.byte $1D, $04, $04, $1E, $04, $83, $7E, $00

; Bank 5
ft_s11p3c0:
	.byte $7F, $02, $E2, $1A, $00, $26, $00, $32, $02, $26, $01, $39, $00, $3E, $03, $1A, $00, $26, $00, $32
	.byte $02, $E3, $2D, $00, $35, $02

; Bank 5
ft_s11p3c1:
	.byte $7F, $02, $E2, $26, $00, $32, $00, $3E, $02, $32, $01, $45, $00, $4A, $03, $26, $00, $32, $00, $3E
	.byte $02, $E3, $32, $03

; Bank 5
ft_s11p4c0:
	.byte $00, $06, $E2, $32, $00, $39, $03, $82, $00, $1A, $26, $32, $26, $39, $3E, $83, $E6, $39, $01, $35
	.byte $00, $E1, $3E, $02

; Bank 5
ft_s11p4c1:
	.byte $00, $03, $E2, $32, $00, $3E, $01, $3E, $00, $45, $03, $82, $00, $26, $32, $3E, $32, $45, $4A, $83
	.byte $E6, $39, $01, $35, $00, $E1, $3E, $02

; Bank 5
ft_s11p5c0:
	.byte $00, $06, $E2, $32, $00, $39, $03, $82, $00, $1A, $26, $32, $26, $39, $3E, $83, $E6, $39, $01, $35
	.byte $00, $E1, $32, $02

; Bank 5
ft_s11p5c1:
	.byte $00, $03, $E2, $32, $00, $3E, $01, $3E, $00, $45, $03, $82, $00, $26, $32, $3E, $32, $45, $4A, $83
	.byte $E6, $39, $01, $35, $00, $E1, $32, $02

; Bank 5
ft_s12_frames:
	.word ft_s12f0
ft_s12f0:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
; Bank 5
ft_s13_frames:
	.word ft_s13f0
	.word ft_s13f1
	.word ft_s13f2
	.word ft_s13f3
	.word ft_s13f4
	.word ft_s13f5
	.word ft_s13f6
	.word ft_s13f7
ft_s13f0:
	.word ft_s13p1c0, ft_s13p0c1, ft_s13p0c1, ft_s13p0c1, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
ft_s13f1:
	.word ft_s13p2c0, ft_s13p0c1, ft_s13p0c1, ft_s13p0c1, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
ft_s13f2:
	.word ft_s13p1c0, ft_s13p0c1, ft_s13p0c1, ft_s13p1c3, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
ft_s13f3:
	.word ft_s13p1c0, ft_s13p0c1, ft_s13p0c1, ft_s13p1c3, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
ft_s13f4:
	.word ft_s13p1c0, ft_s13p0c1, ft_s13p0c1, ft_s13p1c3, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
ft_s13f5:
	.word ft_s13p1c0, ft_s13p0c1, ft_s13p0c1, ft_s13p1c3, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
ft_s13f6:
	.word ft_s13p1c0, ft_s13p0c1, ft_s13p0c1, ft_s13p1c3, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
ft_s13f7:
	.word ft_s13p1c0, ft_s13p0c1, ft_s13p0c1, ft_s13p1c3, ft_s13p0c1
	.byte $05, $05, $05, $05, $05
; Bank 5
ft_s13p0c1:
	.byte $00, $0F

; Bank 5
ft_s13p1c0:
	.byte $E4, $29, $01, $2C, $01, $29, $01, $29, $00, $29, $01, $29, $01, $24, $01, $29, $00, $31, $00, $2E
	.byte $00

; Bank 5
ft_s13p1c3:
	.byte $82, $03, $E9, $1D, $1D, $1D, $83, $1D, $03

; Bank 5
ft_s13p2c0:
	.byte $E4, $35, $00, $30, $00, $2C, $01, $29, $01, $29, $00, $29, $01, $29, $00, $2E, $00, $24, $01, $29
	.byte $00, $31, $00, $2E, $00

; Bank 5
ft_s14_frames:
	.word ft_s14f0
ft_s14f0:
	.word ft_s14p0c0, ft_s14p0c1, ft_s14p0c1, ft_s14p0c3, ft_s14p0c4
	.byte $05, $05, $05, $05, $05
; Bank 5
ft_s14p0c0:
	.byte $80, $20, $F7, $16, $00, $EF, $16, $01, $7F, $00, $80, $20, $16, $00, $EF, $16, $02, $7F, $03, $82
	.byte $00, $80, $20, $16, $7F, $16, $7F, $16, $83, $EF, $16, $01, $7F, $00, $80, $20, $16, $00, $EF, $16
	.byte $02, $7F, $07, $80, $20, $16, $00, $EF, $16, $01, $7F, $00, $80, $20, $16, $00, $EF, $16, $02, $7F
	.byte $03, $82, $00, $80, $20, $16, $7F, $16, $7F, $16, $83, $EF, $16, $02, $7F, $03, $80, $20, $16, $00
	.byte $EF, $16, $00, $80, $20, $16, $00, $EF, $16, $01, $80, $20, $16, $00, $EF, $16, $01, $80, $20, $16
	.byte $00, $EF, $16, $01, $7F, $00, $80, $20, $16, $00, $EF, $16, $02, $7F, $03, $82, $00, $80, $20, $16
	.byte $7F, $16, $7F, $16, $83, $EF, $16, $02, $80, $20, $16, $00, $EF, $16, $02, $7F, $27

; Bank 5
ft_s14p0c1:
	.byte $00, $7F

; Bank 5
ft_s14p0c3:
	.byte $00, $63, $E0, $1C, $01, $7F, $01, $82, $00, $ED, $1C, $7F, $1C, $7F, $1C, $7F, $1C, $7F, $1C, $7F
	.byte $1C, $7F, $83, $E0, $1C, $01, $7F, $01, $1C, $01, $7F, $05

; Bank 5
ft_s14p0c4:
	.byte $82, $07, $1D, $1D, $1D, $1D, $1D, $1D, $83, $27

; Bank 5
ft_s15_frames:
	.word ft_s15f0
ft_s15f0:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
; Bank 5
ft_s16_frames:
	.word ft_s16f0
	.word ft_s16f1
	.word ft_s16f2
	.word ft_s16f3
ft_s16f0:
	.word ft_s16p1c0, ft_s16p1c1, ft_s0p0c2, ft_s16p0c3, ft_s16p0c4
	.byte $05, $05, $03, $05, $05
ft_s16f1:
	.word ft_s16p2c0, ft_s16p2c1, ft_s0p0c2, ft_s16p0c3, ft_s16p0c4
	.byte $05, $05, $03, $05, $05
ft_s16f2:
	.word ft_s16p1c0, ft_s16p3c1, ft_s0p0c2, ft_s16p0c3, ft_s16p0c4
	.byte $05, $06, $03, $05, $05
ft_s16f3:
	.word ft_s16p2c0, ft_s0p0c2, ft_s0p0c2, ft_s16p0c3, ft_s16p0c4
	.byte $05, $03, $03, $05, $05
; Bank 5
ft_s16p0c3:
	.byte $82, $01, $E7, $11, $E9, $1E, $E8, $11, $E9, $1E, $1C, $E7, $11, $E8, $11, $E9, $1E, $E7, $11, $E9
	.byte $1E, $E8, $11, $E9, $1E, $1C, $E7, $11, $E8, $11, $E9, $1E, $E7, $11, $E9, $1E, $E8, $11, $E9, $1E
	.byte $1C, $E7, $11, $E8, $11, $E9, $1E, $E7, $11, $E9, $1E, $E8, $11, $82, $00, $E7, $11, $11, $E9, $1C
	.byte $E7, $11, $83, $11, $01, $E8, $11, $01, $E7, $11, $01

; Bank 5
ft_s16p0c4:
	.byte $1D, $03, $1E, $05, $1D, $01, $1E, $03, $1D, $03, $1E, $05, $1D, $01, $1E, $03, $1D, $03, $1E, $05
	.byte $1D, $01, $1E, $03, $1D, $03, $1E, $01, $1D, $00, $1D, $01, $1D, $00, $1D, $01, $1E, $01, $1D, $01

; Bank 5
ft_s16p1c0:
	.byte $E2, $13, $09, $13, $05, $13, $01, $13, $07, $13, $05, $0F, $02, $0F, $02, $0F, $05, $0F, $03, $11
	.byte $02, $11, $02, $11, $05, $11, $03

; Bank 5
ft_s16p1c1:
	.byte $E4, $13, $09, $13, $05, $13, $01, $13, $07, $13, $05, $0F, $02, $0F, $02, $0F, $05, $0F, $03, $11
	.byte $02, $11, $02, $11, $05, $11, $03

; Bank 5
ft_s16p2c0:
	.byte $E2, $13, $09, $13, $05, $13, $09, $13, $05, $0F, $02, $0F, $02, $0F, $05, $0F, $03, $11, $02, $11
	.byte $02, $11, $03, $16, $01, $15, $01, $11, $01

; Bank 5
ft_s16p2c1:
	.byte $E4, $13, $09, $13, $05, $13, $09, $13, $05, $0F, $02, $0F, $02, $0F, $05, $0F, $03, $11, $02, $11
	.byte $02, $11, $03, $16, $01, $15, $01, $11, $01

; Bank 6
ft_s16p3c1:
	.byte $82, $00, $EF, $F7, $2E, $29, $22, $2B, $83, $7F, $01, $82, $00, $1F, $7F, $1F, $7F, $1F, $7F, $1F
	.byte $83, $7F, $02, $82, $00, $1F, $7F, $1F, $2B, $83, $7F, $01, $82, $00, $2B, $7F, $1F, $7F, $1F, $7F
	.byte $1F, $83, $7F, $22

; Bank 6
ft_s17_frames:
	.word ft_s17f0
ft_s17f0:
	.word ft_s17p0c0, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $06, $03, $03, $03, $03
; Bank 6
ft_s17p0c0:
	.byte $E2, $32, $01, $37, $3D

; Bank 6
ft_s18_frames:
	.word ft_s18f0
	.word ft_s18f1
	.word ft_s18f2
	.word ft_s18f3
	.word ft_s18f4
ft_s18f0:
	.word ft_s18p3c0, ft_s18p3c1, ft_s7p0c0, ft_s7p0c0, ft_s18p3c4
	.byte $06, $06, $04, $04, $06
ft_s18f1:
	.word ft_s18p4c0, ft_s18p4c1, ft_s7p0c0, ft_s7p0c0, ft_s18p3c4
	.byte $06, $06, $04, $04, $06
ft_s18f2:
	.word ft_s18p3c0, ft_s18p3c1, ft_s7p0c0, ft_s7p0c0, ft_s18p3c4
	.byte $06, $06, $04, $04, $06
ft_s18f3:
	.word ft_s18p5c0, ft_s18p4c1, ft_s7p0c0, ft_s7p0c0, ft_s18p3c4
	.byte $06, $06, $04, $04, $06
ft_s18f4:
	.word ft_s18p16c0, ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p0c0
	.byte $06, $04, $04, $04, $04
; Bank 6
ft_s18p3c0:
	.byte $EF, $FF, $2D, $00, $8C, $0F, $00, $00, $8A, $7F, $0F, $82, $00, $2D, $7F, $2D, $7F, $2D, $7F, $2F
	.byte $83, $7F, $01, $2F, $00, $7F, $01, $31, $00, $7F, $00

; Bank 6
ft_s18p3c1:
	.byte $FF, $00, $11, $82, $00, $EF, $28, $7F, $28, $7F, $28, $7F, $2B, $83, $7F, $01, $2B, $00, $7F, $01
	.byte $2D, $00, $7F, $00

; Bank 6
ft_s18p3c4:
	.byte $0B, $02, $17, $02, $17, $01, $0E, $02, $1A, $02, $1A, $01, $07, $02, $13, $02, $13, $01, $09, $02
	.byte $15, $02, $15, $01

; Bank 6
ft_s18p4c0:
	.byte $EF, $21, $03, $80, $20, $21, $03, $7F, $01, $EF, $31, $00, $7F, $06, $EC, $FF, $15, $00, $7F, $01
	.byte $15, $00, $7F, $01, $82, $00, $18, $7F, $1A, $7F, $13, $7F, $18, $83, $7F, $00

; Bank 6
ft_s18p4c1:
	.byte $00, $09, $EF, $2D, $00, $7F, $14

; Bank 6
ft_s18p5c0:
	.byte $EF, $21, $03, $80, $20, $21, $03, $7F, $01, $EF, $31, $00, $7F, $04, $EC, $FF, $1D, $00, $7F, $01
	.byte $1D, $00, $7F, $01, $1D, $00, $7F, $00, $1F, $00, $7F, $02, $1F, $00, $7F, $02

; Bank 6
ft_s18p16c0:
	.byte $E2, $39, $02, $34, $02, $39, $01, $37, $02, $34, $02, $37, $01, $36, $02, $32, $02, $82, $01, $37
	.byte $36, $32, $34, $83, $2D, $01

; Bank 6
ft_s19_frames:
	.word ft_s19f0
	.word ft_s19f1
	.word ft_s19f2
	.word ft_s19f3
	.word ft_s19f4
	.word ft_s19f5
	.word ft_s19f6
	.word ft_s19f7
	.word ft_s19f8
	.word ft_s19f9
	.word ft_s19f10
	.word ft_s19f11
	.word ft_s19f12
	.word ft_s19f13
	.word ft_s19f14
ft_s19f0:
	.word ft_s19p0c0, ft_s19p1c1, ft_s19p0c0, ft_s19p0c0, ft_s19p1c4
	.byte $06, $06, $06, $06, $06
ft_s19f1:
	.word ft_s19p0c0, ft_s19p1c1, ft_s19p1c2, ft_s19p1c3, ft_s19p1c4
	.byte $06, $06, $06, $06, $06
ft_s19f2:
	.word ft_s19p1c0, ft_s19p1c1, ft_s19p4c2, ft_s19p4c3, ft_s19p1c4
	.byte $06, $06, $06, $06, $06
ft_s19f3:
	.word ft_s19p1c0, ft_s19p1c1, ft_s19p4c2, ft_s19p4c3, ft_s19p1c4
	.byte $06, $06, $06, $06, $06
ft_s19f4:
	.word ft_s19p2c0, ft_s19p2c1, ft_s19p4c2, ft_s19p4c3, ft_s19p2c4
	.byte $06, $06, $06, $06, $06
ft_s19f5:
	.word ft_s19p2c0, ft_s19p2c1, ft_s19p4c2, ft_s19p4c3, ft_s19p2c4
	.byte $06, $06, $06, $06, $06
ft_s19f6:
	.word ft_s19p5c0, ft_s19p3c1, ft_s19p3c2, ft_s19p3c3, ft_s19p0c0
	.byte $06, $06, $06, $06, $06
ft_s19f7:
	.word ft_s19p3c0, ft_s19p3c1, ft_s19p4c2, ft_s19p4c3, ft_s19p3c4
	.byte $06, $06, $06, $06, $06
ft_s19f8:
	.word ft_s19p4c0, ft_s19p4c1, ft_s19p4c2, ft_s19p4c3, ft_s19p4c4
	.byte $06, $06, $06, $06, $06
ft_s19f9:
	.word ft_s19p4c0, ft_s19p4c1, ft_s19p4c2, ft_s19p4c3, ft_s19p4c4
	.byte $06, $06, $06, $06, $06
ft_s19f10:
	.word ft_s19p1c0, ft_s19p1c1, ft_s19p4c2, ft_s19p4c3, ft_s19p1c4
	.byte $06, $06, $06, $06, $06
ft_s19f11:
	.word ft_s19p2c0, ft_s19p2c1, ft_s19p4c2, ft_s19p4c3, ft_s19p2c4
	.byte $06, $06, $06, $06, $06
ft_s19f12:
	.word ft_s19p2c0, ft_s19p2c1, ft_s19p4c2, ft_s19p4c3, ft_s19p2c4
	.byte $06, $06, $06, $06, $06
ft_s19f13:
	.word ft_s19p0c0, ft_s19p4c1, ft_s19p0c0, ft_s19p0c0, ft_s19p0c0
	.byte $06, $06, $06, $06, $06
ft_s19f14:
	.word ft_s19p0c0, ft_s19p0c0, ft_s19p0c0, ft_s19p0c0, ft_s19p0c0
	.byte $06, $06, $06, $06, $06
; Bank 6
ft_s19p0c0:
	.byte $7F, $2F

; Bank 6
ft_s19p1c0:
	.byte $82, $00, $E3, $12, $12, $12, $12, $12, $12, $12, $12, $12, $1E, $21, $23, $12, $12, $12, $12, $12
	.byte $12, $12, $12, $12, $21, $23, $1E, $12, $12, $12, $12, $12, $12, $12, $12, $12, $1E, $21, $23, $1E
	.byte $1E, $1C, $1C, $19, $19, $17, $15, $15, $14, $15, $83, $17, $00

; Bank 6
ft_s19p1c1:
	.byte $EC, $1E, $01, $7F, $10, $82, $00, $21, $7F, $2D, $2F, $2A, $83, $1E, $01, $7F, $10, $1E, $01, $7F
	.byte $02

; Bank 6
ft_s19p1c2:
	.byte $00, $1D, $82, $02, $EB, $27, $2E, $27, $30, $27, $83, $31, $02

; Bank 6
ft_s19p1c3:
	.byte $82, $02, $E7, $F1, $11, $E8, $F2, $11, $E7, $F3, $11, $E8, $F4, $11, $E7, $F5, $11, $E8, $F6, $11
	.byte $E7, $F7, $11, $E8, $F8, $11, $E7, $F9, $11, $E8, $FA, $11, $E7, $FB, $11, $E8, $FC, $11, $E7, $FD
	.byte $11, $E8, $FE, $11, $E7, $FF, $11, $83, $E8, $FF, $11, $02

; Bank 6
ft_s19p1c4:
	.byte $82, $00, $08, $08, $08, $08, $08, $08, $08, $08, $08, $14, $17, $19, $08, $08, $08, $08, $08, $08
	.byte $08, $08, $08, $17, $19, $14, $08, $08, $08, $08, $08, $08, $08, $08, $08, $14, $17, $19, $14, $14
	.byte $12, $12, $0F, $0F, $0D, $0B, $0B, $0A, $0B, $83, $0D, $00

; Bank 6
ft_s19p2c0:
	.byte $82, $00, $E4, $12, $12, $12, $12, $12, $12, $12, $12, $12, $12, $83, $12, $01, $82, $00, $12, $12
	.byte $12, $12, $12, $12, $12, $12, $12, $12, $83, $12, $01, $82, $00, $1A, $1A, $1A, $1A, $1A, $1A, $1A
	.byte $1A, $1A, $1A, $83, $1A, $01, $82, $00, $1C, $1C, $1C, $1C, $1C, $1C, $1C, $1C, $1C, $1C, $83, $1C
	.byte $01

; Bank 6
ft_s19p2c1:
	.byte $82, $00, $E6, $1E, $1E, $2A, $2F, $2D, $1E, $2A, $2C, $1E, $2A, $36, $2A, $1E, $1E, $2A, $2F, $2D
	.byte $1E, $2A, $2C, $1E, $2A, $28, $23, $1E, $1E, $2A, $2F, $2D, $1E, $2A, $2C, $1E, $2A, $28, $23, $23
	.byte $23, $23, $34, $2F, $23, $23, $36, $23, $2F, $2D, $83, $2C, $00

; Bank 6
ft_s19p2c4:
	.byte $82, $00, $08, $08, $08, $08, $08, $08, $08, $08, $83, $08, $03, $82, $00, $08, $08, $08, $08, $08
	.byte $08, $08, $08, $83, $08, $03, $82, $00, $10, $10, $10, $10, $10, $10, $10, $10, $83, $10, $03, $82
	.byte $00, $12, $12, $12, $12, $12, $12, $12, $12, $83, $12, $03

; Bank 6
ft_s19p3c0:
	.byte $E3, $FF, $12, $01, $12, $00, $12, $01, $12, $00, $12, $01, $82, $00, $21, $23, $23, $1E, $83, $12
	.byte $01, $12, $00, $12, $01, $12, $00, $12, $01, $82, $00, $15, $17, $17, $12, $83, $12, $01, $12, $00
	.byte $12, $01, $12, $00, $12, $01, $82, $00, $21, $23, $23, $1E, $83, $12, $01, $12, $00, $12, $01, $12
	.byte $00, $12, $01, $82, $00, $21, $23, $23, $83, $1E, $00

; Bank 6
ft_s19p3c1:
	.byte $82, $00, $E2, $2A, $2A, $2A, $2A, $2A, $36, $2A, $2A, $34, $2A, $2F, $31, $2A, $2A, $2A, $2A, $3B
	.byte $36, $38, $39, $34, $38, $2F, $31, $2A, $2A, $2A, $2A, $2A, $36, $2A, $2A, $34, $2A, $2F, $31, $2A
	.byte $2A, $2A, $2A, $3B, $36, $38, $39, $34, $38, $2F, $83, $31, $00

; Bank 6
ft_s19p3c2:
	.byte $EB, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F
	.byte $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F
	.byte $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F, $01, $27, $00, $7F
	.byte $01, $27, $00, $7F, $01

; Bank 6
ft_s19p3c3:
	.byte $82, $02, $E7, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $83, $11
	.byte $02

; Bank 6
ft_s19p3c4:
	.byte $08, $01, $08, $00, $08, $01, $08, $00, $08, $01, $82, $00, $17, $19, $19, $14, $83, $08, $01, $08
	.byte $00, $08, $01, $08, $00, $08, $01, $82, $00, $0B, $0D, $0D, $08, $83, $08, $01, $08, $00, $08, $01
	.byte $08, $00, $08, $01, $82, $00, $17, $19, $19, $14, $83, $08, $01, $08, $00, $08, $01, $08, $00, $08
	.byte $01, $82, $00, $17, $19, $19, $83, $14, $00

; Bank 6
ft_s19p4c0:
	.byte $E3, $12, $01, $12, $00, $12, $01, $12, $00, $12, $01, $82, $00, $21, $23, $23, $1E, $83, $12, $01
	.byte $12, $00, $12, $01, $12, $00, $12, $01, $82, $00, $15, $17, $17, $12, $83, $0E, $01, $0E, $00, $0E
	.byte $01, $0E, $00, $0E, $01, $82, $00, $21, $23, $23, $1E, $83, $10, $01, $10, $00, $10, $01, $10, $00
	.byte $10, $01, $82, $00, $21, $23, $17, $83, $1E, $00

; Bank 6
ft_s19p4c1:
	.byte $82, $00, $E6, $36, $31, $2A, $36, $31, $2A, $39, $31, $2A, $38, $31, $2A, $36, $31, $2A, $36, $31
	.byte $2A, $39, $31, $2A, $38, $31, $2A, $36, $31, $26, $36, $31, $26, $39, $31, $26, $38, $31, $26, $36
	.byte $2F, $28, $36, $2F, $28, $39, $2F, $28, $38, $2F, $83, $28, $00

; Bank 6
ft_s19p4c2:
	.byte $EB, $27, $00, $7F, $01, $31, $00, $7F, $01, $27, $00, $7F, $01, $31, $00, $7F, $01, $27, $00, $7F
	.byte $01, $31, $00, $7F, $01, $27, $00, $7F, $01, $31, $00, $7F, $01, $27, $00, $7F, $01, $31, $00, $7F
	.byte $01, $27, $00, $7F, $01, $31, $00, $7F, $01, $27, $00, $7F, $01, $31, $00, $7F, $01, $27, $00, $7F
	.byte $01, $31, $00, $7F, $01

; Bank 6
ft_s19p4c3:
	.byte $E7, $11, $01, $EA, $20, $00, $E8, $11, $01, $EA, $20, $00, $E7, $11, $01, $EA, $20, $00, $E8, $11
	.byte $01, $EA, $20, $00, $E7, $11, $01, $EA, $20, $00, $E8, $11, $01, $EA, $20, $00, $E7, $11, $01, $EA
	.byte $20, $00, $E8, $11, $01, $EA, $20, $00, $E7, $11, $01, $EA, $20, $00, $E8, $11, $01, $EA, $20, $00
	.byte $E7, $11, $01, $EA, $20, $00, $E8, $11, $01, $EA, $20, $00, $E7, $11, $01, $EA, $20, $00, $E8, $11
	.byte $01, $EA, $20, $00, $E7, $11, $01, $EA, $20, $00, $E8, $11, $01, $EA, $20, $00

; Bank 6
ft_s19p4c4:
	.byte $08, $01, $08, $00, $08, $01, $08, $00, $08, $01, $82, $00, $17, $19, $19, $14, $83, $08, $01, $08
	.byte $00, $08, $01, $08, $00, $08, $01, $82, $00, $0B, $0D, $0D, $08, $83, $04, $01, $04, $00, $04, $01
	.byte $04, $00, $04, $01, $82, $00, $17, $19, $19, $14, $83, $06, $01, $06, $00, $06, $01, $06, $00, $06
	.byte $01, $82, $00, $17, $19, $0D, $83, $14, $00

; Bank 6
ft_s19p5c0:
	.byte $00, $01, $82, $00, $E2, $91, $7F, $F3, $2A, $2A, $2A, $2A, $2A, $36, $2A, $2A, $34, $2A, $2F, $31
	.byte $2A, $2A, $2A, $2A, $3B, $36, $38, $39, $34, $38, $2F, $31, $2A, $2A, $2A, $2A, $2A, $36, $2A, $2A
	.byte $34, $2A, $2F, $31, $2A, $2A, $2A, $2A, $3B, $36, $38, $39, $34, $83, $38, $00

; Bank 6
ft_s20_frames:
	.word ft_s20f0
	.word ft_s20f1
ft_s20f0:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s20p1c4
	.byte $03, $03, $03, $03, $06
ft_s20f1:
	.word ft_s20p2c0, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s20p2c4
	.byte $06, $03, $03, $03, $06
; Bank 6
ft_s20p1c4:
	.byte $07, $03, $82, $01, $13, $07, $11, $13, $07, $0E, $11, $05, $0E, $11, $07, $07, $11, $13, $03, $13
	.byte $0A, $03, $0A, $0F, $03, $0A, $11, $05, $0C, $11, $05, $0C, $11, $83, $13, $01

; Bank 6
ft_s20p2c0:
	.byte $00, $33, $82, $00, $E0, $8C, $7F, $54, $44, $3F, $3A, $7F, $36, $7F, $83, $35, $03, $7F, $00

; Bank 6
ft_s20p2c4:
	.byte $07, $03, $82, $01, $13, $07, $11, $13, $07, $0E, $13, $07, $0E, $13, $07, $07, $11, $13, $03, $0F
	.byte $0A, $03, $0A, $0F, $03, $0F, $83, $0E, $0F

; Bank 6
ft_s21_frames:
	.word ft_s21f0
	.word ft_s21f1
ft_s21f0:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s21p1c3, ft_s21p0c4
	.byte $03, $03, $03, $06, $06
ft_s21f1:
	.word ft_s21p1c0, ft_s21p1c1, ft_s0p0c2, ft_s21p2c3, ft_s21p0c4
	.byte $06, $06, $03, $06, $06
; Bank 6
ft_s21p0c4:
	.byte $00, $11, $97, $00, $1D, $01, $1D, $02, $1D, $01, $1D, $02, $97, $02, $1E, $01, $1E, $00, $97, $00
	.byte $00, $20

; Bank 6
ft_s21p1c0:
	.byte $80, $20, $F5, $2A, $02, $8C, $1F, $00, $00, $8A, $7F, $03, $2D, $01, $7F, $00, $2C, $01, $7F, $00
	.byte $28, $01, $2A, $01, $7F, $0D, $F5, $2A, $02, $8C, $1F, $00, $00, $8A, $7F, $03, $2D, $01, $7F, $00
	.byte $2F, $01, $7F, $00, $31, $01, $7F, $0F

; Bank 6
ft_s21p1c1:
	.byte $80, $20, $F5, $25, $02, $8C, $1F, $00, $00, $8A, $7F, $03, $28, $01, $7F, $00, $25, $01, $7F, $00
	.byte $23, $01, $25, $01, $7F, $0D, $F5, $25, $02, $8C, $1F, $00, $00, $8A, $7F, $03, $28, $01, $7F, $00
	.byte $28, $01, $7F, $00, $2A, $01, $7F, $0F

; Bank 6
ft_s21p1c3:
	.byte $E0, $84, $03, $12, $03, $13, $01, $14, $01, $82, $00, $15, $16, $17, $18, $19, $1A, $1B, $83, $87
	.byte $01, $1C, $30

; Bank 6
ft_s21p2c3:
	.byte $E7, $84, $06, $93, $00, $11, $02, $11, $00, $E8, $11, $01, $E7, $11, $01, $11, $02, $11, $00, $E8
	.byte $11, $01, $E7, $11, $01, $11, $01, $82, $00, $93, $01, $1A, $7F, $1A, $7F, $1A, $1A, $7F, $1A, $7F
	.byte $1A, $83, $8C, $01, $1A, $01, $8C, $01, $1A, $01, $8A, $93, $00, $11, $02, $11, $00, $E8, $11, $01
	.byte $E7, $11, $01, $11, $02, $11, $00, $E8, $11, $01, $E7, $11, $11

; Bank 7
ft_s22_frames:
	.word ft_s22f0
	.word ft_s22f1
	.word ft_s22f2
	.word ft_s22f3
	.word ft_s22f4
	.word ft_s22f5
	.word ft_s22f6
	.word ft_s22f7
	.word ft_s22f8
	.word ft_s22f9
	.word ft_s22f10
	.word ft_s22f11
	.word ft_s22f12
	.word ft_s22f13
	.word ft_s22f14
	.word ft_s22f15
	.word ft_s22f16
	.word ft_s22f17
	.word ft_s22f18
	.word ft_s22f19
	.word ft_s22f20
	.word ft_s22f21
	.word ft_s22f22
	.word ft_s22f23
	.word ft_s22f24
	.word ft_s22f25
	.word ft_s22f26
	.word ft_s22f27
	.word ft_s22f28
	.word ft_s22f29
	.word ft_s22f30
	.word ft_s22f31
	.word ft_s22f32
	.word ft_s22f33
	.word ft_s22f34
	.word ft_s22f35
	.word ft_s22f36
	.word ft_s22f37
	.word ft_s22f38
	.word ft_s22f39
	.word ft_s22f40
	.word ft_s22f41
	.word ft_s22f42
	.word ft_s22f43
	.word ft_s22f44
	.word ft_s22f45
	.word ft_s22f46
	.word ft_s22f47
	.word ft_s22f48
	.word ft_s22f49
	.word ft_s22f50
	.word ft_s22f51
	.word ft_s22f52
	.word ft_s22f53
	.word ft_s22f54
	.word ft_s22f55
	.word ft_s22f56
	.word ft_s22f57
	.word ft_s22f58
	.word ft_s22f59
	.word ft_s22f60
	.word ft_s22f61
	.word ft_s22f62
	.word ft_s22f63
	.word ft_s22f64
	.word ft_s22f65
	.word ft_s22f66
	.word ft_s22f67
	.word ft_s22f68
	.word ft_s22f69
	.word ft_s22f70
	.word ft_s22f71
	.word ft_s22f72
	.word ft_s22f73
	.word ft_s22f74
	.word ft_s22f75
	.word ft_s22f76
	.word ft_s22f77
	.word ft_s22f78
	.word ft_s22f79
	.word ft_s22f80
	.word ft_s22f81
	.word ft_s22f82
	.word ft_s22f83
	.word ft_s22f84
	.word ft_s22f85
	.word ft_s22f86
	.word ft_s22f87
	.word ft_s22f88
	.word ft_s22f89
	.word ft_s22f90
	.word ft_s22f91
	.word ft_s22f92
	.word ft_s22f93
	.word ft_s22f94
	.word ft_s22f95
	.word ft_s22f96
	.word ft_s22f97
	.word ft_s22f98
	.word ft_s22f99
	.word ft_s22f100
	.word ft_s22f101
	.word ft_s22f102
	.word ft_s22f103
	.word ft_s22f104
	.word ft_s22f105
	.word ft_s22f106
	.word ft_s22f107
	.word ft_s22f108
	.word ft_s22f109
	.word ft_s22f110
	.word ft_s22f111
	.word ft_s22f112
	.word ft_s22f113
	.word ft_s22f114
	.word ft_s22f115
	.word ft_s22f116
	.word ft_s22f117
	.word ft_s22f118
	.word ft_s22f119
	.word ft_s22f120
	.word ft_s22f121
	.word ft_s22f122
	.word ft_s22f123
	.word ft_s22f124
	.word ft_s22f125
	.word ft_s22f126
	.word ft_s22f127
	.word ft_s22f128
ft_s22f0:
	.word ft_s22p0c0, ft_s7p0c0, ft_s22p0c2, ft_s22p1c3, ft_s7p0c0
	.byte $07, $04, $07, $07, $04
ft_s22f1:
	.word ft_s22p0c0, ft_s22p1c1, ft_s22p0c2, ft_s22p1c3, ft_s7p0c0
	.byte $07, $07, $07, $07, $04
ft_s22f2:
	.word ft_s22p2c0, ft_s7p0c0, ft_s22p0c2, ft_s22p1c3, ft_s22p1c4
	.byte $07, $04, $07, $07, $07
ft_s22f3:
	.word ft_s22p3c0, ft_s22p3c1, ft_s22p0c2, ft_s22p1c3, ft_s22p1c4
	.byte $07, $07, $07, $07, $07
ft_s22f4:
	.word ft_s22p4c0, ft_s22p4c1, ft_s22p0c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $07, $07, $07, $07
ft_s22f5:
	.word ft_s22p5c0, ft_s22p5c1, ft_s22p0c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $07, $07, $07, $07
ft_s22f6:
	.word ft_s22p6c0, ft_s22p6c1, ft_s22p0c2, ft_s22p1c3, ft_s22p2c4
	.byte $07, $07, $07, $07, $07
ft_s22f7:
	.word ft_s22p7c0, ft_s22p7c1, ft_s22p0c2, ft_s22p1c3, ft_s22p3c4
	.byte $07, $07, $07, $07, $07
ft_s22f8:
	.word ft_s22p0c0, ft_s22p8c1, ft_s22p0c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $07, $07, $07, $07
ft_s22f9:
	.word ft_s22p0c0, ft_s7p0c0, ft_s22p0c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $04, $07, $07, $07
ft_s22f10:
	.word ft_s22p2c0, ft_s7p0c0, ft_s22p0c2, ft_s22p1c3, ft_s22p5c4
	.byte $07, $04, $07, $07, $07
ft_s22f11:
	.word ft_s22p3c0, ft_s22p11c1, ft_s22p0c2, ft_s22p1c3, ft_s22p3c4
	.byte $07, $07, $07, $07, $07
ft_s22f12:
	.word ft_s22p4c0, ft_s22p12c1, ft_s22p0c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $07, $07, $07, $07
ft_s22f13:
	.word ft_s22p5c0, ft_s22p13c1, ft_s22p0c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $07, $07, $07, $07
ft_s22f14:
	.word ft_s22p6c0, ft_s22p14c1, ft_s22p0c2, ft_s22p1c3, ft_s22p2c4
	.byte $07, $07, $07, $07, $07
ft_s22f15:
	.word ft_s22p7c0, ft_s22p15c1, ft_s22p0c2, ft_s22p2c3, ft_s22p6c4
	.byte $07, $07, $07, $07, $07
ft_s22f16:
	.word ft_s22p0c0, ft_s22p16c1, ft_s22p1c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f17:
	.word ft_s22p9c0, ft_s22p17c1, ft_s22p2c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f18:
	.word ft_s22p10c0, ft_s22p8c1, ft_s22p3c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f19:
	.word ft_s22p11c0, ft_s22p19c1, ft_s22p4c2, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f20:
	.word ft_s22p4c0, ft_s22p12c1, ft_s22p5c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f21:
	.word ft_s22p13c0, ft_s22p21c1, ft_s22p6c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f22:
	.word ft_s22p14c0, ft_s22p22c1, ft_s22p7c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f23:
	.word ft_s22p15c0, ft_s22p23c1, ft_s22p8c2, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f24:
	.word ft_s22p0c0, ft_s22p16c1, ft_s22p9c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f25:
	.word ft_s22p9c0, ft_s22p17c1, ft_s22p10c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f26:
	.word ft_s22p10c0, ft_s22p8c1, ft_s22p11c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f27:
	.word ft_s22p11c0, ft_s22p19c1, ft_s22p12c2, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f28:
	.word ft_s22p4c0, ft_s22p12c1, ft_s22p13c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f29:
	.word ft_s22p13c0, ft_s22p21c1, ft_s22p14c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f30:
	.word ft_s22p14c0, ft_s22p22c1, ft_s22p15c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f31:
	.word ft_s22p15c0, ft_s22p23c1, ft_s22p16c2, ft_s22p2c3, ft_s22p6c4
	.byte $07, $07, $07, $07, $07
ft_s22f32:
	.word ft_s22p0c0, ft_s22p24c1, ft_s22p0c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f33:
	.word ft_s22p9c0, ft_s22p25c1, ft_s22p9c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f34:
	.word ft_s22p10c0, ft_s22p26c1, ft_s22p10c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f35:
	.word ft_s22p11c0, ft_s22p27c1, ft_s22p11c0, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f36:
	.word ft_s22p4c0, ft_s22p24c1, ft_s22p4c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f37:
	.word ft_s22p13c0, ft_s22p28c1, ft_s22p13c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f38:
	.word ft_s22p14c0, ft_s22p29c1, ft_s22p14c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f39:
	.word ft_s22p15c0, ft_s22p30c1, ft_s22p15c0, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f40:
	.word ft_s22p0c0, ft_s22p31c1, ft_s22p0c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $08, $07, $07, $07
ft_s22f41:
	.word ft_s22p9c0, ft_s22p25c1, ft_s22p9c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f42:
	.word ft_s22p10c0, ft_s22p33c1, ft_s22p10c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $08, $07, $07, $07
ft_s22f43:
	.word ft_s22p11c0, ft_s22p34c1, ft_s22p11c0, ft_s22p3c3, ft_s22p10c4
	.byte $07, $08, $07, $07, $07
ft_s22f44:
	.word ft_s22p4c0, ft_s22p35c1, ft_s22p4c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $08, $07, $07, $07
ft_s22f45:
	.word ft_s22p13c0, ft_s22p28c1, ft_s22p13c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f46:
	.word ft_s22p14c0, ft_s22p37c1, ft_s22p14c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $08, $07, $07, $07
ft_s22f47:
	.word ft_s22p15c0, ft_s22p30c1, ft_s22p15c0, ft_s22p2c3, ft_s22p6c4
	.byte $07, $07, $07, $07, $07
ft_s22f48:
	.word ft_s22p16c0, ft_s22p39c1, ft_s7p0c0, ft_s22p1c3, ft_s22p11c4
	.byte $07, $08, $04, $07, $07
ft_s22f49:
	.word ft_s22p17c0, ft_s22p40c1, ft_s22p26c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $08, $07, $07, $07
ft_s22f50:
	.word ft_s22p18c0, ft_s22p41c1, ft_s22p27c2, ft_s22p1c3, ft_s22p11c4
	.byte $07, $08, $07, $07, $07
ft_s22f51:
	.word ft_s22p19c0, ft_s22p42c1, ft_s22p28c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $08, $07, $07, $07
ft_s22f52:
	.word ft_s22p18c0, ft_s22p41c1, ft_s22p27c2, ft_s22p1c3, ft_s22p11c4
	.byte $07, $08, $07, $07, $07
ft_s22f53:
	.word ft_s22p19c0, ft_s22p42c1, ft_s22p28c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $08, $07, $07, $07
ft_s22f54:
	.word ft_s22p20c0, ft_s22p41c1, ft_s22p29c2, ft_s22p1c3, ft_s22p11c4
	.byte $07, $08, $07, $07, $07
ft_s22f55:
	.word ft_s22p21c0, ft_s22p44c1, ft_s22p30c2, ft_s22p1c3, ft_s22p13c4
	.byte $07, $08, $07, $07, $07
ft_s22f56:
	.word ft_s22p22c0, ft_s22p45c1, ft_s22p31c2, ft_s22p1c3, ft_s22p13c4
	.byte $07, $08, $08, $07, $07
ft_s22f57:
	.word ft_s22p23c0, ft_s22p46c1, ft_s22p32c2, ft_s22p1c3, ft_s22p5c4
	.byte $07, $08, $08, $07, $07
ft_s22f58:
	.word ft_s22p22c0, ft_s22p45c1, ft_s22p31c2, ft_s22p1c3, ft_s22p13c4
	.byte $07, $08, $08, $07, $07
ft_s22f59:
	.word ft_s22p23c0, ft_s22p46c1, ft_s22p32c2, ft_s22p1c3, ft_s22p5c4
	.byte $07, $08, $08, $07, $07
ft_s22f60:
	.word ft_s22p22c0, ft_s22p45c1, ft_s22p31c2, ft_s22p1c3, ft_s22p13c4
	.byte $07, $08, $08, $07, $07
ft_s22f61:
	.word ft_s22p23c0, ft_s22p46c1, ft_s22p32c2, ft_s22p1c3, ft_s22p5c4
	.byte $07, $08, $08, $07, $07
ft_s22f62:
	.word ft_s22p24c0, ft_s22p47c1, ft_s22p31c2, ft_s22p1c3, ft_s22p13c4
	.byte $07, $08, $08, $07, $07
ft_s22f63:
	.word ft_s22p25c0, ft_s22p48c1, ft_s22p34c2, ft_s22p5c3, ft_s22p15c4
	.byte $07, $08, $08, $07, $07
ft_s22f64:
	.word ft_s22p26c0, ft_s22p49c1, ft_s22p35c2, ft_s22p3c3, ft_s22p16c4
	.byte $07, $08, $08, $07, $07
ft_s22f65:
	.word ft_s22p27c0, ft_s22p50c1, ft_s22p36c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $08, $08, $07, $07
ft_s22f66:
	.word ft_s22p26c0, ft_s22p51c1, ft_s22p35c2, ft_s22p3c3, ft_s22p16c4
	.byte $07, $08, $08, $07, $07
ft_s22f67:
	.word ft_s22p27c0, ft_s22p50c1, ft_s22p36c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $08, $08, $07, $07
ft_s22f68:
	.word ft_s22p26c0, ft_s22p52c1, ft_s22p35c2, ft_s22p3c3, ft_s22p16c4
	.byte $07, $08, $08, $07, $07
ft_s22f69:
	.word ft_s22p27c0, ft_s22p53c1, ft_s22p36c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $08, $08, $07, $07
ft_s22f70:
	.word ft_s22p28c0, ft_s22p54c1, ft_s22p37c2, ft_s22p3c3, ft_s22p16c4
	.byte $07, $08, $08, $07, $07
ft_s22f71:
	.word ft_s22p30c0, ft_s22p55c1, ft_s22p38c2, ft_s22p3c3, ft_s22p18c4
	.byte $07, $08, $08, $07, $07
ft_s22f72:
	.word ft_s22p31c0, ft_s22p56c1, ft_s22p39c2, ft_s22p3c3, ft_s22p19c4
	.byte $07, $08, $08, $07, $07
ft_s22f73:
	.word ft_s22p32c0, ft_s22p57c1, ft_s22p40c2, ft_s22p3c3, ft_s22p20c4
	.byte $08, $08, $08, $07, $07
ft_s22f74:
	.word ft_s22p31c0, ft_s22p58c1, ft_s22p39c2, ft_s22p3c3, ft_s22p19c4
	.byte $07, $08, $08, $07, $07
ft_s22f75:
	.word ft_s22p32c0, ft_s22p59c1, ft_s22p40c2, ft_s22p3c3, ft_s22p20c4
	.byte $08, $08, $08, $07, $07
ft_s22f76:
	.word ft_s22p31c0, ft_s22p60c1, ft_s22p39c2, ft_s22p3c3, ft_s22p19c4
	.byte $07, $08, $08, $07, $07
ft_s22f77:
	.word ft_s22p32c0, ft_s22p61c1, ft_s22p40c2, ft_s22p3c3, ft_s22p20c4
	.byte $08, $08, $08, $07, $07
ft_s22f78:
	.word ft_s22p33c0, ft_s22p62c1, ft_s22p39c2, ft_s22p3c3, ft_s22p19c4
	.byte $08, $08, $08, $07, $07
ft_s22f79:
	.word ft_s7p0c0, ft_s22p63c1, ft_s7p0c0, ft_s22p2c3, ft_s22p21c4
	.byte $04, $08, $04, $07, $07
ft_s22f80:
	.word ft_s22p0c0, ft_s22p16c1, ft_s22p1c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f81:
	.word ft_s22p9c0, ft_s22p17c1, ft_s22p2c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f82:
	.word ft_s22p10c0, ft_s22p8c1, ft_s22p3c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f83:
	.word ft_s22p11c0, ft_s22p19c1, ft_s22p4c2, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f84:
	.word ft_s22p4c0, ft_s22p12c1, ft_s22p5c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f85:
	.word ft_s22p13c0, ft_s22p21c1, ft_s22p6c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f86:
	.word ft_s22p14c0, ft_s22p22c1, ft_s22p7c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f87:
	.word ft_s22p15c0, ft_s22p23c1, ft_s22p8c2, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f88:
	.word ft_s22p0c0, ft_s22p16c1, ft_s22p9c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f89:
	.word ft_s22p9c0, ft_s22p17c1, ft_s22p10c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f90:
	.word ft_s22p10c0, ft_s22p8c1, ft_s22p11c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f91:
	.word ft_s22p11c0, ft_s22p19c1, ft_s22p12c2, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f92:
	.word ft_s22p4c0, ft_s22p12c1, ft_s22p13c2, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f93:
	.word ft_s22p13c0, ft_s22p21c1, ft_s22p14c2, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f94:
	.word ft_s22p14c0, ft_s22p22c1, ft_s22p15c2, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f95:
	.word ft_s22p15c0, ft_s22p23c1, ft_s22p16c2, ft_s22p2c3, ft_s22p6c4
	.byte $07, $07, $07, $07, $07
ft_s22f96:
	.word ft_s22p0c0, ft_s22p24c1, ft_s22p0c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f97:
	.word ft_s22p9c0, ft_s22p25c1, ft_s22p9c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f98:
	.word ft_s22p10c0, ft_s22p26c1, ft_s22p10c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f99:
	.word ft_s22p11c0, ft_s22p27c1, ft_s22p11c0, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f100:
	.word ft_s22p4c0, ft_s22p24c1, ft_s22p4c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $07, $07, $07, $07
ft_s22f101:
	.word ft_s22p13c0, ft_s22p28c1, ft_s22p13c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f102:
	.word ft_s22p14c0, ft_s22p29c1, ft_s22p14c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $07, $07, $07, $07
ft_s22f103:
	.word ft_s22p15c0, ft_s22p30c1, ft_s22p15c0, ft_s22p3c3, ft_s22p10c4
	.byte $07, $07, $07, $07, $07
ft_s22f104:
	.word ft_s22p0c0, ft_s22p31c1, ft_s22p0c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $08, $07, $07, $07
ft_s22f105:
	.word ft_s22p9c0, ft_s22p25c1, ft_s22p9c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f106:
	.word ft_s22p10c0, ft_s22p33c1, ft_s22p10c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $08, $07, $07, $07
ft_s22f107:
	.word ft_s22p11c0, ft_s22p34c1, ft_s22p11c0, ft_s22p3c3, ft_s22p10c4
	.byte $07, $08, $07, $07, $07
ft_s22f108:
	.word ft_s22p4c0, ft_s22p35c1, ft_s22p4c0, ft_s22p3c3, ft_s22p7c4
	.byte $07, $08, $07, $07, $07
ft_s22f109:
	.word ft_s22p13c0, ft_s22p28c1, ft_s22p13c0, ft_s22p3c3, ft_s22p8c4
	.byte $07, $07, $07, $07, $07
ft_s22f110:
	.word ft_s22p14c0, ft_s22p37c1, ft_s22p14c0, ft_s22p3c3, ft_s22p9c4
	.byte $07, $08, $07, $07, $07
ft_s22f111:
	.word ft_s22p15c0, ft_s22p30c1, ft_s22p15c0, ft_s22p2c3, ft_s22p6c4
	.byte $07, $07, $07, $07, $07
ft_s22f112:
	.word ft_s22p16c0, ft_s22p39c1, ft_s7p0c0, ft_s22p1c3, ft_s22p11c4
	.byte $07, $08, $04, $07, $07
ft_s22f113:
	.word ft_s22p17c0, ft_s22p40c1, ft_s22p26c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $08, $07, $07, $07
ft_s22f114:
	.word ft_s22p18c0, ft_s22p41c1, ft_s22p27c2, ft_s22p1c3, ft_s22p11c4
	.byte $07, $08, $07, $07, $07
ft_s22f115:
	.word ft_s22p19c0, ft_s22p42c1, ft_s22p28c2, ft_s22p1c3, ft_s22p4c4
	.byte $07, $08, $07, $07, $07
ft_s22f116:
	.word ft_s22p18c0, ft_s22p41c1, ft_s22p27c2, ft_s7p0c0, ft_s22p11c4
	.byte $07, $08, $07, $04, $07
ft_s22f117:
	.word ft_s22p19c0, ft_s22p42c1, ft_s22p28c2, ft_s7p0c0, ft_s22p4c4
	.byte $07, $08, $07, $04, $07
ft_s22f118:
	.word ft_s22p20c0, ft_s22p41c1, ft_s22p29c2, ft_s7p0c0, ft_s22p11c4
	.byte $07, $08, $07, $04, $07
ft_s22f119:
	.word ft_s22p21c0, ft_s22p44c1, ft_s22p30c2, ft_s7p0c0, ft_s22p13c4
	.byte $07, $08, $07, $04, $07
ft_s22f120:
	.word ft_s22p22c0, ft_s22p45c1, ft_s22p31c2, ft_s7p0c0, ft_s22p13c4
	.byte $07, $08, $08, $04, $07
ft_s22f121:
	.word ft_s22p23c0, ft_s22p46c1, ft_s22p32c2, ft_s7p0c0, ft_s22p5c4
	.byte $07, $08, $08, $04, $07
ft_s22f122:
	.word ft_s22p22c0, ft_s22p45c1, ft_s22p31c2, ft_s7p0c0, ft_s22p13c4
	.byte $07, $08, $08, $04, $07
ft_s22f123:
	.word ft_s22p23c0, ft_s22p46c1, ft_s22p32c2, ft_s7p0c0, ft_s22p5c4
	.byte $07, $08, $08, $04, $07
ft_s22f124:
	.word ft_s22p22c0, ft_s22p45c1, ft_s22p31c2, ft_s7p0c0, ft_s22p13c4
	.byte $07, $08, $08, $04, $07
ft_s22f125:
	.word ft_s22p23c0, ft_s22p46c1, ft_s22p32c2, ft_s7p0c0, ft_s22p5c4
	.byte $07, $08, $08, $04, $07
ft_s22f126:
	.word ft_s22p24c0, ft_s22p47c1, ft_s22p31c2, ft_s7p0c0, ft_s22p13c4
	.byte $07, $08, $08, $04, $07
ft_s22f127:
	.word ft_s22p34c0, ft_s22p64c1, ft_s22p34c2, ft_s7p0c0, ft_s22p15c4
	.byte $08, $08, $08, $04, $07
ft_s22f128:
	.word ft_s7p0c0, ft_s22p65c1, ft_s7p0c0, ft_s7p0c0, ft_s22p23c4
	.byte $04, $08, $04, $04, $07
; Bank 7
ft_s22p0c0:
	.byte $E2, $2F, $07, $36, $03, $34, $01, $36, $03, $32, $01, $36, $03, $31, $03, $32, $03

; Bank 7
ft_s22p0c2:
	.byte $7F, $1F

; Bank 7
ft_s22p1c1:
	.byte $00, $07, $E2, $32, $03, $31, $13

; Bank 7
ft_s22p1c2:
	.byte $82, $00, $E1, $3B, $7F, $3B, $7F, $83, $3D, $01, $7F, $01, $3D, $00, $3E, $02, $7F, $01, $3D, $00
	.byte $3E, $02, $7F, $01, $82, $00, $36, $7F, $36, $7F, $3D, $83, $3E, $01, $82, $00, $7F, $3E, $7F, $3E
	.byte $83, $7F, $00

; Bank 7
ft_s22p1c3:
	.byte $82, $07, $E7, $11, $11, $11, $83, $11, $07

; Bank 7
ft_s22p1c4:
	.byte $82, $07, $1D, $1D, $1D, $83, $1D, $07

; Bank 7
ft_s22p2c0:
	.byte $E2, $2D, $07, $36, $03, $34, $01, $36, $03, $32, $01, $36, $03, $31, $03, $32, $03

; Bank 7
ft_s22p2c2:
	.byte $E1, $3B, $00, $3D, $02, $82, $01, $7F, $3B, $7F, $37, $7F, $83, $36, $00, $7F, $00, $37, $03, $7F
	.byte $0B

; Bank 7
ft_s22p2c3:
	.byte $E7, $11, $0F, $11, $07, $E8, $11, $03, $11, $01, $11, $01

; Bank 7
ft_s22p2c4:
	.byte $82, $01, $1D, $10, $10, $10, $1D, $10, $10, $10, $1D, $10, $10, $10, $1D, $10, $10, $83, $10, $01

; Bank 7
ft_s22p3c0:
	.byte $E2, $2B, $07, $34, $03, $32, $01, $34, $03, $32, $01, $34, $03, $31, $03, $32, $03

; Bank 7
ft_s22p3c1:
	.byte $00, $03, $E2, $31, $0B, $2A, $0F

; Bank 7
ft_s22p3c2:
	.byte $00, $03, $E1, $3B, $03, $3B, $00, $3D, $02, $7F, $01, $3B, $00, $3D, $02, $7F, $01, $82, $00, $34
	.byte $7F, $34, $7F, $38, $3B, $83, $7F, $01, $82, $00, $3D, $7F, $3D, $83, $7F, $00

; Bank 7
ft_s22p3c3:
	.byte $82, $01, $E7, $11, $E9, $1F, $EA, $1C, $E9, $1F, $E8, $11, $E9, $1F, $EA, $1C, $E9, $1F, $E7, $11
	.byte $E9, $1F, $EA, $1C, $E9, $1F, $E8, $11, $E9, $1F, $EA, $1C, $83, $E9, $1F, $01

; Bank 7
ft_s22p3c4:
	.byte $82, $01, $1D, $09, $09, $09, $1D, $09, $09, $09, $1D, $08, $08, $08, $1D, $08, $08, $83, $08, $01

; Bank 7
ft_s22p4c0:
	.byte $E2, $2F, $07, $3B, $03, $39, $01, $3B, $03, $36, $01, $3B, $03, $34, $03, $36, $03

; Bank 7
ft_s22p4c1:
	.byte $00, $07, $E2, $32, $03, $31, $01, $31, $05, $32, $0B

; Bank 7
ft_s22p4c2:
	.byte $E1, $3A, $00, $3B, $02, $82, $01, $7F, $3A, $7F, $36, $7F, $83, $34, $00, $7F, $00, $36, $01, $7F
	.byte $01, $82, $00, $36, $7F, $36, $7F, $83, $3B, $01, $7F, $01, $3D, $00, $7F, $00, $3E, $01

; Bank 7
ft_s22p4c4:
	.byte $82, $01, $1D, $0D, $0D, $0D, $1D, $0D, $0D, $0D, $1D, $0D, $0D, $0D, $1D, $0D, $0D, $83, $0D, $01

; Bank 7
ft_s22p5c0:
	.byte $E2, $2F, $07, $3E, $03, $3D, $01, $3E, $03, $3B, $01, $3E, $03, $39, $03, $3B, $03

; Bank 7
ft_s22p5c1:
	.byte $00, $03, $82, $03, $E2, $34, $36, $2F, $34, $83, $36, $0B

; Bank 7
ft_s22p5c2:
	.byte $7F, $03, $E1, $40, $01, $7F, $01, $40, $00, $42, $02, $7F, $01, $40, $00, $42, $02, $7F, $01, $82
	.byte $00, $3B, $7F, $3B, $7F, $40, $83, $42, $01, $82, $00, $7F, $45, $7F, $45, $83, $7F, $00

; Bank 7
ft_s22p5c3:
	.byte $E7, $11, $07, $11, $07, $11, $07, $E8, $11, $03, $11, $03

; Bank 7
ft_s22p5c4:
	.byte $82, $01, $1D, $0B, $0B, $0B, $1D, $0B, $0B, $0B, $1D, $0B, $0B, $0B, $1D, $0B, $0B, $83, $0B, $01

; Bank 7
ft_s22p6c0:
	.byte $E2, $32, $07, $3E, $03, $3D, $01, $3E, $03, $32, $01, $3E, $03, $31, $03, $2D, $03

; Bank 7
ft_s22p6c1:
	.byte $00, $0D, $E2, $39, $11

; Bank 7
ft_s22p6c2:
	.byte $E1, $43, $00, $45, $02, $7F, $01, $43, $01, $7F, $05, $42, $01, $43, $01, $7F, $0D

; Bank 7
ft_s22p6c4:
	.byte $1D, $0F, $82, $01, $1D, $08, $08, $08, $1E, $08, $1E, $83, $1E, $01

; Bank 7
ft_s22p7c0:
	.byte $E2, $2B, $07, $37, $03, $36, $01, $37, $03, $36, $01, $37, $03, $34, $03, $36, $03

; Bank 7
ft_s22p7c1:
	.byte $00, $07, $E2, $2D, $03, $2B, $03, $2A, $0F

; Bank 7
ft_s22p7c2:
	.byte $82, $00, $E1, $3E, $7F, $3D, $7F, $82, $01, $3E, $7F, $40, $7F, $39, $7F, $83, $3F, $00, $40, $01
	.byte $82, $00, $7F, $39, $7F, $39, $7F, $3D, $83, $40, $01, $82, $00, $7F, $43, $7F, $43, $83, $7F, $00

; Bank 7
ft_s22p7c4:
	.byte $82, $01, $1D, $0D, $0D, $0D, $1E, $0D, $0D, $0D, $1D, $0D, $0D, $0D, $1E, $0D, $0D, $83, $0D, $01

; Bank 7
ft_s22p8c1:
	.byte $00, $17, $E2, $28, $03, $2A, $03

; Bank 7
ft_s22p8c2:
	.byte $E1, $40, $00, $43, $02, $7F, $01, $42, $01, $7F, $05, $40, $01, $7F, $03, $82, $00, $3A, $7F, $3A
	.byte $7F, $3D, $83, $3E, $01, $82, $00, $7F, $3D, $7F, $3B, $83, $7F, $00

; Bank 7
ft_s22p8c4:
	.byte $82, $01, $1D, $09, $09, $09, $1E, $09, $09, $09, $1D, $09, $09, $09, $1E, $09, $09, $83, $09, $01

; Bank 7
ft_s22p9c0:
	.byte $E2, $2B, $07, $37, $03, $36, $01, $37, $03, $32, $01, $37, $03, $31, $03, $32, $03

; Bank 7
ft_s22p9c2:
	.byte $00, $03, $E1, $49, $01, $7F, $01, $49, $00, $4A, $02, $7F, $01, $49, $00, $4A, $02, $7F, $01, $82
	.byte $00, $42, $7F, $42, $7F, $49, $83, $4A, $01, $82, $00, $7F, $4A, $7F, $4A, $83, $7F, $00

; Bank 7
ft_s22p9c4:
	.byte $82, $01, $1D, $0B, $0B, $0B, $1E, $0B, $0B, $0B, $1D, $0B, $0B, $0B, $1E, $0B, $0B, $83, $0B, $01

; Bank 7
ft_s22p10c0:
	.byte $E2, $2D, $07, $34, $03, $32, $01, $34, $03, $32, $01, $34, $03, $2F, $03, $31, $03

; Bank 7
ft_s22p10c2:
	.byte $E1, $47, $00, $49, $02, $82, $01, $7F, $47, $7F, $43, $7F, $83, $42, $00, $7F, $00, $43, $03, $7F
	.byte $0B

; Bank 7
ft_s22p10c4:
	.byte $82, $01, $1D, $08, $08, $08, $1E, $08, $08, $08, $1D, $08, $08, $08, $1E, $08, $08, $83, $08, $01

; Bank 7
ft_s22p11c0:
	.byte $E2, $2A, $07, $34, $03, $32, $01, $34, $03, $32, $01, $34, $03, $31, $03, $32, $03

; Bank 7
ft_s22p11c1:
	.byte $00, $07, $E2, $2B, $03, $2A, $01, $2B, $03, $2A, $01, $2B, $03, $28, $03, $2A, $03

; Bank 7
ft_s22p11c2:
	.byte $00, $03, $E1, $47, $03, $47, $00, $49, $02, $7F, $01, $47, $00, $49, $02, $7F, $01, $82, $00, $40
	.byte $7F, $40, $7F, $44, $47, $83, $7F, $01, $82, $00, $49, $7F, $49, $83, $7F, $00

; Bank 7
ft_s22p11c4:
	.byte $82, $01, $1D, $09, $09, $09, $1D, $09, $09, $09, $1D, $0B, $0B, $0B, $1D, $0B, $0B, $83, $0B, $01

; Bank 7
ft_s22p12c1:
	.byte $E2, $2A, $07, $32, $03, $31, $01, $32, $03, $2F, $05, $2F, $03, $2F, $03

; Bank 7
ft_s22p12c2:
	.byte $E1, $46, $00, $47, $02, $82, $01, $7F, $46, $7F, $42, $7F, $83, $40, $00, $7F, $00, $42, $01, $7F
	.byte $01, $82, $00, $42, $7F, $42, $7F, $83, $47, $01, $7F, $01, $49, $00, $7F, $00, $4A, $01

; Bank 7
ft_s22p13c0:
	.byte $E2, $2B, $07, $3E, $03, $3D, $01, $3E, $03, $3B, $01, $3E, $03, $39, $03, $3B, $03

; Bank 7
ft_s22p13c1:
	.byte $00, $07, $E2, $36, $03, $34, $01, $36, $03, $34, $05, $31, $03, $32, $03

; Bank 7
ft_s22p13c2:
	.byte $7F, $03, $E1, $4C, $01, $7F, $01, $4C, $00, $4E, $02, $7F, $01, $4C, $00, $4E, $02, $7F, $01, $82
	.byte $00, $47, $7F, $47, $7F, $4C, $83, $4E, $01, $82, $00, $7F, $51, $7F, $51, $83, $7F, $00

; Bank 7
ft_s22p13c4:
	.byte $82, $01, $1D, $07, $07, $07, $1D, $07, $07, $07, $1D, $09, $09, $09, $1D, $09, $09, $83, $09, $01

; Bank 7
ft_s22p14c0:
	.byte $E2, $2D, $07, $3D, $03, $3B, $01, $3D, $03, $39, $01, $3D, $03, $32, $03, $34, $03

; Bank 7
ft_s22p14c1:
	.byte $00, $0D, $E2, $39, $05, $39, $03, $2D, $03, $28, $03

; Bank 7
ft_s22p14c2:
	.byte $E1, $4F, $00, $51, $02, $7F, $01, $4F, $01, $7F, $05, $4E, $01, $4F, $01, $7F, $0D

; Bank 7
ft_s22p15c0:
	.byte $E2, $36, $07, $36, $03, $36, $01, $3A, $03, $36, $01, $3A, $03, $34, $03, $36, $03

; Bank 7
ft_s22p15c1:
	.byte $00, $11, $E2, $31, $05, $31, $03, $31, $03

; Bank 7
ft_s22p15c2:
	.byte $82, $00, $E1, $4A, $7F, $49, $7F, $82, $01, $4A, $7F, $4C, $7F, $45, $7F, $83, $4B, $00, $4C, $01
	.byte $82, $00, $7F, $45, $7F, $45, $7F, $49, $83, $4C, $01, $82, $00, $7F, $4F, $7F, $4F, $83, $7F, $00

; Bank 7
ft_s22p15c4:
	.byte $82, $01, $1D, $0A, $0A, $0A, $1D, $0A, $0A, $0A, $1D, $0C, $0C, $0C, $1E, $0C, $1E, $83, $0C, $01

; Bank 7
ft_s22p16c0:
	.byte $E2, $13, $01, $1A, $01, $26, $01, $23, $0B, $21, $01, $25, $01, $28, $09

; Bank 7
ft_s22p16c1:
	.byte $7F, $17, $E2, $28, $03, $2A, $03

; Bank 7
ft_s22p16c2:
	.byte $E1, $4C, $00, $4F, $02, $7F, $01, $4E, $01, $7F, $05, $4C, $01, $7F, $03, $82, $00, $46, $7F, $46
	.byte $7F, $49, $83, $4A, $01, $82, $00, $7F, $49, $7F, $47, $83, $7F, $00

; Bank 7
ft_s22p16c4:
	.byte $82, $01, $1D, $05, $05, $05, $1E, $05, $05, $05, $1D, $07, $07, $07, $1E, $07, $07, $83, $07, $01

; Bank 7
ft_s22p17c0:
	.byte $00, $01, $E2, $23, $01, $2A, $03, $2F, $01, $2A, $03, $2A, $11

; Bank 7
ft_s22p17c1:
	.byte $00, $17, $E2, $2B, $03, $2B, $03

; Bank 7
ft_s22p18c0:
	.byte $00, $01, $E2, $1F, $01, $26, $01, $2F, $09, $E3, $39, $01, $E2, $21, $01, $25, $01, $28, $05, $E3
	.byte $3D, $03

; Bank 7
ft_s22p18c4:
	.byte $82, $01, $1D, $08, $08, $08, $1E, $08, $08, $08, $1D, $0A, $0A, $0A, $1E, $0A, $0A, $83, $0A, $01

; Bank 7
ft_s22p19c0:
	.byte $82, $01, $E3, $3D, $E2, $23, $2A, $E3, $40, $83, $E2, $2F, $03, $E3, $3F, $13

; Bank 7
ft_s22p19c1:
	.byte $E2, $1E, $07, $2B, $03, $2A, $01, $2B, $03, $2A, $01, $2B, $03, $28, $03, $2A, $03

; Bank 7
ft_s22p19c4:
	.byte $82, $01, $1D, $03, $03, $03, $1E, $03, $03, $03, $1D, $05, $05, $05, $1E, $05, $05, $83, $05, $01

; Bank 7
ft_s22p20c0:
	.byte $00, $01, $E2, $1F, $01, $26, $01, $2F, $09, $E3, $39, $01, $E2, $21, $01, $25, $01, $28, $05, $E3
	.byte $39, $03

; Bank 7
ft_s22p20c4:
	.byte $82, $01, $1D, $07, $07, $07, $1E, $07, $07, $07, $1D, $07, $07, $07, $1E, $07, $07, $83, $07, $01

; Bank 7
ft_s22p21c0:
	.byte $00, $03, $E3, $3A, $0B, $E2, $30, $01, $24, $01, $28, $01, $2B, $05, $E3, $30, $03

; Bank 7
ft_s22p21c1:
	.byte $E2, $26, $07, $36, $03, $34, $01, $36, $03, $34, $05, $31, $03, $32, $03

; Bank 7
ft_s22p21c4:
	.byte $82, $01, $1D, $06, $06, $06, $7F, $06, $06, $06, $1D, $08, $08, $08, $1E, $08, $1E, $83, $1E, $01

; Bank 7
ft_s22p22c0:
	.byte $00, $01, $E2, $1D, $01, $24, $01, $2D, $09, $E3, $2B, $01, $E2, $1F, $01, $23, $01, $26, $05, $E3
	.byte $37, $03

; Bank 7
ft_s22p22c1:
	.byte $00, $17, $E2, $32, $03, $34, $03

; Bank 7
ft_s22p23c0:
	.byte $82, $01, $E3, $37, $E2, $21, $28, $E3, $39, $E2, $2D, $28, $E3, $31, $83, $E2, $28, $11

; Bank 7
ft_s22p23c1:
	.byte $00, $07, $E2, $2F, $03, $31, $01, $36, $03, $31, $01, $36, $03, $31, $03, $32, $03

; Bank 7
ft_s22p23c4:
	.byte $00, $06, $88, $00, $00, $18

; Bank 7
ft_s22p24c0:
	.byte $00, $01, $E2, $1D, $01, $24, $01, $2D, $09, $E3, $2B, $01, $E2, $1F, $01, $23, $01, $26, $05, $E3
	.byte $2B, $03

; Bank 7
ft_s22p24c1:
	.byte $E3, $3B, $0F, $36, $03, $36, $03, $82, $01, $34, $34, $39, $83, $3B, $01

; Bank 7
ft_s22p25c0:
	.byte $E2, $20, $01, $2C, $01, $33, $0B, $2E, $01, $22, $01, $26, $01, $29, $05, $E3, $2E, $03

; Bank 7
ft_s22p25c1:
	.byte $00, $01, $E3, $39, $01, $3B, $03, $39, $01, $3B, $07, $36, $01, $37, $03, $36, $01, $37, $05

; Bank 7
ft_s22p26c0:
	.byte $E2, $37, $01, $27, $01, $2E, $01, $37, $03, $82, $01, $2C, $2E, $2F, $35, $29, $2D, $83, $30, $05
	.byte $39, $03

; Bank 7
ft_s22p26c1:
	.byte $E3, $31, $07, $32, $03, $34, $01, $39, $05, $39, $05, $39, $05

; Bank 7
ft_s22p26c2:
	.byte $00, $01, $EE, $23, $01, $2A, $03, $2F, $01, $2A, $05, $2A, $0F

; Bank 7
ft_s22p27c0:
	.byte $82, $01, $E2, $39, $1F, $26, $3C, $2B, $26, $3B, $83, $26, $03, $82, $01, $E3, $2B, $2D, $2F, $32
	.byte $35, $37, $83, $3A, $01

; Bank 7
ft_s22p27c1:
	.byte $82, $01, $E3, $3D, $3D, $25, $36, $83, $39, $03, $82, $01, $34, $39, $1E, $3E, $83, $40, $03, $3E
	.byte $01, $40, $01, $36, $03

; Bank 7
ft_s22p27c2:
	.byte $00, $01, $EE, $1F, $01, $26, $01, $2B, $0B, $21, $01, $25, $01, $28, $05, $39, $03

; Bank 7
ft_s22p28c0:
	.byte $E2, $37, $01, $27, $01, $2E, $01, $37, $03, $82, $01, $2B, $2D, $2E, $35, $29, $2D, $83, $30, $05
	.byte $35, $03

; Bank 7
ft_s22p28c1:
	.byte $00, $01, $E3, $39, $01, $3B, $03, $82, $01, $39, $3B, $3E, $3E, $3E, $3E, $3E, $3E, $39, $39, $3B
	.byte $83, $3B, $01

; Bank 7
ft_s22p28c2:
	.byte $82, $01, $EE, $39, $23, $2A, $3B, $83, $2F, $17

; Bank 7
ft_s22p29c1:
	.byte $82, $01, $E3, $3B, $3B, $2D, $2D, $39, $2D, $34, $39, $2D, $34, $39, $2D, $39, $39, $34, $83, $39
	.byte $01

; Bank 7
ft_s22p29c2:
	.byte $00, $01, $EE, $1F, $01, $26, $01, $2B, $0B, $21, $01, $25, $01, $28, $09

; Bank 7
ft_s22p30c0:
	.byte $82, $01, $E2, $1E, $2A, $31, $E4, $36, $E2, $3A, $2E, $30, $31, $38, $31, $36, $38, $83, $38, $03
	.byte $38, $03

; Bank 7
ft_s22p30c1:
	.byte $00, $01, $82, $01, $E3, $36, $36, $36, $36, $83, $36, $05, $82, $01, $36, $36, $36, $36, $82, $00
	.byte $36, $36, $36, $36, $36, $36, $36, $83, $36, $00

; Bank 7
ft_s22p30c2:
	.byte $EE, $22, $01, $2E, $01, $35, $0B, $30, $01, $24, $01, $28, $01, $2B, $09

; Bank 7
ft_s22p31c0:
	.byte $E2, $35, $01, $25, $01, $2C, $01, $35, $03, $82, $01, $29, $2B, $2C, $33, $27, $2B, $83, $2E, $05
	.byte $37, $03

; Bank 8
ft_s22p31c1:
	.byte $82, $00, $E3, $2F, $2F, $2F, $2F, $2F, $2F, $2F, $83, $2F, $08, $82, $00, $36, $36, $36, $36, $36
	.byte $36, $36, $36, $34, $34, $34, $34, $39, $34, $3B, $83, $34, $00

; Bank 8
ft_s22p31c2:
	.byte $00, $01, $EE, $1D, $01, $24, $01, $2D, $0B, $1F, $01, $23, $01, $26, $09

; Bank 8
ft_s22p32c0:
	.byte $82, $01, $E2, $37, $29, $30, $3A, $35, $30, $39, $83, $30, $03, $82, $01, $E3, $29, $2B, $2D, $30
	.byte $33, $35, $83, $38, $01

; Bank 8
ft_s22p32c2:
	.byte $00, $01, $EE, $21, $01, $28, $03, $2D, $01, $28, $05, $28, $0F

; Bank 8
ft_s22p33c0:
	.byte $E2, $35, $01, $25, $01, $2C, $01, $35, $03, $82, $01, $29, $2B, $2C, $33, $27, $2B, $83, $2E, $05
	.byte $33, $03

; Bank 8
ft_s22p33c1:
	.byte $82, $00, $E3, $31, $31, $31, $31, $83, $2D, $01, $2D, $01, $82, $00, $32, $32, $32, $32, $34, $34
	.byte $34, $34, $34, $34, $34, $34, $83, $39, $05, $39, $05

; Bank 8
ft_s22p34c0:
	.byte $E2, $20, $01, $2C, $01, $33, $0B, $2E, $01, $22, $01, $26, $01, $29, $09

; Bank 8
ft_s22p34c1:
	.byte $82, $01, $E3, $3D, $3D, $25, $36, $83, $39, $03, $34, $01, $39, $01, $26, $01, $3E, $05, $3E, $03
	.byte $36, $00, $36, $00, $36, $01

; Bank 8
ft_s22p34c2:
	.byte $00, $0F, $EE, $2E, $01, $22, $01, $26, $01, $29, $09

; Bank 8
ft_s22p35c1:
	.byte $82, $00, $E3, $32, $32, $32, $32, $32, $32, $32, $32, $83, $42, $03, $82, $01, $42, $42, $2F, $2F
	.byte $2F, $2F, $2F, $2F, $39, $83, $3B, $01

; Bank 8
ft_s22p35c2:
	.byte $00, $01, $EE, $27, $01, $2E, $01, $37, $09, $35, $01, $29, $01, $2D, $01, $30, $05, $35, $03

; Bank 8
ft_s22p36c2:
	.byte $82, $01, $EE, $35, $1F, $26, $37, $2B, $83, $26, $05, $26, $0F

; Bank 8
ft_s22p37c1:
	.byte $82, $01, $E3, $3B, $3B, $2D, $2D, $39, $2D, $34, $39, $2D, $34, $39, $2D, $39, $39, $2D, $83, $39
	.byte $01

; Bank 8
ft_s22p37c2:
	.byte $00, $0F, $EE, $35, $0B, $35, $03

; Bank 8
ft_s22p38c2:
	.byte $00, $03, $EE, $36, $01, $2F, $11, $38, $03, $38, $03

; Bank 8
ft_s22p39c1:
	.byte $E3, $3D, $00, $3E, $02, $3B, $0B, $3B, $03, $82, $00, $31, $31, $31, $31, $31, $31, $83, $31, $05

; Bank 8
ft_s22p39c2:
	.byte $00, $01, $EE, $25, $01, $2C, $01, $31, $09, $33, $0B, $33, $03

; Bank 8
ft_s22p40c1:
	.byte $82, $00, $E3, $33, $33, $33, $33, $33, $33, $33, $33, $3F, $3F, $3F, $3F, $83, $3F, $05, $82, $01
	.byte $2F, $31, $33, $36, $39, $3B, $83, $3E, $01

; Bank 8
ft_s22p40c2:
	.byte $82, $01, $EE, $3F, $29, $30, $41, $35, $30, $83, $39, $03, $30, $0F

; Bank 8
ft_s22p41c1:
	.byte $E3, $3B, $09, $2F, $01, $31, $01, $32, $01, $2D, $0B, $39, $03

; Bank 8
ft_s22p42c1:
	.byte $E3, $39, $05, $3B, $05, $33, $05, $82, $01, $2F, $31, $33, $36, $39, $3B, $83, $3E, $01

; Bank 8
ft_s22p44c1:
	.byte $82, $01, $E3, $34, $35, $35, $32, $3E, $32, $34, $35, $83, $3C, $0B, $3C, $03

; Bank 8
ft_s22p45c1:
	.byte $E3, $39, $09, $2D, $01, $2F, $01, $30, $01, $37, $0B, $3B, $03

; Bank 8
ft_s22p46c1:
	.byte $E3, $3B, $05, $3E, $05, $3D, $05, $82, $01, $2D, $2F, $31, $34, $37, $39, $83, $3C, $01

; Bank 8
ft_s22p47c1:
	.byte $E3, $39, $09, $2D, $01, $2F, $01, $30, $01, $37, $0B, $37, $03

; Bank 8
ft_s22p48c1:
	.byte $E3, $32, $01, $33, $01, $38, $01, $30, $03, $30, $01, $32, $01, $33, $01, $3A, $0B, $3A, $03

; Bank 8
ft_s22p49c1:
	.byte $E4, $37, $03, $7F, $01, $35, $00, $37, $02, $7F, $01, $43, $03, $82, $00, $39, $39, $39, $39, $39
	.byte $39, $39, $39, $39, $39, $39, $39, $83, $E2, $35, $01, $E4, $37, $01

; Bank 8
ft_s22p50c1:
	.byte $82, $01, $E4, $37, $35, $37, $E2, $37, $83, $E4, $37, $03, $37, $05, $82, $01, $37, $37, $37, $37
	.byte $37, $37, $83, $37, $01

; Bank 8
ft_s22p51c1:
	.byte $E4, $36, $00, $37, $04, $37, $05, $33, $01, $35, $03, $33, $01, $35, $05, $41, $01, $35, $03

; Bank 8
ft_s22p52c1:
	.byte $E4, $37, $05, $37, $05, $3E, $05, $82, $01, $29, $29, $29, $2B, $2D, $35, $83, $37, $01

; Bank 8
ft_s22p53c1:
	.byte $00, $01, $E4, $35, $01, $37, $0D, $82, $01, $2F, $2F, $2F, $2F, $2F, $2F, $83, $2F, $01

; Bank 8
ft_s22p54c1:
	.byte $E4, $39, $00, $3A, $00, $3A, $01, $3A, $01, $3A, $05, $33, $01, $35, $03, $33, $01, $35, $05, $3C
	.byte $01, $3C, $03

; Bank 8
ft_s22p55c1:
	.byte $E4, $3D, $03, $E2, $36, $01, $E4, $3A, $03, $31, $01, $36, $01, $38, $03, $36, $01, $38, $01, $31
	.byte $01, $E2, $20, $03, $E4, $33, $03

; Bank 8
ft_s22p56c1:
	.byte $E4, $35, $05, $33, $00, $35, $04, $41, $03, $82, $00, $37, $37, $37, $37, $37, $37, $37, $37, $37
	.byte $37, $37, $37, $83, $33, $01, $35, $01

; Bank 8
ft_s22p57c1:
	.byte $00, $01, $E4, $33, $01, $35, $1B

; Bank 8
ft_s22p58c1:
	.byte $E4, $34, $00, $35, $04, $35, $05, $31, $01, $33, $03, $31, $01, $33, $05, $3F, $01, $33, $03

; Bank 8
ft_s22p59c1:
	.byte $E4, $34, $00, $35, $04, $35, $05, $35, $05, $82, $01, $35, $35, $35, $35, $35, $35, $83, $35, $01

; Bank 8
ft_s22p60c1:
	.byte $00, $05, $E4, $35, $05, $3C, $05, $82, $01, $27, $27, $27, $29, $2B, $33, $83, $35, $01

; Bank 8
ft_s22p61c1:
	.byte $00, $01, $E4, $33, $01, $35, $0D, $82, $01, $2E, $2E, $2E, $2E, $2E, $2E, $83, $2E, $01

; Bank 8
ft_s22p62c1:
	.byte $E4, $37, $00, $38, $00, $38, $01, $38, $07, $31, $01, $33, $03, $31, $01, $33, $05, $3A, $05

; Bank 8
ft_s22p63c1:
	.byte $E4, $3B, $05, $38, $03, $2F, $01, $34, $01, $36, $03, $34, $01, $36, $01, $2F, $05, $31, $03

; Bank 8
ft_s22p64c1:
	.byte $E3, $32, $01, $33, $01, $38, $01, $30, $03, $30, $01, $32, $01, $33, $01, $3A, $07, $82, $00, $3A
	.byte $3A, $3A, $3A, $83, $3A, $03

; Bank 8
ft_s22p65c1:
	.byte $82, $00, $E3, $33, $33, $33, $33, $33, $33, $33, $83, $33, $18

; Bank 8
ft_s23_frames:
	.word ft_s23f0
	.word ft_s23f1
	.word ft_s23f2
	.word ft_s23f3
ft_s23f0:
	.word ft_s23p1c0, ft_s23p1c1, ft_s23p1c2, ft_s23p1c3, ft_s23p1c4
	.byte $08, $08, $08, $08, $08
ft_s23f1:
	.word ft_s23p1c0, ft_s23p1c1, ft_s23p1c2, ft_s23p1c3, ft_s23p1c4
	.byte $08, $08, $08, $08, $08
ft_s23f2:
	.word ft_s23p1c0, ft_s23p1c1, ft_s23p1c2, ft_s23p1c3, ft_s23p1c4
	.byte $08, $08, $08, $08, $08
ft_s23f3:
	.word ft_s23p2c0, ft_s23p2c1, ft_s23p2c2, ft_s23p2c3, ft_s23p2c4
	.byte $08, $08, $08, $08, $08
; Bank 8
ft_s23p1c0:
	.byte $94, $02, $82, $00, $80, $26, $93, $02, $8F, $00, $F9, $19, $94, $02, $19, $94, $02, $25, $94, $02
	.byte $19, $94, $02, $83, $19, $01, $94, $02, $25, $00, $94, $02, $31, $08, $94, $02, $82, $00, $20, $94
	.byte $02, $20, $94, $02, $2C, $94, $02, $20, $94, $02, $83, $20, $01, $94, $02, $2C, $00, $94, $02, $38
	.byte $08, $94, $02, $82, $00, $1E, $94, $02, $1E, $94, $02, $2A, $94, $02, $1E, $94, $02, $83, $1E, $01
	.byte $94, $02, $2A, $00, $94, $02, $36, $01, $94, $02, $1E, $00, $94, $02, $2A, $00, $94, $02, $1E, $04
	.byte $94, $02, $82, $00, $1C, $94, $02, $1C, $94, $02, $28, $94, $02, $1C, $94, $02, $83, $1C, $01, $94
	.byte $02, $82, $00, $28, $94, $02, $34, $94, $02, $00, $94, $02, $1B, $94, $02, $27, $94, $02, $83, $1B
	.byte $02, $94, $02, $27, $01

; Bank 8
ft_s23p1c1:
	.byte $80, $2A, $8F, $77, $93, $01, $FB, $19, $0B, $7E, $03, $8F, $77, $20, $0B, $7E, $03, $1E, $0B, $7E
	.byte $03, $1C, $06, $7E, $00, $1B, $06, $7E, $00

; Bank 8
ft_s23p1c2:
	.byte $82, $00, $80, $20, $9B, $03, $25, $9B, $03, $25, $9B, $03, $31, $9B, $03, $25, $83, $9B, $03, $25
	.byte $01, $9B, $03, $31, $00, $9B, $03, $3D, $05, $7F, $02, $82, $00, $E0, $9B, $03, $2C, $9B, $03, $2C
	.byte $9B, $03, $38, $9B, $03, $2C, $83, $9B, $03, $2C, $01, $9B, $03, $38, $00, $9B, $03, $44, $08, $82
	.byte $00, $9B, $03, $2A, $9B, $03, $2A, $9B, $03, $36, $9B, $03, $2A, $83, $9B, $03, $2A, $01, $9B, $03
	.byte $36, $00, $9B, $03, $42, $01, $9B, $03, $2A, $00, $9B, $03, $36, $00, $9B, $03, $2A, $04, $82, $00
	.byte $9B, $03, $28, $9B, $03, $28, $9B, $03, $34, $9B, $03, $28, $83, $9B, $03, $28, $01, $82, $00, $9B
	.byte $03, $34, $9B, $03, $40, $9B, $03, $00, $9B, $03, $27, $9B, $03, $33, $83, $9B, $03, $27, $02, $9B
	.byte $03, $33, $01

; Bank 8
ft_s23p1c3:
	.byte $82, $00, $E7, $FC, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11
	.byte $11, $E9, $20, $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $E7, $11, $E9, $20, $E8, $11, $E9
	.byte $20, $E7, $11, $E8, $11, $E9, $1C, $E7, $11, $11, $E9, $20, $E8, $11, $F9, $13, $F8, $13, $F7, $13
	.byte $E7, $FC, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11, $11, $E9
	.byte $20, $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $E7, $11, $E9, $20, $E8, $11, $E9, $20, $E7
	.byte $11, $E8, $11, $E9, $1C, $E7, $11, $11, $E9, $20, $E8, $11, $F9, $13, $F8, $13, $83, $F7, $13, $00

; Bank 8
ft_s23p1c4:
	.byte $96, $41, $97, $00, $1D, $03, $97, $04, $1E, $01, $97, $03, $1D, $02, $97, $02, $1D, $00, $97, $00
	.byte $1D, $01, $97, $04, $1E, $03, $97, $01, $1D, $01, $97, $01, $1D, $01, $97, $04, $1E, $01, $97, $01
	.byte $1D, $00, $97, $02, $1E, $01, $97, $00, $1D, $00, $1D, $01, $82, $00, $97, $04, $1E, $97, $08, $1E
	.byte $97, $07, $1E, $97, $09, $1E, $83, $97, $00, $1D, $03, $97, $04, $1E, $02, $97, $00, $1D, $01, $97
	.byte $02, $1D, $00, $97, $01, $1D, $01, $97, $04, $1E, $03, $97, $00, $1D, $01, $1D, $01, $97, $04, $1E
	.byte $01, $97, $00, $1D, $00, $97, $03, $1E, $01, $97, $00, $1D, $00, $1D, $01, $82, $00, $97, $04, $1E
	.byte $97, $08, $1E, $97, $07, $1E, $83, $97, $09, $1E, $00

; Bank 8
ft_s23p2c0:
	.byte $94, $02, $82, $00, $80, $26, $93, $02, $F9, $19, $94, $02, $19, $94, $02, $25, $94, $02, $19, $94
	.byte $02, $83, $19, $01, $94, $02, $25, $00, $94, $02, $31, $08, $94, $02, $82, $00, $20, $94, $02, $20
	.byte $94, $02, $2C, $94, $02, $20, $94, $02, $83, $20, $01, $94, $02, $2C, $00, $94, $02, $38, $08, $94
	.byte $02, $82, $00, $1C, $94, $02, $1C, $94, $02, $28, $94, $02, $1C, $94, $02, $83, $1C, $01, $94, $02
	.byte $82, $00, $28, $94, $02, $34, $94, $02, $00, $94, $02, $1C, $94, $02, $28, $94, $02, $83, $1C, $04
	.byte $EF, $93, $02, $8F, $46, $1B, $0B, $7E, $03

; Bank 8
ft_s23p2c1:
	.byte $80, $2A, $8F, $77, $93, $01, $FA, $19, $0B, $7E, $03, $20, $0B, $7E, $03, $1C, $0B, $7E, $03, $EF
	.byte $8F, $77, $93, $01, $1B, $0B, $7E, $03

; Bank 8
ft_s23p2c2:
	.byte $82, $00, $80, $20, $9B, $03, $25, $9B, $03, $25, $9B, $03, $31, $9B, $03, $25, $83, $9B, $03, $25
	.byte $01, $9B, $03, $31, $00, $9B, $03, $3D, $05, $7F, $02, $82, $00, $E0, $9B, $03, $2C, $9B, $03, $2C
	.byte $9B, $03, $38, $9B, $03, $2C, $83, $9B, $03, $2C, $01, $9B, $03, $38, $00, $9B, $03, $44, $08, $82
	.byte $00, $9B, $03, $28, $9B, $03, $28, $9B, $03, $34, $9B, $03, $28, $83, $9B, $03, $28, $01, $82, $00
	.byte $9B, $03, $34, $9B, $03, $40, $9B, $03, $00, $9B, $03, $28, $9B, $03, $34, $83, $9B, $03, $28, $14

; Bank 8
ft_s23p2c3:
	.byte $82, $00, $E7, $FC, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11
	.byte $11, $E9, $20, $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $E7, $11, $E9, $20, $E8, $11, $E9
	.byte $20, $E7, $11, $E8, $11, $E9, $1C, $E7, $11, $11, $E9, $20, $E8, $11, $F9, $13, $F8, $13, $F7, $13
	.byte $E7, $FC, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11, $11, $E9
	.byte $20, $E8, $11, $E9, $20, $1E, $20, $83, $E7, $11, $01, $11, $03, $E9, $19, $09

; Bank 8
ft_s23p2c4:
	.byte $96, $41, $97, $00, $1D, $03, $97, $04, $1E, $01, $97, $03, $1D, $02, $97, $02, $1D, $00, $97, $00
	.byte $1D, $01, $97, $04, $1E, $03, $97, $01, $1D, $01, $97, $01, $1D, $01, $97, $04, $1E, $01, $97, $01
	.byte $1D, $00, $97, $02, $1E, $01, $97, $00, $1D, $00, $1D, $01, $82, $00, $97, $04, $1E, $97, $08, $1E
	.byte $97, $07, $1E, $97, $09, $1E, $83, $97, $00, $1D, $03, $97, $04, $1E, $02, $97, $00, $1D, $01, $97
	.byte $02, $1D, $00, $97, $01, $1D, $01, $97, $04, $1E, $03, $97, $00, $1D, $01, $97, $01, $1D, $03, $97
	.byte $02, $1D, $03, $97, $02, $1D, $01, $97, $03, $1D, $03

; Bank 8
ft_s24_frames:
	.word ft_s24f0
	.word ft_s24f1
	.word ft_s24f2
	.word ft_s24f3
ft_s24f0:
	.word ft_s24p1c0, ft_s24p1c1, ft_s24p1c2, ft_s24p1c3, ft_s24p1c4
	.byte $08, $08, $08, $08, $08
ft_s24f1:
	.word ft_s24p1c0, ft_s24p1c1, ft_s24p1c2, ft_s24p1c3, ft_s24p1c4
	.byte $08, $08, $08, $08, $08
ft_s24f2:
	.word ft_s24p1c0, ft_s24p1c1, ft_s24p1c2, ft_s24p1c3, ft_s24p1c4
	.byte $08, $08, $08, $08, $08
ft_s24f3:
	.word ft_s24p2c0, ft_s24p1c1, ft_s24p2c2, ft_s24p2c3, ft_s24p2c4
	.byte $08, $08, $08, $08, $08
; Bank 8
ft_s24p1c0:
	.byte $00, $02, $E2, $3D, $0F, $3D, $0F, $3D, $0F, $3D, $0C

; Bank 8
ft_s24p1c1:
	.byte $EC, $19, $0F, $17, $0F, $16, $0F, $15, $06, $17, $08

; Bank 8
ft_s24p1c2:
	.byte $82, $00, $EE, $31, $31, $3D, $ED, $3D, $EE, $38, $83, $ED, $38, $01, $82, $00, $EE, $37, $ED, $37
	.byte $EE, $36, $ED, $36, $EE, $34, $ED, $34, $EE, $31, $34, $36, $2F, $2F, $3D, $ED, $3D, $EE, $38, $83
	.byte $ED, $38, $01, $82, $00, $EE, $37, $ED, $37, $EE, $36, $ED, $36, $EE, $34, $ED, $34, $EE, $31, $34
	.byte $36, $2E, $2E, $3D, $ED, $3D, $EE, $38, $83, $ED, $38, $01, $82, $00, $EE, $37, $ED, $37, $EE, $36
	.byte $ED, $36, $EE, $34, $ED, $34, $EE, $31, $34, $36, $2D, $2D, $3D, $ED, $3D, $EE, $38, $83, $ED, $38
	.byte $01, $82, $00, $EE, $37, $ED, $37, $EE, $36, $ED, $36, $EE, $34, $ED, $34, $EE, $31, $34, $83, $36
	.byte $00

; Bank 8
ft_s24p1c3:
	.byte $82, $00, $E7, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11, $11
	.byte $E9, $20, $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $E7, $11, $E9, $20, $E8, $11, $E9, $20
	.byte $E7, $11, $E8, $11, $E9, $1C, $E7, $11, $11, $E9, $20, $E8, $11, $13, $13, $13, $E7, $11, $E9, $20
	.byte $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11, $11, $E9, $20, $E8, $11, $E9, $20
	.byte $1E, $20, $E7, $11, $E9, $20, $E7, $11, $E9, $20, $E8, $11, $E9, $20, $E7, $11, $E8, $11, $E9, $1C
	.byte $E7, $11, $11, $E9, $20, $E8, $11, $13, $13, $83, $13, $00

; Bank 8
ft_s24p1c4:
	.byte $1D, $03, $1E, $02, $1D, $01, $1D, $00, $1D, $01, $1E, $03, $1D, $01, $1D, $01, $1E, $01, $1D, $00
	.byte $1E, $01, $1D, $00, $1D, $01, $82, $00, $1E, $1E, $1E, $1E, $83, $1D, $03, $1E, $02, $1D, $01, $1D
	.byte $00, $1D, $01, $1E, $03, $1D, $01, $1D, $01, $1E, $01, $1D, $00, $1E, $01, $1D, $00, $1D, $01, $82
	.byte $00, $1E, $1E, $1E, $83, $1E, $00

; Bank 8
ft_s24p2c0:
	.byte $00, $02, $E2, $3D, $0F, $3D, $0F, $3D, $1C

; Bank 8
ft_s24p2c2:
	.byte $82, $00, $EE, $31, $31, $3D, $ED, $3D, $EE, $38, $83, $ED, $38, $01, $82, $00, $EE, $37, $ED, $37
	.byte $EE, $36, $ED, $36, $EE, $34, $ED, $34, $EE, $31, $34, $36, $2F, $2F, $3D, $ED, $3D, $EE, $38, $83
	.byte $ED, $38, $01, $82, $00, $EE, $37, $ED, $37, $EE, $36, $ED, $36, $EE, $34, $ED, $34, $EE, $31, $34
	.byte $36, $2E, $2E, $3D, $ED, $3D, $EE, $38, $83, $ED, $38, $01, $82, $00, $EE, $37, $ED, $37, $EE, $36
	.byte $ED, $36, $EE, $34, $ED, $34, $EE, $31, $34, $83, $36, $10

; Bank 8
ft_s24p2c3:
	.byte $82, $00, $E7, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11, $11
	.byte $E9, $20, $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $E7, $11, $E9, $20, $E8, $11, $E9, $20
	.byte $E7, $11, $E8, $11, $E9, $1C, $E7, $11, $11, $E9, $20, $E8, $11, $13, $13, $13, $E7, $11, $E9, $20
	.byte $1E, $20, $E8, $11, $E9, $20, $1E, $E7, $11, $E9, $1C, $E7, $11, $11, $E9, $20, $E8, $11, $E9, $20
	.byte $1E, $20, $83, $E7, $11, $01, $11, $03, $11, $01, $11, $03, $EA, $1D, $01, $1D, $01

; Bank 8
ft_s24p2c4:
	.byte $1D, $03, $1E, $02, $1D, $01, $1D, $00, $1D, $01, $1E, $03, $1D, $01, $1D, $01, $1E, $01, $1D, $00
	.byte $1E, $01, $1D, $00, $1D, $01, $82, $00, $1E, $1E, $1E, $1E, $83, $1D, $03, $1E, $02, $1D, $01, $1D
	.byte $00, $1D, $01, $1E, $03, $1D, $01, $1D, $03, $1D, $01, $1D, $03, $1D, $01, $1D, $01

; Bank 8
ft_s25_frames:
	.word ft_s25f0
	.word ft_s25f1
	.word ft_s25f2
	.word ft_s25f3
	.word ft_s25f4
	.word ft_s25f5
	.word ft_s25f6
	.word ft_s25f7
	.word ft_s25f8
	.word ft_s25f9
	.word ft_s25f10
	.word ft_s25f11
	.word ft_s25f12
	.word ft_s25f13
	.word ft_s25f14
	.word ft_s25f15
	.word ft_s25f16
	.word ft_s25f17
	.word ft_s25f18
	.word ft_s25f19
	.word ft_s25f20
	.word ft_s25f21
	.word ft_s25f22
	.word ft_s25f23
	.word ft_s25f24
	.word ft_s25f25
	.word ft_s25f26
	.word ft_s25f27
	.word ft_s25f28
	.word ft_s25f29
	.word ft_s25f30
	.word ft_s25f31
ft_s25f0:
	.word ft_s22p0c2, ft_s25p1c1, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $07, $08, $07, $07, $07
ft_s25f1:
	.word ft_s22p0c2, ft_s25p2c1, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $07, $08, $07, $07, $07
ft_s25f2:
	.word ft_s22p0c2, ft_s25p3c1, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $07, $08, $07, $07, $07
ft_s25f3:
	.word ft_s22p0c2, ft_s25p4c1, ft_s22p0c2, ft_s22p0c2, ft_s25p1c4
	.byte $07, $08, $07, $07, $08
ft_s25f4:
	.word ft_s22p0c2, ft_s25p1c1, ft_s25p1c2, ft_s22p0c2, ft_s25p2c4
	.byte $07, $08, $08, $07, $08
ft_s25f5:
	.word ft_s22p0c2, ft_s25p2c1, ft_s25p2c2, ft_s22p0c2, ft_s25p2c4
	.byte $07, $08, $08, $07, $08
ft_s25f6:
	.word ft_s22p0c2, ft_s25p3c1, ft_s25p3c2, ft_s22p0c2, ft_s25p2c4
	.byte $07, $08, $08, $07, $08
ft_s25f7:
	.word ft_s22p0c2, ft_s25p4c1, ft_s25p1c2, ft_s25p1c3, ft_s25p3c4
	.byte $07, $08, $08, $08, $08
ft_s25f8:
	.word ft_s25p5c0, ft_s25p1c1, ft_s25p1c2, ft_s25p4c3, ft_s25p4c4
	.byte $08, $08, $08, $08, $08
ft_s25f9:
	.word ft_s25p6c0, ft_s25p2c1, ft_s25p2c2, ft_s25p5c3, ft_s25p5c4
	.byte $08, $08, $08, $08, $08
ft_s25f10:
	.word ft_s25p7c0, ft_s25p3c1, ft_s25p3c2, ft_s25p4c3, ft_s25p4c4
	.byte $08, $08, $08, $08, $08
ft_s25f11:
	.word ft_s25p8c0, ft_s25p4c1, ft_s25p1c2, ft_s25p6c3, ft_s25p6c4
	.byte $08, $08, $08, $08, $08
ft_s25f12:
	.word ft_s25p5c0, ft_s25p1c1, ft_s25p1c2, ft_s25p4c3, ft_s25p4c4
	.byte $08, $08, $08, $08, $08
ft_s25f13:
	.word ft_s25p6c0, ft_s25p2c1, ft_s25p2c2, ft_s25p5c3, ft_s25p5c4
	.byte $08, $08, $08, $08, $08
ft_s25f14:
	.word ft_s25p7c0, ft_s25p3c1, ft_s25p3c2, ft_s25p4c3, ft_s25p4c4
	.byte $08, $08, $08, $08, $08
ft_s25f15:
	.word ft_s7p0c0, ft_s25p4c1, ft_s25p1c2, ft_s25p6c3, ft_s25p6c4
	.byte $04, $08, $08, $08, $08
ft_s25f16:
	.word ft_s25p9c0, ft_s25p1c1, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $08, $08, $07, $07, $07
ft_s25f17:
	.word ft_s25p10c0, ft_s25p2c1, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $08, $08, $07, $07, $07
ft_s25f18:
	.word ft_s25p11c0, ft_s25p3c1, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $08, $08, $07, $07, $07
ft_s25f19:
	.word ft_s25p12c0, ft_s25p4c1, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $08, $08, $07, $07, $07
ft_s25f20:
	.word ft_s25p9c0, ft_s25p1c1, ft_s22p0c2, ft_s25p4c3, ft_s25p4c4
	.byte $08, $08, $07, $08, $08
ft_s25f21:
	.word ft_s25p10c0, ft_s25p2c1, ft_s22p0c2, ft_s25p5c3, ft_s25p5c4
	.byte $08, $08, $07, $08, $08
ft_s25f22:
	.word ft_s25p11c0, ft_s25p3c1, ft_s22p0c2, ft_s25p4c3, ft_s25p4c4
	.byte $08, $08, $07, $08, $08
ft_s25f23:
	.word ft_s25p12c0, ft_s25p4c1, ft_s22p0c2, ft_s25p6c3, ft_s25p6c4
	.byte $08, $08, $07, $08, $08
ft_s25f24:
	.word ft_s25p13c0, ft_s25p1c1, ft_s25p1c2, ft_s22p0c2, ft_s22p0c2
	.byte $08, $08, $08, $07, $07
ft_s25f25:
	.word ft_s25p14c0, ft_s25p2c1, ft_s25p2c2, ft_s25p5c3, ft_s25p5c4
	.byte $09, $08, $08, $08, $08
ft_s25f26:
	.word ft_s25p15c0, ft_s25p3c1, ft_s25p3c2, ft_s25p4c3, ft_s25p4c4
	.byte $09, $08, $08, $08, $08
ft_s25f27:
	.word ft_s25p16c0, ft_s25p4c1, ft_s25p1c2, ft_s25p6c3, ft_s25p6c4
	.byte $09, $08, $08, $08, $08
ft_s25f28:
	.word ft_s25p13c0, ft_s25p1c1, ft_s25p1c2, ft_s25p4c3, ft_s25p4c4
	.byte $08, $08, $08, $08, $08
ft_s25f29:
	.word ft_s25p14c0, ft_s25p2c1, ft_s25p2c2, ft_s25p5c3, ft_s25p5c4
	.byte $09, $08, $08, $08, $08
ft_s25f30:
	.word ft_s25p15c0, ft_s25p3c1, ft_s25p3c2, ft_s25p4c3, ft_s25p4c4
	.byte $09, $08, $08, $08, $08
ft_s25f31:
	.word ft_s25p16c0, ft_s25p4c1, ft_s25p1c2, ft_s25p6c3, ft_s25p6c4
	.byte $09, $08, $08, $08, $08
; Bank 8
ft_s25p1c1:
	.byte $E2, $FF, $18, $01, $82, $00, $FF, $1F, $80, $22, $F3, $18, $E2, $FF, $27, $80, $22, $F3, $1F, $E2
	.byte $FF, $18, $80, $22, $F3, $27, $E2, $FF, $1F, $80, $22, $F3, $18, $E2, $FF, $27, $80, $22, $F3, $1F
	.byte $E2, $FF, $18, $80, $22, $F3, $27, $E2, $FF, $1F, $80, $22, $F3, $18, $E2, $FF, $29, $80, $22, $F3
	.byte $1F, $E2, $FF, $18, $80, $22, $F3, $29, $E2, $FF, $1F, $80, $22, $F3, $18, $E2, $FF, $29, $80, $22
	.byte $F3, $1F, $E2, $FF, $18, $80, $22, $F3, $29, $E2, $FF, $1F, $80, $22, $F3, $18, $E2, $FF, $29, $80
	.byte $22, $F3, $1F, $E2, $FF, $2B, $83, $80, $22, $F3, $29, $00

; Bank 8
ft_s25p1c2:
	.byte $E0, $8F, $00, $24, $03, $8F, $36, $00, $1B

; Bank 8
ft_s25p1c3:
	.byte $00, $0F, $EA, $1D, $02, $1B, $02, $1D, $03, $E7, $11, $01, $82, $00, $E8, $12, $12, $12, $83, $12
	.byte $00

; Bank 8
ft_s25p1c4:
	.byte $00, $1D, $1D, $01

; Bank 8
ft_s25p2c1:
	.byte $82, $00, $E2, $FF, $14, $80, $22, $F3, $2B, $E2, $FF, $1B, $80, $22, $F3, $14, $E2, $FF, $24, $80
	.byte $22, $F3, $1B, $E2, $FF, $14, $80, $22, $F3, $24, $E2, $FF, $1B, $80, $22, $F3, $14, $E2, $FF, $24
	.byte $80, $22, $F3, $1B, $E2, $FF, $14, $80, $22, $F3, $24, $E2, $FF, $1B, $80, $22, $F3, $14, $E2, $FF
	.byte $27, $80, $22, $F3, $1B, $E2, $FF, $14, $80, $22, $F3, $27, $E2, $FF, $1B, $80, $22, $F3, $14, $E2
	.byte $FF, $27, $80, $22, $F3, $1B, $E2, $FF, $14, $80, $22, $F3, $27, $E2, $FF, $1B, $80, $22, $F3, $14
	.byte $E2, $FF, $29, $80, $22, $F3, $1B, $E2, $FF, $27, $83, $80, $22, $F3, $29, $00

; Bank 8
ft_s25p2c2:
	.byte $E0, $8F, $00, $20, $03, $8F, $36, $00, $1B

; Bank 8
ft_s25p2c4:
	.byte $1D, $1D, $1D, $01

; Bank 8
ft_s25p3c1:
	.byte $82, $00, $E2, $FF, $16, $80, $22, $F3, $27, $E2, $FF, $1D, $80, $22, $F3, $16, $E2, $FF, $26, $80
	.byte $22, $F3, $1D, $E2, $FF, $16, $80, $22, $F3, $26, $E2, $FF, $1D, $80, $22, $F3, $16, $E2, $FF, $26
	.byte $80, $22, $F3, $1D, $E2, $FF, $16, $80, $22, $F3, $26, $E2, $FF, $1D, $80, $22, $F3, $16, $E2, $FF
	.byte $26, $80, $22, $F3, $1D, $E2, $FF, $16, $80, $22, $F3, $26, $E2, $FF, $1D, $80, $22, $F3, $16, $E2
	.byte $FF, $26, $80, $22, $F3, $1D, $E2, $FF, $16, $80, $22, $F3, $26, $E2, $FF, $1D, $80, $22, $F3, $16
	.byte $E2, $FF, $27, $80, $22, $F3, $1D, $E2, $FF, $26, $83, $80, $22, $F3, $27, $00

; Bank 8
ft_s25p3c2:
	.byte $E0, $8F, $00, $22, $03, $8F, $36, $00, $1B

; Bank 8
ft_s25p3c4:
	.byte $1D, $0F, $1E, $02, $1E, $02, $1E, $03, $1D, $01, $82, $00, $1E, $1E, $1E, $83, $1E, $00

; Bank 8
ft_s25p4c1:
	.byte $82, $00, $E2, $FF, $18, $80, $22, $F3, $26, $E2, $FF, $1F, $80, $22, $F3, $18, $E2, $FF, $24, $80
	.byte $22, $F3, $1F, $E2, $FF, $18, $80, $22, $F3, $24, $E2, $FF, $1F, $80, $22, $F3, $18, $E2, $FF, $24
	.byte $80, $22, $F3, $1F, $E2, $FF, $18, $80, $22, $F3, $24, $E2, $FF, $1F, $80, $22, $F3, $18, $E2, $FF
	.byte $26, $80, $22, $F3, $1F, $E2, $FF, $18, $80, $22, $F3, $26, $E2, $FF, $1F, $80, $22, $F3, $18, $E2
	.byte $FF, $26, $80, $22, $F3, $1F, $E2, $FF, $18, $80, $22, $F3, $26, $E2, $FF, $1F, $80, $22, $F3, $18
	.byte $E2, $FF, $26, $80, $22, $F3, $1F, $E2, $FF, $27, $83, $80, $22, $F3, $26, $00

; Bank 8
ft_s25p4c3:
	.byte $82, $00, $E7, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $20, $1E, $20, $E7, $11, $E9, $20
	.byte $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $20, $1E, $20
	.byte $E7, $11, $E9, $20, $E8, $11, $E9, $20, $1E, $83, $20, $00

; Bank 8
ft_s25p4c4:
	.byte $1D, $03, $1E, $05, $1D, $01, $1E, $03, $1D, $03, $1E, $05, $1D, $01, $1E, $03

; Bank 8
ft_s25p5c0:
	.byte $82, $01, $E4, $FF, $24, $2B, $33, $24, $2B, $33, $24, $2B, $35, $24, $2B, $35, $24, $2B, $35, $83
	.byte $37, $01

; Bank 8
ft_s25p5c3:
	.byte $82, $00, $E7, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $20, $1E, $20, $E7, $11, $E9, $20
	.byte $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $E7, $11, $E9, $20
	.byte $1E, $20, $E7, $11, $E9, $20, $E8, $11, $E9, $20, $1E, $83, $20, $00

; Bank 8
ft_s25p5c4:
	.byte $1D, $03, $1E, $05, $1D, $01, $1E, $03, $1D, $03, $1E, $01, $1D, $03, $1D, $01, $1E, $03

; Bank 8
ft_s25p6c0:
	.byte $82, $01, $E4, $20, $27, $30, $20, $27, $30, $20, $27, $33, $20, $27, $33, $20, $27, $35, $83, $33
	.byte $01

; Bank 8
ft_s25p6c3:
	.byte $82, $00, $E7, $11, $E9, $20, $1E, $20, $E8, $11, $E9, $20, $1E, $20, $1E, $20, $E7, $11, $E9, $20
	.byte $E8, $11, $E9, $20, $1E, $20, $E7, $11, $E9, $20, $1E, $E7, $11, $E9, $1E, $20, $E7, $11, $E9, $20
	.byte $1E, $20, $E7, $11, $E9, $20, $E8, $11, $E9, $20, $1E, $83, $20, $00

; Bank 8
ft_s25p6c4:
	.byte $1D, $03, $1E, $05, $1D, $01, $1E, $03, $1D, $02, $1D, $02, $1D, $03, $1D, $01, $1E, $03

; Bank 8
ft_s25p7c0:
	.byte $82, $01, $E4, $22, $29, $32, $22, $29, $32, $22, $29, $32, $22, $29, $32, $22, $29, $33, $83, $32
	.byte $01

; Bank 8
ft_s25p8c0:
	.byte $82, $01, $E4, $24, $2B, $30, $24, $2B, $30, $24, $2B, $32, $24, $2B, $32, $24, $2B, $32, $83, $33
	.byte $01

; Bank 8
ft_s25p9c0:
	.byte $E1, $24, $0D, $29, $00, $2B, $00, $2C, $05, $2B, $05, $27, $03

; Bank 8
ft_s25p10c0:
	.byte $E1, $30, $0D, $30, $00, $32, $00, $33, $05, $32, $05, $2E, $03

; Bank 8
ft_s25p11c0:
	.byte $E1, $35, $05, $33, $05, $32, $0F, $2E, $03

; Bank 8
ft_s25p12c0:
	.byte $E1, $30, $17, $7F, $07

; Bank 8
ft_s25p13c0:
	.byte $EF, $FA, $0C, $01, $82, $00, $FA, $13, $F3, $0C, $FA, $1B, $F3, $13, $FA, $0C, $F3, $1B, $FA, $13
	.byte $F3, $0C, $FA, $1B, $F3, $13, $FA, $0C, $F3, $1B, $FA, $13, $F3, $0C, $FA, $1D, $F3, $13, $FA, $0C
	.byte $F3, $1D, $FA, $13, $F3, $0C, $FA, $1D, $F3, $13, $FA, $0C, $F3, $1D, $FA, $13, $F3, $0C, $FA, $1D
	.byte $F3, $13, $FA, $1F, $83, $F3, $1D, $00

; Bank 9
ft_s25p14c0:
	.byte $82, $00, $EF, $FA, $08, $F3, $1F, $FA, $0F, $F3, $08, $FA, $18, $F3, $0F, $FA, $08, $F3, $18, $FA
	.byte $0F, $F3, $08, $FA, $18, $F3, $0F, $FA, $08, $F3, $18, $FA, $0F, $F3, $08, $FA, $1B, $F3, $0F, $FA
	.byte $08, $F3, $1B, $FA, $0F, $F3, $08, $FA, $1B, $F3, $0F, $FA, $08, $F3, $1B, $FA, $0F, $F3, $08, $FA
	.byte $1D, $F3, $0F, $FA, $1B, $83, $F3, $1D, $00

; Bank 9
ft_s25p15c0:
	.byte $82, $00, $EF, $FA, $0A, $F3, $1B, $FA, $11, $F3, $0A, $FA, $1A, $F3, $11, $FA, $0A, $F3, $1A, $FA
	.byte $11, $F3, $0A, $FA, $1A, $F3, $11, $FA, $0A, $F3, $1A, $FA, $11, $F3, $0A, $FA, $1A, $F3, $11, $FA
	.byte $0A, $F3, $1A, $FA, $11, $F3, $0A, $FA, $1A, $F3, $11, $FA, $0A, $F3, $1A, $FA, $11, $F3, $0A, $FA
	.byte $1B, $F3, $11, $FA, $1A, $83, $F3, $1B, $00

; Bank 9
ft_s25p16c0:
	.byte $82, $00, $EF, $FA, $0C, $F3, $1A, $FA, $13, $F3, $0C, $FA, $18, $F3, $13, $FA, $0C, $F3, $18, $FA
	.byte $13, $F3, $0C, $FA, $18, $F3, $13, $FA, $0C, $F3, $18, $FA, $13, $F3, $0C, $FA, $1A, $F3, $13, $FA
	.byte $0C, $F3, $1A, $FA, $13, $F3, $0C, $FA, $1A, $F3, $13, $FA, $0C, $F3, $1A, $FA, $13, $F3, $0C, $FA
	.byte $1A, $F3, $13, $FA, $1B, $83, $F3, $1A, $00

; Bank 9
ft_s26_frames:
	.word ft_s26f0
	.word ft_s26f1
ft_s26f0:
	.word ft_s26p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p0c0, ft_s7p0c0
	.byte $09, $04, $04, $04, $04
ft_s26f1:
	.word ft_s26p1c0, ft_s7p0c0, ft_s7p0c0, ft_s26p1c3, ft_s26p1c4
	.byte $09, $04, $04, $09, $09
; Bank 9
ft_s26p0c0:
	.byte $EC, $19, $17, $15, $03, $17, $03

; Bank 9
ft_s26p1c0:
	.byte $EC, $19, $0F, $17, $0F

; Bank 9
ft_s26p1c3:
	.byte $00, $0F, $EA, $1C, $05, $1C, $05, $82, $00, $E8, $11, $11, $11, $83, $11, $00

; Bank 9
ft_s26p1c4:
	.byte $00, $0F, $1D, $05, $1D, $05, $82, $00, $1D, $1D, $1D, $83, $1D, $00

; Bank 9
ft_s27_frames:
	.word ft_s27f0
	.word ft_s27f1
	.word ft_s27f2
	.word ft_s27f3
	.word ft_s27f4
	.word ft_s27f5
	.word ft_s27f6
	.word ft_s27f7
	.word ft_s27f8
	.word ft_s27f9
	.word ft_s27f10
	.word ft_s27f11
	.word ft_s27f12
	.word ft_s27f13
	.word ft_s27f14
	.word ft_s27f15
	.word ft_s27f16
	.word ft_s27f17
	.word ft_s27f18
	.word ft_s27f19
	.word ft_s27f20
	.word ft_s27f21
	.word ft_s27f22
	.word ft_s27f23
	.word ft_s27f24
	.word ft_s27f25
	.word ft_s27f26
	.word ft_s27f27
	.word ft_s27f28
	.word ft_s27f29
	.word ft_s27f30
	.word ft_s27f31
	.word ft_s27f32
	.word ft_s27f33
	.word ft_s27f34
	.word ft_s27f35
	.word ft_s27f36
	.word ft_s27f37
ft_s27f0:
	.word ft_s27p1c0, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $09, $07, $07, $07, $07
ft_s27f1:
	.word ft_s27p2c0, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $09, $07, $07, $07, $07
ft_s27f2:
	.word ft_s27p3c0, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $09, $07, $07, $07, $07
ft_s27f3:
	.word ft_s27p4c0, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $09, $07, $07, $07, $07
ft_s27f4:
	.word ft_s27p1c0, ft_s27p1c1, ft_s7p0c0, ft_s22p0c2, ft_s22p0c2
	.byte $09, $09, $04, $07, $07
ft_s27f5:
	.word ft_s27p2c0, ft_s27p2c1, ft_s7p0c0, ft_s22p0c2, ft_s22p0c2
	.byte $09, $09, $04, $07, $07
ft_s27f6:
	.word ft_s27p3c0, ft_s27p3c1, ft_s7p0c0, ft_s22p0c2, ft_s22p0c2
	.byte $09, $09, $04, $07, $07
ft_s27f7:
	.word ft_s27p4c0, ft_s27p3c1, ft_s7p0c0, ft_s22p0c2, ft_s22p0c2
	.byte $09, $09, $04, $07, $07
ft_s27f8:
	.word ft_s27p1c0, ft_s27p1c1, ft_s22p0c2, ft_s22p0c2, ft_s27p1c4
	.byte $09, $09, $07, $07, $09
ft_s27f9:
	.word ft_s27p2c0, ft_s27p2c1, ft_s22p0c2, ft_s22p0c2, ft_s27p2c4
	.byte $09, $09, $07, $07, $09
ft_s27f10:
	.word ft_s27p3c0, ft_s27p3c1, ft_s22p0c2, ft_s22p0c2, ft_s27p3c4
	.byte $09, $09, $07, $07, $09
ft_s27f11:
	.word ft_s27p4c0, ft_s27p3c1, ft_s22p0c2, ft_s22p0c2, ft_s27p3c4
	.byte $09, $09, $07, $07, $09
ft_s27f12:
	.word ft_s27p1c0, ft_s27p1c1, ft_s22p0c2, ft_s22p0c2, ft_s27p4c4
	.byte $09, $09, $07, $07, $09
ft_s27f13:
	.word ft_s27p2c0, ft_s27p2c1, ft_s22p0c2, ft_s22p0c2, ft_s27p5c4
	.byte $09, $09, $07, $07, $09
ft_s27f14:
	.word ft_s27p3c0, ft_s27p3c1, ft_s22p0c2, ft_s22p0c2, ft_s27p6c4
	.byte $09, $09, $07, $07, $09
ft_s27f15:
	.word ft_s27p4c0, ft_s27p3c1, ft_s22p0c2, ft_s22p0c2, ft_s27p6c4
	.byte $09, $09, $07, $07, $09
ft_s27f16:
	.word ft_s27p1c0, ft_s27p1c1, ft_s22p0c2, ft_s22p0c2, ft_s27p4c4
	.byte $09, $09, $07, $07, $09
ft_s27f17:
	.word ft_s27p2c0, ft_s27p2c1, ft_s22p0c2, ft_s22p0c2, ft_s27p5c4
	.byte $09, $09, $07, $07, $09
ft_s27f18:
	.word ft_s27p3c0, ft_s27p3c1, ft_s22p0c2, ft_s22p0c2, ft_s27p7c4
	.byte $09, $09, $07, $07, $09
ft_s27f19:
	.word ft_s27p4c0, ft_s27p3c1, ft_s22p0c2, ft_s22p0c2, ft_s27p8c4
	.byte $09, $09, $07, $07, $09
ft_s27f20:
	.word ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2
	.byte $07, $07, $07, $07, $07
ft_s27f21:
	.word ft_s27p5c0, ft_s27p3c1, ft_s22p0c2, ft_s27p3c3, ft_s22p9c4
	.byte $09, $09, $07, $09, $07
ft_s27f22:
	.word ft_s27p6c0, ft_s27p3c1, ft_s22p0c2, ft_s27p4c3, ft_s27p10c4
	.byte $09, $09, $07, $09, $09
ft_s27f23:
	.word ft_s27p7c0, ft_s27p1c1, ft_s22p0c2, ft_s27p3c3, ft_s22p20c4
	.byte $09, $09, $07, $09, $07
ft_s27f24:
	.word ft_s27p8c0, ft_s27p1c1, ft_s22p0c2, ft_s27p4c3, ft_s27p12c4
	.byte $09, $09, $07, $09, $09
ft_s27f25:
	.word ft_s27p9c0, ft_s27p6c1, ft_s22p0c2, ft_s27p3c3, ft_s27p13c4
	.byte $09, $09, $07, $09, $09
ft_s27f26:
	.word ft_s27p10c0, ft_s27p6c1, ft_s22p0c2, ft_s27p4c3, ft_s27p14c4
	.byte $09, $09, $07, $09, $09
ft_s27f27:
	.word ft_s27p11c0, ft_s27p1c1, ft_s22p0c2, ft_s27p3c3, ft_s22p20c4
	.byte $09, $09, $07, $09, $07
ft_s27f28:
	.word ft_s27p12c0, ft_s27p7c1, ft_s22p0c2, ft_s27p4c3, ft_s27p15c4
	.byte $09, $09, $07, $09, $09
ft_s27f29:
	.word ft_s27p5c0, ft_s27p3c1, ft_s22p0c2, ft_s27p3c3, ft_s22p9c4
	.byte $09, $09, $07, $09, $07
ft_s27f30:
	.word ft_s27p6c0, ft_s27p3c1, ft_s22p0c2, ft_s27p4c3, ft_s27p10c4
	.byte $09, $09, $07, $09, $09
ft_s27f31:
	.word ft_s27p7c0, ft_s27p1c1, ft_s22p0c2, ft_s27p3c3, ft_s22p20c4
	.byte $09, $09, $07, $09, $07
ft_s27f32:
	.word ft_s27p8c0, ft_s27p1c1, ft_s22p0c2, ft_s27p4c3, ft_s27p12c4
	.byte $09, $09, $07, $09, $09
ft_s27f33:
	.word ft_s27p9c0, ft_s27p6c1, ft_s22p0c2, ft_s27p3c3, ft_s27p13c4
	.byte $09, $09, $07, $09, $09
ft_s27f34:
	.word ft_s27p10c0, ft_s27p6c1, ft_s22p0c2, ft_s27p4c3, ft_s27p14c4
	.byte $09, $09, $07, $09, $09
ft_s27f35:
	.word ft_s27p11c0, ft_s27p1c1, ft_s22p0c2, ft_s27p3c3, ft_s22p20c4
	.byte $09, $09, $07, $09, $07
ft_s27f36:
	.word ft_s27p12c0, ft_s27p7c1, ft_s22p0c2, ft_s27p4c3, ft_s27p15c4
	.byte $09, $09, $07, $09, $09
ft_s27f37:
	.word ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s22p0c2, ft_s27p16c4
	.byte $07, $07, $07, $07, $09
; Bank 9
ft_s27p1c0:
	.byte $EE, $F9, $1C, $01, $1F, $01, $21, $01, $24, $05, $24, $03, $23, $01, $23, $01, $23, $01, $23, $05
	.byte $23, $03

; Bank 9
ft_s27p1c1:
	.byte $82, $01, $E5, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, $83, $11
	.byte $01

; Bank 9
ft_s27p1c4:
	.byte $82, $01, $07, $07, $07, $07, $07, $07, $07, $07, $07, $07, $07, $07, $07, $07, $07, $83, $07, $01

; Bank 9
ft_s27p2c0:
	.byte $EE, $1C, $01, $1F, $01, $21, $01, $24, $05, $23, $03, $23, $05, $23, $01, $23, $03, $29, $01, $29
	.byte $01

; Bank 9
ft_s27p2c1:
	.byte $82, $01, $E5, $13, $13, $13, $13, $13, $13, $13, $13, $13, $13, $13, $13, $13, $13, $13, $83, $13
	.byte $01

; Bank 9
ft_s27p2c4:
	.byte $82, $01, $09, $09, $09, $09, $09, $09, $09, $09, $09, $09, $09, $09, $09, $09, $09, $83, $09, $01

; Bank 9
ft_s27p3c0:
	.byte $EE, $29, $05, $28, $05, $28, $03, $28, $05, $21, $05, $21, $03

; Bank 9
ft_s27p3c1:
	.byte $82, $01, $E5, $15, $15, $15, $15, $15, $15, $15, $15, $15, $15, $15, $15, $15, $15, $15, $83, $15
	.byte $01

; Bank 9
ft_s27p3c3:
	.byte $82, $01, $E7, $11, $E9, $1F, $1D, $1F, $E8, $11, $E9, $1F, $1D, $1F, $E7, $11, $E9, $1F, $1D, $1F
	.byte $E8, $11, $E9, $1F, $1D, $83, $1F, $01

; Bank 9
ft_s27p3c4:
	.byte $82, $01, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $0B, $83, $0B, $01

; Bank 9
ft_s27p4c0:
	.byte $EE, $1F, $05, $1F, $05, $82, $03, $21, $23, $24, $23, $83, $24, $03

; Bank 9
ft_s27p4c3:
	.byte $82, $01, $E7, $11, $E9, $1F, $1D, $1F, $E8, $11, $E9, $1F, $1D, $1F, $E7, $11, $E9, $1F, $E8, $11
	.byte $E9, $1F, $E8, $11, $E9, $1F, $E8, $11, $83, $11, $01

; Bank 9
ft_s27p4c4:
	.byte $1D, $00, $07, $00, $07, $01, $07, $01, $07, $01, $1D, $00, $07, $00, $07, $01, $07, $01, $07, $01
	.byte $1D, $00, $07, $00, $07, $01, $07, $01, $07, $01, $1D, $00, $07, $00, $07, $01, $07, $01, $07, $01

; Bank 9
ft_s27p5c0:
	.byte $EE, $28, $05, $28, $05, $23, $03, $24, $05, $24, $05, $2B, $03

; Bank 9
ft_s27p5c4:
	.byte $1D, $00, $09, $00, $09, $01, $09, $01, $09, $01, $1D, $00, $09, $00, $09, $01, $09, $01, $09, $01
	.byte $1D, $00, $09, $00, $09, $01, $09, $01, $09, $01, $1D, $00, $09, $00, $09, $01, $09, $01, $09, $01

; Bank 9
ft_s27p6c0:
	.byte $EE, $28, $05, $28, $05, $23, $03, $24, $05, $24, $05, $28, $01, $2B, $01

; Bank 9
ft_s27p6c1:
	.byte $82, $01, $E5, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $0E, $83, $0E
	.byte $01

; Bank 9
ft_s27p6c4:
	.byte $1D, $00, $0B, $00, $0B, $01, $0B, $01, $0B, $01, $1D, $00, $0B, $00, $0B, $01, $0B, $01, $0B, $01
	.byte $1D, $00, $0B, $00, $0B, $01, $0B, $01, $0B, $01, $1D, $00, $0B, $00, $0B, $01, $0B, $01, $0B, $01

; Bank 9
ft_s27p7c0:
	.byte $EE, $2D, $05, $2D, $05, $2B, $03, $24, $05, $24, $05, $23, $01, $24, $01

; Bank 9
ft_s27p7c1:
	.byte $82, $01, $E5, $10, $10, $10, $10, $10, $10, $10, $10, $10, $10, $10, $10, $10, $10, $10, $83, $10
	.byte $01

; Bank 9
ft_s27p7c4:
	.byte $82, $00, $1D, $0B, $1D, $0B, $1D, $0B, $1D, $1D, $1D, $0B, $1D, $0B, $1D, $0B, $1D, $1D, $1D, $0B
	.byte $1D, $0B, $1D, $0B, $1D, $1D, $1D, $0B, $1D, $0B, $1D, $0B, $1D, $83, $1D, $00

; Bank 9
ft_s27p8c0:
	.byte $EE, $2D, $05, $2D, $05, $2B, $03, $24, $05, $24, $05, $24, $01, $28, $01

; Bank 9
ft_s27p8c4:
	.byte $82, $00, $83, $00

; Bank 9
ft_s27p9c0:
	.byte $EE, $29, $05, $29, $05, $28, $03, $21, $05, $21, $05, $28, $03

; Bank 9
ft_s27p10c0:
	.byte $EE, $29, $05, $29, $05, $28, $03, $2D, $05, $2D, $05, $28, $03

; Bank 9
ft_s27p10c4:
	.byte $82, $01, $1D, $0B, $0B, $0B, $1E, $0B, $0B, $0B, $1D, $0B, $1E, $0B, $1E, $0B, $1E, $83, $1E, $01

; Bank 9
ft_s27p11c0:
	.byte $EE, $21, $05, $21, $05, $1F, $03, $21, $05, $21, $05, $1F, $03

; Bank 9
ft_s27p12c0:
	.byte $EE, $23, $05, $23, $05, $21, $03, $23, $03, $30, $01, $2F, $03, $2D, $01, $2C, $02, $93, $03, $00
	.byte $00

; Bank 9
ft_s27p12c4:
	.byte $82, $01, $1D, $07, $07, $07, $1E, $07, $07, $07, $1D, $07, $1E, $07, $1E, $07, $1E, $83, $1E, $01

; Bank 9
ft_s27p13c4:
	.byte $82, $01, $1D, $04, $04, $04, $1E, $04, $04, $04, $1D, $04, $04, $04, $1E, $04, $04, $83, $04, $01

; Bank 9
ft_s27p14c4:
	.byte $82, $01, $1D, $04, $04, $04, $1E, $04, $04, $04, $1D, $04, $1E, $04, $1E, $04, $1E, $83, $1E, $01

; Bank 9
ft_s27p15c4:
	.byte $82, $01, $1D, $06, $06, $06, $1E, $06, $06, $06, $1D, $06, $1E, $06, $1E, $06, $1E, $83, $1E, $01

; Bank 9
ft_s27p16c4:
	.byte $88, $00, $00, $1F

; Bank 9
ft_s28_frames:
	.word ft_s28f0
	.word ft_s28f1
	.word ft_s28f2
	.word ft_s28f3
	.word ft_s28f4
	.word ft_s28f5
	.word ft_s28f6
	.word ft_s28f7
	.word ft_s28f8
	.word ft_s28f9
	.word ft_s28f10
	.word ft_s28f11
	.word ft_s28f12
	.word ft_s28f13
	.word ft_s28f14
	.word ft_s28f15
	.word ft_s28f16
	.word ft_s28f17
	.word ft_s28f18
ft_s28f0:
	.word ft_s28p1c0, ft_s28p1c1, ft_s0p0c0, ft_s0p0c0, ft_s0p0c0
	.byte $09, $09, $03, $03, $03
ft_s28f1:
	.word ft_s28p2c0, ft_s28p2c1, ft_s0p0c0, ft_s0p0c0, ft_s0p0c0
	.byte $09, $09, $03, $03, $03
ft_s28f2:
	.word ft_s28p1c0, ft_s28p1c1, ft_s28p1c2, ft_s28p1c3, ft_s28p1c4
	.byte $09, $09, $09, $09, $09
ft_s28f3:
	.word ft_s28p2c0, ft_s28p2c1, ft_s28p1c2, ft_s28p1c3, ft_s28p1c4
	.byte $09, $09, $09, $09, $09
ft_s28f4:
	.word ft_s28p1c0, ft_s28p1c1, ft_s28p1c2, ft_s28p2c3, ft_s28p2c4
	.byte $09, $09, $09, $09, $09
ft_s28f5:
	.word ft_s28p2c0, ft_s28p2c1, ft_s28p1c2, ft_s28p2c3, ft_s28p2c4
	.byte $09, $09, $09, $09, $09
ft_s28f6:
	.word ft_s28p1c0, ft_s28p1c1, ft_s28p1c2, ft_s28p2c3, ft_s28p4c4
	.byte $09, $09, $09, $09, $09
ft_s28f7:
	.word ft_s28p2c0, ft_s28p2c1, ft_s28p1c2, ft_s28p2c3, ft_s28p4c4
	.byte $09, $09, $09, $09, $09
ft_s28f8:
	.word ft_s28p1c0, ft_s28p1c1, ft_s28p1c2, ft_s28p3c3, ft_s28p4c4
	.byte $09, $09, $09, $09, $09
ft_s28f9:
	.word ft_s28p2c0, ft_s28p2c1, ft_s28p1c2, ft_s28p3c3, ft_s28p3c4
	.byte $09, $09, $09, $09, $09
ft_s28f10:
	.word ft_s28p3c0, ft_s28p3c1, ft_s0p0c0, ft_s28p4c3, ft_s0p0c0
	.byte $09, $09, $03, $09, $03
ft_s28f11:
	.word ft_s28p4c0, ft_s28p4c1, ft_s28p1c2, ft_s28p3c3, ft_s28p4c4
	.byte $09, $09, $09, $09, $09
ft_s28f12:
	.word ft_s28p5c0, ft_s28p5c1, ft_s28p1c2, ft_s28p3c3, ft_s28p4c4
	.byte $09, $09, $09, $09, $09
ft_s28f13:
	.word ft_s28p6c0, ft_s28p6c1, ft_s28p2c2, ft_s28p3c3, ft_s28p5c4
	.byte $09, $09, $09, $09, $09
ft_s28f14:
	.word ft_s28p7c0, ft_s28p7c1, ft_s28p2c2, ft_s28p3c3, ft_s28p6c4
	.byte $09, $09, $09, $09, $09
ft_s28f15:
	.word ft_s28p4c0, ft_s28p4c1, ft_s28p1c2, ft_s28p3c3, ft_s28p4c4
	.byte $09, $09, $09, $09, $09
ft_s28f16:
	.word ft_s28p5c0, ft_s28p5c1, ft_s28p1c2, ft_s28p3c3, ft_s28p4c4
	.byte $09, $09, $09, $09, $09
ft_s28f17:
	.word ft_s28p6c0, ft_s28p6c1, ft_s28p2c2, ft_s28p3c3, ft_s28p5c4
	.byte $09, $09, $09, $09, $09
ft_s28f18:
	.word ft_s28p7c0, ft_s28p7c1, ft_s28p2c2, ft_s28p3c3, ft_s28p6c4
	.byte $09, $09, $09, $09, $09
; Bank 9
ft_s28p1c0:
	.byte $82, $00, $80, $22, $FA, $16, $7F, $16, $7F, $16, $7F, $16, $7F, $80, $20, $16, $7F, $16, $7F, $16
	.byte $7F, $16, $7F, $83, $EF, $16, $01, $7F, $01, $82, $00, $16, $7F, $16, $7F, $82, $01, $80, $20, $16
	.byte $7F, $16, $7F, $82, $00, $80, $22, $16, $7F, $16, $7F, $82, $01, $16, $7F, $80, $20, $16, $7F, $16
	.byte $7F, $EF, $16, $7F, $16, $7F, $82, $00, $80, $20, $16, $7F, $16, $7F, $83, $11, $01, $19, $01

; Bank 9
ft_s28p1c1:
	.byte $91, $7E, $00, $02, $82, $01, $EF, $F3, $16, $16, $16, $16, $80, $20, $16, $16, $16, $16, $80, $22
	.byte $16, $00, $16, $16, $80, $20, $16, $00, $16, $00, $EF, $16, $16, $16, $00, $80, $20, $16, $00, $16
	.byte $00, $80, $22, $16, $00, $16, $00, $80, $20, $16, $16, $83, $11, $00

; Bank 9
ft_s28p1c2:
	.byte $82, $03, $7F, $E0, $2E, $7F, $2E, $7F, $2E, $7F, $2E, $7F, $2E, $7F, $2E, $7F, $2E, $7F, $83, $2E
	.byte $03

; Bank 9
ft_s28p1c3:
	.byte $82, $07, $E7, $11, $11, $11, $11, $11, $11, $11, $83, $11, $07

; Bank 9
ft_s28p1c4:
	.byte $82, $07, $1D, $1D, $1D, $1D, $1D, $1D, $1D, $83, $1D, $07

; Bank 9
ft_s28p2c0:
	.byte $82, $01, $80, $22, $16, $7F, $16, $7F, $82, $00, $80, $20, $16, $7F, $16, $7F, $82, $01, $16, $7F
	.byte $EF, $16, $7F, $82, $00, $16, $7F, $16, $7F, $80, $20, $16, $7F, $16, $7F, $82, $01, $11, $19, $80
	.byte $22, $16, $7F, $16, $7F, $82, $00, $80, $20, $16, $7F, $16, $7F, $82, $01, $11, $19, $EF, $16, $7F
	.byte $82, $00, $16, $7F, $19, $7F, $82, $01, $80, $20, $1D, $00, $11, $83, $00, $01

; Bank 9
ft_s28p2c1:
	.byte $00, $00, $82, $01, $80, $20, $19, $EF, $16, $00, $16, $00, $80, $20, $16, $16, $16, $00, $80, $22
	.byte $16, $00, $16, $16, $80, $20, $16, $16, $11, $19, $EF, $16, $00, $16, $00, $80, $20, $16, $16, $11
	.byte $19, $80, $22, $16, $00, $16, $19, $80, $20, $1D, $00, $83, $11, $00

; Bank 9
ft_s28p2c2:
	.byte $82, $03, $7F, $E0, $2A, $7F, $2A, $7F, $2A, $7F, $2A, $7F, $2A, $7F, $2A, $7F, $2A, $7F, $83, $2A
	.byte $03

; Bank 9
ft_s28p2c3:
	.byte $82, $03, $E7, $11, $EA, $1C, $E8, $12, $EA, $1C, $E7, $11, $EA, $1C, $E8, $12, $EA, $1C, $E7, $11
	.byte $EA, $1C, $E8, $12, $EA, $1C, $E7, $11, $EA, $1C, $E8, $12, $83, $EA, $1C, $03

; Bank 9
ft_s28p2c4:
	.byte $82, $07, $1D, $1E, $1D, $1E, $1D, $1E, $1D, $83, $1E, $07

; Bank 9
ft_s28p3c0:
	.byte $EF, $16, $0F, $22, $07, $8F, $FF, $00, $06, $8F, $00, $00, $20

; Bank 9
ft_s28p3c1:
	.byte $00, $02, $EF, $F3, $16, $0F, $22, $0B, $87, $01, $00, $20

; Bank 9
ft_s28p3c3:
	.byte $82, $01, $E7, $11, $E9, $1D, $EA, $1C, $E9, $1D, $E8, $12, $E9, $1D, $EA, $1C, $E9, $1D, $E7, $11
	.byte $E9, $1D, $EA, $1C, $E9, $1D, $E8, $12, $E9, $1D, $EA, $1C, $E9, $1D, $E7, $11, $E9, $1D, $EA, $1C
	.byte $E9, $1D, $E8, $12, $E9, $1D, $EA, $1C, $E9, $1D, $E7, $11, $E9, $1D, $EA, $1C, $E9, $1D, $E8, $12
	.byte $E9, $1D, $EA, $1C, $83, $E9, $1D, $01

; Bank 9
ft_s28p3c4:
	.byte $82, $03, $1D, $0C, $1E, $0C, $1D, $0C, $1E, $0C, $82, $00, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E
	.byte $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E
	.byte $1E, $1E, $1E, $83, $1E, $00

; Bank 9
ft_s28p4c0:
	.byte $EF, $16, $00, $7F, $00, $82, $01, $16, $7F, $16, $7F, $16, $7F, $16, $7F, $16, $7F, $83, $19, $00
	.byte $7F, $00, $1D, $03, $11, $03, $80, $20, $16, $00, $7F, $00, $82, $01, $16, $7F, $16, $7F, $16, $7F
	.byte $16, $7F, $16, $7F, $83, $19, $00, $7F, $00, $1D, $03, $11, $03

; Bank 9
ft_s28p4c1:
	.byte $F3, $00, $02, $EF, $16, $01, $82, $03, $16, $16, $16, $16, $16, $83, $19, $01, $1D, $03, $11, $03
	.byte $80, $20, $16, $01, $82, $03, $16, $16, $16, $16, $16, $83, $19, $01, $1D, $03, $11, $00

; Bank 9
ft_s28p4c3:
	.byte $7F, $0F, $82, $01, $80, $20, $F1, $17, $F2, $00, $F3, $00, $F4, $00, $F5, $00, $82, $00, $F6, $00
	.byte $F7, $00, $F8, $00, $FA, $00, $FC, $00, $83, $FF, $00, $20

; Bank 9
ft_s28p4c4:
	.byte $82, $03, $1D, $0C, $1E, $0C, $1D, $0C, $1E, $0C, $1D, $0C, $1E, $0C, $1D, $0C, $1E, $83, $0C, $03

; Bank 9
ft_s28p5c0:
	.byte $EF, $16, $00, $7F, $00, $82, $01, $16, $7F, $16, $7F, $16, $7F, $16, $7F, $16, $7F, $83, $19, $00
	.byte $7F, $00, $1D, $03, $11, $03, $80, $20, $16, $00, $7F, $00, $82, $01, $16, $7F, $16, $7F, $16, $7F
	.byte $16, $7F, $16, $7F, $83, $19, $00, $7F, $00, $1E, $03, $1D, $03

; Bank 9
ft_s28p5c1:
	.byte $00, $02, $EF, $16, $01, $82, $03, $16, $16, $16, $16, $16, $83, $19, $01, $1D, $03, $11, $03, $80
	.byte $20, $16, $01, $82, $03, $16, $16, $16, $16, $16, $83, $19, $01, $1E, $03, $1D, $00

; Bank 9
ft_s28p5c4:
	.byte $82, $03, $1D, $08, $1E, $08, $1D, $08, $1E, $08, $1D, $08, $1E, $08, $1D, $08, $1E, $83, $08, $03

; Bank 9
ft_s28p6c0:
	.byte $EF, $19, $03, $12, $01, $7F, $01, $12, $00, $7F, $00, $82, $01, $19, $7F, $12, $7F, $19, $7F, $83
	.byte $19, $00, $7F, $00, $1D, $03, $19, $03, $80, $20, $12, $00, $7F, $00, $82, $01, $19, $7F, $12, $7F
	.byte $19, $7F, $12, $7F, $19, $7F, $12, $83, $1D, $03, $19, $03

; Bank 9
ft_s28p6c1:
	.byte $00, $02, $EF, $19, $03, $12, $03, $12, $01, $19, $03, $12, $03, $19, $03, $19, $01, $1D, $03, $19
	.byte $03, $80, $20, $12, $01, $82, $03, $19, $12, $19, $12, $19, $83, $12, $01, $1D, $03, $19, $00

; Bank 9
ft_s28p6c4:
	.byte $82, $03, $1D, $08, $1E, $08, $1D, $08, $1E, $08, $1D, $08, $1E, $08, $82, $00, $1E, $1E, $1E, $1E
	.byte $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $1E, $83, $1E, $00

; Bank 9
ft_s28p7c0:
	.byte $EF, $19, $03, $12, $01, $7F, $01, $12, $00, $7F, $00, $82, $01, $19, $7F, $12, $7F, $19, $7F, $83
	.byte $19, $00, $7F, $00, $1D, $03, $19, $03, $80, $20, $12, $00, $7F, $00, $82, $01, $12, $7F, $12, $7F
	.byte $19, $7F, $12, $7F, $12, $7F, $19, $83, $1D, $03, $22, $03

; Bank 9
ft_s28p7c1:
	.byte $00, $02, $EF, $19, $03, $12, $03, $12, $01, $19, $03, $12, $03, $19, $03, $19, $01, $1D, $03, $19
	.byte $03, $80, $20, $12, $01, $82, $03, $12, $12, $19, $12, $19, $83, $16, $01, $1D, $03, $22, $00

; Bank 9
ft_s29_frames:
	.word ft_s29f0
ft_s29f0:
	.word ft_s0p0c2, ft_s29p0c1, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $09, $03, $03, $03
; Bank 9
ft_s29p0c1:
	.byte $82, $00, $80, $22, $93, $02, $30, $37, $3C, $3B, $7F, $37, $83, $7F, $39

; Bank 9
ft_s30_frames:
	.word ft_s30f0
ft_s30f0:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03
; Bank 9
ft_s31_frames:
	.word ft_s31f0
ft_s31f0:
	.word ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2, ft_s0p0c2
	.byte $03, $03, $03, $03, $03

; DPCM samples (located at DPCM segment)

	.segment "DPCM"
ft_sample_0: ; ripped00.dmc
	.byte $BB, $04, $58, $5B, $FB, $0F, $40, $FF, $7F, $F5, $00, $00, $00, $00, $FF, $FF, $0A, $05, $F0, $FF
	.byte $4F, $0F, $A0, $BF, $04, $F5, $BA, $F0, $0F, $00, $F7, $F7, $FF, $00, $58, $04, $FF, $00, $50, $FF
	.byte $F4, $57, $00, $00, $00, $00, $FF, $FF, $A5, $0A, $FA, $FF, $77, $00, $F8, $7F, $00, $FF, $4A, $BF
	.byte $00, $A0, $FF, $FF, $FF, $00, $40, $05, $FF, $00, $F0, $0F, $F8, $8F, $00, $00, $00, $F0, $FF, $BF
	.byte $50, $00, $FF, $FF, $F7, $00, $F8, $AF, $80, $BF, $0A, $FF, $00, $B0, $FF, $FF, $0F, $04, $54, $0A
	.byte $FF, $00, $F0, $5F, $70, $0F, $00, $00, $00, $F0, $FF, $BF, $A8, $40, $FF, $FF, $7B, $00, $F4, $8F
	.byte $B0, $B7, $04, $FF, $00, $F0, $FF, $FF, $0F, $00, $55, $08, $FF, $00, $F0, $5F, $F0, $0F, $00, $00
	.byte $00, $FF, $FF, $85, $44, $B0, $FF, $FF, $55, $00, $FB, $0B, $74, $B7, $88, $FF, $00, $F0, $FF, $FF
	.byte $8F, $00, $A0, $40, $FF, $00, $F4, $8F, $F4, $0A, $00, $00, $00, $FF, $FF, $0B, $8A, $58, $FF, $FF
	.byte $0B, $40, $F7, $85, $5A, $B7, $70, $BF, $00, $F0, $FF, $FF, $0F, $00, $48, $58, $AF, $00, $F7, $8B
	.byte $B5, $04, $00, $00, $00, $FF, $FF, $8F, $08, $7A, $FF, $FF, $84, $A0, $BB, $8A, $BA, $55, $BA, $A7
	.byte $00, $F5, $FF, $FF, $0B, $00, $40, $7A, $8B, $40, $7F, $55, $4B, $04, $00, $00, $A0, $FF, $FF, $8B
	.byte $40, $F5, $FF, $BF, $08, $54, $BB, $54, $B5, $A5, $75, $4B, $40, $7B, $FF, $FF, $05, $00, $44, $75
	.byte $45, $54, $B7, $55, $4B, $08, $00, $00, $B0, $FF, $FF, $8A, $A0, $FA, $FF, $57, $0A, $54, $5B, $55
	.byte $B5, $AA, $5B, $A5, $A0, $75, $FF, $FF, $84, $00, $44, $B5, $8A, $B4, $B5, $5A, $A5, $00, $00, $00
	.byte $F4, $FF, $BF, $8A, $88, $F5, $FF, $AB, $44, $AA, $5A, $55, $AB, $5A, $5B, $4A, $4A, $BB, $FF, $5F
	.byte $0A, $08, $44, $AB, $A4, $AA, $55, $5B, $45, $08, $00, $00, $75, $FF, $BF, $A4, $A8, $F5, $77, $57
	.byte $45, $55, $55, $55, $AB, $5A, $5B, $4A, $AA, $75, $FF, $B7, $44, $08, $A4, $4A, $4A, $AB, $55, $5B
	.byte $8A, $80, $00, $80, $7A, $7F, $77, $A5, $54, $7B, $77, $57, $4A, $55, $55, $55, $AB, $5A, $AB, $A4
	.byte $AA, $F5, $F7, $5B, $8A, $08, $4A, $4A, $AA, $AA, $55, $AB, $44, $04, $08, $40, $BB, $7B, $B7, $AA
	.byte $B4, $75, $77, $AB, $AA, $54, $55, $55, $AB, $55, $AB, $A4, $5A, $BB, $F7, $B5, $44, $8A, $48, $4A
	.byte $AA, $AA, $55, $AB, $88, $08, $80, $A0, $75, $77, $BB, $AA, $5A, $BB, $5B, $B5, $AA, $54, $55, $55
	.byte $AB, $B5, $AA, $A4, $55, $77, $F7, $55, $4A, $A4, $44, $4A, $AA, $AA, $55, $55, $8A, $80, $80, $48
	.byte $5B, $77, $5B, $B5, $BA, $B5, $5B, $55, $55, $55, $55, $B5, $AA, $55, $4B, $55, $B5, $75, $5F, $AB
	.byte $A4, $A4, $44, $4A, $AA, $AA, $55, $A5, $44, $84, $80, $A4, $B5, $75, $5B, $B5, $B5, $75, $AB, $55
	.byte $55, $55, $55, $B5, $AA, $55, $55, $55, $B5, $BB, $75, $55, $A5, $A4, $44, $4A, $AA, $AA, $55, $A5
	.byte $88, $08, $44, $54, $5B, $5B, $AB, $B5, $75, $5B, $AB, $55, $55, $55, $55, $B5, $5A, $55, $55, $55
	.byte $5B, $BB, $5B, $55, $4A, $AA, $48, $4A, $A5, $AA, $AA, $4A, $A4, $40, $44, $AA, $5A, $5B, $AB, $B5
	.byte $5B, $5B, $AB, $55, $55, $55, $55, $B5, $5A, $55, $55, $55, $5B, $B7, $B5, $A5, $4A, $4A, $4A, $4A
	.byte $A5, $AA, $AA, $A4, $44, $84, $44, $55, $B5, $5A, $AB, $75, $5B, $5B, $AB, $55, $55, $55, $55, $AB
	.byte $5A, $55, $55, $55, $5B, $B7, $B5, $AA, $54, $4A, $4A, $4A, $A5, $AA, $AA, $A4, $88, $88, $A4, $54
	.byte $AB, $5A, $5B, $5B, $5B, $5B, $AB, $55, $55, $55, $B5, $AA, $5A, $55, $55, $B5, $B5, $B5, $B5, $4A
	.byte $A5, $4A, $4A, $4A, $55, $AA, $4A, $4A, $A4, $88, $A4, $AA, $AA, $55, $5B, $5B, $B7, $55, $AB, $55
	.byte $55, $55, $B5, $AA, $55, $55, $55, $B5, $B5, $B5, $55, $55, $A5, $54, $4A, $4A, $55, $AA, $4A, $8A
	.byte $44, $A4, $A4, $AA, $5A, $55, $5B, $BB, $B5, $55, $AB, $55, $55, $55, $AB, $AA, $55, $55, $55, $AB
	.byte $B5, $B5, $55, $55, $AA, $A4, $4A, $4A, $55, $AA, $A4, $A4, $48, $A4, $54, $55, $55, $B5, $B5, $B5
	.byte $B5, $55, $AB, $55, $55, $55, $AB, $AA, $55, $55, $55, $5B, $5B, $B5, $55, $A5, $4A, $A5, $54, $4A
	.byte $55, $AA, $A4, $44, $8A, $A4, $54, $55, $55, $AB, $B5, $B5, $B5, $55, $AB, $55, $55, $B5, $AA, $5A
	.byte $55, $55, $B5, $5A, $5B, $B5, $AA, $AA, $4A, $A5, $54, $4A, $55, $4A, $45, $4A, $A4, $A4, $54, $55
	.byte $55, $5B, $B5, $5B, $B5, $B5, $AA, $55, $55, $B5, $AA, $5A, $55, $55, $B5, $5A, $5B, $B5, $AA, $AA
	.byte $54, $AA, $A4, $4A, $A5, $4A, $4A, $8A, $A4, $A4, $4A, $55, $B5, $5A, $5B, $5B, $AB, $B5, $AA, $55
	.byte $55, $B5, $AA, $5A, $55, $55, $AB, $55, $5B, $B5, $AA, $AA, $54, $4A, $A5, $4A, $A5, $4A, $8A, $A4
	.byte $48, $A5, $AA, $54, $AB, $55, $5B, $5B, $5B, $B5, $AA, $55, $55, $AB, $AA, $5A, $55, $55, $AB, $B5
	.byte $5A, $B5, $AA, $4A, $A5, $4A, $A5, $4A, $A5, $A4, $A4, $44, $4A, $A5, $AA, $AA, $AA, $B5, $B5, $55
	.byte $5B, $B5, $AA, $55, $55, $AB, $AA, $55, $55, $55, $AB, $B5, $5A, $B5, $AA, $54, $A5, $4A, $AA, $54
	.byte $AA, $A4, $44, $4A, $4A, $A5, $AA, $AA, $5A, $B5, $B5, $B5, $5A, $B5, $5A, $55, $55, $AB, $AA, $55
	.byte $55, $B5, $5A, $B5, $5A, $55, $55, $55, $AA, $54, $AA, $54, $4A, $4A, $4A, $4A, $4A, $A5, $AA, $AA
	.byte $5A, $5B, $AB, $B5, $55, $AB, $5A, $55, $B5, $AA, $5A, $55, $55, $B5, $5A, $B5, $55, $55, $55, $A5
	.byte $AA, $54, $AA, $54, $4A, $4A, $4A, $A4, $4A, $A5, $AA, $AA, $55, $5B, $5B, $B5, $55, $AB, $5A, $55
	.byte $B5, $AA, $5A, $55, $55, $AB, $5A, $AB, $55, $55, $55, $A5, $4A, $A5, $4A, $A5, $54, $8A, $A4, $A4
	.byte $4A, $5A, $A5, $5A, $AA, $5A, $AA, $55, $A5

	.align 64

ft_sample_1: ; ripped01.dmc
	.byte $75, $0B, $50, $5B, $FF, $00, $F0, $FF, $F4, $4F, $00, $80, $00, $F0, $FF, $8F, $88, $B0, $FF, $8F
	.byte $0F, $A0, $BF, $00, $7F, $45, $FF, $00, $B0, $FF, $FF, $0F, $00, $A5, $F0, $0F, $00, $FF, $F4, $4B
	.byte $00, $00, $00, $F0, $FF, $8F, $48, $50, $FF, $FF, $0F, $80, $FF, $08, $FB, $54, $BF, $00, $B0, $FF
	.byte $FF, $0F, $00, $AB, $F0, $0F, $00, $FF, $0A, $7F, $00, $00, $00, $F0, $FF, $4B, $A8, $80, $FF, $FF
	.byte $0B, $40, $FF, $05, $F5, $55, $F0, $0F, $40, $FF, $FF, $0F, $0A, $AA, $F0, $0A, $00, $FF, $0F, $F5
	.byte $00, $00, $00, $F0, $FF, $4F, $A8, $80, $FF, $FF, $5B, $00, $F7, $05, $FA, $55, $F0, $0F, $00, $FF
	.byte $FF, $FF, $00, $B0, $00, $FF, $00, $FA, $0F, $F4, $0A, $00, $00, $70, $FF, $AF, $A0, $80, $F7, $FF
	.byte $5F, $00, $F5, $87, $78, $57, $B8, $BF, $00, $F4, $FF, $FF, $0A, $00, $0A, $F5, $0A, $F0, $4F, $7A
	.byte $05, $00, $00, $00, $FF, $FF, $8A, $08, $FB, $FF, $5F, $00, $F5, $47, $B4, $5B, $AA, $BF, $00, $F8
	.byte $FF, $FF, $0B, $00, $08, $F5, $05, $F0, $AF, $B4, $8A, $00, $00, $00, $FF, $FF, $0A, $84, $FA, $FF
	.byte $5F, $08, $74, $4F, $AA, $5B, $AA, $77, $08, $78, $FF, $FF, $0F, $00, $08, $F5, $05, $B8, $B7, $B4
	.byte $8A, $00, $00, $00, $F4, $FF, $5F, $08, $7A, $FF, $7F, $84, $58, $5B, $A5, $B5, $AA, $BB, $04, $B4
	.byte $F7, $FF, $4F, $00, $88, $74, $8B, $B0, $5B, $B5, $4A, $00, $00, $00, $FA, $FF, $AF, $40, $B4, $FF
	.byte $BF, $8A, $50, $AB, $5A, $B5, $AA, $5B, $85, $A8, $FB, $FF, $4F, $08, $40, $AA, $A5, $A8, $B5, $55
	.byte $4B, $08, $00, $00, $78, $FF, $BF, $84, $A8, $F7, $7F, $8B, $48, $AB, $AA, $B5, $AA, $75, $4A, $54
	.byte $7B, $FF, $5F, $84, $80, $A8, $A5, $A8, $B5, $5A, $4B, $04, $00, $00, $74, $FF, $5F, $45, $4A, $F7
	.byte $77, $A7, $A4, $AA, $AA, $55, $AB, $B5, $4A, $4A, $BB, $F7, $BF, $44, $84, $48, $AA, $A4, $55, $AB
	.byte $55, $84, $00, $00, $54, $7F, $BF, $A5, $A4, $75, $BF, $AB, $54, $A5, $AA, $55, $B5, $B5, $4A, $AA
	.byte $5A, $7F, $BF, $4A, $44, $A4, $A4, $A4, $55, $B5, $55, $44, $08, $00, $A8, $F5, $BB, $AB, $54, $5B
	.byte $77, $57, $55, $55, $AA, $55, $55, $5B, $4B, $A5, $5A, $F7, $77, $4B, $8A, $48, $8A, $54, $55, $B5
	.byte $AA, $8A, $80, $00, $48, $75, $77, $57, $55, $5B, $B7, $5B, $55, $55, $55, $55, $55, $5B, $55, $A5
	.byte $5A, $77, $F7, $55, $8A, $A4, $48, $4A, $55, $55, $AB, $A4, $08, $08, $88, $5A, $B7, $5B, $55, $5B
	.byte $BB, $B5, $5A, $55, $55, $55, $55, $5B, $55, $55, $5A, $BB, $BB, $AB, $4A, $A4, $A4, $44, $55, $55
	.byte $B5, $A4, $88, $80, $40, $55, $BB, $B5, $5A, $5B, $BB, $B5, $AA, $55, $55, $55, $55, $AB, $55, $55
	.byte $55, $BB, $5B, $57, $55, $4A, $8A, $A4, $54, $55, $55, $A5, $84, $08, $48, $AA, $5A, $5B, $5B, $5B
	.byte $5B, $5B, $AB, $5A, $55, $55, $55, $AB, $55, $55, $55, $5B, $77, $5B, $A5, $4A, $4A, $4A, $4A, $55
	.byte $55, $A5, $44, $84, $88, $54, $55, $5B, $AB, $B5, $5B, $5B, $AB, $AA, $55, $55, $55, $AB, $5A, $55
	.byte $55, $5B, $BB, $B5, $AA, $4A, $4A, $4A, $AA, $54, $55, $A5, $44, $44, $44, $4A, $B5, $5A, $B5, $B5
	.byte $75, $5B, $B5, $AA, $55, $55, $55, $B5, $5A, $55, $55, $B5, $5B, $57, $AB, $4A, $AA, $A4, $A4, $54
	.byte $55, $A5, $44, $0A, $A4, $A8, $AA, $5A, $B5, $B5, $B5, $B5, $B5, $AA, $55, $55, $55, $B5, $5A, $55
	.byte $55, $B5, $75, $5B, $B5, $54, $A5, $A4, $A4, $4A, $55, $A5, $A4, $88, $88, $A4, $AA, $5A, $B5, $5A
	.byte $B7, $B5, $55, $AB, $5A, $55, $55, $B5, $AA, $55, $55, $B5, $B5, $B5, $55, $55, $AA, $A4, $4A, $AA
	.byte $54, $A5, $A4, $88, $44, $4A, $A5, $55, $55, $5B, $BB, $B5, $5A, $AB, $AA, $55, $55, $B5, $AA, $55
	.byte $55, $B5, $B5, $B5, $55, $55, $AA, $54, $4A, $AA, $54, $A5, $A4, $44, $A4, $48, $55, $55, $55, $5B
	.byte $5B, $5B, $5B, $B5, $AA, $55, $55, $B5, $AA, $55, $55, $B5, $B5, $B5, $5A, $55, $AA, $54, $4A, $A5
	.byte $4A, $A5, $A4, $44, $A4, $A4, $54, $55, $55, $5B, $5B, $5B, $5B, $B5, $AA, $55, $55, $B5, $AA, $5A
	.byte $55, $B5, $5A, $5B, $AB, $AA, $AA, $54, $4A, $A5, $4A, $A5, $A4, $44, $8A, $A4, $4A, $55, $B5, $5A
	.byte $5B, $5B, $AB, $55, $AB, $5A, $55, $B5, $AA, $5A, $55, $B5, $5A, $5B, $AB, $AA, $AA, $54, $AA, $A4
	.byte $4A, $A5, $8A, $A4, $48, $4A, $AA, $4A, $B5, $5A, $5B, $5B, $B5, $55, $AB, $5A, $55, $55, $AB, $5A
	.byte $55, $B5, $5A, $AB, $B5, $AA, $AA, $54, $AA, $54, $AA, $A4, $4A, $A4, $44, $4A, $AA, $AA, $AA, $5A
	.byte $5B, $AB, $B5, $55, $AB, $5A, $55, $55, $AB, $5A, $55, $55, $5B, $B5, $55, $AB, $AA, $54, $AA, $54
	.byte $AA, $54, $4A, $8A, $44, $4A, $A5, $AA, $AA, $5A, $B5, $B5, $B5, $5A, $B5, $AA, $55, $55, $AB, $5A
	.byte $55, $55, $5B, $B5, $55, $B5, $AA, $54, $AA, $54, $AA, $54, $4A, $8A, $A4, $A4, $54, $AA, $AA, $5A
	.byte $B5, $B5, $B5, $5A, $B5, $AA, $55, $55, $AB, $5A, $55, $55, $AB, $B5, $5A, $55, $55, $55, $AA, $54
	.byte $AA, $54, $4A, $4A, $A4, $A4, $54, $AA, $AA, $5A, $B5, $B5, $B5, $5A, $B5, $AA, $55, $55, $AB, $AA
	.byte $55, $55, $AB, $B5, $5A, $55, $55, $55, $AA, $54, $AA, $54, $4A, $4A, $8A, $A4, $4A, $A5, $AA, $5A
	.byte $AB, $B5, $55, $5B, $B5, $AA, $5A, $55, $AB, $AA, $55, $55, $AB, $55, $AB, $55, $55, $55, $AA, $54
	.byte $A5, $4A, $4A, $4A, $4A, $54, $4A, $55, $AA, $55, $AB, $B5, $55, $5B, $55, $AB, $5A, $55, $AB, $AA
	.byte $55, $55, $AB, $55, $AB, $55, $55, $55, $AA, $54, $A5, $4A, $4A, $4A, $4A, $4A, $4A, $55, $55, $55
	.byte $AB, $B5, $55, $AB, $55, $AB, $5A, $55, $AB, $AA, $55, $55, $AB

	.align 64

ft_sample_2: ; ripped04.dmc
	.byte $B5, $0B, $50, $5B, $FF, $00, $F8, $4F, $FF, $0F, $00, $00, $00, $FF, $BF, $A0, $00, $FF, $FF, $0B
	.byte $40, $FF, $00, $BF, $05, $FF, $00, $FA, $FF, $FF, $00, $A8, $08, $FF, $00, $FB, $0A, $5F, $00, $00
	.byte $00, $F0, $FF, $45, $0A, $F4, $FF, $FF, $00, $FB, $05, $FA, $A5, $BF, $00, $F0, $FF, $FF, $0F, $00
	.byte $05, $FF, $00, $AF, $0F, $AF, $00, $00, $00, $F0, $FF, $0A, $0A, $70, $FF, $FF, $07, $F0, $A7, $B0
	.byte $57, $F4, $0F, $00, $FF, $FF, $0F, $0A, $A5, $F0, $0F, $F0, $05, $74, $8F, $00, $00, $00, $FF, $5F
	.byte $A8, $00, $FF, $FF, $B7, $00, $7F, $08, $7F, $85, $FF, $00, $F0, $FF, $FF, $80, $B0, $04, $F7, $00
	.byte $F5, $0F, $FB, $00, $00, $00, $F0, $FF, $85, $04, $FA, $FF, $BF, $00, $FA, $07, $7A, $A7, $F8, $0F
	.byte $00, $FF, $FF, $0F, $08, $8B, $F0, $0F, $50, $BF, $70, $0B, $00, $00, $B0, $FF, $0F, $88, $50, $FF
	.byte $FF, $0B, $50, $BF, $50, $77, $4A, $FF, $00, $F8, $FF, $FF, $04, $40, $44, $BF, $00, $FF, $A4, $55
	.byte $00, $00, $00, $BF, $FF, $84, $40, $FB, $FF, $4F, $80, $7B, $45, $5B, $4B, $FB, $0A, $50, $FF, $FF
	.byte $8F, $00, $88, $FA, $04, $F4, $A7, $55, $0A, $00, $00, $40, $FF, $7F, $08, $74, $FF, $FF, $08, $B4
	.byte $AB, $AA, $B5, $5A, $4F, $40, $FB, $FF, $FF, $00, $80, $58, $47, $A8, $B7, $5A, $45, $00, $00, $00
	.byte $F7, $FF, $45, $A0, $FB, $FF, $8B, $A0, $B5, $AA, $55, $AB, $5B, $0A, $5A, $FF, $FF, $0B, $80, $A0
	.byte $B5, $48, $75, $B5, $A5, $08, $00, $00, $F0, $FF, $57, $84, $74, $FF, $5F, $8A, $54, $B5, $5A, $55
	.byte $BB, $4A, $54, $7B, $FF, $5F, $84, $80, $54, $A5, $B4, $5A, $AB, $44, $00, $00, $A0, $F7, $7F, $45
	.byte $A4, $F7, $77, $4B, $4A, $55, $AB, $55, $5B, $AB, $A4, $B4, $F7, $FF, $8A, $08, $A8, $A4, $54, $AB
	.byte $B5, $4A, $08, $00, $00, $F5, $F7, $AB, $A4, $BA, $7B, $57, $A5, $AA, $AA, $5A, $B5, $B5, $A4, $AA
	.byte $F5, $7F, $57, $44, $44, $4A, $4A, $B5, $5A, $55, $0A, $08, $00, $A8, $77, $5F, $55, $5A, $77, $B7
	.byte $55, $AA, $AA, $AA, $55, $5B, $4B, $AA, $BA, $FB, $BB, $4A, $44, $A4, $A4, $54, $AB, $55, $45, $04
	.byte $08, $40, $75, $77, $5B, $55, $5B, $77, $AB, $AA, $AA, $AA, $55, $B5, $55, $A5, $5A, $7B, $BF, $55
	.byte $4A, $A4, $44, $4A, $B5, $5A, $A5, $88, $00, $08, $AA, $5B, $B7, $AA, $B5, $5B, $57, $AB, $AA, $AA
	.byte $5A, $55, $5B, $55, $AA, $75, $F7, $B5, $4A, $4A, $4A, $A4, $4A, $AB, $AA, $8A, $80, $80, $48, $B5
	.byte $75, $B5, $B5, $B5, $5B, $B5, $AA, $AA, $AA, $55, $AB, $55, $A5, $B5, $75, $5F, $AB, $A4, $A4, $44
	.byte $AA, $AA, $AA, $4A, $44, $08, $88, $AA, $B5, $55, $5B, $5B, $B7, $55, $AB, $AA, $AA, $55, $B5, $5A
	.byte $55, $5A, $BB, $5B, $57, $55, $4A, $4A, $54, $AA, $AA, $4A, $8A, $08, $84, $A4, $55, $AB, $B5, $B5
	.byte $5B, $5B, $55, $AB, $AA, $5A, $55, $AB, $55, $55, $B5, $BB, $B5, $55, $4A, $A5, $A4, $A4, $AA, $4A
	.byte $A5, $88, $80, $A4, $54, $AB, $5A, $5B, $BB, $B5, $55, $B5, $AA, $5A, $55, $B5, $5A, $55, $55, $B7
	.byte $5B, $AB, $AA, $54, $4A, $4A, $AA, $AA, $A4, $44, $44, $48, $AA, $AA, $5A, $B5, $75, $5B, $5B, $55
	.byte $AB, $AA, $55, $B5, $AA, $55, $55, $5B, $BB, $B5, $AA, $4A, $4A, $AA, $A4, $AA, $54, $8A, $84, $88
	.byte $A4, $AA, $AA, $55, $BB, $B5, $B5, $55, $B5, $AA, $5A, $55, $AB, $5A, $55, $B5, $75, $5B, $AB, $4A
	.byte $A5, $A4, $4A, $AA, $4A, $4A, $8A, $88, $48, $A5, $AA, $55, $5B, $5B, $5B, $5B, $55, $AB, $AA, $55
	.byte $B5, $AA, $55, $55, $BB, $B5, $55, $55, $A5, $4A, $AA, $A4, $AA, $A4, $44, $A4, $88, $54, $55, $55
	.byte $B5, $B5, $B5, $B5, $55, $AB, $AA, $5A, $55, $AB, $5A, $55, $5B, $5B, $5B, $55, $55, $AA, $A4, $54
	.byte $AA, $54, $8A, $44, $A4, $A8, $54, $55, $B5, $5A, $B7, $55, $5B, $B5, $AA, $5A, $55, $AB, $AA, $55
	.byte $B5, $B5, $B5, $55, $55, $AA, $54, $4A, $A5, $4A, $4A, $8A, $44, $8A, $4A, $55, $55, $5B, $5B, $5B
	.byte $AB, $55, $AB, $AA, $55, $B5, $AA, $5A, $55, $5B, $5B, $AB, $55, $AA, $4A, $AA, $54, $AA, $A4, $44
	.byte $8A, $44, $A5, $4A, $55, $AB, $B5, $B5, $B5, $5A, $B5, $AA, $5A, $55, $AB, $5A, $55, $AB, $B5, $B5
	.byte $AA, $AA, $4A, $A5, $4A, $A5, $54, $8A, $44, $8A, $54, $AA, $54, $B5, $55, $5B, $5B, $AB, $55, $AB
	.byte $5A, $55, $B5, $AA, $55, $B5, $B5, $5A, $AB, $AA, $AA, $54, $AA, $A4, $4A, $4A, $8A, $44, $4A, $A5
	.byte $AA, $B4, $5A, $5B, $5B, $B5, $5A, $B5, $AA, $55, $B5, $AA, $5A, $55, $5B, $5B, $B5, $AA, $AA, $54
	.byte $AA, $54, $AA, $A4, $A4, $48, $A4, $54, $AA, $AA, $AA, $B5, $B5, $55, $5B, $55, $AB, $5A, $55, $AB
	.byte $5A, $55, $AB, $B5, $55, $AB, $AA, $4A, $A5, $4A, $A5, $4A, $8A, $A4, $48, $4A, $A5, $AA, $AA, $B5
	.byte $55, $5B, $AB, $55, $AB, $AA, $55, $AB, $AA, $55, $B5, $5A, $5B, $55, $AB, $4A, $55, $AA, $54, $4A
	.byte $4A, $4A, $A4, $A4, $54, $AA, $AA, $55, $5B, $AB, $B5, $5A, $B5, $AA, $55, $B5, $AA, $5A, $55, $5B
	.byte $B5, $55, $B5, $4A, $55, $AA, $54, $AA, $A4, $A4, $48, $4A, $4A, $A5, $AA, $5A, $AB, $B5, $55, $AB
	.byte $55, $AB, $5A, $55, $AB, $5A, $55, $AB, $B5, $5A, $55, $55, $55, $AA, $4A, $A5, $54, $8A, $A4, $44
	.byte $AA, $54, $AA, $5A, $B5, $B5, $5A, $AB, $55, $B5, $5A, $55, $AB, $AA, $55, $B5, $5A, $AB, $55, $55
	.byte $55, $A5, $4A, $A5, $4A, $4A, $4A, $A4, $A4, $4A, $A5, $5A, $B5, $5A, $5B, $B5, $5A, $B5, $AA, $55
	.byte $B5, $AA, $55, $55, $5B, $B5, $5A, $55, $55, $A5, $AA, $54, $AA, $A4, $44, $4A, $4A, $AA, $54, $55
	.byte $55, $5B, $B5, $55, $AB, $55, $AB, $5A, $55, $AB, $5A, $55, $AB, $55, $AB, $55, $55, $A5, $AA, $54
	.byte $A5, $A4, $A4, $A4, $A4, $5A, $AA, $A5, $55

	.align 64

ft_sample_3: ; ripped03.dmc
	.byte $BB, $0A, $50, $FA, $F0, $FF, $00, $F4, $FF, $F0, $0F, $00, $00, $00, $F0, $FF, $FF, $0A, $0A, $F0
	.byte $FF, $8F, $0B, $08, $FB, $4B, $A0, $AF, $8B, $7F, $00, $40, $FF, $F7, $FF, $80, $50, $B8, $F0, $0F
	.byte $00, $F4, $4F, $AF, $0F, $00, $00, $00, $F0, $FF, $FF, $40, $0B, $F0, $FF, $5F, $0F, $80, $FF, $05
	.byte $F0, $4F, $07, $FF, $00, $B0, $FF, $FF, $FF, $00, $00, $4A, $F0, $0F, $00, $FF, $40, $FF, $05, $00
	.byte $80, $00, $F0, $FF, $FF, $B0, $00, $FF, $FF, $57, $0F, $80, $7F, $0A, $F4, $AB, $F4, $05, $05, $F0
	.byte $FF, $FF, $0F, $0A, $A0, $0A, $5F, $80, $50, $FF, $05, $FF, $00, $00, $00, $00, $FF, $FF, $4F, $B4
	.byte $00, $FF, $FF, $77, $0A, $50, $7F, $08, $7B, $AB, $F0, $0F, $00, $FA, $FF, $FF, $0F, $00, $A8, $04
	.byte $FF, $00, $70, $FF, $40, $7F, $00, $00, $00, $00, $FF, $FF, $AF, $8A, $50, $FF, $FF, $5B, $00, $F4
	.byte $AF, $40, $77, $4B, $F8, $4F, $00, $FA, $FF, $FF, $0F, $00, $A0, $00, $FF, $08, $F0, $7F, $50, $4F
	.byte $00, $00, $00, $40, $FF, $FF, $AF, $84, $B4, $FF, $FF, $45, $80, $7A, $4F, $A8, $5B, $8B, $FA, $0B
	.byte $00, $F7, $FF, $FF, $07, $00, $A0, $50, $BF, $00, $FA, $4F, $74, $A5, $00, $00, $00, $B0, $FF, $FF
	.byte $8B, $88, $F4, $FF, $7F, $8A, $80, $F5, $A5, $54, $5B, $A5, $7B, $0A, $A0, $FB, $FF, $FF, $08, $00
	.byte $44, $74, $A7, $80, $FB, $A5, $5A, $8A, $00, $00, $00, $F4, $FF, $FF, $8A, $88, $FA, $FF, $77, $0A
	.byte $48, $BB, $4A, $B5, $5A, $5A, $B7, $84, $50, $F7, $FF, $7F, $04, $80, $88, $BA, $4A, $A8, $75, $AB
	.byte $55, $0A, $00, $00, $40, $F5, $FF, $FF, $88, $48, $7B, $FF, $B7, $84, $A8, $55, $55, $B5, $A5, $B5
	.byte $55, $8A, $A8, $FB, $FF, $AF, $80, $80, $A0, $B5, $A4, $58, $5B, $B5, $A5, $04, $00, $08, $A0, $FB
	.byte $FF, $57, $8A, $A8, $F5, $7F, $57, $8A, $54, $55, $55, $AB, $AA, $B5, $55, $A4, $54, $7F, $FF, $AB
	.byte $08, $84, $48, $55, $4A, $55, $5B, $B5, $4A, $84, $00, $80, $50, $F7, $FF, $5B, $8A, $54, $77, $7F
	.byte $AB, $A4, $54, $55, $55, $AB, $5A, $5B, $A5, $A4, $B4, $7B, $FF, $55, $44, $88, $48, $A5, $54, $B5
	.byte $AA, $B5, $4A, $88, $00, $80, $58, $F7, $F7, $B5, $A4, $AA, $BB, $BB, $55, $A5, $4A, $55, $55, $AB
	.byte $5A, $AB, $4A, $AA, $5A, $F7, $77, $AB, $88, $88, $A4, $A4, $54, $B5, $5A, $B5, $A4, $40, $08, $80
	.byte $B4, $7B, $77, $57, $A5, $BA, $75, $B7, $55, $AA, $AA, $54, $B5, $AA, $5A, $AB, $4A, $AA, $B5, $7B
	.byte $77, $55, $A4, $88, $A4, $A4, $54, $55, $AB, $55, $4A, $84, $80, $40, $55, $77, $77, $5B, $55, $B5
	.byte $5B, $B7, $AA, $AA, $AA, $54, $AB, $AA, $55, $AB, $54, $5A, $75, $77, $B7, $AA, $44, $8A, $A4, $A4
	.byte $54, $55, $AB, $A5, $8A, $08, $88, $A0, $5A, $BB, $75, $AB, $5A, $5B, $B7, $B5, $AA, $AA, $AA, $AA
	.byte $AA, $AA, $55, $AB, $54, $55, $5B, $77, $57, $55, $4A, $A4, $A4, $A4, $54, $B5, $AA, $AA, $44, $44
	.byte $08, $4A, $B5, $B5, $B5, $B5, $B5, $B5, $B5, $55, $AB, $AA, $AA, $AA, $AA, $5A, $55, $4B, $55, $55
	.byte $BB, $5B, $5B, $A5, $A4, $A4, $A4, $A4, $4A, $B5, $AA, $4A, $8A, $88, $40, $4A, $AB, $B5, $B5, $B5
	.byte $B5, $B5, $B5, $55, $B5, $AA, $AA, $AA, $AA, $5A, $55, $55, $55, $B5, $B5, $5B, $5B, $AA, $A4, $A4
	.byte $A4, $A4, $4A, $B5, $AA, $54, $44, $44, $A4, $A4, $55, $5B, $AB, $B5, $B5, $5B, $AB, $55, $B5, $AA
	.byte $AA, $AA, $AA, $5A, $55, $55, $55, $B5, $75, $5B, $AB, $4A, $A5, $A4, $A4, $A4, $AA, $AA, $4A, $A5
	.byte $48, $44, $A4, $54, $B5, $5A, $AB, $B5, $75, $5B, $AB, $55, $B5, $AA, $AA, $AA, $AA, $55, $55, $55
	.byte $55, $5B, $5B, $5B, $B5, $54, $4A, $A5, $A4, $A4, $AA, $AA, $54, $4A, $8A, $88, $A4, $AA, $AA, $55
	.byte $5B, $5B, $5B, $5B, $AB, $55, $B5, $AA, $AA, $AA, $AA, $55, $55, $55, $55, $5B, $5B, $5B, $55, $A5
	.byte $4A, $4A, $A5, $A4, $AA, $4A, $A5, $8A, $44, $8A, $A4, $AA, $5A, $B5, $5A, $5B, $5B, $5B, $AB, $55
	.byte $B5, $AA, $AA, $AA, $AA, $55, $55, $55, $B5, $5A, $5B, $5B, $55, $AA, $54, $4A, $AA, $A4, $AA, $4A
	.byte $A5, $A4, $48, $A4, $54, $AA, $55, $B5, $5A, $5B, $B7, $55, $AB, $55, $B5, $AA, $AA, $AA, $5A, $55
	.byte $55, $55, $B5, $B5, $55, $AB, $AA, $AA, $A4, $4A, $AA, $A4, $AA, $54, $4A, $4A, $8A, $A4, $54, $55
	.byte $55, $AB, $B5, $B5, $B5, $B5, $5A, $55, $B5, $AA, $AA, $AA, $5A, $55, $55, $55, $AB, $B5, $B5, $AA
	.byte $AA, $4A, $A5, $54, $4A, $A5, $AA, $54, $4A, $8A, $A4, $A4, $54, $55, $B5, $AA, $B5, $B5, $B5, $B5
	.byte $5A, $55, $B5, $AA, $AA, $AA, $55, $55, $55, $B5, $5A, $B5, $B5, $AA, $AA, $54, $AA, $A4, $4A, $A5
	.byte $AA, $A4, $A4, $A4, $44, $A5, $4A, $55, $AB, $5A, $5B, $5B, $AB, $B5, $5A, $55, $B5, $AA, $AA, $AA
	.byte $55, $55, $55, $B5, $5A, $AB, $55, $AB, $4A, $55, $4A, $A5, $4A, $A5, $4A, $A5, $A4, $44, $4A, $A5
	.byte $AA, $AA, $AA, $55, $5B, $5B, $5B, $B5, $5A, $55, $B5, $AA, $AA, $5A, $55, $55, $55, $AB, $55, $AB
	.byte $55, $55, $55, $A5, $4A, $A5, $4A, $A5, $4A, $4A, $4A, $4A, $4A, $AA, $AA, $AA, $AA, $B5, $B5, $55
	.byte $5B, $AB, $5A, $55, $B5, $AA, $AA, $5A, $55, $55, $55, $AB, $55, $5B, $55, $55, $55, $AA, $54, $AA
	.byte $54, $AA, $54, $4A, $4A, $4A, $4A, $A5, $AA, $AA, $5A, $B5, $B5, $B5, $5A, $AB, $5A, $55, $B5, $AA
	.byte $AA, $55, $55, $55, $B5, $AA, $B5, $5A, $55, $55, $55, $AA, $54, $AA, $54, $AA, $A4, $8A, $A4, $A4
	.byte $54, $A5, $AA, $AA, $55, $5B, $AB, $B5, $55, $AB, $55, $55, $AB, $AA, $AA, $55, $55, $55, $B5, $5A
	.byte $B5, $5A, $55, $55, $A5, $4A, $A5, $4A, $55, $4A, $A5, $A4, $A4, $A4, $54, $A5, $AA, $5A, $B5, $5A
	.byte $5B, $AB, $B5, $AA, $55, $5A, $A5, $A5, $55

	.align 64

ft_sample_4: ; ripped02.dmc
	.byte $BB, $0A, $50, $7A, $0A, $FF, $00, $FF, $FF, $04, $FF, $40, $00, $00, $00, $F0, $FF, $FF, $0B, $07
	.byte $F0, $F5, $FF, $F4, $00, $F0, $5F, $08, $F5, $BA, $78, $0F, $00, $F0, $FF, $FF, $FF, $00, $80, $70
	.byte $F0, $0F, $00, $F8, $8F, $FA, $07, $48, $00, $00, $00, $FF, $FF, $FF, $50, $0A, $F4, $FF, $4F, $0F
	.byte $08, $F7, $57, $00, $FF, $5A, $F0, $0F, $00, $FA, $7F, $FF, $8F, $00, $A8, $A4, $F0, $0F, $00, $F5
	.byte $5F, $B0, $4F, $00, $00, $0A, $00, $FF, $FF, $AF, $70, $00, $FF, $FF, $4F, $0F, $00, $FF, $85, $B0
	.byte $AF, $85, $5F, $04, $80, $FF, $BF, $FF, $0F, $00, $48, $05, $5F, $04, $A0, $FF, $0F, $F0, $0F, $00
	.byte $00, $04, $F0, $FF, $FF, $85, $45, $50, $FF, $FF, $5B, $05, $A0, $7F, $0A, $F8, $AB, $0A, $FF, $00
	.byte $40, $FF, $FF, $FF, $0F, $00, $40, $04, $FF, $00, $B0, $FF, $05, $FB, $04, $00, $80, $00, $F0, $FF
	.byte $FF, $8B, $0A, $74, $FF, $FF, $55, $08, $F0, $5F, $08, $7B, $5B, $88, $FF, $04, $40, $FF, $FF, $FF
	.byte $05, $00, $50, $80, $FF, $08, $70, $FF, $40, $BF, $08, $00, $00, $00, $F8, $FF, $FF, $A5, $84, $BA
	.byte $FF, $7F, $A5, $00, $7A, $AF, $A0, $75, $4B, $74, $BF, $00, $70, $FF, $FF, $FF, $00, $00, $48, $58
	.byte $5F, $00, $F5, $5F, $54, $A7, $08, $00, $00, $00, $FF, $FF, $7F, $8A, $A0, $F5, $FF, $BF, $84, $40
	.byte $F5, $A5, $54, $5B, $8B, $75, $A7, $00, $BA, $FF, $FF, $AF, $00, $00, $44, $7A, $47, $88, $F5, $AB
	.byte $AA, $4A, $08, $00, $00, $48, $FF, $FF, $5F, $0A, $54, $FB, $FF, $57, $0A, $44, $BB, $AA, $B4, $5A
	.byte $A5, $BB, $8A, $40, $75, $FF, $FF, $8F, $00, $80, $48, $5B, $A5, $50, $77, $55, $AB, $8A, $00, $00
	.byte $80, $B8, $FF, $FF, $4B, $44, $B4, $FB, $7F, $57, $44, $A4, $B5, $AA, $AA, $55, $55, $B7, $44, $A4
	.byte $B5, $FF, $7F, $8B, $00, $88, $48, $5B, $8A, $AA, $B5, $55, $AB, $84, $00, $00, $88, $F4, $FF, $7F
	.byte $4B, $44, $5A, $7F, $7F, $AB, $88, $54, $55, $55, $AB, $A5, $B5, $55, $4A, $54, $BB, $F7, $BF, $4A
	.byte $08, $88, $A8, $AA, $A4, $5A, $AB, $55, $4B, $0A, $08, $00, $88, $F5, $FF, $77, $A5, $A4, $74, $F7
	.byte $BB, $55, $A4, $AA, $54, $B5, $AA, $5A, $B5, $A5, $A4, $AA, $75, $7F, $5F, $45, $44, $88, $A4, $4A
	.byte $AA, $5A, $B5, $55, $A5, $88, $00, $08, $A8, $F5, $F7, $BB, $AA, $A4, $B5, $BB, $BB, $AA, $54, $AA
	.byte $4A, $AB, $AA, $5A, $AB, $AA, $A4, $AA, $BB, $77, $B7, $A4, $88, $88, $54, $4A, $AA, $55, $B5, $55
	.byte $45, $44, $08, $08, $54, $77, $BF, $5B, $4B, $55, $5B, $77, $5B, $4B, $55, $AA, $AA, $AA, $AA, $5A
	.byte $AB, $4A, $A5, $5A, $77, $77, $57, $4A, $8A, $48, $4A, $4A, $AA, $55, $B5, $5A, $8A, $88, $80, $40
	.byte $5A, $BB, $BB, $5B, $55, $B5, $B5, $5B, $5B, $55, $55, $AA, $AA, $AA, $AA, $55, $AB, $4A, $A5, $B5
	.byte $75, $5F, $AB, $8A, $44, $4A, $4A, $54, $AA, $55, $B5, $AA, $44, $44, $88, $A0, $B4, $75, $B7, $B5
	.byte $55, $5B, $5B, $5B, $AB, $55, $A5, $AA, $AA, $AA, $AA, $B5, $AA, $54, $55, $75, $BB, $5B, $55, $A5
	.byte $48, $4A, $8A, $54, $55, $55, $B5, $4A, $8A, $84, $08, $4A, $5A, $BB, $B5, $B5, $55, $5B, $B7, $B5
	.byte $AA, $AA, $AA, $AA, $AA, $AA, $5A, $B5, $4A, $55, $55, $5B, $B7, $AB, $55, $4A, $4A, $4A, $A4, $4A
	.byte $55, $55, $B5, $54, $A4, $08, $44, $4A, $B5, $B5, $B5, $B5, $B5, $B5, $B5, $B5, $AA, $AA, $AA, $AA
	.byte $AA, $AA, $55, $55, $55, $55, $B5, $B5, $75, $AB, $AA, $A4, $54, $8A, $A4, $4A, $55, $55, $55, $A5
	.byte $48, $44, $44, $AA, $5A, $5B, $B5, $B5, $B5, $B5, $AB, $B5, $AA, $AA, $AA, $AA, $AA, $AA, $55, $55
	.byte $55, $55, $B5, $B5, $5B, $B5, $4A, $A5, $A4, $A4, $A4, $4A, $55, $55, $55, $4A, $A4, $88, $44, $55
	.byte $B5, $5A, $AB, $B5, $75, $5B, $5B, $B5, $AA, $AA, $AA, $AA, $AA, $5A, $55, $55, $55, $55, $AB, $75
	.byte $5B, $55, $55, $AA, $A4, $A4, $A4, $4A, $55, $55, $A5, $A4, $44, $A4, $A4, $54, $AB, $55, $5B, $5B
	.byte $5B, $5B, $5B, $B5, $AA, $AA, $AA, $AA, $AA, $5A, $55, $55, $55, $55, $5B, $5B, $5B, $55, $A5, $4A
	.byte $AA, $A4, $A4, $4A, $55, $55, $AA, $44, $8A, $A4, $A4, $AA, $5A, $B5, $5A, $5B, $5B, $5B, $5B, $B5
	.byte $AA, $AA, $AA, $AA, $AA, $55, $55, $55, $55, $B5, $5A, $5B, $AB, $55, $AA, $54, $4A, $A5, $A4, $4A
	.byte $55, $A5, $4A, $4A, $A4, $48, $A5, $AA, $55, $AB, $55, $BB, $B5, $B5, $5A, $B5, $AA, $AA, $AA, $AA
	.byte $AA, $55, $55, $55, $55, $AB, $B5, $5A, $AB, $AA, $4A, $A5, $4A, $AA, $A4, $4A, $55, $A5, $A4, $A4
	.byte $48, $4A, $55, $55, $55, $AB, $B5, $B5, $B5, $B5, $5A, $B5, $AA, $AA, $AA, $AA, $5A, $55, $55, $55
	.byte $55, $AB, $B5, $55, $AB, $AA, $4A, $A5, $54, $4A, $A5, $4A, $55, $AA, $A4, $48, $4A, $4A, $55, $55
	.byte $B5, $5A, $AB, $5B, $AB, $B5, $55, $B5, $AA, $AA, $AA, $AA, $55, $55, $55, $55, $B5, $5A, $B5, $55
	.byte $AB, $4A, $55, $AA, $A4, $4A, $A5, $4A, $A5, $4A, $4A, $4A, $54, $4A, $55, $B5, $AA, $55, $5B, $5B
	.byte $5B, $AB, $55, $B5, $AA, $AA, $AA, $AA, $55, $55, $55, $55, $AB, $5A, $AB, $55, $B5, $54, $A5, $4A
	.byte $A5, $54, $AA, $4A, $A5, $54, $8A, $A4, $A4, $AA, $AA, $AA, $AA, $B5, $B5, $55, $5B, $AB, $55, $B5
	.byte $AA, $AA, $AA, $5A, $55, $55, $55, $55, $AB, $55, $AB, $55, $55, $55, $AA, $54, $AA, $54, $AA, $54
	.byte $AA, $A4, $A4, $A4, $A4, $AA, $AA, $AA, $5A, $B5, $B5, $B5, $55, $AB, $55, $B5, $AA, $AA, $AA, $5A
	.byte $55, $55, $55, $B5, $AA, $B5, $5A, $55, $55, $A5, $AA, $54, $AA, $54, $AA, $54, $4A, $4A, $4A, $AA
	.byte $A4, $AA, $AA, $AA, $55, $5B, $5B, $B5, $B5, $5A, $55, $B5, $AA

	.align 64

ft_sample_5: ; kick
	.byte $65, $95, $C3, $71, $F8, $C0, $E3, $E0, $18, $E7, $F1, $07, $7F, $3E, $7C, $FE, $19, $18, $C0, $0C
	.byte $0E, $F0, $0F, $70, $00, $0F, $3E, $F0, $0F, $FC, $F8, $9F, $C7, $CF, $1B, $FF, $2D, $2D, $0E, $4F
	.byte $2D, $08, $1F, $06, $18, $0E, $C0, $00, $50, $55, $55, $55, $55, $55, $55, $55, $55, $D5, $FE, $3F
	.byte $EE, $F5, $BF, $C7, $9B, $A7, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $2A, $83, $30, $60, $2C
	.byte $04, $D8, $00, $C8, $34, $55, $55, $55, $55, $55, $55, $55, $55, $55, $B5, $34, $F3, $78, $FF, $F1
	.byte $1F, $BE, $AF, $E7, $AF, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA
	.byte $0A, $C7, $10, $00, $AA, $81, $00, $68, $6A, $31, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55
	.byte $55, $AD, $32, $B3, $EC, $71, $EE, $FF, $35, $EF, $BE, $F3, $CE, $99, $AA, $AA, $AA, $AA, $AA, $AA
	.byte $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $08, $C3, $80, $71, $00, $43, $21, $A0, $23, $55
	.byte $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $35, $B3
	.byte $AA, $BF, $DE, $7D, $ED, $ED, $5E, $7F, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA
	.byte $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $2A, $15, $4A, $4A, $20, $49, $05, $95, $81, $13, $28, $2D
	.byte $C6, $52, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $55, $75, $5D, $ED
	.byte $97, $6D, $DD, $D5, $EC, $69, $D5, $8E, $EE, $5A, $93, $CB, $E6, $A5, $72, $B5, $AA, $32, $16, $2D
	.byte $55, $1B, $EA, $A4, $15, $9A, $96, $E2, $91, $B8, $A2, $52, $46, $15, $93, $A2, $AA, $B0, $5A, $C4
	.byte $58, $56, $AA, $6A, $B4, $E6, $E2, $55, $55, $DA, $52, $5D, $76, $31, $CD, $9A, $95, $76, $6C, $5D
	.byte $96, $B6, $2A, $AD, $4D, $5B, $55, $A5, $52, $AD, $45, $AC, $64, $53, $4C, $6A, $9A, $92, $CA, $D3
	.byte $84, $2A, $55, $AA, $95, $AA, $55, $B9, $4A, $4B, $B5, $55, $A9, $6D, $6A, $53, $AB, $4A, $D7, $D2
	.byte $D2, $56, $AD, $2A, $AB, $5A, $A5, $5A, $69, $AA, $52, $5A, $53, $99, $54, $4D, $55, $56, $59, $6A
	.byte $95, $26, $27, $97, $AC, $D2, $6C, $A9, $55, $35, $55, $AD, $72, $D3, $AA, $AA, $95, $59, $AB, $B2
	.byte $B4, $B4, $4C, $59, $95, $1A, $D5, $54, $C9, $C9, $D2, $4C, $69, $A5, $AA, $D2, $52, $45, $95, $55
	.byte $D5, $AA, $AC, $AC, $A6, $74, $2A, $95, $65, $95, $36, $96, $56, $5A, $A9, $B6, $4C, $55, $55, $AD
	.byte $36, $B5, $56, $55, $55, $DB, $D4, $9A, $54, $B5, $D2, $A8, $2D, $AD, $52, $AB, $AA, $55, $4D, $B5
	.byte $25, $55, $AB, $4A, $29, $AB, $54, $55, $65, $A9, $AA, $54, $55, $AD, $AA, $A6, $4A, $53, $55, $6A
	.byte $51, $95, $5A, $AA, $A6, $AC, $AA, $6A, $6A, $D5, $AA, $6A, $55, $A5, $55, $55, $55, $55, $55, $55
	.byte $55, $55, $55, $55, $55, $55, $D5, $4A, $B5, $AA, $A6, $56, $6A, $6A, $A9, $AA, $16, $AB, $AA, $54
	.byte $55, $55, $55, $55, $AA, $4A, $D5, $AA, $54, $55, $53, $AE, $54, $D5, $2A, $D5, $6A, $49, $AB, $AC
	.byte $54, $59, $A9, $55, $55, $55, $AD, $B2, $55, $56, $55, $6B, $5A, $AA, $55, $55, $D5, $AA, $AA, $AA
	.byte $2A, $B5, $AA, $2A, $AD, $2A, $55, $69, $29, $AB, $54, $2B, $55, $55, $55, $55, $55, $55, $A9, $AA
	.byte $AA, $A9, $AA, $A6, $6A, $55, $55, $A5, $95, $56, $95, $6A, $55

	.align 64

ft_sample_6: ; snare
	.byte $19, $00, $00, $D0, $CC, $FF, $C7, $FF, $F8, $F1, $FF, $C3, $0F, $63, $00, $87, $01, $00, $00, $54
	.byte $55, $55, $55, $E5, $F8, $FF, $FF, $FF, $FF, $FF, $55, $55, $55, $99, $03, $0C, $00, $04, $00, $00
	.byte $40, $55, $65, $CD, $0F, $FF, $FF, $F3, $FF, $E7, $FF, $9E, $29, $DC, $19, $02, $8C, $E1, $C3, $38
	.byte $00, $00, $18, $07, $18, $30, $1F, $3E, $3E, $F0, $E3, $3F, $F7, $FE, $F3, $FF, $1F, $1E, $C6, $18
	.byte $81, $40, $38, $FC, $30, $00, $C4, $63, $3C, $3C, $38, $1C, $90, $E7, $31, $FF, $F3, $CF, $FF, $FF
	.byte $87, $3B, $03, $30, $8E, $C3, $20, $00, $0C, $00, $20, $1E, $77, $9C, $E7, $F1, $8F, $FF, $FB, $6F
	.byte $38, $FF, $39, $FC, $03, $01, $07, $7E, $87, $01, $30, $00, $80, $79, $F0, $3C, $38, $38, $9E, $87
	.byte $9F, $FF, $FF, $3F, $CF, $71, $DC, $E1, $0E, $30, $60, $08, $C3, $81, $21, $38, $C0, $11, $0F, $8F
	.byte $0F, $E7, $1F, $FF, $CF, $F1, $E3, $1F, $E7, $3C, $0C, $87, $03, $8E, $C3, $03, $C2, $81, $E3, $38
	.byte $8E, $38, $0E, $3C, $C7, $E1, $79, $7E, $7C, $BE, $C3, $31, $7E, $1C, $E3, $38, $3C, $86, $E3, $F0
	.byte $C0, $E1, $01, $60, $C0, $1C, $0A, $CF, $71, $FC, $3D, $8F, $CF, $9F, $C7, $F3, $F9, $FF, $0C, $C3
	.byte $21, $0C, $70, $18, $06, $38, $86, $C1, $08, $E3, $88, $F1, $E7, $FF, $F3, $FF, $71, $0E, $FF, $0F
	.byte $87, $0F, $86, $31, $38, $80, $31, $84, $03, $18, $38, $C7, $C1, $39, $1E, $6F, $9E, $F3, $CF, $E3
	.byte $FD, $FD, $C3, $3B, $0C, $E0, $E0, $C0, $60, $60, $30, $18, $0E, $CE, $F1, $18, $CF, $CF, $E7, $E3
	.byte $E1, $F1, $73, $F8, $23, $DC, $E1, $70, $78, $78, $E0, $87, $E3, $18, $63, $0E, $82, $07, $C2, $F1
	.byte $C0, $E3, $38, $C6, $F9, $BC, $E7, $3C, $FF, $F8, $FF, $E0, $0C, $63, $0C, $43, $E0, $70, $70, $18
	.byte $00, $86, $71, $78, $9E, $C7, $1F, $9F, $77, $FE, $9F, $63, $8E, $71, $F4, $86, $03, $7C, $00, $E1
	.byte $70, $38, $C6, $81, $23, $5C, $7C, $1C, $E7, $C7, $73, $CF, $79, $2E, $9E, $67, $1E, $8F, $21, $0E
	.byte $23, $1C, $C3, $F0, $E1, $F0, $18, $3B, $E0, $89, $63, $87, $CF, $F0, $63, $CE, $F1, $0F, $FF, $E3
	.byte $8E, $63, $3C, $8C, $31, $0C, $01, $8E, $10, $63, $98, $79, $1C, $0F, $0F, $EF, $C0, $E3, $FF, $1C
	.byte $FF, $F8, $7C, $1E, $0E, $70, $C0, $01, $E3, $18, $86, $37, $1C, $F8, $E1, $E1, $F1, $F8, $CF, $71
	.byte $8C, $39, $78, $38, $1E, $8F, $61, $8E, $71, $CC, $D3, $E1, $11, $F6, $18, $7B, $30, $1C, $C7, $11
	.byte $F8, $4D, $EF, $C3, $C7, $87, $9B, $E3, $0E, $39, $70, $80, $31, $8C, $79, $BC, $0F, $4F, $C1, $07
	.byte $F7, $18, $FE, $60, $55, $90, $17, $FC, $39, $9E, $C3, $71, $0F, $E7, $38, $7C, $18, $E7, $80, $7D
	.byte $8C, $23, $0E, $81, $C7, $F1, $70, $9E, $F8, $E1, $E5, $70, $FE, $C4, $E7, $C2, $41, $0E, $15, $0F
	.byte $3E, $81, $6F, $88, $C3, $8B, $C7, $C7, $33, $16, $D5, $C3, $39, $CE, $C3, $81, $67, $1E, $F8, $7C
	.byte $8C, $C3, $F1, $30, $1C, $E2, $11, $0F, $87, $F1, $F8, $F8, $9E, $0F, $1F, $C6, $D9, $61, $0E, $0E
	.byte $C3, $61, $38, $8C, $79, $0F, $EF, $C8, $93, $E7, $E1, $38, $C7, $78, $B0, $E2, $F0, $54, $9E, $E1
	.byte $38, $0C, $0F, $C7, $71, $C3, $3D, $06, $EF, $38, $E3, $1E, $1E, $9F, $F1, $90, $72, $C4, $86, $15
	.byte $C6, $C3, $2B, $34, $54, $8C, $C7, $CF, $3B, $7D, $8C, $19, $8F, $CD, $E3, $C6, $71, $0E, $78, $18
	.byte $0D, $C3, $39, $7C, $18, $1E, $8E, $E3, $E1, $9E, $E3, $D9, $83, $CE, $18, $CE, $91, $8F, $F3, $62
	.byte $1D, $8C, $43, $7C, $D0, $1E, $3C, $1C, $1C, $9A, $C1, $EB, $61, $3F, $DC, $51, $F3, $30, $3D, $E7
	.byte $B3, $4E, $C1, $C1, $10, $D3, $30, $3C, $9E, $54, $C7, $0E, $0F, $8E, $F3, $8E, $E7, $5A, $78, $18
	.byte $C7, $E1, $D1, $31, $1D, $0F, $65, $A5, $38, $E1, $71, $57, $55, $4B, $8D, $93, $56, $4C, $5D, $EB
	.byte $F0, $62, $8C, $69, $55, $67, $45, $CF, $E1, $50, $A5, $E1, $18, $1E, $87, $C7, $71, $5C, $79, $3C
	.byte $D3, $AD, $C1, $2B, $47, $39, $1E, $9C, $A7, $F8, $10, $1D, $95, $62, $59, $8C, $33, $F8, $3C, $8E
	.byte $8D, $C3, $75, $D5, $57, $1F, $8D, $33, $2C, $14, $4E, $25, $8E, $E2, $2C, $AC, $35, $1C, $6F, $69
	.byte $79, $55, $77, $79, $1C, $96, $D1, $2C, $96, $52, $35, $CA, $61, $87, $63, $D4, $B0, $A5, $2F, $5E
	.byte $47, $59, $55, $AB, $9C, $E5, $C5, $E2, $70, $E2, $18, $66, $D4, $F1, $AC, $C3, $8D, $C5, $15, $6B
	.byte $4D, $CB, $E5, $68, $D4, $D2, $1A, $73, $0E, $67, $34, $0D, $0D, $8F, $71, $68, $D5, $8D, $87, $5B
	.byte $78, $B5, $5C, $9B, $B3, $6A, $8C, $83, $52, $16, $57, $45, $97, $AA, $12, $AB, $4A, $5F, $9C, $35
	.byte $55, $35, $56, $D5, $58, $9D, $C3, $53, $45, $D5, $61, $69, $9C, $26, $9E, $C5, $A5, $65, $65, $95
	.byte $6A, $55, $D6, $54, $75, $61, $95, $6A, $95, $CB, $74, $1A, $3B, $D4, $71, $54, $95, $15, $87, $5B
	.byte $E2, $C1, $A6, $F1, $6C, $A5, $65, $4D, $73, $51, $17, $57, $2A, $75, $B4, $72, $96, $A5, $2A, $4D
	.byte $85, $C7, $52, $1C, $A7, $6A, $E9, $B4, $56, $D9, $3C, $5A, $8B, $AB, $1C, $1D, $8D, $45, $55, $31
	.byte $8C, $2B, $AA, $6D, $79, $78, $35, $55, $4B, $F5, $D0, $5A, $55, $56, $65, $C9, $46, $55, $A5, $B2
	.byte $D8, $4A, $5B, $54, $39, $56, $AE, $A6, $55, $C7, $B4, $AA, $52, $D5, $54, $D5, $CC, $D2, $16, $55
	.byte $65, $59, $96, $55, $D5, $54, $56, $B1, $15, $D5, $29, $27, $9D, $56, $55, $35, $55, $CD, $B4, $6A
	.byte $2C, $4B, $53, $55, $55, $55, $65, $55, $D5, $54, $9A, $A6, $99, $55, $A9, $66, $2A, $AB, $69, $55
	.byte $56, $55, $2D, $CB, $96, $AA, $52, $4B, $55, $55, $D5, $94, $AA, $54, $8B, $AD, $74, $55, $59, $D3
	.byte $54, $55, $55, $55, $4D, $AD, $2A, $4D, $55, $55, $59, $A5, $55, $55, $55, $55, $55, $AA, $95, $55
	.byte $59, $5A, $55, $55, $55, $55, $55, $55, $55, $D3, $52, $D3, $54, $55, $55, $55, $65, $55, $A9, $AA
	.byte $55

	.align 64

