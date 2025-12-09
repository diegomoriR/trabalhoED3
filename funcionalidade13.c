#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


void FUNCIONALIDADE_13(char *arquivoEntrada, char *arquivoIndicePrimario, char *arquivoOrdenado, char *nomeCelebridade) {

    char nome[50];
    int len = strlen(nomeCelebridade);
    // Limpa o nome da celebridade (remove aspas duplas).
        strncpy(nome, nomeCelebridade + 1, len - 2);
        nome[len - 2] = '\0';

    // Abertura de arquivos
    FILE *fd = fopen(arquivoEntrada, "rb");
    FILE *fdi = fopen(arquivoIndicePrimario, "rb");
    FILE *fdo = fopen(arquivoOrdenado, "rb");

    if (!fd || !fdi || !fdo) {
        printf("Falha na execução da funcionalidade.\n");
        if (fd) fclose(fd);
        if (fdi) fclose(fdi);
        if (fdo) fclose(fdo);
        return;
    }

    char status;
    fread(&status, sizeof(char), 1, fd);
    if (status == '0') {
        printf("Falha na execução da funcionalidade.\n");
        fclose(fd); fclose(fdi); fclose(fdo);
        return;
    }
    // Pula cabeçalho de Pessoas
    INICIO_ARQUIVO(fd);

    header h;
    fread(&h.status, sizeof(char), 1, fd);
    fread(&h.quantidadePessoas, sizeof(int), 1, fd);
    fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
    fread(&h.Offset, sizeof(long), 1, fd);

    Vertice *grafo = NULL;
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

        char *nomeUsuario = (char*)malloc(tamUsuario + 1);
        fread(nomeUsuario, sizeof(char), tamUsuario, fd);
        nomeUsuario[tamUsuario] = '\0';

        // Alocação e inicialização do vértice
        grafo = (Vertice*)realloc(grafo, (qtdVertices + 1) * sizeof(Vertice));
        grafo[qtdVertices].idPessoa = id;
        strcpy(grafo[qtdVertices].nomeUsuario, nomeUsuario);
        grafo[qtdVertices].inicioLista = NULL;

        // Inicialização dos campos para BFS (Busca em Largura)
        grafo[qtdVertices].cor = 0; // 0= branco (não visitado)
        grafo[qtdVertices].distancia = -1; // -1=Infinito
        grafo[qtdVertices].indicePai = -1; // -1=Nulo

        qtdVertices++;
        free(nomeUsuario);
    }
    // Ordenação por Nome para otimizar buscas (buscar_indice_por_nome)
    qsort(grafo, qtdVertices, sizeof(Vertice), comparar_vertices);

    // Leitura do cabeçalho de Relações
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

    // 2. CONSTRUÇÃO DAS ARESTAS
    while (fread(&removido, sizeof(char), 1, fdo) == 1) {
        if (removido == '1') {
            fseek(fdo, 29, SEEK_CUR);
            continue;
        }

        fread(&idSegue, sizeof(int), 1, fdo);
        fread(&idSeguido, sizeof(int), 1, fdo);
        fread(dataInicio, sizeof(char), 10, fdo); dataInicio[10] = '\0';
        fread(dataFim, sizeof(char), 10, fdo); dataFim[10] = '\0';
        fread(&grau, sizeof(char), 1, fdo);

        // idxDono é o SEGUIDO
        int idxDono = buscar_indice_por_id(grafo, qtdVertices, idSeguido);
        // nomeSeguidor é quem SEGUE (a aresta)
        char *nomeSeguidor = buscar_nome_por_id(grafo, qtdVertices, idSegue);

        // Insere a aresta transposta (Seguidor na lista do Seguido)
        if (idxDono != -1 && nomeSeguidor != NULL) {
            inserir_aresta_transposta(&grafo[idxDono], nomeSeguidor, dataInicio, dataFim, grau);
        }
    }

    // 3. EXECUÇÃO DO BFS (Busca em Largura)
    int idxCeleb = buscar_indice_por_nome(grafo, qtdVertices, nome); // Encontra a celebridade

    if (idxCeleb != -1) {
        Fila f;
        inicializar_fila(&f);

        // Inicializa a celebridade (origem do BFS)
        grafo[idxCeleb].cor = 1; // cinza (Visitado)
        grafo[idxCeleb].distancia = 0;
        grafo[idxCeleb].indicePai = -1; // Celebridade não tem pai
        enfileirar(&f, idxCeleb);

        while (!fila_vazia(&f)) {
            int u = desenfileirar(&f); // u é o Seguido

            Aresta *v_aresta = grafo[u].inicioLista; // Lista de quem segue u (v)
            while (v_aresta != NULL) {
                // v é o Seguidor (o próximo a ser visitado)
                int v = buscar_indice_por_nome(grafo, qtdVertices, v_aresta->nomeUsuario);

                if (v != -1 && grafo[v].cor == 0) { // Se v é branco (não visitado)
                    grafo[v].cor = 1; // Marca como cinza (visitado)
                    grafo[v].distancia = grafo[u].distancia + 1; // Incrementa a distância

                    grafo[v].indicePai = u; // Define u (Seguido) como o pai de v (Seguidor)

                    // Armazena as informações da ARESTA (relação Segue) no NÓ DO SEGUIDOR (v)
                    // Isso é essencial para imprimir a relação de "segue" no caminho de volta.
                    strcpy(grafo[v].dataInicio, v_aresta->dataInicio);
                    strcpy(grafo[v].dataFim, v_aresta->dataFim);
                    grafo[v].grauAmizade = v_aresta->grauAmizade;

                    enfileirar(&f, v);
                }
                v_aresta = v_aresta->prox;
            }
            grafo[u].cor = 2; // Marca u como preto (processado)
        }
    }

    // 4. IMPRESSÃO DOS CAMINHOS
    int flagPrimeiraImpressao = 1;

    for (int i = 0; i < qtdVertices; i++) {
        if (i == idxCeleb) continue; // Pula a celebridade

        if (!flagPrimeiraImpressao) printf("\n");
        flagPrimeiraImpressao = 0;

        if (grafo[i].distancia == -1) {
            // Se a distância é -1, é inalcançável no grafo transposto.
            printf("NAO SEGUE A CELEBRIDADE\n");
        } else {
            // Se alcançável, reconstrói o caminho do seguidor 'i' até a celebridade.
            int atual = i; // Começa pelo seguidor
            while (atual != idxCeleb && atual != -1) {
                int prox = grafo[atual].indicePai; // O pai (Seguido)

                // Formatacoes NULO para DataFim e Grau
                char strDataFim[15];
                if (grafo[atual].dataFim[0] == '\0' || grafo[atual].dataFim[0] == '$')
                    strcpy(strDataFim, "NULO");
                else
                    strcpy(strDataFim, grafo[atual].dataFim);

                char strGrau[10];
                if (grafo[atual].grauAmizade == '$' || grafo[atual].grauAmizade == '\0')
                    strcpy(strGrau, "NULO");
                else
                    sprintf(strGrau, "%c", grafo[atual].grauAmizade);

                // Imprime
                printf("%s, %s, %s, %s, %s\n",
                       grafo[atual].nomeUsuario,
                       grafo[prox].nomeUsuario,
                       grafo[atual].dataInicio,
                       strDataFim,
                       strGrau);

                atual = prox; // Move para o pai (Seguido) para continuar o caminho
            }
        }
    }

    // 5. LIBERAÇÃO DE MEMÓRIA
    for (int i = 0; i < qtdVertices; i++) {
        Aresta *p = grafo[i].inicioLista;
        while (p != NULL) {
            Aresta *temp = p;
            p = p->prox;
            free(temp);
        }
    }
    if(grafo) free(grafo);

    fclose(fd); fclose(fdi); fclose(fdo);
}
