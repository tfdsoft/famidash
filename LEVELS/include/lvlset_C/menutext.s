
;;; Exported by export_levels.py

.segment _LVL_NAME_BANK

.export _levelTextsUpper_lo, _levelTextsUpper_hi, _levelTextsLower_lo, _levelTextsLower_hi

.repeat 41, I
.import .ident(.sprintf("_levelText%02X", I))
.endrepeat

_levelTextsUpper_lo:
.byte	<_levelText00
.byte	<_levelText01
.byte	0
.byte	0
.byte	<_levelText02
.byte	0
.byte	0
.byte	<_levelText03
.byte	<_levelText04
.byte	0
.byte	<_levelText05
.byte	<_levelText06
.byte	0
.byte	<_levelText07
.byte	0
.byte	0
.byte	<_levelText08
.byte	<_levelText09
.byte	<_levelText0A
.byte	0
.byte	0
.byte	0
.byte	0
.byte	<_levelText00
.byte	<_levelText0B
.byte	0
.byte	0
.byte	0
.byte	0
.byte	0
.byte	0

_levelTextsUpper_hi:
.byte	>_levelText00
.byte	>_levelText01
.byte	0
.byte	0
.byte	>_levelText02
.byte	0
.byte	0
.byte	>_levelText03
.byte	>_levelText04
.byte	0
.byte	>_levelText05
.byte	>_levelText06
.byte	0
.byte	>_levelText07
.byte	0
.byte	0
.byte	>_levelText08
.byte	>_levelText09
.byte	>_levelText0A
.byte	0
.byte	0
.byte	0
.byte	0
.byte	>_levelText00
.byte	>_levelText0B
.byte	0
.byte	0
.byte	0
.byte	0
.byte	0
.byte	0

_levelTextsLower_lo:
.byte	<_levelText0C
.byte	<_levelText0D
.byte	<_levelText0E
.byte	<_levelText0F
.byte	<_levelText10
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
.byte	<_levelText19
.byte	<_levelText1C
.byte	<_levelText1D
.byte	<_levelText1E
.byte	<_levelText1F
.byte	<_levelText20
.byte	<_levelText21
.byte	<_levelText10
.byte	<_levelText22
.byte	<_levelText23
.byte	<_levelText24
.byte	<_levelText25
.byte	<_levelText26
.byte	<_levelText27
.byte	<_levelText28

_levelTextsLower_hi:
.byte	>_levelText0C
.byte	>_levelText0D
.byte	>_levelText0E
.byte	>_levelText0F
.byte	>_levelText10
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
.byte	>_levelText19
.byte	>_levelText1C
.byte	>_levelText1D
.byte	>_levelText1E
.byte	>_levelText1F
.byte	>_levelText20
.byte	>_levelText21
.byte	>_levelText10
.byte	>_levelText22
.byte	>_levelText23
.byte	>_levelText24
.byte	>_levelText25
.byte	>_levelText26
.byte	>_levelText27
.byte	>_levelText28
