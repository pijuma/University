#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>

void shell_sort(int *v, int n){

    int h = 1 ; 

    for(h = 1 ; h < n ; h = (h*3) + 1) ; 

    while(h > 0){
        h = (h-1)/3 ; 
        for(int i = 1 ; i < n ; i++){
            int valor_at = v[i] ; 
            int j = i ; // considera q ate j ta ordenado 
            while(v[j-h] > valor_at){ // se eu achar algum kra antes de mim q eh maior q o meu ele tem q vir dps 
                v[j] = v[j-h] ; // passo ele p frente 
                j-=h ; 
                if(j < h) break ;
            }
            v[j] = valor_at ; 
        }
    }

}

int main(){

    int n ; scanf("%d", &n) ; 

    int v[n+5] ;
    for(int i = 0 ; i < n ; i++) scanf("%d", &v[i]);

    shell_sort(v, n) ;

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ;
    printf("\n");   
     
}
