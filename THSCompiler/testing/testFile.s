global main

section .text
Hello:
main:
sub rsp, 4
mov dword [rbp], 2
sub rsp, 9
mov dword [rbp-4], 2
mov byte [rbp-8], bool1
mov dword [rbp-9], __float32__(2.000000)
sub rsp, 9
mov dword eax, [rbp-4]
mov dword [rbp-13], eax
mov byte al, [rbp-8]
mov byte [rbp-17], al
mov dword eax, [rbp-9]
mov dword [rbp-18], eax
sub rsp, 4
mov dword eax, [rbp-18]
mov dword [rbp-22], eax

section .data
bool2: db 0

section .rodata
bool1: db 1
float2: dd 1.714286

