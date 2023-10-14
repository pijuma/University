#include "lista.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 

// na main chamamos as funções do TAD da skip_list -> seguindo os padrões requisitados

void make_insertion(SKIP *skip){

    char pal[52], sig[142] ;
    scanf(" %s", pal) ; 
    scanf(" %[^\n]s", sig) ;

    ITEM *at = item_criar(pal, sig) ; 
    
    if(!skip_inserir(skip, at)) {
        item_apagar(&at);
        printf("OPERACAO INVALIDA\n") ; 
    }
        

}

void alterar(SKIP *skip){
    
    char pal[52], sig[142] ;
    scanf(" %s", pal) ; 
    scanf(" %[^\n]s", sig) ;

    ITEM *at = item_criar(pal, sig) ; 

    if(!skip_alterar(skip, at)) {
        printf("OPERACAO INVALIDA\n") ; 
    }

}

void remover(SKIP *skip){

    char pal[52];
    scanf(" %s", pal) ;

    if(!skip_remover(skip, pal))
        printf("OPERACAO INVALIDA\n") ; 

}

void buscar(SKIP *skip){

    char pal[52]; 
    scanf(" %s", pal) ; 

    ITEM *at = skip_busca_key(skip, pal) ;

    if (at == NULL) {
        printf("OPERACAO INVALIDA\n") ; return ;
    }

    printf("%s %s\n", pal, item_get_verb(at)) ;

}

void impressao(SKIP *skip){

    char car ; scanf(" %c", &car) ; 

    if(!skip_imprime_char(skip, car)) 
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", car) ; 

}

int main(){

    SKIP *lista = skip_criar();

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
