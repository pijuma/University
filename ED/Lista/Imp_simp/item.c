#include <stdlib.h>
#include <stdio.h>
#include "item.h"

struct item_{ 
    int chave ; 
};

ITEM *item_criar (int chave){
    
    ITEM *a = NULL ; 
    a = (ITEM * ) malloc(sizeof(ITEM)) ;
    
    if(a != NULL){
        a->chave = chave ; 
        return a ; 
    }
    
    return NULL ; 

}

bool item_apagar(ITEM **item){
    
    if(*item != NULL){ 
        free(*item) ;
        *item = NULL ;
        return true ; 
    }
    
    return false ; 

}

int item_get_chave(ITEM *item){
    if(item != NULL){
        return item -> chave ; 
    }
    exit(1) ; // cuidado para nao dar BO  
}


bool item_set_chave(ITEM *item, int chave){

    if(item != NULL){
        item -> chave = chave ; 
        return true ; 
    }

    return false ; 

}

void item_imprimir(ITEM *item){
    if(item != NULL) printf("Valor %d\n", item -> chave) ;
    else printf("-1\n") ;
}

int valor(ITEM *a){ return a->chave ; }
