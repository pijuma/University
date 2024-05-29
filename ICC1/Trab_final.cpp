/*
   
   10/07/2023 - Trabalho final de Introdução a ciência da computação - USP São Carlos 

   Created: Tiago Zero Araújo - nºUSP: 11814183 , 
   José Carlos Andrde do Nascimento - nºUSP: 12549450 ,   
   Pietra Gullo Salgado Chaves - nºUSP: 14603822 

*/

// Inclusao das bibliotecas utilizadas no projeto
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

// Definição do tipo usado para a struct Produto: produto_t
struct Produto{
	
	char nome [256];
	long long int qtd ; 
	double price ; 

} ;

typedef struct Produto produto_t ; 

// Prototipo das funcoes utilizadas no trabalho para declaraçao
void leia_produto(char nome[256], long long int *qtd, double *price);
void IP(produto_t **produtos, long long int *tam, produto_t *atual);
void AE(produto_t *produtos, long long int code, long long int qtd);
void MP(produto_t *produtos, long long int code, double price);
void CS(double saldo);
void CE(produto_t *produtos, long long int tam);
void VE (produto_t ** produtos, double *saldo );

// Ler as informaçoes do produto da entrada padrao - usado qunado a funçao IP (inserir produto) é chamada
void leia_produto(char nome[256], long long int *qtd, double *price){

	scanf("%s" , nome) ;
	scanf("%lld", qtd) ; 
	scanf("%lf", price) ; 

}


/* Inserir produto no banco de dados do mercado.
Parametros:
	produto_t **produtos -> endereço do vetor que armazena os itens do banco de dados do mercado
	long long int *tam -> quantidade de itens diferentes do mercado 
	produto_t *atual -> produto a ser adicionado no banco de dados do mercado

Retorno: void
*/
void IP(produto_t **produtos, long long int *tam, produto_t *atual){

	(*tam)++ ; 
	(*produtos) = (produto_t *) realloc(*produtos, (*tam)*sizeof(produto_t)) ;

	strcpy(((*produtos)[(*tam)-1]).nome, atual->nome) ;   
	((*produtos)[(*tam)-1]).qtd = atual->qtd ; ((*produtos)[(*tam)-1]).price = atual->price ; 

}

/* Aumenta a quanditade no estoque de determinado produto.
Parametros:
	produto_t *produtos -> vetor que armazena os itens do banco de dados do mercado
	long long int code -> codigo do produto a ser adicionado 
	long long int qtd -> quantidade de itens ja salvos no estoque

Retorno: void
*/
void AE(produto_t *produtos, long long int code, long long int qtd){ produtos[code].qtd += qtd ; }


/* Modificar preço de um produto em especifico no estoque.
Parametros:
	produto_t *produtos -> vetor que armazena os itens do banco de dados do mercado
	long long int code -> codigo do produto a ser adicionado 
	double price -> preço novo a ser inserido

Retorno: void
*/
void MP(produto_t *produtos, long long int code, double price){ produtos[code].price = price ; }


/* Consultar saldo total no estoque, jogando a saida formatada.
Parametros:
	double saldo -> valor do salto total do estoque.

Retorno: void
*/
void CS(double saldo){
	
	printf("Saldo: %.2lf\n", saldo) ;
	
	for(int i = 1 ; i <= 50 ; i++) printf("-") ; 
	printf("\n") ; 

}

/* Consultar estoque total. Mostra as informaçoes formatadas de todos os itens armazenados no estoque.
Parametros:
	produto_t *produtos -> vetor que armazena os itens do banco de dados do mercado
	long long int tam -> tamanho do banco de dados do mercado 

Retorno: void
*/
void CE(produto_t *produtos, long long int tam){

	
	for (int i = 0; i < tam; i++){
		

		printf("%d", i );
		printf(" %s ", produtos[i].nome);
		printf("%lld\n",  produtos[i].qtd);
	}


	for(int i = 0; i < 50; i++) printf("-");
	printf("\n");

}

