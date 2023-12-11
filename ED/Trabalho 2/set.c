#include "set.h"

struct set{
	AVL *T ;  
} ;

// função que aloca a memória para criação de um SET, criando também a AVL interna a esse 
SET *set_criar(void){
	
	SET *set = (SET *) malloc(sizeof(SET)) ; 

	if(set != NULL){
		set -> T = avl_criar() ; 
	}

	return set ; 

}

// função que checa se um elemento pertence ao set - chama a função buscar do TAD AVL 

bool set_pertence(SET *A, int elemento){
	if(A == NULL) return 0 ;
	return avl_buscar(A->T, elemento) ;
}

// insere um novo elemento no set - caso ele não exista ainda no mesmo 
// para isso checamos se ele já existe, foi uma forma que escolhemos de lidar com possíveis perda de memória
// por criar itens que serão perdidos por serem repetidos na estrutura
bool set_inserir (SET *s, int elemento){
	
	if(s == NULL) return 0 ; 

	if(set_pertence(s, elemento)) return 0 ;

	ITEM *item = item_criar(elemento) ; 

	if(item == NULL) return 0 ; 

	return avl_inserir(s->T, item) ; 

}

// remove o "elemento" do set, caso ele exista (checagem feita no TAD AVL (avl_remover))
// para isso faz uma busca no set para checar se ele exista
bool set_remover(SET *s, int elemento){
	
	if(s == NULL) return 0 ; 

	if(!set_pertence(s, elemento)) return 0 ;

	return avl_remover(s->T, elemento) ;

}

// função para desalocar a memória do SET após o uso - chama o TAD AVL para desalocar a AVL 
// os nós e itens utilizados por ela 

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

// retorna um set (uniao) que é a união de todos os elementos contidos
// nos sets A e B dados 
// adicionamos cada elemento no set final, indo elemento por elemento 
SET *set_uniao(SET *A, SET *B){

	SET *uniao = set_criar() ; 

	avl_adicionar_elementos(&(uniao->T), A->T) ;
	avl_adicionar_elementos(&(uniao->T), B->T) ;

	return uniao ; 
}

// retorna um set que contem os elementos comuns dos sets A e B 
// percorremos a menor avl checando se o 
// elemento está contido também na maior avl para que fique mais rápido
// comum, set retornado, representa a intersecção dos SET A e SET B 
SET *set_interseccao(SET *A, SET *B){

	SET *comum = set_criar() ;

	if(avl_get_size(A->T) > avl_get_size(B->T)) avl_comum(&(comum->T), A->T, B->T) ;
	else avl_comum(&(comum->T), B->T, A->T) ;

	return comum ;

}
