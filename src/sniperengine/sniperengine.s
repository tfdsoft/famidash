
; stuff from llvm-mos' mmc3 libraries. 
.importzp __bank_select_hi,__in_progress,__prg_8000,__prg_a000
__prg_c000 = __prg_8000
__rc0 = $00
__rc1 = $01
__rc2 = $02
__rc3 = $03
__rc4 = $04
__rc5 = $05
__rc6 = $06
__rc7 = $07
__rc8 = $08
__rc9 = $09
__rc10 = $0a
__rc11 = $0b
__rc12 = $0c
__rc13 = $0d
__rc14 = $0e
__rc15 = $0f
__rc16 = $10
__rc17 = $11
__rc18 = $12
__rc19 = $13
__rc20 = $14
__rc21 = $15

mmc3_IRQ_LATCH   = $c000
mmc3_IRQ_RELOAD  = $c001
mmc3_IRQ_DISABLE = $e000
mmc3_IRQ_ENABLE  = $e001


.macpack longbranch


.segment "ZEROPAGE"
se_palette_buffer:  .res 32
se_palette_pointer_bg:  .res 2
se_palette_pointer_spr: .res 2

se_name_upd_adr:    .res 1
se_name_upd_enable: .res 1
se_vram_index:      .res 1
se_vram_tmp_stack_pointer:  .res 1

se_joypad:          .res 7
se_mouse_mask:      .res 1
se_no_mouse:        .res 1
.export se_joypad,se_mouse_mask,se_no_mouse

se_post_nmi_ptr:    .res 2
.export se_post_nmi_ptr
se_irq_ptr:         .res 2
.export se_irq_ptr
se_sample_in_progress:  .res 1
.export se_sample_in_progress

;se_rle_pointer:     .res 2 ;__rc2 is used instead

.segment "BSS"
se_frame_count:     .res 1
.export se_frame_count

se_ppu_mask_var:    .res 1
se_ppu_ctrl_var:    .res 1
.export se_ppu_ctrl_var, se_ppu_mask_var

se_scroll_x:        .res 2
se_scroll_y:        .res 2

se_vram_update:     .res 1
se_palette_update:  .res 1
.export se_palette_update

se_sprite_id:       .res 1

se_rle_tag:         .res 1
se_rle_byte:        .res 1

se_music_bank:      .res 1
.export se_music_bank

se_vram_buffer = $100   ;DONUT BUFFER IS ALSO HERE!!!!


se_irq_table:       .res 32
se_irq_table_position:  .res 1
.export se_irq_table, se_irq_table_position


.segment "_pprg__rom__fixed__lo"
;;
;; API, USEFUL FOR ROM HACKING
;; STARTS AT $8000
;;

;; init
jmp se_init

;; nmi
jmp disable_nmi
jmp enable_nmi

;; mmc3 functions
jmp set_prg_a000
jmp set_prg_c000
jmp banked_call_a000
jmp set_chr_bank
jmp jsrfar


;; vram functions
.align 16
jmp se_vram_unrle
jmp se_vram_donut_decompress


;; ppu functions
.align 16
jmp se_wait_vsync
jmp se_wait_frames
jmp se_turn_off_rendering
jmp se_turn_on_rendering

jmp se_set_palette_background
jmp se_set_palette_sprites
jmp se_set_palette_all
jmp se_set_palette_color

jmp se_set_palette_brightness_background
jmp se_set_palette_brightness_sprites
jmp se_set_palette_brightness_all

jmp se_fade_palette_to
jmp se_clear_palette


;; oam stuff
jmp se_clear_sprites
jmp se_draw_sprite
jmp se_draw_metasprite


;; vram buffer
.align 16
;jmp se_set_vram_update  ; not needed
jmp se_set_vram_buffer

jmp se_one_vram_buffer
jmp se_string_vram_buffer


;; memory stuff
.align 16
jmp se_memory_fill
jmp se_memory_copy

;; music stuff
.align 16
.import se_music_play,se_sfx_play,se_music_update
jmp se_music_play   
jmp se_sfx_play 
jmp se_music_update 
jmp famistudio_music_stop
jmp famistudio_music_pause

;;  
;;  IDENTITY TABLE
;;  CAN BE USED TO SPEED UP SOME CALCULATIONS.
;;  STARTS AT $8100
;;
.align 256
.export se_identity_table
se_identity_table:
    .byte $00,$01,$02,$03,$04,$05,$06,$07,$08,$09,$0a,$0b,$0c,$0d,$0e,$0f
    .byte $10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$1a,$1b,$1c,$1d,$1e,$1f
    .byte $20,$21,$22,$23,$24,$25,$26,$27,$28,$29,$2a,$2b,$2c,$2d,$2e,$2f
    .byte $30,$31,$32,$33,$34,$35,$36,$37,$38,$39,$3a,$3b,$3c,$3d,$3e,$3f
    .byte $40,$41,$42,$43,$44,$45,$46,$47,$48,$49,$4a,$4b,$4c,$4d,$4e,$4f
    .byte $50,$51,$52,$53,$54,$55,$56,$57,$58,$59,$5a,$5b,$5c,$5d,$5e,$5f
    .byte $60,$61,$62,$63,$64,$65,$66,$67,$68,$69,$6a,$6b,$6c,$6d,$6e,$6f
    .byte $70,$71,$72,$73,$74,$75,$76,$77,$78,$79,$7a,$7b,$7c,$7d,$7e,$7f
    .byte $80,$81,$82,$83,$84,$85,$86,$87,$88,$89,$8a,$8b,$8c,$8d,$8e,$8f
    .byte $90,$91,$92,$93,$94,$95,$96,$97,$98,$99,$9a,$9b,$9c,$9d,$9e,$9f
    .byte $a0,$a1,$a2,$a3,$a4,$a5,$a6,$a7,$a8,$a9,$aa,$ab,$ac,$ad,$ae,$af
    .byte $b0,$b1,$b2,$b3,$b4,$b5,$b6,$b7,$b8,$b9,$ba,$bb,$bc,$bd,$be,$bf
    .byte $c0,$c1,$c2,$c3,$c4,$c5,$c6,$c7,$c8,$c9,$ca,$cb,$cc,$cd,$ce,$cf
    .byte $d0,$d1,$d2,$d3,$d4,$d5,$d6,$d7,$d8,$d9,$da,$db,$dc,$dd,$de,$df
    .byte $e0,$e1,$e2,$e3,$e4,$e5,$e6,$e7,$e8,$e9,$ea,$eb,$ec,$ed,$ee,$ef
    .byte $f0,$f1,$f2,$f3,$f4,$f5,$f6,$f7,$f8,$f9,$fa,$fb,$fc,$fd,$fe,$ff


