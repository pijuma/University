#include<stdio.h>
#include<stdlib.h>

void alocar(int n, int m, int *(**p)){
    *p = malloc(sizeof(int *)*n) ; 
    for(int i = 0 ; i < n ; i++) (*p)[i] = (int *) malloc(m*sizeof(int)) ;  
}

void leia(int n, int m, int *(**p)){ // ponteiro p matriz 

   alocar(n, m, p) ;

   for(int i = 0 ; i < n ; i++){
       for(int j = 0 ; j < m ; j++){
           scanf("%d", &(*p)[i][j]) ; 
       }
   }

}

void escreva(int n, int m, int *(**p)){

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            printf("%d ", (*p)[i][j]) ; 
        }
        printf("\n") ; 
    }

}

int main(){

    // alterar matriz 

    int n, m ; scanf("%d%d", &n, &m) ; 

    int **p ; 

    leia(n, m, &p) ; 

    escreva(n, m, &p) ; 

    for(int i = 0 ; i < n ; i++) free(p[i]) ;
    free(p) ; 

}
