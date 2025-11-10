#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

//funcionalidade 10 (JUNCAO)

void JUNCAO(char *arquivoEntrada, char *arquivoIndicePrimario, char *arquivoOrdenado){
    FILE *fdin = fopen(arquivoEntrada, "rb");
    if(fdin == NULL){
        printf("Falha no processamento do arquivo\n");
    }
    FILE *fdh = fopen(arquivoIndicePrimario, "rb");
    if(fdh == NULL){
        printf("Falha no processamento do arquivo\n");
    }
    FILE *fdo = fopen(arquivoOrdenado, "rb");
    if(fdo == NULL){
        printf("Falha no processamento do arquivo\n");
    }

    //inicializando para manipulacao dos dados
    header h;
    headerIndice hi;
    headerSegue hs;
    pessoa *p;
    indice i;
    segue *s;

    int n;
    int buscas[n];
    char tipoBusca[15];

    //numero de buscas
    for(int j = 0; j < n; j++){
        int b = 0; //registros encontrados com o parametro buscado
        scanf("%d",&buscas[j]);//numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        INICIO_ARQUIVO(fdh); //coloca no começo do arquivo
        //puxando o indice para a RAM
        indice *indices = (indice *)malloc(NUMERO_PESSOAS * sizeof(indice));
        //lendo o indice para a RAM
        fread(indices, sizeof(indice), NUMERO_PESSOAS, fdh);

        //busca uma pessoa p com o parametro solicitado
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

            //puxando o segueOrdenado para a RAM
            segue *segueOrdenado = (segue *)malloc(NUMERO_RRN * sizeof(segue));
            //lendo o segueOrdenado para a RAM
            fread(segueOrdenado, sizeof(segue), NUMERO_RRN, fdo);

            //realiza a busca binaria no segue ordenado para achar idpessoa == idpessoaQueSegue
            s = busca_binaria(segueOrdenado, NUMERO_RRN, p->idPessoa);

            // percorre todos os registros consecutivos com mesmo idPessoa
            int idx = (s != NULL) ? (s - segueOrdenado) : -1;
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
                if (idx < NUMERO_RRN && segueOrdenado[idx].idPessoaQueSegue == p->idPessoa)
                    s = &segueOrdenado[idx];
                else
                    break;
            }
            // libera memoria
            free(segueOrdenado);
            free(p->nomePessoa);
            free(p->nomeUsuario);
            free(p);
        }else{
            printf("Registro inexistente\n");
        }
    }
}
