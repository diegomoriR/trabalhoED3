#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

pessoa busca_int(FILE *fd, FILE *fdh, char *tipoBusca){

    if(fd == NULL){
        printf("Falha no processamento do arquivo\n");
    }
    if(fdh == NULL){
        printf("Falha no processamento do arquivo\n");
    }

    headerIndice hi;
    header h;
    pessoa p;
    indice i;
    int b = 0;
    int param;
    char parametro[30];

    INICIO_ARQUIVO(fd);

        if(strcmp(tipoBusca, "idPessoa") == 0){
            scanf("%d", &param);// pega o parametro a ser buscado
            fread(&hi.status, sizeof(char), 1, fdh);// vê o status do arquivo de indice
            fseek(fdh, 12, SEEK_SET);// vai para os dados do arquivo indice
            fread(&h.status, sizeof(char), 1, fd);//vê o status do arquivo pessoa
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);//vê o número de pessoas
            fread(&h.quantidadeRemovidos, sizeof(int), 1, fd); //ve o numero de removidos
            if(hi.status == '0'){
                fclose(fd);
                fclose(fdh);
                printf("status do indice inconsistente\n");
                exit(-1);
            }
            if(h.status == '0'){
                fclose(fd);
                fclose(fdh);
                printf("status do arquivo pessoa inconsistente\n");
                exit(-1);
            }


             for(int k=0; k < (NUMERO_PESSOAS); k++){//busca até o número total de pessoas

                fread(&i.idPessoa, sizeof(int), 1, fdh);//lê o id da pessoa no arquivo indice
                //idPessoa
                if(i.idPessoa == param){//verifica se é igual ao parâmetro buscado

                    fread(&i.Offset, sizeof(long), 1, fdh);//lê o byte offset
                    fseek(fd, i.Offset, SEEK_SET);  //vai para o offset no arquivo pessoa
                    fread(&p.removido,sizeof(char), 1, fd);//vê o caracter 0 ou 1 de remoção
                    fread(&p.tamanhoRegistro, sizeof(int), 1, fd);//pega o tamanho do registro
                    if(p.removido == '0'){ //registro nao esta marcado como removido
                        fread(&p.idPessoa, sizeof(int), 1, fd);
                        fread(&p.idadePessoa, sizeof(int), 1, fd);
                        fread(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
                        p.nomePessoa = (char *) malloc(p.tamanhoNomePessoa + 1);
                        fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
                        p.nomePessoa[p.tamanhoNomePessoa] = 0;
                        fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fd);
                        p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario + 1);
                        fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
                        p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                        b++;
                        return p;
                    }else{
                        fseek(fdh, sizeof(long), SEEK_CUR);
                    }//vai para o próximo id no arquivo indice
                }
                if(b == 0){
                    // printf("Registro inexistente.\n\n");
                }//nenhum registro encontrado com esse parâmetro
            }
            }

            //idadePessoa
        else if(strcmp(tipoBusca, "idadePessoa") == 0){
            scanf("%d", &param);// pega o parametro a ser buscado
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(int k = 0; k < (NUMERO_PESSOAS); k++){

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
                    p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario + 1);
                    fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
                    p.nomeUsuario[p.tamanhoNomeUsuario] = 0;

                if(p.idadePessoa == param){//verifica se é o parâmetro buscado
                        b++;
                        return p;
                }
                }else{
                    fseek(fd, p.tamanhoRegistro, SEEK_CUR);//registro removido, vai para o próximo
                    free(p.nomePessoa);
                    free(p.nomeUsuario);}
                }
            if(b == 0){
                // printf("Registro inexistente.\n\n");
            }//nenhum registro encontrado com esse parâmetro
        }

        //nomePessoa
        if(strcmp(tipoBusca,"nomePessoa")==0){
            scan_quote_string(parametro);
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
            fread(&h.Offset, sizeof(long), 1, fd);
            for(int k = 0; k < NUMERO_PESSOAS; k++){

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
                p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario + 1);
                fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
                p.nomeUsuario[p.tamanhoNomeUsuario] = 0;

                if(strcmp(parametro, p.nomePessoa) == 0){//verifica se é o parâmetro buscado
                    b++;
                    return p;
            }
            }else{
                fseek(fd, p.tamanhoRegistro, SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){
                // printf("Registro inexistente.\n\n");
            }//nenhum registro encontrado com esse parâmetro
        }


        //nomeUsuario
        else if(strcmp(tipoBusca, "nomeUsuario") == 0){
            scan_quote_string(parametro);
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(int k = 0; k < (NUMERO_PESSOAS); k++){

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
                    p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario + 1);
                    fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
                    p.nomeUsuario[p.tamanhoNomeUsuario] = 0;

                    if(strcmp(parametro,p.nomeUsuario) == 0){//verifica se é o parâmetro buscado
                        b++;
                        return p;
                    }
                }else{fseek(fd, p.tamanhoRegistro, SEEK_CUR);//registro removido, vai para o próximo
                    free(p.nomePessoa);
                    free(p.nomeUsuario);}
            }
            if(b==0){
                // printf("Registro inexistente.\n\n");
            }//nenhum registro encontrado com esse parâmetro

        }


}
