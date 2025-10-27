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

typedef struct _headerSegue{
    char status;
    int quantidadePessoas;
    int proxRRN;
}headerSegue;

typedef struct _segue{
    char removido;
    int idPessoaQueSegue;
    int idPessoaQueESeguida;
    char *dataInicioQueSegue;
    char *dataFimQueSegue;
    char grauAmizade;
}segue;



#define TAMANHO_HEADER_INDICE 12
#define INICIO_ARQUIVO(fd) fseek(fd, 0 , SEEK_SET)
#define TAMANHO_LINHA 1024
#define NUMERO_PESSOAS h.quantidadePessoas - h.quantidadeRemovidos

void CREATE_INDEX(char *arquivoIndicePrimario);
void CREATE_TABLE(char *arquivoEntrada, char *arquivoSaida, char *arquivoIndicePrimario);
void CREATE_TABLE_2(char *arquivoEntrada, char *arquivoSaida);
void SELECT(char *arquivoSaida);
void Select_Where(char* arquivoEntrada, char* arquivoIndice, int n);
void DELETE(char *arquivoEntrada, char *arquivoIndicePrimario, int n);

void scan_quote_string(char *str);
void binarioNaTela(char *nomeArquivoBinario);
char *mystrsep(char **str, char const *delim);
void inserirIndiceOrdenado(FILE *fdh, indice novo);



#endif



#endif



