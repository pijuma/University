#include "set.h"

struct set{
	AVL *T ;  
} ;

SET *set_criar(void){
	
	SET *set = (SET *) malloc(sizeof(SET)) ; 

	if(set != NULL){
		set -> T = avl_criar() ; 
	}

	return set ; 

}

bool set_pertence(SET *A, int elemento){
	if(A == NULL) return 0 ;
	return avl_buscar(A->T, elemento) ;
}

bool set_inserir (SET *s, int elemento){
	
	if(s == NULL) return 0 ; 

	ITEM *item = item_criar(elemento) ; 

	if(item == NULL) return 0 ; 

	return avl_inserir(s->T, item) ; 

}

bool set_remover(SET *s, int elemento){
	
	if(s == NULL) return 0 ; 

	return avl_remover(s->T, elemento) ;

}

void set_apagar(SET **s){
	
	if(*s == NULL) return ; 

	avl_apagar(&((*s)->T)) ; 
	
	free(*s) ; *s = NULL ; 

}

void set_imprimir(SET *s){
	
	if(s == NULL) return ; 

	avl_dfs(s->T) ; 

}

SET *set_uniao(SET *A, SET *B){

	SET *uniao = set_criar() ; 

	avl_adicionar_elementos(&(uniao->T), A->T) ;
	avl_adicionar_elementos(&(uniao->T), B->T) ;

	return uniao ; 
}
SET *set_interseccao(SET *A, SET *B){

	SET *comum = set_criar() ;

	if(avl_get_size(A->T) > avl_get_size(B->T)) avl_comum(&(comum->T), A->T, B->T) ;
	else avl_comum(&(comum->T), B->T, A->T) ;

	return comum ;

}