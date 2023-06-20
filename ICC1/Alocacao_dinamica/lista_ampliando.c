#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

int maior(char *a, char *b){ // a eh maior que b ? 
    
    int len = strlen(a) ;
    if(len > strlen(b)) len = strlen(b) ;

    for(int i = 0 ; i < len ; i++){
        if(a[i] == b[i]) continue ; 
        if(a[i] > b[i]) return 1 ; 
        return 0 ; 
    }

    return 0 ; 

}

void troca(char *(*a), char *(*b)){
    char *tmp = *a ; 
    *a = *b ; 
    *b = tmp ; 
}

int main(){

    char **p = NULL ; 

    int at = 0 ; 

    while(1){
        
        p = (char **) realloc(p, (at+1)*sizeof(char *)) ;

        p[at] = NULL ; 
        
        int j = 0 ; 

        for(j = 0 ; 1 ; j++){
            char o ; scanf("%c", &o) ;
            //printf("%c\n", o) ;
            if(o == '\n') break ; 
            p[at] = (char *) realloc(p[at], (j+1)*sizeof(char)) ;
            p[at][j] = o ; 
        }
 
        p[at] = (char *) realloc(p[at], (j+1)*sizeof(char)) ; 
        p[at][j] = '\0' ; 
        //printf("%s\n", p[at]) ;

        if(!strcmp(p[at], "sair")) break ; 
        at++ ; 
 
    }

    // vetor vai de 0 ate at-1
    // ordenar ele 

    while(1){
        int ord = 1 ; //supoe ordenado 
        for(int i = 0 ; i < at - 1 ; i++){
            if(maior(p[i], p[i+1])){
                troca(&p[i], &p[i+1]) ; ord = 0 ; 
            }
        }
        if(ord) break ; 
    }
    
    for(int i = 0 ; i < at ; i++) printf("%d) %s\n", i+1, p[i]) ; 

}
