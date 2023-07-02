#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

struct P{
    char *nome ; 
} ;

typedef struct P pp ;

int main(){

    int n ; scanf("%d", &n) ;

    pp *pessoa ; 

    pessoa = (pp *) malloc(1*sizeof(pp)) ; 

    (pessoa->nome) = (char *) malloc((n+1)*sizeof(char)) ; 

    scanf(" %s", (pessoa->nome)) ; 

    printf("%s\n", (pessoa->nome)) ; 

}
