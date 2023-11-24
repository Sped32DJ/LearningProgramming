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

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr .fill xFE00
LOAD_FILL_VALUE_3200 .FILL X3200
; STACK_SIZE     .fill x0100

.end

; Isolating digits
; And modulo for exercise 1
;=================================================
; Subroutine: LOAD_FILL_VALUE_3200
; Parameter: // Fixme
; Postcondition: // Fixme
; Return Value: // Fixme
;=================================================

.ORIG x3200
LD R6, BACKUP_3200
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

; Restore registers
; RESTORE_3200 ; LABEL
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
BACKUP_3200 .FILL xFE00

.END

;=================================================
; Subroutine: OUTPUT_AS_DECIMAL_3400
; Parameter: // Fixme
; Postcondition: // Fixme
; Return Value: // Fixme
;=================================================

.ORIG x3400

; Backup registers

; Code

; Restore registers

RET

.END
