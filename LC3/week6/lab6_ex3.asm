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

LEA R0, First_in
PUTS
JSRR R1

LEA R0, Second_in
PUTS
JSRR R1

GETC
OUT

JSRR R3



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
    LEA R0, Overflow_Error  ;output the error msg, and reset the data
    PUTS
    LD R1, backup_r1_3200
    LD R2, backup_r2_3200
    LD R3, backup_r3_3200
    LD R7, backup_r7_3200
    RET

ADD R6, R6, #1
GETC
OUT
ADD R0, R1, R0
STR R0, R6, #0


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
;------------------------------------------------------------------------------------------
; Subroutine: SUB_STACK_POP
; Parameter (R3): BASE: A pointer to the base (one less than the lowest available address) of the
; stack
; Parameter (R4): MAX: The "highest" available address in the stack
; Parameter (R5): TOS (Top of Stack): A pointer to the current top of the stack
; Postcondition: The subroutine has popped MEM[TOS] off of the stack and copied it to R0.
; If the stack was already empty (TOS = BASE), the subroutine has printed
; an underflow error message and terminated.
; Return Values: R0 ← value popped off the stack
; R5 ← updated TOS
;------------------------------------------------------------------------------------------
.ORIG x3400
; Backup Registers
ST R1, backup_r1_3400
ST R2, backup_r2_3400
ST R3, backup_r3_3400
ST R7, backup_r7_3400

NOT R2, R4
ADD R2, R2, #1
ADD R2, R2, R6
BRp #7
LEA R0, Underflow_Error ;output the error msg, and reset the data
PUTS
LD R1, backup_r1_3400
LD R2, backup_r2_3400
LD R3, backup_r3_3400
LD R7, backup_r7_3400
RET


LDR R0, R6, #0
ADD R6, R6, #-1

END_3400:

LD R2, backup_r2_3400
LD R3, backup_r3_3400
LD R7, backup_r7_3400


RET
backup_r1_3400      .blkw #1
backup_r2_3400      .blkw #1
backup_r3_3400      .blkw #1
backup_r7_3400      .blkw #1
Underflow_Error      .stringz    "\n Underflow Overflow! \n"

.END

;------------------------------------------------------------------------------------------
; Subroutine: SUB_RPN_ADD
; Parameter (R4): BASE: A pointer to the base (one less than the lowest available
;                       address) of the stack
; Parameter (R5): MAX: The "highest" available address in the stack
; Parameter (R6): TOS (Top of Stack): A pointer to the current top of the stack
; Postcondition: The subroutine has popped off the top two values of the stack,
;		    added them together, and pushed the resulting value back
;		    onto the stack.
; Return Value: R6 ← updated TOS address
;------------------------------------------------------------------------------------------

.ORIG x3600
ST R1, backup_r1_3600
ST R2, backup_r2_3600
ST R3, backup_r3_3600
ST R7, backup_r7_3600

JSRR R2                 ;r0 hold the first input
AND R3, R3, #0          ;clear r3, and store the first number in R3
ADD R3, R0, R3
BRz #10

JSRR R2                 ;now the second value is stored in r0
BRnp #2                 ;if the first input is 0, result is 0
    AND R3, R3, #0      ;becauee one of first input number is 0, so just set both number as 0.
    BRz #6

AND R1, R1, #0
ADD R1, R1, R3          ;NOW r1 sotre the first popped value, used in the loop_add

LOOP_add                ;do the multiplication of those 2 numbers
    ADD R0, R0, #-1
        brnz #2
    ADD R3, R3, R1
    BRp LOOP_add

LEA R0, Print_result
PUTS

AND R0, R0, #0          ;move the number from r3 to r0
ADD R0, R3, R0

ADD R6, R6, #1          ;move the tos to the next address
STR R0, R6, #0          ;store the value into the stack

AND R0, R0, #0          ;move the number from r3 to r0
ADD R0, R3, R0
LD R1, ascii_offset_3600
ADD R0, R0, R1
OUT

; Backup register:
LD R1, backup_r1_3600
LD R2, backup_r2_3600
LD R3, backup_r3_3600
LD R7, backup_r7_3600

RET
; SUB_RPN_MULTIPLY local data
backup_r1_3600      .blkw #1
backup_r2_3600      .blkw #1
backup_r3_3600      .blkw #1
backup_r7_3600      .blkw #1

ascii_offset_3600   .FILL x30  ; #48
Print_result          .stringz "\n The final result is: \n"
;===============================================================================================
.END

