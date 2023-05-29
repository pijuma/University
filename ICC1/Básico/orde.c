//ordenação de 3 valores por ponteiros 

#include<stdio.h> 

void ord(int *a, int *b, int *c){
    
    if(*a > *b){
        int temp = *a ; 
        *a = *b ; *b = temp ;  
    }

    if(*b > *c){
        int temp = *b ; 
        *b = *c ; *c = temp ; 
    }

    if(*a > *b){
        int temp = *a ; 
        *a = *b ; *b = temp ;  
    }

}

int main(){

    int a, b, c ; scanf("%d%d%d", &a, &b, &c) ; 

    ord(&a, &b, &c) ;

    printf("%d %d %d\n", a, b, c) ;

}
