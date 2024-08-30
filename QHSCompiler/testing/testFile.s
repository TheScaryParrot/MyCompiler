section .bss
bssInt: resb 4
section .data
dataInt: dd 69
section .rodata
wordToGuess: db 'moin', 0xa
wordLength: equ $ - wordToGuess
sub rsp, 4
section .text
PrintLine:
mov rbp, rsp
sub rsp, 4
mov eax, dword [rbp+16]
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
sub rsp, 4
sub rsp, 1
sub rsp, 4
Hello:
mov rbp, rsp
sub rsp, 4
mov eax, dword [rbp+21]
mov eax, eax
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
sub rsp, 4
sub rsp, 4
Hello2:
mov rbp, rsp
sub rsp, 4
mov eax, dword [rbp+16]
mov eax, eax
mov dword [rbp-4], eax
sub rsp, 4
mov eax, dword [rbp+20]
mov eax, eax
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
add eax, dataInt
sub eax, dataInt
mov eax, eax
mov dword [rbp-4], eax
sub rsp, 4
mov eax, 66
mov eax, eax
mov dword [rbp-8], eax
sub rsp, 4
mov eax, dword [rbp-4]
mov dword [rbp-12], eax
push rbp
call PrintLine
pop rbp
add rsp, 4
mov eax, 67
add eax, 4
mov eax, eax
mov dword [rbp-8], eax
mov eax, 6
add dword [rbp-8], eax
mov eax, 6
add eax, 1
sub dword [rbp-8], eax
mov eax, 35
sub dword [rbp-8], eax
mov eax, 2
mov edx, eax
mov eax, dword [rbp-8]
mul edx
mov dword [rbp-8], eax
mov eax, 1
mov edx, 5
mul edx
sub eax, 4
add dword [rbp-8], eax
sub rsp, 4
mov eax, dword [rbp-8]
mov dword [rbp-12], eax
push rbp
call PrintLine
pop rbp
add rsp, 4
mov eax, dword [rbp-8]
add eax, 5
mov edx, dword [rbp-8]
mul edx
sub eax, 3
mov rax, 1
mov rdi, 1
mov rsi, dataInt
mov rdx, 4
syscall
sub rsp, 9
mov eax, dword [rbp-8]
mov dword [rbp-17], eax
mov al, 1
mov byte [rbp-13], al
mov eax, 69
mov dword [rbp-12], eax
push rbp
call Hello
pop rbp
add rsp, 9
sub rsp, 8
mov eax, dword [rbp-4]
mov dword [rbp-16], eax
mov eax, dword [rbp-8]
mov dword [rbp-12], eax
push rbp
call Hello2
pop rbp
add rsp, 8
mov rax, 60
mov rdi, 0
syscall
