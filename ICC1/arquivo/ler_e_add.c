// le a mensagem colocada pos ./nome 
// ex: ./nome a.txt 
// passa uma msg pra esse arquivo a.txt 
#include<stdio.h>
#include<stdlib.h> 

int main(int argc, char *argv[]){

    FILE *fp ; // ponteiro pro file 
    char c ; 

    if(argc != 2){
        printf("faltou nome\n") ; exit(1) ;
    }

    if((fp = fopen(argv[1], "w"))==NULL){ // tenta abrir pra escrita 
        printf("erro ao abrir\n") ; exit(1) ;
    }

    do{ // escreve a msg nele 
        scanf("%c", &c) ;
        fprintf(fp, "%c", c) ;//colocar no arquivo 
    } while(c != '$') ;
    
    fclose(fp) ; // passa as alterações
    
    if((fp = fopen(argv[1], "r"))==NULL){ // abre p leitura 
        printf("erro ao abrirz\n") ; exit(1) ;
    }

    while(fscanf(fp, "%c", &c) != EOF) printf("%c", c) ; // imprime no arquivo oq foi lido 
    
    return 0 ; 

} 
