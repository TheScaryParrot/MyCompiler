global _start

section .text
Hello:
mov rbp, rsp
sub rsp, 1
mov al, byte [rbp+8]
mov byte [rbp-8], al
sub rsp, 1
mov al, byte [rbp+9]
mov byte [rbp-9], al
mov rsp, rbp
ret 
_start:
mov rbp, rsp
sub rsp, 4
mov dword [rbp-8], 2
sub rsp, 9
mov dword [rbp-12], 2
mov al, byte [bool1]
mov byte [rbp-16], al
mov dword [rbp-17], __float32__(2.000000)
sub rsp, 9
mov eax, dword [rbp-12]
mov dword [rbp-21], eax
mov al, byte [rbp-16]
mov byte [rbp-25], al
mov eax, dword [rbp-17]
mov dword [rbp-26], eax
sub rsp, 4
mov eax, dword [rbp-26]
mov dword [rbp-30], eax
sub rsp, 1
mov al, byte [bool2]
mov byte [rbp-34], al
sub rsp, 1
mov al, byte [bool1]
mov byte [rbp-35], al
push rbp
call Hello
pop rbp
add rsp, 2
mov eax, 60
xor edi, edi
syscall 
ret 

section .bss
bool3: resb 1
float3: resb 4

section .data
bool2: db 0

section .rodata
bool1: db 1
float2: dd 1.714286

