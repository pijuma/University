#include<stdlib.h>
#include<stdio.h>

void merge(int t1, int p1, int *v1, int t2, int p2, int *v2, int *r){
    if(p1 == t1 && p2 == t2) return ; 
    if(p1 == t1){ // terminamos o 1o vetor 
        r[p2+p1] = v2[p2] ;
        merge(t1, p1, v1, t2, p2+1, v2, r) ;
    }
    else if(p2 == t2){
        r[p1+p2] = v1[p1] ;
        merge(t1, p1 + 1, v1, t2, p2, v2, r) ;
    }
    else{
        if(v1[p1] < v2[p2]){//colocar p1 
            r[p1+p2] = v1[p1] ;
            merge(t1, p1 + 1, v1, t2, p2, v2, r) ;
        }
        else{//colocar p2 
            r[p2+p1] = v2[p2] ;
            merge(t1, p1, v1, t2, p2+1, v2, r) ;
        }
    }
    return ; 
}

int main(){

    int n1, n2 ; scanf("%d %d", &n1, &n2) ; 
    int *arr1 = NULL, *arr2 = NULL, *resp = NULL ; 
    
    arr1 = (int *) malloc(sizeof(int)*n1); 
    arr2 = (int *) malloc(sizeof(int)*n2) ; 
    resp = (int *) malloc(sizeof(int)*(n1+n2)) ;

    for(int i = 0 ; i < n1 ; i++) scanf("%d", &arr1[i]) ; 
    for(int i = 0 ; i < n2 ; i++) scanf("%d", &arr2[i]) ;

    merge(n1, 0, arr1, n2, 0, arr2, resp) ;

    for(int i = 0 ; i < n2 + n1 ; i++) printf("%d ", resp[i]) ; 

    free(arr1) ; free(arr2) ; free(resp) ;
    arr1 = arr2 = resp = NULL ; 

}
