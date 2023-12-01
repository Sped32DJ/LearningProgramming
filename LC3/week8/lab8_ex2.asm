;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 8, ex 2
; Lab section:
; TA: Karan
;
;=================================================

.orig x3000

LD R6, top_stack_addr

; Test harness
;-------------------------------------------------
LEA R0, PROMPT
PUTS

GETC
OUT

; R0 GETC into R1
ADD R1, R0, #0

LD R5, PARITY_CHECK_3600
JSRR R5


HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr .fill xFE00
PARITY_CHECK_3600 .FILL x3600
PROMPT .STRINGZ "ENTER A CHAR: "

.end

;=================================================
; Subroutine: PARITY_CHECK_3600
; Parameter: R1 (Value)
; Postcondition: R2 (Count 1s in binary)
; Return Value (R3): R3 (number of 1s)
;=================================================

.orig x3600
LD R6, BACKUP
ADD R6, R6, #-1
STR R1, R6, #0

ADD R6, R6, #-1
STR R2, R6, #0

ADD R6, R6, #-1
STR R4, R6, #0

ADD R6, R6, #-1
STR R5, R6, #0

ADD R6, R6, #-1
STR R7, R6, #0

; Backup registers

; Code
; Initializing vals
LD R3, ascii
LD R4, DEC_15 ; because 16 bit

ADD R2, R1, #0 ;R2 now holds R1

; LMR counter logic
WHILE_COUNTER:
    LD R5, MASK
    AND R5, R5, R2
    BRz ELSE
    IF_NEG
        ADD R3, R3, #1
    ELSE
        ADD R2, R2, R2
        ADD R4, R4, #-1 ;Counter
        BRp WHILE_COUNTER
    END

; OUTPUTS
LEA R0, RESULT_1
PUTS

ADD R0, R1, #0
OUT

LEA R0, RESULT_2
PUTS

ADD R0, R3, #0
OUT

LD R0, ENDL
OUT

; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1

LDR R5, R6, #0
ADD R6, R6, #1

LDR R4, R6, #0
ADD R6, R6, #1

LDR R2, R6, #0
ADD R6, R6, #1

LDR R1, R6, #0
ADD R6, R6, #1

RET
BACKUP  .FILL xFE00
ascii   .FILL x30
DEC_15  .FILL #15
MASK    .FILL x8000
RESULT_1 .STRINGZ "\nThe number of 1s in's IN '"
RESULT_2 .STRINGZ "' IS: "
ENDL     .FILL x0A

.end
