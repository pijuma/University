#include<stdio.h>

#define MAXN 450

void leia(int n, int m, int (*v)[MAXN]){
 
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            scanf("%d", &v[i][j]) ;
        }
    }
 
}
 
void trans(int n, int m, int (*v)[MAXN], int (*transposta)[MAXN]){
 
    for(int i = 1 ; i <= m ; i++){
        for(int j = 1 ; j <= n ; j++) transposta[i][j] = v[j][i] ;
    }
 
}
 
void escreva(int n, int m, int (*v)[MAXN]){

    for(int i = 1 ; i <= m ; i++){
        for(int j = 1 ; j <= n ; j++) printf("%d ", v[i][j]) ;
        printf("\n") ;
    }

}

int main(){
 
    int n, m ; scanf("%d%d", &n, &m) ;
 
    int v[MAXN][MAXN], transposta [MAXN][MAXN] ;
 
    leia(n, m, v) ;
    trans(n, m, v, transposta) ; 
    escreva(n, m, transposta) ;

    return 0 ; 
 
}
