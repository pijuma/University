	.data 
	.align 0 #colocar string
str1: 	.asciz " " 
str2: 	.asciz "\n" 
	.align 2 
array: 	.word 0: 30 # .word (numero) 0 (inicializacao td com 0) 30 tamanho max
	
	 .text
	 .globl main  

main:
	#ler o n - guarda no t0 
	li a7, 5 
	ecall 
	add t0, a0, x0 
	
	li t1, 0 # t1 vai ser o contador 
	la t2, array #t2 guarda o 1o byte do end de array 
	add t4, x0, t2 # t4 guarda o final 
	
loop_leitura: 
	
	beq t1, t0, fim_leitura
	li a7, 5 
	ecall #ler o inteiro atual 
	sw a0, 0(t4) 
	addi t1, t1, 1 
	addi t4, t4, 4 
	j loop_leitura
	
fim_leitura:
	
	li, t1, 0 
	add t4, x0, t2 # t4 guarda o final 
	li t5, 0 #vai guardar a soma 
	
loop_soma: 
	
	beq t1, t0, fim_soma 
	lw t6, 0(t4) #precisa 1o passar pra um reg p dps somar
	add t5, t5, t6
	addi t4, t4, 4 
	addi t1, t1, 1 
	j loop_soma 
	
fim_soma: 
	
	li a7, 1 
	add a0, t5, x0  
	ecall 
	
	li a7, 4 
	la a0, str2
	ecall 
	
	li a7, 10
	ecall  	
