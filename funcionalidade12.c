#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"



void FUNCIONALIDADE_12(char *arquivoEntrada, char *arquivoIndicePrimario, char *arquivoOrdenado) {
    FILE *fd = fopen(arquivoEntrada, "rb");
    FILE *fdi = fopen(arquivoIndicePrimario, "rb"); // Apenas para consistência
    FILE *fdo = fopen(arquivoOrdenado, "rb");

    if (!fd || !fdi || !fdo) {
        printf("Falha na execução da funcionalidade.\n");
        if (fd) fclose(fd);
        if (fdi) fclose(fdi);
        if (fdo) fclose(fdo);
        return;
    }

    // Verifica status do arquivo de Pessoas
    char status;
    fread(&status, sizeof(char), 1, fd);
    if (status == '0') {
        printf("Falha na execução da funcionalidade.\n");
        fclose(fd); fclose(fdi); fclose(fdo);
        return;
    }
    INICIO_ARQUIVO(fd);

    header h;
    // Leitura do cabeçalho do arquivo de Pessoas
    fread(&h.status, sizeof(char), 1, fd);
    fread(&h.quantidadePessoas, sizeof(int), 1, fd);
    fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
    fread(&h.Offset, sizeof(long), 1, fd);

    Vertice *grafo = NULL; // Vetor de vértices
    int qtdVertices = 0;
    char removido;
    int tamReg;

    // 1. CONSTRUÇÃO DOS VÉRTICES
    while (fread(&removido, sizeof(char), 1, fd) == 1) {
        fread(&tamReg, sizeof(int), 1, fd);
        if (removido == '1') {
            fseek(fd, tamReg, SEEK_CUR);
            continue;
        }

        int id, idade, tamNome, tamUsuario;
        fread(&id, sizeof(int), 1, fd);
        fread(&idade, sizeof(int), 1, fd);
        fread(&tamNome, sizeof(int), 1, fd);
        fseek(fd, tamNome, SEEK_CUR);
        fread(&tamUsuario, sizeof(int), 1, fd);

        char *nomeUser = (char*)malloc(tamUsuario + 1);
        fread(nomeUser, sizeof(char), tamUsuario, fd);
        nomeUser[tamUsuario] = '\0';

        grafo = (Vertice*)realloc(grafo, (qtdVertices + 1) * sizeof(Vertice));
        grafo[qtdVertices].idPessoa = id;
        strcpy(grafo[qtdVertices].nomeUsuario, nomeUser);
        grafo[qtdVertices].inicioLista = NULL;
        qtdVertices++;
        free(nomeUser);
    }

    // Ordenar vértices pelo nome
    qsort(grafo, qtdVertices, sizeof(Vertice), comparar_vertices);

    // Leitura do cabeçalho do arquivo de Relações "Segue"
    headerSegue hs;
    fread(&hs.status, sizeof(char), 1, fdo);
    fread(&hs.quantidadePessoas, sizeof(int), 1, fdo);
    fread(&hs.proxRRN, sizeof(int), 1, fdo);

    if (hs.status == '0') {
        printf("Falha na execução da funcionalidade.\n");
        fclose(fd); fclose(fdi); fclose(fdo);
        return;
    }

    int idSegue, idSeguido;
    char dataInicio[11], dataFim[11];
    char grau;

    // 2. CONSTRUÇÃO DAS ARESTAS (Grafo Transposto)
    while (fread(&removido, sizeof(char), 1, fdo) == 1) {
        if (removido == '1') {
            fseek(fdo, 29, SEEK_CUR);
            continue;
        }

        // Lê os campos da relação
        fread(&idSegue, sizeof(int), 1, fdo);
        fread(&idSeguido, sizeof(int), 1, fdo);
        fread(dataInicio, sizeof(char), 10, fdo); dataInicio[10] = '\0';
        fread(dataFim, sizeof(char), 10, fdo); dataFim[10] = '\0';
        fread(&grau, sizeof(char), 1, fdo);

        // Encontra o índice da Pessoa SEGUIDA
        int idxDonoLista = buscar_indice_por_id(grafo, qtdVertices, idSeguido);

        // Busca o nome do SEGUE
        char *nomeSeguidor = buscar_nome_por_id(grafo, qtdVertices, idSegue);

        // Insere a aresta
        if (idxDonoLista != -1 && nomeSeguidor != NULL) {
            // Insere o nome do Seguidor na lista de adjacência do Seguido.
            inserir_aresta_transposta(&grafo[idxDonoLista], nomeSeguidor, dataInicio, dataFim, grau);
        }
    }

    // 3. IMPRESSÃO DO GRAFO TRANSPOSTO (Relações)
    int flagPrimeiraImpressao = 1;

    for (int i = 0; i < qtdVertices; i++) {
        // Itera sobre o vetor de vértices
        if (grafo[i].inicioLista != NULL) {
            // Imprime linha de separação
            if (!flagPrimeiraImpressao) printf("\n");
            flagPrimeiraImpressao = 0;

            Aresta *atual = grafo[i].inicioLista; // Itera sobre os seguidores
            while (atual != NULL) {
                // Formatação NULO para DataFim e GrauAmizade
                char strDataFim[15];
                if (atual->dataFim[0] == '\0' || atual->dataFim[0] == '$')
                    strcpy(strDataFim, "NULO");
                else
                    strcpy(strDataFim, atual->dataFim);

                char strGrau[10];
                if (atual->grauAmizade == '$' || atual->grauAmizade == '\0')
                    strcpy(strGrau, "NULO");
                else
                    sprintf(strGrau, "%c", atual->grauAmizade);

                // Imprime
                printf("%s, %s, %s, %s, %s\n",
                       grafo[i].nomeUsuario,
                       atual->nomeUsuario,
                       atual->dataInicio,
                       strDataFim,
                       strGrau);

                atual = atual->prox;
            }
        }
    }

    // 4. LIBERAÇÃO DE MEMÓRIA
    for (int i = 0; i < qtdVertices; i++) {
        Aresta *p = grafo[i].inicioLista;
        while (p != NULL) {
            Aresta *temp = p;
            p = p->prox;
            free(temp);
        }
    }
    if(grafo) free(grafo);

    fclose(fd);
    fclose(fdi);
    fclose(fdo);
}
