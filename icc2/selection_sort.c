#include<stdio.h>

void sort(int *v, int n){

    for(int i = 1 ; i <= n ; i++){
        for(int j = i + 1 ; j <= n ; j++){
            if(v[i] > v[j]){
                int t = v[i] ; v[i] = v[j] ; 
                v[j] = t ; 
            }
        }
    }

}

int main(){

    int n ; scanf("%d", &n) ; 

    int v[n+2] ; 

    for(int i = 1 ; i <= n ; i++) scanf("%d", &v[i]) ; 

    sort(v, n) ; 

    for(int i = 1 ; i <= n ; i++) printf("%d ", v[i]) ; 
    printf("\n") ; 

}
