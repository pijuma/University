#include "avl.h"
#define max(a, b) (a > b ? a : b)

struct NO_{
    ITEM *item ; 
    struct NO_ *esq, *dir ; 
    int altura ; 
} ;

typedef struct NO_ NO ; 

struct AVL_{
    NO *raiz ; 
} ;

AVL *criar_avl(){
    
    AVL *avl = (AVL *) malloc(sizeof(AVL)) ; 

    if(avl != NULL) avl -> raiz = NULL ; 

    return avl ; 

}

NO *criar_no(ITEM *item){

    NO *at = (NO *) malloc(sizeof(NO)) ;

    if(at != NULL){
        at -> item = item ; 
        at->esq = NULL ; at->dir = NULL ; 
        at -> altura = 0 ; 
    }

}

void apagar_avl_no(NO **node){

    if(*node == NULL) return ; 
    
    apagar_avl_no(&(*node)->esq) ; apagar_avl_no(&(*node)->dir) ;
    
    item_apagar(&(*node)->item) ;
    free(*node) ; *node = NULL ; 

}

void apagar_avl(AVL **a){

    if(*a == NULL) return ; 
    
    apagar_avl_no(&((*a)->raiz)) ; 
    free(*a) ; *a = NULL ; 

}

void apagar_no(NO **node){
    item_apagar(&(*node)->item) ; 
    free(*node) ; *node = NULL ; 
}


int get_alt(NO *node){
    if(node == NULL) return -1 ; 
    return node->altura ; 
}

NO *rodar_esq(NO *node){
    NO *b = node->dir ; 
    node->dir = b->esq ; 
    b->esq = node ;
    node->altura = max(get_alt(node->esq), get_alt(node->dir)) + 1 ;  
    return b ; 
}

NO *rodar_dir(NO *node){
    NO *b = node->esq ; 
    node->esq = b->dir ;
    b -> dir = node ; 
    node->altura = max(get_alt(node->esq), get_alt(node->dir)) + 1 ; 
    return b ; 
}

NO *rodar_esq_dir(NO *node){
    node->esq = rodar_esq(node->esq) ; 
    node = rodar_dir(node) ; 
}

NO *rodar_dir_esq(NO *node){
    node->dir = rodar_dir(node->dir) ; 
    node = rodar_esq(node) ; 
}

NO *inserir_no_avl(NO *node, NO *novo){

    if(node == NULL){
        node = novo ; 
    }

    else if(item_get_chave(node->item) < item_get_chave(novo->item)) node->dir = inserir_no_avl(node->dir, novo) ; 
    else if(item_get_chave(node->item) > item_get_chave(novo->item)) node->esq = inserir_no_avl(node->esq, novo) ; 

    node->altura = max(get_alt(node->esq), get_alt(node->dir)) + 1 ; 

    // rotação direita ou esq/dir 
    if(get_alt(node->esq) - get_alt(node->dir) == 2){
        if(item_get_chave(novo->item) < item_get_chave(node->esq->item)) node = rodar_dir(node) ;
        else node = rodar_esq_dir(node) ;
    } 
    // rotacao esq ou dir/esq
    else if(get_alt(node->esq) - get_alt(node->dir) == -2){
        if(item_get_chave(novo->item) > item_get_chave(node->dir->item)) node = rodar_esq(node) ;
        else node = rodar_dir_esq(node) ;
    }

    return node ; 

}

void troca_max_esq(NO **raiz, NO **ant, NO **troca){
    
    if((*troca)->dir != NULL){
        troca_max_esq(raiz, troca, &(*troca)->dir) ;
        return ;
    }

    printf("trocando %d por %d\n", item_get_chave((*ant)->item), item_get_chave((*troca)->item));

    NO *ot = (*troca) ;

    if(*ant == *raiz) (*ant)->esq = (*troca)->esq ; 
    else (*ant)->dir = ((*troca))->esq ;  

    (*raiz) -> item = (ot) -> item ; 

    printf("trocando %d por %d\n", item_get_chave((*raiz)->item), item_get_chave((*troca)->item));

    apagar_no(&ot) ;

}

