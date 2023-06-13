#include<stdio.h>
#include<stdlib.h>

int **create(int n, int m){

    int **g = malloc(n*sizeof(int*)) ; // ponteiro de ponteiro - matriz - 2D

    for(int i = 0 ; i < n ; i++) g[i] = (int *) malloc(m*sizeof(int)) ;

    return g ;

}

void transposta(int **g, int **p, int n, int m){

    for(int j = 0 ; j < m ; j++){
        for(int i = 0 ; i < n ; i++) p[j][i] = g[i][j] ;
    }

}

void zera_mat(int **g, int n){

    for(int i = 0 ; i < n ; i++) free(g[i]) ;
    free(g) ;

}

int main(){

    int n, m ; scanf("%d %d", &n, &m) ;

    int **g = create(n, m) ; // ponteiro de ponteiro - matriz - 2D

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++) scanf("%d", &g[i][j]) ;
    }

    int **ot = create(m, n) ;

    transposta(g, ot, n, m) ;

    for(int i = 0  ; i < m ; i++){
        for(int j = 0 ; j < n ; j++) {
            if(ot[i][j] <= 9) printf(" %d ", ot[i][j]) ;
            else printf("%d ", ot[i][j]) ;
        }
        if(i != m-1) printf("\n") ;
    }

    zera_mat(g, n) ; zera_mat(ot, m) ;
}
