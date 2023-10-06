/*

    inserção remoção alterar busca
    imprimir todos os verbetes que começam 
    com letra "X"
    
    OK inserção(s1, s2) -> insere palavra s1 com sig s2 
    OK alterar(s1, s2) -> alterar definição de s1 pra s2 
    rem(s1) -> remover palavra s1 do dic 
    OK busca(s1) -> imprime definição da palavra s1 
    impressão(char c) -> imprime todas as palavras que começam 
    com caracter c -> em ord alf -> com a definição 
    palavra e definição em linhas diferentes 

    se der ruim -> operação invalida 
    n achou palavras que começam com c -> nao ha palavras iniciadas por c

    palavra tem até 50 caracteres e verbete ate 140 caracteres 

    skiplist:
    considera nós acima e abaixo - agrupamento  vertical de listas 
    organizada em niveis - cada nivel eh uma lista 
    a cabeça do nivel tem um ponteiro p prox lista 
    cada nivel contem um numero aleatorio de nós 
    só a lista maix baixa tem todos nós 

    criar a lista - ok 
    pra cada nó guarda o nivel dele o prox (direita) e o debaixo 
    na hora de inserir procura o ultimo kra <= a mim qd eu achei eu desço 
    tudo - guardando os nós q eu passei (posso ter q mudar o prox - dir desses) 
    salva eles num array de tamanho[niveis_lista]
    se o valor ja ta presente - nao insere dnv 


*/
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include "lista.h"

// declaração da struct do nó 
struct NO_{ 
    ITEM *item ; // cara atual 
    struct NO_ *prox, *baixo; // cara da direita e cara que esta no nivel abaixo dele 
    int lvl; // nivel que ele esta
} ; 

typedef struct NO_ NO ; 

struct SKIP_L{
    int mx_lvl, tam ; //maior nivel ate agora 
    NO *ini ; // no cabeça inicial - cara maix acima 
} ;

// criando nossa skip list 

bool skip_vazia(SKIP *skip){ return skip->tam == 0 ; }

SKIP *skip_criar(){

    SKIP *skip = (SKIP *) malloc(sizeof(SKIP)) ; 

    if(skip == NULL) exit(1) ; 
    else { 
        
        skip->mx_lvl = 0 ; skip->tam = 0 ; skip->ini = NULL ; // inicializa o skip

        NO *sentinela = (NO *) malloc(sizeof(NO)) ; 
        
        if(sentinela == NULL) exit(1) ; 

        sentinela->lvl = 0 ; sentinela->item = NULL ;
        sentinela->prox = NULL ; sentinela->baixo = NULL ; 

        skip->ini = sentinela ;

    }

    return skip ; 

}

ITEM *skip_busca_key(SKIP *skip, char *pal){
    
    if(skip == NULL || skip_vazia(skip)) return NULL ; 

    NO *atual = (skip->ini) ;

    //printf("estou tentando buscar %s:\n", pal) ; 

    while(atual != NULL){

        if(atual->item != NULL && !strcmp(pal, item_get_key(atual->item))) return atual->item ;

        else if(atual->prox == NULL){
            atual = atual->baixo ; 
        }

        else{

            //if(atual->item != NULL) printf("tenho %s\n", item_get_key(atual->item)) ;

            if(atual->item != NULL && !strcmp(pal, item_get_key(atual->item))){ 
                //printf("achei um cara %s procurando %s\n", item_get_key(atual->item), pal) ; 
                return atual->item ;
            }

            if(strcmp(item_get_key((atual->prox)->item), pal) > 0){//meu proximo é maior = devo descer
                //printf("to no nivel %d procurando %s e meu proximo %s\n", atual->lvl, pal, item_get_key((atual->prox)->item)) ; 
                atual = atual -> baixo ; 
            }

            else{ // senao continuo indo pra direita 
                //printf("to no nivel %d procurando %s e meu proximo %s\n", atual->lvl, pal, item_get_key((atual->prox)->item)) ; 
                atual = atual->prox ; 
            }

        } 

    } 

    return NULL ; 

}

