#include "me.h"

struct celula{
    int linha, coluna ; 
    float valor ; 
    struct celula *dir, *baixo ; 
} ;

typedef struct celula Cel ; 

struct matriz{
    Cel **linhas, **colunas ; 
    int n, m ; 
} ;

Mat *criar_matriz(int n, int m){
    Mat *mat = (Mat *) malloc(sizeof(Mat)) ;
    if(mat != NULL){
        mat->n = n, mat->m = m ; 
        mat->linhas = (Cel **) malloc(sizeof(Cel *)*n) ;
        mat->colunas = (Cel **) malloc(sizeof(Cel *)*m) ; 
        if(mat->colunas != NULL && mat->linhas!=NULL){
            for(int i = 0 ; i < m ; i++) mat->colunas[i] = NULL ; 
            for(int i = 0 ; i < n ; i++) mat->linhas[i] = NULL ; 
        }
    }
    return mat ; 
}

void apagar_matriz(Mat **matriz){
    
    for(int i = 0 ; i < (*mat)->n ; i++){
        if((*matriz)->linhas[i] != NULL){
            Cel *paux = (*matriz)->linhas[i]->dir ; 
            while(paux != NULL){
                Cel *nxt = paux ; 
                paux = paux->dir ; 
                free(nxt) ; nxt = NULL ; 
            }
        } 
        free((*matriz)->linhas[i]) ; (*matriz)->linhas[i] = NULL ; 
    }

    free((*matriz)->linhas) ; free((*matriz)->coluna) ; 

    free(*matriz) ; *matriz = NULL ; 

}

int set(Mat *matriz, int n, int m, float val){
    Cel *add, *at, *ant ; 
    add = (Cel *)malloc(sizeof(Cel)) ;
    //checar se tem algo invalido 
    add->n = n, add->m = m ; add->valor = val ; 
    q = matriz->linha[n] ; //inserir na linha 
    ant = NULL ; 
    while(q!=NULL){
        if(q->coluna < m){
            ant = q ; 
            q = q->dir ; 
        }
        else{//achou local 
            if(ant == NULL){
                matriz->linha[n] = add ; 
            }
            else{
                ant->dir = add ; 
            }
            add->dir = q ; 
            break ; 
        }
    }
    if(q == NULL){// eh o ultimo 
        if(ant != NULL) ant->dir = add ; 
        else matriz->linha[n] = add ; 
    }
    //mesma coisa pra coluna
}

float get(Mat *matriz, int n, int m){
    //percorre linha 
    Cel *at = matriz->linha[n] ; 
    while(at!=NULL){
        if(at->coluna == m) return at->val ; 
        else if(at->coluna > m) break ; 
        at = at->dir ; 
    }
    return 0 ; 
}

void imprimir_matriz(Mat *matriz){
    for(int i = 0 ; i < matriz->n ; i++){// em q linha eu to 
        //imprimo a coluna toda 
        Cel *at = matriz->linha[i] ; 
        while(at != NULL){
            printf("%d ", at->valor) ; 
            at = at->dir ; 
        }
        printf("\n") ; 
    }
}

// add valor n nulo na coluna toda 
void add_coluna(Mat *matriz, int col, float valor){
    Cel *at = matriz->coluna[col] ;
    int lin_at = 0 ;
    if(at == NULL){
        set(matriz, lin_at, col, valor) ;
        at = matriz->coluna[col] ;
    } 
    while(lin_at != matriz->linha){
        if(at->dir == NULL || lin_at + 1 != at->dir->coluna) set(matriz, lin_at+1, col, 0)  ; 
        at = at->dir ; 
    }
    // criei os kras extras 
    // tenho q apagar e somar 
    at = matriz->coluna[col] ;
    while(at != NULL){
        Cel *nxt = at->dir ; 
        if(at->valor + valor == 0.00) remover(matriz, at->n, at->m, valor) ;
        else at->valor == valor ; 
    }
}
