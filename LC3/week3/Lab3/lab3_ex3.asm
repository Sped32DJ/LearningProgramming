;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 3, ex 3
; Lab section: 021
; TA: Karan/Nicholas
;
;=================================================

.ORIG   x3000

LD R3, ARR_PTR ; Holds ARR
LD R2, Count    ; Holds iterations

LOOP ;Fill the array
    TRAP x23
    STR R0, R3, #0 ; Store R0 into mem addr
    ADD R3, R3, #1 ; increment by 1
    ADD R2, R2, #-1
    BRp LOOP

; output the array
AND R3, R3, #0
AND R2, R2, #0

LD R3, ARR_PTR  ;Holds addr
LD R2, Count    ; Holds iterations
; Enteres loops, insta craash
LOOP_2
;    STR R0, R3, #0
    LDR R0, R3, #0
    OUT
    LD R0, Space
    OUT ; OUT because hex
    ADD R3, R3, #1
    ADD R2, R2, #-1


    BRp Loop_2



HALT

Count           .FILL #10
ARR_PTR         .FILL x4000
Space           .FILL x0A

.END

.ORIG x4000

ARRAY_1         .BLKW   #10 ;Allocate 10 mem

.END

