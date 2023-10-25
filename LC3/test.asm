    .ORIG x3000
    LD R3,FT        ; load x4000 in R3 as array base address
    LD R2,Count        ; load #10 in R2 as counter from 10 to 1
Loop
    TRAP x23        ; take input from user
    STR R0,R3,#0        ; store inputted chatacter in mem addr stored in R3
    ADD R3,R3,#1        ; increment R3 (mem location)
    ADD R2,R2,#-1        ; decrement R2 (counter)
    BRp Loop
    HALT
FT    .FILL x4000
Count    .FILL #10
    .END
