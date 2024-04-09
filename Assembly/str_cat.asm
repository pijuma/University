# ler duas strings uma destino e uma src 
# concatenar as duas em destino 
# fazer tudo dinamico e com função
		.data
		.align 0
str_1:		.asciz "Eai," 
str_2: 		.asciz " Tudo bem?"
		.align 2
ptr_final:	.word #vai apontar pro 1o byte da string final dest+add 

		.text 
		.globl main

main:
		#preciso saber qual tamanho de str1+str2
		#vou percorrer as duas e ir somando guardar o tam em t2
		#t0 end de str1 
		#t1 end de str2 
		la t0, str_1
		la t1, str_2
		addi t3, zero, 1 #o \0 se so tiver ele
		
		lb a2, 0(t0) #em a2 o 1o byte lido 
		la a1, str_1 #em a1 o end do 1byte 
		
		jal somar_str
		
		add t3, a3, t3 
		
		lb a2, 0(t1) 
		la a1, str_2
		#n preciso somar dois \0 - apenas 1 
		jal somar_str
		
		add t3, a3, t3 
		
		#em t3 tenho o tamanho de str1+str2 agora 
		#irei relocar o end do byte inicial de cada uma 
		la t0,  str_1
		la t1, str_2 
		
		add a0, zero, t3 #qro reservra t3 bytes 
		li a7, 9 #alocar dinamica espaço 
		ecall #em a0 tenho o endereço 
		
		 la t3, ptr_final #endereço de ptr_final em t3 para poder dar sw 
		 sw a0, 0(t3) #end de onde irei alocar agr ta em ptr_final cujo end tá em t3 
		 lw t4, 0(t3) #1o byte da nova string 
		 #percorrer str1 e add em 0(t4) dps fazer isso com str2 
		 #nao quero escrever se for \0 
		 
loop_preencher_1: 
		  lb t2, 0(t0) #leio o atual 
		  beq t2, zero, fim_p_1 #n qro escrever \0 
		  sb t2, 0(t4) #escrevo em 0(t4)
		  addi t4, t4, 1 
		  addi t0, t0, 1 #vou pro prox byte nas 2 str 
		  j loop_preencher_1 
		  
fim_p_1: 
		#se for \0 quero escrever 
		lb t2, 0(t1) 
		sb t2, 0(t4) 
		addi t1, t1, 1 
		addi t4, t4, 1 
		
loop_preencher_2: 
		beq t2, zero, fim_p_2 
		lb t2, 0(t1)
		sb t2, 0(t4) 
		addi t1, t1, 1
		addi t4, t4, 1 
		j loop_preencher_2 
fim_p_2:
		
		li a7, 4 #imprimir string
		la t4, ptr_final 
		lw a0, 0(t4) #passa end pra a0 
		ecall 
		
		li a7, 10 
		ecall #terminar codigo
#a2 -> valor lido 
#a1 -> endereço
#retorna em a3 o tamanho
somar_str:	
		addi sp, sp, -4 #guardar apenas o ra 
		sw ra, 0(sp)
		beq a2, zero, fim_soma  
		addi a3, a3, 1 
		addi a1, a1, 1 
		lb a2, 0(a1)
		jal somar_str
fim_soma:
		lw ra, 0(sp)
		addi sp, sp, 4
		jr ra 
