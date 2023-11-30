#ifndef ABB_H
    
    #define ABB_H 
    
    #include "item.h"
    #include<stdio.h> 
    #include<stdlib.h>
    #include<stdbool.h>

    typedef struct ABB_ abb ; 

    abb *ab_criar(); 
    bool ab_rem(abb *T, int chave);
    bool ab_inserir(abb*T, ITEM *item);
    bool ab_remover(abb*T, int chave);
    ITEM *abb_busca(abb *T, int chave);
    void ab_apagar_arvore(abb **T);
    void percurso(abb *T);

#endif
