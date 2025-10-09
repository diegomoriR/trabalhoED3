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
        
        fread(rem,sizeof(char),1, arquivoEntrada);
        fread(&tamReg,sizeof(int),1, arquivoEntrada);
        if(rem==0){
        fread(&id,sizeof(int),1,arquivoEntrada);
        printf("Dados da pessoa do código %d\n",id);
        fread(&idade,sizeof(int),1,arquivoEntrada);
        fread(&TAM_nPessoa,sizeof(int),1,arquivoEntrada);
        printf("Nome: ");
        if(TAM_nPessoa>0){
        freads(nome,sizeof(char),TAM_nPessoa,arquivoEntrada);
        fputs(nome, stdout);}
        else{printf("--");}
        printf("\nIdade: %d\n", idade);
        fread(&TAM_nUsuario,sizeof(int),1,arquivoEntrada);
        fread(usuario,sizeof(char),TAM_nUsuario,arquivoEntrada);
        printf("Usuário: ");
        fputs(usuario, stdout);
        printf("\n\n");}
        else{fseek(arquivoEntrada,tamReg-5,SEEK_CUR);}

    }
    return;

}