int fator_b(NO *a){
    return get_alt(a->esq) - get_alt(a->dir) ; 
}

NO *remover_no_avl(NO **node, int chave){
    
    if(*node == NULL) return 0 ; 

    if(item_get_chave((*node)->item) == chave){

        // no max 1 filho 
        printf("Meu no ¨%d\n", item_get_chave((*node)->item)) ;
        if((*node)->esq == NULL || (*node)->dir == NULL){
            
            NO *p = *node ;

            if((*node)->esq == NULL){
                (*node) = (*node)->dir ; 
            }

            else (*node) = (*node)->esq ; 

            apagar_no(&p) ; 

        }

        else troca_max_esq(node, node, &((*node)->esq)) ; 

        //printf("Meu no ¨%d\n", item_get_chave((*node)->item)) ;

        return *node ; 

    }

    /*else if(item_get_chave((*node)->item) > chave) (*node)->esq = remover_no_avl(&(*node)->esq, chave) ;  
    
    else (*node)->dir = remover_no_avl(&(*node)->dir, chave) ; 

    if(*node == NULL) return NULL ; 

    // rebalancear 

    (*node)->altura = max(get_alt((*node)->esq), get_alt((*node)->dir)) + 1 ; 

    // dir ou esq/dir 
    if(get_alt((*node)->esq) - get_alt((*node)->dir) == 2){
        if(fator_b((*node)->esq) < 0) (*node) = rodar_esq_dir(*node) ; 
        else (*node) = rodar_dir(*node) ;
    }

    // esq ou dir/esq 

    else if(get_alt((*node)->esq) - get_alt((*node)->dir) == -2){
        if(fator_b((*node)->dir) > 0) (*node) = rodar_dir_esq(*node) ;
        else (*node) = rodar_esq(*node) ; 
    }*/

    return *node ; 

}

bool remover_avl(AVL *a, int chave){

    if(a == NULL) return 0 ; 
    a->raiz = remover_no_avl(&(a->raiz), chave) ; 
    return 1 ; 
}

bool inserir_avl(AVL *a, ITEM *item){

    if(a == NULL) return 0 ; 

    NO *novo = criar_no(item) ;

    if(novo == NULL) return 0 ; 

    a->raiz = inserir_no_avl(a->raiz, novo) ;

    return 1 ; 

}

bool buscar_valor(NO *node, int chave){
    
    if(node == NULL) return 0 ; 

    if(item_get_chave(node->item) == chave) return 1 ; 

    if(item_get_chave(node->esq->item) < chave) return buscar_valor(node->dir, chave) ;
    else return buscar_valor(node->esq, chave) ;

}

bool buscar_avl(AVL *a, int chave){
    if(a == NULL) return 0 ; 
    return buscar_valor(a->raiz, chave) ;
}

void dfs_em_ordem(NO *node){
    if(node == NULL) return ; 
    //printf("nao nulo\n") ;
    dfs_em_ordem(node->esq) ;
    printf("%d com altura %d\n", item_get_chave(node->item), get_alt(node)) ; 
    dfs_em_ordem(node->dir) ;
}

/*bool talkei(NO *node){
    if(node == NULL) return 1 ; 
    bool ok_dokey = 1 ; 
    ok_dokey &= talkei(node->esq) ;
    ok_dokey &= talkei(node->dir) ;
    int at = get_alt(node->esq) - get_alt(node->dir) ;
    if(at >= 2 || at <= -2) ok_dokey = 0 ; 
    return ok_dokey ; 
}*/

/*bool ta_ok(AVL *a){
    if(a == NULL) return 0 ; // ta nao 
    return talkei(a->raiz) ;
}*/

void percurso_avl(AVL *a){
    if(a == NULL) return ; 
    //printf("chamou\n") ;
    dfs_em_ordem(a->raiz) ;
}
