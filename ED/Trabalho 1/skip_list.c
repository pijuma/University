/*
    Trabalho 1 - implementação de um dicionário com uso de skiplist

    Pietra Gullo Salgado Chaves - 14603822
    Bruno Figueiredo Lima - 14562383

    Para o projeto foi implementada uma skiplist encadeada e com cabeça, essa que facilita as operações
    de remoção, inserção busca e encadeada pois não sabemos quantos elementos teremos logo fazê-la estática fica
    custoso e inviável

    A skiplist foi utilizada no intuito de reduzir a complexidade do algoritmo, já que sem a skiplist para alterar, inserir, remover
    e fazer busca, por exemplo, todas operações seriam no minimo O(N) pois teriamos que percorrer a lista inteira no pior caso 
    Assim, com uso de skiplist, escolhendo os niveis de forma randomizada podemos acelerar as operações citadas "pulando" elementos que não 
    irão fazer diferença em listas de níveis superiores (que não terão todos os elementos da original), assim acelerando o algoritmo 

    as operações requeridas e implementadas foram: 
    inserção(s1, s2) -> insere palavra s1 com verbete s2 
    alterar(s1, s2) -> alterar definição de s1 pra s2 
    rem(s1) -> remover palavra s1 do dicionário 
    busca(s1) -> imprime definição da palavra s1 
    impressão(char c) -> imprime todas as palavras que começam com o caracter c e seus respectivos verbetes

    Como extra, implementamos as funções (pois vimos utilidade para debugar/executar as outras):
    skip_vazia -> para checar se a lista tem elementos 
    get_nivel -> para gerar o nivel do nosso nó de forma randomica
    imprime_skip -> para debugar, utilizada para checar se a lista foi montada corretamente 
    skip_apagar -> para desalocar a memória utilizada 

*/

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include "skip.h"

// declaração da struct do no
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

// checar se a skip list está vazia 
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

    while(atual != NULL){

        if(atual->item != NULL && !strcmp(pal, item_get_key(atual->item))) return atual->item ;

        else if(atual->prox == NULL){
            atual = atual->baixo ; 
        }

        else{

            if(atual->item != NULL && !strcmp(pal, item_get_key(atual->item))) return atual->item ;

            if(strcmp(item_get_key((atual->prox)->item), pal) > 0){//meu proximo é maior = devo descer
                atual = atual -> baixo ; 
            }

            else{ // senao continuo indo pra direita 
                atual = atual->prox ; 
            }

        } 

    } 

    return NULL ; 

}

