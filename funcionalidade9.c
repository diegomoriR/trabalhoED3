//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 9 ORDER_BY
void ORDER_BY(char* arquivoEntrada, char* arquivoSaida){

    FILE *fdin = fopen(arquivoEntrada, "rb+"); // abrindo o arquivo para ler os dados
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    FILE *fdout = fopen(arquivoSaida, "wb"); // abrindo o arquivo para a escrita binaria no indice
    if(fdout == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    headerSegue hs;
    fread(&hs.status,sizeof(char),1,fdin);
    fread(&hs.quantidadePessoas,sizeof(int),1,fdin);
    fread(&hs.proxRRN,sizeof(int),1,fdin);


    segue Ps[hs.quantidadePessoas];
    for(int i =0; i<hs.quantidadePessoas;i++){
        fread(&Ps[i].removido,sizeof(char),1,fdin);
        fread(&Ps[i].idPessoaQueSegue,sizeof(int),1,fdin);
        fread(&Ps[i].idPessoaQueESeguida,sizeof(int),1,fdin);
        Ps[i].dataInicioQueSegue = (char *) malloc(10);
        fread(&Ps[i].dataInicioQueSegue,sizeof(char),10,fdin);
        Ps[i].dataFimQueSegue = (char *) malloc(10);
        fread(&Ps[i].dataFimQueSegue,sizeof(char),10,fdin);
        fread(&Ps[i].grauAmizade,sizeof(int),1,fdin);
    }

    qsort(Ps,hs.quantidadePessoas,sizeof(segue),comparaSegue);

    fread(&hs.status,sizeof(char),1,fdin);
    fread(&hs.quantidadePessoas,sizeof(int),1,fdin);
    fread(&hs.proxRRN,sizeof(int),1,fdin);

    for(int i =0; i<hs.quantidadePessoas;i++){
    fwrite(&Ps[i].removido,sizeof(char),1,fdin);
    fwrite(&Ps[i].idPessoaQueSegue,sizeof(int),1,fdin);
    fwrite(&Ps[i].idPessoaQueESeguida,sizeof(int),1,fdin);
    fwrite(&Ps[i].dataInicioQueSegue,sizeof(char),10,fdin);
    free(Ps[i].dataInicioQueSegue);
    fwrite(&Ps[i].dataFimQueSegue,sizeof(char),10,fdin);
    free(Ps[i].dataFimQueSegue);
    fwrite(&Ps[i].grauAmizade,sizeof(int),1,fdin);
    }

    fclose(fdin);
    fclose(fdout);


}