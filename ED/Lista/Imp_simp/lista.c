#include "lista.h" 

struct lista_{
    ITEM *list[maxn] ;
    int ini, fim ; 
} ;

LISTA *criar(){

    LISTA *a = (LISTA *) malloc(sizeof(LISTA)) ;
    
    if(a != NULL) a -> ini = 0, a -> fim = 0 ; 

    return a ; 

}

bool lista_inserir(LISTA *lista, ITEM *a){ // insere no fim
    
    if(lista != NULL && !lista_cheia(lista)){
        lista->list[lista->fim] = a ; 
        lista->fim++ ; 
        return 1 ; 
    }
    
    return 0 ; 

}

ITEM *lista_remove(LISTA *lista, int pos){ // tira do começo 
    
    if(lista != NULL && !lista_vazia(lista)){
        ITEM *b = lista->list[lista->ini] ;
        lista->list[lista->ini] = NULL ; 
        for(int i = lista->ini + 1 ; i < lista->fim; i++) lista->list[i-1] = lista->list[i] ;
        lista->fim-- ; 
        return b ;
    }

    return NULL ; 

}

int lista_tamanho(LISTA *a){ 
    if(a != NULL) return (a -> fim) - (a -> ini) ;
    return -1 ; 
}

bool lista_vazia(LISTA *a){ 
    if(a != NULL) return (a->fim == 0) ; 
    return 0 ; 
}

bool lista_cheia(LISTA *a){ 
    if(a != NULL) return lista_tamanho(a) == maxn ;
    return NULL ; 
}

void lista_imprime(LISTA *a){
    if(a == NULL) return ; 
    for(int i = a->ini ; i < a->fim ; i++) item_imprimir(a->list[i]) ; 
}

void lista_find(LISTA *list, ITEM *a){
    if(list == NULL || lista_vazia(list)){
        printf("Nao tem como achar") ;
        return ; 
    } 
    for(int i = list->ini ; i < list-> fim ; i++) {
        if(valor(list->list[i]) == valor(a)){
            printf("Tem esse valor %d", valor(list->list[i])) ; 
            return ; 
        }
    }
    printf("Nao tem esse valor\n") ;
}
    
