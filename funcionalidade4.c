//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"



//funcionalidade 4 (SELECT_WHERE)
void Select_Where(char* arquivoEntrada, char* arquivoIndice, int n){


    FILE *fdin = fopen(arquivoEntrada, "rb"); // abrindo o arquivo para ler os dados
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    FILE *fdh = fopen(arquivoIndice, "rb"); // abrindo o arquivo para a escrita binaria no indice
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    
    for( int i=0; i<n;i++){//controle para o número de buscas


        fseek(fdin, 0, SEEK_SET);//coloca no começo do arquivo pessoa
        busca_print(fdin, fdh);
    }

    fclose(fdin);
    fclose(fdh);
    return;

}
