/*
lista sequencial nao ordenada com insercao numa pos fixa pelo cara 
o proximo do ultimo eh o 1o cara 
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
	NO *sentinela, *fim ; 
	int tam ; 
} ; 

LISTA *lista_criar(){

	LISTA *l = (LISTA *) malloc(sizeof(LISTA)) ; 

	if(l != NULL){
		NO *c = (NO *) malloc(sizeof(NO)) ;
		c->x = item_criar(-1) ; c->prox = c->ant = c ; 
		l->sentinela = c ; l->fim = c ;   
		l->tam = 0 ; 
	}

	return l ;

}

int lista_inserir_ini(LISTA *l, ITEM *x){// insere sempre no começo/fim 

	if(l == NULL) return 0 ;

	NO *novo = (NO *) malloc(sizeof(NO)) ; 
	novo -> x = x ; 
	novo->ant = l->sentinela ; novo->prox = l->sentinela->prox ;

	if(l->sentinela->prox == l->sentinela){//vazio
		l->fim = novo ; 
	}

	l->sentinela->prox->ant = novo ; 
	l->sentinela->prox = novo ; 

	l->tam++ ; 

	return 1 ; 

}

int lista_inserir_fim(LISTA *l, ITEM *x){

	if(l == NULL) return 0 ; 

	NO *novo = (NO *) malloc(sizeof(NO)) ; 
	novo -> x = x ;

	novo->ant = l->fim ;
	l->fim->prox = novo ; 

	novo->prox = l->sentinela ; 

	l->fim = novo ; 
	l->tam++ ; 

	return 1 ; 

}

int lista_inserir_ord(LISTA *l, ITEM *x){

	if(l == NULL) return 0 ; 

	NO *at = l->sentinela ; 

	int fv = 0 ; 

	NO *novo = (NO *) malloc(sizeof(NO)) ; 
	novo -> x = x ; 

	while(item_get_chave(at->prox->x) <= item_get_chave(x)){
		if(fv && at->prox == l->sentinela) break ; 
		if(at == l->sentinela) fv = 1 ;  
		at = at->prox ;
	} 

	if(at->prox == l->sentinela){ // final 
		l->fim = novo ;  
	}

	novo -> prox = at->prox ; 
	novo -> ant = at ; 

	at->prox->ant = novo ; 
	at -> prox = novo ; 

	l->tam++ ; 

	return 1 ; 


}

ITEM *lista_buscar(LISTA *l, int chave){

	if(lista_vazia(l) || l == NULL) return NULL ; 

	NO *at = l->sentinela->prox ; 
	item_set_chave(l->sentinela->x, chave) ; 

	while(item_get_chave(at->x) != chave) at = at->prox ; 

	return (at == l->sentinela ? NULL : at->x) ; 

}

ITEM *buscar(NO *at, int chave){
	if(at == NULL) return NULL ; 
	if(item_get_chave(at->x) == chave) return at->x ; 
	return buscar(at->prox, chave) ; 
}

ITEM *busca(LISTA *l, int chave){
	if(l == NULL) return NULL ; 
	return buscar(l->sentinela->prox, chave) ; 
}

ITEM *lista_remover(LISTA *l, ITEM *x){ // desloca todos pra esq dps de remover 

	if(l == NULL) return NULL ; 

	NO *at = l->sentinela ->prox ;  
	item_set_chave(l->sentinela->x, -1) ; 

	while(at != l->sentinela && item_get_chave(at->x) != item_get_chave(x)) 
		at = at->prox ; 

	if(at == l->sentinela) return NULL ; 
	
	// vou mudar o final 
	if(at->prox == l->sentinela){
		l->fim = at->ant ;
	} 
	
	at->ant->prox = at->prox ; 
	at->prox->ant = at-> ant ; 

	ITEM *item = at->x ; 
	free(at) ; at = NULL ; 

	l->tam--;

	return item ; 

}

// limpando aproveitando a função remover 
// int lista_apagar(LISTA **l){
// 	if(*l == NULL) return 0 ; 
// 	while((*l)->sentinela != NULL) lista_remover((*l), ((*l)->sentinela)->x) ; 
// 	free(*l) ; *l = NULL ; 
// 	return 1 ; 
// }

// limpando sem a função remover 
void apaga(NO *no, LISTA *l){
	if(no->prox != l->sentinela) apaga(no->prox, l) ; 
	item_apagar(&(no->x)) ; 
	free(no) ; no = NULL ; 
}

int lista_apagar(LISTA **l){
	if(*l == NULL) return 0 ; 
	apaga((*l)->sentinela, *l) ; 
	free(*l) ; *l = NULL ; return 1 ; 
}

int lista_tamanho(LISTA *l){ return l->tam ; }

int lista_vazia(LISTA *l){ return (l->tam==0) ; }

void lista_imprimir(LISTA *l){

	if(l == NULL || lista_vazia(l)) return ; 

	NO *at = l->sentinela->prox ; 

	while(at != l->sentinela){
		printf("%d ", item_get_chave(at->x)) ; 
		at = at->prox ; 
	}

	printf("\n") ;

	return ; 

}
