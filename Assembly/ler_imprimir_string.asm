		.data
		.align 0 
str: 		.space 100
		
		.text 
		.align 2 
		.globl main 

main: 
		la a0, str #local que vai ser guardado a string 
		li a7, 8 
		li a1, 100 #tamanho max a ser lido
		ecall 
		
		li a7, 4 
		la a0, str 
		ecall 
		
		li a7, 10 
		ecall 
		
