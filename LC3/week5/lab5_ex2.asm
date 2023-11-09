;=================================================
; Name: Danny Topete ; Hold NOT ENDL ; Hold NOT ENDL
; Email: dtope004@ucr.edu
;
; Lab: lab 5, ex 2
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE
; your code goes here

AND R5, R5, #0 ; Have this as an iterator for num of chars
LEA R1, race_car ; R1 hold string
; LD R1, ARRAY_ADDR

LD R6, GET_STRING
JSSR R6 ; R6 hold subroutine pointers

LEA R0, SUB_IS_PALINDROME

LEA R1, race_car ; reinitialize R1 addr

PUTS

LD R6, SUB_IS_PALINDROME
JSSR

halt

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
GET_STRING              .FILL x3200
SUB_IS_PALINDROME       .FILL x3400
race_car        .stringz "racecar"
routine_helper  .fill x32xx
endl            .fill x0A ; detect newline, so NOT this
.end

; ===================================
; Subroutine: GET_STRING
; Parameter (R1): Chars be stored into an array held by R1
; Postcondition: Array null-terminated
; Return Value (R5): char count
; ===================================

.orig x3200
; Backup registers logic
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

LD R3, NEWLINE_3200
LD R5, COUNTER
NOT R3, R3
ADD R3, R3, #1 ; Two's compl

USR_INP
    GETC
    OUT

    ; Second message
    ADD R2, R0, R3
    BRz END_INPUT
    STR R0, R1, #0
    ADD R1, R1, #1 ; Go up addr
    ADD R5, R5, #1 ; ++COUNTER
    BR USR_INP

END_INPUT


; Backup logic
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

RET
NULL_3200       .FILL x00
NEWLINE_3200    .FILL x0A
COUNTER         .FULL #0

.end

; ===================================
; Subroutine: SUB_IS_PALINDROME
; Parameter (R1): Take addr of string in R1
;       Number of chars in R5
; Postcondition: Determine if string in R1 IS_PALINDROME
; Return Value (R5): Set R4 to 1 if it is IS_PALINDROME
;       or 0 if it is not
; ===================================

.orig x3400
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #0
ADD R6, R6, #-1
STR R3, R6, #0

; R1,  top addr
; R5, iterator
; R2, end of addr

ADD R2, R1, R5
ADD R2, R2, #-1

CHECK
    LDR R3, R1, #0
    LDR R4, R2, #0

    NOT R3, R3, R4
    BRnp EXIT_LOOP
    ADD R1, R1, #1
    ADD R2, R2, #-1
    ADD R5, R5, #-2
    ADD R0, R5, #-1
    BRp CHECK

AND R4, R4, #0
ADD R4, R4, #1
BR FINISH

EXIT_LOOP
    AND R4, R4, #0

FINISH ; Backup logic I stole
    LDR R3, R6, #0
    LDR R2, R6, #0
    ADD R6, R6, #1
    ADD R6, R6, #1
    LDR R1, R6, #0
    ADD R6, R6, #1

RET
.end
; .orig x3xx

; ; backup registers
; ADD R6, R6, #-1
; STR R7, R6, #0
; ADD R6, R6, #-1
; STR R1, R6, #0

; ; subroutine logic
; LDR R1, R6, #0
; ADD R6, R6, #1
; LDR R7, R6, #0
; ADD R6, R6, #1;

; RET

; .end

; your subroutines go below here
.orig xFE00

.end

.orig x4000
Locations       .blck #40 ; LIFO
;null            .fill x00 ; ends with a null
.end

