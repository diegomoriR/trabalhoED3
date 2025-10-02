#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"
#include "header_indice.h"

//funcionalidade 3 (SELECT)
void Select(FILE* arquivoEntrada){

char* rem;
char lixo;
char* nome;
char* usuario;
char TamReg;
int qtdPessoas;
int id, idade, TAM_nPessoa, TAM_nUsuario;

    FILE *fd = fopen("arquivoEntrada.bin", "rb"); //abrindo o arquivo para a leitura binaria
    VERIFICAR_ARQUIVO(arquivoEntrada); // verificando se o arquivo foi aberto corretamente

    fread(lixo, sizeof(char),1,arquivoEntrada);
    fread(qtdPessoas, sizeof(int), 1, arquivoEntrada);
    INICIO_ARQUIVO(arquivoEntrada);
    fseek(arquivoEntrada,17,SEEK_CUR);



    for(int i = 0; i < qtdPessoas; i++){
        fscanf(arquivoEntrada,"%c", rem);
        fscanf(arquivoEntrada,"%d", TamReg);
        if(rem==0){
        fscanf(arquivoEntrada,"%d", &id);
        printf("Dados da pessoa do código %d\n",id);
        fscanf(arquivoEntrada,"%d",&idade);
        fscanf(arquivoEntrada,"%d",&TAM_nPessoa);
        printf("Nome: ");
        if(TAM_nPessoa>0){
        fgets(nome,TAM_nPessoa,arquivoEntrada);
        fputs(nome, stdout);}
        else{printf("--");}
        printf("\nIdade: %d\n", idade);
        fscanf(arquivoEntrada,"%d",&TAM_nUsuario);
        fgets(usuario,TAM_nUsuario,arquivoEntrada);
        printf("Usuário: ");
        fputs(usuario, stdout);
        printf("\n\n");}
        else{fseek(arquivoEntrada,TamReg-5,SEEK_CUR);}

    }
    return;

}