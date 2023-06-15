#include<stdio.h>
#include<stdlib.h> 

void al(int n, double *(*p)){ 
    *p = (double *) malloc(n*sizeof(double)) ;
    return ; 
}

void leia(int n, double *(*p)){

    al(n, p) ;

    for(int i = 0 ; i < n ; i++) scanf("%lf", &((*p)[i])) ;

    return ; 

}

void escreva(double *(*p), int n){

    for(int i = 0 ; i < n ; i++) printf("%lf ", (*p)[i]) ;
    printf("\n") ;

}

int main(){

    int n ; scanf("%d", &n) ;
    
    double *p ; 
    leia(n, &(p)) ;

    escreva(&(p), n) ;

    free(p) ;

}
