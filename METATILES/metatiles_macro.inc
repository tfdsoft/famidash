
.ifndef __METATILE_P_INC
__METATILE_P_INC = 1

.global metatiles_top_left
.global metatiles_top_right
.global metatiles_bot_left
.global metatiles_bot_right
.global metatiles_attr
.global metatiles_coll


METATILES_COUNT .set 0

PAL_0 = (0)
PAL_1 = (1)
PAL_2 = (2)
PAL_3 = (3)

COL_FLOOR_CEIL = 9
COL_DEATH = 8
COL_ALL   = 7
COL_BOTTOM   = 6
COL_TOP   = 5
COL_DEATH_BOTTOM   = 4
COL_DEATH_TOP   = 3
COL_DEATH_LEFT   = 2
COL_DEATH_RIGHT   = 1
COL_NONE  = 0


.macro MetatileReserve name
.ident( .sprintf("METATILE_%s", name) ) = METATILES_COUNT
METATILES_COUNT .set METATILES_COUNT + 1
.endmacro

.macro Metatile name, tl, tr, bl, br, at, cl

.ident(.sprintf("METATILE_%d_TL", (METATILES_COUNT))) = (<tl)
.ident(.sprintf("METATILE_%d_TR", (METATILES_COUNT))) = (<tr)
.ident(.sprintf("METATILE_%d_BL", (METATILES_COUNT))) = (<bl)
.ident(.sprintf("METATILE_%d_BR", (METATILES_COUNT))) = (<br)
.ident(.sprintf("METATILE_%d_AT", (METATILES_COUNT))) = (<at)
.ident(.sprintf("METATILE_%d_CL", (METATILES_COUNT))) = (<cl)

.out .sprintf("METATILE_%s = $%02x", name, METATILES_COUNT)
MetatileReserve .sprintf("%s", name)

.endmacro

.endif