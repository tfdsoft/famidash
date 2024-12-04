
.include "metatiles.inc"

.export _metatiles_top_left := metatiles_top_left
.export _metatiles_top_right := metatiles_top_right
.export _metatiles_bot_left := metatiles_bot_left
.export _metatiles_bot_right := metatiles_bot_right
.export _metatiles_attr := metatiles_attr
.export _metatiles_coll := metatiles_coll

.segment "XCD_BANK_02"	; same one as draw_screen, where they are used

metatiles_top_left:
.repeat METATILES_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_TL", I))
.endrepeat

metatiles_top_right:
.repeat METATILES_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_TR", I))
.endrepeat

metatiles_bot_left:
.repeat METATILES_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_BL", I))
.endrepeat

metatiles_bot_right:
.repeat METATILES_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_BR", I))
.endrepeat

metatiles_attr:
.repeat METATILES_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_AT", I))
.endrepeat

.segment "RODATA"

metatiles_coll:
.repeat METATILES_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_CL", I))
.endrepeat
