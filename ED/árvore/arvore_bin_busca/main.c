#include "abb.h"

int main(){

    abb *T = ab_criar() ;

    int n ; scanf("%d", &n) ;

    for(int i = 1 ; i <= n ; i++){
        int a ; scanf("%d", &a) ; 
        ITEM *at = item_criar(a) ; 
        ab_inserir(T, at) ; 
    }

    percurso(T) ;
    
    for(int i = 1 ; i <= n ; i++){
        char t ; scanf(" %c", &t) ;
        int a ; scanf("%d", &a) ; 
        if(t == 'a'){
            ab_remover(T, a) ;
        }
        else{
            ITEM *at = abb_busca(T, a) ; 
            if(at != NULL) printf("deu bom\n") ; 
            else printf("deu ruim\n") ;
        }
    }

    ab_apagar_arvore(&T) ; 

}
