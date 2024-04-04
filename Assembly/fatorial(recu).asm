	.data
	.align 0 
str1:	.asciz "digite um valor" 
strq:	.asciz "\n"
	.align 2 
	.text
	.globl main 

main: 

	li a7, 4
	la a0, str1 
	ecall 
	
	li a7, 5 
	ecall 
	add s0, a0, x0 #salvar o n 
	
	jal fatorial #chamar a função recursiva 
	
	add a0, a1, x0 
	li a7, 1 
	ecall 
	
	li a7, 10 
	ecall

#a0 = parametro 
# a1 saida
fatorial: #convenção de empilhar no começo sempre mesmo que va para um caso base 
 	 
 	 addi sp, sp, -8 #salvar os valores (ra e 
 	 sw  ra, 0(sp) # salva o ra 
 	 sw a0, 4(sp) #salva o a0   
 	 
 	 beq a0, x0, retorna_1 #testa condição de parada
 	 
 	 addi a0, a0, -1 #decrementa 
 	 jal fatorial #recursao
 	 lw a0, 4(sp) #recupera valor anterior de a0 
 	 mul a1, a1, a0 # multiplica com o valor caclulado com fat(n-1) 
 	 
 	 j sai_fat

retorna_1:

 	  addi a1, x0, 1 

sai_fat: #executa uma vez a mais que o resto antes do j  sai_fat - tomar cuidado 
 
	 lw  ra, 0(sp) #puxa o ra de volta
 	 addi sp, sp, 8 #libera espaço 

 	 jr ra #volta na recursão 
