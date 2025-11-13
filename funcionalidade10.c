#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

//funcionalidade 10 (JUNCAO)

void JUNCAO(char *arquivoEntrada, char *arquivoIndicePrimario, char *arquivoOrdenado, int n){
    FILE *fdin = fopen(arquivoEntrada, "rb");
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb");
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    FILE *fdo = fopen(arquivoOrdenado, "rb");
    if(fdo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }


    //numero de buscas
    for(int i=0; i < n; i++){//controle para o número de buscas

        fseek(fdin, 0, SEEK_SET);//coloca no começo do arquivo pessoa
        busca(fdin, fdh, fdo);
    }

    fclose(fdin);
    fclose(fdh);
    fclose(fdo);
    return;

}

    free(p);
}

