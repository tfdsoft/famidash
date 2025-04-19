.include "metadata_macro.inc"

RIFFChunkStart "auth"
.asciiz "Famidash"
.asciiz "Originals by 9 people, covers by 8 people"
.byte $C0, $A9
.asciiz " TFDSoft 2023-2024, RobTop 2014, ForeverBound 2012, DJVI 2011-2013, Step 2013, Waterflame 2008-2014, Dj-Nate 2010, OcularNebula 2013"
.asciiz "alexmush"

RIFFChunkStart "psfx"
.repeat sfx_max+2, n
.byte song_max+n
.endrepeat

; track labels, track authors, durations, fade durations
; generated by export.py from the metadata
.include "nsf_metadata.s"

EndNSFERIFFList