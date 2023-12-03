#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  SET *A, *B;
  int n_a, n_b, x;
  int op;

  A = set_criar();
  B = set_criar();

  scanf("%d %d", &n_a, &n_b);

  for(int i=0; i<n_a; i++){
    scanf("%d",&x);
    set_inserir(A, x);

  }
  
  for(int i=0; i<n_b; i++){
    scanf("%d",&x);
    set_inserir(B, x);

  }

  scanf("%d", &op);

  switch(op){
    case 1: {
              int num;
              scanf("%d", &num);
              if(set_pertence(A,num)) 
                printf("Pertence.");
              else
                printf("Não Pertence.");
              break;
    }
    case 2: {
              SET *C = set_uniao(A,B);
              set_imprimir(C);
              set_apagar(&C);
              break;//pietra e bruno 
    }
    case 3: {
              SET *C = set_interseccao(A, B);
              set_imprimir(C);
              set_apagar(&C);
              break;
    }
    case 4: {
              int num;
              scanf("%d", &num);
              set_remover(A,num);
              set_imprimir(A); 
    }
  }

  set_apagar(&A);
  set_apagar(&B);
    
  return 0;
}
