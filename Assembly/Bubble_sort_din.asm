		.data
		.align 0 
esp:		.asciz " " 
		.align 2 
		.text
		.globl main 

main: 

		#quantos numeros vou ter? 
		li a7, 5 
		ecall 
		addi s1, a0, 0 #guardar em a1
		addi a1, s1, 0 
		li s5, 4  
		mul t1, a0, s5 #quantos bytes preciso alocar 
		li a7, 9 
		ecall 
		addi s6, a0, 0 #salva em s6 o end inicial 
		addi a2, s6, 0 #end inicial  
		addi t1, a0, 0 #passa end do começo pra t1 
		#preciso ler 
		jal ler_numeros
		addi a0, s6, 0 
		addi a1, s1, 0 
		jal bubble 
		addi a2, s6, 0 
		addi a1, s1, 0
		jal imprimir_numeros
		li a7, 10 
		ecall #encerrar
		
#em a2 temos o endereço inicial 
#em a1 a quantidade que queremos ler 
ler_numeros:
		beq a1, zero, fim_ler
		addi a1, a1, -1 
		
		li a7, 5 #ler numero atual  
		ecall 
		
		sw a0, 0(a2) #escreve na posição 
		
		addi a2, a2, 4 
		
		j ler_numeros 
fim_ler: 
		jr ra 
#a0 -> end inicial 
#a1 -> quantidade 
bubble: 
		li s2, 0 #s1 guarda se ta ordenado -> 0 se estiver  
		addi s3, a1, 0 #quantidade pra percorrer 
		addi s3, s3, -1 #olho pro atual e prox cuidado para nao passar do limite 
		addi s4, a0, 0 #s4 guarda endereço 
		
		ordenar: 
				beq s3, zero, fim_loop
				lw t1, 0(s4)  
				lw t2, 4(s4)
				bge t2, t1, no_swap
				li s2, 1 #nao ordenado
				sw t1, 4(s4) 
				sw t2, 0(s4) 
				no_swap:
				addi s4, s4, 4 	
				addi s3, s3, -1 
				j ordenar 
		fim_loop:		
				beq s2, zero, fim_bubble 
				j bubble #nao ta ordenado ainda 
fim_bubble: 
		jr ra #voltar pro ra de antes de ordenar 

#a2 -> end inicial 
#a1 -> quantidade 
imprimir_numeros: 
		beq a1, zero, fim_imp
		lw a0, 0(a2) 
		li a7, 1 
		ecall 
		li a7, 4 
		la a0, esp
		ecall 
		addi a2, a2, 4 
		addi a1, a1, -1
		j imprimir_numeros
fim_imp: 
		jr ra 
