global _start

section .text
_start:
mov rbp, rsp
extern _print
extern intToChar
sub rsp, 4
mov eax, 0
mov dword [rbp-4], eax
sub rsp, 4
mov eax, 1
mov dword [rbp-8], eax
JL2:
mov eax, dword [rbp-4]
cmp eax, 10
setl al
movzx eax, al
test eax, eax
jz JL1 
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-12], eax
push rbp
call intToChar
pop rbp
add rsp, 4
sub rsp, 4
mov eax, dword [rax]
mov dword [rbp-12], eax
sub rsp, 4
mov eax, dword [rbp-12]
mov dword [rbp-16], eax
sub rsp, 4
mov eax, 4
mov dword [rbp-20], eax
push rbp
call _print
pop rbp
add rsp, 12
mov eax, dword [rbp-4]
add eax, dword [rbp-8]
sub rsp, 4
mov dword [rbp-12], eax
mov eax, dword [rbp-8]
mov dword [rbp-4], eax
mov eax, dword [rbp-12]
mov dword [rbp-8], eax
add rsp, 4
jmp JL2 
JL1:
add rsp, 8
mov eax, 60
xor edi, edi
syscall 
ret 

