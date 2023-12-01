;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 6, ex 3
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

.ORIG x3000

; NOTE  Backup all registers modified in the sub routine
; Always Backup R7, never backup return values
LD R1, SUB_STACK_PUSH
LD R2, SUB_STACK_POP
LD R3, SUB_RPN_ADD

LD R4, STACK_BASE
LD R5, STACK_MAX
LD R6, TOS      ; Dynamically holds TOS

; LEA R0, First_in
; PUTS
JSRR R1

; LEA R0, Second_in
; PUTS
; JSRR R1

; GETC
; OUT

; JSRR R3



HALT

; Local data
REG_STACK       .FILL xFE00
STACK_BASE      .FILL xA000
TOS             .FILL xA000
STACK_MAX       .FILL xA005
SUB_STACK_PUSH  .FILL x3200
SUB_STACK_POP   .FILL x3400
SUB_RPN_ADD     .FILL x3600
First_in        .stringz "\nPlease enter the first digit: \n"
Second_in       .stringz "\nPlease enter the second digit: \n"
Symbol_in       .stringz "\nPlease enter the operation symbol: \n"


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
ST R1, backup_r1_3200
ST R2, backup_r2_3200
ST R3, backup_r3_3200
ST R7, backup_r7_3200

;--------------

LD R1, ascii_offset_3200
NOT R1, R1
ADD R1, R1, #1 ; R1 = #-48

NOT R2, R6
ADD R2, R2, #1

ADD R2, R2, R5

ADD R2, R2, R5

BRp #7
    LEA R0, Overflow_Error
    PUTS
    BR END_3200

ADD R6, R6, #1
GETC
OUT
ADD R0, R1, R0
STR R0, R6, #0


END_3200:
;--------------
; Restoring Registers
;--------------
LD R1, backup_r1_3200
LD R2, backup_r2_3200
LD R3, backup_r3_3200
LD R7, backup_r7_3200


RET
backup_r1_3200      .blkw #1
backup_r2_3200      .blkw #1
backup_r3_3200      .blkw #1
backup_r7_3200      .blkw #1
Overflow_Error      .stringz    "\n Stack Overflow! \n"

OVERFLOW_DETECTED    .stringz "Overflow was detected"
ascii_offset_3200    .FILL x30  ; #48

.END

