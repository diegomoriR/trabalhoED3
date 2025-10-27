//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 3 (SELECT)
void SELECT(char *arquivoSaida){

    FILE *fd = fopen(arquivoSaida, "rb"); //abrindo o arquivo de dados pessoa para a leitura binaria
    if(fd == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    header h;
    fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
    fread(&h.quantidadePessoas, sizeof(int), 1, fd);
    //printf("qtdep:%d\n",h.quantidadePessoas);
    fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
    //printf("qtder:%d\n",h.quantidadeRemovidos);
    fread(&h.Offset,sizeof(long), 1, fd);
    //printf("offset:%ld\n",h.Offset);
    int qtdePessoas = h.quantidadePessoas;
    int qtdeRemovidos = h.quantidadeRemovidos;
    


    //ler todos os dados das pessoas
    pessoa p;
    //removido -> tamanho registro -> idPessoa -> idadePessoa -> tamanho nomePessoa -> nomePessoa -> tamanho nomeUsuario -> nomeUsuario
    for(int i = 0; i <qtdePessoas; i++){
        fread(&p.removido,sizeof(char), 1, fd);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
        
        if(p.removido == '0'){ //registro nao esta marcado como removido
            
            fread(&p.idPessoa, sizeof(int), 1, fd);
            fread(&p.idadePessoa, sizeof(int), 1, fd);
            fread(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
            p.nomePessoa = (char *) malloc(p.tamanhoNomePessoa + 1);
            fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
            p.nomePessoa[p.tamanhoNomePessoa] = 0;
            fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fd);
            p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario+1);
            fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
            p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
            //idPessoa
            if(p.idPessoa != -1){
                printf("Dados da pessoa de codigo %d\n", p.idPessoa);
            }else{
                printf("Dados da pessoa de codigo -\n");
            }
            //nomePessoa
            if(p.tamanhoNomePessoa != 0){
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
            if(p.tamanhoNomeUsuario != 0){
                printf("Usuario: %s\n", p.nomeUsuario);
            }else{
                printf("Usuario: - \n");
            }
            printf("\n");
            free(p.nomePessoa);
            free(p.nomeUsuario);

        }else{
            printf("Registro inexistente\n\n");
            fseek(fd,p.tamanhoRegistro,SEEK_CUR);
        }
        }

        fclose(fd);

        
}

