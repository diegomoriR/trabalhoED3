#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

pessoa* busca(FILE *fd, FILE *fdh, char *tipoBusca) {
    headerIndice hi;
    header h;
    pessoa *p;
    indice i;
    int encontrado = 0;
    int param;
    char parametro[30];



    // idPessoa (utiliza índice)
    if(strcmp(tipoBusca, "idPessoa") == 0){
        scanf("%d", &param);
        if(param == 0){
            param = -1;
        }
        fread(&hi.status, sizeof(char), 1, fdh);
        fseek(fdh, 12, SEEK_SET);
        fread(&i.idPessoa, sizeof(int), 1, fdh);
        fseek(fdh,sizeof(long),SEEK_CUR);
        fread(&h.status, sizeof(char), 1, fd);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        if(hi.status == '0' || h.status == '0'){
            printf("status inconsistente\n");
            return NULL;
        }
        for(int k=0; k < (NUMERO_PESSOAS); k++){
            fread(&i.idPessoa, sizeof(int), 1, fdh);
            if(i.idPessoa == param){
                fread(&i.Offset, sizeof(long), 1, fdh);
                fseek(fd, i.Offset, SEEK_SET);
                fread(&p->removido,sizeof(char), 1, fd);
                fread(&p->tamanhoRegistro, sizeof(int), 1, fd);
                if(p->removido == '0'){
                    fread(&p->idPessoa, sizeof(int), 1, fd);
                    fread(&p->idadePessoa, sizeof(int), 1, fd);
                    fread(&p->tamanhoNomePessoa, sizeof(int), 1, fd);
                    p->nomePessoa = (char*) malloc(p->tamanhoNomePessoa + 1);
                    fread(p->nomePessoa, sizeof(char), p->tamanhoNomePessoa, fd);
                    p->nomePessoa[p->tamanhoNomePessoa] = 0;
                    fread(&p->tamanhoNomeUsuario, sizeof(int), 1, fd);
                    p->nomeUsuario = (char*) malloc(p->tamanhoNomeUsuario + 1);
                    fread(p->nomeUsuario, sizeof(char), p->tamanhoNomeUsuario, fd);
                    p->nomeUsuario[p->tamanhoNomeUsuario] = 0;
                    encontrado = 1;
                    break;
                    }
                }else {
                    fseek(fdh, sizeof(long), SEEK_CUR);
                    }
        }
        if(encontrado){
            return p;
        }else{printf("Registro inexistente\n");
        return NULL;
        }
    }

    // idadePessoa
    else if(strcmp(tipoBusca, "idadePessoa") == 0){
        scanf("%d", &param);
        if(param == 0){
            param = -1;
        }
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
        fread(&h.Offset,sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            fread(&p->removido,sizeof(char), 1, fd);
            fread(&p->tamanhoRegistro, sizeof(int), 1, fd);
            if(p->removido == '0'){
                fread(&p->idPessoa, sizeof(int), 1, fd);
                fread(&p->idadePessoa, sizeof(int), 1, fd);
                fread(&p->tamanhoNomePessoa, sizeof(int), 1, fd);
                p->nomePessoa = malloc(p->tamanhoNomePessoa + 1);
                fread(p->nomePessoa, sizeof(char), p->tamanhoNomePessoa, fd);
                p->nomePessoa[p->tamanhoNomePessoa] = 0;
                fread(&p->tamanhoNomeUsuario, sizeof(int), 1, fd);
                p->nomeUsuario = malloc(p->tamanhoNomeUsuario + 1);
                fread(p->nomeUsuario, sizeof(char), p->tamanhoNomeUsuario, fd);
                p->nomeUsuario[p->tamanhoNomeUsuario] = 0;
                if(p->idadePessoa == param){
                    encontrado = 1;
                    break;
                }
                free(p->nomePessoa);
                free(p->nomeUsuario);
            } else {
                fseek(fd, p->tamanhoRegistro, SEEK_CUR);
            }
        }
        if(encontrado){
            return p;
        }else{printf("Registro inexistente\n");
        return NULL;
        }
    }

    // nomePessoa
    else if(strcmp(tipoBusca,"nomePessoa")==0){
        scan_quote_string(parametro);
        if(strcmp(parametro, "NULO") == 0){
            strcpy(parametro, "");
        }
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            fread(&p->removido,sizeof(char), 1, fd);
            fread(&p->tamanhoRegistro, sizeof(int), 1, fd);
            if(p->removido == '0'){
                fread(&p->idPessoa, sizeof(int), 1, fd);
                fread(&p->idadePessoa, sizeof(int), 1, fd);
                fread(&p->tamanhoNomePessoa, sizeof(int), 1, fd);
                p->nomePessoa = malloc(p->tamanhoNomePessoa + 1);
                fread(p->nomePessoa, sizeof(char), p->tamanhoNomePessoa, fd);
                p->nomePessoa[p->tamanhoNomePessoa] = 0;
                fread(&p->tamanhoNomeUsuario, sizeof(int), 1, fd);
                p->nomeUsuario = malloc(p->tamanhoNomeUsuario + 1);
                fread(p->nomeUsuario, sizeof(char), p->tamanhoNomeUsuario, fd);
                p->nomeUsuario[p->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro, p->nomePessoa) == 0){
                    encontrado = 1;
                     break;
                }
                free(p->nomePessoa);
                free(p->nomeUsuario);
            } else {
                fseek(fd, p->tamanhoRegistro, SEEK_CUR);
            }
        }
        if(encontrado){
            return p;
        }else{printf("Registro inexistente\n");
        return NULL;
        }
    }

    // nomeUsuario
    else if(strcmp(tipoBusca,"nomeUsuario")==0){
        scan_quote_string(parametro);
        if(strcmp(parametro, "NULO") == 0){
            strcpy(parametro, "");
        }
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k = 0; k < NUMERO_PESSOAS; k++){
            fread(&p->removido,sizeof(char), 1, fd);
            fread(&p->tamanhoRegistro, sizeof(int), 1, fd);
            if(p->removido == '0'){ //nao esta removido registro
                fread(&p->idPessoa, sizeof(int), 1, fd);
                fread(&p->idadePessoa, sizeof(int), 1, fd);
                fread(&p->tamanhoNomePessoa, sizeof(int), 1, fd);
                p->nomePessoa = malloc(p->tamanhoNomePessoa + 1);
                fread(p->nomePessoa, sizeof(char), p->tamanhoNomePessoa, fd);
                p->nomePessoa[p->tamanhoNomePessoa] = 0;
                fread(&p->tamanhoNomeUsuario, sizeof(int), 1, fd);
                p->nomeUsuario = malloc(p->tamanhoNomeUsuario + 1);
                fread(p->nomeUsuario, sizeof(char), p->tamanhoNomeUsuario, fd);
                p->nomeUsuario[p->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro,p->nomeUsuario)==0){
                    encontrado = 1;
                    break;
                }
                free(p->nomePessoa);
                free(p->nomeUsuario);
            } else { //registro removido entao vai para o proximo
                fseek(fd, p->tamanhoRegistro, SEEK_CUR);
                printf("registro removido\n");
            }
        }
        if(encontrado){ // registro foi encontrado
            return p;
        }else{printf("Registro inexistente\n"); //registro nao foi encontrado
        return NULL;
        }
    }

    printf("Tipo de busca inválido\n");
    return NULL;
}

