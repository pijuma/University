#include "graph.h"

/*

o codigo foi feito considerando um grafo 0-indexado
assim os vertices vao de 0 a n-1 

O tad considera que o grafo pode ser direcionado ou nao direcionado
para isso existirá uma flag nas funções necessarias 

para caso o grafo nao tenha peso basta o usuario colocar peso 0 em todas as arestas 
a serem adicionadas

como a estrutura utilizada para representar o grafo é uma matriz de adjacencia
não serão aceitos arestas multiplas, pois não há como representar

foi considerado que caso seja ponderado, o maior peso não irá exceder 1e9 
*/

struct graph_{

	int n ; //qtd de vertices

	int **matriz ; //matriz de adjacencia 

} ; 

GRAPH *MyGraph(int n){

	GRAPH *new_graph = (GRAPH *) malloc(sizeof(GRAPH)) ;
	
	if(new_graph == NULL) return NULL ; 
	
	new_graph->n = n ; 
	new_graph->matriz = (int **) malloc(sizeof(int *)*n) ; 
	
	for(int i = 0 ; i < n ; i++){
		new_graph->matriz[i] = (int *) malloc(sizeof(int)*n) ; 
	}
	
	//inicialmente nao tem aresta
	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++) new_graph->matriz[i][j] = -1 ; 
	}
	
	return new_graph ; 
} 

void remove_edgge(GRAPH *grafo, int a, int b){
	if(grafo->matriz[a][b] == -1){
		printf("Não é possível remover a aresta %d -> %d pois ela nao existe\n", a, b);
		return;
	} 
	printf("A aresta %d -> %d foi removida\n", a, b) ;
	grafo->matriz[a][b] = -1 ; 
}

bool exist_edge(GRAPH *grafo, int a, int b){ return grafo->matriz[a][b] != -1 ; }

int *get_adj_vertex(GRAPH *grafo, int a){
	
	int ct = 1 ; 

	int n = grafo->n ; 

	for(int i = 0 ; i < n ; i++) ct += (grafo->matriz[a][i] != -1) ;
	
	int *v = (int *) malloc(sizeof(int *)*ct) ; 
	
	int j = 0 ; 
	for(int i = 0 ; i < n ; i++){
		if(grafo->matriz[a][i] == -1) continue ; 
		v[j++] = i ; 
	}

	v[j] = -2 ; // indica o termino da lista  

	return v ; 

}

// imprime vertices e arestas 

void print_info(GRAPH *grafo){

	int n = grafo->n ; 

	printf("Os vertices do grafo são:\n") ; 
	for(int i = 0 ; i < n ; i++) printf("%d ", i) ; 
	printf("\n");

	printf("As arestas do grafo são:\n");

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			if(grafo->matriz[i][j]!=-1){
				if(!grafo->matriz[i][j]){
					printf("%d -> %d\n", i, j) ; 
				}
				else{
					printf("%d -> %d (peso %d)\n", i, j, grafo->matriz[i][j]) ; 
				}
			}
		}
	}
	
	printf("\n") ; 

} 

int numb_of_vertex(GRAPH *grafo){ return grafo->n ; }

void remove_graph(GRAPH **grafo){

	int n = (*grafo)->n ; 

	if(*grafo == NULL) return ; 

	for(int i = 0 ; i < n ; i++){
		free((*grafo)->matriz[i]) ; 
		(*grafo)->matriz[i] = NULL ; 
	}

	free((*grafo)->matriz) ; (*grafo)->matriz = NULL ; 
	free(*grafo) ; *grafo = NULL ;

}  

void add_edge(GRAPH *grafo, int a, int b, int peso){
	if(grafo->matriz[a][b] != -1){
		printf("Não é possível adicionar a aresta %d -> %d pois ela já existe\n", a, b);
		return;
	}
	printf("A aresta %d -> %d foi adicionada\n", a, b) ;
	grafo->matriz[a][b] = peso ; 
}

void remove_lower_edge(GRAPH *grafo){

	int mn = inf ; int a = -1, b = -1 ; 

	int n = grafo->n ; 

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			if(grafo->matriz[i][j] == -1) continue ; 
			if(mn > grafo->matriz[i][j]){
				mn = grafo->matriz[i][j] ; 
				a = i, b = j ; 
			}
		}
	}

	if(a != -1){
		printf("Aresta (%d -> %d), de peso %d, removida com sucesso!\n", a, b, grafo->matriz[a][b]);
		grafo->matriz[a][b] = -1 ; 
	}
	else{
		printf("Não há arestas para serem removidas\n") ; 
	}

}

int **adjacency_matrix(GRAPH *grafo){

	int n = grafo->n ; 

	int **v = (int **) malloc(sizeof(int *)*n) ; 
	for(int i = 0 ; i < n ; i++) v[i] = (int *) malloc(sizeof(int)*n) ; 

	if(v == NULL) return v ; 

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			v[i][j] = grafo->matriz[i][j] ; 
		}
	} 

	return v ; 

}