;;  
;;  PALETTE BRIGHTNESS TABLE
;;  CAN BE USED TO SPEED UP SOME CALCULATIONS.
;;  STARTS AT $8200
;;
;.align 256
se_palette_brightness_table:
    .byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f ;0
    .byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f ;1
    .byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f ;2
    .byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f ;3
    
    .byte $00,$01,$02,$03,$04,$05,$06,$07,$08,$09,$0a,$0b,$0c,$0d,$0e,$0f ;4

    .byte $10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$1a,$1b,$1c,$1d,$1e,$00 ;5

    .byte $20,$21,$22,$23,$24,$25,$26,$27,$28,$29,$2a,$2b,$2c,$2d,$2e,$10 ;6

    .byte $30,$31,$32,$33,$34,$35,$36,$37,$38,$39,$3a,$3b,$3c,$3d,$3f,$20 ;7

    .byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30 ;8
    .byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
    .byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
    .byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30




;;
;;  INIT
;;  SETS UP THE ENGINE FOR YOU
;;
.export se_init
.proc se_init
    and #%00000001 ; just the zeroth bit.
    ror 
    ror ; now its the seventh! 
    ora __bank_select_hi
    sta __bank_select_hi

    ; set post-nmi pointer
    lda #<nofunction
    ldx #>nofunction
    sta se_post_nmi_ptr + 0
    stx se_post_nmi_ptr + 1
    sta se_irq_ptr + 0
    stx se_irq_ptr + 1
    sta se_irq_table + 1
    stx se_irq_table + 2
    dec se_irq_table + 0

    ; disable apu frame counter irq
    lda #$c0
    sta $4017
    ; disable mapper irq
    sta $e000

    jsr se_clear_palette
    jsr se_clear_sprites

    ; set up default banks
    lda #0
    ldx #0
    jsr set_chr_bank
    lda #1
    inx
    inx
    jsr set_chr_bank
    lda #2
    inx
    inx
    jsr set_chr_bank
    lda #3
    inx
    jsr set_chr_bank
    lda #4
    inx
    jsr set_chr_bank
    lda #5
    inx
    jsr set_chr_bank

    ; set up vram buffer
    jsr se_set_vram_buffer

    ; enable sram
    lda #%10000000
    sta $a001

    rts
.endproc

.export nofunction
.proc nofunction
    rts
.endproc


.export disable_nmi
.proc disable_nmi
    lda se_ppu_ctrl_var
    and #%01111111
    sta se_ppu_ctrl_var
    sta $2000
    rts
.endproc

.export enable_nmi
.proc enable_nmi
    lda se_ppu_ctrl_var
    ora #%10000000
    sta se_ppu_ctrl_var
    sta $2000
    rts
.endproc

;;
;;  MMC3 BANKING FUNCTIONS
;;  CODE IS FROM THE LLVM-MOS-SDK (modified, of course)
;;  EVERYTHING FROM THIS POINT FORWARD IS AT $8300
;;
.export set_prg_c000
.proc set_prg_c000
	sta __prg_c000
	tax
	lda #%00000110
	ora __bank_select_hi
	jmp __set_reg_retry
.endproc

.export set_prg_a000
.proc set_prg_a000
	sta __prg_a000
	tax
	lda #%00000111
	ora __bank_select_hi
	;jmp __set_reg_retry    ;; SNIPERENGINE MODIFICATION:
.endproc                    ;; why not just fall through here?

.proc __set_reg_retry
	dec __in_progress
	sta $8000
	stx $8001
	bit __in_progress
	bpl __set_reg_retry
	lda #0
	sta __in_progress
	rts
.endproc

.export banked_call_a000
.proc banked_call_a000
    .import __call_indir
	tay
	lda __prg_a000
	pha
	tya
	jsr set_prg_a000
	lda __rc2
	sta __rc18
	lda __rc3
	sta __rc19
	jsr __call_indir
	pla
	jsr set_prg_a000
	rts
.endproc

.export set_chr_bank
.proc set_chr_bank
	ora __bank_select_hi
	sta $8000
	stx $8001
	lda #0
	sta __in_progress
	rts
.endproc

.proc set_chr_bank_retry
	ora __bank_select_hi
	jmp __set_reg_retry
.endproc

.export jsrfar
.proc jsrfar
    .import __call_indir

    ; adapted from commander x16 rom.
    ; basically:
    ;   jsr jsrfar
    ;   .word address
    ;   .bank bank

    php ; reserve 1 byte
    php ; save registers and status

    clc
    jsrfare:    ; emulation mode
        pha
        txa
        pha
        tya
        pha

        tsx
        lda $106,x 
        sta __rc16
        
        adc #3
        sta $106,x 
        lda $107,x 
        sta __rc17

        ldy #1
        lda (__rc16),y 
        sta __rc18
        iny
        lda (__rc16),y 
        sta __rc19

        lda __prg_a000
        sta $105,x 
        iny 
        lda (__rc16),y 
        jsr set_prg_a000
        pla
        tay
        pla
        tax
        pla
        plp
        jsr __call_indir
        php
        pha
        txa
        pha
        tsx
        lda $104,x 
        jsr set_prg_a000
        tsx
        lda $103,x 
        sta $104,x 
        pla
        tax
        pla
        plp
        plp
        rts

.endproc



;;
;; DONUT CODE, MODIFIED TO USE LLVM-MOS' SYNTAX:
;;

; "Donut", NES CHR codec decompressor,
; Copyright (c) 2018  Johnathan Roatch
;
; Copying and distribution of this file, with or without
; modification, are permitted in any medium without royalty provided
; the copyright notice and this notice are preserved in all source
; code copies.  This file is offered as-is, without any warranty.
;
; Version History:
; 2019-02-15: Swapped the M and L bits, for conceptual consistency.
;             Also rearranged branches for speed.
; 2019-02-07: Removed "Duplicate" block type, and moved
;             Uncompressed block to below 0xc0 to make room
;             for block handling commands in the 0xc0~0xff space
; 2018-09-29: Removed block option of XORing with existing block
;             for extra speed in decoding.
; 2018-08-13: Changed the format of raw blocks to not be reversed.
;             Register X is now an argument for the buffer offset.
; 2018-04-30: Initial release.
;