int get_nivel() {

    srand((unsigned)time(NULL));

    int res = 0;

    while(true) {
        int num = rand();
        if (num%2 == 0) res++;
        else break;
    }

    return res;
}

void imprime_skip(SKIP *skip){

    NO *cabeca = skip->ini ; 

    while(cabeca != NULL){

        printf("estou no nivel %d\n", cabeca->lvl) ; 
        printf("passei por\n") ; 

        for(NO *i = cabeca->prox ; i != NULL ; i = i->prox){
            printf("%s ", item_get_key(i->item)) ; 
            if(i->baixo != NULL){
                printf("%s\n", item_get_key((i->baixo)->item)) ; 
            }
        }

        printf("\n") ; 

        cabeca = cabeca->baixo ; 

    }

}

bool skip_inserir(SKIP *skip, ITEM *a){

    //printf("tentando inserir %s %s:\n", item_get_key(a), item_get_verb(a)) ; 

    //if(skip == NULL || skip_busca_key(skip, item_get_key(a)) != NULL) return 0 ; 

    skip->tam++ ; 

    int nivel = get_nivel();

    printf("%d\n", nivel) ;

    NO *at = skip->ini ; 
    // o anterior é para caso eu tenha add ja algum 
    // e tenho que ligar de baixo com o meu atual agora

    if(at->lvl < nivel){ // tenho que criar novos nós cabeças 

        int ct = nivel-(at->lvl); 
        
        while(ct--){

            NO *criado = (NO *) malloc(sizeof(NO)) ;

            criado->prox = NULL ; criado->item = NULL ; 
            criado->lvl =  1 + (at->lvl); 

            //printf("add um nivel %d\n", criado->lvl) ;

            criado->baixo = at ; 
            at = criado ; 

        }

    }

    skip->mx_lvl = at->lvl ; skip->ini = at ; 
    
    NO *ant = NULL ; 

    while(at != NULL){

        if(at->prox == NULL){ // checa se o nivel dele é <= ao meu 

            if(at->lvl <= nivel){

                NO *agr = (NO *)malloc(sizeof(NO)) ;

                agr->lvl = at->lvl ; agr -> prox = NULL ; agr -> baixo = NULL ; 
                agr -> item = a ;
                at->prox = agr ; 

                if(ant != NULL){// tenho que ligar o meu de cima com meu atual
                    ant->baixo = agr ;
                }

                ant = agr ;

            }

            at = at->baixo ; 

        }

        else{

            if(at->lvl > nivel) at = at->baixo ; //n devo add o meu ainda 

            else if(strcmp(item_get_key((at->prox)->item), item_get_key(a)) > 0){//tenho que add meu agr e dps descer 
                
                NO *agr = (NO *)malloc(sizeof(NO)) ;

                agr->lvl = at->lvl ; agr->prox = NULL ; agr->baixo = NULL ; 
                agr->item = a ;

                if(ant != NULL){
                    ant->baixo = agr ; 
                }

                agr->prox = at->prox ; 
                at->prox = agr ; 
                at = at->baixo ;

                ant = agr ;  

            }

            else{ // senao continuo indo pra direita 
                at = at->prox ; 
            }

        }

    }

    return 1 ; 

}

bool skip_alterar(SKIP *skip, ITEM *a){

    if(skip == NULL || skip_vazia(skip) || !skip_busca_key(skip, item_get_key(a))) return 0 ; 

    NO *at = skip->ini ; 

    while(at != NULL){

        if(at->item != NULL && !strcmp(item_get_key(a), item_get_key(at->item))){// achei = tenho q alterar e descer nele 
            //printf("achou\n") ; 
            item_set_verb(at->item, item_get_verb(a)) ;
            at = at->baixo ; 
        }

        else{

            if(at->prox == NULL) at = at->baixo ; 
            else{
                if(strcmp(item_get_key((at->prox)->item), item_get_key(a))>0) at = at->baixo ; 
                else at = at->prox ;  
            }

        }

    }

}

