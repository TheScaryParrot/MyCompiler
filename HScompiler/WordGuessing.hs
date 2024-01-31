global _start

section .text

_start:
    push -1

guess:
    ; Get input
    mov rax, 0
    mov rdi, 0
    mov rsi, inputBuffer
    mov rdx, inputBufferLength
    syscall

    lea rbx, inputBuffer ; first string memory address
    lea rcx, wordToGuess ; second string memory address

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

success:
    print successText successTextLength
    jmp end

failed:
    ;   increment first stack element
    pop rcx
    inc rcx

    ; jump if all letters have been given
    cmp rcx, wordLength - 1
    je allLettersGiven

    push rcx

    print failedText failedTextLength

    ; write next letter of wordToGuess
    pop rcx
    push rcx

    mov rax, 1
    mov rdi, 1
    mov rsi, wordToGuess
    add rsi, rcx
    mov rdx, 1
    syscall

    ; write \n
    print newLine newLineLength

    jmp guess

allLettersGiven:
    print allLettersGivenText allLettersGivenTextLength

end:
    mov rax, 60       ; exit(
    mov rdi, 0        ;   EXIT_SUCCESS
    syscall           ; );

section .rodata
    wordToGuess: db "moinsen", 0xa
    wordLength: equ $ - wordToGuess

    guessText: db "Guess the word: "
    guessTextLength: equ $-guessText

    failedText: db "Failed! The next letter is: "
    failedTextLength: equ $ - failedText

    successText: db "Success!", 0xa
    successTextLength: equ $ - successText

    allLettersGivenText: db "All Letters have been given. You are stupid!", 0xa
    allLettersGivenTextLength: equ $-allLettersGivenText

    newLine: db 0xa
    newLineLength: equ $-newLine

section .bss
    inputBufferLength: equ 24
    inputBuffer: resb inputBufferLength