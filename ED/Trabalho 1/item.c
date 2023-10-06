#include <stdlib.h>
#include <stdio.h>
#include<string.h> 
#include "item.h"

struct item_{ 
    char key[55], verb[145] ;
};

ITEM *item_criar (char pal[], char sig[]){
    
    ITEM *a = (ITEM * ) malloc(sizeof(ITEM)) ;
    
    if(a != NULL){
        strcpy((a->key), pal) ;
        strcpy((a->verb), sig);
    }
    
    return a ; 

}

bool item_apagar(ITEM **item){
    
    if(*item != NULL){ 
        free(*item) ;
        *item = NULL ;
        return true ; 
    }
    
    return false ; 

}

char *item_get_key(ITEM *item){ // retorna a palavra 
    if(item != NULL){
        return item -> key ; 
    }
    exit(1) ; // cuidado para nao dar BO  
}

char *item_get_verb(ITEM *item){ // retorna o significado 
    if(item != NULL){
        return item -> verb ; 
    }
    exit(1) ; // cuidado para nao dar BO  
}

bool item_set_verb(ITEM *item, char *sig){

    if(item != NULL){
        strcpy(item->verb, sig); 
        return true ; 
    }

    return false ; 

}

void item_imprimir_key(ITEM *a){

    if(a == NULL){
        printf("OPERACAO INVALIDA\n") ; 
    }

    else{
        printf("%s\n", a->key) ;
    }

}

void item_imprimir_verb(ITEM *a){

    if(a == NULL){
        printf("OPERACAO INVALIDA\n") ; 
    }

    else{
        printf("%s\n", a->verb) ;
    }

}
