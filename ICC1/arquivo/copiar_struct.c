#include<stdio.h> 
#include<stdlib.h> 

struct T{
    int i ; 
    double d ; 
    char str[5] ; 
} ;

typedef struct T t ;

t coloca(int id, double a, char s){
    t ans ; 
    ans.i = id, ans.d = a, ans.str[0] = s ;  
    return ans ; 
}

void imprime(t a){ printf("%d %lf %s\n", a.i, a.d, a.str[0]) ; }

int main(){

    FILE *fp ; 
    t *vet = NULL ; // vetor de structs 

    vet = (t *) malloc(sizeof(5*sizeof(t))) ; // cria um vetor com 5 structs 

    if(vet == NULL){
        printf("deu ruim\n") ; exit(1) ;
    }

    vet[0] = coloca(1, 1.0, 'A') ; vet[1] = coloca(2, 2.0, 'B') ; vet[2] = coloca(3, 3.0, 'C') ;

    if((fp = fopen("teste.bin", "wb")) == NULL){ // abrir binario p escrita 
        printf("erro ao abrir p escrita\n") ;
        exit(1) ;
    }

    fwrite(vet, sizeof(t), 3, fp) ; fwrite(&vet[0], sizeof(t), 1, fp) ;

    fclose(fp) ;
    
    if((fp = fopen("teste.bin", "rb")) == NULL){ 
        printf("erro ao abrir p leitura\n") ; exit(1) ;
    }

    free(vet) ; vet = NULL ; 

    vet = (t *) malloc(sizeof(t)*4) ;

    fread(vet, sizeof(t), 4, fp) ;

    for(int i = 0 ; i < 4 ; i++) imprime(vet[i]) ;
    
    printf("%d", vet[0].i) ;

    free(vet) ; vet = NULL ; fclose(fp) ;

    return 0 ; 

}
