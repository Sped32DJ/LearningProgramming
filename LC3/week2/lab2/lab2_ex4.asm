;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 2, ex 4
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

.ORIG x3000
LD R3, AMOUONT_OF_ITERATIONS
LD R0, ZERO_IN_ASCII

DO_WHILE_LOOP
    ADD R0, R0, #1
    OUT

    ADD R3, R3, #-1 ; iteration
    BRp DO_WHILE_LOOP
END_DO_WHILE_LOOP


HALT

ZERO_IN_ASCII           .FILL #48
AMOUONT_OF_ITERATIONS   .FILL #42


.END
