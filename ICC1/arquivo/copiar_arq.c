// copia oq ta no arquivo fp pro arquivo hh 
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

    FILE *fp, *hh ; 
    char c ; 

    if(argc != 3){
        printf("faltou nomen\n") ; exit(1) ;
    }

    if((fp = fopen(argv[1], "rb"))==NULL){ // abre o 1o p leitura 
        printf("Erro p abrir pra leitura\n") ;
        exit(1) ;
    }

    if((hh = fopen(argv[2], "wb")) == NULL){ // abre o 2o pra escrita
        printf("Erro pra abrir pra escrita\n") ; exit(1) ;
    }
  
    //outra forma de fazer: 
    /*c = fgetc(fp) ;

    while(!feof(fp)){
        fputc(c, hh) ;
        c = fgetc(fp) ;
    }*/

    fscanf(fp, "%c", &c) ;

    while(!feof(fp)){ // passa oq ta escrito no 1o pro 2o - até o final do 1o arquivo 
        fprintf(hh, "%c", c) ;
        fscanf(fp, "%c", &c) ; 
    }

    fclose(fp) ;
    fclose(hh) ; // fecha o segundo - salva alterações 
    
}
