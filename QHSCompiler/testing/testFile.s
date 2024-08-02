
section .rodata
wordToGuess: db 'moin', 0xa
wordLength: equ $ - wordToGuess
section .data
section .bss
section .text
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
mov rax, 65
mov [rbp-4], rax
sub rsp, 4
mov rax, [rbp-4]
mov [rsp], rax
mov rax, 1
mov rdi, 1
mov rsi, rsp 
mov rdx, 4
syscall
add rsp, 4
sub rsp, 1
mov rax, 0xa
mov [rsp], rax
mov rax, 1
mov rdi, 1
mov rsi, rsp 
mov rdx, 1
syscall
add rsp, 1
mov rax, 60
mov rdi, 0
syscall 

