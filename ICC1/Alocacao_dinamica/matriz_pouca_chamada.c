// alocar uma matriz chamando menos vezes o malloc 
#include<stdio.h>
#include<stdlib.h>

int main(){

    int n, m ; scanf("%d%d", &n, &m) ;

    int **g, *v ; 

    g = (int **) malloc(n*sizeof(int *)) ;
    v = (int *) malloc(n*m*sizeof(int)) ;

    for(int i = 0 ; i < n ; i++) g[i] = &v[i*m] ;

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++) scanf("%d", &g[i][j]) ;
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++) printf("%d ", g[i][j]) ;
        printf("\n") ;
    }

}
