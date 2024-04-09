# pegar duas strings e comparar
		.data
		.align 0 
str:		.asciz "opa eae"
str2:		.asciz "opa eae"
n_eq:		.asciz "diferente"
eq: 		.asciz "igual" 
		.align 2 
		.text 
		.globl main 

main:
		la t0, str 
		la t1, str2 
		
loop:	
		lb t2, 0(t0) 
		lb t3, 0(t1) 
		
		bne t2, t3, nao_igual 
		beq t2, zero, igual
		
		addi t0, t0, 1
		addi t1, t1, 1 
		
		j loop 
		
nao_igual:
		li a7, 4 
		la a0, n_eq 
		ecall 
		j terminou 
		
igual:
		li a7, 4 
		la a0, eq 
		ecall 

terminou:
		li a7, 10 
		ecall 
