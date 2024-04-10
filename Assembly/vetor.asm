#dado dois vetores a e b -> serão colocado em registradores
#fazer uma função que retorne c como um novo vetor resultado de c = k*a + b
#c estará nos registradores a0, a1, a2 
#a função irá receber os vetores em t0, t1, t2 e t3, t4, t5  e inteiro k em t6 respectivamente 
		.data
		.align 2
		.text
		.globl main 
main: 
		li a7, 5 #ler inteiro 
		#salvando todos os vetores nos regs 
		ecall 
		addi t0, a0, 0 
		ecall 
		addi t1, a0, 0 
		ecall 
		addi t2, a0, 0 
		ecall 
		addi t3, a0, 0 
		ecall 
		addi t4, a0, 0 
		ecall 
		addi t5, a0, 0 
		ecall 
		addi t6, a0, 0 
		
		jal calc #calcular c -> retorno em a0, a1, a2
		
		li a7, 1 
		ecall 
		add a0, a1, x0 
		ecall 
		add a0, a2, x0 
		ecall 
		
		li a7, 10 #encerrar 
		ecall 

calc:
	
	mul a0, t6, t0 
	mul a1, t6, t1
	mul a2, t6, t2 
	add a0, a0, t3
	add a1, a1, t4
	add a2, a2, t5
	jr ra #voltar