segue* busca_binaria(segue *vetor, int tamanho, int idBusca){
    int esquerda = 0, direita = tamanho - 1;
    int resultado = -1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (vetor[meio].idPessoaQueSegue < idBusca) {
            esquerda = meio + 1;
        } else if (vetor[meio].idPessoaQueSegue > idBusca) {
            direita = meio - 1;
        } else {
            resultado = meio;
            // Continua procurando para a ESQUERDA!
            direita = meio - 1;
        }
    }
    if (resultado == -1)
        return NULL;
    return &vetor[resultado];
}

long busca_binaria_indice(indice* vetor, int n, int valor){
    int ini = 0, fim = n-1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (vetor[meio].idPessoa == valor){
            return vetor[meio].Offset;
        }
        else if (vetor[meio].idPessoa < valor)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

int busca_binaria_indice_atualiza(indice* vetor, int n, int valor){

    int ini = 0, fim = n-1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (vetor[meio].idPessoa == valor){

            return meio;
        }
        else if (vetor[meio].idPessoa < valor)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void busca_substitui(FILE *fd, FILE *fdh){

  if(fd == NULL || fdh == NULL) {
        printf("Falha no processamento do arquivo\n");
        return;
    }

   int buscas;
    int b, param, k;
    char tipoBusca[15];
    char parametro[30];

    // criando headers e pessoas pra facilitar a manipulação de dados
    headerIndice hi;
    header h;
    pessoa p;
    indice* i;


        b=0;//controle de registros encontrados com o parametro buscado
        scanf("%d",&buscas);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        fseek(fd, 0, SEEK_SET);//coloca no começo do arquivo pessoa

        if(strcmp(tipoBusca, "idPessoa") == 0){
        indice ibusca;
        scanf("%d", &param);
        fread(&hi.status, sizeof(char), 1, fdh);
        fseek(fdh, 12, SEEK_SET);
        fread(&h.status, sizeof(char), 1, fd);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        if(hi.status == '0' || h.status == '0'){
            fclose(fd);
            fclose(fdh);
            printf("status do arquivo/pessoa inconsistente\n");
            return;
        }

        //copiando o Arquivo indice para um vetor
        fseek(fdh, 0, SEEK_END);
        long tamanhoArquivo = ftell(fdh);//pega o tamanho do arquivo
        const long inicioRegistros = 12;
        int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));//calcula o número de registros
        indice VetInd[n];
        headerIndice hi;
        fseek(fdh, 0, SEEK_SET);
        fread(&hi.status,sizeof(char),1,fdh);
        fseek(fdh, TAMANHO_HEADER_INDICE,SEEK_SET);
        for(int i=0;i<n;i++){//copia os indices para o vetor
            fread(&VetInd[i].idPessoa,sizeof(int),1,fdh);
            fread(&VetInd[i].Offset,sizeof(long),1,fdh);
        }


        ibusca.Offset=busca_binaria_indice(VetInd,h.quantidadePessoas,param);
        fseek(fd, ibusca.Offset, SEEK_SET);
        fread(&p.removido,sizeof(char), 1, fd);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
        long offset= ftell(fd);
        if(p.removido == '0'){
            fread(&p.idPessoa, sizeof(int), 1, fd);
            if(p.idPessoa == param){
                fread(&p.idadePessoa, sizeof(int), 1, fd);
                fread(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
                p.nomePessoa = (char*) malloc(p.tamanhoNomePessoa + 1);
                fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
                p.nomePessoa[p.tamanhoNomePessoa] = 0;
                fread(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
                p.nomeUsuario = (char*) malloc(p.tamanhoNomeUsuario + 1);
                fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
                p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                b = 1;
                substitui_registro(fd,fdh,p,offset);
            }
            else{
                    b=0;
                }
        }
        fclose(fd); fclose(fdh);
        if(b==0){
        printf("Registro inexistente.\n\n");
        scanf("%*c");
        scanf("%s", parametro);//lê qual campo quer substituir para funcionamento das próximas chamadas
        return;}

        return;
    }// caso busca por id


        else if(strcmp(tipoBusca,"idadePessoa")==0){
            scanf("%d",&param);// pega o parametro a ser buscado
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(k=0;k<NUMERO_PESSOAS;k++){

        fread(&p.removido,sizeof(char), 1, fd);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
        long offset= ftell(fd);

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

                if(p.idadePessoa == param){//verifica se é o parâmetro buscado

                b++;//aumenta o número de registros encontrados
                //imprime os dados
                substitui_registro(fd,fdh,p, offset);
                }
            free(p.nomePessoa);
            free(p.nomeUsuario);

            }else{fseek(fd,p.tamanhoRegistro,SEEK_CUR);}//registro removido, vai para o próximo
            }
            if(b==0){
                printf("Registro inexistente.\n\n");
                 scanf("%*c");
                 scanf("%s", parametro);//lê qual campo quer substituir para funcionamento das próximas chamadas
            }//nenhum registro b com esse parâmetro
        }//caso busca idade


        else if(strcmp(tipoBusca,"nomePessoa")==0){
            scan_quote_string(parametro);
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(k=0;k<h.quantidadePessoas;k++){

        fread(&p.removido,sizeof(char), 1, fd);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
        long offset= ftell(fd);

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

                if(strcmp(parametro,p.nomePessoa)==0){//verifica se é o parâmetro buscado

                b++;//aumenta o número de registros encontrados
                //imprime os dados
                substitui_registro(fd,fdh,p,offset);
                free(p.nomePessoa);
                free(p.nomeUsuario);
                return;
                }
            free(p.nomePessoa);
            free(p.nomeUsuario);

            }else{fseek(fd,p.tamanhoRegistro,SEEK_CUR);//registro removido, vai para o próximo
}
            }
            if(b==0){
                printf("Registro inexistente.\n\n");
                 scanf("%*c");
                 scanf("%s", parametro);//lê qual campo quer substituir para funcionamento das próximas chamadas
            }//nenhum registro b com esse parâmetro

        }//caso busca nome pessoa


        else if(strcmp(tipoBusca,"nomeUsuario")==0){
            scan_quote_string(parametro);
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(k=0;k<h.quantidadePessoas;k++){

        fread(&p.removido,sizeof(char), 1, fd);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
        long offset= ftell(fd);

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

                 if(strcmp(parametro,p.nomeUsuario)==0){//verifica se é o parâmetro buscado

                b++;//aumenta o número de registros encontrados
                //imprime os dados
                substitui_registro(fd,fdh,p, offset);
                free(p.nomePessoa);
                free(p.nomeUsuario);
                return;
                }
            free(p.nomePessoa);
            free(p.nomeUsuario);

            }else{fseek(fd,p.tamanhoRegistro,SEEK_CUR);}//registro removido, vai para o próximo

            }
            if(b==0){
                printf("Registro inexistente.\n\n");
                 scanf("%*c");
                 scanf("%s", parametro);//lê qual campo quer substituir para funcionamento das próximas chamadas
            }//nenhum registro b com esse parâmetro

        }//caso busca nome Usuário





}

