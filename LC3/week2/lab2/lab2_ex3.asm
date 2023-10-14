;=================================================
; Name: Danny Topete
; Email:  dtope004@ucr.edu
;
; Lab: lab 2, ex 3
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================

; LDR & STR

.ORIG x3000

LD R0, ARR_ADDR
LDR R1, R0, #0
;PUTS, nvm, this only pulls from R0

LDR R1, R0, #1
;PUTS

; STR Example
LD R0, ARR2_ADDR
STR R1, R0, #0
STR R1, R0, #1

HALT

ARR_ADDR .FILL x4000

ARR2_ADDR .FILL x4002

.END

.ORIG x4000

ARR0    .FILL #7 ; x4000
ARR1    .FILL #8

; .ORIG x4002
; Arrays make more sense now...
; Second Array (STR)
ARR2    .FILL #10 ;x4002
ARR4    .FILL #12

.END
