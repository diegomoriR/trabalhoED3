//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"





//funcionalidade 2 (CREATE TABLE)
void CREATE_TABLE(char *arquivoEntrada, char *arquivoSaida, char *arquivoIndicePrimario){
    FILE *fdin = fopen(arquivoEntrada, "r"); // abrindo o arquivo para ler os dados
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;// verificando se o arquivo foi aberto corretamente
    }
    FILE *fdout = fopen(arquivoSaida, "wb"); // abrindo o arquivo para a escrita binaria no arquivo de dados
    if(fdout == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;// verificando se o arquivo foi aberto corretamente
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb+"); // abrindo o arquivo para a escrita binaria no indice
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;// verificando se o arquivo foi aberto corretamente
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
    if(hi.status=='0'){printf("arquivo indice inconsistente");
    return;}

    hi.status = '0'; //status incosistente
    INICIO_ARQUIVO(fdh);
    fwrite(&hi.status, sizeof(char), 1, fdh);
    for(int i = 0; i < TAMANHO_INDICE - 1; i++){
        fputc('$', fdh);
    }
    //Ler os dados do arquivo csv
    //removido -> tamanho registro -> idPessoa -> idadePessoa -> tamanho nomePessoa -> nomePessoa -> tamanho nomeUsuario -> nomeUsuario
    pessoa p;
    char l[TAMANHO_LINHA]; // linha para ler os dados

    fgets(l, TAMANHO_LINHA, fdin);//pula linha do arquivo csv
    while(fgets(l, TAMANHO_LINHA, fdin) != NULL){ // ler as linhas ate o final do arquivo csv
        
        if (l[0] == '\n' || l[0] == '\r' || l[0] == '\0') {
        continue;
    }
        char* str1;
        char* linha = l;
        int tamNomePessoa;
        int tamNomeUsuario;

    //id Pessoa
        str1 = strsep(&linha, ",");
        
        if(str1 != NULL && strlen(str1) > 0){
            p.idPessoa = atoi(str1);
        }else{
            p.idPessoa = -1;
        }
        
    //nome Pessoa
        str1 = strsep(&linha,",");
        if(str1 != NULL && strlen(str1) > 0){
            // Remover o caractere de nova linha, se presente
            size_t len = strlen(str1);
            if (len > 0 && (str1[len-1] == '\n' || str1[len-1] == '\r')) {
                str1[len-1] = '\0';
                len--;
            }
        // Se a string ainda contiver \r, remova-o também
        if (len > 0 && str1[len-1] == '\r') {
            str1[len-1] = '\0';
            len--;
        }
            p.nomePessoa = strdup(str1);
            tamNomePessoa = len;
        }else{
            p.nomePessoa = NULL;
            tamNomePessoa = 0;
        }
       
    //idade Pessoa
        str1 = strsep(&linha, ",");
        if(str1 != NULL && strlen(str1) > 0){
            p.idadePessoa = atoi(str1);
        }else{
            p.idadePessoa = -1;
        }
    
    //nome Usuario
        str1 = strsep(&linha, ",");
        if(str1 != NULL && strlen(str1) > 0){
            // Remover o caractere de nova linha, se presente
            size_t len = strlen(str1);
            if (len > 0 && (str1[len-1] == '\n' || str1[len-1] == '\r')) {
                str1[len-1] = '\0';
                len--;
            }
        if (len > 0 && str1[len-1] == '\r') {
            str1[len-1] = '\0';
            len--;
        }
            p.nomeUsuario = strdup(str1);
            tamNomeUsuario = len;
        }else{
            p.nomeUsuario = NULL;
            tamNomeUsuario = 0;
        }

    //calculando tamanho do registro;
        int tamReg = 16 + tamNomePessoa + tamNomeUsuario;
        p.removido = '0';//colocando como não removido
    //escrevendo no arquivo binario os dados lidos
        long Offset = ftell(fdout);
        fwrite(&p.removido, sizeof(char), 1, fdout);
        fwrite(&tamReg, sizeof(int), 1, fdout);
        fwrite(&p.idPessoa, sizeof(int), 1, fdout);
        fwrite(&p.idadePessoa, sizeof(int), 1, fdout);
        fwrite(&tamNomePessoa, sizeof(int), 1, fdout);
        if(tamNomePessoa != 0){
        fwrite(p.nomePessoa, sizeof(char), tamNomePessoa, fdout);
        }
        fwrite(&tamNomeUsuario, sizeof(int), 1, fdout);
        if(tamNomeUsuario != 0){
        fwrite(p.nomeUsuario, sizeof(char), tamNomeUsuario, fdout);

        }
    //mais uma pessoa inserida
        hp.quantidadePessoas++;
    //escrevendo o arquivo do indice
        indice i;
        int idArquivo;
        i.idPessoa = p.idPessoa;
        i.Offset = Offset;
        
        if(i.idPessoa!=-1){ 
        fwrite(&i.idPessoa, sizeof(int), 1, fdh);
        fwrite(&i.Offset, sizeof(long), 1, fdh);
        }
    }



    //atualizando cabecalho do arquivo de dados binario
    hp.Offset = ftell(fdout);
    INICIO_ARQUIVO(fdout);
    hp.status = '1'; //status consistente
    fwrite(&hp.status, sizeof(char), 1, fdout);
    fwrite(&hp.quantidadePessoas, sizeof(int), 1, fdout);
    fwrite(&hp.quantidadeRemovidos, sizeof(int), 1, fdout);
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
