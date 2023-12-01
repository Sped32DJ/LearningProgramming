;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 8, ex 1
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

.orig x3000

LD R6, top_stack_addr
; Test harness
;-------------------------------------------------
LD R5, LOAD_FILL_VALUE_3200
JSRR R5

ADD R1, R1, #1

LD R5, SUB_OUTPUT_DECIMAL
JSRR R5

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr          .fill xFE00
LOAD_FILL_VALUE_3200    .FILL X3200
SUB_OUTPUT_DECIMAL      .FILL x3400
; STACK_SIZE     .fill x0100

.end

; Isolating digits
; And modulo for exercise 1
;=================================================
; Subroutine: LOAD_FILL_VALUE_3200
; Parameter: R1
; Postcondition: NA
; Return Value: R1
;=================================================

.ORIG x3200
LD R6, BACKUP_3200

ADD R6, R6, #-1
STR R2, R6, #0

ADD R6, R6, #-1
STR R3, R6, #0

ADD R6, R6, #-1
STR R4, R6, #0

ADD R6, R6, #-1
STR R5, R6, #0

ADD R6, R6, #-1
STR R7, R6, #0

; Backup registers

; Code
LD R1, INPUT_VALUE ; Hardcoded

ADD R1, R1, #0
BRzp END_IF ; Fails to branch IF_NEG

IF_NEG
    NOT R1, R1
    ADD R1, R1, #1
    LD R0, minus
    OUT
END_IF

; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1

LDR R5, R6, #0
ADD R6, R6, #1

LDR R4, R6, #0
ADD R6, R6, #1

LDR R3, R6, #0
ADD R6, R6, #1

LDR R2, R6, #0
ADD R6, R6, #1

RET
BACKUP_3200 .FILL xFE00
INPUT_VALUE .FILL #-4
minus       .FILL x2D

.END

;=================================================
; Subroutine: OUTPUT_AS_DECIMAL_3400
; Parameter:
; Postcondition:
; Return Value: R2
;=================================================

.ORIG x3400
LD R6, BACKUP_3400
ADD R6, R6, #-1
STR R1, R6, #0

ADD R6, R6, #-1
STR R2, R6, #0

ADD R6, R6, #-1
STR R3, R6, #0

ADD R6, R6, #-1
STR R4, R6, #0

ADD R6, R6, #-1
STR R5, R6, #0

ADD R6, R6, #-1
STR R7, R6, #0

; Backup registers

; Code
LD R2, DECIMAL_ADD
AND R3, R3, x0
AND R4, R4, x0

; Standard Modulo logic
MODULO:
    ADD R4, R1, #0
    ADD R1, R1, #-10
    BRn END
    ADD R4, R3, #1
    BR MODULO
END:
    STR R4, R2, #0
    ADD R2, R2, #1
    ADD R1, R3, #0
    AND R3, R3, #0
    ADD R1, R1, #0
    BRp MODULO

; Load val for next half
LD R3, ascii
LD R4, DECIMAL_ADD

; Calculate STACK_SIZE
NOT R4, R4
ADD R4, R4, #1
ADD R4, R2, R4

; Prints
WHILE_PRNT:
    ADD R2, R2, #-1
    LDR R0, R2, #0
    ADD R0, R0, R3
    OUT
    ADD R4, R4, #-1
    BRp WHILE_PRNT
PRINT_END

; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1

LDR R5, R6, #0
ADD R6, R6, #1

LDR R4, R6, #0
ADD R6, R6, #1

LDR R3, R6, #0
ADD R6, R6, #1

LDR R2, R6, #0
ADD R6, R6, #1

LDR R1, R6, #0
ADD R6, R6, #1

RET
BACKUP_3400 .FILL xFE00
ascii       .FILL x30
DECIMAL_ADD .FILL x4000

.END
