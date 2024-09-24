section .text
mod:
mov rbp, rsp
sub rsp, 4
mov edx, dword [rbp+16]
mov dword [rbp-4], edx
sub rsp, 4
mov edx, dword [rbp+20]
mov dword [rbp-8], edx
JL2:
mov eax, dword [rbp-4]
cmp eax, dword [rbp-8]
setge al
movzx eax, al
test eax, eax
jz JL1 
mov edx, dword [rbp-8]
sub dword [rbp-4], edx
jmp JL2 
JL1:
mov rsp, rbp
mov edx, dword [rbp-4]
mov dword [rbp-4], edx
mov rax, rbp
sub rax, 4
ret 
add rsp, 8
mov rsp, rbp
ret 
isPrime:
mov rbp, rsp
sub rsp, 1
mov eax, dword [rbp+16]
cmp eax, 1
setle al
movzx eax, al
test eax, eax
jz JL4 
mov dl, 0
mov byte [rbp-1], dl
mov rsp, rbp
mov dl, byte [rbp-1]
mov byte [rbp-1], dl
mov rax, rbp
sub rax, 1
ret 
jmp JL3 
JL4:
sub rsp, 4
mov edx, 2
mov dword [rbp-5], edx
JL7:
mov eax, dword [rbp-5]
mov edx, dword [rbp-5]
mul edx
mov eax, eax
cmp eax, dword [rbp+16]
setle al
movzx eax, al
test eax, eax
jz JL5 
sub rsp, 4
mov edx, dword [rbp-5]
mov dword [rbp-9], edx
sub rsp, 4
mov edx, dword [rbp+16]
mov dword [rbp-13], edx
push rbp
call mod
pop rbp
add rsp, 8
sub rsp, 4
mov edx, dword [rax]
mov dword [rbp-9], edx
mov eax, dword [rbp-9]
cmp eax, 0
sete al
movzx eax, al
test eax, eax
jz JL8 
mov dl, 0
mov byte [rbp-1], dl
mov rsp, rbp
mov dl, byte [rbp-1]
mov byte [rbp-1], dl
mov rax, rbp
sub rax, 1
ret 
jmp JL8 
JL8:
add rsp, 4
JL6:
mov edx, 1
add dword [rbp-5], edx
jmp JL7 
JL5:
add rsp, 4
mov dl, 1
mov byte [rbp-1], dl
mov rsp, rbp
mov dl, byte [rbp-1]
mov byte [rbp-1], dl
mov rax, rbp
sub rax, 1
ret 
JL3:
add rsp, 1
mov rsp, rbp
ret 
extern _print
printDigit:
mov rbp, rsp
mov edx, 48
add dword [rbp+16], edx
sub rsp, 4
mov edx, dword [rbp+16]
mov dword [rbp-4], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-8], edx
push rbp
call _print
pop rbp
add rsp, 8
mov rsp, rbp
ret 
printInt:
mov rbp, rsp
sub rsp, 4
mov edx, 10
mov dword [rbp-4], edx
sub rsp, 4
mov edx, dword [rbp+16]
mov dword [rbp-8], edx
push rbp
call mod
pop rbp
add rsp, 8
sub rsp, 4
mov edx, dword [rax]
mov dword [rbp-4], edx
sub rsp, 4
mov edx, dword [rbp-4]
mov dword [rbp-8], edx
mov eax, dword [rbp+16]
sub eax, dword [rbp-8]
mov eax, eax
xor rdx, rdx
mov ebx, 10
div ebx
mov dword [rbp+16], eax
mov eax, dword [rbp+16]
cmp eax, 0
setg al
movzx eax, al
test eax, eax
jz JL9 
sub rsp, 4
mov edx, dword [rbp+16]
mov dword [rbp-12], edx
push rbp
call printInt
pop rbp
add rsp, 4
jmp JL9 
JL9:
sub rsp, 4
mov edx, dword [rbp-8]
mov dword [rbp-12], edx
push rbp
call printDigit
pop rbp
add rsp, 4
add rsp, 8
mov rsp, rbp
ret 
global _start
_start:
mov rbp, rsp
sub rsp, 4
mov edx, 800000
mov dword [rbp-4], edx
sub rsp, 4
mov edx, 0
mov dword [rbp-8], edx
JL12:
mov eax, dword [rbp-8]
cmp eax, dword [rbp-4]
setl al
movzx eax, al
test eax, eax
jz JL10 
sub rsp, 4
mov edx, dword [rbp-8]
mov dword [rbp-12], edx
push rbp
call isPrime
pop rbp
add rsp, 4
sub rsp, 1
mov dl, byte [rax]
mov byte [rbp-9], dl
mov al, byte [rbp-9]
test [rbp-9], al
jz JL13 
sub rsp, 4
mov edx, dword [rbp-8]
mov dword [rbp-13], edx
push rbp
call printInt
pop rbp
add rsp, 4
sub rsp, 4
mov edx, 10
mov dword [rbp-13], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-17], edx
push rbp
call _print
pop rbp
add rsp, 8
jmp JL13 
JL13:
add rsp, 1
JL11:
mov edx, 1
add dword [rbp-8], edx
jmp JL12 
JL10:
add rsp, 4
add rsp, 4
mov eax, 60
xor edi, edi
syscall 
ret 
section .bss
section .data
section .rodata
