#ifndef ITEM_H 
    #define ITEM_H 
    #include <stdbool.h>

    typedef struct item_ ITEM ;

    ITEM *item_criar (char pal[], char sig[]) ;

    bool item_apagar(ITEM **item) ;

    char *item_get_key(ITEM *item) ;
    char *item_get_verb(ITEM *item) ;
    void item_imprimir_key(ITEM *a);
    void item_imprimir_verb(ITEM *a);
    bool item_set_verb(ITEM *item, char *sig) ;
        
    
#endif
