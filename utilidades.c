#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header_pessoa.h"

/*
Fun��o para imprimir dados salvos no arquivo em bin�rio
(util para comparar saida no run codes)
*/
void binarioNaTela(char *nomeArquivoBinario) {

	/* Use essa fun��o para compara��o no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (voc� n�o vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (fun��o binarioNaTela): n�o foi poss�vel abrir o arquivo que me passou para leitura. Ele existe e voc� t� passando o nome certo? Voc� lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa fun��o para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada est� da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings j� alocadas str1 e str2 do seu programa, voc� faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espa�os, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler at� o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc t� tentando ler uma string que n�o t� entre aspas! Fazer leitura normal %s ent�o, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

char *mystrsep(char **str, char const *delim) {
    char *inicio = *str;
    char *p;
    if (inicio == NULL)
        return NULL;
    for (p = inicio; *p != '\0'; p++) {
        const char *d;
        for (d = delim; *d != '\0'; d++) {
            if (*p == *d) {
                *p = '\0';
                *str = p + 1;
                return inicio;
            }
        }
    }
    *str = NULL;
    return inicio;
}



void print_registro(pessoa p){
if(p.removido=='1'){return;}

    //idPessoa
    if(p.idPessoa != -1){
    printf("Dados da pessoa de codigo %d\n", p.idPessoa);
    }else{
    printf("Dados da pessoa de codigo -\n");
    }
    //nomePessoa
    if(p.tamanhoNomePessoa != 0){
    printf("Nome: %s\n", p.nomePessoa);
    }else{
    printf("Nome: - \n");
    }
    //idadePessoa
    if(p.idadePessoa != -1){
    printf("Idade: %d\n", p.idadePessoa);
    }else{
    printf("Idade: -\n");
    }
    //usuarioPessoa
    if(p.tamanhoNomeUsuario != 0){
    printf("Usuario: %s\n", p.nomeUsuario);
    }else{
    printf("Usuario: - \n");
    }
    printf("\n");
return;
}

int comparaSegue(const void *a, const void *b) {
    // Converte os ponteiros gen�ricos (void*) de volta para o nosso tipo (segue*)
    const segue *regA = (const segue *)a;
    const segue *regB = (const segue *)b;


    // CRIT�RIO 1: idPessoaQueSegue
    if(regA->idPessoaQueSegue!=regB->idPessoaQueSegue){
        if(regA->idPessoaQueSegue==-1){return 1;}
        else if(regB->idPessoaQueSegue==-1){return -1;}
        else {return regA->idPessoaQueSegue - regB->idPessoaQueSegue;}
    }

    // CRIT�RIO 2: idPessoaQueESeguida
    else if(regA->idPessoaQueESeguida!=regB->idPessoaQueESeguida){
        if(regA->idPessoaQueESeguida==-1){return 1;}
        else if(regB->idPessoaQueESeguida==-1){return -1;}
        else {return regA->idPessoaQueESeguida - regB->idPessoaQueESeguida;}
    }

    // CRIT�RIO 3: dataInicioQueSegue
    else if(strcmp(regA->dataInicioQueSegue,regB->dataInicioQueSegue)!=0){
        if(strcmp(regA->dataInicioQueSegue, "$$$$$$$$$$") == 0){return 1;}
        else if(strcmp(regB->dataInicioQueSegue, "$$$$$$$$$$") == 0){return -1;}
        else{return strcmp(regA->dataInicioQueSegue,regB->dataInicioQueSegue);}
    }

    // CRIT�RIO 4: dataFimQueSegue
    else if(strcmp(regA->dataFimQueSegue,regB->dataFimQueSegue)!=0){
        if(strcmp(regA->dataFimQueSegue, "$$$$$$$$$$") == 0){return 1;}
        else if(strcmp(regB->dataFimQueSegue, "$$$$$$$$$$") == 0){return -1;}
        else{return strcmp(regA->dataFimQueSegue,regB->dataFimQueSegue);}
    }

    // EMPATE TOTAL
    return 0;
}


indice* vetor_ind(FILE *fdh){

    if (fdh == NULL) exit(-1);//arquivo n�o encontrado
    fseek(fdh, 0, SEEK_END);
    long tamanhoArquivo = ftell(fdh);//pega o tamanho do arquivo
    const long inicioRegistros = 12;
    int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));//calcula o n�mero de registros

    indice* VetInd = (indice *)malloc(n * sizeof(indice));
    headerIndice hi;
    fseek(fdh, 0, SEEK_SET);
    fread(&hi.status,sizeof(char),1,fdh);
    fseek(fdh, inicioRegistros ,SEEK_SET);

    for(int i=0;i<n;i++){//copia os indices para o vetor
        fread(&VetInd[i].idPessoa,sizeof(int),1,fdh);
        fread(&VetInd[i].Offset,sizeof(long),1,fdh);
    }
    return VetInd;

}

void lista_segue(FILE *fdin, FILE *fdh, FILE *fdo, pessoa p){
    header h;
    headerIndice hi;
    headerSegue hs;
    indice i;
    segue *s;
    INICIO_ARQUIVO(fdin); //coloca no come�o do arquivo pessoa
        //ler cabecalho
        fread(&h.status, sizeof(char), 1, fdin);
        fread(&h.quantidadePessoas, sizeof(int), 1, fdin);
        fread(&h.quantidadeRemovidos, sizeof(int), 1, fdin);
        INICIO_ARQUIVO(fdin); // coloca no comeco do arquivo pessoa

        //printa a pessoa na tela
        //idPessoa
        if(p.idPessoa != -1){
            printf("Dados da pessoa de codigo %d\n", p.idPessoa);
        }else{
            printf("Dados da pessoa de codigo -\n");
        }
        //nomePessoa
        if(p.tamanhoNomePessoa != 0){
            printf("Nome: %s\n", p.nomePessoa);
        }else{
            printf("Nome: -\n");
        }
        //idadePessoa
        if(p.idadePessoa != -1){
            printf("Idade: %d\n", p.idadePessoa);
        }else{
            printf("Idade: -\n");
        }
        //nomeUsuario
        if(p.tamanhoNomeUsuario != 0){
            printf("Usuario: %s\n", p.nomeUsuario);
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
            s = busca_binaria(VetSegue, NUMERO_RRN, p.idPessoa);

            // percorre todos os registros consecutivos com mesmo idPessoa
            int idx = (s != NULL) ? (s - VetSegue) : -1;
            while( (s->idPessoaQueSegue == p.idPessoa)){
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
                // avan�a para o pr�ximo registro consecutivo
                if (idx < NUMERO_RRN && VetSegue[idx].idPessoaQueSegue == p.idPessoa)
                    s = &VetSegue[idx];
                if(VetSegue[idx].idPessoaQueSegue != p.idPessoa){
                    break;
                }
            }

}

void remover_registro(FILE *fdin, FILE *fdh, pessoa p){

    headerIndice hi;
    header h;
    indice i;

    indice VetInd[500];
            fseek(fdh, 12, SEEK_SET);
        //puxando o indice para a RAM
            for(int in = 0; in < 500; in++){//copia os indices para o vetor
                fread(&VetInd[in].idPessoa,sizeof(int),1,fdh);
                fread(&VetInd[in].Offset,sizeof(long),1,fdh);
            }
            //busca binaria no arquivo de indice para descobrir o offset para a remocao
            //i.Offset = busca_binaria_indice(VetInd,500, p.idPessoa);
            printf("offset %ld\n", i.Offset);
            if(i.Offset != -1){
                long Offset = i.Offset;
            //remover no arquivo pessoa
                fseek(fdin, Offset, SEEK_SET);
                p.removido = '1';
                fwrite(&p.removido, sizeof(char), 1, fdin);

            //shift para remover da RAM
                int pos;
                for(int in = 0; in < 500; in++){
                    if(VetInd[in].Offset == i.Offset)
                    pos = in;
                }
                for (int j = pos; j < 500 -1; j++){
                        VetInd[j] = VetInd[j+1];
                }
                h.quantidadeRemovidos++;
            //escrever indice no disco
            //status inconsistente
                INICIO_ARQUIVO(fdh);
                hi.status = '0';
                fwrite(&hi.status, sizeof(char), 1, fdh);

                fseek(fdh, 12, SEEK_SET);
                for(int in = 0; in < 500; in++){
                    fwrite(&VetInd[in].idPessoa,sizeof(int),1,fdh);
                    fwrite(&VetInd[in].Offset,sizeof(long),1,fdh);
                }

            //status consistente
                INICIO_ARQUIVO(fdh);
                hi.status = '1';
                fwrite(&hi.status, sizeof(char), 1, fdh);

            //atualizar cabecalho
            //status inconsistente
                INICIO_ARQUIVO(fdin);
                h.status = '0';
                fwrite(&h.status, sizeof(char), 1, fdin);
                //campo quantidade removidos
                fseek(fdin, 5, SEEK_SET);
                fwrite(&h.quantidadeRemovidos, sizeof(int), 1, fdin);
                //status consistente
                INICIO_ARQUIVO(fdin);
                h.status = '1';
                fwrite(&h.status, sizeof(char), 1, fdin);


        }else{
            printf("Registro nao encontrado.\n");
        }

}

void swape(indice *a, indice *b) {
    indice temp = *a;
    *a = *b;
    *b = temp;
}

int partitione(indice *vetor, int low, int high) {
    indice pivot = vetor[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (vetor[j].idPessoa <= pivot.idPessoa) {
            i++;
            swape(&vetor[i], &vetor[j]);
        }
    }
    swape(&vetor[i + 1], &vetor[high]);
    return (i + 1);
}

void quicksort(indice *vetor, int low, int high) {
    if (low < high) {
        int pi = partitione(vetor, low, high);
        quicksort(vetor, low, pi - 1);
        quicksort(vetor, pi + 1, high);
    }
}

void inserirIndiceOrdenado(FILE *fdh, indice novo){
    if (fdh == NULL) return;
    fseek(fdh, 0, SEEK_END);
    long tamanhoArquivo = ftell(fdh);
    const long inicioRegistros = 12;
    int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));
    if (n == 0) {
        fseek(fdh, inicioRegistros, SEEK_SET);
        fwrite(&novo.idPessoa, sizeof(int), 1, fdh);
        fwrite(&novo.Offset, sizeof(long), 1, fdh);
        return;
    }
    int ini = 0, fim = n - 1, meio, pos = n;
    indice temp;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        fseek(fdh, inicioRegistros + meio * (sizeof(int) + sizeof(long)), SEEK_SET);
        fread(&temp.idPessoa, sizeof(int), 1, fdh);
        if (temp.idPessoa == novo.idPessoa) {
            pos = meio;
            break;
        } else if (temp.idPessoa > novo.idPessoa) {
            pos = meio;
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    if (ini > fim) pos = ini;
    size_t tamanhoRegistro = sizeof(int) + sizeof(long);
    long destino = inicioRegistros + pos * tamanhoRegistro;
    for (int i = n - 1; i >= pos; i--) {
        long posLeitura = inicioRegistros + i * tamanhoRegistro;
        fseek(fdh, posLeitura, SEEK_SET);
        indice temp2;
        fread(&temp2.idPessoa, sizeof(int), 1, fdh);
        fread(&temp2.Offset, sizeof(long), 1, fdh);
        fseek(fdh, posLeitura + tamanhoRegistro, SEEK_SET);
        fwrite(&temp2.idPessoa, sizeof(int), 1, fdh);
        fwrite(&temp2.Offset, sizeof(long), 1, fdh);
    }
    fseek(fdh, destino, SEEK_SET);
    fwrite(&novo.idPessoa, sizeof(int), 1, fdh);
    fwrite(&novo.Offset, sizeof(long), 1, fdh);
}

int comparar_datas(const char *data1, const char *data2) {
    if (!data1 || data1[0] == '\0' || data1[0] == '$') return 1;
    if (!data2 || data2[0] == '\0' || data2[0] == '$') return -1;

    // Comparar Ano
    int res = strncmp(data1 + 6, data2 + 6, 4);
    if (res != 0) return res;
    // Comparar M�s
    res = strncmp(data1 + 3, data2 + 3, 2);
    if (res != 0) return res;
    // Comparar Dia
    return strncmp(data1, data2, 2);
}

int comparar_vertices(const void *a, const void *b) {
    Vertice *v1 = (Vertice *)a;
    Vertice *v2 = (Vertice *)b;
    return strcmp(v1->nomeUsuario, v2->nomeUsuario);
}

void inserir_aresta_ordenada(Vertice *v, char *nomeSeguido, char *dataInicio, char *dataFim, char grau) {
    Aresta *nova = (Aresta *)malloc(sizeof(Aresta));
    strcpy(nova->nomeUsuario, nomeSeguido);

    // Copia e garante terminador nulo
    strncpy(nova->dataInicio, dataInicio, 10); nova->dataInicio[10] = '\0';
    if(dataFim[0] != '\0') {
        strncpy(nova->dataFim, dataFim, 10); nova->dataFim[10] = '\0';
    } else {
        nova->dataFim[0] = '\0';
    }

    nova->grauAmizade = grau;
    nova->prox = NULL;

    // Caso 1: Lista vazia ou inser��o no in�cio
    if (v->inicioLista == NULL) {
        v->inicioLista = nova;
        return;
    }

    // Compara com o primeiro
    int cmpNome = strcmp(nova->nomeUsuario, v->inicioLista->nomeUsuario);
    // Se nomes iguais, desempata por data
    int cmpData = comparar_datas(nova->dataInicio, v->inicioLista->dataInicio);

    if (cmpNome < 0 || (cmpNome == 0 && cmpData < 0)) {
        nova->prox = v->inicioLista;
        v->inicioLista = nova;
        return;
    }

    // Caso 2: Percorre a lista
    Aresta *atual = v->inicioLista;
    while (atual->prox != NULL) {
        cmpNome = strcmp(nova->nomeUsuario, atual->prox->nomeUsuario);
        cmpData = comparar_datas(nova->dataInicio, atual->prox->dataInicio);

        // Verifica se deve inserir antes do pr�ximo
        int cmpProxNome = strcmp(nova->nomeUsuario, atual->prox->nomeUsuario);
        int cmpProxData = comparar_datas(nova->dataInicio, atual->prox->dataInicio);

        if (cmpProxNome < 0 || (cmpProxNome == 0 && cmpProxData < 0)) {
            break;
        }
        atual = atual->prox;
    }

    nova->prox = atual->prox;
    atual->prox = nova;
}

void inserir_aresta_transposta(Vertice *v, char *nomeSeguido, char *dataInicio, char *dataFim, char grau) {
    Aresta *nova = (Aresta *)malloc(sizeof(Aresta));
    strcpy(nova->nomeUsuario, nomeSeguido);

    strncpy(nova->dataInicio, dataInicio, 10); nova->dataInicio[10] = '\0';
    if(dataFim[0] != '\0') {
        strncpy(nova->dataFim, dataFim, 10); nova->dataFim[10] = '\0';
    } else {
        nova->dataFim[0] = '\0';
    }
    nova->grauAmizade = grau;
    nova->prox = NULL;

    // Lista vazia ou inserir no in�cio
    if (v->inicioLista == NULL) {
        v->inicioLista = nova;
        return;
    }

    // Compara com o primeiro (crit�rio: NomeSeguidor asc, DataInicio asc)
    int cmpNome = strcmp(nova->nomeUsuario, v->inicioLista->nomeUsuario);
    int cmpData = comparar_datas(nova->dataInicio, v->inicioLista->dataInicio);

    if (cmpNome < 0 || (cmpNome == 0 && cmpData < 0)) {
        nova->prox = v->inicioLista;
        v->inicioLista = nova;
        return;
    }

    // Busca posi��o no meio/fim
    Aresta *atual = v->inicioLista;
    while (atual->prox != NULL) {
        cmpNome = strcmp(nova->nomeUsuario, atual->prox->nomeUsuario);
        cmpData = comparar_datas(nova->dataInicio, atual->prox->dataInicio);

        int cmpProxNome = strcmp(nova->nomeUsuario, atual->prox->nomeUsuario);
        int cmpProxData = comparar_datas(nova->dataInicio, atual->prox->dataInicio);

        if (cmpProxNome < 0 || (cmpProxNome == 0 && cmpProxData < 0)) {
            break;
        }
        atual = atual->prox;
    }

    nova->prox = atual->prox;
    atual->prox = nova;
}

void inicializar_fila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void enfileirar(Fila *f, int idx) {
    Node *novo = (Node*)malloc(sizeof(Node));
    novo->indiceVertice = idx;
    novo->prox = NULL;
    if (f->fim != NULL) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;
}

int desenfileirar(Fila *f) {
    if (f->inicio == NULL) return -1;
    Node *temp = f->inicio;
    int val = temp->indiceVertice;
    f->inicio = temp->prox;
    if (f->inicio == NULL) f->fim = NULL;
    free(temp);
    return val;
}

int fila_vazia(Fila *f) {
    return (f->inicio == NULL);
}



/* ---------------- EXTRA ----------------

OPCIONAL: dicas sobre scanf() e fscanf():

scanf("%[^,]", string) -> l� at� encontrar o caractere ',', n�o incluindo o mesmo na leitura.

Exemplo de entrada: "Oi, esse � um exemplo."
Nesse caso, o scanf("%[^,]") tem como resultado a string "Oi";

scanf("%[^\"]", string) -> l� at� encontrar o caractere '"', n�o incluindo o mesmo na leitura.
scanf("%[^\n]", string) -> l� at� encontrar o fim da linha, n�o incluindo o '\n' na leitura.

scanf("%*c") --> l� um char e n�o guarda em nenhuma vari�vel, como se tivesse ignorado ele

*/


