#ifndef ITEM_H 
    #define ITEM_H 
    // TAD item padrão 
    typedef struct item_ ITEM ;

    ITEM *item_criar (char pal[], char sig[]) ;

    int item_apagar(ITEM **item) ;

    char *item_get_key(ITEM *item) ;
    char *item_get_verb(ITEM *item) ;
    void item_imprimir_key(ITEM *a);
    void item_imprimir_verb(ITEM *a);
    int item_set_verb(ITEM *item, char *sig) ;
        
    
#endif
