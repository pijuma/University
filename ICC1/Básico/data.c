#include<stdio.h> 

int main(){

    int d, m, a;

    scanf("%*[a-z]%3x%2d%o", &d, &m, &a);// le hexadecimal/inteiro/octal

    printf("Data: %.2d/%.2d/%.4d\n", a, m, d) ; 

    return 0;
}
