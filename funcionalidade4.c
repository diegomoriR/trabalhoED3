#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 4 (SELECT_WHERE)
void Select_Where(char* arquivoEntrada, char* arquivoIndice, int n){


    FILE *fdin = fopen(arquivoEntrada, "r"); // abrindo o arquivo para ler os dados
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
    }

    FILE *fdh = fopen(arquivoIndice, "rb"); // abrindo o arquivo para a escrita binaria no indice
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
    }
    int buscas[n];
    int i,b, param, k, tamReg, idade,TAM_nPessoa,TAM_nUsuario, idPessoa, byteOffset;
    char busca[15];
    char* tipoBusca, nome, nomeUsuario, usuario;
    char* parametro[30];

    // criando headers e pessoas pra facilitar a manipulação de dados
    headerIndice hi;
    header h;
    pessoa p;
    b=1;//seta o número de buscas para primeira busca
    for( i=0; i<n;i++){

        
        scanf("%s",busca);
        buscas[i] = atoi(strtok(busca," "));//numero de buscas com o parametro
        fseek(fdin, 0, SEEK_SET);//coloca no começo do arquivo pessoa
        tipoBusca = strtok(NULL,'=');//qual o tipo de busca
        if(strcmp(tipoBusca,"idPessoa")==0){
            param = strtok(NULL,' ');// pega o parametro a ser buscado
            fread(&hi.status,sizeof(char),1,arquivoIndice);// vê o status do arquivo de indice
            fseek(arquivoIndice,11, SEEK_SET);// vai para 
            fread(&h.status,sizeof(char),1,arquivoEntrada);
            fread(h.quantidadePessoas,sizeof(int),1,arquivoEntrada);

             for(k=0;k<h.quantidadePessoas;k++){
                
             fread(&idPessoa,sizeof(int),1,arquivoIndice);
             if(idPessoa == param){
             
                    
               fread(&p.removido,sizeof(char), 1, fdin);
               fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
               if(p.removido == '0'){ //registro nao esta marcado como removido
                if(b==buscas[i]){// verifica se esta no numero correto da busca
                 fread(&p.idPessoa, sizeof(int), 1, fdin);
                 fread(&p.idadePessoa, sizeof(int), 1, fdin);
                 fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                 fread(&p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                 fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
                fread(&p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
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
               }else{b++;//aumenta número da busca
                fseek(fdin, p.tamanhoRegistro,SEEK_CUR);//pula para o próximo registro
            }
            }else{
                 fseek(fdin, p.tamanhoRegistro,SEEK_CUR);//pula para o próximo registro
            }
            }
            }
        }


        else if(strcmp(tipoBusca,"idade")==0){
            param = strtok(NULL,'\n');
            fscanf(arquivoEntrada,"%c",h.status);
            fscanf(arquivoEntrada,"%d",j);
            fseek(arquivoEntrada,16, SEEK_SET);
            for(k=0;k<j;k++){
                
                c = fgetc(arquivoEntrada);
                fscanf(arquivoEntrada,"%d",&tamReg);
                if(c==0){
                fscanf(arquivoEntrada,"%d",&idPessoa);
                fscanf(arquivoEntrada,"%d",&idade);
                    if(idade == param){
             
                    
               fread(&p.removido,sizeof(char), 1, fdin);
               fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
               if(p.removido == '0'){ //registro nao esta marcado como removido
                if(b==buscas[i]){
                 fread(&p.idPessoa, sizeof(int), 1, fdin);
                 fread(&p.idadePessoa, sizeof(int), 1, fdin);
                 fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                 fread(&p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                 fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
                fread(&p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
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
               }else{b++;
                fseek(fdin, p.tamanhoRegistro,SEEK_CUR);}
            }
            else{
                 fseek(fdin, p.tamanhoRegistro,SEEK_CUR);
            }
            }
                    else{fseek(arquivoEntrada,tamReg-13,SEEK_CUR);}
                }
                else{fseek(arquivoEntrada,tamReg-5,SEEK_CUR);}

            }

        }




        
        else if(strcmp(tipoBusca,"nomePessoa")==0){
            param = strtok(NULL,'\n');

            fscanf(arquivoEntrada,"%c",c);
            fscanf(arquivoEntrada,"%d",j);
            fseek(arquivoEntrada,16, SEEK_SET);
            for(k=0;k<j;k++){
                
                c = fgetc(arquivoEntrada);
                fscanf(arquivoEntrada,"%d",&tamReg);
                if(c==0){
                fscanf(arquivoEntrada,"%d",&idPessoa);
                fscanf(arquivoEntrada,"%d",&idade);
                fscanf(arquivoEntrada,"%d",&TAM_nPessoa);
                fgets(nome,TAM_nPessoa,arquivoEntrada);
                    if(TAM_nPessoa>0){
                    if(strcmp(nome, parametro)){
             
                    
               fread(&p.removido,sizeof(char), 1, fdin);
               fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
               if(p.removido == '0'){ //registro nao esta marcado como removido
                if(b==buscas[i]){
                 fread(&p.idPessoa, sizeof(int), 1, fdin);
                 fread(&p.idadePessoa, sizeof(int), 1, fdin);
                 fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                 fread(&p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                 fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
                fread(&p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
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
               }else{b++;
                fseek(fdin, p.tamanhoRegistro,SEEK_CUR);}
            }
            else{
                 fseek(fdin, p.tamanhoRegistro,SEEK_CUR);
            }
            }}

                    else{fseek(arquivoEntrada,tamReg-(17+TAM_nPessoa),SEEK_CUR);}
                }
                else{fseek(arquivoEntrada,tamReg-5,SEEK_CUR);}

            }
        }


        else if(strcmp(tipoBusca,"nomeUsuario")==0){
            param = strtok(NULL,'=');

            fscanf(arquivoEntrada,"%c",h.status);
            fscanf(arquivoEntrada,"%d",j);
            fseek(arquivoEntrada,16, SEEK_SET);
            for(k=0;k<j;k++){
                
                c = fgetc(arquivoEntrada);
                fscanf(arquivoEntrada,"%d",&tamReg);
                if(c==0){

                fscanf(arquivoEntrada,"%d",&idPessoa);
                fscanf(arquivoEntrada,"%d",&idade);
                fscanf(arquivoEntrada,"%d",&TAM_nPessoa);
                fgets(nome,TAM_nPessoa,arquivoEntrada);
                fscanf(arquivoEntrada,"%d",&TAM_nUsuario);
                fgets(usuario,TAM_nUsuario,arquivoEntrada);
                    if(TAM_nUsuario>0){
                    if(strcmp(usuario, parametro)){
             
                    
               fread(&p.removido,sizeof(char), 1, fdin);
               fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
               if(p.removido == '0'){ //registro nao esta marcado como removido
                if(b==buscas[i]){
                 fread(&p.idPessoa, sizeof(int), 1, fdin);
                 fread(&p.idadePessoa, sizeof(int), 1, fdin);
                 fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                 fread(&p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                 fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
                fread(&p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
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
               }else{b++;
                fseek(fdin, p.tamanhoRegistro,SEEK_CUR);}
            }
            else{
                 fseek(fdin, p.tamanhoRegistro,SEEK_CUR);
            }
            }}

                    else{fseek(arquivoEntrada,tamReg-(17+TAM_nPessoa+TAM_nUsuario),SEEK_CUR);}
                }
                else{fseek(arquivoEntrada,tamReg-5,SEEK_CUR);}

            }
        }
     

    }
    return 0;

}
