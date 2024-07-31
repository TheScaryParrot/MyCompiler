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
mov eax, dword [rbp+16]
cmp eax, dword [rbp+20]
sete al
movzx eax, al
test eax, eax
jz JL1 
mov rsp, rbp
mov eax, 65
mov dword [rbp-4], eax
mov rax, rbp
sub rax, 4
ret 
jmp JL1 
JL1:
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
extern mod
sub rsp, 4
mov eax, 66
mov dword [rbp-4], eax
sub rsp, 4
mov eax, 2
mov dword [rbp-8], eax
sub rsp, 9
mov eax, 2
mov dword [rbp-17], eax
mov al, byte [bool1]
mov byte [rbp-21], al
mov eax, __float32__(2.000000)
mov dword [rbp-22], eax
sub rsp, 9
mov eax, dword [rbp-17]
mov dword [rbp-26], eax
mov al, byte [rbp-21]
mov byte [rbp-30], al
mov eax, dword [rbp-22]
mov dword [rbp-31], eax
mov eax, dword [rbp-8]
cmp eax, dword [rbp-4]
sete al
movzx eax, al
test eax, eax
jz JL3 
mov rsp, rbp
mov eax, 1
mov dword [rbp-4], eax
mov rax, rbp
sub rax, 4
ret 
jmp JL2 
JL3:
mov eax, dword [rbp-8]
cmp eax, dword [rbp-4]
setl al
movzx eax, al
test eax, eax
jz JL4 
sub rsp, 4
mov eax, 65
mov dword [rbp-30], eax
sub rsp, 4
mov eax, 4
mov dword [rbp-34], eax
push rbp
call _print
pop rbp
add rsp, 8
jmp JL2 
JL4:
sub rsp, 4
mov eax, 66
mov dword [rbp-30], eax
sub rsp, 4
mov eax, 4
mov dword [rbp-34], eax
push rbp
call _print
pop rbp
add rsp, 8
JL2:
sub rsp, 4
mov eax, 10
mov dword [rbp-30], eax
JL6:
mov eax, dword [rbp-30]
cmp eax, 0
setg al
movzx eax, al
test eax, eax
jz JL5 
mov eax, 1
sub dword [rbp-30], eax
jmp JL6 
JL5:
sub rsp, 4
mov eax, __float32__(3.000000)
mov dword [rbp-34], eax
sub rsp, 4
mov eax, 0
mov dword [rbp-38], eax
JL9:
mov eax, dword [rbp-38]
cmp eax, 10
setl al
movzx eax, al
test eax, eax
jz JL7 
mov eax, __float32__(1.000000)
add dword [rbp-34], eax
JL8:
mov eax, 2
add dword [rbp-38], eax
jmp JL9 
JL7:
add rsp, 4
sub rsp, 4
mov eax, dword [rbp-31]
mov dword [rbp-38], eax
sub rsp, 4
mov eax, 1000
mov dword [rbp-42], eax
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-46], eax
push rbp
call mod
pop rbp
add rsp, 8
sub rsp, 4
mov eax, dword [rax]
mov dword [rbp-42], eax
mov eax, dword [rbp-42]
mov dword [rbp-4], eax
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-46], eax
sub rsp, 4
mov eax, 4
mov dword [rbp-50], eax
push rbp
call _print
pop rbp
add rsp, 8
sub rsp, 4
mov eax, 2
mov dword [rbp-46], eax
sub rsp, 4
mov eax, 2
mov dword [rbp-50], eax
push rbp
call Hello2
pop rbp
add rsp, 8
sub rsp, 4
mov eax, dword [rax]
mov dword [rbp-46], eax
sub rsp, 4
mov eax, dword [rbp-46]
mov dword [rbp-50], eax
sub rsp, 4
mov eax, 4
mov dword [rbp-54], eax
push rbp
call _print
pop rbp
add rsp, 12
add rsp, 42
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

