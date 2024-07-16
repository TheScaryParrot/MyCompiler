extern printf

global main

section .text
main:
    mov rdi, printf_format
    mov rsi, 0x404000
    mov rax, 0
    call printf


    mov rax, 60
    mov rdi, 0
    syscall


section .rodata
    printf_format: db '%x', 10, 0