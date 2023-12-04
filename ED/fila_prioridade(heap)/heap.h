#ifndef HEAP_H 
    #define HEAP_H 

    #include<stdbool.h> 
    #include<stdlib.h> 
    #include<stdio.h> 
    #include "item.h" 

    #define maxn 100005
    typedef struct heap_ HEAP ; 

    HEAP *heap_criar() ;
    int heap_cheia(HEAP *h) ; 
    int heap_vazia(HEAP *h) ; 
    int heap_inserir(HEAP *h, ITEM *item) ; 
    int heap_remover(HEAP *h) ;
    int topo(HEAP *h) ;
    void show(HEAP *h) ; 
    
#endif 
