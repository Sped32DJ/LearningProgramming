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



HALT

ARRAY_PTR               .FILL x4000
SUB_FILL_ARRAY_PTR      .FILL x3200


.END

; ===================================
; Subroutine: SUB_FILL_ARRAY
; Parameter (R1): The starting address of the array.
;       This should be unchanged at the end of the subroutine!
; Postcondition: The array has values from 0 through 9.
; Return Value (None)
; ===================================
.ORIG x3200

AND R3, R3, #0
AND R4, R4, #0
LD R2, ARRAY_PTR_SUB

LD R3, DEC_10 ; Iterations

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
DEC_10  .FILL #10
ARRAY_PTR_SUB       .FILL x4000

.END

.ORIG x4000
ARRAY_1         .BLKW   #10

.END
