
.ORIG x3000 ; Program starts at address x3000 (hexadecimal)
            ; in C++, it begins in main()

; storing data inside registeres, int datatype
LD R1, DEC_6
LD R2, DEC_12
LD R3, DEC_0

DO_WHILE
    ADD R3, R3, R2
    ADD R1, R1, #-1
    BRp DO_WHILE

HALT ; return 0 from main
