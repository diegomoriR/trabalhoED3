#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 8 (CREATE TABLE)

void CREATE_TABLE_2(char *arquivoEntrada, char *arquivoSaida){

    //abrindo arquivos para a leitura e escrita
    FILE *fdin = fopen(arquivoEntrada, "r");
    if(fdin == NULL){
        printf("Falha no processamento do arquivo\n");
    }
    FILE *fdout = fopen(arquivoSaida, "wb");
    if(fdout == NULL){
        printf("Falha no processamento do arquivo\n");
    }

    //criar cabecalho do arquivo de dados segue
    headerSegue hs;
    hs.status = '0'; // status inconsistente
    INICIO_ARQUIVO(fdout);
    fwrite(&hs.status, sizeof(char), 1, fdout); //escrevendo status inconsistente
    //inicializando cabecalho
    hs.quantidadePessoas = 0;
    hs.proxRRN = 0;
    fwrite(&hs.quantidadePessoas, sizeof(int), 1, fdout);
    fwrite(&hs.proxRRN, sizeof(int), 1, fdout);

    //ler dados do csv
    //removido->idPessoaQueSegue->idPessoaQueESeguida->dataInicioQueSegue->dataFimQueSegue->grauAmizade

    segue s;
    char linha[TAMANHO_LINHA]; // linha para ler os dados
    fgets(linha, TAMANHO_LINHA, fdin);//pula linha do arquivo csv
    while(fgets(linha, TAMANHO_LINHA, fdin) != NULL){ // ler as linhas ate o final do arquivo csv
        char *str1;
        char *pointer = linha;

    //idPessoaQueSegue
        str1 = strsep(&pointer, ",");
        if(str1 != NULL){
            s.idPessoaQueSegue = atoi(str1);
        }else{
            s.idPessoaQueSegue = -1;
        }
        //printf("id:%d\n",p.idPessoa);
    //idPessoaQueESeguida
        str1 = strsep(&pointer, ",");
        if(str1 !=NULL){
            s.idPessoaQueESeguida = atoi(str1);
        }else{
            s.idPessoaQueESeguida = -1;
        }
        //dataInicioQueSegue
        str1 = strsep(&pointer, ",");
        if(str1 != NULL){
            char dataInicio[10];
            strcpy(dataInicio, str1);
            s.dataInicioQueSegue = strdup(dataInicio);
        }else{
            for(int i = 0; i < 9; i++){
                s.dataInicioQueSegue[i] = '$';
            }
        }
        //dataFimQueSegue
        str1 = strsep(&pointer, ",");
        if(str1 != NULL){
            char dataFim[10];
            strcpy(dataFim, str1);
            s.dataFimQueSegue = strdup(dataFim);
        }else{
            for(int i = 0; i < 9; i++){
                s.dataFimQueSegue[i] = '$';
            }
        }
        //grauAmizade
        str1 = strsep(&pointer, ",");
        if(str1 != NULL){
            s.grauAmizade = *str1;
        }else{
            s.grauAmizade = '$';
        }
        s.removido = '0';
    //escrevendo no arquivo binario os dados lidos
        fwrite(&s.removido, sizeof(char), 1, fdout);
        fwrite(&s.idPessoaQueSegue, sizeof(int), 1, fdout);
        fwrite(&s.idPessoaQueESeguida, sizeof(int), 1, fdout);
        if(s.dataInicioQueSegue != NULL){
        fwrite(s.dataInicioQueSegue, sizeof(char), 10, fdout);
        }
        if(s.dataFimQueSegue != NULL){
        fwrite(s.dataFimQueSegue, sizeof(char), 10, fdout);
        }
        fwrite(&s.grauAmizade, sizeof(char), 1, fdout);
    //mais um segue inserida
        hs.quantidadePessoas++;
    }

    //atualizando cabecalho do arquivo segue
    fseek(fdout, 1, SEEK_SET);
    fwrite(&hs.quantidadePessoas, sizeof(int), 1, fdout);
    fseek(fdout, 0, SEEK_END);
    hs.proxRRN = ftell(fdout);
    fseek(fdout, 5, SEEK_SET);
    fwrite(&hs.proxRRN, sizeof(int), 1, fdout);
    hs.status = '1'; //status consistente
    INICIO_ARQUIVO(fdout);
    fwrite(&hs.status, sizeof(char), 1, fdout);

    //fechar os arquivos
    fclose(fdin);
    fclose(fdout);

}
