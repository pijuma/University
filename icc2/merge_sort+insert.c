#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void insert_sort(int *v, int t){

    for(int i = 1 ; i < t ; i++){
        int valor_at = v[i] ; 
        int j = i-1 ; // supoe q ta ordenado p antes do kra
        while(j >= 0 && valor_at < v[j]){// enquanto tiver kra antes de mim maior que o meu eu passo esses p frente
            v[j+1] = v[j] ;
            j-- ; 
        }
        v[j+1] = valor_at ; // me add na 1a pos em q n tem ng maior q mim antes de mim 
    }

    for(int i = 0 ; i < t ; i++) printf("%d ", v[i]) ; 
    printf("\n") ; 

}

void merge_sort(int *v, int t, int k){

    if(t <= k){
        insert_sort(v, t) ; return ; 
    }

    int *ve, *vd ; // novos vetores 
    int mid = t/2 ; 
    int tame = mid, tamd = t-mid ; 

    ve = (int *) malloc(tame*sizeof(int *)) ; 
    vd = (int *) malloc(tamd*sizeof(int *)) ; 

    for(int i = 0 ; i < tame ; i++) ve[i] = v[i] ; 
    for(int i = 0 ; i < tamd ; i++) vd[i] = v[i+tame] ; 

    merge_sort(ve, tame, k) ; merge_sort(vd, tamd, k) ; 

    int pte = 0, ptd = 0 ; 

    for(int i = 0 ; i < t ; i++){
        if(pte >= tame){// coloca dir
            v[i] = vd[ptd] ; ptd++ ; 
        }
        else if(ptd >= tamd){
            v[i] = ve[pte] ; pte++ ; 
        }
        else{
            if(ve[pte] <= vd[ptd]){
                v[i] = ve[pte] ; pte++ ; 
            }
            else{
                v[i] = vd[ptd] ; ptd++ ; 
            }
        }
    }

    return ;

}

int main(){

    int n ; scanf("%d", &n) ; 
    int *v ; v = (int *) malloc(sizeof(int *) *n ) ; 

    for(int i = 0 ; i < n ; i++) scanf("%d", &v[i]) ; 

    int k ; scanf("%d", &k) ; 

    merge_sort(v, n, k) ; 

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ; 
    printf("\n") ; 

}
