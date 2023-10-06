#include "lista.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 

int main(){

    SKIP *lista = skip_criar();
    int n ; scanf("%d", &n) ; 

    for(int i = 0 ; i < n ; i++){
        char a[55], b[145] ;
        scanf(" %s", a) ; 
        scanf(" %[^\n]s", b) ;
        printf("%s %s\n", a, b) ; 
        ITEM *at = item_criar(a, b) ;
        skip_inserir(lista, at) ;
    }
    
    //imprime_skip(lista) ; 
    
    char c[55] ;
    scanf(" %s", c) ; 
    ITEM *r = skip_busca_key(lista, c) ;
    if(r == NULL) printf("Nao achei\n") ; 
    else{
        char *resp = item_get_verb(r) ;
        printf("%s\n", resp) ; 
    }

    char d[145] ;
    scanf(" %s", d) ;
    ITEM *neww = item_criar(c, d) ;
    skip_alterar(lista, neww) ;  
    
    r = skip_busca_key(lista, c) ;
    if(r == NULL) printf("Nao achei\n") ; 
    else{
        char *resp = item_get_verb(r) ;
        printf("%s\n", resp) ; 
    }

}
