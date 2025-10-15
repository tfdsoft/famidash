
.segment "_pprg__rom__fixed"
    .include "./famistudio_ca65.s"

.segment "_pprg__rom__36"
    .org $a000
    .include "./sfx.s"

.segment "_pprg__rom__37"
    .org $a000
    .include "./music_0.s"

.segment "_pprg__rom__38"
    .org $a000
    .include "./music_1.s"

.segment "_pprg__rom__39"
    .org $a000
    .include "./music_2.s"
