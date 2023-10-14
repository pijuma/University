#ifndef LISTA_H
    #define LISTA_H
    // TAD lista padrão 
    #include "item.h"

    typedef struct SKIP_L SKIP ; 
          
    SKIP *skip_criar();
    ITEM *skip_busca_key(SKIP *skip, char *pal);
    int skip_inserir(SKIP *skip, ITEM *a);
    void imprime_skip(SKIP *skip);
    int skip_alterar(SKIP *skip, ITEM *a);
    int skip_remover(SKIP *skip, char *a);
    int skip_imprime_char(SKIP *skip, char a);
    void skip_apagar(SKIP **skip);
    
#endif
