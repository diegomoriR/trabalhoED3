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
        printf("Falha no processamento do arquivo entrada.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    FILE *fdout = fopen(arquivoSaida, "wb+"); // abrindo o arquivo para a escrita binaria
    if(fdout == NULL){
        printf("Falha no processamento do arquivo saida.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }



    //lendo o cabeçalho do arquivo
    headerSegue hs;
    fread(&hs.status,sizeof(char),1,fdin);
    fread(&hs.quantidadePessoas,sizeof(int),1,fdin);
    fread(&hs.proxRRN,sizeof(int),1,fdin);

    // vetor para os resgistros
    segue Ps[hs.quantidadePessoas];
    for(int i =0; i<hs.quantidadePessoas;i++){//copiando os registros para o vetor

        fread(&Ps[i].removido,sizeof(char),1,fdin);
        fread(&Ps[i].idPessoaQueSegue,sizeof(int),1,fdin);
        fread(&Ps[i].idPessoaQueESeguida,sizeof(int),1,fdin);
        Ps[i].dataInicioQueSegue = (char *) malloc(10);
        fread(&Ps[i].dataInicioQueSegue,sizeof(char),10,fdin);
        Ps[i].dataInicioQueSegue[10] = '\0';
        Ps[i].dataFimQueSegue = (char *) malloc(10);
        fread(&Ps[i].dataFimQueSegue,sizeof(char),10,fdin);
        Ps[i].dataFimQueSegue[10] = '\0';
        fread(&Ps[i].grauAmizade,sizeof(int),1,fdin);
    }

    qsort(Ps,hs.quantidadePessoas,sizeof(segue),comparaSegue);//ordenando o vetor


    //escrevendo o cabeçalho
    fwrite(&hs.status,sizeof(char),1,fdout);
    fwrite(&hs.quantidadePessoas,sizeof(int),1,fdout);
    fwrite(&hs.proxRRN,sizeof(int),1,fdout);

    for(int i =0; i<hs.quantidadePessoas;i++){//escrevendo no arquivo ordenado
    fwrite(&Ps[i].removido,sizeof(char),1,fdout);
    fwrite(&Ps[i].idPessoaQueSegue,sizeof(int),1,fdout);
    fwrite(&Ps[i].idPessoaQueESeguida,sizeof(int),1,fdout);
    fwrite(&Ps[i].dataInicioQueSegue,sizeof(char),10,fdout);
    free(Ps[i].dataInicioQueSegue);
    fwrite(&Ps[i].dataFimQueSegue,sizeof(char),10,fdout);
    free(Ps[i].dataFimQueSegue);
    fwrite(&Ps[i].grauAmizade,sizeof(int),1,fdout);
    }

    
    fclose(fdin);
    fclose(fdout);
    binarioNaTela(arquivoSaida);


}