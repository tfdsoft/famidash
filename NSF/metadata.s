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

RIFFChunkStart "tlbl"
.asciiz "Menu Theme"
.asciiz "Stereo Madness"
.asciiz "Back On Track"
.asciiz "Polargeist"
.asciiz "Dry Out"
.asciiz "Base After Base"
.asciiz "Cant Let Go ~ Can't Let Go"
.asciiz "Jumper"
.asciiz "Time Machine"
.asciiz "Cycles"
.asciiz "xStep"
.asciiz "Clutterfunk"
.asciiz "Theory Of Everything"
.asciiz "Electroman Adventures"
.asciiz "Decode ~ Endgame"
.asciiz "Practice ~ Stay Inside Me"

.asciiz "Death SFX"
.asciiz "Click SFX"
.asciiz "LEVEL COMPLETE! SFX"
.asciiz "Coin SFX"
.asciiz "Chest Open SFX"
.asciiz "Orbs SFX"
.asciiz "Diamonds SFX"
.asciiz "Exit Level SFX"
.asciiz "Start Level SFX"
.asciiz "Invalid SFX"
.asciiz "Achievement Get SFX"

.asciiz "Geometry Dash Voice Clip"
.asciiz "FIRE IN THE HOLE! Voice Clip"

RIFFChunkStart "taut"
AutMeta "RobTop", "Zenith302" ; Menu
AutMeta "ForeverBound", "Zenith302, UserSniper" ; Stereo Madness
AutMeta "DJVI", "aquamarine.gay" ; Back On Track
AutMeta "Step", "UserSniper, Zenith302, Vikrinox" ; Polargeist
AutMeta "DJVI", "UserSniper" ; Dry Out
AutMeta "DJVI", "Zenith302, UserSniper, Vikrinox, alexmush" ; Base After Base
AutMeta "DJVI", "UserSniper, alexmush" ; Can't Let Go
AutMeta "Waterflame", "zukinnyk, UserSniper, Zenith302" ; Jumper
AutMeta "Waterflame", "Zenith302, Vikrinox, alexmush" ; Time Machine
AutMeta "DJVI", "aquamarine.gay, alexmush" ; Cycles
AutMeta "DJVI", "Vikrinox, alexmush" ; xStep
AutMeta "Waterflame", "Zenith302, aquamarine.gay, Vikrinox" ; Clutterfunk
AutMeta "Dj-Nate", "leejh20, UserSniper, Vikrinox, Zenith302" ; TOE
AutMeta "Waterflame", "cloud54, UserSniper, alexmush" ; Electroman Adventures
AutMeta "Waterflame", "Vikrinox" ;  Endgame
AutMeta "OcularNebula", "UserSniper" ; Practice

.repeat sfx_max
.asciiz "UserSniper"
.endrepeat

.asciiz "VA: MDK"
.asciiz "VA: Joe"

RIFFChunkStart "time"
.if REGION = 0
.dword (30017*2), 85550, 82817, 90700
.dword 81433, 85000, 80750, 86467
.dword 96067, 85933, 82350, 96583
.dword 89000, 87800, 79283, (239817*2)

.dword 383, 50, 3167, 683
.dword 100, 683, 683, 650
.dword 967, 633, 950

.dword 1150, 1650
.else
.dword (36080*2), 102840, 99540, 109000
.dword 97880, 102160, 97040, 104100
.dword 115460, 103280, 98980, 116080
.dword 106960, 105520, 95280, (288380*2)

.dword 460, 40, 3020, 700
.dword 120, 820, 820, 680
.dword 920, 640, 1140

.dword 1100, 1650

.endif

RIFFChunkStart "fade"
.dword $FFFFFFFF, 0, 0, 0
.dword 0, 0, 0, 0
.dword 0, 0, 0, 0
.dword 0, 0, 0, $FFFFFFFF

.repeat sfx_max+2
.dword 0
.endrepeat

EndNSFERIFFList