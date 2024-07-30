global _start

section .text
Hello:
mov rbp, rsp
sub rsp, 1
mov al, byte [rbp+16]
mov byte [rbp-1], al
sub rsp, 1
mov al, byte [rbp+17]
mov byte [rbp-2], al
mov rsp, rbp
mov al, byte [rbp-1]
and al, byte [rbp-2]
mov byte [rbp-1], al
mov rax, rbp
sub rax, 1
ret 
mov rsp, rbp
ret 
add rsp, 2
Hello2:
mov rbp, rsp
sub rsp, 4
mov eax, dword [rbp+16]
mov dword [rbp-4], eax
sub rsp, 4
mov eax, dword [rbp+20]
mov dword [rbp-8], eax
mov rsp, rbp
mov eax, dword [rbp-4]
add eax, dword [rbp-8]
mov dword [rbp-4], eax
mov rax, rbp
sub rax, 4
ret 
mov rsp, rbp
ret 
add rsp, 8
_start:
mov rbp, rsp
sub rsp, 4
mov dword [rbp-4], 66
sub rsp, 9
mov dword [rbp-13], 2
mov al, byte [bool1]
mov byte [rbp-17], al
mov dword [rbp-18], __float32__(2.000000)
sub rsp, 9
mov eax, dword [rbp-13]
mov dword [rbp-22], eax
mov al, byte [rbp-17]
mov byte [rbp-26], al
mov eax, dword [rbp-18]
mov dword [rbp-27], eax
sub rsp, 4
mov eax, dword [rbp-27]
mov dword [rbp-26], eax
sub rsp, 1
mov al, byte [bool2]
mov byte [rbp-27], al
sub rsp, 1
mov al, byte [bool1]
mov byte [rbp-28], al
push rbp
call Hello
pop rbp
add rsp, 2
sub rsp, 1
mov al, byte [rax]
mov byte [rbp-27], al
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-31], eax
sub rsp, 4
mov dword [rbp-35], 2
push rbp
call Hello2
pop rbp
add rsp, 8
sub rsp, 4
mov eax, dword [rax]
mov dword [rbp-31], eax

; print rbp-31
mov rax, 1
mov rdi, 1
mov rsi, rbp
sub rsi, 31
mov rdx, 4
syscall

mov eax, 60
xor edi, edi
syscall 
ret 
add rsp, 31

section .bss
bool3: resb 1
float3: resb 4

section .data
bool2: db 0

section .rodata
bool1: db 1
float2: dd 1.714286

