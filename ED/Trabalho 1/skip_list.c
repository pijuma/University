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
    skip_apagar e auxiliares -> para desalocar a memória utilizada 

*/

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include "lista.h"

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
int skip_vazia(SKIP *skip){ return skip->tam == 0 ; }

// função para criar a skip_list
SKIP *skip_criar(){

    SKIP *skip = (SKIP *) malloc(sizeof(SKIP)) ;

    if(skip == NULL) exit(1) ; 
    else { 
        
        skip->mx_lvl = 0 ; skip->tam = 0 ; skip->ini = NULL ; // inicializa o skip

        // criamos o nó sentinela inicial -> nó cabeça do nivel 0 
        NO *sentinela = (NO *) malloc(sizeof(NO)) ;
        
        if(sentinela == NULL) exit(1) ; 

        sentinela->lvl = 0 ; sentinela->item = NULL ;
        sentinela->prox = NULL ; sentinela->baixo = NULL ; 

        skip->ini = sentinela ;

    }

    return skip ; 

}

// essa função retorna o item que contém a palavra pal como chave, caso exista 
ITEM *skip_busca_key(SKIP *skip, char *pal){
    
    if(skip == NULL || skip_vazia(skip)) return NULL ; 

    NO *atual = (skip->ini) ;

    while(atual != NULL){

        if(atual->item != NULL && !strcmp(pal, item_get_key(atual->item))) return atual->item ; // achei o item 

        else if(atual->prox == NULL){ // não tenho um proximo -> devo descer
            atual = atual->baixo ; 
        }

        else{

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

// função para criar o nivel do meu nó de forma randomizada 
// fizemos dessa forma para que a quantidade de níveis não fique crescendo de forma indefinida 
int get_nivel() {

    int res = 0;

    while(1) {
        if(res > 20) break ; // colocamos um limite para a quantidade de niveis 
        int num = rand();
        if (num%2 == 0) res++;
        else break;
    }

    return res;
}

// funcao para inserir novos itens na lista  
int skip_inserir(SKIP *skip, ITEM *item){

    // se o item ja existir ou a lista nao existir nao devemos inserir 
    if(skip == NULL || skip_busca_key(skip, item_get_key(item)) != NULL) return 0 ; 

    skip->tam++ ; 

    int nivel = get_nivel();

    // meu vertice inicial de busca -> o nó cabeça mais alto que tem na skip_list 
    NO *at = skip->ini ; 

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

    // irá guardar o nó anterior que foi inserido do meu item -> posso precisar fazer conecções futuras
    // mudando o "baixo" desse anterior     
    NO *ant = NULL ; 

    while(at != NULL){

        if(at->prox == NULL){ // não tenho proximo -> existe apenas o nó cabeça 

            if(at->lvl <= nivel){ // adiciono ele se eu existir naquele nivel 

                NO *agr = (NO *)malloc(sizeof(NO)) ; 

                agr->lvl = at->lvl ; agr -> prox = NULL ; agr -> baixo = NULL ; 
                agr -> item = item ;
                at->prox = agr ; 

                if(ant != NULL){// tenho que ligar o meu de cima com meu atual
                    ant->baixo = agr ;
                }

                ant = agr ;

            }

            at = at->baixo ; 

        }

        else{

            if(strcmp(item_get_key((at->prox)->item), item_get_key(item)) > 0){//tenho que descer e adicionar o meu, caso eu exista no nivel  
                
                if(at->lvl <= nivel){ // preciso adicionar meu novo nó 

                    NO *agr = (NO *)malloc(sizeof(NO)) ;

                    agr->lvl = at->lvl ; agr->prox = NULL ; agr->baixo = NULL ; 
                    agr->item = item ;

                    if(ant != NULL){
                        ant->baixo = agr ; 
                    }

                    agr->prox = at->prox ; 
                    at->prox = agr ; 
                    ant = agr ; 

                }

                at = at->baixo ; 

            }

            else{ // senao continuo indo pra direita procurando o primeiro cara que o proximo dele eh maior que o meu para eu descer 
                at = at->prox ; 
            }

        }

    }

    return 1 ; 

}

// pietra e bruno 
// função para alterar o significado de uma palavra 
int skip_alterar(SKIP *skip, ITEM *novo_item){

    // se o item ou a skip nao existirem - não devo fazer nada - apenas retornar que deu erro 
    if(skip == NULL || skip_vazia(skip) || !skip_busca_key(skip, item_get_key(novo_item))) {
        return 0;
    }

    // ponteiro para o vertice atual - utilizado para percorrer a lista
    NO *at = skip->ini ; 

    while(at != NULL){

        if(at->item != NULL && !strcmp(item_get_key(novo_item), item_get_key(at->item))){// achei = tenho q alterar e descer nele 
            item_set_verb(at->item, item_get_verb(novo_item)) ;
            return 1 ; 
        }

        else{

            if(at->prox == NULL) at = at->baixo ; // nao tenho como ir pro prox 
            else{
                if(strcmp(item_get_key((at->prox)->item), item_get_key(novo_item))>0) at = at->baixo ; // se meu proximo eh maior que o que eu procuro -> nao preciso ir para a direita (estrutura ordenada)
                else at = at->prox ;  
            }

        }

    }

    return 0 ; 

}

// função para remover uma palavra do meu dicionario 
int skip_remover(SKIP *skip, char *pal_del){

    if(skip == NULL || skip_vazia(skip) || !skip_busca_key(skip, pal_del)) return 0 ; 

    NO *at = skip->ini ;
    int achei = 0 ; 

    while(at != NULL){

        if(at->item == NULL){ // nó cabeça
            
            if(at->prox == NULL) at = at->baixo ; // n tenho pra onde ir 

            else{

                // se meu proximo é maior do que o que eu quero -> devo descer -> todos os proximos no nivel que estou tambem serão maiores que o meu 
                if(strcmp(item_get_key((at->prox)->item), pal_del) > 0) at = at->baixo ; 
                
                else{ // tenho que apagar meu proximo? 

                    // fizemos procurando se o próximo é quem eu busco pois facilita a deleção 
                    if(!strcmp(item_get_key((at->prox)->item), pal_del)){ // tenho que apagar o meu proximo -> ele é o cara que eu procuro 
                        
                        achei = 1 ;

                        // mudando os ponteiros para retirar o item que eu quero deletar
                        NO *no_del = at->prox ; 
                        at->prox = no_del->prox ; 

                        if (no_del != NULL && at->baixo == NULL) {
                            item_apagar(&(no_del->item));
                            free(no_del) ;
                            no_del = NULL ;
                        }

                        at = at->baixo ; 
                    }

                    else at = at->prox ; 

                }

            }

        }

        else{

            if (at->prox != NULL) {
                    
                if(!strcmp(item_get_key((at->prox)->item), pal_del)){ // tenho que apagar 
                    
                    achei = 1 ; // apaguei algum cara 

                    // mudando os ponteiros 
                    NO *no_del = at->prox ; 
                    at -> prox = no_del->prox ; 

                    if (no_del != NULL && at->baixo == NULL) {
                        item_apagar(&(no_del->item));
                        free(no_del) ;
                        no_del = NULL ;
                    }
                    
                    at = at->baixo ;
                }

                else{

                    // minha proxima é maior do que a palavra que eu procuro 
                    if(strcmp(item_get_key((at->prox)->item), pal_del) > 0) at = at->baixo ; 
                    else at = at->prox ; 

                } 

            } 

            // se meu prox eh nulo so tenho a opção de descer no meu no 
            else at = at->baixo;          

        }

    }

    // retorna se a operação de deleção foi bem sucedida = achamos o item para deletar 
    return achei ; 

}

// imprime todas as palavras que começam com a letra car - em ord alfabética
int skip_imprime_char(SKIP *skip, char car){

    NO *at = skip->ini ; 

    while(at!=NULL){

        if(at->prox == NULL) at = at->baixo ; // tenho que descer 

        else{

            // to no array completo e achei onde começa oq quero imprimir 
            if(at->baixo == NULL && at->prox != NULL && car == item_get_key((at->prox)->item)[0]){ // achei e to no nó cabeça

                for(NO *i = at->prox ; i != NULL && car == item_get_key((i)->item)[0] ; i = i->prox){
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

            // tenho que descer no meu atual porque meu proximo tem caracter maior do que o que eu procuro 
            else if(car -'a' <= (item_get_key((at->prox)->item))[0]-'a') at = at->baixo ; 

            else at = at->prox ; 

        }

    }

    return 0 ;

}

// funcao pra liberar a memória alocada para os nós da lista 
void liberar_no_lista(NO **no){

    if((*no) == NULL) return ; 
    
    liberar_no_lista(&((*no)->prox));

    (*no)->prox = NULL ;
    free(*no); no = NULL ; 
}

// pietra e bruno 
// função para liberar a memória alocada para os nós cabeças
void liberar_nos_cabecas(NO **no){
    
    if((*no) == NULL) return ; 

    liberar_nos_cabecas(&((*no)->baixo));

    (*no)->baixo = NULL ;
    free(*no); (*no) = NULL ; 

}

// função para liberar os itens alocados e também chamar as funções 
// para liberar os nós da skip_list - evitando vazamento de memória
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
