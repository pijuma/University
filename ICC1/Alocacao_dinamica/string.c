// ignora as strings proibidas, printa qts vzs apareceu e o texto sem ela 
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

char tol(char a){

    if(a >= 'A' && a <= 'Z') return (a+32) ;
    return a ; 

}

int eq(char *a, char *b){
    
    for(int i = 0 ; ; i++){
        if(tol(a[i]) != tol(b[i])) return 0 ; 
        if(a[i] == '\0') break ; 
    }

    return 1 ;

}

int main(){

    char *brk ; 

    brk = NULL ; // usar aloc dinamica, inicia como null pra nao dar BO 
    //palavra que iremos ignorar
    int sz = 0 ; 

    while(1){
        char a ; scanf("%c", &a) ;
        if(a == '\n' || a == '\0' || a == '\r' || a == ' ' || a == EOF) break ; 
        brk = realloc(brk, (sz+1)*sizeof(char)) ;
        brk[sz] = a ;
        sz++ ;
    }

    // coolocar \0 p falar q acabou a palavra 
    brk = realloc(brk, (sz+1)*sizeof(char)) ;
    brk[sz] = '\0' ;

    //printf("%s\n", brk) ;

    char *txt ; txt = NULL ; int tam = 0 ; 

    char *atual ; atual = NULL ; sz = 0 ; 

    int qtd = 0 ; 

    char a ; 

    while(scanf("%c", &a) != EOF){
        
        if(a == ' ' || a == '\n' || a == '\r'){//terminei a palavra que tinha antes 
            atual = realloc(atual, (sz+1)*sizeof(char)) ;
            atual[sz] = '\0' ; 
            if(sz == 0){
                txt = realloc(txt, (tam+1)*sizeof(char)) ;
               txt[tam] = a ; 
               tam++ ;
               continue ; 
            } 
            if(!eq(atual, brk)){
               txt = (char *)realloc(txt, (tam+sz+1)*sizeof(char)) ;
               for(int j = 0 ; j < sz ; j++){
                txt[tam + j] = atual[j] ;
               } 
               //printf("\n") ;
               //printf("%s %d %d\n", atual, sz, tam) ;
               tam += sz ; 
               sz = 0 ; //nova palavra
               atual = NULL ; 
               txt = realloc(txt, (tam+1)*sizeof(char)) ;
               txt[tam] = a ; 
               tam++ ;
           }

           else{
              qtd++ ; sz = 0 ; 
              atual = NULL ; 
           } 

        }
        else{
            atual = (char *) realloc(atual, (sz+1)*sizeof(char)) ;
            atual[sz] = a ; 
            sz++ ; 
        }

    }

    if(sz != 0 && !eq(atual, brk)){
        txt = (char *)realloc(txt, (tam+sz+1)*sizeof(char)) ;
        atual = realloc(atual, (sz+1)*sizeof(char)) ;
        atual[sz] = '\0' ; 
        for(int j = 0 ; j < sz ; j++) txt[tam + j] = atual[j] ;
        //printf("%s\n", atual) ;
        tam += sz ; 
        sz = 0 ; //nova palavra
        free(atual) ; 
        atual = NULL ; 
    }

    else{
          qtd++ ; 
          free(atual) ;
          atual = NULL ; 
    }

    printf("[Palavras invasoras: %d]\n\n", qtd) ;
    for(int i = 0 ; i < tam ; i++) printf("%c", txt[i]) ;

}
