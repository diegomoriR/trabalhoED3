#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

//funcionalidade 10 (JUNCAO)

void JUNCAO(char *arquivoEntrada, char *arquivoIndicePrimario, char *arquivoOrdenado, int n){
    FILE *fdin = fopen(arquivoEntrada, "rb");
    if(fdin == NULL){
        printf("Falha no processamento do arquivo.\n");
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb");
    if(fdh == NULL){
        printf("Falha no processamento do arquivo.\n");
    }
    FILE *fdo = fopen(arquivoOrdenado, "rb");
    if(fdo == NULL){
        printf("Falha no processamento do arquivo.\n");
    }

    //inicializando para manipulacao dos dados
    header h;
    headerIndice hi;
    headerSegue hs;
    pessoa *p = malloc(sizeof(pessoa));
    indice i;
    segue *s;

    int buscas[n];
    char tipoBusca[15];

    //numero de buscas
    for(int j = 0; j < n; j++){
        int b = 0; //registros encontrados com o parametro buscado
        scanf("%d",&buscas[j]);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        INICIO_ARQUIVO(fdin); //coloca no começo do arquivo pessoa
        //ler cabecalho
        fread(&h.status, sizeof(char), 1, fdin);
        fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fdin);
        INICIO_ARQUIVO(fdin); // coloca no comeco do arquivo pessoa

        indice VetInd[NUMERO_PESSOAS];
            fseek(fdh, 12, SEEK_SET);
        //puxando o indice para a RAM
            for(int in = 0; in < NUMERO_PESSOAS; in++){//copia os indices para o vetor
                fread(&VetInd[in].idPessoa,sizeof(int),1,fdh);
                fread(&VetInd[in].Offset,sizeof(long),1,fdh);
            }
        //busca uma pessoa p com o parametro solicitado
        for(int k = 0; k < NUMERO_PESSOAS; k++){
        p = busca(fdin, fdh, tipoBusca);
        if(p != NULL){
        //printa a pessoa na tela
        //idPessoa
        if(p->idPessoa != -1){
            printf("Dados da pessoa de codigo %d\n", p->idPessoa);
        }else{
            printf("Dados da pessoa de codigo -\n");
        }
        //nomePessoa
        if(p->tamanhoNomePessoa != 0){
            printf("Nome: %s\n", p->nomePessoa);
        }else{
            printf("Nome: -\n");
        }
        //idadePessoa
        if(p->idadePessoa != -1){
            printf("Idade: %d\n", p->idadePessoa);
        }else{
            printf("Idade: -\n");
        }
        //nomeUsuario
        if(p->tamanhoNomeUsuario != 0){
            printf("Usuario: %s\n", p->nomeUsuario);
        }else{
            printf("Usuario: -\n");
        }
        //pula linha
        printf("\n");

            INICIO_ARQUIVO(fdo);
            fread(&hs.status, sizeof(char), 1, fdo);
            if(hs.status == '0'){
                fclose(fdin);
                fclose(fdh);
                fclose(fdo);
                return;
            }
            fread(&hs.proxRRN, sizeof(int), 1, fdo);
            fread(&hs.quantidadePessoas, sizeof(int), 1, fdo);

            segue VetSegue[hs.quantidadePessoas];
            fseek(fdo, 9, SEEK_SET);
        //puxando o indice para a RAM
            for(int in = 0; in < hs.quantidadePessoas; in++){//copia os indices para o vetor
                fread(&VetSegue[in].removido,sizeof(char),1,fdo);
                fread(&VetSegue[in].idPessoaQueSegue,sizeof(int),1,fdo);
                fread(&VetSegue[in].idPessoaQueESeguida,sizeof(int),1,fdo);
                VetSegue[in].dataInicioQueSegue = (char *) malloc(11);
                fread(VetSegue[in].dataInicioQueSegue,sizeof(char),10,fdo);
                VetSegue[in].dataInicioQueSegue[11]= '\0';
                VetSegue[in].dataFimQueSegue = (char *) malloc(11);
                fread(VetSegue[in].dataFimQueSegue,sizeof(char),10,fdo);
                VetSegue[in].dataFimQueSegue[11]= '\0';
                fread(&VetSegue[in].grauAmizade, sizeof(char), 1, fdo);
            }

            //realiza a busca binaria no segue ordenado para achar idpessoa == idpessoaQueSegue
            s = busca_binaria(VetSegue, NUMERO_RRN, p->idPessoa);

            // percorre todos os registros consecutivos com mesmo idPessoa
            int idx = (s != NULL) ? (s - VetSegue) : -1;
            while(p != NULL && (s->idPessoaQueSegue == p->idPessoa)){
                //idSeguida
                printf("Segue a pessoa de codigo %d\n", s->idPessoaQueESeguida);
                //grauAmizade
                if(s->grauAmizade == '0'){
                    printf("Justificativa para seguir: celebridade\n");
                }else if(s->grauAmizade == '1'){
                    printf("Justificativa para seguir: amiga de minha amiga\n");
                }else if(s->grauAmizade == '2'){
                    printf("Justificativa para seguir: minha amiga\n");
                }else if(s->grauAmizade == '$'){
                    printf("Justificativa para seguir: -\n");
                }
                //dataInicio
                printf("Comecou a seguir em: %s\n", s->dataInicioQueSegue);
                //dataFim
                if(strcmp(s->dataFimQueSegue, "$$$$$$$$$$") == 0){
                    printf("Parou de seguir em: -\n");
                }else{
                printf("Parou de seguir em: %s\n", s->dataFimQueSegue);
                }
                //pula linha
                printf("\n");
                idx++;
                // avança para o próximo registro consecutivo
                if (idx < NUMERO_RRN && VetSegue[idx].idPessoaQueSegue == p->idPessoa)
                    s = &VetSegue[idx];
                if(VetSegue[idx].idPessoaQueSegue != p->idPessoa){
                    break;
                }
            }
        }else{
            printf("Registro inexistente\n");
        }
        }
    }
    free(p);
}

