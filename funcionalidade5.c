#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 5 DELETE
void DELETE(char *arquivoEntrada, char *arquivoIndicePrimario, int n){

    //abrindo os arquivos para leitura e escrita binaria
    FILE *fd = fopen(arquivoEntrada, "rb+");
    if(fd == NULL){
        printf("Falha no processamento do arquivo\n");
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb+");
    if(fd == NULL){
        printf("Falha no processamento do arquivo\n");
    }

    int buscas[n];
    int param;
    char tipoBusca[15];
    char parametro[30];

    headerIndice hi;
    header h;
    pessoa p;
    indice i;

    //numero de buscas
    for(int j = 0; j < n; j++){
        int b = 0; //registros encontrados com o parametro buscado
        scanf("%d",&buscas[j]);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        INICIO_ARQUIVO(fd); //coloca no começo do arquivo pessoa

        //puxando o indice para a RAM
        indice *indices = (indice *)malloc(NUMERO_PESSOAS * sizeof(indice));
        //lendo o indice para a RAM
        if (fread(indices, sizeof(indice), NUMERO_PESSOAS, fdh) != NUMERO_PESSOAS) {
            printf("Aviso: Leitura incompleta do índice. Trabalhando com o que foi lido.\n");
        }


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
                return;
            }
            if(h.status == '0'){
                fclose(fd);
                fclose(fdh);
                printf("status do arquivo pessoa inconsistente\n");
                return;
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
                        for(int j = 0; j < NUMERO_PESSOAS - k; j++){
                            indices[j] = indices[j + 1];
                        } //shift no indice para remover

                        INICIO_ARQUIVO(fdh);
                        hi.status = '0'; //status inconsistente
                        fwrite(&hi.status, sizeof(char), 1, fdh);
                        fseek(fdh, 12, SEEK_SET);//inicio do arquivo de indice
                        if (fwrite(indices, sizeof(indice), NUMERO_PESSOAS, fdh) != NUMERO_PESSOAS) {
                            printf("Aviso: Escrita incompleta do índice. Trabalhando com o que foi lido.\n");
                        }//escrita no arquivo de indice
                        hi.status = '1'; //status consistente
                        INICIO_ARQUIVO(fdh);
                        fwrite(&hi.status, sizeof(char), 1, fdh);

                        b++;//aumenta o valor de registros encontrados

                        h.status = '0'; //status inconsistente
                        INICIO_ARQUIVO(fd);
                        fwrite(&h.status, sizeof(char), 1, fd);

                        p.removido = '1'; //registro marcado como removido
                        fseek(fd, i.Offset, SEEK_SET); //vai novamente para o offset para marcar como removido
                        fwrite(&p.removido, sizeof(char), 1, fd);

                        h.status = '1';
                        INICIO_ARQUIVO(fd);
                        fwrite(&h.status, sizeof(char), 1, fd);

                        h.quantidadeRemovidos++;

                }else{
                    fseek(fdh, sizeof(long), SEEK_CUR);
                }//vai para o próximo id no arquivo indice
                }
                if(b == 0){
                    printf("Registro inexistente.\n\n");
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
                    for(int j = 0; j < NUMERO_PESSOAS - k; j++){
                            indices[j] = indices[j + 1];
                        } //shift no indice para remover

                        INICIO_ARQUIVO(fdh);
                        hi.status = '0'; //status inconsistente
                        fwrite(&hi.status, sizeof(char), 1, fdh);
                        fseek(fdh, 12, SEEK_SET);//inicio do arquivo de indice
                        if (fwrite(indices, sizeof(indice), NUMERO_PESSOAS, fdh) != NUMERO_PESSOAS) {
                            printf("Aviso: Escrita incompleta do índice. Trabalhando com o que foi lido.\n");
                        }//escrita no arquivo de indice
                        hi.status = '1'; //status consistente
                        INICIO_ARQUIVO(fdh);
                        fwrite(&hi.status, sizeof(char), 1, fdh);

                    b++;//aumenta o número de registros encontrados

                    h.status = '0';
                    INICIO_ARQUIVO(fd);
                    fwrite(&h.status, sizeof(char), 1, fd);

                    p.removido = '1'; //registro marcado como removido
                    fseek(fd, -(p.tamanhoRegistro), SEEK_CUR); //vai novamente para o offset para marcar como removido
                    fwrite(&p.removido, sizeof(char), 1, fd);

                    h.status = '1';
                    INICIO_ARQUIVO(fd);
                    fwrite(&h.status, sizeof(char), 1, fd);

                    h.quantidadeRemovidos++;
                }
                }else{
                    fseek(fd, p.tamanhoRegistro, SEEK_CUR);//registro removido, vai para o próximo
                    free(p.nomePessoa);
                    free(p.nomeUsuario);}
                }
            if(b == 0){
                printf("Registro inexistente.\n\n");
            }//nenhum registro encontrado com esse parâmetro
        }

        //nomePessoa
        else if(strcmp(tipoBusca,"nomePessoa")==0){
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
                    for(int j = 0; j < NUMERO_PESSOAS - k; j++){
                            indices[j] = indices[j + 1];
                        } //shift no indice para remover

                        INICIO_ARQUIVO(fdh);
                        hi.status = '0'; //status inconsistente
                        fwrite(&hi.status, sizeof(char), 1, fdh);
                        fseek(fdh, 12, SEEK_SET);//inicio do arquivo de indice
                        if (fwrite(indices, sizeof(indice), NUMERO_PESSOAS, fdh) != NUMERO_PESSOAS) {
                            printf("Aviso: Escrita incompleta do índice. Trabalhando com o que foi lido.\n");
                        }//escrita no arquivo de indice
                        hi.status = '1'; //status consistente
                        INICIO_ARQUIVO(fdh);
                        fwrite(&hi.status, sizeof(char), 1, fdh);

                    b++;//aumenta o número de registros encontrados

                    h.status = '0';
                    INICIO_ARQUIVO(fd);
                    fwrite(&h.status, sizeof(char), 1, fd);

                    p.removido = '1'; //registro marcado como removido
                    fseek(fd, -(p.tamanhoRegistro), SEEK_CUR);
                    fwrite(&p.removido, sizeof(char), 1, fd);
                    free(p.nomePessoa);
                    free(p.nomeUsuario);

                    h.status = '1';
                    INICIO_ARQUIVO(fd);
                    fwrite(&h.status, sizeof(char), 1, fd);

                    h.quantidadeRemovidos++;

            }
            }else{
                fseek(fd, p.tamanhoRegistro, SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){
                printf("Registro inexistente.\n\n");
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
                        for(int j = 0; j < NUMERO_PESSOAS - k; j++){
                            indices[j] = indices[j + 1];
                        } //shift no indice para remover

                        INICIO_ARQUIVO(fdh);
                        hi.status = '0'; //status inconsistente
                        fwrite(&hi.status, sizeof(char), 1, fdh);
                        fseek(fdh, 12, SEEK_SET);//inicio do arquivo de indice
                        if (fwrite(indices, sizeof(indice), NUMERO_PESSOAS, fdh) != NUMERO_PESSOAS) {
                            printf("Aviso: Escrita incompleta do índice. Trabalhando com o que foi lido.\n");
                        }//escrita no arquivo de indice
                        hi.status = '1'; //status consistente
                        INICIO_ARQUIVO(fdh);
                        fwrite(&hi.status, sizeof(char), 1, fdh);

                        b++;//aumenta o número de registros encontrados

                        h.status = '0';
                        INICIO_ARQUIVO(fd);
                        fwrite(&h.status, sizeof(char), 1, fd);

                        p.removido = '1'; //registro marcado como removido
                        fseek(fd, -(p.tamanhoRegistro), SEEK_CUR); //vai parar o offset do registro para marcar como removido
                        fwrite(&p.removido, sizeof(char), 1, fd);
                        free(p.nomePessoa);
                        free(p.nomeUsuario);

                        h.status = '1';
                        INICIO_ARQUIVO(fd);
                        fwrite(&h.status, sizeof(char), 1, fd);

                        h.quantidadeRemovidos++;
                    }
                }else{fseek(fd, p.tamanhoRegistro, SEEK_CUR);//registro removido, vai para o próximo
                    free(p.nomePessoa);
                    free(p.nomeUsuario);}
            }
            if(b==0){
                printf("Registro inexistente.\n\n");
            }//nenhum registro encontrado com esse parâmetro

            }

        }
    fclose(fd);
    fclose(fdh);
    return;
}

