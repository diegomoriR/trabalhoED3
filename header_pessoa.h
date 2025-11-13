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
#define NUMERO_RRN hs.proxRRN
#define TAMANHO_INDICE 12

void CREATE_INDEX(char *arquivoIndicePrimario);
void CREATE_TABLE(char *arquivoEntrada, char *arquivoSaida, char *arquivoIndicePrimario);
void CREATE_TABLE_2(char *arquivoEntrada, char *arquivoSaida);
void SELECT(char *arquivoSaida);
void Select_Where(char* arquivoEntrada, char* arquivoIndice, int n);
void DELETE(char *arquivoEntrada, char *arquivoIndicePrimario, int n);
void INSERT_INTO( char *arquivoPessoa, char *arquivoIndicePrimario, int NInsert);
void UPDATE(char* arquivoEntrada, char* arquivoIndice, int n);
void ORDER_BY(char* arquivoEntrada, char* arquivoSaida);
void JUNCAO(char *arquivoEntrada, char *arquivoIndicePrimario, char * arquivoOrdenado, int n);

void scan_quote_string(char *str);
void binarioNaTela(char *nomeArquivoBinario);
void quicksort(indice *vetor, int low, int high);
int partitione(indice *vetor, int low, int high);
void swape(indice *a, indice *b);
char *mystrsep(char **str, char const *delim);
void inserirIndiceOrdenado(FILE *fdh, indice novo);
void lista_segue(FILE *fdin, FILE *fdh, FILE *fdo, pessoa p);
void print_registro(pessoa p);
int comparaSegue(const void *a, const void *b);
void busca(FILE *fd, FILE *fdh, FILE *fdo);
segue* busca_binaria(segue *vetor, int tamanho, int idBusca);
long busca_binaria_indice(indice* vetor, int n, int valor);
void busca_substitui(FILE *fd, FILE *fdh);
int busca_binaria_indice_atualiza(indice* vetor, int n, int valor);
void busca_print(FILE *fd, FILE *fdh, int funcionalidade);
void substitui_registro(FILE* fd, FILE* fdh,  pessoa p, long offsetP);
void remover_registro(FILE *fdin, FILE *fdh, pessoa p);




#endif






