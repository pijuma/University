#include "avl.h"

int main(){

    int n; scanf("%d", &n) ; 
    
    AVL *avl = criar_avl() ;

    for(int i = 1 ; i <= n ; i++){
        int a ; scanf("%d", &a) ; 
        ITEM *at = item_criar(a) ; 
        inserir_avl(avl, at) ; 
    }

    printf("OI\n") ;

    percurso_avl(avl) ; 

    //printf("tudo certo? %d\n", ta_ok(avl)) ;
    //printf("Oi\n") ;

    for(int i = 1 ; i <= n ; i++){
        char c ; scanf(" %c", &c) ; 
        int a ; scanf("%d", &a) ; 
        if(c == 'a'){
            remover_avl(avl, a) ; 
            percurso_avl(avl) ; 
        }
        else{
            printf("%d\n", buscar_avl(avl, a)) ; 
        }
    }

    percurso_avl(avl) ; 

    apagar_avl(&avl) ;

}
