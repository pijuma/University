#include "lista.h"

int main(){

    int n ; scanf("%d", &n) ;
    
    LISTA *lista = criar() ;

    for(int i = 1  ; i <= n ; i++){
        int b ; scanf("%d", &b) ; 
        ITEM *at = item_criar(b) ;
        if(!lista_inserir(lista, at)) return 0 ; 
    }

    lista_imprime(lista) ; 

    int p ; scanf("%d", &p) ;

    ITEM *o = item_criar(p) ;

    lista_find(lista, o) ;

}
