#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"
#include "header_indice.h"

//funcionalidade 2 (CREATE TABLE)
    FILE *fdin = fopen("arquivoEntrada.csv", "r"); // abrindo o arquivo para ler os dados
    VERIFICAR_ARQUIVO(fdin);
    FILE *fdout = fopen("arquivoSaida.bin", "wb"); // abrindo o arquivo para a escrita binaria no arquivo de dados
    VERIFICAR_ARQUIVO(fdout);
    FILE *fdh = fopen("arquivoIndicePrimario.bin", "wb"); // abrindo o arquivo para a escrita binaria no indice
    VERIFICAR_ARQUIVO(fdh)

    //criar cabecalho do arquivo de dados pessoa
    headerI hp;
    hp.status = '0' //status incosistente
    fwrite(&hp.status, sizeof(char), 1, fdout);
    hp.quantidadePessoas = 0;
    hp.quantidadeRemovidos = 0;  //iniciando o cabecalho
    hp.Offset = 0;
    fwrite(hp.quantidadePessoas, sizeof(int), 1, fdout);
    fwrite(hp.quantidadeRemovidos, sizeof(int), 1, fdout);
    fwrite(hp.Offset, sizeof(long), 1, fdout);
    hp.status = '1' //status consistente
    INICIO_ARQUIVO(fdout) // cursor do arquivo para o inicio
    fwrite(&hp.status, sizeof(char), 1, fdout);

    //Ler os dados do arquivo csv
    pessoa p; 
    char linha[TAMANHO_LINHA]; // linha para ler os dados
    fgets(linha, TAMANHO_LINHA, fdin);//pula linha do arquivo csv

    while(fgets(linha, TAMANHO_LINHA, fdin) != EOF){ // ler as linhas ate o final do arquivo csv
        char *str1;
        char *str2;
    
        //id Pessoa    
        SEPARA_LINHA(linha,str2)
        p.idPessoa = atoi(str1);
        fwrite(p.idPessoa, sizeof(int), 1, fdout);
        LINHA_NOVA
    //nome Pessoa
        SEPARA_LINHA(linha,str2)
        
    //idade Pessoa

    //nome Usuario
    }