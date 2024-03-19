#lembrar sempre que é sequencial, arquitetura de Von Neumann
	.data #declarar as variaveis/colocar na memoria os valores
	.align 0 #alinha no 2^0 pra colocar string na memoria
str1: 	.asciz "Hello World++!" #"declarando as duas strings que usaremos" 
str2: 	.asciz "Hello World--!"
	.text #começar o código
	.align 2 #colocar pois iremos definir instruções de 32 bits
	.globl main 
	main: 
	
	addi a7, zero, 5 #colocamos no a7 o valor 5 -> valor que define leitura de inteiro, siscall pega no a7 a instrução que deve fzr
	#li a7, 10 -> pode colocar ao inves de addi -> é uma abstração 
	#se usar ela chama a addi por baixo dos panos
	ecall #chama siscall pra ler o valor -> coloca oq leu no a0 
	add s0, a0, zero #passar o valor de a0 pro registrador s0 para não perdermos 
	blt s0, zero, print_neg #compara s0 com zero, se s0 < zero desvia pro layble print_neg 
	addi a7, zero, 4 #carrega o serviço 4 -> imrpmir o valor de a0 ao chamar ecall  
	la a0, str1 #load adress -> carrega o endereço do 1o byte que quer que imprima 
	ecall #imprimindo Hello World++ 
	#se colocar direto o print_neg ele vai passar por ele
	
	j the_end #desvio incondicional para ele ir pro final  
	
	print_neg:
		addi a7, zero, 4 #pra garantir que carregou a operação de impressão no a7 
		la a0, str2
		ecall 
	
	the_end:
	addi a7, zero, 1 #serviço que imprime inteiro 
	add a0, zero, s0 #passa o valor do s0 pro a0 pra poder imprimir o valor 
	ecall #chama siscall pra imprimir o valor que ta no a0 
	
	#li = load imediate -> abstração -> converte em instruções que realmente existem na arquitetura 
	li a7, 10 #coloca o serviço de termino no a7 
	ecall #termina o codigo 
	
