section .data
    filename db 'input.txt', 0
    filemode db 'r+', 0
    buffer times 1024 db 0
    temp dw 0
    isSorted db 0
    newline db 10

section .text
    global _start

_start:
    ; Open the input file
    mov rax, 2
    mov rdi, filename
    mov rsi, 2
    xor rdx, rdx
    syscall
    mov r8, rax ; store the file descriptor

    ; Read the integers from the file into an array
    xor rax, rax
    lea rdi, [buffer]
    mov rsi, 1024
    mov rdx, 1
    mov rcx, r8
    call readIntegers

    ; Sort the array using bubble sort
    lea rdi, [buffer]
    mov rsi, 1024
    call bubbleSort

    ; Rewind the file pointer
    mov rax, 8
    mov rdi, r8
    xor rsi, rsi
    syscall

    ; Write the sorted array back to the file
    xor rax, rax
    lea rdi, [buffer]
    mov rsi, 1024
    mov rdx, 1
    mov rcx, r8
    call writeIntegers

    ; Close the file
    mov rax, 3
    mov rdi, r8
    syscall

    ; Exit the program
    xor rax, rax
    mov rdi, 0
    syscall

readIntegers:
    push rbp
    mov rbp, rsp

    xor rax, rax

.read_loop:
    lea rdi, [buffer + rax]
    mov rsi, 1024
    xor rdx, rdx
    mov r10, 0x00ffffff ; maximum value to read as unsigned integer
    syscall
    cmp rax, 0
    je .read_done

    cmp rax, 4
    jne .read_loop

    movzx edx, word [buffer + rax]
    mov [rdi], dx
    add rax, 2
    jmp .read_loop

.read_done:
    pop rbp
    ret

writeIntegers:
    push rbp
    mov rbp, rsp

    xor rax, rax

.write_loop:
    lea rdi, [buffer + rax]
    xor rsi, rsi
    xor rdx, rdx
    mov r10, 0x00ffffff ; maximum value to write as unsigned integer
    syscall

    add rax, 2
    cmp rax, rsi
    jl .write_loop

    pop rbp
    ret

bubbleSort:
    push rbp
    mov rbp, rsp

    xor rax, rax
    mov rsi, 1024
    sub rsi, 2

    .outer_loop:
    xor rbx, rbx
    mov rdi, rsi

    .inner_loop:
    movzx edx, word [rdi]
    movzx ecx, word [rdi + 2]
    cmp edx, ecx
    jbe .not_swap

    mov word [rdi], cx
    mov word [rdi + 2], dx
    mov rbx, 1

    .not_swap:
    sub rdi, 2
    cmp rdi, 0
    jg .inner_loop

    test rbx, rbx
    jnz .outer_loop

    pop rbp
    ret
