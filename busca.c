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
    int b = 0;
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
                
        
        fseek(fdh, 0, SEEK_END);
        long tamanhoArquivo = ftell(fdh);//pega o tamanho do arquivo
        const long inicioRegistros = 12;
        int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));//calcula o número de registros
        indice VetInd[n];
        headerIndice hi;
        fseek(fdh, 0, SEEK_SET);
        fread(&hi.status,sizeof(char),1,fdh);
        fseek(fdh, TAMANHO_HEADER_INDICE ,SEEK_SET);
        for(int i=0;i<n;i++){//copia os indices para o vetor
            fread(&VetInd[i].idPessoa,sizeof(int),1,fdh);
            fread(&VetInd[i].Offset,sizeof(long),1,fdh);
        }


        ibusca.Offset=busca_binaria_indice(VetInd,h.quantidadePessoas,param);
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
                b = 1;
            }
            else{
                    free(p); p = NULL;
                    fseek(fdh, sizeof(long), SEEK_CUR);
                }
        }
        fclose(fd); fclose(fdh);
        if(b) return p;
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
                    p = tmp; b = 1; break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(b) return p;
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
                    p = tmp; b = 1; break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(b) return p;
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
                    p = tmp; b = 1; break;
                }
                free(tmp->nomePessoa); free(tmp->nomeUsuario); free(tmp);
            } else {
                fseek(fd, tmp->tamanhoRegistro, SEEK_CUR);
                free(tmp);
            }
        }
        fclose(fd);
        if(b) return p;
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


  
