#include "pq.h"
#define esq (2*i)+1 
#define dir (2*i)+2

struct heap_{
    ITEM *v[maxn] ;
    int lst ; 
} ;

HEAP *heap_criar(){
    
    HEAP *heap = (HEAP *) malloc(sizeof(HEAP)) ;
    
    if(heap != NULL){
        heap->lst = -1 ;
    }
    
    return heap ; 

}

int heap_cheia(HEAP *h){ return h->lst == maxn - 1 ; }

int heap_vazia(HEAP *h){ return h->lst == -1 ; } 

void swap(HEAP *h, int a, int b){
    ITEM *t = h->v[a] ; 
    h->v[a] = h->v[b] ;
    h->v[b] = t ; 
}


void fix_up(HEAP *h, int i){
    while(i){
        int pai = i-1 ; pai >>= 1 ; 
        if(item_get_chave(h->v[i]) < item_get_chave(h->v[pai])) break ;
        swap(h, i, pai) ;
        i = pai ; 
    }
}

int heap_inserir(HEAP *h, ITEM *item){
    // insere no lst e faz fix_up
    int neww = h->lst + 1 ; 
    h->v[neww] = item ; 
    h->lst++ ; 
    fix_up(h, neww) ;
}

void fix_down(HEAP *h, int i){

    int mx = i ; 

    if(esq <= h->lst && item_get_chave(h->v[mx]) < item_get_chave(h->v[esq])) mx = esq ; 
    if(dir <= h->lst && item_get_chave(h->v[mx]) < item_get_chave(h->v[dir])) mx = dir ;

    if(mx == i) return ; 

    swap(h, mx, i) ;
    fix_down(h, mx) ;

}

int heap_remover(HEAP *h){
    // troca toopo pelo lst e faz fix_down 
    swap(h, 0, h->lst) ;
    h->lst-- ; 
    printf("%d\n", h->lst) ;
    fix_down(h, 0) ;
}

int topo(HEAP *h){ return item_get_chave(h->v[0]) ; }

void show(HEAP *h){
    for(int i = 0 ; i <= h->lst/2 ; i++){
        printf("Eu sou %d", item_get_chave(h->v[i])) ;
        if(esq <= h->lst) printf(" meu esq eh %d", item_get_chave(h->v[esq])) ;
        if(dir <= h->lst) printf(" meu direito eh %d", item_get_chave(h->v[dir])) ;
        printf("\n") ; 
    }
}
