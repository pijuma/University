#include<stdio.h>
#include<string.h>

int main(){

    char ss[30] ;

    scanf("%s", ss) ; // NAO USAR &ss QUANDO LER STRING -> ELA JA VEM COM REFERENCIA PELO USO DE []
    printf("Bom dia, %s!\n", ss) ;

}
