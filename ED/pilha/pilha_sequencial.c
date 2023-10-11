/*
nao esta implementada totalmente bonitinha (vulgo n coloquei checkers etc)
Implementação sequencial da pilha e estatica 
(nao tem como fazer implementacao estatica com uso de TAD)
a pilha adciona e retira do final, o que facilita sua implementacao 
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include "pilha.h"

typedef struct NO_ NO ; 

struct pilha_{
    ITEM *itens[maxn] ;
    int fim; 
} ;

PILHA *pilha_criar(){

    PILHA *p = (PILHA *) malloc(sizeof(PILHA)) ;

    if(p != NULL){
        p->fim = -1 ; 
    }

    return p ; 

}

int tam(PILHA *p){ return p->fim ; }
bool pilha_vazia(PILHA *pilha){ return (pilha->fim == 0) ;}
bool pilha_cheia(PILHA *pilha){ return pilha->fim>=maxn ; }

ITEM *pilha_topo(PILHA *p){ return p->itens[p->fim-1] ; }

ITEM *pop(PILHA *p){
    if(p == NULL || pilha_vazia(p)) return NULL ; 
    ITEM *at = p->itens[p->fim-1] ; 
    p->fim-- ; 
    return at ;  
}

bool push(PILHA *p, ITEM *x){

    if(pilha_cheia(p) || p == NULL) return 0 ; 

    p->itens[p->fim++] = x ; 

    return 1 ; 

}

bool pilha_apagar(PILHA **p){
    free(*p) ; *p = NULL ; 
}
