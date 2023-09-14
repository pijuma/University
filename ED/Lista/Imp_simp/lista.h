#ifndef LISTA_h
    
    #define LISTA_h
    #include "item.h"
    #include<stdbool.h> 
    #include<stdlib.h>
    #include<stdio.h>
    #define maxn 20004 

    typedef struct lista_ LISTA ; 
    
    LISTA *criar() ; 
    bool lista_inserir(LISTA *lista, ITEM *a) ;
    ITEM *lista_remove(LISTA *lista, int pos) ;
    int lista_tamanho(LISTA *a) ;
    bool lista_vazia(LISTA *a); 
    bool lista_cheia(LISTA *a); 
    void lista_imprime(LISTA *a);
    void lista_find(LISTA *list, ITEM * a);

#endif
