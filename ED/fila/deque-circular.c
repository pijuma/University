#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "circ.h"

struct fila_{
	ITEM *itens[maxn] ; 
	int ini, fim, tam ; 
} ; 

FILA *fila_criar(){
	
	FILA *f = (FILA *) malloc(sizeof(FILA)) ; 

	if(f != NULL){
		f->ini = f->fim = f->tam = 0 ; 
	}

	return f ; 

}

bool fila_apagar(FILA **f){
	free(*f) ; *f = NULL ;
}

bool fila_inserir_ini(FILA *f, ITEM *x){

	if(f == NULL || fila_cheia(f)) return 0 ; 

	f->ini-- ; f->ini = (f->ini+maxn)%maxn ; 

	f->itens[f->ini] = x ; 

	f->tam++ ; 

	return 1 ; 

}

bool fila_inserir(FILA *f, ITEM *x){ // insere no final 

	if(f == NULL || fila_cheia(f)) return 0 ; 

	f->itens[f->fim] = x ; 
	f->fim++  ;f->fim %= maxn ; 
	f->tam++ ; 

	return 1 ; 

}

ITEM *fila_remover_fim(FILA *f){

	if(f == NULL || fila_vazia(f)) return NULL ; 

	ITEM *a = f->itens[f->fim] ; 

	f->itens[f->fim] = NULL ; 
	f->fim-- ; f->fim = (f->fim+maxn)%maxn ; 
	f->tam-- ; 

	return a ; 

}

ITEM *fila_remover(FILA *f){ // tira no começo 

	if(f == NULL || fila_vazia(f)) return NULL ; 

	ITEM *a = f->itens[f->ini] ; 

	f->itens[f->ini] = NULL ; 
	f->ini++ ; f->ini %= maxn ; 
	f->tam-- ; 

	return a ; 

}

int fila_tam(FILA *f){ return f->tam ; }

bool fila_vazia(FILA *f){
	if(f == NULL) return 1 ; 
	return (f->tam==0) ; 
} 

bool fila_cheia(FILA *f){
	if(f == NULL) return 1 ;
	return (f->tam>=maxn) ; 
}
