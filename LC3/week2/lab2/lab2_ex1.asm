;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 2. ex 1
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

.ORIG x3000

LD R3, DEC_65
LD R4, HEX_41
; Both of these values are equivalent in binary

HALT

DEC_65  .FILL #65
HEX_41  .FILL x41

.END
