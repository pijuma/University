#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "lista.h"

// tem que fazer encadeada e inverter a lista 

struct NO_{
    ITEM *x ; //cara atual 
    struct NO_ *prox ; // next dele  
};

typedef struct NO_ NO ; 

struct lista_{
    NO *ini, *fim ; 
    int tam ;  
} ;

LISTA *lista_criar(void){

    LISTA *lista = (LISTA *) malloc(sizeof(LISTA)) ;

    if(lista != NULL){
        lista->ini = lista -> fim = NULL ; 
        lista->tam = 0 ; 
    }

    return lista ; 

}

bool lista_inserir(LISTA *lista, ITEM *item){//insercao sem ordenar - insere no final 

    if(lista == NULL || lista_cheia(lista)) return 0 ; 

    //fala que o prox do ultimo agora eh meu atual e guarda meu no como fim 

    NO *at = (NO *) malloc(sizeof(NO)) ; 
    at -> x = item ; at->prox = NULL ; 

    if(lista_vazia(lista)){
        lista->ini = lista->fim = at ; 
    }

    else{
        (lista->fim)->prox = at ;
        lista->fim = at ;
    } 

    lista->tam++ ; 

    return 1 ; 

}

ITEM *lista_remover(LISTA *lista, int chave){ // procura o cara e remove ele 

    if(lista == NULL || lista_vazia(lista)) return NULL ; 

    NO *at = lista->ini ; // ao final esse NO vai guardar o cara q vou remover 
    NO *ant = NULL ; 

    for(; at != NULL ; at = at->prox){
        if(item_get_chave(at->x) == chave) break ; 
        ant = at ; 
    }

    ITEM *who = at->x ; 

    if(ant == NULL){ // to tirando do 1o 
        if(at->prox != NULL) lista->ini = at->prox ;
        at->prox = NULL ; 
    }

    else{
        ant->prox = at->prox ; at->prox = NULL ; 
    }
    
    lista->tam-- ;

    free(at) ;

    return who ; 

}

bool lista_apagar(LISTA **lista){

    if(*lista == NULL) return 0 ; // n precisa apagar 

    for(NO *i = (*lista)->ini ; i != NULL ; ){
        NO *nxt = i->prox ; 
        i->prox = NULL ; free(i) ; 
        i = nxt ; 
    }

    *lista = NULL ; 
    free(*lista) ;

    return 1 ; 

}

ITEM *lista_busca(LISTA *lista, int chave){
    ITEM *who = NULL ; 
    for(NO *i = lista->ini ; i != NULL ; i = i->prox){
        if(item_get_chave(i->x) == chave){
            return (i->x) ; 
        }
    }
    return NULL ;
}

int lista_tamanho(LISTA *lista){ return lista->tam ; }

bool lista_vazia(LISTA *lista){ return (lista->tam==0) ; }

bool lista_cheia(LISTA *lista){ 
    NO *neww = (NO *) malloc(sizeof (NO)) ;
    return (neww==NULL) ; 
}
void lista_imprimir(LISTA *lista){
    if(lista_vazia(lista) || lista == NULL) return ; 
    //printf("%d %d", item_get_chave(lista->ini->x), item_get_chave(lista->fim->x)) ;
    for(NO *i = lista->ini ; i != NULL ; i = i->prox) printf("[%d]; ", item_get_chave(i->x)) ;
    printf("\n") ; 
}

void change(NO *at, NO *ant){

    if(at==NULL) return ; 

    change(at->prox, at) ;

    at->prox = ant ; 

}

bool lista_inverter(LISTA **lista){
    // faz uma funcao pra inverter os nos internamente - recursiva retorna o meu atual 
    if((*lista)==NULL || lista_vazia(*lista)) return 0 ; 
    change((*lista)->ini, NULL) ;
    NO *ini_ant = (*lista)->ini ; 
    (*lista)->ini = (*lista)->fim ;
    (*lista)->fim = ini_ant ;   
    return 1 ; 
}
