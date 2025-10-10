#include "header_pessoa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
            CREATE_INDEX("arquivoIndicePrimario.bin");

            CREATE_TABLE("arquivosEntrada.csv", "arquivoSaida.bin", "arquivoIndicePrimario.bin");

            SELECT("arquivoSaida.bin");
    return 0;
}
