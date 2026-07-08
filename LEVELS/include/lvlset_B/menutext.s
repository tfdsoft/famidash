
;;; Exported by export_levels.py

.segment _LVL_NAME_BANK

.export _levelTextsUpper_lo, _levelTextsUpper_hi, _levelTextsLower_lo, _levelTextsLower_hi

.repeat 52, I
.import .ident(.sprintf("_levelText%02X", I))
.endrepeat

_levelTextsUpper_lo:
.byte	<_levelText00
.byte	0
.byte	0
.byte	<_levelText01
.byte	0
.byte	<_levelText02
.byte	<_levelText03
.byte	<_levelText04
.byte	0
.byte	0
.byte	<_levelText05
.byte	<_levelText06
.byte	0
.byte	0
.byte	0
.byte	<_levelText07
.byte	<_levelText08
.byte	<_levelText09
.byte	0
.byte	<_levelText0A
.byte	<_levelText0B
.byte	0
.byte	0
.byte	0
.byte	<_levelText0C
.byte	<_levelText0D
.byte	0
.byte	<_levelText0E
.byte	0
.byte	<_levelText0F
.byte	0
.byte	0
.byte	<_levelText10
.byte	0
.byte	0

_levelTextsUpper_hi:
.byte	>_levelText00
.byte	0
.byte	0
.byte	>_levelText01
.byte	0
.byte	>_levelText02
.byte	>_levelText03
.byte	>_levelText04
.byte	0
.byte	0
.byte	>_levelText05
.byte	>_levelText06
.byte	0
.byte	0
.byte	0
.byte	>_levelText07
.byte	>_levelText08
.byte	>_levelText09
.byte	0
.byte	>_levelText0A
.byte	>_levelText0B
.byte	0
.byte	0
.byte	0
.byte	>_levelText0C
.byte	>_levelText0D
.byte	0
.byte	>_levelText0E
.byte	0
.byte	>_levelText0F
.byte	0
.byte	0
.byte	>_levelText10
.byte	0
.byte	0

_levelTextsLower_lo:
.byte	<_levelText11
.byte	<_levelText12
.byte	<_levelText13
.byte	<_levelText14
.byte	<_levelText15
.byte	<_levelText16
.byte	<_levelText17
.byte	<_levelText18
.byte	<_levelText19
.byte	<_levelText1A
.byte	<_levelText1B
.byte	<_levelText1C
.byte	<_levelText1D
.byte	<_levelText1E
.byte	<_levelText1F
.byte	<_levelText20
.byte	<_levelText21
.byte	<_levelText22
.byte	<_levelText23
.byte	<_levelText24
.byte	<_levelText25
.byte	<_levelText26
.byte	<_levelText27
.byte	<_levelText28
.byte	<_levelText29
.byte	<_levelText2A
.byte	<_levelText2B
.byte	<_levelText2C
.byte	<_levelText2D
.byte	<_levelText2E
.byte	<_levelText2F
.byte	<_levelText30
.byte	<_levelText31
.byte	<_levelText32
.byte	<_levelText33

_levelTextsLower_hi:
.byte	>_levelText11
.byte	>_levelText12
.byte	>_levelText13
.byte	>_levelText14
.byte	>_levelText15
.byte	>_levelText16
.byte	>_levelText17
.byte	>_levelText18
.byte	>_levelText19
.byte	>_levelText1A
.byte	>_levelText1B
.byte	>_levelText1C
.byte	>_levelText1D
.byte	>_levelText1E
.byte	>_levelText1F
.byte	>_levelText20
.byte	>_levelText21
.byte	>_levelText22
.byte	>_levelText23
.byte	>_levelText24
.byte	>_levelText25
.byte	>_levelText26
.byte	>_levelText27
.byte	>_levelText28
.byte	>_levelText29
.byte	>_levelText2A
.byte	>_levelText2B
.byte	>_levelText2C
.byte	>_levelText2D
.byte	>_levelText2E
.byte	>_levelText2F
.byte	>_levelText30
.byte	>_levelText31
.byte	>_levelText32
.byte	>_levelText33
