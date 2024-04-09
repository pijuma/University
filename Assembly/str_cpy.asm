		.data
		.align 0 
str_scr:	.asciz "Hello!" 
str_dst:	.space 7 
		.text
		.align 2 
		.globl main 

main:
		la t0, str_scr #guarda o end do 1o byte de str_scr
		la t1, str_dst #guarda 1o byte de str_dst
		
		lb t2, 0(t0) 
		sb t2, 0(t1) 
		
loop: 		beq t2, zero, fim_loop
		addi t0, t0, 1 #ir pro prox byte 
		addi t1, t1, 1 #ir pro prox byte 
		lb t2, 0(t0) #ler o byte atual
		sb t2, 0(t1) #escrever o byte atual 
		j loop 
fim_loop:
		 
		la a0, str_dst 
		li a7, 4
		ecall 
		
		li a7, 10 
		ecall 		
