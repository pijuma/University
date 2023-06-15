#include<stdio.h>
#include<stdlib.h> 

double *alloca(int n){ return (double *) malloc(n*sizeof(double)) ; }

double *leia(int n){

    double *p = alloca(n) ;

    for(int i = 0 ; i < n ; i++) scanf("%d", &p[i]) ;

    return p ; 

}

void escreva(double *p, int n){

    for(int i = 0 ; i < n ; i++) printf("%d ", p[i]) ;
    printf("\n") ;

}

int main(){

    int n ; scanf("%d", &n) ;
    
    double *p = leia(n) ;

    escreva(p, n) ;

    free(p) ;

}
