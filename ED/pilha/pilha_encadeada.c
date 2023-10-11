/*
Implementação encadeada da pilha e dinamica 
(nao tem como fazer implementacao estatica com uso de TAD)
a pilha adciona e retira do final, o que facilita sua implementacao 
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include "pilha.h"

struct NO_{
    ITEM *x ; 
    struct NO_ *ant ; 
} ;

typedef struct NO_ NO ; 

struct pilha_{
    NO *topo ; int tam ; 
} ;

PILHA *pilha_criar(){

    PILHA *p = (PILHA *) malloc(sizeof(PILHA)) ;

    if(p != NULL){
        p->topo = NULL ; p->tam = 0 ; 
    }

    return p ; 

}

int tam(PILHA *p){ return p->tam ; }
bool pilha_vazia(PILHA *pilha){ return (pilha->tam == 0) ;}
bool pilha_cheia(PILHA *pilha){ return 0 ; }

ITEM *pilha_topo(PILHA *p){ return p->topo->x ; }

ITEM *pop(PILHA *p){
    NO *resp = p->topo ; 
    ITEM *ans = resp->x ; 
    p->topo = resp->ant ; 
    resp->ant = NULL ; 
    free(resp) ; resp = NULL ; 
    p->tam-- ; 
    return ans ; 
}

bool push(PILHA *p, ITEM *x){

    if(pilha_cheia(p) || p == NULL) return 0 ; 

    //printf("criei item com chave %d", item_get_chave(x)) ;

    NO *at = (NO *) malloc(sizeof(NO)) ;
    at->x = x ; 
    at->ant = p->topo ; 
    p->topo = at ; 
    return 1 ; 

}

bool pilha_apagar(PILHA **p){
    while(!pilha_vazia(*p)){
        ITEM *a = pop(*p) ;
        item_apagar(&a) ;
    } 
    free(*p) ; *p = NULL ; 
}
