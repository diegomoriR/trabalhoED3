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
    int buscas[n];
    int i,b, param, k;
    char tipoBusca[15];
    char parametro[30];

    // criando headers e pessoas pra facilitar a manipulação de dados
    headerIndice hi;
    header h;
    pessoa p;
    indice j;
    
    for( i=0; i<n;i++){//controle para o número de buscas


        scanf("%d",&buscas[i]);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        fseek(fdin, 0, SEEK_SET);//coloca no começo do arquivo pessoa
        p = busca_int(fdin, fdh,tipoBusca);
        print_registro(p);
    }

    fclose(fdin);
    fclose(fdh);
    return;

}
