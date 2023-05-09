%macro scall 4
        mov rax,%1
        mov rdi,%2
        mov rsi,%3
        mov rdx,%4
        syscall
%endmacro

section .data
        menu db 0xA, 0xD, "----MENU----"
             db 0xA, "1. Hex to BCD"
             db 0xA, "2. BCD to Hex"
             db 0xA, "3. Exit"
             db 0xA, "Enter your choice: "
        menulen equ $-menu
        
        m1 db 0xA, 0xD, "Enter Hex Number: "
        l1 equ $-m1
        
        m2 db 0xA, 0xD, "Enter BCD Number: "
        l2 equ $-m2
        
        m3 db 0xA, 0xD, "Equivalent BCD Number: "
        l3 equ $-m3
        
        m4 db 0xA, 0xD, "Equivalent Hex Number: "
        l4 equ $-m4
        
section .bss
        choice resb 1
        num resb 16
        answer resb 16
        factor resb 16
        cnt resb 1
        
section .text
        global _start
_start:
        
        scall 1,1,menu,menulen
        scall 0,0,choice,2
        
        cmp byte[choice],'3'
        jae exit
        
        cmp byte[choice],'1'
        je hex2bcd
        
        cmp byte[choice],'2'
        je bcd2hex
        
;**********Hex to BCD Conversion*************************      
hex2bcd:
		scall 1,1,m1,l1
		scall 0,0,num,17
		call asciihextohex
		
		mov rax, rbx		;HEX number into RAX
		mov rbx, 10		;Division Factor
		mov rdi, num+15	;Pointer to digits starting from LSB
	loop3:
		mov rdx, 0
		div rbx		;Divide by factor
		add dl, 30h		;Convert remainder to Ascii by (BCD + 48)
		mov [rdi], dl		;Replace current digit by Ascii equivalent
		
		dec rdi		;Next digit
		cmp rax,0		;Check if number is exhausted
		jne loop3
			     
		scall 1,1,m3,l3
		scall 1,1,num,16          
	jmp _start
   

;**********BCD to Hex Conversion*************************
bcd2hex:        
		scall 1,1,m2,l2
		scall 0,0,num,17  
		        
		mov byte[cnt], 16	;counter for digits
		mov rsi, num+15	;pointer at digits starting from LSB
		mov rbx, 0		;store final HEX answer
		mov qword[factor], 1	;multiplying factor
		
	loop4:
		mov rax, 0	
		mov al, [rsi]		;get current digit in AL
		sub al, 30h		;convert to BCD by (ASCII - 48)
		
		mul qword[factor]	;multiply current digit by factor
		add rbx, rax		;add term to final ans
		
		mov rax, 10		;update factor
		mul qword[factor]
		mov qword[factor], rax
		
		dec rsi		;next digit
		dec byte[cnt]		
		jnz loop4

		scall 1,1,m4,l4	;"Equivalent Hex Number: "
		mov rax, rbx		;store ans in RAX
		call display           ;ASCII o/p
	jmp _start     
   
exit:   
        mov rax,60
        mov rdx,0
        syscall
        
        
;*********************PROCEDURES*************************
	
asciihextohex:
		mov rsi, num		;iterator to num
		mov byte[cnt], 16
		mov rbx, 0
		mov rax, 0
			
	loop1:	rol rbx, 04
		mov al, [rsi]		;get curr digit
		cmp al, 39h
		jbe skip1
		sub al, 07h
	skip1:	sub al, 30h
		
		add rbx, rax
		
		inc rsi
		dec byte[cnt]
		jnz loop1	
	ret	

display:
		mov rsi, answer+15
		mov byte[cnt], 16

	loop2:	mov rdx, 0
		mov rbx, 16
		div rbx
		cmp dl, 09h
		jbe skip2
		
		add dl, 07h
	skip2:	add dl, 30h
		mov [rsi], dl
		
		dec rsi
		dec byte[cnt]
		jnz loop2
		scall 1,1,answer,16       
	ret

;Note = Input format is 16-bit number
;Example = 4660 -> 0000 0000 0000 4660
