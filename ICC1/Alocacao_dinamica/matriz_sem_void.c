#include<stdio.h>
#include<stdlib.h>


int **leia(int n, int m){

    int **p = (int **) malloc(sizeof(int *)*n) ; 
    for(int i = 0 ; i < n ; i++) p[i] = (int *) malloc(sizeof(int)*m) ; 

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++) scanf("%d", &p[i][j]) ; 
    }

    return p ; 

}

void escreve(int n, int m, int **p){

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++) printf("%d ", p[i][j]) ; 
        printf("\n") ;  
    }

}

void limpar(int n, int *(**p)){
    
    for(int i = 0 ; i < n ; i++) free((*p)[i]) ; 
    free(*p) ; 

}

int main(){

    // alterar matriz 

    int n, m ; scanf("%d%d", &n, &m) ; 

    int **p = leia(n, m) ; 

    escreve(n, m, p) ; 

    limpar(n, &p) ; 

}
