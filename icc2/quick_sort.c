#include<stdio.h>
#include<stdbool.h>

void swapa(int i, int j, int *v){
    int t = v[i] ; 
    v[i] = v[j] ; v[j] = t ; 
}

void quick_sort(int l, int r, int *v){

    if(l >= r) return ; 

    int ini = l, fim = r  ; 

    int pivot = (l+r)/2 ; pivot = v[pivot] ;

    // l eh o 1o kra maior que pivot a esquerda 
    // r eh o 1o kra menor que o pivot a direita 
    
    while(l <= r){
        while(v[l] < pivot) l++ ;
        while(v[r] > pivot) r-- ; 
        swapa(l, r, v) ; l++ ; r-- ; // troca as posições se tiver um caso que algum na esq eh maior e algum na dir menor 
    }

    // faz pro resto considerando que o piivot ta no local certo 
    quick_sort(ini, l-1, v) ; quick_sort(l + 1, fim, v) ;

}

int main(){

    int n ; scanf("%d", &n) ;

    int v[n+2] ;
    
    for(int i = 0 ; i < n ; i++) scanf("%d", &v[i]) ;

    quick_sort(0, n-1, v) ;

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ;
    printf("\n") ;
    
}
