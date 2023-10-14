;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Assignment name: Assignment 1
; Lab section: 021
; TA: Karan / Nicholas
;
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

;------------------------------------------
;           BUILD TABLE HERE
;------------------------------------------
; I believe the table will be 6x8 (R1 = 6 )
;
;------------------------------------------
; REG VALUES    R0   R1   R2   R3   R4   R5  R6   R7
;------------------------------------------
; Pre-loop      0    6    0    0    0    0    0    0
; Iteration 01  0    5    12   12   0    0    0    0
; Iteration 02  0    4    12   24   0    0    0    0
; Iteration 03  0    3    12   36   0    0    0    0
; Iteration 04  0    2    12   48   0    0    0    0
; Iteration 05  0    1    12   60   0    0    0    0
; Iteration 06  0    0    12   72   0    0    0    0

; Iteration n   0   6-n   12  12(n) 0    0    0    0
; End of program 0 32767  12   72   0    0  12286  0
;------------------------------------------
;
;
;
;
;
;


.ORIG x3000			; Program begins here
;-------------
;Instructions: CODE GOES HERE
;-------------
AND R1, R2, #0        ; R1 = 0
; AND -> destination
; R1 source
; #0 Operand

LD R1, DEC_6
LD R2, DEC_12
LD R3, DEC_0

DO_WHILE
    ADD R3, R3, R2 ; R3 = R3 + R2

    ADD R1, R1, #-1 ; subtract R1 by 1; ADD source register (R1) with Operand #-1; takes care of iteration
    BRp DO_WHILE
END_DO_WHILE_LOOP



HALT
;---------------
;Data (.FILL, .STRINGZ, .BLKW)
;---------------
DEC_0 .FILL #0
DEC_6 .FILL #6
DEC_12 .FILL #12



;---------------
; END of PROGRAM
;---------------
.END


