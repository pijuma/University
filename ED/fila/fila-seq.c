/*
implementacao de uma fila sequencial e dinamica 
com funcao inverter 
*/

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "fila.h" 

struct fila_{
    ITEM *itens[maxn] ;
    int fim, tam ; 
} ;

FILA *fila_criar(){

    FILA *at = (FILA *) malloc(sizeof(FILA)) ;

    if(at != NULL){
        at -> tam = 0, at -> fim = 0 ; 
    }

    return at ; 

}

ITEM *final(FILA *f){
    if(f == NULL || fila_vazia(f)) return NULL ; 
    return f->itens[f->fim-1] ;    
}

bool fila_apagar(FILA **f){
    free(*f) ; *f = NULL ; 
}

bool fila_inserir(FILA *f, ITEM *x){ // insere no começo
 
    if(fila_cheia(f) || f == NULL) return 0 ; 

    f->itens[f->fim] = x ;
    f->tam++ ; f->fim++ ; 

    return 1 ; 

}

ITEM *popar(FILA *f){

    if(fila_cheia(f) || f == NULL) return 0 ; 

    ITEM *at = f->itens[0] ;

    for(int i = 0 ; i < f->fim ; i++) f->itens[i] = f->itens[i+1] ;

    f->tam-- ; f->fim-- ; 
    
    return at ;

}

int fila_tam(FILA *f){ 
    if(f == NULL) return -1 ; 
    return f->tam ; 
}

bool fila_vazia(FILA *f){
    if(f == NULL) return 1 ; 
    return f->tam==0 ; 
}

bool fila_invert(FILA *f){

    if(f == NULL || fila_vazia(f)) return 0 ; 

    ITEM *aux[f->tam] ; 

    for(int i = 0 ; i < f->fim ; i++) aux[f->fim-i-1] = f->itens[i] ;

    for(int i = 0 ; i < f->fim ; i++) f->itens[i] = aux[i] ;
    
    return 1 ; 

}

bool fila_cheia(FILA *f) { 
    if(f == NULL) return 1 ; 
    return f->tam >= maxn ;
}
  
