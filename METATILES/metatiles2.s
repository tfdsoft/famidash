
.include "metatiles2.inc"

.export _metatiles2_top_left := metatiles2_top_left
.export _metatiles2_top_right := metatiles2_top_right
.export _metatiles2_bot_left := metatiles2_bot_left
.export _metatiles2_bot_right := metatiles2_bot_right
.export _metatiles2_attr := metatiles2_attr
.export _is2_solid := metatiles2_coll

metatiles2_top_left:
.repeat METATILES2_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_TL", I))
.endrepeat

metatiles2_top_right:
.repeat METATILES2_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_TR", I))
.endrepeat

metatiles2_bot_left:
.repeat METATILES2_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_BL", I))
.endrepeat

metatiles2_bot_right:
.repeat METATILES2_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_BR", I))
.endrepeat

metatiles2_attr:
.repeat METATILES2_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_AT", I))
.endrepeat

metatiles2_coll:
.repeat METATILES2_COUNT, I
  .byte .ident(.sprintf("METATILE_%d_CL", I))
.endrepeat
