#include<stdio.h>
#include<string.h>

int n ;
char x ;

int main(){

    scanf("%d %c", &n, &x) ; // Dúvida: pq tem que ler com %s e &x?? - vc fornece o endereço que a variavel está
    // passa onde o valor lido será armazenado

    printf("Inteiro lido: %d\n", n) ; //imprime inteiro
    printf("Codigo hexadecimal: %x\n", n) ; // imprime na base hexadecimal
    printf("Caractere ASCII: %c\n\n", n) ; // imprime na tabela ASCII
    printf("Inteiro lido: %d\n", x) ;
    printf("Codigo hexadecimal: %x\n", x) ;
    printf("Caractere ASCII: %c\n", x) ;

}