.export donut_decompress_block, donut_block ;, donut_block_ayx, donut_block_x
.export donut_block_buffer
.exportzp donut_stream_ptr
; .exportzp donut_block_count

; jroweboy: We alias these with __rc5 - __rc20
; since we only call donut from the main thread its fine
temp = $05  ; 15 bytes are used

; jroweboy - donut starts at this addr + 64 because ???? but it works out just fine anyway
donut_block_buffer = $0110  ; 64 bytes

; .segment "_pzp":zeropage
; donut_stream_ptr:       .res 2
; donut_block_count:      .res 1

;;
; helper subroutine for passing parameters with registers
; decompress X*64 bytes starting at AAYY to PPU_DATA
; .proc donut_block_ayx
;   sty donut_stream_ptr+0
;   sta donut_stream_ptr+1
;   stx donut_block_count
; ;,; jmp donut_block_x
; .endproc

donut_stream_ptr = $02
; donut_block_count = $00

.proc donut_block
PPU_DATA = $2007
  ; lda $02
  ; sta donut_stream_ptr
  ; lda $03
  ; sta donut_stream_ptr+1
    block_loop:
        ldx #0
        jsr .loword(donut_decompress_block)
        cpx #64
        bne end_block_upload
        ; bail if donut_decompress_block does not
        ; advance X by 64 bytes, indicating a header error.

    tsx
    stx se_vram_tmp_stack_pointer
    ldx #$0f    ; set temporary stack location for faster writes
    txs

    ldx #256 - 64
    upload_loop:
        pla ;lda a:donut_block_buffer - (256 - 64), x
        sta PPU_DATA
        inx
        bmi upload_loop

    ldx se_vram_tmp_stack_pointer
    txs
    bne block_loop

    ; ldx donut_block_count
    ; bne block_loop
    end_block_upload:
    
    
    rts
.endproc

;;
; Decompresses a single variable sized block pointed to by donut_stream_ptr
; Outputing 64 bytes to donut_block_buffer offsetted by the X register.
; On success, 64 will be added to the X register, donut_block_count
; will be decremented, and Y will contain the number of bytes read.
;
; Block header:
; LMlmbbBR
; |||||||+-- Rotate plane bits (135° reflection)
; ||||000--- All planes: 0x00
; ||||010--- L planes: 0x00, M planes:  pb8
; ||||100--- L planes:  pb8, M planes: 0x00
; ||||110--- All planes: pb8
; ||||001--- In another header byte, For each bit starting from MSB
; ||||         0: 0x00 plane
; ||||         1: pb8 plane
; ||||011--- In another header byte, Decode only 1 pb8 plane and
; ||||       duplicate it for each bit starting from MSB
; ||||         0: 0x00 plane
; ||||         1: duplicated plane
; ||||       If extra header byte = 0x00, no pb8 plane is decoded.
; ||||1x1--- Reserved for Uncompressed block bit pattern
; |||+------ M planes predict from 0xff
; ||+------- L planes predict from 0xff
; |+-------- M = M XOR L
; +--------- L = M XOR L
; 00101010-- Uncompressed block of 64 bytes (bit pattern is ascii '*' )
; Header >= 0xc0: Error, avaliable for outside processing.
; X >= 192: Also returns in Error, the buffer would of unexpectedly page warp.
;
; Trashes Y, A, temp 0 ~ temp 15.
; bytes: 253, cycles: 1269 ~ 7238.
.proc donut_decompress_block
    plane_buffer        = temp+0 ; 8 bytes
    pb8_ctrl            = temp+8
    temp_y              = pb8_ctrl
    even_odd            = temp+9
    block_offset        = temp+10
    plane_def           = temp+11
    block_offset_end    = temp+12
    block_header        = temp+13
    is_rotated          = temp+14
    ;_donut_unused_temp  = temp+15
    ldy #$00
    txa
    clc
    adc #64
    bcs exit_error
    sta block_offset_end

    lda (donut_stream_ptr), y
    iny  ; Reading input bytes are now post-increment.
    sta block_header

    cmp #$2a
    beq do_raw_block
    ;,; bne do_normal_block
    do_normal_block:
    cmp #$c0
    bcc continue_normal_block
    ;,; bcs exit_error
    exit_error:
    rts
    ; If we don't exit here, xor_l_onto_m can underflow into zeropage.

    ; I'm inserting these things here instead of above the donut_decompress_block
    ; at the cost of 1 cycle with the continue_normal_block branch for these reasons:
    ; The start of the main routine remains at the start of the .proc scope
    ; and I can save 1 byte with 'bcs end_block'

    read_plane_def_from_stream:
    ror
    lda (donut_stream_ptr), y
    iny
    bne plane_def_ready  ;,; jmp plane_def_ready

    do_raw_block:
    ;,; ldx block_offset
    raw_block_loop:
        lda (donut_stream_ptr), y
        iny
        sta a:donut_block_buffer, x
        inx
        cpy #65  ; size of a raw block
    bcc raw_block_loop
    bcs end_block  ;,; jmp end_block

    continue_normal_block:
    stx block_offset

    ;,; lda block_header
    and #%11011111
        ; The 0 are bits selected for the even ("lower") planes
        ; The 1 are bits selected for the odd planes
        ; bits 0~3 should be set to allow the mask after this to work.
    sta even_odd
        ; even_odd toggles between the 2 fields selected above for each plane.

    ;,; lda block_header
    lsr
    ror is_rotated
    lsr
    bcs read_plane_def_from_stream
    ;,; bcc unpack_shorthand_plane_def
    unpack_shorthand_plane_def:
        and #$03
        tax
        lda .loword(shorthand_plane_def_table), x
    plane_def_ready:
    ror is_rotated
    sta plane_def
    sty temp_y

    clc
    lda block_offset
    plane_loop:
        adc #8
        sta block_offset

        lda even_odd
        eor block_header
        sta even_odd

        ;,; lda even_odd
        and #$30
        beq not_predicted_from_ff
        lda #$ff
        not_predicted_from_ff:
        ; else A = 0x00

        asl plane_def
        bcc do_zero_plane
        ;,; bcs do_pb8_plane
    do_pb8_plane:
        ldy temp_y
        bit is_rotated
        bpl no_rewind_input_pointer
        ldy #$02
        no_rewind_input_pointer:
        tax
        lda (donut_stream_ptr), y
        iny
        sta pb8_ctrl
        txa

        ;,; bit is_rotated
    bvs do_rotated_pb8_plane
    ;,; bvc do_normal_pb8_plane
    do_normal_pb8_plane:
        ldx block_offset
        ;,; sec  ; C is set from 'asl plane_def' above
        rol pb8_ctrl
        pb8_loop:
        bcc pb8_use_prev
            lda (donut_stream_ptr), y
            iny
        pb8_use_prev:
        dex
        sta a:donut_block_buffer, x
        asl pb8_ctrl
        bne pb8_loop
        sty temp_y
    ;,; beq end_plane  ;,; jmp end_plane
    end_plane:
        bit even_odd
        bpl not_xor_m_onto_l
        xor_m_onto_l:
        ldy #8
        xor_m_onto_l_loop:
            dex
            lda a:donut_block_buffer, x
            eor a:donut_block_buffer+8, x
            sta a:donut_block_buffer, x
            dey
        bne xor_m_onto_l_loop
        not_xor_m_onto_l:

        bvc not_xor_l_onto_m
        xor_l_onto_m:
        ldy #8
        xor_l_onto_m_loop:
            dex
            lda a:donut_block_buffer, x
            eor a:donut_block_buffer+8, x
            sta a:donut_block_buffer+8, x
            dey
        bne xor_l_onto_m_loop
        not_xor_l_onto_m:

        lda block_offset
        cmp block_offset_end
    bcc plane_loop
    ldy temp_y
    end_block:
    ;,; sec
    clc
    tya
    adc donut_stream_ptr+0
    sta donut_stream_ptr+0
    bcc add_stream_ptr_no_inc_high_byte
        inc donut_stream_ptr+1
    add_stream_ptr_no_inc_high_byte:
    ldx block_offset_end
    ; dec donut_block_count
    rts

    do_zero_plane:
    ldx block_offset
    ldy #8
    fill_plane_loop:
        dex
        sta a:donut_block_buffer, x
        dey
    bne fill_plane_loop
    beq end_plane  ;,; jmp end_plane

    do_rotated_pb8_plane:
    ldx #8
    buffered_pb8_loop:
        asl pb8_ctrl
        bcc buffered_pb8_use_prev
        lda (donut_stream_ptr), y
        iny
        buffered_pb8_use_prev:
        dex
        sta plane_buffer, x
    bne buffered_pb8_loop
    sty temp_y
    ldy #8
    ldx block_offset
    flip_bits_loop:
        asl plane_buffer+0
        ror
        asl plane_buffer+1
        ror
        asl plane_buffer+2
        ror
        asl plane_buffer+3
        ror
        asl plane_buffer+4
        ror
        asl plane_buffer+5
        ror
        asl plane_buffer+6
        ror
        asl plane_buffer+7
        ror
        dex
        sta a:donut_block_buffer, x
        dey
    bne flip_bits_loop
    beq end_plane  ;,; jmp end_plane

    shorthand_plane_def_table:
    .byte $00, $55, $aa, $ff
