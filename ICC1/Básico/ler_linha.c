#include<stdio.h>
#include<stdlib.h> 

int main(){

    char nome[20], kr[20] ;

    scanf(" %[^\n]s", nome) ; // ler pegando a linha toda - n para numa palavra so 
    scanf(" %[^\n]s", kr) ;
    printf("%s\n%s\n", nome, kr) ;

} 
