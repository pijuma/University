/*
lista sequencial nao ordenada com insercao numa pos fixa pelo cara 
*/

#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>
#include "lista.h" 

struct lista_{
	ITEM *itens[maxn] ; 
	int ini, fim ; 
} ; 

LISTA *lista_criar(){

	LISTA *l = (LISTA *) malloc(sizeof(LISTA)) ; 

	if(l != NULL){
		l->ini = l->fim = 0 ; 
	}

	return l ;

}

bool lista_inserir(LISTA *l, ITEM *x, int pos){// muda todos do fim ate o pos p dir O(N)

	if(lista_cheia(l) || l == NULL) return 0 ; 

	for(int i = l->fim -1 ; i >= pos ; i--) l->itens[i+1] = l->itens[i] ; 
	l->itens[pos] = x ; 
	l->fim++ ;  

	return 1 ;

}

int lista_buscar(LISTA *l, int chave){

	if(l == NULL || lista_vazia(l)) return -1 ; 

	for(int i = l->ini ; i < l->fim ; i++) if(item_get_chave(l->itens[i]) == chave) return i ; 

	return -1 ; 

}

ITEM *lista_remover(LISTA *l, ITEM *x){ // desloca todos pra esq dps de remover 

	int pos = lista_buscar(l, item_get_chave(x)) ; 

	if(pos == -1) return NULL ; 

	item_apagar(&(l->itens[pos])) ; 

	for(int i = pos ; i < l->fim - 1 ; i++) l->itens[i] = l->itens[i+1] ;

	l->fim-- ; 

	return x ; 

}

bool lista_apagar(LISTA **l){
	if(*l == NULL) return 0 ; 
	for(int i = (*l)->ini ; i < (*l)->fim ; i++) item_apagar(&((*l)->itens[i])) ; 
	free(*l) ; *l = NULL ; 
	return 1 ; 

}

int lista_tamanho(LISTA *l){ return l->fim - l->ini ; }

bool lista_vazia(LISTA *l){ return (l->fim == l->ini) ; }

bool lista_cheia(LISTA *l){ return (l->fim -l->ini == maxn) ; }

void lista_imprimir(LISTA *l){

	if(l == NULL || lista_vazia(l)) return ; 

	printf("tentei imprimir\n") ;

	for(int i = l->ini ; i < l -> fim ; i++) printf("%d ", item_get_chave(l->itens[i])) ; 

	printf("\n") ; 

}
