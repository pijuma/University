#include <stdlib.h>
#include <stdio.h>
#include<string.h> 
#include "item.h"

// TAD Item 
// a principal alteração feita foi em relação a struct que agora guarda
// a palavra e o significado dela 

struct item_{ 
    char key[52], verb[142] ;
};

ITEM *item_criar (char pal[], char sig[]){
    
    ITEM *a = (ITEM * ) malloc(sizeof(ITEM)) ;
    
    if(a != NULL){
        strcpy((a->key), pal) ;
        strcpy((a->verb), sig);
    }
    
    return a ; 

}

int item_apagar(ITEM **item){
    
    if(*item != NULL){ 
        free(*item) ;
        *item = NULL ;
        return 1 ; 
    }
    
    return 0 ; 

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

int item_set_verb(ITEM *item, char *sig){

    if(item != NULL){
        strcpy(item->verb, sig); 
        return 1 ; 
    }

    return 0 ; 

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
