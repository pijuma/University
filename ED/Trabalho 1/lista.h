#ifndef LISTA_H
    #define LISTA_H
    
    #include "item.h"

    typedef struct SKIP_L SKIP ; 
          
    SKIP *skip_criar();
    ITEM *skip_busca_key(SKIP *skip, char *pal);
    bool skip_inserir(SKIP *skip, ITEM *a);

#endif
