section .text
global mod
mod:
mov rbp, rsp
JL2:
mov eax, dword [rbp+16]
cmp eax, dword [rbp+20]
setge al
movzx eax, al
test eax, eax
jz JL1 
mov eax, dword [rbp+20]
sub dword [rbp+16], eax
jmp JL2 
JL1:
mov rsp, rbp
mov eax, dword [rbp+16]
mov dword [rbp-4], eax
mov rax, rbp
sub rax, 4
ret 
mov rsp, rbp
ret 

