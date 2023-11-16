#include<stdio.h>
#include<stdbool.h>

void shell(int *v, int n){

    int h = 1 ; 

    // insertion eh o shell qd h = 1 sempre 

    for(; h < n ; h = (3*h) + 1) ; // calcular h inicial 

    while(h > 0){

        h = (h-1)/3 ;

        for(int i = h ; i < n ; i++){
            int aux = v[i], j = i ; 
            while(j - h >= 0 && aux < v[j-h]){
                v[j] = v[j-h] ;
                j -= h ; 
            }
            v[j] = aux ; 
        }

    }


}

int main(){

    int n ; scanf("%d", &n) ; 

    int v[n+2] ;
    
    for(int i = 0 ; i < n ; i++) scanf("%d", &v[i]) ;

    shell(v, n) ;

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ;
    printf("\n") ;
    
}
