#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void buble(int *v, int n){

    while(1){
        bool ord = 1 ; 
        for(int i = 1 ; i < n ; i++){
            if(v[i+1] < v[i]){
                int t = v[i] ; 
                v[i] = v[i+1] ; 
                v[i+1] = t ; 
                ord = 0 ; 
            }
        }
        if(ord) break ; 
    }
    
}

int main(){

    int n ; scanf("%d", &n) ; 

    int v[n+5] ; 

    for(int i = 1 ; i <= n ; i++) scanf("%d", &v[i]) ; 

    buble(v, n) ; 

}
