// Lucas Soares Leite Santos - 15472162
// Diego Mori Rodrigues - 13782421

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

// funcionalidade 7 UPDATE
void UPDATE(char *arquivoEntrada, char *arquivoIndice, int n)
{

    FILE *fdin = fopen(arquivoEntrada, "rb+"); // abrindo o arquivo para ler os dados
    if (fdin == NULL)
    {
        printf("Falha no processamento do arquivo.\n"); // verificando se o arquivo foi aberto corretamente
        return;
    }

    FILE *fdh = fopen(arquivoIndice, "rb+"); // abrindo o arquivo para a escrita binaria no indice
    if (fdh == NULL)
    {
        printf("Falha no processamento do arquivo.\n"); // verificando se o arquivo foi aberto corretamente
        return;
    }

    INICIO_ARQUIVO(fdin);

    // criando headers e pessoas pra facilitar a manipulação de dados
    headerIndice hi;
    header h;
    pessoa p;

    // copiando o Arquivo indice para um vetor
    fseek(fdh, 0, SEEK_END);
    long tamanhoArquivo = ftell(fdh); // pega o tamanho do arquivo
    const long inicioRegistros = 12;
    int t = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long)); // calcula o número de registros
    indice *VetInd = (indice *)malloc(t * sizeof(indice));
    fseek(fdh, 0, SEEK_SET);
    fread(&hi.status, sizeof(char), 1, fdh);
    fseek(fdh, TAMANHO_HEADER_INDICE, SEEK_SET);
    for (int i = 0; i < t; i++)
    { // copia os indices para o vetor
        fread(&VetInd[i].idPessoa, sizeof(int), 1, fdh);
        fread(&VetInd[i].Offset, sizeof(long), 1, fdh);
    }

    for (int j = 0; j < n; j++)
    { // controle para o número de buscas

        int buscas;
        int b, param, k, tam;
        char tipoBusca[15];
        char parametro[30];

        b = 0;                // controle de registros encontrados com o parametro buscado
        scanf("%d", &buscas); // numero da busca com o parametro
        scanf(" %[^=]", tipoBusca);
        scanf("%*c");
        fseek(fdin, 0, SEEK_SET); // coloca no começo do arquivo pessoa

        if (strcmp(tipoBusca, "idPessoa") == 0)
        {
            indice ibusca;
            scanf("%s", parametro);
            if (strcmp(parametro, "NULO") == 0)
            {

                param = -1;
            }
            else
            {
                param = atoi(parametro);
            }
            fread(&hi.status, sizeof(char), 1, fdh);
            fseek(fdh, 12, SEEK_SET);
            fread(&h.status, sizeof(char), 1, fdin);
            fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
            fread(&h.quantidadeRemovidos, sizeof(int), 1, fdin);
            if (hi.status == '0' || h.status == '0')
            {
                fclose(fdin);
                fclose(fdh);
                printf("status do arquivo/pessoa inconsistente\n");
                return;
            }

            ibusca.Offset = busca_binaria_indice(VetInd, h.quantidadePessoas, param);
            fseek(fdin, ibusca.Offset, SEEK_SET);
            fread(&p.removido, sizeof(char), 1, fdin);
            fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
            long offset = ftell(fdin);
            if (p.removido == '0')
            {
                fread(&p.idPessoa, sizeof(int), 1, fdin);
                if (p.idPessoa == param)
                {
                    fread(&p.idadePessoa, sizeof(int), 1, fdin);
                    fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                    p.nomePessoa = (char *)malloc(p.tamanhoNomePessoa + 1);
                    fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                    p.nomePessoa[p.tamanhoNomePessoa] = 0;
                    fread(&p.tamanhoNomeUsuario, sizeof(int), 1, fdin);
                    p.nomeUsuario = (char *)malloc(p.tamanhoNomeUsuario + 1);
                    fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
                    p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
                    b = 1;
                    substitui_registro(fdin, fdh, p, offset,VetInd);
                }
                else
                {
                    b = 0;
                }
            }

            if (b == 0 && j < n - 1)
            {
                scanf("%*c");
                scanf("%s", parametro); // lê qual campo quer substituir para funcionamento das próximas chamadas
                continue;
            }

        } // caso busca por id

        else if (strcmp(tipoBusca, "idadePessoa") == 0)
        {
            scanf("%s", parametro);
            if (strcmp(parametro, "NULO") == 0)
            {

                param = -1;
            }
            else
            {
                param = atoi(parametro);
            } // pega o parametro a ser buscado
            fseek(fdin, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
            fread(&h.quantidadeRemovidos, sizeof(int), 1, fdin);
            fread(&h.Offset, sizeof(long), 1, fdin);
            for (k = 0; k < NUMERO_PESSOAS; k++)
            {

                fread(&p.removido, sizeof(char), 1, fdin);
                fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
                long offset = ftell(fdin);

                if (p.removido == '0')
                { // registro nao esta marcado como removido

                    fread(&p.idPessoa, sizeof(int), 1, fdin);
                    fread(&p.idadePessoa, sizeof(int), 1, fdin);
                    fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                    p.nomePessoa = (char *)malloc(p.tamanhoNomePessoa + 1);
                    fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                    p.nomePessoa[p.tamanhoNomePessoa] = 0;
                    fread(&p.tamanhoNomeUsuario, sizeof(int), 1, fdin);
                    p.nomeUsuario = (char *)malloc(p.tamanhoNomeUsuario + 1);
                    fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
                    p.nomeUsuario[p.tamanhoNomeUsuario] = 0;

                    if (p.idadePessoa == param)
                    { // verifica se é o parâmetro buscado

                        b++; // aumenta o número de registros encontrados
                        // imprime os dados
                        substitui_registro(fdin, fdh, p, offset,VetInd);
                    }
                    free(p.nomePessoa);
                    free(p.nomeUsuario);
                }
                else
                {
                    fseek(fdin, p.tamanhoRegistro, SEEK_CUR);
                } // registro removido, vai para o próximo
            }
            if (b == 0 && j < n - 1)
            {
                scanf("%*c");
                scanf("%s", parametro); // lê qual campo quer substituir para funcionamento das próximas chamadas
            } // nenhum registro b com esse parâmetro
        } // caso busca idade

        else if (strcmp(tipoBusca, "nomePessoa") == 0)
        {
            scanf("%s", parametro);
            if (strcmp(parametro, "NULO") == 0)
            {
                tam = 0;
            }
            else
            {
                memmove(&parametro[0], &parametro[1], strlen(parametro)); // "NOVO\""
                // Remove a última aspa (colocando um '\0')
                parametro[strlen(parametro) - 1] = '\0';
                tam = strlen(parametro);
            }
            fseek(fdin, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
            fread(&h.quantidadeRemovidos, sizeof(int), 1, fdin);
            fread(&h.Offset, sizeof(long), 1, fdin);
            for (k = 0; k < NUMERO_PESSOAS; k++)
            {

                fread(&p.removido, sizeof(char), 1, fdin);
                fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
                long offset = ftell(fdin);

                if (p.removido == '0')
                { // registro nao esta marcado como removido

                    fread(&p.idPessoa, sizeof(int), 1, fdin);
                    fread(&p.idadePessoa, sizeof(int), 1, fdin);
                    fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                    p.nomePessoa = (char *)malloc(p.tamanhoNomePessoa + 1);
                    fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                    p.nomePessoa[p.tamanhoNomePessoa] = 0;
                    fread(&p.tamanhoNomeUsuario, sizeof(int), 1, fdin);
                    p.nomeUsuario = (char *)malloc(p.tamanhoNomeUsuario + 1);
                    fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
                    p.nomeUsuario[p.tamanhoNomeUsuario] = 0;

                    if (tam == 0)
                    { // caso está buscando o nulo
                        if (p.tamanhoNomeUsuario == 0)
                        {
                            b++; // aumenta o número de registros encontrados
                            // imprime os dados
                            substitui_registro(fdin, fdh, p, offset,VetInd);
                            break;
                        }
                    }
                    else if (strcmp(parametro, p.nomePessoa) == 0)
                    { // verifica se é o parâmetro buscado

                        b++; // aumenta o número de registros encontrados
                        // imprime os dados
                        substitui_registro(fdin, fdh, p, offset,VetInd);
                        break;
                    }
                    free(p.nomePessoa);
                    free(p.nomeUsuario);
                }
                else
                {
                    fseek(fdin, p.tamanhoRegistro, SEEK_CUR); // registro removido, vai para o próximo
                }
            }
            if (b == 0 && j < n - 1)
            {
                scanf("%*c");
                scanf("%s", parametro); // lê qual campo quer substituir para funcionamento das próximas chamadas
            } // nenhum registro b com esse parâmetro

        } // caso busca nome pessoa

        else if (strcmp(tipoBusca, "nomeUsuario") == 0)
        {
            scanf("%s", parametro);
            if (strcmp(parametro, "NULO") == 0)
            {
                tam = 0;
            }
            else
            {
                memmove(&parametro[0], &parametro[1], strlen(parametro)); // "NOVO\""
                // Remove a última aspa (colocando um '\0')
                parametro[strlen(parametro) - 1] = '\0';
                tam = strlen(parametro);
            }
            fseek(fdin, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
            fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
            fread(&h.quantidadeRemovidos, sizeof(int), 1, fdin);
            fread(&h.Offset, sizeof(long), 1, fdin);
            for (k = 0; k < NUMERO_PESSOAS; k++)
            {

                fread(&p.removido, sizeof(char), 1, fdin);
                fread(&p.tamanhoRegistro, sizeof(int), 1, fdin);
                long offset = ftell(fdin);

                if (p.removido == '0')
                { // registro nao esta marcado como removido

                    fread(&p.idPessoa, sizeof(int), 1, fdin);
                    fread(&p.idadePessoa, sizeof(int), 1, fdin);
                    fread(&p.tamanhoNomePessoa, sizeof(int), 1, fdin);
                    p.nomePessoa = (char *)malloc(p.tamanhoNomePessoa + 1);
                    fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fdin);
                    p.nomePessoa[p.tamanhoNomePessoa] = 0;
                    fread(&p.tamanhoNomeUsuario, sizeof(int), 1, fdin);
                    p.nomeUsuario = (char *)malloc(p.tamanhoNomeUsuario + 1);
                    fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fdin);
                    p.nomeUsuario[p.tamanhoNomeUsuario] = 0;

                    if (tam == 0)
                    {
                        if (p.tamanhoNomeUsuario == 0)
                        {
                            b++; // aumenta o número de registros encontrados
                            // imprime os dados
                            substitui_registro(fdin, fdh, p, offset,VetInd);
                            break;
                        }
                    }
                    else if (strcmp(parametro, p.nomeUsuario) == 0)
                    { // verifica se é o parâmetro buscado

                        b++; // aumenta o número de registros encontrados
                        // imprime os dados
                        substitui_registro(fdin, fdh, p, offset,VetInd);
                        break;
                    }
                    free(p.nomePessoa);
                    free(p.nomeUsuario);
                }
                else
                {
                    fseek(fdin, p.tamanhoRegistro, SEEK_CUR);
                } // registro removido, vai para o próximo
            }
            if (b == 0 && j < n - 1)
            {
                scanf("%*c");
                scanf("%s", parametro); // lê qual campo quer substituir para funcionamento das próximas chamadas
            } // nenhum registro b com esse parâmetro

        } // caso busca nome Usuário
    }


    free(VetInd);
    fclose(fdin);
    fclose(fdh);
    binarioNaTela(arquivoEntrada);
    binarioNaTela(arquivoIndice);
    return;
}