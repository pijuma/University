#include<stdio.h>
#include<stdlib.h> 

int **ler(int n, int m, int (**p)){

	p = (int **) malloc(n*sizeof(int *)) ; // dereferencio o ponteiro e aloco n ponteiros (um p cada linha)

	for(int i = 0 ; i < n ; i++){
		p[i] = (int *) malloc(m*sizeof(int)) ; // dereferencio o ponteiro p cada linha
		// e aloco m posições pra cada linha 
	}

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < m ; j++) scanf("%d", &p[i][j]) ; 
	}

    return p ; 

}

void escreve(int n, int m, int (**g)){

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < m ; j++) printf("%d ", g[i][j]) ; // dereferencio e imprimo a pos 
		printf("\n") ; 
	} 

	printf("\n") ; 

}

void apagar(int n, int **p){ 

	for(int i = 0 ; i < n ; i++) free(p[i]) ; 

	free(p) ; 

}

int **transposta(int n, int m, int (**p)){

	int **g = (int **) malloc(m*sizeof(int *)) ; 

	for(int i = 0 ; i < m ; i++){
		g[i] = (int *) malloc(n*sizeof(int)) ; 
	}

	for(int j = 0 ; j < m ; j++){
		for(int i = 0 ; i < n ; i++) g[j][i] = p[i][j] ; 
	}

    return g ; 

}

int main(){

	int n, m ; scanf("%d%d", &n, &m) ; 

	int **p ; // ponteiro que aponta pro ponteiro da matriz  
	int **g ; 

	p = ler(n, m, p) ; 
	g = transposta(n, m, p) ; 
	escreve(m, n, g) ; 
	apagar(n, p) ; apagar(m, g) ;//passo endereço do ponteiro - na função
	// tem um ponteiro p esse endereço - assim consigo alterar direto nele 

}
