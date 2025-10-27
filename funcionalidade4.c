//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"



//funcionalidade 4 (SELECT_WHERE)
void Select_Where(char* arquivoEntrada, char* arquivoIndice, int n){


    FILE *fdin = fopen(arquivoEntrada, "rb"); // abrindo o arquivo para ler os dados
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    FILE *fdh = fopen(arquivoIndice, "rb"); // abrindo o arquivo para a escrita binaria no indice
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }
    int buscas[n];
    int i,b, param, k;
    char tipoBusca[15];
    char parametro[30];

    // criando headers e pessoas pra facilitar a manipulação de dados
    headerIndice hi;
    header h;
    pessoa p;
    indice j;
    
    for( i=0; i<n;i++){//controle para o número de buscas


        b=0;//controle de registros encontrados com o parametro buscado
        scanf("%d",&buscas[i]);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        fseek(fdin, 0, SEEK_SET);//coloca no começo do arquivo pessoa
        if(strcmp(tipoBusca,"idPessoa")==0){
            
            scanf("%d",&param);// pega o parametro a ser buscado
            fread(&hi.status,sizeof(char),1,fdh);// vê o status do arquivo de indice
            fseek(fdh,12, SEEK_SET);// vai para os dados do arquivo indice
            fread(&h.status,sizeof(char),1,fdin);//vê o status do arquivo pessoa
            fread(&h.quantidadePessoas,sizeof(int),1,fdin);//vê o número de pessoas

             for(k=0;k<h.quantidadePessoas;k++){//busca até o número total de pessoas
                
                
             fread(&j.idPessoa,sizeof(int),1,fdh);//lê o id da pessoa no arquivo indice
             if(j.idPessoa == param){//verifica se é igual ao parâmetro buscado
             
               fread(&j.Offset,sizeof(long),1,fdh);//lê o byte offset
               fseek(fdin,j.Offset,SEEK_SET);  //vai para o offset no arquivo pessoa   
               fread(&p.removido,sizeof(char), 1, fdin);//vê o caracter 0 ou 1 de remoção
               fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);//pega o tamanho do registro
               if(p.removido == '0'){ //registro nao esta marcado como removido
                b++;//aumenta o valor de registros encontrados
                //pega os dados da pessoa para imprimir
                 fread(&p.idPessoa, sizeof(int), 1, fdin);
                 fread(&p.idadePessoa, sizeof(int), 1, fdin);
                 fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                 p.nomePessoa = (char *) malloc(p.tamanhoNomePessoa + 1);
                 fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                 p.nomePessoa[p.tamanhoNomePessoa] = 0;
                 fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
                 p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario + 1);
                 fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
                 p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                //imprime os dados
                if(p.idPessoa != -1){
                printf("Dados da pessoa de codigo %d\n", p.idPessoa);
                }else{
                printf("Dados da pessoa de codigo -\n");
                }
                if(p.tamanhoNomePessoa != 0){
                printf("Nome: %s\n", p.nomePessoa);
                }else{
                printf("Nome: - \n");
                }
                if(p.idadePessoa != -1){
                    printf("Idade: %d\n", p.idadePessoa);
                }else{
                     printf("Idade: -\n");
                }
                if(p.nomeUsuario != NULL){
                    printf("Usuario: %s\n\n", p.nomeUsuario);
                }else{
                    printf("Usuario: - \n\n");
                }
                free(p.nomePessoa);
                free(p.nomeUsuario);               
               }
            }else{fseek(fdh,sizeof(long),SEEK_CUR);}//vai para o próximo id no arquivo indice
            }
            if(b==0){printf("Registro inexistente.\n\n");}//nenhum registro encontrado com esse parâmetro
        }// caso busca por id


        else if(strcmp(tipoBusca,"idadePessoa")==0){
            scanf("%d",&param);// pega o parametro a ser buscado
            fseek(fdin, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fdin);
            fread(&h.Offset,sizeof(long), 1, fdin);
            for(k=0;k<h.quantidadePessoas;k++){

        fread(&p.removido,sizeof(char), 1, fdin);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
        
        if(p.removido == '0'){ //registro nao esta marcado como removido
            
            fread(&p.idPessoa, sizeof(int), 1, fdin);
            fread(&p.idadePessoa, sizeof(int), 1, fdin);
            fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
            p.nomePessoa = (char *) malloc(p.tamanhoNomePessoa + 1);
            fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
            p.nomePessoa[p.tamanhoNomePessoa] = 0;
            fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
            p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario+1);
            fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
            p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                 
                 if(p.idadePessoa == param){//verifica se é o parâmetro buscado
                    
                b++;//aumenta o número de registros encontrados
                //imprime os dados
                if(p.idPessoa != -1){
                printf("Dados da pessoa de codigo %d\n", p.idPessoa);
                }else{
                printf("Dados da pessoa de codigo -\n");
                }
                if(p.tamanhoNomePessoa != 0){
                    printf("Nome: %s\n", p.nomePessoa);
                }else{
                    printf("Nome: - \n");
                }
                if(p.idadePessoa != -1){
                    printf("Idade: %d\n", p.idadePessoa);
                }else{
                     printf("Idade: -\n");
                }
                if(p.tamanhoNomeUsuario != 0){
                    printf("Usuario: %s\n\n", p.nomeUsuario);
                }else{
                    printf("Usuario: - \n\n");
                }
                free(p.nomePessoa);
                free(p.nomeUsuario);

            }
            }else{fseek(fdin,p.tamanhoRegistro,SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){printf("Registro inexistente.\n\n");}//nenhum registro encontrado com esse parâmetro

        }//caso busca idade




        
        else if(strcmp(tipoBusca,"nomePessoa")==0){
            scan_quote_string(parametro);
            fseek(fdin, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fdin);
            fread(&h.Offset,sizeof(long), 1, fdin);
            for(k=0;k<h.quantidadePessoas;k++){

        fread(&p.removido,sizeof(char), 1, fdin);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
        
        if(p.removido == '0'){ //registro nao esta marcado como removido
            
            fread(&p.idPessoa, sizeof(int), 1, fdin);
            fread(&p.idadePessoa, sizeof(int), 1, fdin);
            fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
            p.nomePessoa = (char *) malloc(p.tamanhoNomePessoa + 1);
            fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
            p.nomePessoa[p.tamanhoNomePessoa] = 0;
            fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
            p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario+1);
            fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
            p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                 
                 if(strcmp(parametro,p.nomePessoa)==0){//verifica se é o parâmetro buscado
                    
                b++;//aumenta o número de registros encontrados
                //imprime os dados
                if(p.idPessoa != -1){
                printf("Dados da pessoa de codigo %d\n", p.idPessoa);
                }else{
                printf("Dados da pessoa de codigo -\n");
                }
                if(p.tamanhoNomePessoa != 0){
                    printf("Nome: %s\n", p.nomePessoa);
                }else{
                    printf("Nome: - \n");
                }
                if(p.idadePessoa != -1){
                    printf("Idade: %d\n", p.idadePessoa);
                }else{
                     printf("Idade: -\n");
                }
                if(p.tamanhoNomeUsuario != 0){
                    printf("Usuario: %s\n\n", p.nomeUsuario);
                }else{
                    printf("Usuario: - \n\n");
                }
                free(p.nomePessoa);
                free(p.nomeUsuario);

            }
            }else{fseek(fdin,p.tamanhoRegistro,SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){printf("Registro inexistente.\n\n");}//nenhum registro encontrado com esse parâmetro

        }//caso busca nome pessoa


        else if(strcmp(tipoBusca,"nomeUsuario")==0){
            scan_quote_string(parametro);
            fseek(fdin, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fdin);
            fread(&h.Offset,sizeof(long), 1, fdin);
            for(k=0;k<h.quantidadePessoas;k++){

        fread(&p.removido,sizeof(char), 1, fdin);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
        
        if(p.removido == '0'){ //registro nao esta marcado como removido
            
            fread(&p.idPessoa, sizeof(int), 1, fdin);
            fread(&p.idadePessoa, sizeof(int), 1, fdin);
            fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
            p.nomePessoa = (char *) malloc(p.tamanhoNomePessoa + 1);
            fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
            p.nomePessoa[p.tamanhoNomePessoa] = 0;
            fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fdin);
            p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario+1);
            fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
            p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                 
                 if(strcmp(parametro,p.nomeUsuario)==0){//verifica se é o parâmetro buscado
                    
                b++;//aumenta o número de registros encontrados
                //imprime os dados
                if(p.idPessoa != -1){
                printf("Dados da pessoa de codigo %d\n", p.idPessoa);
                }else{
                printf("Dados da pessoa de codigo -\n");
                }
                if(p.tamanhoNomePessoa != 0){
                    printf("Nome: %s\n", p.nomePessoa);
                }else{
                    printf("Nome: -\n");
                }
                if(p.idadePessoa != -1){
                    printf("Idade: %d\n", p.idadePessoa);
                }else{
                     printf("Idade: - \n");
                }
                if(p.tamanhoNomeUsuario != 0){
                    printf("Usuario: %s\n\n", p.nomeUsuario);
                }else{
                    printf("Usuario: - \n\n");
                }
                free(p.nomePessoa);
                free(p.nomeUsuario);

            }
            }else{fseek(fdin,p.tamanhoRegistro,SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){printf("Registro inexistente.\n\n");}//nenhum registro encontrado com esse parâmetro

        }//caso busca nome Usuário
     

    }

    fclose(fdin);
    fclose(fdh);
    return;

}
