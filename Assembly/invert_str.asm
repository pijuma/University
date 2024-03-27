	.data
	.align 0 
str: 	.space 30 #string de 30 caracteres
strinv: .space 30
strq: 	.asciz "\n" 
	.align 2 
	
	.text 
	.globl main 

#lb - load - ler 
#sb - store - salvar

main: 

	li a7, 5 
	ecall 
	
	#mv passa o valor de a0 pra t0 
	mv t0, 	a0 #t0 guarda o tamanho da string 
	la t1, str #t1 guarda o 1o byte de str 
	
	li a7, 8 
	la a0, str # str eh um end ent precisa de la 
	add a1, x0, t0 #lendo string de tamanho a1 
	ecall 
	
	add t2, t1, t0 #guarda o ultimo byte de str 
	addi t3, x0, 0 
	la t4, strinv #t4 guarda o 1o byte de strinv 
	addi t2, t2, -2 #eh 0 indexado  
	addi t3, t3, 1 
	
loop_inverte:
	
	 beq t3, t0, fim_inversao 
	 #passar oq ta em t2 pro que ta em t4 
	 #qro pegar oq ta em t2 (um byte) usa lb 
	 lb t5, (t2)
	 #qro passar o conteudo de um byte usa sb 
	 sb t5, (t4)
	 addi t2, t2, -1
	 addi t4, t4, 1
	 addi t3, t3, 1
	 j loop_inverte
	  
fim_inversao:	
	
	add t2, t1, x0 #guarda o ultimo byte de str
	add t2, t2, t0 
	lb t5, (t2)
	sb t5, (t4)
	 
	la t4, strinv #1o byte de strinv
	add t2, x0, t1 #1o byte de str 
	addi t3, x0, 0 

loop_mudar:
	
	beq t3, t0, fim_mudar
	
	lb t5, 0(t4)
	sb t5, 0(t2) 
	addi t2, t2, 1 
	addi t4, t4, 1
	addi t3, t3, 1 
	
	j loop_mudar
	
fim_mudar:
	
	la a0, str 
	#passar direto o valor 4 pra a7 
	li a7, 4
	ecall 
	
	la a0, strq 
	li a7, 4 
	ecall
	
	li a7, 10 
	ecall 
	

	
