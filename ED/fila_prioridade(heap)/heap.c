#include "heap.h"

#define esq (2*at) + 1 
#define dir (2*at) + 2

// max heap 

struct heap_{
    ITEM *v[maxn] ;
    int lst ; 
} ;

HEAP *heap_criar(){

    HEAP *h = (HEAP *) malloc(sizeof(HEAP)) ;

    if(h != NULL) h->lst = -1 ; 

    return h ; 

}

int heap_cheia(HEAP *h){ return h->lst >= maxn ; }

int heap_vazia(HEAP *h){ return h->lst == -1 ; }

void swap(HEAP *h, int i, int j){
    ITEM *t = h->v[j] ; 
    h->v[j] = h->v[i] ; 
    h->v[i] = t ; 
}


void fix_up(HEAP *h, int at){

    while(at != 0){
        int pai = (at-1)/2 ; 
        if(item_get_chave(h->v[pai]) > item_get_chave(h->v[at])) break ; 
        swap(h, pai, at) ; 
        at = pai ; 
    }

}

void fix_down(HEAP *h, int at){

    while(at <= h->lst){
        int mx = at ; 
        if(item_get_chave(h->v[esq]) > item_get_chave(h->v[mx])) mx = esq ; 
        if(item_get_chave(h->v[dir]) > item_get_chave(h->v[mx])) mx = dir ; 
        if(mx == at) break ; 
        swap(h, mx, at) ; 
        at = mx ; 
    }

}

int heap_inserir(HEAP *h, ITEM *item){
    // insere no lst + 1 - fix_up 
    if(heap_cheia(h)) return 0 ; 
    int neww = h->lst + 1 ; 
    h->v[neww] = item ; 
    fix_up(h, neww) ;
    h->lst = neww ; 
    return 1 ; 
}

int heap_remover(HEAP *h){
    // remove topo -> joga last pro topo -> rearruma o resto descendo fix_down 
    if(heap_vazia(h)) return 0 ; 
    swap(h, 0, h->lst) ;
    h->lst-- ; 
    fix_down(h, 0) ;
    return 1 ; 
}

int topo(HEAP *h){ return item_get_chave(h->v[0]) ; }

void show(HEAP *h){
    for(int at = 0 ; at <= h->lst ; at++){
        printf("sou %d:\n", item_get_chave(h->v[at])) ; 
        if(esq <= h->lst)printf("tenho filho esq %d ", item_get_chave(h->v[esq])) ;
        if(dir <= h->lst) printf("tenho filho direito %d\n",  item_get_chave(h->v[dir])) ; 
    }
}
