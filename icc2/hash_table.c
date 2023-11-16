/*
inserção 
remoção 
busca
usando hash table 
com a função sendo h(k, i) = (k+i)%B 
B eh a qtd de buckets 
*/

#include<stdio.h>
#include<stdbool.h>

#define B 10

void inicializar(int *v){
    for(int i = 0 ; i < B ; i++) v[i] = -1 ; 
}

int inserir(int val, int *v){

    for(int i = 0 ; i < B ; i++){
        int h = (val + i)%B ; 
        if(v[h] <= -1){
            v[h] = h ; 
            return h ; 
        }
    }

    return -1 ; 

}

void apagar(int val, int *v){

    for(int i = 0 ; i < B ; i++){
        int h = (val + i)%B ; 
        if(v[h] == val){
            v[h] = -2 ; 
            return ; 
        } 
    }

}

bool busca(int val, int *v){

    for(int i = 0 ; i < B ; i++){
        int h = (val + i)%B ;
        if(v[h] == -1) return 0 ; 
        if(v[h] == val) return 1 ; 
    }

    return 0 ; 

}

int main(){

    int n ; scanf("%d", &n); 

    int hash_table[B+2] ;

    inicializar(hash_table) ;

    for(int i = 1 ; i <= n ; i++){
        char op ; scanf(" %c", &op) ; 
        int a ; scanf("%d", &a) ; 
        if(op == 'A'){
           printf("insercao %d\n", inserir(a, hash_table)) ; 
        }   
        else if(op == 'E'){
            apagar(a, hash_table);
        }
        else{
            printf("Busca %d\n", busca(a, hash_table)) ;
        }
    }

}
