#ifndef AVL_H
	#define AVL_H
	
	#include <stdio.h>
	#include <stdlib.h> 
	#include <stdbool.h>
	#include "item.h"

	typedef struct AVL_ AVL ;

	AVL *avl_criar() ; 
	void avl_apagar(AVL **T) ; 
	bool avl_remover(AVL *T, int chave) ; 
	bool avl_inserir(AVL *T, ITEM *item) ; 
	bool avl_buscar(AVL *T, int chave) ; 
	void avl_dfs(AVL *T) ; 
	void avl_adicionar_elementos(AVL **copia, AVL *other) ; 
	AVL *avl_comum(AVL **final, AVL *maior, AVL *menor) ; 
	int avl_get_size(AVL *T) ; 

#endif