#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"
//#include "utilidades.h"


//funcionalidade 2 (CREATE TABLE)
void CREATE_TABLE(char *arquivoEntrada, char *arquivoSaida, char *arquivoIndicePrimario){
    FILE *fdin = fopen(arquivoEntrada, "r"); // abrindo o arquivo para ler os dados
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
    }
    FILE *fdout = fopen(arquivoSaida, "wb"); // abrindo o arquivo para a escrita binaria no arquivo de dados
    if(fdout == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "wb"); // abrindo o arquivo para a escrita binaria no indice
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
    }

    //criar cabecalho do arquivo de dados pessoa e status inconsistente
    header hp;
    hp.status = '0'; //status incosistente
    fwrite(&hp.status, sizeof(char), 1, fdout);
    hp.quantidadePessoas = 0;
    hp.quantidadeRemovidos = 0;  //iniciando o cabecalho
    hp.Offset = 0;
    fwrite(&hp.quantidadePessoas, sizeof(int), 1, fdout);
    fwrite(&hp.quantidadeRemovidos, sizeof(int), 1, fdout);
    fwrite(&hp.Offset, sizeof(long), 1, fdout);

    //criar cabecalho do arquivo de indice e status inconsistente
    headerIndice hi;
    INICIO_ARQUIVO(fdh);
    fread(&hi.status, sizeof(char), 1, fdh);
    hi.status = '0'; //status incosistente
    INICIO_ARQUIVO(fdh);
    fwrite(&hi.status, sizeof(char), 1, fdh);
    fseek(fdh, 12, SEEK_SET);

    //Ler os dados do arquivo csv
    //removido -> tamanho registro -> idPessoa -> idadePessoa -> tamanho nomePessoa -> nomePessoa -> tamanho nomeUsuario -> nomeUsuario
    pessoa p;
    char linha[TAMANHO_LINHA]; // linha para ler os dados
    fgets(linha, TAMANHO_LINHA, fdin);//pula linha do arquivo csv
    while(fgets(linha, TAMANHO_LINHA, fdin) != NULL){ // ler as linhas ate o final do arquivo csv
        char *str1;
        char *pointer = linha;
        int tamNomePessoa;
        int tamNomeUsuario;

    //id Pessoa
        str1 = mystrsep(&pointer, ",");
        if(str1 != NULL){
            p.idPessoa = atoi(str1);
        }else{
            p.idPessoa = -1;
        }
        //printf("id:%d\n",p.idPessoa);
    //nome Pessoa
        str1 = mystrsep(&pointer, ",");
        if(str1 != NULL){
            char nomePessoa[100];
            strcpy(nomePessoa, str1);
            p.nomePessoa = strdup(nomePessoa);
            //calculando tamanho do campo nome Pessoa
            tamNomePessoa = strlen(p.nomePessoa);
        }else{
            p.nomePessoa = NULL;
            tamNomePessoa = 0;
        }
        //printf("nome:%s\n", p.nomePessoa);
        //printf("tamanho nome:%d\n",tamNomePessoa);
        //removido -> tamanho registro -> idPessoa -> idadePessoa -> tamanho nomePessoa -> nomePessoa -> tamanho nomeUsuario -> nomeUsuario
    //idade Pessoa
        str1 = mystrsep(&pointer, ",");
        if(str1 != NULL && strcmp(str1,"")!=0){
            p.idadePessoa = atoi(str1);
        }else{
            p.idadePessoa = -1;
        }
        //printf("idade:%d\n", p.idadePessoa);
    //nome Usuario
        str1 = mystrsep(&pointer, ",");
        if(str1 != NULL){
            char nomeUsuario[100];
            strcpy(nomeUsuario, str1);
            p.nomeUsuario = strdup(nomeUsuario);
            //calculando tamanho do campo nome Usuario
            tamNomeUsuario = strlen(p.nomeUsuario) - 1;
        }else{
            p.nomeUsuario = NULL;
            tamNomeUsuario = 0;
        }
        //printf("tamanho usuario:%d\n",tamNomeUsuario);
        //printf("usuario: %s\n", p.nomeUsuario);

    //calculando tamanho do registro;
        int tamReg = 21 + tamNomePessoa + tamNomeUsuario;
        p.removido = '0';
    //escrevendo no arquivo binario os dados lidos
        long Offset = ftell(fdout);
        fwrite(&p.removido, sizeof(char), 1, fdout);
        fwrite(&tamReg, sizeof(int), 1, fdout);
        fwrite(&p.idPessoa, sizeof(int), 1, fdout);
        fwrite(&p.idadePessoa, sizeof(int), 1, fdout);
        fwrite(&tamNomePessoa, sizeof(int), 1, fdout);
        if(p.nomePessoa != NULL){
        fwrite(p.nomePessoa, sizeof(char), tamNomePessoa, fdout);
        }
        fwrite(&tamNomeUsuario, sizeof(int), 1, fdout);
        if(p.nomeUsuario != NULL){
        fwrite(p.nomeUsuario, sizeof(char), tamNomeUsuario, fdout);
        }
    //mais uma pessoa inserida
        hp.quantidadePessoas++;
    //escrevendo o arquivo do indice
        indice i;
        i.idPessoa = p.idPessoa;
        i.Offset = Offset;
        //ordenar os indices
        inserirIndiceOrdenado(fdh, i);
        //printf("id:%d\n",p.idPessoa);
        //printf("offset:%ld\n",i.Offset);
        fwrite(&i.idPessoa, sizeof(int), 1, fdh);
        fwrite(&i.Offset, sizeof(long), 1, fdh);

    }
    //atualizando cabecalho do arquivo de dados binario
    INICIO_ARQUIVO(fdout);
    hp.status = '1'; //status consistente
    fwrite(&hp.status, sizeof(char), 1, fdout);
    fwrite(&hp.quantidadePessoas, sizeof(int), 1, fdout);
    fwrite(&hp.quantidadeRemovidos, sizeof(int), 1, fdout);
    fseek(fdout, 0, SEEK_END);
    hp.Offset = ftell(fdout);
    fseek(fdout, 9, SEEK_SET);
    fwrite(&hp.Offset, sizeof(long), 1, fdout);

    //atualizando cabecalho do arquivo de indice
    INICIO_ARQUIVO(fdh);
    hi.status = '1'; //status consistente
    fwrite(&hi.status, sizeof(char), 1, fdh);

    //fechar os arquivos
    fclose(fdin);
    fclose(fdout);
    fclose(fdh);

    binarioNaTela(arquivoSaida);
    binarioNaTela(arquivoIndicePrimario);
}
