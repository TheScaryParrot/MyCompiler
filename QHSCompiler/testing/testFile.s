section .bss
bssInt: resb 4
section .data
dataInt: dd 69
section .rodata
wordToGuess: db 'moin', 0xa
wordLength: equ $ - wordToGuess
section .text
Hello:
mov rbp, rsp
sub rsp, 4
mov eax, 68
mov dword [rbp-4], eax
sub rsp, 4
mov eax, dword [rbp-4]
mov [rsp], eax
mov rax, 1
mov rdi, 1
mov rsi, rsp
mov rdx, 4
syscall
add rsp, 4
sub rsp, 1
mov al, 0xa
mov [rsp], al
mov rax, 1
mov rdi, 1
mov rsi, rsp
mov rdx, 1
syscall
add rsp, 1
mov rsp, rbp
ret
global _start
_start:
mov rbp, rsp
mov rax, 1
mov rdi, 1
mov rsi, wordToGuess
mov rdx, wordLength
syscall
mov rax, 1
mov rdi, 1
mov rsi, wordToGuess
mov rdx, wordLength
syscall
sub rsp, 4
mov eax, 65
mov dword [rbp-4], eax
sub rsp, 4
mov eax, 66
mov dword [rbp-8], eax
sub rsp, 4
mov eax, dword [rbp-4]
mov [rsp], eax
mov rax, 1
mov rdi, 1
mov rsi, rsp
mov rdx, 4
syscall
add rsp, 4
sub rsp, 1
mov al, 0xa
mov [rsp], al
mov rax, 1
mov rdi, 1
mov rsi, rsp
mov rdx, 1
syscall
add rsp, 1
sub rsp, 4
mov eax, dword [rbp-8]
mov [rsp], eax
mov rax, 1
mov rdi, 1
mov rsi, rsp
mov rdx, 4
syscall
add rsp, 4
sub rsp, 1
mov al, 0xa
mov [rsp], al
mov rax, 1
mov rdi, 1
mov rsi, rsp
mov rdx, 1
syscall
add rsp, 1
mov rax, 1
mov rdi, 1
mov rsi, dataInt
mov rdx, 4
syscall
push rbp
call Hello
pop rbp
mov rax, 60
mov rdi, 0
syscall