.endproc


;;
;; END OF DONUT CODE
;;


;; see the header
;.export se_vram_address
;.proc se_vram_address
;    stx $2006
;    sta $2006
;    rts
;.endproc

.export se_vram_unrle
.proc se_vram_unrle
    pha

    se_rle_pointer = __rc2

    ldy se_rle_pointer+0
    lda #0
    sta se_rle_pointer+0

    lda (se_rle_pointer),y
    sta se_rle_tag
    iny
    bne :+
    inc se_rle_pointer+1
    :
    
    pla
    bne @ignorezero_loop

    @1:
        lda (se_rle_pointer+0),y
        iny
        bne :+
        inc se_rle_pointer+1
        :
        cmp se_rle_tag
        beq @2
        sta $2007
        sta se_rle_byte
        bne @1

    @2:
        lda (se_rle_pointer+0),y
        beq @exit
        iny
        bne :+
        inc se_rle_pointer+1
        :
        tax
        lda se_rle_byte

    @3:
        sta $2007
        dex
        bne @3
        beq @1
    @exit:
    rts

    @ignorezero_loop:
        lda (se_rle_pointer+0),y
        iny
        bne :+
        inc se_rle_pointer+1
        :
        cmp se_rle_tag  ; is it the tag?
        beq @grab_run_length
        sta se_rle_byte

        cmp #0
        beq :+
        sta $2007
        bne @ignorezero_loop
        :
        lda $2007
        jmp @ignorezero_loop

    @grab_run_length:
        lda (se_rle_pointer+0),y
        beq @exit
        iny
        bne :+
        inc se_rle_pointer+1
        :
        tax
        lda se_rle_byte
        beq @read_loop

    @write_loop:
        sta $2007
        dex
        bne @write_loop
        beq @ignorezero_loop

    @read_loop:
        lda $2007
        dex
        bne @read_loop
        beq @ignorezero_loop
.endproc

.export se_vram_donut_decompress
.proc se_vram_donut_decompress
    ;     A = bank number
    ; __rc2 = ptr (lo)
    ; __rc3 = ptr (hi)

    ; inlined for extra SPEED
    tax
    lda __prg_a000
    pha

    ; stop the vram buffer *juuuuuust* in case
    lda #255
    sta $100

    txa

    jsr set_prg_a000

    ; disable nmi
    lda se_ppu_ctrl_var
    and #%01111111
    sta $2000

    jsr donut_block

    ; revert ppu_ctrl
    lda se_ppu_ctrl_var
    sta $2000

    pla
    jsr set_prg_a000
    rts
.endproc






;;
;;  NESLIB-ESQUE FUNCTIONS
;;
.export se_wait_vsync
.proc se_wait_vsync
    lda #1
    sta se_vram_update
    lda se_frame_count
    @wait:
        cmp se_frame_count
        beq @wait
    rts
.endproc

.export se_wait_frames
.proc se_wait_frames
    tax
    @wait:
        jsr se_wait_vsync
        dex
        bne @wait
    rts
.endproc
;   enable/disable rendering

