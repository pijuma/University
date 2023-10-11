#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h> 
#include "pilha.h"

// sequencial estatica

struct pilha_{
	ITEM *item[maxn] ; 
	int tamanho ; 
} ; 

PILHA *pilha_criar(){

	PILHA *a = NULL ; 
	a = (PILHA *) malloc(sizeof(PILHA)) ; 

	if(a != NULL){
		a -> tamanho = 0 ; // vazia
	}

	return a ; 

} 

bool pilha_apagar(PILHA *pilha){

	if(pilha == NULL) return 1 ; 

	for(int i = 0 ; i < (pilha -> tamanho) ; i++){
		item_apagar(&(pilha->item[i])) ; 
	}

	free(pilha) ; pilha = NULL ; 

	return 1 ; 

} 

ITEM *top(PILHA *pilha){
	
	if(pilha != NULL){
		return pilha -> item[pilha -> tamanho - 1] ; // -1 -> 0 index 
	}

	return NULL ;

}

ITEM *pop(PILHA *pilha){

	if(pilha != NULL && !pilha_vazia(pilha)){
		ITEM *a = top(pilha) ; 
		pilha -> item[pilha-> tamanho-1] = NULL ; 
		pilha-> tamanho-- ; 
		return a ; 
	}

	return NULL ; 

}

bool push(PILHA *pilha, ITEM *x){
	
	if(pilha != NULL && !pilha_cheia(pilha)){

		pilha -> item[pilha -> tamanho] = x ; 
		pilha -> tamanho ++ ; 

	    return 1 ; 
	}

	return 0 ; 
}

int pilha_tamanho(PILHA *pilha){ return pilha->tamanho ; }

bool pilha_vazia(PILHA *pilha){
	if(pilha != NULL) return (pilha -> tamanho == 0) ;
	return false ; 
}

bool pilha_cheia(PILHA *pilha){
	
	if(pilha != NULL){
		return (pilha -> tamanho == maxn) ; 
	}
	
	return false ; 

}
