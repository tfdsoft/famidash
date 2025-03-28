; Music data banks
.segment "MUS_BANK_00"
	firstMusicBankPtr := *
	.include "music_0.s"
.segment "MUS_BANK_01"
	.include "music_1.s"
.segment "MUS_BANK_02"
	.include "music_2.s"
.segment "MUS_BANK_03"
	.include "music_3.s"
.segment "MUS_BANK_04"
	.include "music_4.s"
.segment "MUS_BANK_05"
	.include "music_5.s"
.segment "MUS_BANK_06"
	.include "music_6.s"
.segment "MUS_BANK_07"
	.include "music_7.s"
.segment "MUS_BANK_08"
	.include "music_8.s"
.segment "MUS_BANK_09"
	.include "music_9.s"
.segment "MUS_BANK_0A"
	.include "music_10.s"
.segment "MUS_BANK_0B"
	.include "music_11.s"
.segment "MUS_BANK_0C"
	.include "music_12.s"
.segment "MUS_BANK_0D"
	.include "music_13.s"

; DMC banks
.segment "DMC_BANK_00"
	firstDMCBankPtr := *
	.incbin "music_bank0.dmc"
.segment "DMC_BANK_01"
	.incbin "music_bank1.dmc"
.segment "DMC_BANK_02"
	.incbin "music_bank2.dmc"

; Constants
FIRST_MUSIC_BANK = .bank(firstMusicBankPtr)
FIRST_DMC_BANK = .bank(firstDMCBankPtr)