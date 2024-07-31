section .text
global intToChar
intToChar:
mov rbp, rsp
mov rsp, rbp
mov eax, dword [rbp+16]
add eax, 48
mov dword [rbp-4], eax
mov rax, rbp
sub rax, 4
ret 
mov rsp, rbp
ret 

