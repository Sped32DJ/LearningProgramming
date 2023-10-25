;=================================================
; Name:  Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 3, ex 2
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

.ORIG   x3000

LD R3, ARR_PTR ; Holds ARR
LD R2, Count    ; Holds iterations

LOOP
    GETC    ;Input
    OUT     ;OUT
    STR R0, R3, #0 ; Store R0 into mem addr
    ADD R3, R3, #1 ; increment by 1

    ADD R2, R2, #-1
    BRp LOOP


HALT

Count           .FILL #10
ARR_PTR         .FILL x4000

.END

.ORIG x4000

ARRAY_1         .BLKW   #10 ;Allocate 10 mem

.END
