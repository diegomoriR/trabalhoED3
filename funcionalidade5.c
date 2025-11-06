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
    int param, pos;
    char tipoBusca[15];
    char parametro[30];

    headerIndice hi;
    header h;
    pessoa p;
    indice i;

    //numero de buscas
    for(int i=0; i<n;i++){//controle para o número de buscas


        scanf("%d",&buscas[i]);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        fseek(fd, 0, SEEK_SET);//coloca no começo do arquivo pessoa
        p = busca_int(fd, fdh,tipoBusca);
        fseek(fd,-(sizeof(char)+sizeof(int)),SEEK_CUR);
        char removido = '1';
        fwrite(&removido,sizeof(char),1,fd);
        //tem que ajeitar o arquivo indice agora
    }


    fclose(fd);
    fclose(fdh);
    binarioNaTela(arquivoEntrada);
    binarioNaTela(arquivoIndicePrimario);
    return;

}




