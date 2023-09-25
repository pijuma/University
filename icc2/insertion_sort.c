#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>

void insert_sort(int *v, int n){

    for(int i = 1 ; i < n ; i++){
        int valor_at = v[i] ; 
        int j = i-1 ; // considera q ate j ta ordenado 
        while(j >= 0 && v[j] > valor_at){ // se eu achar algum kra antes de mim q eh maior q o meu ele tem q vir dps 
            v[j+1] = v[j] ; // passo ele p frente 
            j-- ; 
        }
        v[j+1] = valor_at ; 
    }

}

int main(){

    int n ; scanf("%d", &n) ; 

    int v[n+5] ;
    for(int i = 0 ; i < n ; i++) scanf("%d", &v[i]);

    insert_sort(v, n) ;

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ;
    printf("\n");   
     
}
