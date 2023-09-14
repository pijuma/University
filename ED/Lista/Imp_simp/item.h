#ifndef ITEM_H 
    #define ITEM_H 
    #include <stdbool.h>

    typedef struct item_ ITEM ;

    ITEM *item_criar (int chave) ; 

    bool item_apagar(ITEM **item) ;

    int item_get_chave(ITEM *item) ;


    bool item_set_chave(ITEM *item, int chave) ;

    void item_imprimir(ITEM *item) ;

    int valor(ITEM *item) ;
    
#endif
