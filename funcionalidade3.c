#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 3 (SELECT)
<<<<<<< HEAD
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
=======
void SELECT(char *arquivoEntrada, char *arquivoIndicePrimario){
>>>>>>> 1ff2394bb21a1ba2306778629d879b40c116153d

    FILE *fdh = fopen(arquivoIndicePrimario, "rb");//abrindo o arquivo de indice para a leitura binaria
    if(fdh == NULL){
        printf("Falha no processamento do arquivo\n");//verificando se o arquivo foi aberto corretamente
    }

    FILE *fd = fopen(arquivoIndicePrimario, "rb"); //abrindo o arquivo de dados pessoa para a leitura binaria
    if(fd == NULL){
        printf("Falha no processamento do arquivo\n");// verificando se o arquivo foi aberto corretamente
    }
    headerIndice hi;
    //verificar o status do indice para ver se ta consistente
    if(hi.status == '0'){
        printf("Falha no processamento do arquivo\n");
        return;
    }

    fseek(fdh, 12, SEEK_SET);//la o lixo do header do indice

    header h;
    fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
    fread(&h.quantidadePessoas, sizeof(int), 1, fd);
    fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
    fread(&h.Offset,sizeof(long), 1, fd);
    int qtdePessoas = h.quantidadePessoas;
    int qtdeRemovidos = h.quantidadeRemovidos;
    long Offset = h.Offset;

    //ler todos os dados das pessoas
    indice index;
    pessoa p;
    for(int i = 0; i < (qtdePessoas-qtdeRemovidos) + 1;i++){
        fread(&index.idPessoa, sizeof(int), 1, fdh);//leitura o id pessoa no indice primario
        fread(&index.Offset, sizeof(long), 1, fdh);//leitura do byteoffset no indice primario
        fseek(fd, index.Offset, SEEK_SET); // pulo no arquivo de dados para o byteoffset do indice primario
        fread(&p.removido,sizeof(char), 1, fd);
        if(p.removido == '0'){ //registro nao esta marcado como removido
            fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
            fread(&p.idPessoa, sizeof(int), 1, fd);
            fread(&p.idadePessoa, sizeof(int), 1, fd);
            fread(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
            fread(&p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
            fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fd);
            fread(&p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
            //idPessoa
            if(p.idPessoa != -1){
                printf("Dados da pessoa de codigo %d\n", p.idPessoa);
            }else{
                printf("Dados da pessoa de codigo -\n");
            }
            //nomePessoa
            if(p.nomePessoa != NULL){
                printf("Nome: %s\n", p.nomePessoa);
            }else{
                printf("Nome: - \n");
            }
            //idadePessoa
            if(p.idadePessoa != -1){
                printf("Idade: %d\n", p.idadePessoa);
            }else{
                printf("Idade: -\n");
            }
            //usuarioPessoa
            if(p.nomeUsuario != NULL){
                printf("Usuario: %s\n", p.nomeUsuario);
            }else{
                printf("Usuario: - \n");
            }
        }
    }
}
