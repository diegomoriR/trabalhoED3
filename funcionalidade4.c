#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"
#include "header_indice.h"

//funcionalidade 3 (SELECT)
void Select_Where(FILE* arquivoEntrada, FILE* arquivoIndice, int n){

    int buscas[n];
    char c;
    int j, param, k, tamReg, idade,TAM_nPessoa,TAM_nUsuario, idPessoa, byteOffset;
    char* busca;
    char* tipoBusca, nome, nomeUsuario, usuario;
    char* parametro;

    for(int i=0; i<n;i++){

        j=0;
        scanf("%d",buscas[i]);
        scanf("%s",busca);
        INICIO_ARQUIVO(arquivoEntrada);
        tipoBusca = strtok(busca,'=');
        if(strcmp(tipoBusca,"idPessoa ")==0){
            param = strtok(NULL,'\n');
            fread(&c,sizeof(char),1,arquivoIndice);
            fseek(arquivoIndice,11, SEEK_SET);
            fread(&j,sizeof(int),1,arquivoEntrada);

            for(k=0;k<j;k++){
                

                
                fread(&idPessoa,sizeof(int),1,arquivoIndice);
                if(idPessoa == param){
                    
                    fread(&byteOffset,sizeof(int),1,arquivoIndice);
                    fseek(arquivoEntrada,byteOffset,SEEK_SET);
                    c = fgetc(arquivoEntrada);
                    fscanf(arquivoEntrada,"%d",&tamReg);
                    printf("Dados da pessoa do código %d\n",idPessoa);
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
                    else{fseek(arquivoIndice,8,SEEK_CUR);}


            }
        }
        else if(strcmp(tipoBusca,"idade")==0){
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
                    if(idade == param){
                    printf("Dados da pessoa do código %d\n",idPessoa);
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
                    printf("Dados da pessoa do código %d\n",idPessoa);
                    printf("Nome: ");
                    if(TAM_nPessoa>0){
                    fputs(nome, stdout);}
                    else{printf("--");}
                    printf("\nIdade: %d\n", idade);
                    fscanf(arquivoEntrada,"%d",&TAM_nUsuario);
                    fgets(usuario,TAM_nUsuario,arquivoEntrada);
                    printf("Usuário: ");
                    if(TAM_nUsuario>0){
                    fputs(usuario, stdout);}
                    else{printf("--");}
                    printf("\n\n");}}

                    else{fseek(arquivoEntrada,tamReg-(17+TAM_nPessoa),SEEK_CUR);}
                }
                else{fseek(arquivoEntrada,tamReg-5,SEEK_CUR);}

            }
        }
        else if(strcmp(tipoBusca,"nomeUsuario")==0){
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
                fscanf(arquivoEntrada,"%d",&TAM_nUsuario);
                fgets(usuario,TAM_nUsuario,arquivoEntrada);
                    if(TAM_nUsuario>0){
                    if(strcmp(usuario, parametro)){
                    printf("Dados da pessoa do código %d\n",idPessoa);
                    printf("Nome: ");
                    if(TAM_nPessoa>0){
                    fputs(nome, stdout);}
                    else{printf("--");}
                    printf("\nIdade: %d\n", idade);
                    if(TAM_nUsuario>0){
                    fputs(usuario, stdout);}
                    else{printf("--");}
                    printf("\n\n");}}

                    else{fseek(arquivoEntrada,tamReg-(17+TAM_nPessoa+TAM_nUsuario),SEEK_CUR);}
                }
                else{fseek(arquivoEntrada,tamReg-5,SEEK_CUR);}

            }
        }
     

    }
    return 0;

}