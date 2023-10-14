;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 2, ex 2
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

;LDI and STI
; Load vs Store Indirect
.ORIG x3000

LDI R1, FARAWAYDATA_ADDR

LD R2, DEC_5 ; Override the 4 with a 5
STI R2, DOGS_ADDR

HALT

FARAWAYDATA_ADDR        .FILL x4000

DEC_5   .FILL #5
DOGS_ADDR               .FILL x4001

.END

.ORIG x4000

FARAWAYDATA     .FILL #7

DOGS            .FILL #4 ; There are 4 dogs

.END