.export se_turn_off_rendering
.proc se_turn_off_rendering
    lda se_ppu_mask_var
    and #%11100111
    sta se_ppu_mask_var
    jmp se_wait_vsync
.endproc

.export se_turn_on_rendering
.proc se_turn_on_rendering
    lda se_ppu_mask_var
    ora #%00011000
    sta se_ppu_mask_var
    jmp se_wait_vsync
.endproc


;
.export se_set_palette_background
.proc se_set_palette_background
    ldx #0
    lda #$10
    bne __se_pal_copy ; bra
.endproc

.export se_set_palette_sprites
.proc se_set_palette_sprites
    ldx #$10
    txa 
    bne __se_pal_copy ; bra
.endproc

.export se_set_palette_all
.proc se_set_palette_all
    ldx #0
    lda #$20
    ;bne __se_pal_copy ; bra ; fall through
.endproc

.proc __se_pal_copy
    sta __rc4
    ldy #0
    @loop:
        lda (__rc2), y
        sta se_palette_buffer, x
        inx
        iny
        dec __rc4
        bne @loop
    inc se_palette_update
    rts
.endproc

.export se_set_palette_color
.proc se_set_palette_color
    and #$1f
    stx __rc2 ; swap a and x
    tax
    lda __rc2
    sta se_palette_buffer, x
    inc se_palette_update
    rts
.endproc

.export se_set_palette_brightness_background
.proc se_set_palette_brightness_background
    asl
    asl
    asl
    asl
    sta     __rc2
    lda     #<se_palette_brightness_table
    clc
    adc     __rc2
    tax
    lda     #>se_palette_brightness_table
    adc     #0
    stx     se_palette_pointer_bg+0
    sta     se_palette_pointer_bg+1
    inc     se_palette_update
    rts
.endproc

.export se_set_palette_brightness_sprites
.proc se_set_palette_brightness_sprites
    asl
    asl
    asl
    asl
    sta     __rc2
    lda     #<se_palette_brightness_table
    clc
    adc     __rc2
    tax
    lda     #>se_palette_brightness_table
    adc     #0
    stx     se_palette_pointer_spr+0
    sta     se_palette_pointer_spr+1
    inc     se_palette_update
    rts
.endproc

.export se_set_palette_brightness_all
.proc se_set_palette_brightness_all
    pha
    jsr se_set_palette_brightness_background
    pla
    jmp se_set_palette_brightness_sprites
.endproc

.export se_fade_palette_to
.proc se_fade_palette_to
    tay
	lda __rc20
	pha
	lda __rc21
	pha
	stx __rc20 ;to
	sty __rc21 ;from
	jmp @check_equal

    @fade_loop:
        lda #2
        jsr se_wait_frames ;wait 4 frames

        lda __rc21 ;from
        cmp __rc20 ;to
        bcs @more

    @less:
        clc
        adc #1
        sta __rc21 ;from
        jsr se_set_palette_brightness_all
        jmp @check_equal

    @more:
        sec
        sbc #1
        sta __rc21 ;from
        jsr se_set_palette_brightness_all

    @check_equal:
        lda __rc21
        cmp __rc20
        bne @fade_loop

    @done:
	jsr se_wait_vsync ;do 1 final, make sure the last change goes
	pla
	sta __rc21
	pla
	sta __rc20
	rts
.endproc


.export se_clear_palette
.proc se_clear_palette
    ldx #$20
    lda #0
    @loop:
        sta se_palette_buffer, x
        dex
        bne @loop
    inc se_palette_update
    rts
.endproc

;.export
;.proc
;
;.endproc


;.export
;.proc
;
;.endproc


;.export
;.proc
;
;.endproc



.export se_clear_sprites
.proc se_clear_sprites
    .import sprite_buffer
    ldx #0
    stx se_sprite_id
    lda #$ff
    @loop:
        sta sprite_buffer,x
        inx
        inx
        inx
        inx
        bne @loop
    rts
.endproc 

.export se_draw_sprite
.proc se_draw_sprite
    .import sprite_buffer
    ;   A:  x
    ;   X:  y
    ;__rc2: tile
    ;__rc3: attributes
    ldy se_sprite_id
    sta sprite_buffer+3,y

    dex
    txa
    sta sprite_buffer+0,y

    lda __rc2
    sta sprite_buffer+1,y 

    lda __rc3
    sta sprite_buffer+2,y 

    tya
    clc
    adc #4
    sta se_sprite_id
    rts
.endproc

.export se_draw_metasprite
.proc se_draw_metasprite
    .import sprite_buffer
    ;   A:  x
    ;   X:  y
    ;__rc2: pointer (lo)
    ;__rc3: pointer (hi)
    sta __rc4
	stx __rc5
	ldx se_sprite_id
	ldy #0
    @loop:
        lda (__rc2),y		;x offset
        cmp #$80
        beq @exit
        iny
        clc
        adc __rc4
        sta sprite_buffer+3,x
        lda (__rc2),y		;y offset
        iny
        clc 
        adc __rc5
        clc
        sbc #0
        sta sprite_buffer+0,x
        lda (__rc2),y		;tile
        iny
        sta sprite_buffer+1,x
        lda (__rc2),y		;attribute
        iny
        sta sprite_buffer+2,x
        inx
        inx
        inx
        inx
        jmp @loop
    @exit:
    stx se_sprite_id
    rts
.endproc



;;
;;  VRAM BUFFER STUFF
;;  easily write to the screen with these several cool tricks!
;;
.proc __post_vram_update
    ldx #255
    stx se_vram_buffer
    inx
    stx se_vram_index
    ldx $2002
    rts
.endproc

.export se_set_vram_update
.proc se_set_vram_update
    sta se_name_upd_adr+0
    stx se_name_upd_adr+1
    inc se_name_upd_enable
    rts
.endproc

.export se_set_vram_buffer
.proc se_set_vram_buffer
    lda #<se_vram_buffer
    ldx #>se_vram_buffer
    jsr se_set_vram_update
    jsr __post_vram_update
    rts
.endproc

.export se_one_vram_buffer
.proc se_one_vram_buffer
    ldy se_vram_index

    pha
    lda __rc2
    sta se_vram_buffer,y
    txa
    iny
    sta se_vram_buffer,y
    pla
    iny
    sta se_vram_buffer,y
    lda #$ff
    iny
    sta se_vram_buffer,y
    sty se_vram_index

    rts
