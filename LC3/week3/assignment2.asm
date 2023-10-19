;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name:  Danny Topete
; Email: dtope004@ucr.edu
;
; Assignment name: Assignment 2
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

;----------------------------------------------
;output prompt
;----------------------------------------------
LEA R0, intro			; get starting address of prompt string
PUTS			    	; Invokes BIOS routine to output string

;-------------------------------
;INSERT YOUR CODE here
;--------------------------------

; Grab input
; TODO  Convert to ASCII
GETC
OUT

; Convert into ascii, x30
ADD R1, R0, #0
LD R0, newline
OUT

GETC
OUT
ADD R2, R0, #0

LD R0, newline
OUT

; output 5 - 7 =
ADD R0, R1, #0
OUT
LD R0, space
OUT
LD R0, minus
OUT
LD R0, space
OUT
ADD R0, R2, #0
OUT
LD R0, space
OUT
LD R0, equal
OUT
LD R0, space
OUT

LD R3, ascii
ADD R1, R1, R3
ADD R2, R2, R3

; Take care of negative
NOT R2, R2
ADD R2, R2, #1
ADD R4, R1, R2

LD R5, ascii ; R5 holds ascii offset
ADD R4, R4, #0

; Enter function
BRn neg_conversion ;BR-n 'n' = negative
ADD R0, R4, #0
ADD R0, R0, R5 ; R0 = R4 + R5
OUT
BR end

; Function defined
neg_conversion
NOT R4, R4
ADD R4, R4, #1 ; Two's complement offset
ADD R4, R4, R5 ; ascii offset!
LD R0, minus
OUT

ADD R0, R4, #0
OUT
END ;Function ends

LD R0, newline
OUT

HALT				; Stop execution of program
;------
;Data
;------
; String to prompt user. Note: already includes terminating newline!
intro 	.STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 		; prompt string - use with LEA, followed by PUTS.
newline .FILL x0A	; newline character - use with LD followed by OUT
minus .FILL x2D
equal .FILL x3D
space .FILL x20
ascii .FILL x30
;---------------
;END of PROGRAM
;---------------
.END

