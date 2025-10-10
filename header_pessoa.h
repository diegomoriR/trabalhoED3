#ifndef HEADER_PESSOA_H
#define HEADER_PESSOA_H
#include <stdio.h>

typedef struct _header{
    char status;
    int quantidadePessoas;
    int quantidadeRemovidos;
    long Offset;
}header;

typedef struct _pessoa{
    char removido;
    int tamanhoRegistro;
    int idPessoa;
    int idadePessoa;
    int tamanhoNomePessoa;
    int tamanhoNomeUsuario;
    char *nomePessoa;
    char *nomeUsuario;
}pessoa;

typedef struct _headerIndice{
    char status;
}headerIndice;

typedef struct _indice{
    int idPessoa;
    long Offset;
}indice;



#define TAMANHO_INDICE 12
#define INICIO_ARQUIVO(fd) fseek(fd, 0 , SEEK_SET)
#define TAMANHO_LINHA 1024

void CREATE_INDEX(char *arquivoIndicePrimario);
void CREATE_TABLE(char *arquivoEntrada, char *arquivoSaida, char *arquivoIndicePrimario);
void SELECT(char *arquivoSaida);
void scan_quote_string(char *str);
void binarioNaTela(char *nomeArquivoBinario);
char *mystrsep(char **str, char const *delim);



#endif

