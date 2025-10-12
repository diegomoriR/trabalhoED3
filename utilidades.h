#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header_pessoa.h"

/*
Função para imprimir dados salvos no arquivo em binário
(util para comparar saida no run codes)
*/
void binarioNaTela(char *nomeArquivoBinario) {

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
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
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
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

void inserirIndiceOrdenado(FILE *fdh, indice novo){
    if (fdh == NULL) return;
    fseek(fdh, 0, SEEK_END);
    long tamanhoArquivo = ftell(fdh);
    const long inicioRegistros = 13;
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
    long origem = inicioRegistros + pos * tamanhoRegistro;
    long destino = origem + tamanhoRegistro;
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
    fseek(fdh, origem, SEEK_SET);
    fwrite(&novo.idPessoa, sizeof(int), 1, fdh);
    fwrite(&novo.Offset, sizeof(long), 1, fdh);
}

/* ---------------- EXTRA ----------------

OPCIONAL: dicas sobre scanf() e fscanf():

scanf("%[^,]", string) -> lê até encontrar o caractere ',', não incluindo o mesmo na leitura.

Exemplo de entrada: "Oi, esse é um exemplo."
Nesse caso, o scanf("%[^,]") tem como resultado a string "Oi";

scanf("%[^\"]", string) -> lê até encontrar o caractere '"', não incluindo o mesmo na leitura.
scanf("%[^\n]", string) -> lê até encontrar o fim da linha, não incluindo o '\n' na leitura.

scanf("%*c") --> lê um char e não guarda em nenhuma variável, como se tivesse ignorado ele

*/

