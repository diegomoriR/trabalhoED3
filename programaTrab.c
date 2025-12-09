#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


int main(){

int funcionalidade, vezes;
char arquivoEntrada[30];
char arquivoSaida[30];
char arquivoIndice[30];
char arquivoOrdenado[30];
char nomeCelebridade[50];
char b;



    scanf("%d", &funcionalidade);

    switch (funcionalidade)
    {
    case 1:
        scanf("%s", arquivoIndice);
        CREATE_INDEX(arquivoIndice);
        break;
    case 2:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);
        scanf("%s", arquivoIndice);
        CREATE_TABLE(arquivoEntrada, arquivoSaida, arquivoIndice);
        break;
    case 3:
        scanf("%s", arquivoEntrada);
        SELECT(arquivoEntrada);
        break;
    case 4:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%d", &vezes);
        Select_Where(arquivoEntrada, arquivoIndice, vezes);
        break;
    case 5:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%d", &vezes);
        DELETE(arquivoEntrada, arquivoIndice, vezes);
        break;
    case 6:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%d", &vezes);
        INSERT_INTO(arquivoEntrada, arquivoIndice, vezes);
        break;
    case 7:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%d", &vezes);
        UPDATE(arquivoEntrada, arquivoIndice, vezes);
        break;
    case 8:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);
        CREATE_TABLE_2(arquivoEntrada,arquivoSaida);
        break;
    case 9:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);
        ORDER_BY(arquivoEntrada,arquivoSaida);
        break;
    case 10:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%s", arquivoOrdenado);
        scanf("%d", &vezes);
        JUNCAO(arquivoEntrada, arquivoIndice, arquivoOrdenado, vezes);
        break;
    case 11:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%s", arquivoOrdenado);
        FUNCIONALIDADE_11(arquivoEntrada, arquivoIndice, arquivoOrdenado);
        break;
    case 12:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%s", arquivoOrdenado);
        FUNCIONALIDADE_12(arquivoEntrada, arquivoIndice, arquivoOrdenado);
        break;
    case 13:
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoIndice);
        scanf("%s", arquivoOrdenado);
        scanf("%s", nomeCelebridade);
        FUNCIONALIDADE_13(arquivoEntrada, arquivoIndice, arquivoOrdenado, nomeCelebridade);
        break;
    default:
        break;
    }



return 0;
}
