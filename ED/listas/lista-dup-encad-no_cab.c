/*
lista duplamente encadeada com nó cabeça 
*/

#include<stdio.h>
#include<stdlib.h> 
#include<stdint.h>
#include "lista.h" 

struct NO_{
	ITEM *x ; 
	struct NO_ *prox, *ant ; 
} ; 

typedef struct NO_ NO ; 

struct lista_{
	NO *cab, *fim ; 
	int tam ; 
} ; 

LISTA *lista_criar(){

	LISTA *l = (LISTA *) malloc(sizeof(LISTA)) ; 

	if(l != NULL){
		NO *c = (NO *) malloc(sizeof(NO)) ;
		c->x = NULL ; c->prox = c->ant = NULL ; 
		l->cab = c ; l->fim = NULL ;   
		l->tam = 0 ; 
	}

	return l ;

}

int lista_inserir_cab(LISTA *l, ITEM *x){// insere sempre no começo/fim 

	if(l == NULL) return 0 ;

	NO *novo = (NO *) malloc(sizeof(NO)) ; 
	novo -> x = x ; novo->prox = novo->ant = NULL ; 
	novo->ant = l->cab ; novo->prox = l->cab->prox ;

	if(l->cab->prox != NULL) l->cab->prox->ant = novo ; 
	else l->fim = novo ; 

	l->cab->prox = novo ; 

	l->tam++ ; 

	return 1 ; 

}

int lista_inserir_fim(LISTA *l, ITEM *x){

	if(l == NULL) return 0 ; 

	NO *novo = (NO *) malloc(sizeof(NO)) ; 
	novo -> x = x ; novo->prox = novo->ant = NULL ; 

	if(l->fim != NULL){
		novo->ant = l->fim ;
		l->fim->prox = novo ; 
	}

	else{
		novo->ant = l->cab ; 
		l->cab->prox = novo ; 
	}

	l->fim = novo ; 
	l->tam++ ; 

	return 1 ; 

}

int lista_inserir_ord(LISTA *l, ITEM *x){

	if(l == NULL) return 0 ; 

	NO *at = l->cab ; 

	NO *novo = (NO *) malloc(sizeof(NO)) ; 
	novo -> x = x ; novo->prox = novo->ant = NULL ; 

	while(at != NULL && at->prox != NULL && item_get_chave(at->prox->x) <= item_get_chave(x)){
		at = at->prox ;
	} 

	if(at == NULL){ // final 
		novo->ant = l->fim ;
		if(l->fim != NULL) l->fim->prox = novo ;  
		l->fim = novo ; 
	}

	else{
		if(at->prox != NULL) (at->prox)->ant = novo ;  
		(novo->prox) = at->prox ; at->prox = novo ;
		novo->ant = at ;  
	}

	l->tam++ ; 

	return 1 ; 


}

ITEM *lista_buscar(LISTA *l, int chave){

	if(lista_vazia(l) || l == NULL) return NULL ; 

	NO *at = l->cab ; 

	while(at != NULL){
		if(item_get_chave(at->x) == chave) return at->x ; 
		at = at->prox ; 
	}

	return NULL ; 

}

ITEM *buscar(NO *at, int chave){
	if(at == NULL) return NULL ; 
	if(item_get_chave(at->x) == chave) return at->x ; 
	return buscar(at->prox, chave) ; 
}

ITEM *busca(LISTA *l, int chave){
	if(l == NULL) return NULL ; 
	return buscar(l->cab->prox, chave) ; 
}

ITEM *lista_remover(LISTA *l, ITEM *x){ // desloca todos pra esq dps de remover 

	if(l == NULL || busca(l, item_get_chave(x)) == NULL) return NULL ; 

	NO *at = l->cab->prox ; 

	while(at != NULL && item_get_chave(at->x) != item_get_chave(x)) at = at->prox ; 

	if(at == NULL) return NULL ; 
	// vou mudar o final 
	if(at->prox == NULL){
		if(at->ant == l->cab) l->fim = NULL ; // ficou vazia 
		else l->fim = at->ant ;
	} 

	at->ant->prox = at->prox ; 
	if(at->prox != NULL) at->prox->ant = at-> ant ; 

	ITEM *item = at->x ; 
	item_apagar(&(at->x)) ; 
	free(at) ; at = NULL ; 

	return item ; 

}

// limpando aproveitando a função remover 
int lista_apagar(LISTA **l){
	if(*l == NULL) return 0 ; 
	while((*l)->cab != NULL) lista_remover((*l), ((*l)->cab)->x) ; 
	free(*l) ; *l = NULL ; 
	return 1 ; 
}

// limpando sem a função remover 
void apaga(NO *no){
	if(no == NULL) return ; 
	apaga(no->prox) ; 
	item_apagar(&(no->x)) ; 
	free(no) ; no = NULL ; 
}

int lista_apagar(LISTA **l){
	if(*l == NULL) return 0 ; 
	apaga((*l)->cab) ; 
	free(*l) ; *l = NULL ; return 1 ; 
}

int lista_tamanho(LISTA *l){ return l->tam ; }

int lista_vazia(LISTA *l){ return (l->tam==0) ; }

void lista_imprimir(LISTA *l){

	if(l == NULL || lista_vazia(l)) return ; 

	NO *at = l->cab->prox ; 

	while(at != NULL){
		printf("%d ", item_get_chave(at->x)) ; 
		at = at->prox ; 
	}

	return ; 

}
