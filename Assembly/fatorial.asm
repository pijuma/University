	.data
	.align 0 #colocar string na memoria 
str1: 	.asciz "Me dê um Valor 'n' para ser retornado n!"
str2: 	.asciz "O fatorial é: " 
	.text #inicio codigo 
	.align 2 
	.globl main

main:
	addi a7, zero, 4 #colocar em a7 pra imprimir string
	la a0, str1 #passar a palavra a ser impressa 
	ecall 
	
	addi a7, zero, 5 #quero ler um inteiro 
	ecall
	 
	add s0, a0, zero #passar o valor de a0 pra s0 pra guardar 
	addi s1, zero, 1 #em s1 guardarei o fatorial, que começa com 0 

loop: 
	ble s0, zero, fim_loop #se s0 <= 0 sai do loop 
	mul s2, s1, s0 #coloca o novo fatorial em s2 (posso colocar direto em s1?) 
	addi s0, s0, -1 #subtraio 1 do s0 (variavel n) 
	add s1, zero, s2 #passo o novo valor da mult pra s1 
	j loop #volta pro começo do loop 
fim_loop:
	 
	 li a7, 4 
	 la a0, str2 
	 ecall #imprimir a string 2 "O fatorial eh:" 
	 
	 addi a7, zero 1 #carregar pra imprimir inteiro
	 add a0, zero, s1 #passar o valor do fartorial pra a0 p ser impresso 
	 ecall 
	 
	 li a7, 10
	 ecall
	 #encerrar codigo 
	 
