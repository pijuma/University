#include <stdlib.h>
#include <stdio.h>
#include "item.h"

// TAD item padrão 
struct item_{ 
    int chave ; 
};

ITEM *item_criar (int chave){
    
    ITEM *a = (ITEM * ) malloc(sizeof(ITEM)) ;
    
    if(a != NULL){
        a->chave = chave ; 
    }
    
    return a ; 

}

bool item_apagar(ITEM **item){
    
    if(*item != NULL){ 
        free(*item) ;
        *item = NULL ;
        return 1 ; 
    }
    
    return 0 ; 

}

int item_get_chave(ITEM *item){
    if(item != NULL){
        return item -> chave ; 
    }
    else return -1 ; // cuidado para nao dar BO  
}


bool item_set_chave(ITEM *item, int chave){

    if(item != NULL){
        item -> chave = chave ; 
        return 1 ; 
    }

    return 0 ; 

}

void item_imprimir(ITEM *item){
    if(item != NULL) printf("Valor %d\n", item -> chave) ;
}