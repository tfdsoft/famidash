
.segment "_pprg__rom__fixed"
    .include "./famistudio_ca65.s"

.segment "_pprg__rom__36"
    .org $a000
    .include "./EXPORTS/sfx.s"

.segment "_pprg__rom__37"
    .org $a000
    .include "./EXPORTS/music_0.s"

.segment "_pprg__rom__38"
    .org $a000
    .include "./EXPORTS/music_1.s"

.segment "_pprg__rom__39"
    .org $a000
    .include "./EXPORTS/music_2.s"
