%include "io64.inc"

section .data

section .rodata

section .bss
    state: resd 4

section .text
global main
global xorshift128

xorshift128:
    ; r9d - t
    ; r10d - s
    
    mov r9d, [state + 12]
    mov r10d, [state]
    
    mov r11d, [state + 8]
    mov [state + 12], r11d
    
    mov r11d, [state + 4]
    mov [state + 8], r11d
    
    mov [state + 4], r10d
    
    mov r11d, r9d ; t ^= t << 11;
    shl r11d, 11
    xor r9d, r11d
    
    mov r11d, r9d; t ^= t >> 8;
    shr r11d, 8
    xor r9d, r11d
    
    mov r11d, r10d ; s ^= s >> 19;
    shr r11d, 19
    xor r10d, r11d
    
    xor r11d, r11d ; r11d = 0
    
    xor r9d, r10d ; t^=s
    mov [state], r9d ; state[0] = t
    
    ret
   
main:
    ; r8d - seed
    ; ecx - i
    
    PRINT_STRING "Write seed: "
    GET_UDEC 4, r8d
    
    mov [state], r8d
    xor r8d, 0x12345678
    mov [state+4], r8d
    xor r8d, 0x87654321
    mov [state+8], r8d
    xor r8d, 0xABCDEF01
    mov [state+12], r8d
    
    mov ecx, 0
.start_cycle:
    cmp ecx, 100
    je main.end_cycle
    
    call xorshift128
    
    PRINT_UDEC 4, [state]
    PRINT_STRING " "
    
    add ecx, 1
    jmp main.start_cycle
.end_cycle:

    xor rax, rax
    xor rbx, rbx
    ret