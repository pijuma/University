#include<stdlib.h>
#include<stdio.h>

//lista encadeada

struct Cel{
    int conteudo ; 
    struct Cel *prox ; // qual o proximo cara da lista?
};

typedef struct Cel celula ; 

// p add um elemento no meio do vetor tem q percorrer ele até achar o elemento 

void create(int a, celula *ini){ 
   
    // acha qual o ultimo cara 
    // cria um novo cara p ultimo apontar p esse novo 
    // o prox do novo eh nullo e o valor eh oq a gnt quer colocar 

    celula *lst = NULL ; 

    for(celula *p = ini ; 1 ; p = p ->prox){
        lst = p ;
        if((p->prox) == NULL) break ; 
    } 

    //alterar o prox do ponteiro p 

    //printf("%d", lst-> conteudo) ;
    (lst -> prox) = (celula *) malloc(sizeof(celula)) ;
    (*(lst->prox)).conteudo = a ; 
    (lst->prox)->prox = NULL ; 

    printf("Deu bom? add cara %d\n", (*(lst->prox)).conteudo) ;

}

celula *encontra(int a, celula *ini){ // percorre o vetor procurando o cara que tem o conteudo a -> n achou = NULL 

    celula *lst = ini ; 

    for(celula *p = ini ; p != NULL ; p = p -> prox){
        if(p->conteudo == a){
            return lst ; 
        }
        lst = p->prox;
    }

    return NULL ; 

}

int main(){

    celula *ini = NULL ; //ponteiro inicial 
    ini = (celula *) malloc(sizeof(celula));
    ini -> conteudo = -1 ; ini -> prox = NULL ; 

    int n ; scanf("%d", &n); 

    for(int i = 1 ; i <= n ; i++){
        int a ; scanf(" %d", &a) ; create(a, ini) ;
    }

    int x ; scanf("%d", &x) ;
    celula *resp = encontra(x, ini);
    if(resp == NULL) printf("nao achou\n") ;
    else printf("%d %p\n", resp->conteudo, resp->prox);
}
