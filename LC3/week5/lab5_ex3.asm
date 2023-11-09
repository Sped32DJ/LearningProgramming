;=================================================
; Name: Danny Topete
; Email: dtope004@ucr.edu
;
; Lab: lab 5, ex 3
; Lab section: 021
; TA: Karan / Nicholas
;
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE

LD R1, ARRAY_ADD;
LD R2,

; your code goes here
halt

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
.end

; your subroutines go below here
