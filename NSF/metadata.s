.include "metadata_macro.inc"

RIFFChunkStart "auth"
.asciiz "Famidash"
.asciiz "Originals by 9 people, covers by 7 people"
.byte $C0, $A9
.asciiz " TFDSoft 2023-2024, [include more shit about OG composers here]"
.asciiz "alexmush"

RIFFChunkStart "plst"
.byte song_menu_theme, song_stereo_madness, song_back_on_track, song_polargeist
.byte song_dry_out, song_base_after_base, song_cant_let_go, song_jumper
.byte song_time_machine, song_cycles, song_xstep, song_clutterfunk
.byte song_theory_of_everything, song_electroman_adventures, song_custom_endgame, song_practice

RIFFChunkStart "psfx"
.repeat sfx_max+2, n
.byte song_max+n
.endrepeat

RIFFChunkStart "tlbl"
.asciiz "Time Machine"
.asciiz "Clutterfunk"
.asciiz "Decode ~ Endgame"
.asciiz "Practice ~ Stay Inside Me"
.asciiz "Menu Theme"
.asciiz "Polargeist"
.asciiz "Jumper"
.asciiz "Electroman Adventures"
.asciiz "Stereo Madness"
.asciiz "Back On Track"
.asciiz "Base After Base"
.asciiz "Cycles"
.asciiz "Dry Out"
.asciiz "Cant Let Go ~ Can't Let Go"
.asciiz "xStep"
.asciiz "Theory Of Everything"

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
AutMeta "Waterflame", "Zenith302, Vikrinox, alexmush"
AutMeta "Waterflame", "Zenith302, aquamarine.gay, Vikrinox"
AutMeta "Waterflame", "Vikrinox"
AutMeta "OcularNebula", "UserSniper"
AutMeta "RobTop", "Zenith302"
AutMeta "Step", "UserSniper, Zenith302, Vikrinox"
AutMeta "Waterflame", "zukinnyk, UserSniper, Zenith302"
AutMeta "Waterflame", "UserSniper, alexmush"
AutMeta "ForeverBound", "Zenith302, UserSniper"
AutMeta "DJVI", "aquamarine.gay"
AutMeta "DJVI", "Zenith302, UserSniper, Vikrinox, alexmush"
AutMeta "DJVI", "aquamarine.gay, alexmush"
AutMeta "DJVI", "UserSniper"
AutMeta "DJVI", "UserSniper, alexmush"
AutMeta "DJVI", "Vikrinox, alexmush"
AutMeta "Dj-Nate", "leejh20, UserSniper, Vikrinox, Zenith302"

.repeat sfx_max
.asciiz "UserSniper"
.endrepeat

.asciiz "VA: MDK"
.asciiz "VA: Joe"

; TODO: figure out wtf to do with the time

EndNSFERIFFList