int get_nivel() {
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

    if(skip == NULL || skip_busca_key(skip, item_get_key(a)) != NULL) return 0 ; 

    skip->tam++ ; 

    int nivel = get_nivel();

    //printf("%d\n", nivel) ;

    NO *at = skip->ini ; 
    // o anterior é para caso eu tenha add ja algum 
    // e tenho que ligar de baixo com o meu atual agora

    if(at->lvl < nivel){ // tenho que criar novos nós cabeças 

        int ct = nivel-(at->lvl); 
        
        while(ct--){

            NO *criado = (NO *) malloc(sizeof(NO)) ; 

            criado->prox = NULL ; criado->item = NULL ; 
            criado->lvl =  1 + (at->lvl); 

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

    if(skip == NULL || skip_vazia(skip) || !skip_busca_key(skip, item_get_key(a))) {
        item_apagar(&a); return false;
    }

    NO *at = skip->ini ; 

    int mudei = 0 ; 

    while(at != NULL){

        if(at->item != NULL && !strcmp(item_get_key(a), item_get_key(at->item))){// achei = tenho q alterar e descer nele 
            mudei = 1 ;  
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

    item_apagar(&a);

    return mudei ; 

}

bool skip_remover(SKIP *skip, char *a){

    if(skip == NULL || skip_vazia(skip) || !skip_busca_key(skip, a)) return 0 ; 

    NO *at = skip->ini ;
    int achei = 0 ; 

    while(at != NULL){

        if(at->item == NULL){ // nó cabeça
            
            if(at->prox == NULL) at = at->baixo ; // n tenho pra onde ir 

            else{

                if(strcmp(item_get_key((at->prox)->item), a) > 0) at = at->baixo ; // n tem ngm meu naql nivel
                
                else{ // tenho que apagar meu proximo? 

                    if(!strcmp(item_get_key((at->prox)->item), a)){ // tenho q apagar meu prox
                        
                        achei = 1 ;
                        
                        

                        NO *mid = at->prox ;
                        at->prox = mid->prox ; 


                        if (mid != NULL) {
                            item_apagar(&(mid->item));
                            free(mid) ;
                            mid->prox = NULL ;
                        }

                        at = at->baixo ; 
                    }

                    else at = at->prox ; 

                }

            }

        }

        else{
            if (at->prox != NULL) {
                    if(!strcmp(item_get_key((at->prox)->item), a)){ // tenho que apagar 
                    
                    achei = 1 ; // apaguei algum cara 

                    NO *mid = at->prox ; 
                    at -> prox = mid->prox ; 

                    if (mid != NULL) {
                        item_apagar(&(mid->item));
                        free(mid) ;
                        mid->prox = NULL ;
                    }
                    
                    
                    at = at->baixo ;

                }

                else{

                    if(strcmp(item_get_key((at->prox)->item), a) > 0) at = at->baixo ; 
                    else at = at->prox ; 

                } 
            } else {
                at = at->baixo;
            } 


            

        }

    }

    return achei ; 

}

// imprime todas as palavras que começam com a letra "a" - em ord alfabética
bool skip_imprime_char(SKIP *skip, char a){

    NO *at = skip->ini ; 

    while(at!=NULL){

        // quero ver o prox - se o prox n vai me satisfazer mais eu desço no meu 

        if(at->prox == NULL) at = at->baixo ; // tenho que descer 

        else{

            // to no array completo e achei onde começa oq quero imprimir 

            if(at->baixo == NULL && at->prox != NULL && a == item_get_key((at->prox)->item)[0]){ // achei e to em cabeça

                for(NO *i = at->prox ; i != NULL && a == item_get_key((i)->item)[0] ; i = i->prox){
                    printf("%s %s\n", item_get_key(i->item), item_get_verb(i->item)) ; 
                }

                return 1 ; 
            
            }

            else if(at->item != NULL && at->baixo == NULL && a == item_get_key(at->item)[0]){ // achei e nao to em cabeça

                for(NO *i = at ; i != NULL && a == item_get_key((i)->item)[0] ; i = i->prox){
                    printf("%s %s\n", item_get_key(i->item), item_get_verb(i->item)) ; 
                }

                return 1 ; 
            
            }

            else if(a -'a' <= (item_get_key((at->prox)->item))[0]-'a'){ // tenho que descer no meu atual 
                at = at->baixo ; 
            }

            else{
                at = at->prox ; 
            }

        }

    }

    return 0 ;

}

void liberar_no_lista(NO **i){

    if((*i) == NULL) return ; 
    
    liberar_no_lista(&((*i)->prox));

    (*i)->prox = NULL ;
    free(*i); i = NULL ; 
}

void liberar_nos_cabecas(NO **i){
    
    if((*i) == NULL) return ; 

    liberar_nos_cabecas(&((*i)->baixo));

    (*i)->baixo = NULL ;
    item_apagar(&(*i)->item);
    free(*i); (*i) = NULL ; 

}

void skip_apagar(SKIP **skip){

    for(NO *i = (*skip)->ini ; i != NULL ; i = i->baixo) {
        if (i->baixo == NULL) {
            for(NO* j = i; j != NULL; j = j->prox) {
                item_apagar(&(j->item));
            }
        }
    }

    for(NO *i = (*skip)->ini ; i != NULL ; i = i->baixo){ // liberar lista
        if(i->prox != NULL) liberar_no_lista(&(i->prox));
    }

    liberar_nos_cabecas(&((*skip)->ini));

    free(*skip);
    *skip = NULL ; 
}
