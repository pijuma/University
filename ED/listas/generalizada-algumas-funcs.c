#include "gen.h"

struct NO_{
	int tipo ; 
	union{
		ITEM *x ;
		struct NO_ *sub_list ; 
	} info ; 
	struct NO_ *prox ; 
} ;

typedef struct NO_ NO ;

void print(NO *at){

	if(at == NULL) return ; 

	if(at->tipo){ // sublista
		print(at->info.sub_list) ; 
	}

	else printf("%d ", item_get_chave(at->info.x)) ; 

	print(at->prox) ; 

}

ITEM *find(NO *at, ITEM *x){

	if(at == NULL) return NULL ; 

	if(at->tipo){ // sub
		return print(at->info.sub_list) ; 
	}

	else{
		if(item_get_chave(at->info.x) == item_get_chave(x)) return at->info.x ; 
	}

	return find(at->prox) ; 

}

bool eq(NO *at, NO *at2){// so formato 

	if(at == at2 && at == NULL) return 1 ; 
	if(at == NULL || at2 == NULL) return 0 ; 

	bool ok = 1 ; 

	if(at->tipo==at2->tipo){
		if(at->tipo) eq &= eq(at->info.sub_list, at2->info.sub_list) ;
		else ok &= 1 ; 
	}

	else return 0 ; 

	return ok&eq(at->prox, at2->prox) ; 

}

bool eq(NO *at, NO *at2){// valor tb importa

	if(at == at2 && at == NULL) return 1 ; 
	if(at == NULL || at2 == NULL) return 0 ; 

	bool ok = 1 ; 

	if(at->tipo==at2->tipo){
		if(at->tipo) eq &= eq(at->info.sub_list, at2->info.sub_list) ;
		else ok &= item_get_chave(at->tipo.x) == item_get_chave(at2->tipo.x) ; 
	}

	else return 0 ; 

	return ok&eq(at->prox, at2->prox) ; 

}


