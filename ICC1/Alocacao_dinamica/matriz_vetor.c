// alocar matriz como vetor 
#include<stdio.h>
#include<stdlib.h>

int main(){

    int n, m ; scanf("%d%d", &n, &m) ;

    int *v ; 

    v = (int *) malloc(n*m*sizeof(int)) ;

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++) scanf("%d", &v[(i*m) + j]) ;
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++) printf("%d ", v[(i*m) + j]) ;
        printf("\n") ;
    }

}
