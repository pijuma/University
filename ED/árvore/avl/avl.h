#ifndef AVL_H
	#define AVL_H
	
	#include <stdio.h>
	#include <stdlib.h> 
	#include <stdbool.h>
	#include "item.h"

	typedef struct AVL_ AVL ;

	AVL *avl_criar() ; 
	void apagar_avl(AVL **T) ; 
	bool avl_remover(AVL *T, int chave) ; 
	bool avl_inserir(AVL *T, ITEM *item) ; 
	bool avl_buscar(AVL *T, int chave) ; 
	void avl_dfs(AVL *T) ; 

#endif
