CHUNK_COUNT .set 0

.macro RIFFChunkReserve
.ident( .sprintf("CHUNK_%d", CHUNK_COUNT) ):
CHUNK_COUNT .set CHUNK_COUNT + 1
.endmacro

.macro RIFFChunkStart ID
RIFFChunkReserve 
.out .sprintf("Chunk #%d ID: '%s'", CHUNK_COUNT-1, ID)
.dword .ident(.sprintf("CHUNK_%d", CHUNK_COUNT)) - .ident(.sprintf("CHUNK_%d", CHUNK_COUNT-1)) - 8
.byte ID
.endmacro

.macro EndNSFERIFFList
.ident( .sprintf("CHUNK_%d", CHUNK_COUNT) ):
.out "Chunk List Finish"
.byte "NEND"
.dword 0
.endmacro

.macro AutMeta OG, Cover
.asciiz .sprintf("Original by %s, covered by %s", OG, Cover)
.endmacro