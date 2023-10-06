;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name:
; Email:
;
; Assignment name: Assignment 1
; Lab section:
; TA:
;
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

;------------------------------------------
;           BUILD TABLE HERE
;------------------------------------------
;
;
;
;
;
;
;
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

DO_WHILE
    ADD R1, R1, #-1 ; subtract R1 by 1; ADD source register (R1) with Operand #-1
    BRp DO_WHILE_LOOP
END_DO_WHILE_LOOP



HALT
;---------------
;Data (.FILL, .STRINGZ, .BLKW)
;---------------




;---------------
;END of PROGRAM
;---------------
.END


