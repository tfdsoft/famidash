.segment "_pprg__rom__fixed"
    .include "famistudio_ca65.s"
    .export FAMISTUDIO_DPCM_PTR
    
.segment "_pprg__rom__61"
    .include "./EXPORTS/sfx.s"