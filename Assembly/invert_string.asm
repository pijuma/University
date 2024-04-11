		.data
		.align 0 
str: 		.space 40
str2:		.space 40
		.align 2
		.text
		.globl main 

 main: 
 		li a7, 8 
 		la a0, str 
 		li a1, 10
 		ecall #ler string
 		
 		la s0, str
 		la s1, str2
 		
 		addi a0, zero, 0 #a0 vai guardando o tamanho
 		jal find_size #s0 terá a ultima posicao (contando com \0) - subtrai 
 		addi s0, s0, -1 
 		mv s5, a0 
 		
 		jal invert 
 		
 		sb zero, 0(s1) # add \0 no final da invertida
 		
 		li a7, 4 
 		la a0, str2 
 		ecall 
 		
 		li a7, 10 
 		ecall  
 		
invert:  
  		beq s5, zero, fim_invert
  		lb s4, 0(s0) #tem o final joga ele p começo em s1 
  		sb s4, 0(s1) 
  		addi s0, s0, -1
  		addi s1, s1, 1
  		addi s5, s5, -1 
  		j invert 
  		
fim_invert:	
		jr ra 
  		
find_size:
		lb s2, 0(s0) 
  		beq  s2, zero, fim_find_sz #se eh \0 sai do loop 
  		addi s0, s0, 1
  		addi a0, a0, 1 
  		j find_size
  		
fim_find_sz: 	
		jr ra 
