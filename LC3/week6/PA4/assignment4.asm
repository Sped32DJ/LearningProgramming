;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Assignment name: Assignment 4
; Lab section: 021
; TA: Karan / Nicholas
;
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
;THE BINARY REPRESENTATION OF THE USER-ENTERED DECIMAL NUMBER MUST BE STORED IN R4
;=================================================================================

.ORIG x3000
;-------------
;Instructions
;-------------

; TODO   CHANGE ALL THE NAMES

; output intro prompt
IntroPrompt:
    LD R0, introPromptPtr
    PUTS

; Set up flags, counters, accumulators as needed
SetFlags:

; RESULT in R4
; R5 COUNTER    FROM #5
; R1 IS OUR CHECKER
    AND R4, R4, x0
    LD R5, COUNTER
    AND R0, R0, x0
    AND R1, R1, x0

; Get first character, test for '\n', '+', '-', digit/non-digit
FirstChar:
    GETC
    OUT
; is very first character = '\n'? if so, just quit (no message)!
    LD R1, newlineCheck
    ADD R1, R1, R0
    BRz TerminateProgram

; is it = '+'? if so, ignore it, go get digits
    LD R1, plus
    ADD R1, R1, R0
    BRz TerminateProgram

; is it = '-'? if so, set neg flag, go get digits
    LD R1, minus
    ADD R1, R1, R0
    Brz SetNegFlag

    BR NextNums

SetNegFlag:
    ADD R6, R6, #-1
    BR CharCheck

CharCheck:
    GETC
    OUT

NextNums:

; CHECK IF ENDL WAS ENTERED, THEN QUIT
    LD R1, newlineCheck
    ADD R1, R1, R0
    BRz TerminateProgram

; is it < '0'? if so, it is not a digit	- o/p error message, start over
    LD R1, zero
    ADD R1, R1, R0
    BRn IssueError
; is it > '9'? if so, it is not a digit	- o/p error message, start over
    LD R1, nine
    ADD R1, R1, R0
    BRp IssueError

; if none of the above, first character is first numeric digit - convert it to number & store in target register!
    LD R1, zero
    ADD R0, R0, R1 ;R0 should hold our true numeric val

    AND R7, R7, #0      ;START at 0
    ADD R7, R4, #0      ; PUT R4 curr into R7

    AND R7, R7, #0 ; start as 0
    ADD R7, R4, #0 ; Put R4 into R7
    LD R3, ten
    AND R1, R1,  #0

    Multiply:
        ADD R1, R1, R4
        ADD R3, R3, #-1
        BRp Multiply

    ; ADD CURR
    ADD R4, R1, R0

    ADD R5, R5, #-1 ; Decrement counter

    BRz TerminateProgram
    BRp CharCheck



; Now get remaining digits from user in a loop (max 5), testing each to see if it is a digit, and build up number in accumulator
IssueError:
    LD R0, errorMessagePtr
    PUTS
    BR IntroPrompt

; remember to end with a newline!
TerminateProgram:
    ;TODO  IF negative, Make R4 Negative
    ;OUTPUT NEWLINE
    ; This should be like 2 lines

;

HALT

;---------------
; Program Data
;---------------

introPromptPtr  .FILL xB000
errorMessagePtr .FILL xB200

COUNTER         .FILL #5
newline         .FILL #-10
plus            .FILL x-2B
minus           .FILL x-2D
zero            .FILL x-48 ;ascii
nine            .FILL x-57 ;ascii
ten             .FILL #10



.END

;------------
; Remote data
;------------
.ORIG xB000	 ; intro prompt
.STRINGZ	 "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"

.END

.ORIG xB200	 ; error message
.STRINGZ	 "ERROR: invalid input\n"

;---------------
; END of PROGRAM
;---------------
.END

;-------------------
; PURPOSE of PROGRAM
;-------------------
; Convert a sequence of up to 5 user-entered ascii numeric digits into a 16-bit two's complement binary representation of the number.
; if the input sequence is less than 5 digits, it will be user-terminated with a newline (ENTER).
; Otherwise, the program will emit its own newline after 5 input digits.
; The program must end with a *single* newline, entered either by the user (< 5 digits), or by the program (5 digits)
; Input validation is performed on the individual characters as they are input, but not on the magnitude of the number.
