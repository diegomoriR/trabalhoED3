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
#define TAMANHO_INDICE 12

void CREATE_INDEX(char *arquivoIndicePrimario);
void CREATE_TABLE(char *arquivoEntrada, char *arquivoSaida, char *arquivoIndicePrimario);
void SELECT(char *arquivoSaida);
void Select_Where(char* arquivoEntrada, char* arquivoIndice, int n);
void DELETE(char *arquivoEntrada, char *arquivoIndicePrimario, int n);
void INSERT_INTO( char *arquivoSaida, char *arquivoIndicePrimario, int NInsert);
void UPDATE(char* arquivoEntrada, char* arquivoIndice, int n);
void CREATE_TABLE_2(char *arquivoEntrada, char *arquivoSaida);
void ORDER_BY(char* arquivoEntrada, char* arquivoSaida);


void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
void print_registro( pessoa p);
char* strsep(char** stringp, const char* delim);
void substitui_registro(FILE* fd, FILE* fdh,  pessoa p,char* campo);
int comparaSegue(const void *a, const void *b);
pessoa busca_int(FILE *fd, FILE *fdh, char *tipoBusca);
int busca_ind(int id, FILE* indices,int inicio, int fim);




#endif






