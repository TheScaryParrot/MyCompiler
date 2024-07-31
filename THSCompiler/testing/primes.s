section .text
isPrime:
mov rbp, rsp
extern mod
sub rsp, 4
mov eax, 2
mov dword [rbp-4], eax
JL3:
mov eax, dword [rbp-4]
cmp eax, dword [rbp+16]
setl al
movzx eax, al
test eax, eax
jz JL1 
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-8], eax
sub rsp, 4
mov eax, dword [rbp+16]
mov dword [rbp-12], eax
push rbp
call mod
pop rbp
add rsp, 8
sub rsp, 4
mov eax, dword [rax]
mov dword [rbp-8], eax
mov eax, dword [rbp-8]
cmp eax, 0
sete al
movzx eax, al
test eax, eax
jz JL4 
mov rsp, rbp
mov al, 0
mov byte [rbp-1], al
mov rax, rbp
sub rax, 1
ret 
jmp JL4 
JL4:
add rsp, 4
JL2:
mov eax, 1
add dword [rbp-4], eax
jmp JL3 
JL1:
add rsp, 4
mov rsp, rbp
mov al, 1
mov byte [rbp-1], al
mov rax, rbp
sub rax, 1
ret 
mov rsp, rbp
ret 
global _start
_start:
mov rbp, rsp
extern _print
extern intToChar
sub rsp, 4
mov eax, 2
mov dword [rbp-4], eax
JL7:
mov eax, dword [rbp-4]
cmp eax, 10
setl al
movzx eax, al
test eax, eax
jz JL5 
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-8], eax
push rbp
call isPrime
pop rbp
add rsp, 4
sub rsp, 1
mov al, byte [rax]
mov byte [rbp-5], al
mov al, byte [rbp-5]
test [rbp-5], al
jz JL8 
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-9], eax
push rbp
call intToChar
pop rbp
add rsp, 4
sub rsp, 4
mov eax, dword [rax]
mov dword [rbp-9], eax
sub rsp, 4
mov eax, dword [rbp-9]
mov dword [rbp-13], eax
sub rsp, 4
mov eax, 4
mov dword [rbp-17], eax
push rbp
call _print
pop rbp
add rsp, 12
jmp JL8 
JL8:
add rsp, 1
JL6:
mov eax, 1
add dword [rbp-4], eax
jmp JL7 
JL5:
add rsp, 4
mov eax, 60
xor edi, edi
syscall 
ret 

