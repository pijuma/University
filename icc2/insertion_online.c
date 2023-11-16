#include<stdio.h>
#include<stdbool.h>

int main(){

    int n ; scanf("%d", &n) ; 

    int v[n+2] ;

    for(int i = 0 ; i < n ; i++){
        int a ; scanf("%d", &a) ;
        int j = i-1 ; // posição que irei inserir é j + 1 inicialmente 
        while(j >= 0 && v[j] > a){
            v[j+1] = v[j] ; j-- ; //desloco tudo - abrir espaço 
        }
        v[j+1] = a ;
    }

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ;
    printf("\n") ; 

}
