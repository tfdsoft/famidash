; Generated by export.py using data in metadata.json

; Music data banks
.segment "DAT_BANK_29"
	firstMusicBankPtr := *
	.include "music_0.s"
.segment "DAT_BANK_2A"
	.include "music_1.s"
.segment "DAT_BANK_2B"
	.include "music_2.s"
.segment "DAT_BANK_2C"
	.include "music_3.s"
.segment "DAT_BANK_2D"
	.include "music_4.s"
.segment "DAT_BANK_2E"
	.include "music_5.s"
.segment "DAT_BANK_2F"
	.include "music_6.s"
.segment "DAT_BANK_30"
	.include "music_7.s"
.segment "DAT_BANK_31"
	.include "music_8.s"
.segment "DAT_BANK_32"
	.include "music_9.s"

; DMC banks
.segment "DAT_BANK_33"
	firstDMCBankPtr := *
	.incbin "music_bank0.dmc"

; PCM includes
.segment "PCM_BANK"
	pcmData0:
		.incbin "MUSIC/PCM/SSDPCM2-geometryDash.pcm"
.segment "PCM_BANK_B"
	pcmData1:
		.incbin "MUSIC/PCM/SSDPCM2-fire.pcm"

; Constants
FIRST_MUSIC_BANK = .bank(firstMusicBankPtr)
FIRST_DMC_BANK = .bank(firstDMCBankPtr)