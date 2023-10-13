#include "lista.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 

void make_insertion(SKIP *skip){

    char a[55], b[145] ;
    scanf(" %s", a) ; 
    scanf(" %[^\n]s", b) ;

    ITEM *at = item_criar(a, b) ; 
    
    if(!skip_inserir(skip, at)) {
        item_apagar(&at);
        printf("OPERACAO INVALIDA\n") ; 
    }
        

}

void alterar(SKIP *skip){
    
    char a[55], b[145] ;
    scanf(" %s", a) ; 
    scanf(" %[^\n]s", b) ;

    ITEM *at = item_criar(a, b) ; 

    if(!skip_alterar(skip, at)) {
        printf("OPERACAO INVALIDA\n") ; 
    }

}

void remover(SKIP *skip){

    char a[55];
    scanf(" %s", a) ;

    if(!skip_remover(skip, a))
        printf("OPERACAO INVALIDA\n") ; 

}

void buscar(SKIP *skip){

    char a[55]; 
    scanf(" %s", a) ; 

    ITEM *at = skip_busca_key(skip, a) ;

    if (at == NULL) {
        printf("OPERACAO INVALIDA\n") ; return ;
    }

    printf("%s %s\n", a, item_get_verb(at)) ;

}

void impressao(SKIP *skip){

    char a ; scanf(" %c", &a) ; 

    if(!skip_imprime_char(skip, a)) 
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", a) ; 

}

int main(){

    SKIP *lista = skip_criar();

    //int n ; scanf("%d", &n) ; 
    char t[55];

    while(scanf(" %s", t) != EOF) {
        if(!strcmp(t, "insercao")) make_insertion(lista) ; 
        else if(!strcmp(t, "alteracao")) alterar(lista) ; 
        else if(!strcmp(t, "remocao")) remover(lista) ;
        else if(!strcmp(t, "busca")) buscar(lista) ; 
        else impressao(lista) ;  
    }

    skip_apagar(&lista);
}
