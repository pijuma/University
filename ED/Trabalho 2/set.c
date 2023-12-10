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

// função que checa se um elemento pertence ao set 
// O(log(n)) - mesma complexidade da busca da avl 

bool set_pertence(SET *A, int elemento){
	if(A == NULL) return 0 ;
	return avl_buscar(A->T, elemento) ;
}

// insere um novo elemento no set - caso já não exista
bool set_inserir (SET *s, int elemento){
	
	if(s == NULL) return 0 ; 

	if(set_pertence(s, elemento)) return 0 ;

	ITEM *item = item_criar(elemento) ; 

	if(item == NULL) return 0 ; 

	return avl_inserir(s->T, item) ; 

}

// remove um elemento do set, caso ele exista
bool set_remover(SET *s, int elemento){
	
	if(s == NULL) return 0 ; 

	if(!set_pertence(s, elemento)) return 0 ;

	return avl_remover(s->T, elemento) ;

}

void set_apagar(SET **s){
	
	if(*s == NULL) return ; 

	avl_apagar(&((*s)->T)) ; 
	
	free(*s) ; *s = NULL ; 

}

// imprime os elementos do set
// a impressão é feita pelo percurso em-ordem 
// que retorna os elementos da avl (armazenada no set) 
// em ordem crescente 
void set_imprimir(SET *s){
	
	if(s == NULL) return ; 

	avl_dfs(s->T) ; 

}

// retorna um set que é a união de todos os elementos contidos
// nos sets A e B dados 
// adicionamos cada elemento no set final, indo elemento por elemento 
// portanto a complexidade será na ordem de O(n+m)
// sendo n o tamanho do Set A e m o tamanho do Set B 
SET *set_uniao(SET *A, SET *B){

	SET *uniao = set_criar() ; 

	avl_adicionar_elementos(&(uniao->T), A->T) ;
	avl_adicionar_elementos(&(uniao->T), B->T) ;

	return uniao ; 
}

// retorna um set que contem os elementos comuns dos sets A e B 
// fica O(menor*log(maior))
// isso pois percorremos a menor avl checando se o 
// elemento está contido também na maior avl
SET *set_interseccao(SET *A, SET *B){

	SET *comum = set_criar() ;

	if(avl_get_size(A->T) > avl_get_size(B->T)) avl_comum(&(comum->T), A->T, B->T) ;
	else avl_comum(&(comum->T), B->T, A->T) ;

	return comum ;

}
