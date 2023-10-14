/*
lista sequencial ordenada
o int t na busca define para que serve ela, assim posso realizar apenas uma função de busca 
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

bool lista_inserir(LISTA *l, ITEM *x){// muda todos do fim ate o pos p dir O(N)

	if(lista_cheia(l) || l == NULL) return 0 ; 

	int pos = lista_buscar(l, item_get_chave(x), 1) ; 

	for(int i = l->fim - 1 ; i >= pos ; i--) l->itens[i+1] = l->itens[i] ; 
	l->itens[pos] = x ; 
	l->fim++ ;  

	return 1 ;

}

int lista_buscar(LISTA *l, int chave, int t){ // tenho que achar o 1o cara maior que eu 

	int ini = l->ini, fim = l->fim-1, mid, best = l->fim ; 

	while(ini <= fim){
		mid = (ini + fim)>>1 ; 
		if(item_get_chave(l->itens[mid]) >= chave) best = mid, fim = mid - 1 ; 
		else ini = mid + 1 ; 
	}

	if(t == 0){
		if(best < l->fim && item_get_chave(l->itens[best]) == chave) return best ; 
		else return -1 ; 
	}

	return best ; 

}

ITEM *lista_remover(LISTA *l, ITEM *x){ // desloca todos pra esq dps de remover 

	int pos = lista_buscar(l, item_get_chave(x), 1) ; 

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
