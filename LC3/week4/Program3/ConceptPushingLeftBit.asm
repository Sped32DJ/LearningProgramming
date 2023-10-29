.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R6, Value_ptr		; R6 <-- pointer to value to be displayed as binary
LDR R1, R6, #0			; R1 <-- value to be displayed as binary
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------

IN ; Grab input -> R0 + echo
STR R1, R6, #0 ; Storing R1 into R6 pointer
ADD R5, R5, #16 ; 16 iterations
ADD R4, R4, ascii_offset

WHILE_LOOP
LD R0, R1 ; R1 now holds the val
ADD R0, R0, R4
OUT

ADD R1, R1, R1 ; Left shifting bit
ADD R2, R2, #-1
BRp WHILE_LOOP


IF_POSITIVE
    AND R0, R0, #0
    ADD R0, R0, R4
    OUT
    BRnzp       NIBBLE

;Val two's complement
IF_NEGATIVE
    AND R0, R0, #0 ; Set to 0
    ADD R0, R0, #1 ;
    ADD R0, R0, R4 ; ascii_offset
    OUT
    BRnzp       NIBBLE ; GOTO Space function


HALT
;---------------
;Data
;---------------
Value_ptr	.FILL xCA01	; The address where value to be displayed is stored
Pos_Twos_Mask   .FILL x8FFF     ; AND Mask 1000 1111 1111 1111
Space           .FILL x20
Newline         .FILL x0A
ascii_offset    .FILL x30

.END

.ORIG xCA01					; Remote data
Value .FILL  ABCD			; <----!!!NUMBER TO BE DISPLAYED AS BINARY!!! Note: label is redundant.
;---------------
;END of PROGRAM
;---------------
.END

