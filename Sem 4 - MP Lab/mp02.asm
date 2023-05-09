global _start

section .data
    msgIn db "Enter a string =", 0xA
    lenIn equ $ - msgIn

    msgOut db "Length of string = "
    lenOut equ $- msgOut

    newLine db 0xA
    lenNewLine equ $-newLine

    cnt db 16

section .bss
    str: resb 50
    strlen: resb 50

section .text
_start:
    mov rax, 01             ; call for input
    mov rdi, 01
    mov rsi, msgIn
    mov rdx, lenIn
    syscall

Input:
    mov rax, 00             ; input string
    mov rdi, 00
    mov rsi, str
    mov rdx, 50
    syscall
;-------

    dec al                  ; store actual value of string length
    mov rbx, rax            
    mov rdi, strlen         ; pointer at result

LOOP:
    rol rbx, 4              ; rotate B by 4 bits to left
    mov al, bl  
    and al, 0fh             ; mask at lower byte

    cmp al, 09h
    jbe BELOW_9
    add al, 07h

    BELOW_9:    
    add al, 30h
    mov [rdi], al           ; store hex-ascii value into result

    inc rdi                 ; increment result pointer 
    dec byte[cnt]                 ; decrement counter
    jnz LOOP                ; repeat LOOP till cnt becomes zero (16 times)

;-------

Output:
    mov rax, 01             ; call for output
    mov rdi, 01
    mov rsi, msgOut
    mov rdx, lenOut
    syscall

    mov rax, 01             ; o/p length of string
    mov rdi, 01
    mov rsi, strlen
    mov rdx, 50
    syscall

NewLine:    
    mov rax, 01             ; go to next line
    mov rdi, 01
    mov rsi, newLine
    mov rdx, lenNewLine
    syscall

Exit:
    mov rax, 60
    mov rdx, 00
    syscall