.endproc

.export se_string_vram_buffer
.proc se_string_vram_buffer
    pha

    ; write high byte of address
    txa
    ora #$40
    ldx se_vram_index
    sta se_vram_buffer,x

    ; write low byte of address
    pla
    inx
    sta se_vram_buffer,x

    ; save index for later
    inx
    txa
    pha
    inx

    ;ldx se_identity_table,y ;tyx
    ldy #0

    @copy_string:
        lda (__rc2),y
        beq :+
        sta se_vram_buffer,x
        inx
        iny
        bne @copy_string
    :
    stx se_vram_index

    lda #$ff
    sta se_vram_buffer,x

    ; length of string is in y, put that at index 2
    pla
    tax
    tya
    sta se_vram_buffer,x

    rts
.endproc

; system from neslib, modified to be  T H E  S P E E D
.proc flush_vram_update2
    tsx
    stx se_vram_tmp_stack_pointer

    ; push new stack value
    ldx #$ff
    txs

    @1:
    ; ldy #0
    __get_next_instruction:
        pla
        tax
        cmp #255
        beq @exit

        sta __rc18
        bit __rc18 ; V if horizontal, N if vertical

        bvs @update_horizontal_sequence
        bvc @update_single_tile
        ;cmp #$40
        ;bcc @update_single_tile

        ;not horizontal? save upper address byte for arithmetic
        ;tax
        ;lda se_ppu_ctrl_var
        ;cpx #$80
        ;bmi @update_horizontal_sequence
        ;cpx #$ff
        ;beq @exit

    @update_vertical_sequence:
        lda se_ppu_ctrl_var
        ora #$04
        bne @update_common_sequence

    @update_single_tile:
        sta $2006
        pla
        sta $2006
        pla
        sta $2007
        clc
        bcc __get_next_instruction

    @update_horizontal_sequence:
        lda se_ppu_ctrl_var
        and #$fb

    @update_common_sequence:
        sta $2000

        txa
        and #$3f

        sta $2006
        pla
        sta $2006
        pla

        bmi @update_repeated_byte

        tax
    ;@update_common_sequence_loop:
        ;pla
        ;sta $2007
        ;dex
        ;bne @update_common_sequence_loop

        ;; larger overhead, but the fastest possible writes
        ;tax
        ;lda the_funny_fours_table_lmao,x
        asl
        asl
        tay
        lda #<pla_sta_2007_table_end ; low byte
        ldx #>pla_sta_2007_table_end ; high byte
        sec
        sbc se_identity_table,y
        bcs:+   ;; TODO: align to a page boundary
        dex     ;; so i don't have to decrement x
        :
        sta __rc18
        stx __rc19
        
        jmp (__rc18)

    @update_repeated_byte:
        and #$7f
        tax
        pla
    @update_repeated_byte_loop:
        sta $2007
        dex
        bne @update_repeated_byte_loop

        lda se_ppu_ctrl_var
        sta $2000

        bne __get_next_instruction

    @exit:
    ldx se_vram_tmp_stack_pointer
    txs
    jmp __post_vram_update

    return_to_flush_vram_update:
        


    ;.align 256
    the_funny_pla_sta_2007_table_lmao:
        .repeat 32,i
            pla
            sta $2727
        .endrepeat
    pla_sta_2007_table_end:

    lda se_ppu_ctrl_var
    sta $2000
    jmp __get_next_instruction
.endproc



;;
;;  MEMORY FUNCTIONS
;;  move memory around!
;;

.export se_memory_fill
.proc se_memory_fill
    ;   A: value to fill with
    ;   X: length of memory region (lo)
    ;__rc2: ptr to memory to fill (lo)
    ;__rc3: ptr to memory to fill (hi)
    ;__rc4: length of memory region (hi)

    
    pha
    ldy __rc2 ; save low byte of memory ptr
    lda #0
    sta __rc2 ; write 0 to low byte to save cycles later

    ; is the pointer in the $2xxx region? (likely ppu_data)
    lda __rc3
    and #$f0 ; mask off the lower four bits
    cmp #$20
    beq @no_inc_pointer
    
    pla

    ; decrement x by one
    dex
    cpx #$ff
    bne @inc_loop
    dec __rc4

    @inc_loop:
        sta (__rc2),y 
        iny
        bne :+ ; inc pointer
        inc __rc3
        : 
        dex
        bne @inc_loop
    
    @il_is_remaining_length_zero:
        cpx __rc4 ; x should be zero here
        beq @done
        dec __rc4
        jmp @inc_loop


    @no_inc_pointer:
    pla

    @no_inc_loop:
        sta $2007 ; using indexed instructions breaks it :sob: 
        dex
        bne @no_inc_loop

    @nil_is_remaining_length_zero:
        cpx __rc4
        beq @done
        dec __rc4
        jmp @no_inc_loop

    @done:
    rts
        

.endproc

; memcpy(*to, *from, numBytes);
.export se_memory_copy
.proc se_memory_copy
    ;   A: length of memory region (lo)
    ;   X: length of memory region (hi)
    ;__rc2: ptr to memory to (lo)
    ;__rc3: ptr to memory to (hi)
    ;__rc4: ptr to memory from (lo)
    ;__rc5: ptr to memory from (hi)

    stx __rc6 ; high byte of length is now in a zp register
    tax
    ldy #0

    pha
    ; is the pointer in the $2xxx region? (likely ppu_data)
    lda __rc3
    and #$f0 ; mask off the lower four bits
    cmp #$20
    beq @no_inc_loop_entry
    pla

    @inc_loop:
        lda (__rc4),y 
        sta (__rc2),y 
        iny
        bne :+ ; inc pointer if Y=0
            inc __rc3
            inc __rc5
        :
        dex
        bne @inc_loop
    ; is X equal to zero? if so, decrement __rc6
        dec __rc6
        bpl @inc_loop ; fall through if X is negative
    rts

    @no_inc_loop_entry:
        pla

    @no_inc_loop:
        lda (__rc4),y 
        sta $2007 
        iny
        bne :+ ; inc pointer if Y=0
            inc __rc3
            inc __rc5
        :
        dex
        bne @no_inc_loop
    ; is X equal to zero? if so, decrement __rc6
        dec __rc6
        bpl @no_inc_loop ; fall through if X is negative
    rts
