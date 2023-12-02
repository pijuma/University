#ifndef AVL_H 
    #define AVL_H 

    #include <stdio.h> 
    #include <stdlib.h> 
    #include <stdbool.h>
    #include "item.h" 

    typedef struct AVL_ AVL ; 

    AVL *criar_avl() ;
    void apagar_avl(AVL **a) ;
    bool remover_avl(AVL *a, int chave) ; 
    bool inserir_avl(AVL *a, ITEM *item) ; 
    bool buscar_avl(AVL *a, int chave) ;
    void percurso_avl(AVL *a) ; 
    //bool ta_ok(AVL *a);

#endif 
