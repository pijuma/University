# bubble sort, enquanto n está ordenado 
# tenta trocar adjascente 
# guarda uma variavel pra saber se ta ordenado, se tiver quebra o loop de fora 
# guarda um vetor com os valores 
# indicador se houve troca: t4
# t1 é o contador
# t3 guarda o inicio do vetor
# t2 fala se o vetor ta ou n ordenado 
# pra pegar o valor que ta no end faz: 
# lw t6, 0(t5) dai ele pega o valor que ta no end q t5 guarda a partir do byte 0 
# guarda em t4 e t5 o array[i] e array[i-1] e ve se troca
#size será guardado em t0
#lw -> lê da memoria e coloca no registrador 
#sw -> le do registrador e coloca na memoria 

	.data
	.align 0 
str1: 	.asciz " " 	
str2: 	.asciz "\n"
	.align 2 #colocar o vetor de palavras 
array: 	.word 0: 30 #separa MAXN espaços inicializados com 0 (vetor de word)
	.text
	.globl main

main:
	li a7, 5 # ler o tamanho do vetor 
	ecall 
	
	mv t0, a0 #em t0 temos o size agr
	
	li t1, 0 #contador 
	la t3, array 
	
loop_leitura: 
	
	beq t1, t0, fim_leitura
	li a7, 5 
	ecall 
	addi t4, x0, 4 
	mul t4, t1, t4 
	add t4, t3, t4 
	sw a0, (t4) 
	addi t1, t1, 1 
	
	j loop_leitura
	
fim_leitura: 

ordenacao:  

	li t2, 0 #t2 guarda se o vetor tá ordenado 
	li t1, 1 #recomeçar o loop
	#pega t1 e t1-1
	
	loop_ord:
		
		beq t1, t0, fim_loop_ord
		
		addi t4, x0, 4
		mul t4, t1, t4
		add t4, t3, t4 
		addi t5, t4, -4 
		#comparar t7 e t8 se t7 > t8 tem q trocar
		lw s2, 0(t4) 
		lw s1, 0(t5) 
		
		bge s2, s1, no_swap 
		sw s1, (t4)
		sw s2, (t5) 
		li t2, 1
		
		no_swap:  
		addi t1, t1, 1 
		j loop_ord 
		
	fim_loop_ord:	  
	
	
	beqz t2, ordenado
	
	j ordenacao 
	
ordenado: 

	li t1, 0  
	
loop_impressao: 

	beq t1, t0, fim_impressao  
	addi t4, x0, 4 
	mul t4, t1, t4 
	add t4, t3, t4  
	lw a0, (t4) 
	li a7, 1 
	ecall
	li a7, 4 
	la a0, str1 
	ecall 
	addi t1, t1, 1
	j loop_impressao
	
fim_impressao: 

	li a7, 4 
	la a0, str2 
	ecall 
	li a7, 10 
	ecall 
	
