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
