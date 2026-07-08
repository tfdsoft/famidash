
;;; Exported by export_levels.py

.segment _LVL_NAME_BANK

.export _levelTextsUpper_lo, _levelTextsUpper_hi, _levelTextsLower_lo, _levelTextsLower_hi

.repeat 0, I
.import .ident(.sprintf("_levelText%02X", I))
.endrepeat

_levelTextsUpper_lo:

_levelTextsUpper_hi:

_levelTextsLower_lo:

_levelTextsLower_hi:
