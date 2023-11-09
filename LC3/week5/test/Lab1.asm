.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE
LD R1, ARRAY_ADDRESS

LD R2, GET_STRING
JSRR R2

ld r3, TO_UPPER
JSRR R3

LD R3, SUB_PALINDROME
JSRR R3

lea r0, starter
PUTS

ADD R0, R1, #0
PUTS

; Checks booleans
ADD R4, R4, #0
BRp istrue

LEA R0, false
PUTS

; Skip True option if you don't need it
BR endprogram
istrue
LEA r0, true
PUTS

endprogram

; your code goes here
HALT

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
ARRAY_ADDRESS .FILL X4000
GET_STRING .FILL X3200
SUB_PALINDROME .FILL X3400
starter .stringz "The string "
true .stringz " IS a palindrome"
false .stringz " IS NOT a palindrome"
;TO_UPPER .FILL  x3600
.END

; ===================================
; Subroutine: GET_STRING
; Parameter (R1): Chars be stored into an array held by R1
; Postcondition: Array null-terminated
; Return Value (R5): char count
; ===================================

.ORIG X3200
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0

LD R3, newline
LD R5, COUNTER
NOT R3, R3
ADD R3, R3, #1

USER_INPUT
GETC
OUT

; SECONDS MESSAGE
ADD R2, R0, R3
BRz END_USER_INPUT
STR R0, R1, #0
ADD R1, R1, #1
ADD R5, R5, #1
BR USER_INPUT
END_USER_INPUT

LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

RET

newline .fill #010
COUNTER .FILL #0
.END

.ORIG X3400
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6 #-1
STR R3, R6, #0

;r1 = top adress
; r5 = counter
;r2 is end address

ADD R2, R1, R5
ADD R2, R2, #-1

check
; r3 = top value
;r4 = bottom value
LDR R3, R1, #0
LDR R4, R2, #0

NOT R3, R3
ADD R3, R3, #1

ADD R3 , R3, R4
BRnp exitloop
ADD R1, R1, #1
ADD R2, R2 , #-1
ADD R5, R5, #-2
ADD R0, R5, #-1
BRp check

AND R4, R4, #0
ADD R4, R4, #1
BR finish

exitloop
and r4, r4, #0

finish

LDR R3, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

RET
.END

; .ORIG X3600
; ADD R6, R6, #-1
; STR R1, R6, #0
; ADD R6, R6, #-1
; STR R2, R6, #0
; ADD R6, R6, #-1
; STR R5, R6, #0

; LD R2, MASKVALUE
; LOOP

; LDR R0, R1, #0 ; Grabbing char
; AND R0, R2, R0 ; Masking TO_UPPER
; STR R0, R1, #0 ; Storing uppercased Char
; ADD R1, R1, #1 ; Iterating addr
; ADD R5, R5, #-1 ; Iterating down
; BRp LOOP

; ; Stolen backup register values code
; LDR R5, R6, #0
; ADD R6, R6, #1
; LDR R2, R6, #0
; ADD R6, R6, #1
; LDR R1, R6, #0
; ADD R6, R6, #1

; RET

; MASKVALUE .FILL xDF ; Mask for UPPER
; .END
; your subroutines go below here
.ORIG X4000
ARRAY_SIZE .BLKW #100
.END
