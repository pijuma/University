#include "abb.h" 

struct NO_{
    ITEM *item ; 
    struct NO_ *esq, *dir ; 
} ;

typedef struct NO_ NO ; 

struct ABB_{
    NO *raiz ;  
};

abb*ab_criar(){

    abb *T = (abb *) malloc(sizeof(abb)) ;

    if(T != NULL){
        T ->raiz = NULL ;
    }

    return T ; 

}

// inserção iterativa (?) 

NO *ab_inserir_no(NO *at, NO *novo){ // implementação de inserção recursiva 

    if(at == NULL) at = novo ;

    if(item_get_chave(novo->item) > item_get_chave(at->item)) at->dir = ab_inserir_no(at->dir, novo) ; 
    else if(item_get_chave(novo->item) < item_get_chave(at->item)) at->esq = ab_inserir_no(at->esq, novo) ; 

    return at ; 

}

NO *criar_no(ITEM *x){
    NO *at = (NO *) malloc(sizeof(NO)) ;
    if(at != NULL){
        at->item = x ; 
        at->esq = at->dir = NULL ; 
    }
    return at ; 
}

bool ab_inserir(abb *T, ITEM *item){ // recursiva 

    if(T == NULL) return 0 ; 

    NO *novo = criar_no(item) ;

    if(novo != NULL){
        T->raiz = ab_inserir_no(T->raiz, novo) ;
        return 1 ; 
    }

    return 0 ; 

}

ITEM *bb_it(abb *T, int val){ // busca iterativa 
    
    NO *at = T->raiz ;

    while(at != NULL){
        if(item_get_chave(at->item) == val) return at->item ; 
        if(item_get_chave(at->item) < val) at = at->dir ; 
        else at = at->esq ; 
    }

    return NULL ; 

}

ITEM *abb_busca_no(NO *at, int val){// busca recursiva 

    if(at == NULL) return NULL ; 
    if(item_get_chave(at->item) == val) return at->item ; 

    if(item_get_chave(at->item) < val) return abb_busca_no(at->dir, val) ;
    else return abb_busca_no(at->esq, val) ; 

}

ITEM *abb_busca(abb *T, int chave){// busca recursiva 
    return abb_busca_no(T->raiz, chave) ;
}

// não precisa trocar o ponteiro que aponta pro cara que vai ser apagado pois 
// eu posso trocar o conteudo dele com o cara que vai ser o subst 
// diferente doq fizemos pro caso 1 em que nós mudamos pra onde o ponteiro aponta *raiz = (*raiz)->dir etc 
void troca_max_esq(NO *remocao, NO *troca, NO *ant_troca){ 
    
    if(troca -> dir != NULL){
        troca_max_esq(remocao, troca->dir, troca) ;
        return ; 
    }

    // se o cara que eu vou trocar cmg é meu filho esq ent o filho esq dele vira o meu esq 
    // se n o filho esq do meu cara vira direito do meu "removido"
    if(remocao == ant_troca) remocao -> esq = troca->esq ; 
    else remocao -> dir = troca->esq ; 

    // troca o conteudo do nó removido com o que vai subst 
    remocao -> item = troca -> item ; 
    free(troca) ; troca = NULL ; // apaga o nó troca que nao esta sendo mais usado 

}


bool ab_remover_no(NO **at, int chave){

    if(at == NULL) return 0 ; // n achou 

    if(item_get_chave((*at)->item) == chave){ // achou o nó 

        if((*at)->esq == NULL || (*at)->dir == NULL){ // tem no max um filho - troca ele com o nó - caso 1 

            NO *rem = *at ; // preciso guardar pra liberar memo do meu nó 

            if((*at)->esq == NULL){ // posso ter filho esq 
                (*at) = (*at)->dir ; // o ponteiro que aponta pra **at agora aponta pro filho direito de **at
            }

            else (*at) = (*at)->esq ; 

            free(rem) ; rem = NULL ; 

        }

        else troca_max_esq((*at)->esq, (*at), (*at)) ; // troca o cara mais a dir da minha esquerda cmg 

        return 1 ; 

    }

    else{
        
        if(item_get_chave((*at)->item) < chave) return ab_remover_no(&(*at)->dir, chave) ; 
        else return ab_remover_no(&(*at)->esq, chave) ;
        
    }

}

bool ab_remover(abb *T, int chave){
    if(T == NULL) return 0 ; 
    return ab_remover_no(&(T->raiz), chave) ; 
}

void apagar_aux(NO **at){

    if(*at != NULL){
        apagar_aux(&(*at)->esq) ; apagar_aux(&(*at)->dir) ; 
        item_apagar(&(*at)->item) ; 
        free(*at) ; *at = NULL ; 
    }

}

void ab_apagar_arvore(abb **T){
    apagar_aux(&(*T)->raiz) ; 
    free(*T) ; *T = NULL ; 
}

void dfs_em_ordem(NO *at){
    if(at == NULL) return ; 
    dfs_em_ordem(at->esq) ; 
    printf("%d ", item_get_chave(at->item));
    dfs_em_ordem(at->dir);
}

void percurso(abb *T){
    dfs_em_ordem(T->raiz) ;
}
