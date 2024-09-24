section .text
sub rsp, 4
    sub rsp, 4
    mod:
    mov rbp, rsp
    sub rsp, 4
    mov eax, dword [rbp+16]
    mov dword [rbp-4], eax
            sub rsp, 4
    mov eax, dword [rbp+20]
    mov dword [rbp-8], eax
            JL1:
    mov eax, dword [rbp-4]
    cmp eax, dword [rbp-8]
        setge dl
        xor rax, rax
        mov al, dl
        test eax, eax
        jz JL2
        mov eax, dword [rbp-8]
    sub dword [rbp-4], eax
        jmp JL1
        JL2:
        xor rax, rax
        mov eax, dword [rbp-4]
    mov rsp, rbp
            ret
            sub rsp, 4
    isPrime:
    mov rbp, rsp
    sub rsp, 1
    mov al, 0
    mov byte [rbp-1], al
            mov eax, dword [rbp+16]
    cmp eax, 1
        setle dl
        xor rax, rax
        mov al, dl
        test eax, eax
        jz JL3
        mov al, 0
    mov byte [rbp-1], al
        xor rax, rax
        mov al, byte [rbp-1]
    mov rsp, rbp
            ret
            JL3:
        test eax, eax
    jnz JL4
    sub rsp, 4
    mov eax, 2
    mov dword [rbp-5], eax
            JL5:
    mov eax, dword [rbp-5]
    mov edx, dword [rbp-5]
        mul edx
        cmp eax, dword [rbp+16]
        setle dl
        xor rax, rax
        mov al, dl
        test eax, eax
        jz JL6
        sub rsp, 8
    mov eax, dword [rbp+16]
    mov dword [rbp-13], eax
    mov eax, dword [rbp-5]
    mov dword [rbp-9], eax
    push rbp
    call mod
    pop rbp
    add rsp, 8
    
mov eax, eax
    cmp eax, 0
        sete dl
        xor rax, rax
        mov al, dl
        test eax, eax
        jz JL7
        mov al, 0
    mov byte [rbp-1], al
        xor rax, rax
        mov al, byte [rbp-1]
    mov rsp, rbp
            ret
            JL7:
        mov eax, 1
    add dword [rbp-5], eax
        jmp JL5
        JL6:
        mov al, 1
    mov byte [rbp-1], al
        xor rax, rax
        mov al, byte [rbp-1]
    mov rsp, rbp
            ret
            JL4:
        xor rax, rax
        mov al, byte [rbp-1]
    mov rsp, rbp
            ret
            sub rsp, 4
    printDigit:
    mov rbp, rsp
    mov eax, 48
    add dword [rbp+16], eax
        sub rsp, 4
    mov eax, dword [rbp+16]
    mov [rsp], eax
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 4
    syscall
    
    add rsp, 4
    
mov rsp, rbp
        ret
        sub rsp, 4
    printInt:
    mov rbp, rsp
    sub rsp, 8
    mov eax, dword [rbp+16]
    mov dword [rbp-8], eax
    mov eax, 10
    mov dword [rbp-4], eax
    push rbp
    call mod
    pop rbp
    add rsp, 8
    
sub rsp, 4
    mov eax, eax
    mov dword [rbp-4], eax
            mov eax, dword [rbp-4]
    sub dword [rbp+16], eax
        mov eax, 10
    mov ebx, eax
        xor rdx, rdx
        mov eax, dword [rbp+16]
        div ebx
        mov dword [rbp+16], eax
        mov eax, dword [rbp+16]
    cmp eax, 0
        setg dl
        xor rax, rax
        mov al, dl
        test eax, eax
        jz JL8
        sub rsp, 4
    mov eax, dword [rbp+16]
    mov dword [rbp-8], eax
    push rbp
    call printInt
    pop rbp
    add rsp, 4
    
JL8:
        sub rsp, 4
    mov eax, dword [rbp-4]
    mov dword [rbp-8], eax
    push rbp
    call printDigit
    pop rbp
    add rsp, 4
    
mov rsp, rbp
        ret
        
    global _start
    _start:
    mov rbp, rsp
    sub rsp, 4
    mov eax, 800000
    mov dword [rbp-4], eax
            sub rsp, 4
    mov eax, 0
    mov dword [rbp-8], eax
            JL9:
    mov eax, dword [rbp-8]
    cmp eax, dword [rbp-4]
        setl dl
        xor rax, rax
        mov al, dl
        test eax, eax
        jz JL10
        sub rsp, 4
    mov eax, dword [rbp-8]
    mov dword [rbp-12], eax
    push rbp
    call isPrime
    pop rbp
    add rsp, 4
    
mov al, al
    test al, al
        jz JL11
        sub rsp, 4
    mov eax, dword [rbp-8]
    mov dword [rbp-12], eax
    push rbp
    call printInt
    pop rbp
    add rsp, 4
    
sub rsp, 4
    mov eax, 10
    mov [rsp], eax
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 4
    syscall
    
    add rsp, 4
    
JL11:
        mov eax, 1
    add dword [rbp-8], eax
        jmp JL9
        JL10:
        mov rax, 60
    mov rdi, 0
    syscall
    
