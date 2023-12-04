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
LEA R2, user_prompt ; Holds prompt (temporarily)

LD R5, get_user_string_addr ; string from user input
    JSRR R5 ; R1 now holds filled input_string

; Get size of input_string
LEA R1, user_string ; Parameter
LD R5, strlen_addr
    JSRR R5 ; returns R3 with str.size

; call palindrome method
; * put your code here
LEA R1, user_string
ADD R2, R1, R3 ; R2 now holds the last char

ADD R3, R3, #0 ; if str.size = 0, you can skip the R2 -= 2
BRz IS_EMPTY ; If R2 is null char, skips --R2 (empty string case)
    ADD R2, R2, #-1 ; R2 holds the last char
IS_EMPTY

AND R0, R0, x0 ; intialize 0 (R0 bool parameter)
LD R5, palindrome_addr
JSRR R5 ; If bool R0 = 1(true), it is a palindrome!

; determine of string is a palindrome
; * put your code here
; R0 holds the bool

ADD R1, R0, #0 ; R1 now holds the bool
LEA R0, result_string
    PUTS

ADD R1, R1, #0
BRnp PRINT_FINAL_RESULT ; Skips "not" if it is valid palindrome


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
;string_size          .FILL #100   ; Will be overwritten
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
    BRnp NOT_AN_ENDL
        STR R3, R1, #0 ; Stores R3 (holding 0) into R1 (last char is null)
        BR WHILE_INPUT_END
    NOT_AN_ENDL
    STR R0, R1, #0 ; Stores input into curr addr
    ADD R1, R1, #1 ; ++addr, ready for next char
    BR WHILE_INPUT ; Goes back to grab next char

WHILE_INPUT_END ; Stops grabbing input


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
    BRz STOP_COUNT ; Stops counting after null (Doesn't iterate if there is a null)
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
; Parameter: R1 - first char of string
;       R2 - Last char of string
;       R6 - Holds stack
;       R3 - Used to hold result of tests
;               (Checks if the palindrome identity tests are passed)
; Return Value: R0 (bool holding true or false)
;=================================================

.ORIG x3400
palindrome ; Hint, do not change this label and use for recursive alls
; Backup all used registers, R7 first, using proper stack discipline
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

; Test 1: Range check
NOT R1, R1
ADD R1, R1, #1 ; R1 is now a mask

ADD R3, R1, R2 ; first addr (negative) and last addr -> if positive, keep checking
BRp CHECK_RANGE_PASSED ; Checks if R1 < R2, then keeps going
    AND R0, R0, x0
    ADD R0, R0, #1 ; R0 = true because R1 is ahead of R2 (Implying successful checks happened)
    BR DONE_CHECK ; Ends because this implies first char and last char addr are equal
CHECK_RANGE_PASSED

; R1 back original val
ADD R1, R1, #-1
NOT R1, R1

; Range test passed!!

; Test 2: Check First and last char similarity check
LDR R4, R1, #0  ; R4 Holds first char
LDR R5, R2, #0  ; R5 holds last char

; R4 now holds mask
NOT R4, R4
ADD R4, R4, #1

ADD R3, R4, R5 ; R3 holds sum of -R4 and R5 (should = 0)
    BRz CHARS_ARE_EQUAL ; If not equal, bool is false
        AND R0, R0, #0 ; R0 = false
        BR DONE_CHECK

CHARS_ARE_EQUAL

; Iterating the parameters for next recursive call
ADD R1, R1, #1
ADD R2, R2, #-1
JSR palindrome ; Recursively calling the top of the subroutine

DONE_CHECK ; Must be after the JSR!!
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

; ---------------
.END

; Pseudo code
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
