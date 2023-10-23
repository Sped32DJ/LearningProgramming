;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 3, ex 1
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================
; Indirections!

.ORIG x3000

ADD R0, R0, #0 ; Holds 1-10
ADD R3, R3, #10 ; number of iterations

LEA R1, DATA_PTR ; Load Effective Addr
;STR R2, R0, #0 ; # offset/addr arithmetic
;STR R3, R0, #1

DO_WHILE_LOOP
    STR R1, R0, #1 ; is this legal?
    ADD R0, R0, x1 ; ++addr

    ADD R3, R3, #-1 ; 10 iterations
    BRp DO_WHILE_LOOP
END_DO_WHILE_LOOP


HALT

DATA_PTR .FILL x4000

.END

.ORIG x4000

ARRAY_1 .BLKW   #10 ; allocates 10 memory locations
DEC_25  .FILL   #25 ; x4010

.END
