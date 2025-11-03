//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"





//funcionalidade 6 (INSERT_INTO)
void INSERT_INTO( char *arquivoPessoa, char *arquivoIndicePrimario, int NInsert){

    FILE *fdout = fopen(arquivoPessoa, "rb+"); // abrindo o arquivo para a escrita binaria no arquivo de dados
    if(fdout == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;// verificando se o arquivo foi aberto corretamente
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb+"); // abrindo o arquivo para a escrita binaria no indice
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;// verificando se o arquivo foi aberto corretamente
    }


    //ler cabecalho do arquivo de dados pessoa e status inconsistente
    header hp;
    INICIO_ARQUIVO(fdout);
    fread(&hp.status, sizeof(char), 1, fdout);
    if(hp.status=='0'){printf("arquivo pessoa inconsistente");
    return;}
    hp.status = '0'; //status incosistente
    INICIO_ARQUIVO(fdout);
    fwrite(&hp.status, sizeof(char), 1, fdout);
    fread(&hp.quantidadePessoas, sizeof(int), 1, fdout);
    fread(&hp.quantidadeRemovidos, sizeof(int), 1, fdout);
    fread(&hp.Offset, sizeof(long), 1, fdout);

    //criar cabecalho do arquivo de indice e status inconsistente
    headerIndice hi;
    INICIO_ARQUIVO(fdh);
    fread(&hi.status, sizeof(char), 1, fdh);
    if(hi.status=='0'){printf("arquivo indice inconsistente");
    return;}

    hi.status = '0'; //status incosistente
    INICIO_ARQUIVO(fdh);
    fwrite(&hi.status, sizeof(char), 1, fdh);
    //Ler os dados
    //removido -> tamanho registro -> idPessoa -> idadePessoa -> tamanho nomePessoa -> nomePessoa -> tamanho nomeUsuario -> nomeUsuario
    pessoa p;
    char l[TAMANHO_LINHA]; // linha para ler os dados
    fseek(fdout, hp.Offset, SEEK_SET);

    for(int i = 0;i<NInsert;i++){
        
        scanf("%s",l);


        int tamNomePessoa;
        int tamNomeUsuario;

    //id Pessoa
        scanf("%*c");
        scanf("%[^,]", l);
        if(strcmp(l,"NULO")!=0 && strlen(l) > 0){
            p.idPessoa = atoi(l);
        }else{
            p.idPessoa = -1;
        }
        
    //nome Pessoa
        scanf("%*c");
        scan_quote_string(l);
        if(strcmp(l,"NULO")!=0 && strlen(l) > 0){
            // Remover o caractere de nova linha, se presente
            size_t len = strlen(l);
            if (len > 0 && (l[len-1] == '\n' || l[len-1] == '\r')) {
                l[len-1] = '\0';
                len--;
            }
        // Se a string ainda contiver \r, remova-o também
        if (len > 0 && l[len-1] == '\r') {
            l[len-1] = '\0';
            len--;
        }
        if (len > 0 && l[len-1] == '\"') {
            l[len-1] = '\0';
            len--;
        }
            p.nomePessoa = strdup(l);
            tamNomePessoa = len;
        }else{
            p.nomePessoa = NULL;
            tamNomePessoa = 0;
        }
       
    //idade Pessoa
        scanf("%*c");
        scanf("%[^,]", l);
        if(strcmp(l,"NULO")!=0 && strlen(l) > 0){
            p.idadePessoa = atoi(l);
        }else{
            p.idadePessoa = -1;
        }
    
    //nome Usuario
        scanf("%*c");
        scan_quote_string(l);
        if(strcmp(l,"NULO")!=0 && strlen(l) > 0){
            // Remover o caractere de nova linha, se presente
            size_t len = strlen(l);
            if (len > 0 && (l[len-1] == '\n' || l[len-1] == '\r')) {
                l[len-1] = '\0';
                len--;
            }
        if (len > 0 && l[len-1] == '\r') {
            l[len-1] = '\0';
            len--;
        }
            p.nomeUsuario = strdup(l);
            tamNomeUsuario = len;
        }else{
            p.nomeUsuario = NULL;
            tamNomeUsuario = 0;
        }

    //calculando tamanho do registro;
        int tamReg = 16 + tamNomePessoa + tamNomeUsuario;
        p.removido = '0';//colocando como não removido
    //escrevendo no arquivo binario os dados lidos
        fseek(fdout,0,SEEK_END);
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
        i.idPessoa = p.idPessoa;
        i.Offset = Offset;
        inserirIndiceOrdenado(fdh, i);
        


    }



    //atualizando cabecalho do arquivo de dados binario
    hp.Offset = ftell(fdout);
    INICIO_ARQUIVO(fdout);
    hp.status = '1'; //status consistente
    fwrite(&hp.status, sizeof(char), 1, fdout);
    fwrite(&hp.quantidadePessoas, sizeof(int), 1, fdout);


    //atualizando cabecalho do arquivo de indice
    INICIO_ARQUIVO(fdh);
    hi.status = '1'; //status consistente
    fwrite(&hi.status, sizeof(char), 1, fdh);

    //fechar os arquivos
    fclose(fdout);
    fclose(fdh);

    binarioNaTela(arquivoPessoa);
    binarioNaTela(arquivoIndicePrimario);
}
