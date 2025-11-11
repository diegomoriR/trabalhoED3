#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

pessoa* busca(FILE *fd, FILE *fdh, char *tipoBusca) {
    if(fd == NULL || fdh == NULL) {
        printf("Falha no processamento do arquivo\n");
        return NULL;
    }

    headerIndice hi;
    header h;
    pessoa *p;
    indice* i;
    indice ibusca;
    int encontrado = 0;
    int param;
    char parametro[30];

    // idPessoa (utiliza índice)
    if(strcmp(tipoBusca, "idPessoa") == 0){
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
            return NULL;
        }
        i = vetor_ind(fdh);
        ibusca.Offset=busca_binaria_indice(i,h.quantidadePessoas,param);
        fseek(fd, ibusca.Offset, SEEK_SET);
        p = malloc(sizeof(pessoa));
        fread(&p->removido,sizeof(char), 1, fd);
        fread(&p->tamanhoRegistro, sizeof(int), 1, fd);
        if(p->removido == '0'){
            fread(&p->idPessoa, sizeof(int), 1, fd);
            if(p->idPessoa == param){
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
            }
            else{
                    free(p); p = NULL;
                    fseek(fdh, sizeof(long), SEEK_CUR);
                }
        }
        fclose(fd); fclose(fdh);
        if(encontrado) return p;
        printf("Registro inexistente.\n\n");
        return NULL;
    }

    // idadePessoa
    else if(strcmp(tipoBusca, "idadePessoa") == 0){
        scanf("%d", &param);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
        fread(&h.Offset,sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(tmp->idadePessoa == param){
                    p = tmp; encontrado = 1; break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado) return p;
        printf("Registro inexistente.\n\n");
        return NULL;
    }

    // nomePessoa
    else if(strcmp(tipoBusca,"nomePessoa")==0){
        scan_quote_string(parametro);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro,tmp->nomePessoa)==0){
                    p = tmp; encontrado = 1; break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado) return p;
        printf("Registro inexistente.\n\n");
        return NULL;
    }

    // nomeUsuario
    else if(strcmp(tipoBusca,"nomeUsuario")==0){
        scan_quote_string(parametro);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro,tmp->nomeUsuario)==0){
                    p = tmp; encontrado = 1; break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado) return p;
        printf("Registro inexistente.\n\n");
        return NULL;
    }

    printf("Tipo de busca inválido.\n");
    fclose(fd);
    fclose(fdh);
    return NULL;
}

segue* busca_binaria(segue *vetor, int tamanho, int idBusca){
    int esquerda = 0, direita = tamanho - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (vetor[meio].idPessoaQueSegue == idBusca) {
            return &vetor[meio];
        } else if (vetor[meio].idPessoaQueSegue < idBusca) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return NULL;
}

