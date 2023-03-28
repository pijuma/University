#include<stdio.h> 
#include<math.h> 

int x ; 

int main(){

    scanf("%d", &x) ; 

    printf("Numero: %d\n", x) ; 
    double ans = 1.00 ; 
    for(int i = 1 ; i <= 10 ; i++) ans *= x ; 
    printf("%17.2e\n", ans) ; // 17 espaçamentos -> e pra deixar em notação cientifica 
    double raiz = sqrt(x) ;  
    printf("%13.2lf\n", raiz) ; 

}
