.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE
LD R1, ARRAY_ADDRESS
LD R2, USER_SENTENCE
JSRR R2


ld r3, PUTUPPERCASE
JSRR R3


LD R3, PALINDROME
JSRR R3

lea r0, starter
puts

ADD R0, R1, #0
PUTS

add r4, r4, #0
brp istrue

lea r0, false
puts
br endprogram
istrue
lea r0, true
puts

endprogram
;////////////


; your code goes here
halt

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
ARRAY_ADDRESS .FILL X4000
USER_SENTENCE .FILL X3200
PALINDROME .FILL X3400
starter .stringz "The string "
true .stringz " IS a palindrome"
false .stringz " IS NOT a palindrome"
PUTUPPERCASE .FILL  x3600
.end

.ORIG X3200
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0

ld r3, newline
LD R5, COUNTER
not r3, r3
add r3, r3, #1

USER_INPUT
getc
out

; SECONDS MESSAGE
add r2, r0, r3
BRz END_USER_INPUT
str r0, r1, #0
add r1, r1, #1
add r5, r5, #1
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

add r2, r1, r5
add r2, r2, #-1

check
; r3 = top value
;r4 = bottom value
ldr r3, r1, #0
ldr r4, r2, #0

not r3, r3
add r3, r3, #1

add r3 , r3, r4
BRnp exitloop
add r1, r1, #1
add r2, r2 , #-1
add r5, r5, #-2
add r0, r5, #-1
BRp check

and r4, r4, #0
add r4, r4, #1
br finish

exitloop
and r4, r4, #0

finish

LDR R3, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

Ret
.END

.ORIG X3600
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R5, R6, #0

ld r2, MASKVALUE
LOOP

ldr R0, R1, #0
and r0, r2, r0
str R0, R1, #0
add r1, r1, #1
add r5, r5, #-1
brp loop

LDR R5, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1





RET

MASKVALUE .FILL xDF
.END
; your subroutines go below here
.ORIG X4000
ARRAY_SIZE .BLKW #100
.END
