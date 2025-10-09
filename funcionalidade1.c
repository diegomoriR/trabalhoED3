#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"
#include "utilidades.h"

void CREATE_INDEX(char *arquivoIndicePrimario){
    FILE *fd = fopen(arquivoIndicePrimario, "wb"); //abrindo o arquivo para a escrita binaria
    if(fd == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
    }
    headerIndice h;
    h.status = '0'; // status inconsistente
    fwrite(&h.status, sizeof(char), 1, fd);
    for(int i = 0; i < TAMANHO_INDICE - 1; i++){
        fputc('$', fd);
    }
    h.status = '1'; //status consistente
    INICIO_ARQUIVO(fd); // cursor do arquivo para o inicio
    fwrite(&h.status, sizeof(char), 1, fd);
    fclose(fd); //fechando arquivo
    //binarioNaTela(arquivoIndicePrimario);
}

