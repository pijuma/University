all: item.o avl.o set.o main.o
	gcc item.o avl.o set.o main.c -o main -std=c99 -Wall -lm

set.o: 
	gcc -c set.c -o set.o
avl.o:
	gcc -c avl.c -o avl.o
	
item.o:
	gcc -c item.c -o item.o

run:
	valgrind --leak-check=full ./main
clean:
	rm avl.o
	rm item.o
	rm set.o
	rm main

# -s para nao aparecer comenntarios chatos
# @ pra nao aparecer comandos
tudo: 
	make -s clean  
	make -s
	make -s run 
