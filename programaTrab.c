#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


int main(){

int funcionalidade, buscas;
char* arquivoEntrada;
char* arquivoSaida;
char arquivoIndice;
char f;
char str1[100];
char b;


    
    scanf("%s", str1);
    f = strtok(str1," ");
    funcionalidade = atoi(f);
    switch (funcionalidade)
    {
    case 1:
        arquivoIndice = strtok(NULL, " ");
        CREATE_INDEX(arquivoIndice);
        break;
    case 2:
        arquivoEntrada = strtok(NULL, " ");
        arquivoSaida = strtok(NULL, " ");
        arquivoIndice = strtok(NULL, " ");
        CREATE_TABLE(arquivoEntrada, arquivoSaida, arquivoIndice);
        break;
    case 3:
        arquivoEntrada = strtok(NULL, " ");
        SELECT(arquivoEntrada);
        break;
    case 4:
//        arquivoEntrada = strtok(NULL, " ");
  //      arquivoIndice = strtok(NULL, " ");
    //    b = strtok(NULL, " ");
      //  buscas = atoi(b);
        //Select_Where(arquivoEntrada, arquivoIndice, buscas);
        break;
    
    default:
        break;
    }



return 0;
}
