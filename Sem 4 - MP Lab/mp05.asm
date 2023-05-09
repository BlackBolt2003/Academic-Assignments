%macro print 2
	mov rax, 01
	mov rdi, 01
	mov rsi, %1	;result
	mov rdx, %2	;bytes to read
	syscall
%endmacro

section .data
	newLine db 0xA
	newLineLen equ $-newLine
	
	msgPos db "Positive Numbers = "
	msgPosLen equ $-msgPos
	
	msgNeg db "Negative Numbers = "
	msgNegLen equ $-msgNeg
	
	num dq 0xFFFF000011110000, 0xFFFF000011110000, 0x0FFF000011110000, 0xFFFF0000111A0000, 0x3FFF000011110000
	
	cnt db 5
	
	pos: db 0
	neg: db 0

section .bss
	result: resb 1
	
	
section .text
global _start

_start:
	
	call CountSign
	
_exit:
	mov rax, 60			;exit system call
	mov rdx, 00
	syscall
	
; ---- SUB-ROUTINES ----

HexToAscii:
	mov byte[cnt], 2           
	mov rdi, result        	 ;pointer at result

	Loop4:
		rol al, 4               ;rotate B by 4 bits to left
		mov bl, al  
		and bl, 0fh             ;mask at lower byte

		cmp bl, 09h
		jbe BELOW_9
		add bl, 07h

	BELOW_9:    
		add bl, 30h
		mov [rdi], bl           ;store hex-ascii value into result

		inc rdi                 ;increment result pointer 
		dec byte[cnt]           ;decrement counter
		jnz Loop4               ;repeat LOOP till cnt becomes zero (16 times)
	ret
	
CountSign:  	
	mov r8, num			;iterator set at base address
	
	Loop:
		mov rax, qword[r8]

		;bt rax, 63h		;check MSB for sign bit
		rol rax, 01h		;rotate left to get MSB into CF
		jnc POSITIVE
			add byte[neg], 01h
			jmp j1
		
		POSITIVE:
			add byte[pos], 01h
			
		j1: 	add r8, 08h	
			dec byte[cnt]
			jnz Loop
		
	print msgPos, msgPosLen
	mov al, byte[pos]
	call HexToAscii
	print result, 2
	print newLine, newLineLen
	
	print msgNeg, msgNegLen
	mov al, byte[neg]
	call HexToAscii
	print result, 2
	print newLine, newLineLen
	
	ret
