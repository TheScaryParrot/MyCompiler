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
add rsp, 2
mov rsp, rbp
ret 
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
add rsp, 8
mov rsp, rbp
ret 
_start:
mov rbp, rsp
extern _print
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
mov dword [rbp-26], 10
JL2:
mov eax, dword [rbp-26]
cmp eax, 0
setg al
movzx eax, al
test eax, eax
jz JL1 
sub dword [rbp-26], 1
jmp JL2 
JL1:
sub rsp, 4
mov dword [rbp-30], __float32__(3.000000)
sub rsp, 4
mov dword [rbp-34], 0
JL5:
mov eax, dword [rbp-34]
cmp eax, 10
setl al
movzx eax, al
test eax, eax
jz JL3 
add dword [rbp-30], __float32__(1.000000)
JL4:
add dword [rbp-34], 2
jmp JL5 
JL3:
add rsp, 4
sub rsp, 4
mov eax, dword [rbp-27]
mov dword [rbp-34], eax
sub rsp, 1
mov al, byte [bool2]
mov byte [rbp-35], al
sub rsp, 1
mov al, byte [bool1]
mov byte [rbp-36], al
push rbp
call Hello
pop rbp
add rsp, 2
sub rsp, 1
mov al, byte [rax]
mov byte [rbp-35], al
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-39], eax
sub rsp, 4
mov dword [rbp-43], 2
push rbp
call Hello2
pop rbp
add rsp, 8
sub rsp, 4
mov eax, dword [rax]
mov dword [rbp-39], eax
sub rsp, 4
mov eax, dword [rbp-39]
mov dword [rbp-43], eax
sub rsp, 4
mov dword [rbp-47], 4
push rbp
call _print
pop rbp
add rsp, 12
add rsp, 35
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

