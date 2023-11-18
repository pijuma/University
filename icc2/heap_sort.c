#include<stdio.h>
#include<stdlib.h>
#define esq ((2*i)+1)
#define dir ((2*i)+2)

void swap(int a, int b, int *v){
    int t = v[a] ; 
    v[a] = v[b] ; v[b] = t ; 
}

void rearranja(int *v, int i, int tam){

    int maior = i ; 
    
    if(esq >= tam && dir >= tam) return ; // folha - nem tem pra onder descer o vertice

    if(esq < tam && v[maior] < v[esq]) maior = esq ; 
    if(dir < tam && v[maior] < v[dir]) maior = dir ; 

    //printf("esq %d dir %d i %d valor maior de todos %d\n", v[esq], v[dir], v[i], v[maior]) ; 

    if(maior != i){ // se a raiz não é o maior cara ent é pq deu ruim 
        swap(maior, i, v) ;
        rearranja(v, maior, tam) ;
    }

}

void monta_heap(int i, int tam, int *v){

    if(esq >= tam && dir >= tam) return ; //folha

    if(esq < tam) monta_heap(esq, tam, v) ;
    if(dir < tam) monta_heap(dir, tam, v) ; 

    //printf("chamei a de rearrumar para %d com esq %d dir %d\n", i, esq, dir) ;
    rearranja(v, i, tam) ; // joga o cara i pra pos certa dele  

}

void heap_sort(int *v, int n){

    monta_heap(0, n, v) ;
    
    int tam = n ; 

    for(int i = n - 1 ; i >= 0 ; i--){
        int aux = v[0] ; //maior valor 
        v[0] = v[i] ; // troca o meu atual pelo maior valor 
        v[i] = aux ; // joga o maior valor p final atual - será ignorado
        //printf("em %d o maior era %d\n", i, aux) ; 
        tam-- ; rearranja(v, 0, tam) ;
    }

}

int main(){

    int n ; scanf("%d", &n); 

    int v[n+2] ; 

    for(int i = 0 ; i < n ; i++) scanf("%d", &v[i]) ; 

    heap_sort(v, n) ; 

    for(int i = 0 ; i < n ; i++) printf("%d ", v[i]) ; 
    printf("\n") ; 

}
