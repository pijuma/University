#ifndef PILHA_H
	#define PILHA_H 
    
    #include <stdbool.h>
    #include "item.h"
    #define maxn (int)(20005) 

    typedef struct pilha_ PILHA ; 

    PILHA *pilha_criar() ; 

    bool pilha_apagar(PILHA **pilha) ; 

    ITEM *top(PILHA *pilha) ; 

    ITEM *pop(PILHA *pilha) ; 

    bool push(PILHA *pilha, ITEM *x) ; 

    int pilha_tamanho(PILHA *pilha) ; 

    bool pilha_vazia(PILHA *pilha) ;
    bool pilha_cheia(PILHA *pilha) ; 


#endif 
