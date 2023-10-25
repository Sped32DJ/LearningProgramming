;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 3, ex 3
; Lab section: 021
; TA: Karan/Nicholas
;
;=================================================

.ORIG   x3000

LD R3, ARR_PTR ; Holds ARR
;LD R2, Counter    ; Holds iterations
AND R2, R2, #0

LD R4, char_q
NOT R4, R4
ADD R4, R4, #1 ; Grabbing two's complement

LOOP ; Fill the array, doesn't terminte with 'q'
    TRAP x23
    STR R0, R3, #0 ; Store R0 into mem addr
    ADD R3, R3, #1 ; increment by 1
    ; Use this to allocate a larger Array

    ADD R5, R0, R4 ; R4 holds #113 = x71
    BRnp LOOP ; Looks for 0

; output the array
AND R3, R3, #0
AND R2, R2, #0

LD R3, ARR_PTR  ; Holds addr
LD R2, Count    ; Holds iterations
; Enteres loops, insta craash
LOOP_2
;    STR R0, R3, #0
    LDR R0, R3, #0
    OUT
;    LD R0, Space
    OUT ; OUT because hex
    ADD R3, R3, #1
    ADD R2, R2, #-1


    BRp Loop_2
LD R0, Space


HALT

Count           .FILL #10
ARR_PTR         .FILL x4000
Space           .FILL x0A
char_q          .FILL x71

.END

.ORIG x4000

; Dynamic Allocating loop doesn't work
ARRAY_1         .BLKW   #100 ;Allocate 10 mem

.END
