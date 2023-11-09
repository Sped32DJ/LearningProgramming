;=================================================
; Name: Danny Topete ; Hold NOT ENDL ; Hold NOT ENDL
; Email: dtope004@ucr.edu
;
; Lab: lab 5, ex 1
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

LD R6, GET_STRING
JSSR R6 ; R6 hold subroutine pointers

PUTS

halt

; your local data goes here

top_stack_addr  .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
GET_STRING      .FILL x3200
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
AND R5, R5, #0
AND R2, R2, #0 ; R2 Hold NOT ENDL
LD  R2, NULL_3200
ADD R2, R2, #1 ; NOT + 2's compl

WHILE_3200
; R1 holds string, R5 is storing array
; STR R5, R1, #0 ; Store R5 val into R1 addr
STR R1, R5, #0 ; Store R1 val into R5 addr

ADD R1, R1, #1 ; ++addr arr
ADD R2, R2, #1 ; ++addr string

ADD R5, R5, #1 ; ++counter

ADD R0, R0, R2 ; if 0, then break
BRnp WHILE_3200 ; while R0 is positive or negative
; Breaks when curr char is an endl

RET
NULL_3200       .FILL x00

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