.endproc



;;
;;  MUSIC STUFF
;;  music and sound effects, powered by FamiStudio!
;;
    
    ; see the header file




;;
;;  OAM DMA SHENANIGANS
;;  ok so basically, controller reads aligned to OAM DMA
;;

MouseBoundsMin:
    .byte 1,1
MouseBoundsMax:
    .byte 254,239


.export se_safe_controller_polling
.proc se_safe_controller_polling
    .export joypad1
    .export joypad2
    joypad2 = se_joypad+1
    joypad1 = se_joypad+4
    controller_port_1 = $4016
    controller_port_2 = $4017
    mouse_port = controller_port_2
    controller_port = controller_port_1
    kMouseZero = 0
    kMouseButtons = 1
    kMouseY = 2
    kMouseX = 3

    ; save registers (this *is* called from nmi, after all)
    lda __rc2
    pha
    lda __rc3
    pha
    lda __rc4
    pha
    lda __rc6
    pha
    lda __rc7
    pha
    
    ;save previous controller state
    lda joypad1
    sta __rc6

    ;save previous controller state
    lda joypad2
    sta __rc7

    ;save previous mouse state
    lda se_joypad + kMouseY
    sta __rc2
    lda se_joypad + kMouseX
    sta __rc3
    lda se_joypad + kMouseButtons
    sta __rc4

    ;strobe joypads
    ldx #0
    ldy #1
    sty se_joypad
    sty controller_port_1
    stx controller_port_1

    ;INITIATE THE DMA!
    lda #2
    sta $4014

    ; poll
    @poll_mouse:
        lda se_mouse_mask    ; get put get*     *576  // Starts: 4, 158, 312, 466, [620]
        and mouse_port   ; put get put GET
        cmp #1           ; put get
        rol se_joypad,x        ; put get put get* PUT GET  *432
        bcc @poll_mouse            ; put get (put)

        inx                ; put get
        cpx #4           ; put get
        sty se_joypad,x        ; put get put GET
        bne @poll_mouse             ; put get (put)

    @poll_controller:
        lda controller_port ; put get put GET        // Starts: 619
        and #3           ; put get*         *672
        cmp #1           ; put get
        rol joypad1 ; put get put get put    // This can desync, but we finish before it matters.
        bcc @poll_controller             ; get put (get)

    ;".if 0" // TODO support SNES extra buttons 
    ;    "STY joypad1+1" // get put get
    ;    "NOP"                // put get
    ;"1:"
    ;    "LDA CONTROLLER_PORT \n" // put get* put GET *848  // Starts: 751, [879]
    ;    "AND #$03 \n"           // put get
    ;    "CMP #$01 \n"           // put get
    ;    "ROL joypad1+1 \n" // put get put get put    // This can desync, but we finish before it matters.
    ;    "BCC 1b \n"             // get* put (get)   *860


    ; calculate the remaining fields:
    ; pressed
    lda __rc6
    eor #$ff
    and joypad1
    sta joypad1 + 1

    ; released
    lda joypad1
    eor #$ff
    and __rc6
    sta joypad1 + 2

    ; Check the report to see if we have a snes mouse plugged in
    lda se_joypad + kMouseButtons
    and #15
    cmp #1
    beq @snes_mouse_detected
        ; no mouse? treat this as a standard controller instead
        lda se_joypad + kMouseZero
        sta joypad2

        ; pressed
        lda __rc7
        eor #$ff
        and joypad2
        sta joypad2 + 1

        ; released
        lda joypad1
        eor #$ff
        and __rc7
        sta joypad2 + 2

        ; no snes mouse, so leave the first field empty
        ldx #0
        stx se_joypad + kMouseZero
        inx
        stx se_no_mouse
        jmp @exit

    @snes_mouse_detected:
        ldx #1

    @loop:
        lda se_joypad + kMouseY,x
        bpl :+
            ; subtract the negative number instead
            and #$7f
            sta se_joypad + kMouseZero
            lda __rc2,x
            sec
            sbc se_joypad + kMouseZero
            ; check if we underflowed
            bcc @wrappednegative

            ;check lower bounds
            cmp MouseBoundsMin,x
            bcs @setvalue   ; didn't wrap so set the value now
        
        @wrappednegative:
            lda MouseBoundsMin,x
            jmp @setvalue

        :   ; add the positive number
            clc
            adc __rc2,x 
            ; check if we wrapped, set to the max bounds if we did
            bcs @wrapped

            ; check the upper bounds
            cmp MouseBoundsMax,x
            bcc @setvalue

        @wrapped:
            lda MouseBoundsMax,x 
        
        @setvalue:
            sta se_joypad + kMouseY,x 
            dex
            bpl @loop

    ; calculate newly pressed buttons and shift it into byte zero
    lda __rc4
    eor #$c0
    and se_joypad + kMouseButtons
    rol
    ror se_joypad + kMouseZero
    rol
    ror se_joypad + kMouseZero

    ; calculate newly released buttons

    lda se_joypad + kMouseButtons
    eor #$c0
    and __rc4
    rol
    ror se_joypad + kMouseZero
    rol
    ror se_joypad + kMouseZero

    ; set the connected bit
    sec
    ror se_joypad + kMouseZero

    @exit:

    pla
    sta __rc7
    pla
    sta __rc6
    pla
    sta __rc4
    pla
    sta __rc3
    pla
    sta __rc2
    
    rts
.endproc







