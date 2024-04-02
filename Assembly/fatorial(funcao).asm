#a1 guarda o fatorial 
	.data 
	.align 0 
str1: 	.asciz "entre com o numero"
str2:	.asciz "o fatorial de: " 
str3: 	.asciz " eh "
q_l:	.asciz "\n"
 	
	.text 
	.align 2 
	.globl main 

main: 
	li a7, 4 
	la a0, str1  
	ecall 
	
	li a7, 5 #le o numero  
	ecall 
	
	add s0, a0, x0 #salvar o n em s0 
	
	jal fatorial 
	
	add s1, a0, x0 # passa pra s1 o valor do fatorial 
	
	li a7, 4 
	la a0, str2 
	ecall 
	
	mv a0, s0 #imprimir o n 
	li a7, 1 
	ecall 
	
	li a7, 4 #imprimir o "eh" 
	la a0, str3 
	ecall 
	
	mv a0, s1 #imprimir fat
	li a7, 1 
	ecall 
	
	li a7, 4 
	la a0, q_l 
	ecall 
	
	li a7, 10 
	ecall 
	
#em a0 esta o n 
#a0 retorna fatorial 
fatorial: 
	
	add a1, a0, x0 #a2 é o contador 
	addi a0, x0, 1 # a0 guarda o fatorial 
	
	loop: 
		
		beq a1, x0, fim_loop
		
		mul a0, a0, a1 
		addi a1, a1, -1 
		
		j loop 
		
	fim_loop: 
	
	jr ra
