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

LEA R1, user_string ; Holds string, pointer to first char, BEG INDEX
LEA R2, user_prompt

LD R5, get_user_string_addr
    JSRR R5

; Get size of input_string
LEA R1, user_string ; Parameter
LD R5, strlen_addr
    JSRR R5 ; returns R3 with str.size

; call palindrome method
; * put your code here
LEA R1, user_string
ADD R2, R1, R0 ; R2 holds the last char (The null char)

ADD R3, R3, #0 ; if str.size = 0, you can skip the R2 -= 2
BRz IS_EMPTY
    ADD R2, R2, #-1 ; R2 holds the last char
IS_EMPTY

LD R5, palindrome_addr
JSRR R5 ; If bool R0 = 1(true), it is a palindrome!

; determine of string is a palindrome
; * put your code here
; R0 holds the bool

ADD R1, R0, #0 ; R1 now holds the bool
LEA R0, result_string
    PUTS

ADD R1, R1, #0
BRnp PRINT_FINAL_RESULT ; Skips "not" if it is valid


; decide whether or not to print "not"
; * put your code here
LEA R0, not_string ; Prints "not"
    PUTS

; print the result to the screen
; * put your code here
PRINT_FINAL_RESULT:

LEA R0, final_string
    PUTS



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
; Parameter: R1 (Beg Str addr)
; Parameter: R2 - user_prompt str addr
;               Holds ENDL_MASK after used
; Postcondition: R1 - addr of string
; Return Value: String_location(R1)
;=================================================

.ORIG x3200
get_user_string
; ---------------
; Backing up registers
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
; LEA R1 user_string
; LEA R2 user_prompt
ADD R0, R2, x0 ; R0 holds user_prompt to print
    PUTS

LD R2, ENDL_MASK ; R2 replaced to hold ENDL_MASK (NOT -> ADD #1)

WHILE_INPUT
    GETC
    OUT

    ADD R3, R0, R2 ; Input + ENDL_MASK
    BRz WHILE_INPUT_END ; if ENDL_MASK + ENDL = 0, stop grabbing input!
        STR R0, R1, #0 ; R0 into the string
        ADD R1, R1, #1 ; R1 ++addr for next char
    BR WHILE_INPUT ; Goes back to grab next char

WHILE_INPUT_END ; Stops grabbing input
    STR R3, R2, #0 ; (R3 is holding 0 for WHILE_INPUT_END to run)
    ; Adds the null to the end of the string


; ---------------
; Restoring Registers
; ---------------
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
ENDL_MASK            .FILL      x-0A ; Two's complement of \n, NOT -> ADD #1

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
ADD R6, R6, #-1
STR R0, R6, #0

ADD R6, R6, #-1
STR R1, R6, #0

ADD R6, R6, #-1
STR R2, R6, #0

; ADD R6, R6, #-1
; STR R3, R6, #0

ADD R6, R6, #-1
STR R4, R6, #0

ADD R6, R6, #-1
STR R5, R6, #0

ADD R6, R6, #-1
STR R7, R6, #0
; Code below

ADD R3, R3, x0 ; Initialize R3 (counter)

WHILE_COUNT
    LDR R2, R1, #0 ; R2 holds R1's curr char
    BRz STOP_COUNT ; Stops counting after null
    ADD R3, R3, #1 ; ++counter
    ADD R1, R1, #1 ; ++ addr
    BR WHILE_COUNT ; Checks next char
STOP_COUNT


; ---------------
; Restoring Registers
; ---------------
LDR R7, R6, #0
ADD R6, R6, #1

LDR R5, R6, #0
ADD R6, R6, #1

LDR R4, R6, #0
ADD R6, R6, #1

; LDR R3, R6, #0
; ADD R6, R6, #1

LDR R2, R6, #0
ADD R6, R6, #1

LDR R1, R6, #0
ADD R6, R6, #1

RET

.END


;---------------------------------------------------------------------------------
; palindrome - DO NOT FORGET TO REPLACE THIS HEADER WITH THE PROPER HEADER
;---------------------------------------------------------------------------------
;=================================================
; Subroutine: palindrome
; Parameter: R1(string)
; Parameter: R2 begginning index
; Parameter: R3 ending index
; Postcondition:
; Return Value: R0 (holds palindrome bool)
;=================================================

.ORIG x3400
palindrome ; Hint, do not change this label and use for recursive alls
; Backup all used registers, R7 first, using proper stack discipline
ADD R6, R6, #-1
STR R0, R6, #0

ADD R6, R6, #-1
STR R1, R6, #0

ADD R6, R6, #-1
STR R2, R6, #0

; ADD R6, R6, #-1
; STR R3, R6, #0

ADD R6, R6, #-1
STR R4, R6, #0

ADD R6, R6, #-1
STR R5, R6, #0

ADD R6, R6, #-1
STR R7, R6, #0
; Code below

; Resture all used registers, R7 last, using proper stack discipline
JSR palindrome

DONE_CHECK
; ---------------
; Restoring Registers
; ---------------
LDR R7, R6, #0
ADD R6, R6, #1

LDR R5, R6, #0
ADD R6, R6, #1

LDR R4, R6, #0
ADD R6, R6, #1

; LDR R3, R6, #0
; ADD R6, R6, #1

LDR R2, R6, #0
ADD R6, R6, #1

LDR R1, R6, #0
ADD R6, R6, #1


RET

; ---------------
.END

; Pseudo
; bool is_palindrome(char *beg, char *end){
; if (beg >= end) return true
;BR True_ending

; if (beg != end) return false

;return is_palindrome

; JSR palindrome

; If single char
; BEGINDEX - ENDINDEXZ
; if BRzp return true

;False check
; if arr[begINDEx] - ARR[ENDINDEX]
; if BRnp return false

; .ORIG x

; ---------------

; Backing up registers

; ADD R6, R6, #-1
; STR R0, R6, #0

; ADD R6, R6, #-1
; STR R1, R6, #0

; ADD R6, R6, #-1
; STR R2, R6, #0

; ADD R6, R6, #-1
; STR R3, R6, #0

; ADD R6, R6, #-1
; STR R4, R6, #0

; ADD R6, R6, #-1
; STR R5, R6, #0

; ADD R6, R6, #-1
; STR R7, R6, #0

; ; ---------------

; ; your code goes here
; ; ---------------

; ; Restoring Registers

; LDR R7, R6, #0
; ADD R6, R6, #1

; LDR R5, R6, #0
; ADD R6, R6, #1

; LDR R4, R6, #0
; ADD R6, R6, #1

; LDR R3, R6, #0
; ADD R6, R6, #1

; LDR R2, R6, #0
; ADD R6, R6, #1

; LDR R1, R6, #0
; ADD R6, R6, #1

; LDR R0, R6, #0
; ADD R6, R6, #1
; ; ---------------
