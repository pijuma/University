#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void troca(int *v, int a, int b){
    int t = v[a] ;
    v[a] = v[b] ; 
    v[b] = t ;  
}

int partition(int *v, int l, int r, int pivot){

    while(l <= r){

        while(l <= r && v[l] < pivot) l++ ; // preciso achar o cara a esq maior q o pivot 

        while(l <= r && v[r] > pivot) r-- ; // preciso achar o kra a dir q eh menor q o pivot

        if(l <= r){ // vou trocar os 2 kras 
            troca(v, l, r) ; 
            l++ ; r-- ; 
        }

    }

    return l ; // onde parou eh onde vou fzr a partição 

}

void quick(int *v, int ini, int fim){

    if(ini >= fim) return ; 

    int p = (ini + fim)/2 ; 

    int pivot = v[p] ; 
    int part_id = partition(v, ini, fim, pivot) ; 

    quick(v, ini, part_id - 1) ; quick(v, part_id, fim) ;

}

int main(){

    int n ; scanf("%d", &n) ; 

    int v[n+5] ; 

    for(int i = 0 ; i < n ; i++) scanf("%d", &v[i]) ; 

    quick(v, 0, n-1) ; 

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ; 
    printf("\n") ; 

}
