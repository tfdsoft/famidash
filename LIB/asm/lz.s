; THCMod-like LZ decompressor for 6502 by AArt1256
; made and finished in 04/01/2025
 
; SET THIS TO ANY 256-BYTE ALIGNED RAM ADDRESS!!!!!!!!!!!!
LZ_buffer_addr := aart_lz_buffer

.segment "ZEROPAGE"
LZ_addr: .res 2

; check if the decompression has been finished
; $00 = currently not fully decompressed
; $FF = done/complete!
LZ_done: .res 1

LZ_buf_addr: .res 1
LZ_copy_left: .res 1
LZ_y_temp: .res 1

.segment "BSS"
LZ_buffer := LZ_buffer_addr
LZ_buffer2 := LZ_buffer_addr+256

.segment "CODE_2"

.export LZ_init_decomp, LZ_get_byte, LZ_done

; LZ_init_decomp: initialize the LZ decompressor
; input:
; X = lobyte of compressed data address
; Y = hibyte of compressed data address
; output: nothing
; clobbers: A, X (both are set to 0)
LZ_init_decomp:
  sty LZ_addr+1
  stx LZ_addr
  lda #0
  sta LZ_done
  sta LZ_buf_addr
  sta LZ_copy_left

  tax
  @clear_buf:
    ; alexmush note: clearing the first buffer is essential
    sta LZ_buffer, x
    dex
    bne @clear_buf

  rts


; LZ_get_byte: output the decompressed data one byte at a time
; input: nothing
; output:
; A: the current decompressed byte
; clobbers: A, X, Y
LZ_get_byte:
  lda LZ_done
  beq @is_not_finished
  lda #0
  rts
@is_not_finished:

  lda LZ_copy_left
  beq @no_continue_copy
@continue_copy:
  tay
  dey
  lda LZ_buffer2, y
  jsr @write_byte
  sty LZ_copy_left
  rts

@no_continue_copy:

  jsr @get_compressed_byte
  cmp #$ff
  bne @skip_end
  sta LZ_done
  lda #0
  rts

@skip_end:
  cmp #$80
  beq @is_imm ; bcs in OG src, works either way
  tax
  inx
  stx LZ_copy_left
  dex
  dex
  jsr @get_compressed_byte
  tay
@pre_copy_loop:
  lda LZ_buffer, y
  iny
  sta LZ_buffer2+1, x
  dex
  bpl @pre_copy_loop
  jsr @get_compressed_byte
  sta LZ_buffer2

  lda LZ_copy_left
  jmp @continue_copy

@is_imm:
  jsr @get_compressed_byte
  ; drops down to @write_byte anyway...

@write_byte:
  ldx LZ_buf_addr
  sta LZ_buffer, x
  inx
  stx LZ_buf_addr
  rts

@get_compressed_byte:
  sty LZ_y_temp
  ldy #0
  lda (LZ_addr), y
  ldy LZ_y_temp

  inc LZ_addr
  bne :+
  inc LZ_addr+1
:
  rts

