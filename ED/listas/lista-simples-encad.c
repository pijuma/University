/*
lista sequencial nao ordenada com insercao numa pos fixa pelo cara 
*/

#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>
#include "lista.h" 

struct NO_{
	ITEM *x ; 
	struct NO_ *prox ; 
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

bool lista_inserir(LISTA *l, ITEM *x, int pos){// muda todos do fim ate o pos p dir O(N) 

	if(l == NULL) return 0 ;

	NO *node = (NO *) malloc(sizeof(NO)) ; 
	node->x = x ; node->prox = NULL ; 

	if(node == NULL) printf("deu ruim\n") ; 

	if(pos == 0){ // add no começo
		node -> prox = l->ini ;
		l->ini = node ;
		if(l->fim == NULL) l->fim = node ;   
		l->tam++ ; 
		return 1 ;
	}

	NO *ant = NULL, *at = l->ini ; 
	int i = 0 ; 

	while(1){
		if(i == pos){
			if(ant == NULL) l->ini = node ; 
			if(at == NULL) l->fim = node ; 
			if(ant != NULL) ant->prox = node ; 
			node->prox = at ; 
		}
		if(at == NULL) break ; 
		ant = at ; at = at->prox ; i++ ; 
	}

	return 0 ; 

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

	NO *ant = NULL, *at = l->ini ;

	while(at != NULL){

		if(item_get_chave(at->x) == item_get_chave(x)){ // apagar o kra 

			if(ant  == NULL){// tirando do 1o 
				l->ini = at->prox ;
			} 
			
			else ant->prox = at->prox ; 

			if(at->prox == NULL) l->fim = ant ; 

			ITEM *item = at->x ;  
			item_apagar(&(at->x)) ;
			l->tam-- ;
			free(at) ; at = NULL ;
			return item ;

		}
		

		ant = at ; 
		at = at->prox ; 

	}

	return NULL ; 

}

// limpando aproveitando a função remover 
bool lista_apagar(LISTA **l){
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

bool lista_apagar(LISTA **l){
	if(*l == NULL) return 0 ; 
	apaga((*l)->ini) ; 
	free(*l) ; *l = NULL ; return 1 ; 
}

int lista_tamanho(LISTA *l){ return l->tam ; }

bool lista_vazia(LISTA *l){ return (l->tam==0) ; }

void lista_imprimir(LISTA *l){

	if(l == NULL || lista_vazia(l)) return ; 

	NO *at = l->ini ; 

	while(at != NULL){
		printf("%d ", item_get_chave(at->x)) ; 
		at = at->prox ; 
	}

	return ; 

}
