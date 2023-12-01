; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Assignment name: Assignment 5
; Lab section: 021
; TA: Karan / Nicholas
;
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
; PUT ALL YOUR CODE AFTER THE main LABEL
;=================================================================================

;---------------------------------------------------------------------------------
;  Initialize program by setting stack pointer and calling main subroutine
;---------------------------------------------------------------------------------
.ORIG x3000

; initialize the stack
LD R6, stack_addr

; call main subroutine
LEA R5, main
JSRR R5

;---------------------------------------------------------------------------------
; Main Subroutine
;---------------------------------------------------------------------------------
main
; get a string from the user
; * put your code here

; To getline, you just keep getting input until sentinel
; Declaring Parameters

LEA R1, user_string ; Holds string, pointer to first char
LD R6, get_user_string_addr
JSRR R6

; call palindrome method
; * put your code here
LD R6, palindrome_addr
JSRR R6

; determine of string is a palindrome
; * put your code here

; print the result to the screen
; * put your code here

; decide whether or not to print "not"
; * put your code here


HALT

;---------------------------------------------------------------------------------
; Required labels/addresses
;---------------------------------------------------------------------------------

; Stack address ** DO NOT CHANGE **
stack_addr           .FILL      xFE00


; Addresses of subroutines, other than main
get_user_string_addr .FILL      x3200
strlen_addr          .FILL      x3300
palindrome_addr      .FILL      x3400


; Reserve memory for strings in the progrtam
user_prompt          .STRINGZ "Enter a string: "
result_string        .STRINGZ "The string is "
not_string           .STRINGZ "not "
final_string         .STRINGZ "a palindrome\n"

; Reserve memory for user input string
string_size          .FILL #100   ; Will be overwritten
user_string          .BLKW	  100

.END

;---------------------------------------------------------------------------------
; get_user_string - DO NOT FORGET TO REPLACE THIS HEADER WITH THE PROPER HEADER
;---------------------------------------------------------------------------------
;=================================================
; Subroutine: get_user_string
; Parameter: R1(string), R2(ENDL_MASK)
; Postcondition:
; Return Value: String_location(R1)
;=================================================

.ORIG x3200
get_user_string
; ---------------
; Backing up registers
LD R6, STACK_3200
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

ADD R6, R6, #-1
STR R5, R6, #0

ADD R6, R6, #-1
STR R7, R6, #0
; Backup all used registers, R7 first, using proper stack discipline
; ---------------

; your code goes here
; LEA L1 user_string
LD R2, ENDL_MASK

WHILE_INPUT
    GETC
    OUT

    ADD R1, R1, #1 ; Iterating ADDR
    STR R1, R0, #0 ;Add value to R1

    ADD R0, R0, R2 ; If R0 is \n
    BRnp WHILE_INPUT

; Adding a null at the end of the string
ADD R1, R1, #1
ADD R0, R0, x0
STR R1, R0, #0

; ---------------
; Restoring Registers
; ---------------
LD R6, STACK_3200
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
ENDL_MASK            .FILL      x-0A

; Resture all used registers, R7 last, using proper stack discipline

.END


;---------------------------------------------------------------------------------
; strlen - DO NOT FORGET TO REPLACE THIS HEADER WITH THE PROPER HEADER
;---------------------------------------------------------------------------------
;=================================================
; Subroutine: strlen
; Parameter: R1(String)
; Postcondition:
; Return Value: R3(string_size)
;=================================================
.ORIG x3300
strlen

; Backup all used registers, R7 first, using proper stack discipline
LD R6, STACK_3300
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

ADD R6, R6, #-1
STR R5, R6, #0

ADD R6, R6, #-1
STR R7, R6, #0
; Code below

ADD R3, R3, x0

WHILE_COUNT
    STR R1, R1, #0
    ADD R3, R3, #1

    ADD R4, R0, x0 ; Keeps counting until null
    BRnp WHILE_COUNT

ADD R3, R3, #-1



; ---------------
; Restoring Registers
; ---------------
LD R6, STACK_3200
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

.END


;---------------------------------------------------------------------------------
; palindrome - DO NOT FORGET TO REPLACE THIS HEADER WITH THE PROPER HEADER
;---------------------------------------------------------------------------------
;=================================================
; Subroutine: palindrome
; Parameter:
; Postcondition:
; Return Value:
;=================================================

.ORIG x3400
palindrome ; Hint, do not change this label and use for recursive alls
; Backup all used registers, R7 first, using proper stack discipline

; Resture all used registers, R7 last, using proper stack discipline
.END