/* Vender um produto especifico armazenado no banco de dados do mercado.
Parametros:
	produto_t **produtos -> endereço do vetor que armazena os itens do banco de dados do mercado
	double * saldo ->  endereço do valor saldo total, para que possa ser atualizado dentro da funçao 

Retorno: void
*/
void VE (produto_t ** produtos, double *saldo ){
				
		int codigo; 
		double total_vendas = 0;

		while(1){
			scanf("%d", &codigo);
			if (codigo < 0) break ; 

			if (!(*produtos)[codigo].qtd ) continue;

			(*produtos)[codigo].qtd--;
			(total_vendas) += (*produtos)[codigo].price;

			printf("%s %.2lf\n", (*produtos)[codigo].nome, (*produtos)[codigo].price );

	}
	printf("Total: %.2lf\n", total_vendas);
	for(int i = 0; i < 50; i++) printf("-");
	printf("\n");


	(*saldo) += total_vendas;
			
}

/* Função main, principal, que é responsavel pela edição do arquivo e pela escolha das operações */
int main(void){

	FILE *fp ; 

	long long int tamanho_estoque = 0 ; double saldo_vendas = 0.00 ; 

	produto_t *produtos ; 
	produtos = (produto_t*)calloc(1, sizeof(produto_t)); 

	if((fp = fopen("estoque", "rb")) == NULL){  	
		// Caso o arquivo nao exista, le o tamanho do estoque e o saldo inicial pela entrada padrao

		scanf("%lld", &tamanho_estoque) ; 
		tamanho_estoque = 0;
		scanf("%lf", &saldo_vendas) ;

	}

	else{
		// Caso o arquivo ja exista, le o tamanho do estoque e o saldo inicial pelo arquivo

	    	fscanf(fp, "%lld ", &tamanho_estoque) ; 	
		fscanf(fp, "%lf ", &saldo_vendas) ; 

		produtos = (produto_t *) realloc(produtos, sizeof(produto_t)*tamanho_estoque) ; 


		for ( int i = 0; i < tamanho_estoque ; i++)
		{
			fread(&produtos[i], sizeof(produto_t), 1, fp) ; 
		}

	}

	// Escolha das funções
	while(1){

		char tipo[3] ; scanf("%s", tipo) ; 

		if(!strcmp("FE", tipo)){
			// Abre o estoque no modo write-binary e salva as informaçoes no arquivo
			if((fp = fopen("estoque", "wb")) == NULL){
				exit(1) ; 
			}


			fprintf(fp, "%lld \n", tamanho_estoque) ;
			fprintf(fp, "%lf \n", saldo_vendas) ; 

			for (int i = 0; i < tamanho_estoque ; i++)
			{
				fwrite(&produtos[i], sizeof(produto_t), 1, fp);
			}

			fclose(fp) ; 

			break ; 

		}

		else if(!strcmp("IP", tipo)){

			char nome[256] ; long long int qtd ; double price ; 
			leia_produto(nome, &qtd, &price) ; 
			
			produto_t atual  ;

			strcpy(atual.nome, nome) ;  

			atual.qtd = qtd ; atual.price = price ; 

			IP(&produtos, &tamanho_estoque, &atual) ; 


		}

		else if(!strcmp("AE", tipo)){
			long long int code, qtd ; scanf("%lld %lld", &code, &qtd) ; 
			AE(produtos, code, qtd) ; 
		}

		else if(!strcmp("MP", tipo)){
			long long int code ; double price ; scanf("%lld %lf", &code, &price) ;
			MP(produtos, code, price) ;  
		}

		else if(!strcmp("CS", tipo)) CS(saldo_vendas) ;

		else if(!strcmp("CE", tipo)) {
			CE(produtos, tamanho_estoque) ;
		}

		else if(!strcmp("VE", tipo)) VE (&produtos, &saldo_vendas );
	}

	// Desalocando vetores alocados dinamicamente
	free (produtos);
	return 0;

}
