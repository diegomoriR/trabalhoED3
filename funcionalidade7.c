//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 7 UPDATE
void UPDATE(char* arquivoEntrada, char* arquivoIndice, int n){


    FILE *fdin = fopen(arquivoEntrada, "rb+"); // abrindo o arquivo para ler os dados
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    FILE *fdh = fopen(arquivoIndice, "rb+"); // abrindo o arquivo para a escrita binaria no indice
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }
    int buscas[n];
    int i;
    char tipoBusca[15];


 



    INICIO_ARQUIVO(fdin);

    for( i=0; i<n;i++){//controle para o número de buscas


        scanf("%d",&buscas[i]);//numero da busca com o parametro
        scanf("%*c");
        scanf(" %[^=]", tipoBusca);//tipo de busca
        printf("\n%s\n",tipoBusca);
        fseek(fdin, 0, SEEK_SET);//coloca no começo do arquivo pessoa


         busca_substitui(fdin,fdh,tipoBusca);//busca o registro

        }


    fclose(fdin);
    fclose(fdh);
    binarioNaTela(arquivoEntrada);
    binarioNaTela(arquivoIndice);
    return;

}