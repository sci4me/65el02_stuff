.include "65el02.inc"
.include "iox.inc"
.include "disk.inc"
.include "monitor.inc"

.org LOADED_CODE_START

.define REDBUS $0300


; Disable interrupts
sei

; Switch to native mode
clc
xce


; Switch to full 16-bit mode
a16
i16


; Set up stack and disable decimal mode
pha
ldx #$01FF
txs
cld


; Set POR address
lda #LOADED_CODE_START
mmu MMUOp::SET_POR


; Enable interrupts
cli


; Set the RedBus window at 0x0300
lda #REDBUS
mmu MMUOp::SET_MAP

; Enable RedBus window
mmu MMUOp::ENABLE_RB


    lda FRONT_PANEL_DISPLAY_ID
    mmu MMUOp::SET_ID
    blit_fill REDBUS, #32, 0, 0, #MONITOR_W, #MONITOR_H


; Map the IO Expander (assumed bus ID 3) in on RedBus
lda #3
mmu MMUOp::SET_ID


lda #0
sta count


loop:
    lda count
    sta REDBUS+IOX::write

    inc count

    ldx #5
    jsr ticks

    bra loop


count: .res 2


.proc ticks
:   dex
    wai
    bne :-
    rts
.endproc