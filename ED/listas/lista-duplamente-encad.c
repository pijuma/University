/*
lista duplamente encadeada com funções para manter ordenada ou nao (opcional)  
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
	NO *ini, *fim ; 
	int tam ; 
} ; 

LISTA *lista_criar(){

	LISTA *l = (LISTA *) malloc(sizeof(LISTA)) ; 

	if(l != NULL){
		l->ini = l->fim = NULL ; 
		l->tam = 0 ; 
	}

	return l ;

}

int lista_inserir_ini(LISTA *l, ITEM *x){// insere sempre no começo/fim 

	if(l == NULL) return 0 ;

	NO *novo = (NO *) malloc(sizeof(NO)) ;

	novo -> x = x ; novo->ant = novo->prox = NULL ; 

	l->tam++ ; 

	if(l->fim == NULL) l->fim = novo ; 

	if(l->ini != NULL) (l->ini)->ant = novo ;
	novo->prox = l->ini ;  
	l->ini = novo ; 

	return 1 ; 

}

int lista_inserir_fim(LISTA *l, ITEM *x){

	if(l == NULL) return 0 ; 

	NO *novo = (NO *) malloc(sizeof(NO)) ; 

	novo -> x = x ; novo->ant = novo->prox = NULL ; 

	if(l->ini == NULL) l->ini = novo ; 

	novo -> ant = l->fim ; 
	if(l->fim != NULL) l->fim->prox = novo ; 
	l->fim = novo ; 
	l->tam++ ; 

	return 1 ; 

}

int lista_inserir_ord(LISTA *l, ITEM *x){

	if(l == NULL) return 0 ; 

	// buscar o ultimo lugar que eh menor que eu 

	NO *at = l->ini ; 
	NO *novo = (NO *) malloc(sizeof(NO)) ; 

	novo->x = x ; novo->ant = novo->prox = NULL ; 
	novo->ant = NULL ; 

	while(at != NULL && at->prox != NULL && item_get_chave((at->prox)->x) <= item_get_chave(x)) at = at->prox ; 

	// at guarda o ultimo <= a mim 

	if(at == NULL){//lista vazia 
		l->ini = l->fim = novo ; 
		l->tam++ ; 
		return 1 ; 
	}

	if(item_get_chave(at->x) > item_get_chave(x)){ // to na 1a pos 
		novo->prox = l->ini ; 
		l->ini->ant = novo ; 
		l->ini = novo ; 
	}

	else if(at->prox == NULL){ // sou o ultimo ent meu prox n existe 
		at->prox = novo ; 
		novo->ant = at ;
		l->fim = novo ; 
	}

	else{ // meio 
		novo -> ant = at ; novo ->prox = at->prox ; 
		at->prox = novo ; (novo->prox)->ant = novo ; 
	}

	l->tam++ ; 

	return 1 ; 

}

ITEM *lista_buscar(LISTA *l, int chave){

	if(lista_vazia(l) || l == NULL) return NULL ; 

	NO *at = l->ini ; 

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
	return buscar(l->ini, chave) ; 
}

ITEM *lista_remover(LISTA *l, ITEM *x){ // desloca todos pra esq dps de remover 

	if(l == NULL || busca(l, item_get_chave(x)) == NULL) return NULL ; 

	NO *at = l->ini ; 

	while(at != NULL && item_get_chave(at->x) != item_get_chave(x)) at = at->prox ; 

	if(at == NULL) return NULL ; 

	if(at->ant != NULL) (at->ant)->prox = (at)->prox ; 
	else l->ini = at->prox ; // sou inicio 

	if(at->prox == NULL) l->fim = at->ant ; 
	else (at->prox)->ant = at->ant ;  

	ITEM *itemm = at->x ; 

	at->ant = NULL ; at->prox = NULL ; 
	free(at) ; at = NULL ; 
	l->tam-- ; 

	return itemm ; 

}

// limpando aproveitando a função remover 
int lista_apagar(LISTA **l){
	if(*l == NULL) return 0 ; 
	while((*l)->ini != NULL) lista_remover((*l), ((*l)->ini)->x) ; 
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
	apaga((*l)->ini) ; 
	free(*l) ; *l = NULL ; return 1 ; 
}

int lista_tamanho(LISTA *l){ return l->tam ; }

int lista_vazia(LISTA *l){ return (l->tam==0) ; }

void lista_imprimir(LISTA *l){

	if(l == NULL || lista_vazia(l)) return ; 

	NO *at = l->ini ; 

	while(at != NULL){
		printf("%d ", item_get_chave(at->x)) ; 
		at = at->prox ; 
	}

	return ; 

}