long busca_binaria_indice(indice* vetor, int n, int valor){
    
    int ini = 0, fim = n-1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (vetor[meio].idPessoa == valor)
            return vetor[meio].Offset;
        else if (vetor[meio].idPessoa < valor)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void busca_print(FILE *fd, FILE *fdh, char *tipoBusca){
  if(fd == NULL || fdh == NULL) {
        printf("Falha no processamento do arquivo\n");
        return;
    }

    headerIndice hi;
    header h;
    pessoa *p;
    indice* i;
    indice ibusca;
    int encontrado = 0;
    int param;
    char parametro[30];

    // idPessoa (utiliza índice)
    if(strcmp(tipoBusca, "idPessoa") == 0){
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
        i = vetor_ind(fdh);
        ibusca.Offset=busca_binaria_indice(i,h.quantidadePessoas,param);
        fseek(fd, ibusca.Offset, SEEK_SET);
        p = malloc(sizeof(pessoa));
        fread(&p->removido,sizeof(char), 1, fd);
        fread(&p->tamanhoRegistro, sizeof(int), 1, fd);
        if(p->removido == '0'){
            fread(&p->idPessoa, sizeof(int), 1, fd);
            if(p->idPessoa == param){
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
                print_registro(*p);
            }
            else{
                    free(p); p = NULL;
                }
        }
        fclose(fd); fclose(fdh);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    // idadePessoa
    else if(strcmp(tipoBusca, "idadePessoa") == 0){
        scanf("%d", &param);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
        fread(&h.Offset,sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(tmp->idadePessoa == param){
                    p = tmp; 
                    encontrado = 1;
                    print_registro(*p);
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    // nomePessoa
    else if(strcmp(tipoBusca,"nomePessoa")==0){
        scan_quote_string(parametro);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro,tmp->nomePessoa)==0){
                    p = tmp; 
                    encontrado = 1;
                    print_registro(*p);
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    // nomeUsuario
    else if(strcmp(tipoBusca,"nomeUsuario")==0){
        scan_quote_string(parametro);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro,tmp->nomeUsuario)==0){
                    p = tmp; 
                    encontrado = 1; 
                    print_registro(*p);
                    break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    printf("Tipo de busca inválido.\n");
    fclose(fd);
    fclose(fdh);
    return;

}

void busca_substitui(FILE *fd, FILE *fdh, char *tipoBusca){
  if(fd == NULL || fdh == NULL) {
        printf("Falha no processamento do arquivo\n");
        return;
    }

    headerIndice hi;
    header h;
    pessoa *p;
    indice* i;
    indice ibusca;
    int encontrado = 0;
    int param;
    char parametro[30];

    // idPessoa (utiliza índice)
    if(strcmp(tipoBusca, "idPessoa") == 0){
        scanf("%d", &param);
        printf("tetste %d",param);
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
        i = vetor_ind(fdh);
        ibusca.Offset=busca_binaria_indice(i,h.quantidadePessoas,param);
        fseek(fd, ibusca.Offset, SEEK_SET);
        free(i);
        p = malloc(sizeof(pessoa));
        fread(&p->removido,sizeof(char), 1, fd);
        fread(&p->tamanhoRegistro, sizeof(int), 1, fd);
        if(p->removido == '0'){
            fread(&p->idPessoa, sizeof(int), 1, fd);
            if(p->idPessoa == param){
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
                substitui_registro(fd,fdh,*p);
            }
            else{
                    free(p); p = NULL;
                }
        }
        fclose(fd); fclose(fdh);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    // idadePessoa
    else if(strcmp(tipoBusca, "idadePessoa") == 0){
        scanf("%d", &param);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
        fread(&h.Offset,sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(tmp->idadePessoa == param){
                    p = tmp; 
                    encontrado = 1;
                    substitui_registro(fd,fdh,*p);
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    // nomePessoa
    else if(strcmp(tipoBusca,"nomePessoa")==0){
        scan_quote_string(parametro);//parametro a ser buscado
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro,tmp->nomePessoa)==0){
                    p = tmp; 
                    encontrado = 1;
                    substitui_registro(fd,fdh,*p);
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    // nomeUsuario
    else if(strcmp(tipoBusca,"nomeUsuario")==0){
        scan_quote_string(parametro);
        fseek(fd, 1, SEEK_SET);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        fread(&h.Offset, sizeof(long), 1, fd);
        for(int k=0; k<NUMERO_PESSOAS; k++){
            pessoa *tmp = malloc(sizeof(pessoa));
            fread(&tmp->removido,sizeof(char), 1, fd);
            fread(&tmp->tamanhoRegistro, sizeof(int), 1, fd);
            if(tmp->removido == '0'){
                fread(&tmp->idPessoa, sizeof(int), 1, fd);
                fread(&tmp->idadePessoa, sizeof(int), 1, fd);
                fread(&tmp->tamanhoNomePessoa, sizeof(int), 1, fd);
                tmp->nomePessoa = malloc(tmp->tamanhoNomePessoa + 1);
                fread(tmp->nomePessoa, sizeof(char), tmp->tamanhoNomePessoa, fd);
                tmp->nomePessoa[tmp->tamanhoNomePessoa] = 0;
                fread(&tmp->tamanhoNomeUsuario, sizeof(int), 1, fd);
                tmp->nomeUsuario = malloc(tmp->tamanhoNomeUsuario + 1);
                fread(tmp->nomeUsuario, sizeof(char), tmp->tamanhoNomeUsuario, fd);
                tmp->nomeUsuario[tmp->tamanhoNomeUsuario] = 0;
                if(strcmp(parametro,tmp->nomeUsuario)==0){
                    p = tmp; 
                    encontrado = 1; 
                    substitui_registro(fd,fdh,*p);
                    break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(encontrado==0){printf("Registro inexistente.\n\n");}
        
        return;
    }

    else{printf("Tipo de busca inválido.\n");}
    fclose(fd);
    fclose(fdh);
    return;
    
}