#include "avl.h"

#define max(a, b) (a > b ? a : b)
#define DEU_RUIM -1000000 

struct NO_{
	ITEM *item ; 
	struct NO_ *esq, *dir ; 
	int altura ; // maior dist pra uma folha 
} ; 

typedef struct NO_ NO ;

struct AVL_{
	NO *raiz ; 
} ;

/*funções auxiliares*/
int get_altura(NO *node){
	if(node == NULL) return -1 ; // nó nulo tem altura -1  
	return node->altura ; 
}

// função retorna o fator de balanceamento pro node 
// h(esq) - h(dir)
int fb(NO *node){
	if(node == NULL) return DEU_RUIM ;
	return get_altura(node->esq) - get_altura(node->dir) ; 
}

void apagar_no(NO **a){
	item_apagar(&((*a)->item)) ;
	free(*a) ; *a = NULL ;
}

NO *no_criar(ITEM *it){
	NO *node = (NO *) malloc(sizeof(NO)) ; 
	if(node == NULL) return NULL ; 
	node->item = it ; 
	node->esq = NULL ; node->dir = NULL ; 
	node->altura = 0 ; 
	return node ;  
} 

/*funções para auxiliar a manutenção do balanceamento*/

NO *rodar_esq(NO *A){
	NO *B = A->dir ; 
	A->dir = B->esq ; 
	B->esq = A ;
	A->altura = max(get_altura(A->esq), get_altura(A->dir)) + 1 ;  
	return B ; 
}

NO *rodar_dir(NO *A){
	NO *B = A->esq ; 
	A->esq = B->dir ;
	B->dir = A ;
	A->altura = max(get_altura(A->esq), get_altura(A->dir)) + 1 ;  
	return B ;  
}

NO *rodar_esq_dir(NO *A){
	A->esq = rodar_esq(A->esq) ;
	return rodar_dir(A) ; 
}

NO *rodar_dir_esq(NO *A){
	A->dir = rodar_dir(A->dir) ; 
	return rodar_esq(A) ; 
}

NO *troca_max_esq(NO *rem, NO *troca, NO *ant){

	while(troca->dir != NULL){
		ant = troca ; 
		troca = troca -> dir ; 
	}

	if(rem == ant) ant->esq = troca->esq ;  
	else ant->dir = troca->esq ; 

	item_set_chave(rem->item, item_get_chave(troca->item)) ; 
	
	apagar_no(&troca) ; 

	return rem ; 

}

AVL *avl_criar(){

	AVL *T = (AVL *) malloc(sizeof(AVL)) ; 

	if(T != NULL){
		T -> raiz = NULL ; 
	}

	return T ; 

} 
 
NO *avl_remover_no(NO **node, int chave){

	if(*node == NULL) return NULL ; 

	if(item_get_chave((*node)->item) == chave){
		
		// no max 1 filho 

		if((*node)->esq == NULL || (*node)->dir == NULL){
			
			NO *removed = (*node) ;
			
			if((*node)->dir == NULL) (*node) = (*node)->esq ; 
			else (*node) = (*node)->dir ; 

			free(removed) ; removed = NULL ;  
		}

		else (*node) = troca_max_esq((*node), (*node)->esq, (*node)) ; // removido (raiz), troca, anterior (do troca) 

	}

	else if(item_get_chave((*node)->item) < chave) (*node)->dir = avl_remover_no(&(*node)->dir, chave) ; 

	else if(item_get_chave((*node)->item) > chave) (*node)->esq = avl_remover_no(&(*node)->esq, chave) ; 

	if(*node == NULL) return *node ; 

	(*node)->altura = max(get_altura((*node)->esq), get_altura((*node)->dir)) + 1 ; 

	if(fb(*node) == 2){
		if(fb((*node)->esq) < 0) (*node) = rodar_esq_dir((*node)) ; 
		else (*node) = rodar_dir((*node)) ; 
	}

	else if(fb(*node) == -2){
		if(fb((*node)->dir) > 0) (*node) = rodar_dir_esq((*node)) ; 
		else (*node) = rodar_esq(*node) ; 
	}

	return *node ; 


}

bool avl_remover(AVL *T, int chave){

	if(T == NULL) return 0 ; 
	
	T->raiz = avl_remover_no(&(T->raiz), chave) ; 

	return 1 ; 
} 

NO *avl_inserir_no(NO *node, NO *novo){

	if(node == NULL) node = novo ;
	else if(item_get_chave(node->item) < item_get_chave(novo->item)) node->dir = avl_inserir_no(node->dir, novo) ;
	else if(item_get_chave(node->item) > item_get_chave(novo->item)) node->esq = avl_inserir_no(node->esq, novo) ;

	node -> altura = max(get_altura(node->esq), get_altura(node->dir)) + 1 ; 

	// REBALANCEAR! 

	// rotação direita ou rotação esquerda/direita
	if(fb(node) == 2){
		if(item_get_chave(node->esq->item) < item_get_chave(novo->item)) node = rodar_esq_dir(node) ; 
		else node = rodar_dir(node) ;  
	}

	else if(fb(node) == -2){
		if(item_get_chave(node->dir->item) > item_get_chave(novo->item)) node = rodar_dir_esq(node) ; 
		else node = rodar_esq(node) ; 
	}

	return node ; 

}

bool avl_inserir(AVL *T, ITEM *item){

	if(T == NULL) return 0 ; 

	NO *novo = no_criar(item) ; 

	if(novo != NULL){
		T->raiz = avl_inserir_no(T->raiz, novo) ; 
		return 1 ;
	}

	return 0 ; 

} 

bool buscar_avl_no(NO *node, int chave){
	
	if(node == NULL) return 0 ; 

	if(item_get_chave(node->item) == chave) return 1 ; 

	if(item_get_chave(node->item) < chave) return buscar_avl_no(node->dir, chave) ;
	else return buscar_avl_no(node->esq, chave) ;

} 

bool avl_buscar(AVL *T, int chave){
	if(T == NULL) return 0 ; 
	return buscar_avl_no(T->raiz, chave) ; 
} 

// imprime o percurso em-ordem 

void dfs(NO *node){
	
	if(node == NULL) return ; 

	dfs(node->esq) ; 
	printf("%d altura %d\n", item_get_chave(node->item), get_altura(node)) ;
	dfs(node->dir) ; 

}

void avl_dfs(AVL *T){
	if(T == NULL) return ; 
	dfs(T->raiz) ; 
}

/*funções para desalocar memória*/
// função para apagar os nós recursivamente 
void apagar_avl_no(NO **node){
	
	if(*node == NULL) return ; 
	
	apagar_avl_no(&(*node)->esq) ; apagar_avl_no(&(*node)->dir) ;
	item_apagar(&(*node)->item) ; 
	
	free(*node) ; *node = NULL ; 

}

// função para apagar a avl
void apagar_avl(AVL **T){
	
	if(*T == NULL) return ; 
	
	apagar_avl_no(&(*T)->raiz) ; 
	
	free(*T) ; *T = NULL ; 

}
