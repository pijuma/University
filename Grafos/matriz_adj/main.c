#include "graph.h" 

/*
Pietra Gullo Salgado Chaves 14603822 
Bruno Figueiredo Lima 14562383 
Bruno Kazuya Yamato Sakaji 14562466
Vinicius Gustierrez Neves - 14749363
Lázaro Pereira Vinaud Neto - 14675396
*/

/*
para compilar todo o projeto, use: make all
*/

/*
formato Sample:
#qtd vertices -> aqui o grafo deve ser criado 
enquanto o usuario nao indicar um inteiro 0 o codigo ira rodar
é preciso que o usuario insira um inteiro que indica o tipo de operação que ele gostaria de realizar
foram adotados os seguintes padrões: 
0 -> operação de sair + excluir grafo 
1 a b -> verificar se existe uma aresta a -> b 
2 a -> retorna a lista de vertices adjascentes a "a" 
3 a b -> remove aresta a->b 
4 -> imprimir todos os vertices e arestas
5 -> quantos vertices tem o grafo? 
6 a b p-> adicionar uma aresta a -> b com peso p
7 -> remover aresta de menor peso no grafo 
8 -> retornar a matriz de adjacencia 
*/

int main(){

	printf("Digite a quantidade de vértices que o grafo possuirá: (os vértices do grafo serão 0-indexados)\n");

	int n ; scanf("%d", &n) ; 
	GRAPH *grafo = MyGraph(n) ; 

	while(1){

		printf("\nOpções: \n0       - SAIR do programa \n1 a b   - verifica se existe aresta (a->b) \n2 a     - imprime lista com todos os vértices adjacentes ao vértice a \n3 a b   - REMOVE aresta (a->b) \n4       - imprime todos os vértice e arestas do grafo \n5       - informa quantos vértices tem o grafo \n6 a b p - ADICIONA uma aresta (a->b) com peso p \n7       - remove a aresta de menor peso do grafo \n8       - imprime matriz de adjacencia do grafo \n");
		
		int id ; scanf("%d", &id) ; 
		
		if(!id) break ; 

		if(id == 1){
			int a, b ; scanf("%d %d", &a, &b) ; 
			if(exist_edge(grafo, a, b)) printf("A aresta %d -> %d existe\n", a, b) ; 
			else printf("A aresta %d -> %d não existe\n", a, b) ; 
		}

		else if(id == 2){
			int a ; scanf("%d", &a) ;
			int *v = get_adj_vertex(grafo, a) ;  
			printf("Vertices ligados a %d:\n", a) ;
			for(int i = 0 ; v[i] != -2 ; i++) printf("%d ", v[i]) ; 
			printf("\n") ; 
			free(v) ; v = NULL ;
		}

		else if(id == 3){
			int a, b ; scanf("%d %d", &a, &b) ; 
			remove_edgge(grafo, a, b) ; 
		}

		else if(id == 4) print_info(grafo) ; 

		else if(id == 5) printf("O grafo tem %d vertices\n", numb_of_vertex(grafo)) ;

		else if(id == 6){ // Se nao tiver peso coloque peso = 0 
			int a, b ; scanf("%d%d", &a, &b) ; 
			int peso ; scanf("%d", &peso) ;
			add_edge(grafo, a, b, peso) ;  
		}

		else if(id == 7) remove_lower_edge(grafo) ; 

		else if(id == 8){
			int **v = adjacency_matrix(grafo) ;
			int n = numb_of_vertex(grafo); 
			printf("Matriz de adjacência atual:\n") ; 
			for(int i = 0 ; i < n ; i++){
				for(int j = 0 ; j < n ; j++) printf("%d ", v[i][j]) ;
				printf("\n") ;  
			}
			for(int i = 0 ; i < n ; i++){
				free(v[i]) ; v[i] = NULL ; 
			}

			free(v) ; v = NULL ; 
		}

	} 

	remove_graph(&grafo) ;
}
