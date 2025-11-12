#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 5 DELETE
void DELETE(char *arquivoEntrada, char *arquivoIndicePrimario, int n){

    //abrindo os arquivos para leitura e escrita binaria
    FILE *fd = fopen(arquivoEntrada, "rb+");
    if(fd == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb+");
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    int buscas[n];
    char tipoBusca[15];

    headerIndice hi;
    header h;
    pessoa *p;
    indice i;


    //numero de buscas
    for(int j = 0; j < n; j++){
        scanf("%d",&buscas[j]);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        INICIO_ARQUIVO(fd); //coloca no começo do arquivo pessoa
        //ler cabecalho
        fread(&h.status, sizeof(char), 1, fd);
        fread(&h.quantidadePessoas, sizeof(int), 1, fd);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
        INICIO_ARQUIVO(fd); // coloca no comeco do arquivo pessoa

        //busca a pessoa p
        p = busca(fd, fdh, tipoBusca);

        if(p != NULL){
            indice VetInd[NUMERO_PESSOAS];
            fseek(fdh, 12, SEEK_SET);
        //puxando o indice para a RAM
            for(int in = 0; in < NUMERO_PESSOAS; in++){//copia os indices para o vetor
                fread(&VetInd[in].idPessoa,sizeof(int),1,fdh);
                fread(&VetInd[in].Offset,sizeof(long),1,fdh);
            }
            //busca binaria no arquivo de indice para descobrir o offset para a remocao
            i.Offset = busca_binaria_indice(VetInd, NUMERO_PESSOAS, p->idPessoa);
            if(i.Offset != -1){
                long Offset = i.Offset;
            //remover no arquivo pessoa
                fseek(fd, Offset, SEEK_SET);
                p->removido = '1';
                fwrite(&p->removido, sizeof(char), 1, fd);

            //shift para remover da RAM
                int pos;
                for(int in = 0; in < NUMERO_PESSOAS; in++){
                    if(VetInd[in].Offset == i.Offset)
                    pos = in;
                }
                for (int j = pos; j < NUMERO_PESSOAS -1; j++){
                        VetInd[j] = VetInd[j+1];
                }
                h.quantidadeRemovidos++;
            //escrever indice no disco
            //status inconsistente
                INICIO_ARQUIVO(fdh);
                hi.status = '0';
                fwrite(&hi.status, sizeof(char), 1, fdh);

                fseek(fdh, 12, SEEK_SET);
                for(int in = 0; in < NUMERO_PESSOAS; in++){
                    fwrite(&VetInd[in].idPessoa,sizeof(int),1,fdh);
                    fwrite(&VetInd[in].Offset,sizeof(long),1,fdh);
                }

            //status consistente
                INICIO_ARQUIVO(fdh);
                hi.status = '1';
                fwrite(&hi.status, sizeof(char), 1, fdh);

            //atualizar cabecalho
            //status inconsistente
                INICIO_ARQUIVO(fd);
                h.status = '0';
                fwrite(&h.status, sizeof(char), 1, fd);
                //campo quantidade removidos
                fseek(fd, 5, SEEK_SET);
                fwrite(&h.quantidadeRemovidos, sizeof(int), 1, fd);
                //status consistente
                INICIO_ARQUIVO(fd);
                h.status = '1';
                fwrite(&h.status, sizeof(char), 1, fd);
            }

        }else{
            printf("Registro nao encontrado.\n");
        }
    }

    binarioNaTela(arquivoEntrada);
    binarioNaTela(arquivoIndicePrimario);
}
