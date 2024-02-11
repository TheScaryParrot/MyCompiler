compareLoop:
    ; Comparison
    mov ah, byte [rbx]
    mov al, byte [rcx]
    cmp ah, al
    jne failed

    ; if the inputBuffer ends here
    cmp byte [rbx], 0xa
    je success

    inc rbx
    inc rcx
    jmp compareLoop