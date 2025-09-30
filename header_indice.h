#ifndef HEADER_INDICE_H
#define HEADER_INDICE_H

typedef struct _headerI{
    char status;
    char lixo[11];
}headerI;

typedef struct _indice{
    int idPessoa;
    long offSet;
}indice;

#endif
