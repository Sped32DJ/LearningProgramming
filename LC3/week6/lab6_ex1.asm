;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 6, ex 1
; Lab section:021
; TA: Karan / Nicholas
;
;=================================================

.ORIG x3000

; NOTE  Backup all registers modified in the sub routine
; Always Backup R7, never backup return values

; Load register-backup stack
LD R6, REG_STACK ;Holds all the backups

;Load value stack
LD R3, STACK_BASE
LD R4, STACK_MAX
LD R5, STACK_BASE  ;Dynamically holds TOS

LD R5, SUB_STACK_PUSH
JSRR, R5
; R5 now has an updated TOS


HALT

; Local data
REG_STACK       .FILL xFE00
STACK_BASE      .FILL xA000
STACK_MAX       .FILL xA005
SUB_STACK_PUSH  .FILL x3200


.END

;---------------------------------------------------------------------
; Subroutine: SUB_STACK_PUSH
; Parameter (R1): The value to push onto the stack
; Parameter (R3): BASE: A pointer to the base (one less than the lowest available                      ;                       address) of the stack
; Parameter (R4): MAX: The "highest" available address in the stack
; Parameter (R5): TOS (Top of Stack): A pointer to the current top of the stack
; Postcondition: The subroutine has pushed (R1) onto the stack (i.e to address TOS+1).
;		    If the stack was already full (TOS = MAX), the subroutine has printed an
;		    overflow error message and terminated.
; Return Value: R5 ← updated TOS
;---------------------------------------------------------------------

.ORIG x3200
;--------------
; Backup R1, R3, R4
ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R3, R6, #0
ADD R6, R6, #-1
STR R4, R6, #0
;--------------

; TODO  Overflow logic

; Two's complement of MAX
NOT R4, R4
ADD R4, R4, #1

IF_OVERFLOW
    ADD R4, R4, R5
BRzp PREVENT_OVERFLOW ; -MAX + TOS >= 0, don't add to stack
BR NO_OVERFLOW

PREVENT_OVERFLOW
    LEA R0, OVERFLOW_DETECTED
    PUTS
    BR OVERFLOW_TO_RESTORE

NO_OVERFLOW
; push R1 into stack
STR R1, R5, #0

ADD R5, R5, #1 ; ++TOS

OVERFLOW_TO_RESTORE
;--------------
; Restoring Registers
LDR R4, R6, #0
ADD R6, R6, #1
LDR R3, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
LDR R0, R6, #0
ADD R6, R6, #1
;--------------


RET
OVERFLOW_DETECTED       .stringz "Overflow was detected"

.END
