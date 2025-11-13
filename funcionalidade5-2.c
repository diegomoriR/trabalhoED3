#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 5 DELETE
void DELETE(char *arquivoEntrada, char *arquivoIndicePrimario, int n){

    //abrindo os arquivos para leitura e escrita binaria
    FILE *fd = fopen(arquivoEntrada, "rb+");
    if(fd == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb+");
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    int buscas[n];
    char tipoBusca[15];

    headerIndice hi;
    header h;
    pessoa *p;
    indice i;
    int funcionalidade = 5;


    //numero de buscas
    for(int j = 0; j < n; j++){
        INICIO_ARQUIVO(fd);
        INICIO_ARQUIVO(fdh);
        busca_print(fd, fdh, funcionalidade);
    }

    binarioNaTela(arquivoEntrada);
    binarioNaTela(arquivoIndicePrimario);
}
