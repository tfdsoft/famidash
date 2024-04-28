
.ifndef __METATILE2_P_INC
__METATILE2_P_INC = 1

.global metatiles2_top_left
.global metatiles2_top_right
.global metatiles2_bot_left
.global metatiles2_bot_right
.global metatiles2_attr
.global metatiles2_coll


METATILES2_COUNT .set 0



.macro MetatileReserve2 name
.ident( .sprintf("METATILE2_%s", name) ) = METATILES2_COUNT
METATILES2_COUNT .set METATILES2_COUNT + 1
.endmacro

.macro Metatile2 name, tl, tr, bl, br, at, cl

.ident(.sprintf("METATILE2_%d_TL", (METATILES2_COUNT))) = (<tl)
.ident(.sprintf("METATILE2_%d_TR", (METATILES2_COUNT))) = (<tr)
.ident(.sprintf("METATILE2_%d_BL", (METATILES2_COUNT))) = (<bl)
.ident(.sprintf("METATILE2_%d_BR", (METATILES2_COUNT))) = (<br)
.ident(.sprintf("METATILE2_%d_AT", (METATILES2_COUNT))) = (<at)
.ident(.sprintf("METATILE2_%d_CL", (METATILES2_COUNT))) = (<cl)

.out .sprintf("METATILE2_%s = $%02x", name, METATILES2_COUNT)
MetatileReserve2 .sprintf("%s", name)

.endmacro

.endif