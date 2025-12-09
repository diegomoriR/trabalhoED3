#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


void FUNCIONALIDADE_11(char *arquivoEntrada, char *arquivoIndicePrimario, char *arquivoOrdenado) {
    // Abre os arquivos de entrada em modo binário de leitura.
    FILE *fd = fopen(arquivoEntrada, "rb"); // Arquivo de dados de Pessoas
    FILE *fdi = fopen(arquivoIndicePrimario, "rb"); // Apenas para validação conforme padrão (não usado para leitura de dados aqui)
    FILE *fdo = fopen(arquivoOrdenado, "rb"); // Arquivo de relações "Segue"

    // Verifica se a abertura dos arquivos foi bem-sucedida.
    if (!fd || !fdi || !fdo) {
        printf("Falha na execução da funcionalidade.\n");
        if (fd) fclose(fd);
        if (fdi) fclose(fdi);
        if (fdo) fclose(fdo);
        return;
    }

    // Verificando consistência do arquivo de Pessoas (cabeçalho)
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

    Vertice *grafo = NULL;
    int qtdVertices = 0;

    char removido;
    int tamReg;

    // 1. CONSTRUÇÃO DOS VÉRTICES
    // Loop para leitura de todos os registros de Pessoas no arquivo de entrada.
    while (fread(&removido, sizeof(char), 1, fd) == 1) {
        fread(&tamReg, sizeof(int), 1, fd); // Lê o tamanho do registro

        if (removido == '1') {
            // Se o registro foi removido, pula o restante do registro.
            fseek(fd, tamReg, SEEK_CUR);
            continue;
        }

        // Se não removido, lê os campos necessários para o vértice.
        int id, idade, tamNome, tamUsuario;
        fread(&id, sizeof(int), 1, fd);
        fread(&idade, sizeof(int), 1, fd);
        fread(&tamNome, sizeof(int), 1, fd);

        fseek(fd, tamNome, SEEK_CUR); // Pula nomePessoa (não usado no grafo)

        fread(&tamUsuario, sizeof(int), 1, fd);
        char *nomeUsuario = (char*)malloc(tamUsuario + 1); // Aloca espaço para o nome de usuário
        fread(nomeUsuario, sizeof(char), tamUsuario, fd);
        nomeUsuario[tamUsuario] = '\0'; // Adiciona terminador nulo

        // Adiciona a nova Pessoa ao vetor de vértices (grafo).
        grafo = (Vertice*)realloc(grafo, (qtdVertices + 1) * sizeof(Vertice));
        grafo[qtdVertices].idPessoa = id;
        strcpy(grafo[qtdVertices].nomeUsuario, nomeUsuario);
        grafo[qtdVertices].inicioLista = NULL; // Inicializa lista de adjacência (arestas)
        qtdVertices++;

        free(nomeUsuario); // Libera o buffer temporário
    }

    // Ordena o vetor de vértices pelo nome de usuário.
    qsort(grafo, qtdVertices, sizeof(Vertice), comparar_vertices);

    // Leitura do cabeçalho do arquivo de Relações "Segue" (arquivoOrdenado).
    headerSegue hs;
    fread(&hs.status, sizeof(char), 1, fdo);
    fread(&hs.quantidadePessoas, sizeof(int), 1, fdo);
    fread(&hs.proxRRN, sizeof(int), 1, fdo);

    // Verifica status do arquivo de Relações.
    if (hs.status == '0') {
        printf("Falha na execução da funcionalidade.\n");
        fclose(fd); fclose(fdi); fclose(fdo);
        return;
    }

    int idSegue, idSeguido;
    char dataInicio[11], dataFim[11];
    char grau;

    // 2. CONSTRUÇÃO DAS ARESTAS
    // Loop para leitura de todos os registros de Relações no arquivo ordenado.
    while (fread(&removido, sizeof(char), 1, fdo) == 1) {
        if (removido == '1') {
            // Pula registro removido (tamanho 29)
            fseek(fdo, 29, SEEK_CUR);
            continue;
        }

        // Lê os campos da relação "Segue".
        fread(&idSegue, sizeof(int), 1, fdo);
        fread(&idSeguido, sizeof(int), 1, fdo);
        fread(dataInicio, sizeof(char), 10, fdo); dataInicio[10] = '\0';
        fread(dataFim, sizeof(char), 10, fdo); dataFim[10] = '\0';
        fread(&grau, sizeof(char), 1, fdo);

        // Encontra o índice do SEGUE (Seguidor) no vetor de vértices.
        int idxSeguidor = buscar_indice_por_id(grafo, qtdVertices, idSegue);

        // Busca o nome do SEGUIDO (o alvo da aresta).
        char *nomeSeguido = buscar_nome_por_id(grafo, qtdVertices, idSeguido);

        // Se ambos existirem, insere a aresta. (Grafo DIRETO: Seguidor -> Seguido)
        if (idxSeguidor != -1 && nomeSeguido != NULL) {
            // Insere o Seguido na lista de adjacência do Seguidor (ordenada por nome).
            inserir_aresta_ordenada(&grafo[idxSeguidor], nomeSeguido, dataInicio, dataFim, grau);
        }
    }

    // 3. IMPRESSÃO DO GRAFO (Relações)
    int flagPrimeiraImpressao = 1;

    for (int i = 0; i < qtdVertices; i++) {
        // Exibe apenas se o vértice (Seguidor) tiver arestas (segue alguém).
        if (grafo[i].inicioLista != NULL) {

            // Pula linha entre usuários diferentes (exceto antes do primeiro)
            if (!flagPrimeiraImpressao) {
                printf("\n"); // Pula linha entre o output de diferentes seguidores.
            }
            flagPrimeiraImpressao = 0;

            Aresta *atual = grafo[i].inicioLista;
            while (atual != NULL) {

                // Formatação Data Fim
                char strDataFim[15];
                if (atual->dataFim[0] == '\0' || atual->dataFim[0] == '$')
                    strcpy(strDataFim, "NULO");
                else
                    strcpy(strDataFim, atual->dataFim);

                // Formatação Grau
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
    if(grafo) free(grafo); // Libera o vetor de vértices

    // Fecha os arquivos.
    fclose(fd);
    fclose(fdi);
    fclose(fdo);
}