.export nmi
.proc nmi
    pha
    txa
    pha
    tya
    pha

    ; disable rendering on the ppu side
    lda #0
    sta $2001

    ; is rendering enabled on the engine side?
    lda se_ppu_mask_var
    and #%00011000
    cmp #%00011000
    jne @skip_all_updates  ; if not, skip vram updates
        ;; START OF VRAM UPDATES
        lda #0
        sta $2001

        ldy se_palette_update
        jeq @skip_palette   ; skip palette if not needed

            ldy #0
            sty $2001
            sty se_palette_update

            ldy $2002
            lda #$3f
            ldx #$00

            sta $2006
            stx $2006

            ; background
            .repeat 16,i
                ldy se_palette_buffer+i
                lda (se_palette_pointer_bg), y
                sta $2007
            .endrepeat

            ; sprites
            ldy se_palette_buffer+0
            lda (se_palette_pointer_bg), y
            sta $2007
            .repeat 3,i
                ldy se_palette_buffer+i+17
                lda (se_palette_pointer_bg), y
                sta $2007
            .endrepeat
            ldy se_palette_buffer+4
            lda (se_palette_pointer_bg), y
            sta $2007
            .repeat 3,i
                ldy se_palette_buffer+i+21
                lda (se_palette_pointer_bg), y
                sta $2007
            .endrepeat
            ldy se_palette_buffer+8
            lda (se_palette_pointer_bg), y
            sta $2007
            .repeat 3,i
                ldy se_palette_buffer+i+25
                lda (se_palette_pointer_bg), y
                sta $2007
            .endrepeat
            ldy se_palette_buffer+12
            lda (se_palette_pointer_bg), y
            sta $2007
            .repeat 3,i
                ldy se_palette_buffer+i+29
                lda (se_palette_pointer_bg), y
                sta $2007
            .endrepeat
            
        @skip_palette:
        ldy se_vram_update
        beq @skip_vram_updates
            ldy se_name_upd_enable
            beq @skip_nametable_updates
                ldy #0
                sty se_vram_update
                jsr flush_vram_update2
            @skip_nametable_updates:
            ldy $2002

            lda se_scroll_x
            ldx se_scroll_y
            sta $2005
            stx $2005
            lda se_ppu_ctrl_var
            sta $2000

        @skip_vram_updates:

        ; disable irq while we update it
        lda #0
        sta se_irq_table_position
        sta mmc3_IRQ_DISABLE

        ; get new values for this frame
        lda se_irq_table+0  ; first reload value
        ldx se_irq_table+1  ; first pointer (lo)
        ldy se_irq_table+2  ; first pointer (hi)

        ; prime irq pointer and reload registers
        stx se_irq_ptr + 0
        sty se_irq_ptr + 1
        sta mmc3_IRQ_LATCH
        sta mmc3_IRQ_RELOAD
        sta mmc3_IRQ_ENABLE

        lda se_ppu_mask_var
        sta $2001

        jsr se_safe_controller_polling
        cli

    @skip_all_updates:

    inc se_frame_count

    ;reset irq


    lda __rc2
    pha
    lda __rc3
    pha
    lda __rc4
    pha
    lda __rc5
    pha
    lda __rc6
    pha
    lda __rc7
    pha
    lda __rc8
    pha
    lda __rc9
    pha
    lda __rc10
    pha
    lda __rc11
    pha
    lda __rc12
    pha
    lda __rc13
    pha
    lda __rc14
    pha
    lda __rc15
    pha
    lda __rc16
    pha
    lda __rc17
    pha
    lda __rc18
    pha
    lda __rc19
    pha

    jsr @post_nmi

    pla
    sta __rc19
    pla
    sta __rc18
    pla
    sta __rc17
    pla
    sta __rc16
    pla
    sta __rc15
    pla
    sta __rc14
    pla
    sta __rc13
    pla
    sta __rc12
    pla
    sta __rc11
    pla
    sta __rc10
    pla
    sta __rc9
    pla
    sta __rc8
    pla
    sta __rc7
    pla
    sta __rc6
    pla
    sta __rc5
    pla
    sta __rc4
    pla
    sta __rc3
    pla
    sta __rc2

    pla
    tay
    pla
    tax
    pla
    rti
    
    @post_nmi:
    jmp (se_post_nmi_ptr)
.endproc






;;
;;  IRQ STUFF
;;  need interrupts? this has you covered.
;;
se_run_da_irq:
    jmp (se_irq_ptr)

.export irq
.proc irq
    sta mmc3_IRQ_DISABLE
    pha
    txa
    pha
    jsr se_run_da_irq

    ; prime irq for the next time it fires
    ldx se_irq_table_position

    lda se_irq_table + 0, x
    sta mmc3_IRQ_LATCH
    sta mmc3_IRQ_RELOAD
    sta mmc3_IRQ_ENABLE
    
    lda se_irq_table + 1, x
    sta se_irq_ptr + 0
    lda se_irq_table + 2, x
    sta se_irq_ptr + 1

    pla
    tax
    pla
    
    rti
.endproc


.export se_play_sample
.proc se_play_sample
;    php
;    sei
;    sta __prg_c000
;    txa
;    pha

;    lda #$ad    ; opcode for LDA abs
;    sta $d0

    ; copy to this location
;    lda #$d3
;    ldx #0
;    sta __rc2
;    stx __rc3

;    sec
;    sbc #3
;    sta se_irq_table+1
;    stx se_irq_table+2

;    dex
;    stx se_irq_table+0
    
    ; from this location
;    lda #<funny_pcm_routine+3
;    ldx #>funny_pcm_routine
;    sta __rc4
;    stx __rc5

    ; with this length
;    lda #45
;    ldx #0
;    jsr se_memory_copy


    ; set bank
;    lda #%00000110                  ; 25
;    ora __bank_select_hi            ; 27
;    sta $8000                       ; 30
;    lda __prg_c000                  ; 32
;    sta $8001                       ; 35

    ; get playback rate
;    pla
;    tax
;    stx se_irq_table+0
;    inc se_sample_in_progress

;    plp
    rts
.endproc

.proc se_sample_eof
    lda #0
    sta se_sample_in_progress
    lda #255
    sta se_irq_table+0
    rts
.endproc

.proc funny_pcm_routine
    .org $00d0  ; 60 bytes to work with

    @load_instruction: lda $c000    ; 3
    bmi @exit_eof_sample            ; 5
    sta $4011                       ; 8
    inc @load_instruction + 1       ; 10
    beq @inc_high_byte              ; 12
    rts                             ; 13

    @inc_high_byte:
    inc @load_instruction + 2       ; 15
    lda @load_instruction + 2       ; 17
    cmp #$e0                        ; 19
    bne @exit                       ; 21

    inc __prg_c000                  ; 23

    lda #%00000110                  ; 25
    ora __bank_select_hi            ; 27
    sta $8000                       ; 30
    lda __prg_c000                  ; 32
    sta $8001                       ; 35
    lda #$c0                        ; 37
    sta @load_instruction + 2       ; 39
    @exit:
    rts                             ; 40
    @exit_eof_sample:
    jmp se_sample_eof               ; 43

    .reloc
.endproc

;.align 128
.include "famistudio_ca65.s"