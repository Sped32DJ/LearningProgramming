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





HALT				; Stop execution of program
;------
;Data
;------
; String to prompt user. Note: already includes terminating newline!
intro 	.STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 		; prompt string - use with LEA, followed by PUTS.
newline .FILL x0A	; newline character - use with LD followed by OUT

;---------------
;END of PROGRAM
;---------------
.END

