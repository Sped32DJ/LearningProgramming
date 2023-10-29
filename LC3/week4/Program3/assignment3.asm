;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name:  Danny Topete
; Email: dtope004@ucr.edu
;
; Assignment name: Assignment 3
; Lab section: 021
; TA: Karan / Nicholas
;
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R6, Value_ptr		; R6 <-- pointer to value to be displayed as binary
LDR R1, R6, #0			; R1 <-- value to be displayed as binary
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------

; TESTING  PURPOSES
;IN ; Grab input -> R0 + echo
;ADD R1, R0, #0

LD R5, Iteration_count ; R5 holds iterations
LD R4, ascii_offset    ; R4 holds ascii_offset

; Building tunnels is fun!
MAIN_LOOP
    ; Check if pos or neg
    ADD R1, R1, #0 ; BR checks LMR
    BRn IF_ONE
    BRzp IF_ZERO


Space_Printer
    ADD R1, R1, R1 ; Left shifting
    ADD R5, R5, #-1 ; --iteration
                    ; Works because it enters this loop every time

; These 3 blocks check if a space is needed
    ADD R3, R5, #0 ; Copy count to R3
    LD R2, END_NIBBLE_1
    ADD R3, R3, R2 ; Value copied to check with ascii_offset
    BRz OUT_SPACE       ; if(#Iteration % 4 == 0) print space

    ADD R3, R5, #0
    LD R2, END_NIBBLE_2
    ADD R3, R3, R2
    BRz OUT_SPACE

    ADD R3, R5, #0
    LD R2, END_NIBBLE_3
    ADD R3, R3, R2
    BRz OUT_SPACE

NEXT_NIBBLE
    ADD R5, R5, #0
    BRp MAIN_LOOP ; Print another nibble if Iterations > 0
                  ; Tunnels back to the top
    BRnz  ENDL          ; If (Iterations < 0), endl, then HALT
    BRnzp ENDL

; Prints out MSB
; Then checks if a space is required
; binary set to x0000, then given ascii_offset

; Tunnels back to the top so OUT_SPACE doesn't prematurely execute
; Below are the base cases
IF_ZERO
    AND R0, R0, #0
    ADD R0, R0, R4 ; ascii_offset to print '0'
    OUT
    BRnzp       Space_Printer ; Tunnels back up

IF_ONE
    AND R0, R0, #0 ; Set to 0
    ADD R0, R0, #1
    ADD R0, R0, R4 ; ascii_offset to print '1'
    OUT
    BRnzp       Space_Printer

OUT_SPACE ;OUTPUT SPACE
    LD R0, Space
    OUT
    BRnzp NEXT_NIBBLE ; Jumps up and NEXT_NIBBLE (which jumps up to start or ending)

; Doesn't end in BR, so it goes straight to HALT
; Below only executes if NEXT_NIBBLE tunnels here
ENDL
    LD R0, Newline
    OUT

HALT

;---------------
;Data
;---------------
Value_ptr	.FILL xCA01	; The address where value to be displayed is stored
;Pos_Twos_Mask   .FILL x8FFF     ; AND Mask 1000 1111 1111 1111
; This mask was never used
Space           .FILL x20
Newline         .FILL x0A
ascii_offset    .FILL x30
Iteration_count .FILL #16

; Compensate for lack of modulo (if R3%4)
END_NIBBLE_1    .FILL #-12
END_NIBBLE_2    .FILL #-8
END_NIBBLE_3    .FILL #-4

.END

.ORIG xCA01					; Remote data
Value .FILL  xABCD			; <----!!!NUMBER TO BE DISPLAYED AS BINARY!!! Note: label is redundant.
;---------------
;END of PROGRAM
;---------------
.END
