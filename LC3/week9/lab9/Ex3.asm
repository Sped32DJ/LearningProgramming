#include <stdio.h>

int main() {
    for (int i = 0; i < 15; i++) {
        printf("Hello, World!\n");
    }
}

.LC0:
        .string "Hello, World!"
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     DWORD PTR [rbp-4], 0
        jmp     .L2
.L3:
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        add     DWORD PTR [rbp-4], 1
.L2:
        cmp     DWORD PTR [rbp-4], 14
        jle     .L3
        mov     eax, 0
        leave
        ret

; Now with -O -funroll-loops
.LC0:
        .string "Hello, World!"
main:
        push    rbx
        mov     ebx, 15
.L2:
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        sub     ebx, 1
        jne     .L2
        mov     eax, 0
        pop     rbx
        ret

; Now with i<20
.LC0:
        .string "Hello, World!"
main:
        push    rbx
        mov     ebx, 20
.L2:
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        sub     ebx, 1
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        sub     ebx, 9
        jne     .L2
        mov     eax, 0
        pop     rbx
        ret
