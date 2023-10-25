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

LD R3, DATA_PTR
LD R2, Count ;Iterator

ADD R0, R0, #0

DO_WHILE_LOOP
    STR R0, R3, #1 ; Writing R0 into R3 addr
    ADD R3, R3, #1 ; Adding one
    ADD R0, R0, #1 ; Input into Array
    PUTS

    ADD R2, R2, #-1
    BRp DO_WHILE_LOOP
END_DO_WHILE_LOOP

LD R4, DATA_PTR
LDR R5, R4, #2

HALT

DATA_PTR .FILL x4000
Count    .FILL #9

.END

.ORIG x4000

ARRAY_1 .BLKW   #10 ; allocates 10 memory locations
DEC_25  .FILL   #25 ; x4010

.END
