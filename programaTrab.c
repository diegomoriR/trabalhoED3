#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"
#include "header_indice.h"

int main(int argc, char *argv[]){

int funcionalidade, buscas;



FILE *arquivoEntrada = fopen(argv[2], "rb");
FILE *arquivoSaida = fopen(argv[2], "rb");
FILE *arquivoIndice = fopen(argv[2], "rb");

    funcionalidade = atoi(argv[1]);
    switch (funcionalidade)
    {
    case 1:
        FILE *arquivoIndice = fopen(argv[2], "wb");
        CREATE_INDEX(arquivoIndice);
        break;
    case 2:
        FILE *arquivoEntrada = fopen(argv[2], "rb");
        FILE *arquivoSaida = fopen(argv[3], "wb");
        FILE *arquivoIndice = fopen(argv[4], "wb");
        void CREATE_TABLE(arquivoEntrada, arquivoSaida, arquivoIndicePrimario);
        break;
    case 3:
        FILE *arquivoEntrada = fopen(argv[2], "rb");
        Select(arquivoEntrada);
        break;
    case 4:
        FILE *arquivoEntrada = fopen(argv[2], "rb");
        FILE *arquivoIndice = fopen(argv[3], "wb");
        buscas = atoi(argv[4]);
        Select_Where(arquivoEntrada, arquivoIndice, buscas);
        break;
    
    default:
        break;
    }



return 0;}