#ifndef LISTA_H
    #define LISTA_H
    
    #include "item.h"

    typedef struct SKIP_L SKIP ; 
          
    SKIP *skip_criar();
    ITEM *skip_busca_key(SKIP *skip, char *pal);
    bool skip_inserir(SKIP *skip, ITEM *a);
    void imprime_skip(SKIP *skip);
    bool skip_alterar(SKIP *skip, ITEM *a);
    bool skip_remover(SKIP *skip, char *a);
    bool skip_imprime_char(SKIP *skip, char a);
    void skip_apagar(SKIP **skip);
    
#endif
