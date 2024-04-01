/*
matriz de adj 
*/

#ifndef GRAPH_H
	
	#define GRAPH_H 

	#include<stdio.h>
	#include<stdlib.h>  
	#include<stdbool.h> 

	
	#define inf 1000000000

	typedef struct graph_ GRAPH ; 

	GRAPH *MyGraph(int n) ; 
	bool exist_edge(GRAPH *grafo, int a, int b) ; 
	void remove_edgge(GRAPH *grafo, int a, int b) ; 
	int *get_adj_vertex(GRAPH *grafo, int a) ; 
	void print_info(GRAPH *grafo) ; // imprime vertices e arestas 
	int numb_of_vertex(GRAPH *grafo) ; 
	void remove_graph(GRAPH **grafo) ;  
	void add_edge(GRAPH *grafo, int a, int b, int peso) ; 
	void remove_lower_edge(GRAPH *grafo) ;
	int **adjacency_matrix(GRAPH *grafo) ;

#endif 
