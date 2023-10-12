#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "circ.h"

struct NO_{
	ITEM *x ; 
	struct NO_ *prox ; 
} ; 

struct fila_{
	NO *ini, *fim ; 
	int tam ; 
} ; 

FILA *fila_criar(){

	FILA *f = (FILA *) malloc(sizeof(FILA)) ;

	if(f != NULL){
		f->tam = 0 ; f->ini = f->fim = NULL ; 
	}

	return f ; 

}

void apagar(NO *a){

	if(a == NULL) return ; 
	apagar(a->prox) ; 
	item_apagar(&(a->x)) ;
	free(a) ; a = NULL ; 

}

bool fila_apagar(FILA **f){

	if(*f == NULL || fila_vazia(*f)) return 0 ; 

	apagar((*f)->ini) ; 

	free(*f) ; *f = NULL ;
}

bool fila_inserir(FILA *f, ITEM *x){ // insere no final 

	if(f == NULL) return 0 ; 

	NO *at = (NO *) malloc(sizeof (NO)) ; 
	at -> x = x ; 
	at-> prox = NULL ; 

	if(f->fim != NULL){
		NO *lst = f->fim ; 
		lst->prox = at ; 
	}

	f->tam++ ; 

	if(f->ini == NULL) f->ini = at ; 
	
	f->fim = at ; 

	return 1 ; 

}

ITEM *fila_remover(FILA *f){ // tira no começo 

	if(fila_vazia(f) || f == NULL) return NULL ; 

	NO *topo = f->ini ; 
	ITEM *a = topo->x ; 

	f->ini = topo->prox ;
	f->tam--;

	free(topo) ; topo = NULL ; 

	return a ;

}

void impressao(NO *a){
	if(a == NULL) return ;
	printf("%d ", item_get_chave(a->x)) ;
	impressao(a->prox) ;  
}

void imprimir(FILA *f){
	
	if(f == NULL || fila_vazia(f)) return ; 

	impressao(f->ini) ; 

}

void inverter(NO *ant, NO *a){

	if(a == NULL) return ; 

	inverter(a, a->prox) ; 

	a->prox = ant ; 

}

bool fila_invert(FILA *f){
	if(f == NULL || fila_vazia(f)) return 0 ; 
	NO *final = f->fim ; 
	inverter(NULL, f->ini) ; 
	f->fim = f->ini ; f->ini = final ;
	return 1 ; 
}

int fila_tam(FILA *f){ return f->tam ; }

bool fila_vazia(FILA *f){
	if(f == NULL) return 1 ; 
	return (f->tam==0) ; 
} 
