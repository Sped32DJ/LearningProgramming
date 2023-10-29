;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 4, ex 1
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================
; Intro to subroutines
    ;   They are like functions
; Filling up the plate

.ORIG x3000
LD R5, SUB_FILL_ARRAY_PTR
JSRR R5 ; Puts the next line to R7 (backup)

LD R5, SUB_CONVERT_ARRAY
JSRR R5 ; Enters SUB_CONVERT_ARRAY function


HALT

ARRAY_PTR               .FILL x4000
SUB_FILL_ARRAY_PTR      .FILL x3200
SUB_CONVERT_ARRAY       .FILL x3400


.END

; ===================================
; Subroutine: SUB_FILL_ARRAY
; Parameter (R1): The starting address of the array.
;       This should be unchanged at the end of the subroutine!
; Postcondition: The array has values from 0 through 9.
; Return Value (None)
; ===================================
.ORIG x3200 ; {

AND R3, R3, #0
AND R4, R4, #0
LD R2, ARRAY_PTR_SUB

ADD R3, R3, #10 ; Iterations

WHILE_LOOP
    STR R4, R2, #0 ; Val of R4 into R2 addr
    ADD R2, R2, #1 ; ++addr
    ADD R4, R4, #1 ; Value put into array

    ADD R3, R3, #-1 ; Iterates 10 times
    BRnp WHILE_LOOP


RET ; Basically, JMP R7. Works with JSRR
; Not sure if this goes out of scope
; You can fill this with variables
; Vars you only need after the func
ARRAY_PTR_SUB       .FILL x4000

.END ; }

;------------------------------------------------------------------------
; Subroutine: SUB_CONVERT_ARRAY
; Parameter (R1): The starting address of the array. This
;       should be unchanged at the end of the subroutine!
; Postcondition: Each element (number) in the array should
;       be represented as a character. E.g. 0 -> ‘0’
; Return Value (None)
;-------------------------------------------------------------------------
.ORIG x3400 ; {

AND R3, R3, #0
ADD R3, R3, #10

AND R0, R0, #0
AND R4, R4, #0
LD R2, ARRAY_PTR_SUB_1
LD R5, ascii_offset ; R5 holds offset

PRINT_WHILE
    LDR R0, R2, #0 ; Load R4 addr into R0
    ADD R0, R0, R5 ; Binary now now has ascii alphabet
    OUT ; output ascii
    STR R0, R2, #0 ; Overwritting array to hold ascii

    ADD R2, R2, #1
    ADD R3, R3, #-1
    BRnp PRINT_WHILE


RET
ARRAY_PTR_SUB_1 .FILL x4000
ascii_offset    .FILL x30

.END ; }

; Array Memory
.ORIG x4000
ARRAY_1         .BLKW   #10

.END
