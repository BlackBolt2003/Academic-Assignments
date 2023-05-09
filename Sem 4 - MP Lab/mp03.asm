section .data
	msgNum db "Numbers =", 0xA	;msg to display numbers
	msgNumLen equ $-msgNum
	
	msgMax db "Largest Number = ",
	msgMaxLen equ $-msgMax
	
	newLine db 0xA
	newLineLen equ $-newLine
	
	num db 4, 7, 1, 9, 30		;array of 5 byte numbers
	cnt db 5

section .bss
	max: resb 1

	Print:
	%macro print 2
		mov rax, 01
		mov rdi, 01
		mov rsi, %1	;max
		mov rdx, %2	;2
		syscall

	%endmacro
		
	
section .text
global _start

_start:
	print msgMax, msgMaxLen

GreatestNum:
	mov byte[cnt], 5
	;AL = store max number, RDI = iterator for array, NUM = start address of array

	mov al, 0h			;set al as 0 (current max value)
	mov rdi, num;			;point RDI to start of array 
	
	Loop3:
		cmp [rdi], al		;compare value at index with max value
		jbe NoUpdate		;jump to label if max is still larger
	Update:
		mov al, [rdi];		;update max variable by replacing with current index element
	NoUpdate:
		inc rdi;		;increment pointer at array to next element
		dec byte[cnt]		;decrement counter
		jnz Loop3		;repeat 5 times
	

	call HexToAscii

	print max, 2
	print newLine, newLineLen
	
_exit:
	mov rax, 60			;exit system call
	mov rdx, 00
	syscall
	
; ---- SUB-ROUTINES ----

HexToAscii:
	mov byte[cnt], 2           
	mov rdi, max        		 ;pointer at result

	Loop4:
		rol al, 4              ;rotate B by 4 bits to left
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

