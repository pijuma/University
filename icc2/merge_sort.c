#include<stdlib.h>
#include<stdio.h>

void merge_sort(int t1, int *v1){
    if(t1 == 1) return ; // ja ta ordenado - 1 elemento 
    int tam = t1 ; int mid = t1/2 ; 
    int *ve, *vd ; 
    int tame = mid, tamd = tam-mid ;
    ve = (int *) malloc(sizeof(int)*tame) ;
    vd = (int *) malloc(sizeof(int)*tamd) ;
    for(int i = 0 ; i < mid ; i++) ve[i] = v1[i] ;
    for(int i = mid, j = 0 ; i < tam ; i++, j++) vd[j] = v1[i] ;
    merge_sort(tame, ve) ; merge_sort(tamd, vd) ;
    int pte = 0, ptd = 0 ; 
    for(int i = 0 ; i < tam ; i++){
        if(pte >= tame){ // colocar ptd
            v1[i] = vd[ptd] ; ptd++ ; 
        }
        else if(ptd >= tamd){
            v1[i] = ve[pte] ; pte++ ; 
        }
        else{
            if(ve[pte] < vd[ptd]){
                v1[i] = ve[pte] ; pte++ ; 
            }
            else{
                v1[i] = vd[ptd] ; ptd++ ; 
            }
        }
    } 
    return ; 
}

int main(){

    int n1; scanf("%d", &n1) ; 
    int *arr1 = NULL; 
    
    arr1 = (int *) malloc(sizeof(int)*n1); 

    for(int i = 0 ; i < n1 ; i++) scanf("%d", &arr1[i]) ; 

    merge_sort(n1, arr1) ;

    for(int i = 0 ; i < n1 ; i++) printf("%d ", arr1[i]) ; 

    free(arr1) ; 
    arr1 = NULL ; 

}

#include<stdio.h>
#include<stdlib.h>

void merge(int t, int *v){

    if(t == 1) return ; 
    
    int mid = (t)>>1 ; 
    int tame = mid, tamd = (t-mid) ; 

    int ve[tame+2], vd[tamd+2] ; 
    
    for(int i = 1 ; i <= mid ; i++) ve[i] = v[i] ;
    for(int i = mid + 1 ; i <= t ; i++) vd[i-mid] = v[i] ;

    merge(tame, ve) ; merge(tamd, vd) ; 

    int pte = 1, ptd = 1 ; 

    for(int i = 1 ; i <= t ; i++){
        if(ptd > tamd){
            v[i] = ve[pte++] ;
        }
        else if(pte > tame) v[i] = vd[ptd++] ;
        else{
            if(ve[pte] >= vd[ptd]) v[i] = vd[ptd++] ;
            else v[i] = ve[pte++] ;
        }
    }

}

int main(){

    int n ; scanf("%d", &n) ; 
    
    int v[n+3] ;

    for(int i = 1 ; i <= n ; i++) scanf("%d", &v[i]) ;

    merge(n, v) ; 

    for(int i =1  ; i <= n ; i++) printf("%d ", v[i]) ;
    printf("\n") ;

}
