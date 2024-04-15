		.data
		.align 2 
		.text 
		.globl main 

main: 
		li a7, 5 
		ecall 
		add a1, a0, zero #passar o n para a1
		jal fat # calcular fatorial
		
		li a7, 1 
		ecall
		
		li a7, 10 
		ecall 
		
#funcao que calcula fatorial 
#em a0 teremos o valor do fatorial 
#em a1 teremos o valor p multiplicar agr
 fat:
 		#empilha -> 0() = ra 4() = a1 -> p multiplicar dps 
 		addi sp, sp, -8 
 		sw ra, 0(sp)
 		sw a1, 4(sp) 
 		beq a1, zero, retorna_1
 		addi a1, a1, -1
 		jal fat #chama recursao 
 		lw a1, 4(sp) #recupera o valor
 		mul a0, a0, a1 
 		
 		jal desempilha
#retornar 1 
retorna_1:
  		addi a0, zero, 1 
#soma e coloca valores de volta
desempilha:
 		lw ra, 0(sp) 
 		addi sp, sp, 8
 		jr ra 
 		 
