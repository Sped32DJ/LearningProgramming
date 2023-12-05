#include <stdio.h>
int main(){
    printf("Hello World\n");
    return 0    ;
}

.LC0:
        .string "Hello World"
main:
        push    rbp
        mov     rbp, rsp
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     eax, 0
        pop     rbp
        ret

; Q2
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
}
.LC0:
        .string "Hello, world! %d \n"
main:
        push    rbp
        mov     rbp, rsp
        mov     esi, 10 ; Takes care of loops
        mov     edi, OFFSET FLAT:.LC0
        mov     eax, 0
        call    printf
        mov     eax, 0
        pop     rbp
        ret

; With -O1
.LC0:
        .string "Hello, world! %d \n"
main:
        sub     rsp, 8
        mov     esi, 10
        mov     edi, OFFSET FLAT:.LC0
        mov     eax, 0
        call    printf
        mov     eax, 0
        add     rsp, 8
        ret

; With -O2
.LC0:
        .string "Hello, world! %d \n"
main:
        sub     rsp, 8
        mov     esi, 10
        mov     edi, OFFSET FLAT:.LC0
        xor     eax, eax ; Arithmetic faster than moving data
        call    printf
        xor     eax, eax
        add     rsp, 8
        ret

; With -O3
.LC0:
        .string "Hello, world! %d \n"
main:
        sub     rsp, 8
        mov     esi, 10
        mov     edi, OFFSET FLAT:.LC0
        xor     eax, eax
        call    printf
        xor     eax, eax
        add     rsp, 8
        ret
