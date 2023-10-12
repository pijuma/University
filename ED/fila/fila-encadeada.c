#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "circ.h"

struct NO_{
	ITEM *x ; 
	struct NO_ *prox ; 
} ; 

typedef struct NO_ NO ; 

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

bool fila_apagar(FILA **f){

	while(!fila_vazia(*f)){
		ITEM *a = fila_remover(*f) ; 
		item_apagar(&a) ; 
	}

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

int fila_tam(FILA *f){ return f->tam ; }

bool fila_vazia(FILA *f){
	if(f == NULL) return 1 ; 
	return (f->tam==0) ; 
} 
