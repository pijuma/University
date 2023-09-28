// fazer o insertion_sort enquanto le os valores 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main(){

    int t; scanf("%d", &t) ; 

    int a; scanf("%d", &a) ; 

    int *v ; v = (int *) malloc(sizeof(int *) * t) ; 

    v[0] = a ; 

    printf("-1\n") ; 

    for(int i = 1 ; i < t ; i++){
        int at ; scanf("%d", &at); 
        int j = i-1 ; 
        while(j >= 0 && at < v[j]){
            v[j+1] = v[j] ; j-- ; 
        }
        v[j+1] = at ;   
        if(i-2 >= 0){
            printf("%d %d %d\n", v[i], v[i-1], v[i-2]) ; 
        }
        else printf("-1\n") ; 
    }

} 