void busca_print(FILE *fd, FILE *fdh){

  if(fd == NULL || fdh == NULL) {
        printf("Falha no processamento do arquivo\n");
        return;
    }

   int buscas;
    int b, param, k;
    char tipoBusca[15];
    char parametro[30];

    // criando headers e pessoas pra facilitar a manipulação de dados
    headerIndice hi;
    header h;
    pessoa p;
    indice* i;


        b=0;//controle de registros encontrados com o parametro buscado
        scanf("%d",&buscas);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        fseek(fd, 0, SEEK_SET);//coloca no começo do arquivo pessoa

        if(strcmp(tipoBusca, "idPessoa") == 0){
        indice ibusca;
        scanf("%d", &param);
        fread(&hi.status, sizeof(char), 1, fdh);
        fseek(fdh, 12, SEEK_SET);
        fread(&h.status, sizeof(char), 1, fd);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        if(hi.status == '0' || h.status == '0'){
            fclose(fd);
            fclose(fdh);
            printf("status do arquivo/pessoa inconsistente\n");
            return;
        }

        //copiando o Arquivo indice para um vetor
        fseek(fdh, 0, SEEK_END);
        long tamanhoArquivo = ftell(fdh);//pega o tamanho do arquivo
        const long inicioRegistros = 12;
        int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));//calcula o número de registros
        indice VetInd[n];
        headerIndice hi;
        fseek(fdh, 0, SEEK_SET);
        fread(&hi.status,sizeof(char),1,fdh);
        fseek(fdh, TAMANHO_HEADER_INDICE,SEEK_SET);
        for(int i=0;i<n;i++){//copia os indices para o vetor
            fread(&VetInd[i].idPessoa,sizeof(int),1,fdh);
            fread(&VetInd[i].Offset,sizeof(long),1,fdh);
        }


        ibusca.Offset=busca_binaria_indice(VetInd,h.quantidadePessoas,param);
        fseek(fd, ibusca.Offset, SEEK_SET);
        fread(&p.removido,sizeof(char), 1, fd);
        fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
        if(p.removido == '0'){
            fread(&p.idPessoa, sizeof(int), 1, fd);
            if(p.idPessoa == param){
                fread(&p.idadePessoa, sizeof(int), 1, fd);
                fread(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
                p.nomePessoa = (char*) malloc(p.tamanhoNomePessoa + 1);
                fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
                p.nomePessoa[p.tamanhoNomePessoa] = 0;
                fread(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
                p.nomeUsuario = (char*) malloc(p.tamanhoNomeUsuario + 1);
                fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
                p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                b = 1;
                print_registro(p);
            }
            else{
                    b=0;
                }
        }
        fclose(fd); fclose(fdh);
        if(b==0){printf("Registro inexistente.\n\n");}

        return;
    }// caso busca por id


        else if(strcmp(tipoBusca,"idadePessoa")==0){
            scanf("%d",&param);// pega o parametro a ser buscado
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(k=0;k<h.quantidadePessoas;k++){

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

                 if(p.idadePessoa == param){//verifica se é o parâmetro buscado

                b++;//aumenta o número de registros encontrados
                //imprime os dados
                print_registro(p);
                free(p.nomePessoa);
                free(p.nomeUsuario);

            }
            }else{fseek(fd,p.tamanhoRegistro,SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){printf("Registro inexistente.\n\n");}//nenhum registro b com esse parâmetro

        }//caso busca idade


        else if(strcmp(tipoBusca,"nomePessoa")==0){
            scan_quote_string(parametro);
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(k=0;k<h.quantidadePessoas;k++){

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

                 if(strcmp(parametro,p.nomePessoa)==0){//verifica se é o parâmetro buscado

                b++;//aumenta o número de registros encontrados
                //imprime os dados
                print_registro(p);
                free(p.nomePessoa);
                free(p.nomeUsuario);

            }
            }else{fseek(fd,p.tamanhoRegistro,SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){printf("Registro inexistente.\n\n");}//nenhum registro b com esse parâmetro

        }//caso busca nome pessoa


        else if(strcmp(tipoBusca,"nomeUsuario")==0){
            scan_quote_string(parametro);
            fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fd);
            fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
            fread(&h.Offset,sizeof(long), 1, fd);
            for(k=0;k<h.quantidadePessoas;k++){

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

                 if(strcmp(parametro,p.nomeUsuario)==0){//verifica se é o parâmetro buscado

                b++;//aumenta o número de registros encontrados
                //imprime os dados
                print_registro(p);
                free(p.nomePessoa);
                free(p.nomeUsuario);

            }
            }else{fseek(fd,p.tamanhoRegistro,SEEK_CUR);//registro removido, vai para o próximo
                free(p.nomePessoa);
                free(p.nomeUsuario);}
            }
            if(b==0){printf("Registro inexistente.\n\n");}//nenhum registro b com esse parâmetro

        }//caso busca nome Usuário




}
