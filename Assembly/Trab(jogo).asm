#t0 = numero a ser advinhado
		.data
		.align 0 
		#frases de recepção
inicial:	.asciz "Bem-vindo ao Jogo advinhe o número! Seu objetivo é tentar advinhar o número oculto fazendo chutes.\n"
inicial2:	.asciz "A cada chute será dado um veredito dizendo se o número está muito alto, muito baixo ou se você está correto.\n"
inicial3:	.asciz "Bom jogo!\n" 
maior: 		.asciz "O número que você digitou é maior do que o valor esperado\n" 
menor:  	.asciz "O número que você digitou é menor que o valor esperado\n" 
igual:  	.asciz "Você acertou o valor\n"
acabou: 	.asciz "Parabéns, você ganhou!"
qtd_chutes:	.asciz "A quantidade de chutes foi de:" 
quebra_l: 	.asciz "\n"
frase_fin:	.asciz "e os chutes foram: \n" 
espaco:		.asciz " " 
		.align 2 
head: 		.space 4 #ponteiro para o inicio da lista -> no cabeça 
		
		.text
		.globl main 
		
main: 

	la t5, head #passar o end do head pro t5 temporariamente  
	sw zero, 0(t5) #inicializando o head como null (lista vazia)
	
	li a7, 4 
	la a0, inicial 
	ecall 
	la a0, inicial2
	ecall 
	la a0, inicial3
	ecall
	
	addi t0, x0, 0 #em t0 temos xn -> valor a ser advinhado
	addi t1, x0, 0 #t1 tem o valor de a -> e temporario para realizar as operações (a*xn + c )%m = xn+1
	addi t2, x0, 0 #t2 tem o valor de c 
	addi t3, x0, 100 #t3 tem o valor de m 
	
	add a1, x0, t3 
	
	li a7, 42 
	ecall 

	addi t4, zero, 10 #t4 será o contador de iterações
	add t0, a0, x0

#função para gerar um número aleatório utilizando o algoritmo de gerador contruencial linear 
gen_linear: 
		
	beq t4, zero, fim_gen_linear
	j gerar_aleatorio #queremos gerar 2 numeros aleatorios (a e c)
	fim_gerar:
		mul t1, t1, t0 # a = a*xn 
		add t1, t1, t2 # a = a + c 
		rem t1, t1, t3 # a = a%m
		add t0, t1, x0 # xn+1 = a 
		addi t4, t4, -1 #decremento do loop 
		j gen_linear

gerar_aleatorio: 
	
	li a7, 42 #ecall para gerar numero aleatorio - valor é dado em 42
	ecall 
	add t1, a0, x0
	add t2, a0, x0
	j fim_gerar 
	
	
fim_gen_linear:
	
	addi t0, t0, 1 #para garantir que o numero está no range [1, 100] 
	addi t1, x0, 0 #t1 irá guardar a quantidade de chutes feitos 
	
loop_jogo: 
	
	li a7, 5 
	ecall 
	add t6, x0, a0 #t6 guarda temporariamente o chute feito
	jal add_node 
	addi t1, t1, 1 
	blt t6, t0, less 
	bgt t6, t0, greater
	beq t6, t0, equal

fim_jogo:
	
	la a0, acabou 
	li a7, 4 
	ecall 
	
	li a7, 4 
	la a0, qtd_chutes
	ecall 
	add a0, x0, t1 
	li a7, 1 
	ecall 
	li a7, 4 
	la a0, quebra_l
	ecall 
	la a0, frase_fin 
	ecall 
	
	add t4, x0, t1 #t1 guarda a qtd de chutes 
	la t5, head 
	lw t5, 0(t5) #guarda end do 1o no em t5, ele ira guardar o end do nó a ser impresso

#t4 é contador 
#imprime os chutes
#t5 -> nó a ser impresso
loop_impressao:

	beq t4, x0, fim_impressao #acabou a lista
	
	lw a0, 0(t5) #guarda o valor que ta no end 0(t5)  
	
	li a7, 1 
	ecall 
	
	li a7, 4
	la a0, espaco 
	ecall 
	
	#t4 = t4->prox
	lw t5, 4(t5)
	addi t4, t4, -1
	
	j loop_impressao
	
fim_impressao:
	
	li a7, 4 
	la a0, quebra_l 
	ecall 
	
	li a7, 4
	li a7, 10 
	ecall

less:
	la a0, menor 
	li a7, 4
	ecall 
	j loop_jogo
	
greater: 
	la a0, maior 
	li a7, 4
	ecall
	j loop_jogo

equal:
	la a0, igual
	li a7, 4 
	ecall
	j fim_jogo


add_node:
	
	beq t1, x0, primeiro_no
	li a0, 8 #nosso nó tem 8bytes (numero + end)
	li a7, 9 
	ecall 
	sw a0, 4(t5) #fala que os 4 bytes finais do nó anterior apontam pro nó atual 
	sw t6, 0(a0) #os 1os 4o bytes do atual guardam o novo chute
	sw, x0, 4(a0) #aponta pra null 
	mv t5, a0 #seta t5 como a0  -> passa a ser meu ultimo 
	jr ra 

primeiro_no:
	
	li a0, 8 
	li a7, 9 
	ecall #em a0 teremos um endereço onde será o nosso novo nó 
	sw t6, 0(a0) #coloca o valor de t6 (chute feito) no começo de a0 
	sw a0, 0(t5) #fala que o head guarda a0, 1o nó 
	sw x0, 4(a0) #o 1o nó aponta pra null 
	add t5, x0, a0 #meu end do ultimo nó passa a ser a0 
	jr ra
	
