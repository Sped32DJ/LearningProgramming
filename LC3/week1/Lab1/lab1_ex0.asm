;=================================================
; Name:  Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 1, ex 0
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

.ORIG x3000
; R0 = Register 0
    LEA R0, MSG_TO_PRINT ; LEA, value of the entire address
                         ; LD, addrr of the first thing on the register
    PUTS ; print the string, always uses R0


HALT
    MSG_TO_PRINT .STRINGZ "Hello World!!!\n"

.END
