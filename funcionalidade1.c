#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"
#include "header_indice.h"

//funcionalidade 1 (CREATE INDEX)
void CREATE_INDEX(FILE *fd){
    FILE *fd = fopen("arquivoIndicePrimario.bin", "wb"); //abrindo o arquivo para a escrita binaria
    VERIFICAR_ARQUIVO(fd); // verificando se o arquivo foi aberto corretamente
    headerIndice h;
    h.status = '0'; // status inconsistente
    fwrite(&h.status, sizeof(char), 1, fd);
    for(int i = 0; i < TAMANHO_INDICE - 1, i++){
        fputc('$', fd);
    }
    h.status = '1'; //status consistente
    INICIO_ARQUIVO(fd) // cursor do arquivo para o inicio
    fwrite(&h.status, sizeof(char), 1, fd);
    fclose(fd); //fechando arquivo
}
