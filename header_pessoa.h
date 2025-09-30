#ifndef HEADER_PESSOA_H
#define HEADER_PESSOA_H

typedef struct _header {
    char status;
    int quantidadePessoas;
    int quantidadeRemovidos;
    long Offset;
}header;

typedef struct _registroPessoa{
    char removido;
    int tamanhoRegistro;
    int idPessoa;
    int idadePessoa;
    int tamanhoNomePessoa;
    char nomePessoa[];
    int tamanhoNomeUsuario;
    char nomeUsuario[];
}pessoa;

#define VERIFICAR_ARQUIVO(fd) (if(fd == NULL){printf("Falha no processamento do arquivo.\n");})
#define TAMANHO_INDICE 12
#define INICIO_ARQUIVO(fd) (fseek(fd, 0 , SEEK_SET);)
#define TAMANHO_LINHA 1024
#endif
