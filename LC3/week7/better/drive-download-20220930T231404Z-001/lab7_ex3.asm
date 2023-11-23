;=================================================
; Name:  Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 7, ex 1
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

;========================
; Main Program
;========================
.ORIG x3000

    ; Setup parameter
    AND R1, R1, #0
    ADD R1, R1, #5

    ; Call the factorial sub-routine
    LD R6, FACT_SUB_ADDR
    JSRR R6

    HALT
;========================
; Local Data
;========================
FACT_SUB_ADDR   .FILL x3200
.END

;=======================================================================
; Subroutine: SUB_FACT
; Parameter (R1): Starting number for the factorial.
; Postcondition: Take the factorial of the value in R1.
; Return Value (R0): Result of the factorial.
;=======================================================================
.ORIG x3200
;========================
; Subroutine Instructions
;========================
FACT_SUB_START
; Backup Registers R1-7
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

; Subroutine Logic

;  NOTE
; ADD R2, R1, R2 ; Added
ADD R1, R1, #-1
BRz BASE_3200 ; Recursive Base Case: if r1 == 0 jump to base case
; Recursive call

LD R6, MUL_SUB_ADDR_3200
JSRR R6

JSR FACT_SUB_START

; Setup multiplication parameters
ADD R2, R1, #0 ; Move result of factorial call to R2
ADD R1, R1, #1 ; Use original value of R1

; Perform multiplication
LD R6, MUL_SUB_ADDR_3200
JSRR R6
BR RESTORE_3200 ; Skip the base case

; Handle base case, return 1
BASE_3200
AND R0, R0, #0
ADD R0, R0, #1

; Restore Registers
RESTORE_3200
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

;========================
; Subroutine Data
;========================
MUL_SUB_ADDR_3200   .FILL x3400
BACKUP_3200         .FILL xFE00

.END

;=======================================================================
; Subroutine: SUB_MULT
; Parameter (R1): First operand.
; Parameter (R2): Second operand.
; Postcondition: Multiply the first operand by the second operand.
; Return Value (R0): Return the product.
;=======================================================================
.ORIG x3400
;========================
; Subroutine Instructions
;========================
; Backup registers
; ST R1, BACKUP_R1_3400
; ST R2, BACKUP_R2_3400
LD R6, BACKUP_3400
; Backup Registers R1-7
ADD R6, R6, #-1
STR R1, R6, #0 ; Access Violation

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

; Backup done

; Subroutine logic
AND R0, R0, #0
;NOTE  ADDED
; ADD R2, R1, #-1

MULT_LOOP_3400
    ADD R0, R0, R1
    ADD R2, R2, #-1
    BRp MULT_LOOP_3400

; Restore registers
; LD R1, BACKUP_R1_3400
; LD R2, BACKUP_R2_3400
; Restore Registers
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

;========================
; Subroutine Data
;========================
; BACKUP_R1_3400  .BLKW #1
; BACKUP_R2_3400  .BLKW #1
BACKUP_3400     .FILL xFE00
.END
