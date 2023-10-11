;=================================================
; Name:  Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 1, ex 1
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

; First REAL Program
.ORIG x3000
    AND R1, R1, x0 ; Inserting literal 0 is more efficient
    LD R2, DEC_12 ; R2 = #12
    LD R3, DEC_6  ; R3 = #6

DO_WHILE_LOOP
    ADD R1, R1, R2 ;  R1 = R1 + R2
    ADD R3, R3, #-1 ; R3 = R3 - #1
    BRp DO_WHILE_LOOP ; if (R3>0) goto DO_WHILE_LOOP
    ; BR = Conditional Branch
    ; 3 modifiers, n,z,p
    ; n = N Condition Code
    ; z = Z condition Code
    ; p = if specific condition is met
    ; Figure this out
END_DO_WHILE_LOOP


HALT ;

; Defining variables
DEC_0   .FILL #0
DEC_12  .FILL #12
DEC_6   .FILL #6


.END
