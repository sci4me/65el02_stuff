.include "65el02.inc"
.include "monitor.inc"
.include "disk.inc"
.include "iox.inc"

.org LOADED_CODE_START

.define REDBUS $0300


sei ; Disable interrupts

clc ; Switch to native mode
xce

a16 ; Switch to full 16-bit mode
i16

ldx #$01FF ; Set up stack
txs

cld ;Disable decimal mode

lda #LOADED_CODE_START ; Set POR address
mmu MMUOp::SET_POR

cli ; Enable interrupts

lda #REDBUS ; Set the RedBus window at 0x0300
mmu MMUOp::SET_MAP

mmu MMUOp::ENABLE_RB ; Enable RedBus window


    a8
        lda FRONT_PANEL_DISPLAY_ID
        mmu MMUOp::SET_ID

        blit_fill REDBUS, #32, 0, 0, #MONITOR_W, #MONITOR_H
        stz REDBUS+Monitor::row
        stz REDBUS+Monitor::cursor_x
        lda #4
        sta REDBUS+Monitor::cursor_y
        sta REDBUS+Monitor::row

        lda #65
        sta REDBUS+Monitor::display

        blit_shift REDBUS, #0, #1, #0, #0, #80, #49
    a16


lda #3 ; Map the IO Expander (assumed bus ID 3) in on RedBus
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