#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 

int main(){

    char *p ; 
    p = NULL ; 
    int at = 0 ; 

    char a ;
    
    while(scanf("%c", &a) != EOF){
        p = (char *)realloc(p, (at+1)*sizeof(char)) ;
        p[at] = a ; 
        at++ ; 
    }
    
    for(int i = at - 1 ; i >= 0 ; i--) printf("%c", p[i]) ;

    printf("\n") ;

    free(p) ;

}
