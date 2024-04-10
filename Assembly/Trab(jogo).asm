#t0 = numero a ser advinhado
		.data
		.align 0 
		#frases de recepcão
inicial:	.asciz "Bem-vindo ao Jogo advinhe o numero! Seu objetivo e tentar advinhar o numero oculto fazendo chutes.\n"
inicial2:	.asciz "A cada chute sera dado um veredito dizendo se o numero esta muito alto, muito baixo ou se voce esta correto.\n"
inicial3:	.asciz "Bom jogo!\n" 
maior: 		.asciz "O numero que voce digitou e maior do que o valor esperado\n" 
menor:  	.asciz "O numero que voce digitou e menor que o valor esperado\n" 
igual:  	.asciz "Voce acertou o valor\n"
acabou: 	.asciz "Parabens, voce ganhou!"
qtd_chutes:	.asciz "A quantidade de chutes foi de:" 
quebra_l: 	.asciz "\n"
frase_fin:	.asciz "e os chutes foram: \n" 
espaco:		.asciz " " 
		.align 2 
head: 		.space 4 #ponteiro para o inicio da lista -> no cabeca 
 
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
	addi t1, x0, 0 #t1 tem o valor de a -> e temporario para realizar as operacoes (a*xn + c )%m = xn+1
	addi t2, x0, 0 #t2 tem o valor de c 
	addi t3, x0, 100 #t3 tem o valor de m 
 
	add a1, x0, t3 
 
	li a7, 42 
	ecall 
 
	addi t4, zero, 10 #t4 sera o contador de iteracoes
	add t0, a0, x0
 
#funcão para gerar um numero aleatorio utilizando o algoritmo de gerador contruencial linear 
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
 
	li a7, 42 #ecall para gerar numero aleatorio - valor e dado em 42
	ecall 
	add t1, a0, x0
	add t2, a0, x0
	j fim_gerar 
 
 
fim_gen_linear:
 
	addi t0, t0, 1 #para garantir que o numero esta no range [1, 100] 
	addi t1, x0, 0 #t1 ira guardar a quantidade de chutes feitos 
 
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
 
	la t5, head # pego o endereco do head (NAO eh o valor do head que aponta para o primeiro no)
	lw t5,0(t5) # armazeno o valor que ta no head (o endereco do primeiro no)
 
#t1 e contador (que armazenava a quantidade de tentativas) 
#imprime os chutes
#t5 -> no a ser impresso
loop_impressao:
 
	beq t1, x0, fim_impressao #acabou a lista
 
	lw a0, 0(t5) # pega o valor armazenado em t5(endereco do no atual)  
	li a7, 1 
	ecall # printar o valor
 
	li a7, 4
	la a0, espaco 
	ecall 

	lw t5, 4(t5) # mudar o valor de t5 para o novo endereco do proximo no
	addi t1, t1, -1
 
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
	li a0, 8 #nosso no tem 8bytes (numero + end)
	li a7, 9 
	ecall # escreve a nova memoria em a0
	sw a0, 4(t5) # t5 (current) deve apontar para o no criado
	sw t6, 0(a0) # o valor de a0 passa a ser o valor de t6(chute feito)
	sw, x0, 4(a0) # a0 deve apontar para NULL (nao existe proximo item)
	mv t5, a0 # seta t5 como a0  -> passa a ser meu ultimo 
	jr ra 
 
primeiro_no:
 
	li a0, 8 
	li a7, 9 
	ecall # escreve a nova memoria em a0 
	sw t6, 0(a0) # o valor de a0 passa a ser o valor de t6(chute feito)
	sw x0, 4(a0) # a0 deve apontar para NULL (nao existe proximo item)
	sw a0, 0(t5) # t5 (head nesse momento) tera o valor de a0(que armazena o endereco alocado pelo ecall)
	add t5, x0, a0 #o no t5 (current) passa a ser o no adicionado
	jr ra
