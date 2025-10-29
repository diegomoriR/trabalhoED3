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
/* ---------------- EXTRA ----------------

OPCIONAL: dicas sobre scanf() e fscanf():

scanf("%[^,]", string) -> lê até encontrar o caractere ',', não incluindo o mesmo na leitura.

Exemplo de entrada: "Oi, esse é um exemplo."
Nesse caso, o scanf("%[^,]") tem como resultado a string "Oi";

scanf("%[^\"]", string) -> lê até encontrar o caractere '"', não incluindo o mesmo na leitura.
scanf("%[^\n]", string) -> lê até encontrar o fim da linha, não incluindo o '\n' na leitura.

scanf("%*c") --> lê um char e não guarda em nenhuma variável, como se tivesse ignorado ele

*/

char* strsep(char** stringp, const char* delim) {
    if (stringp == NULL || *stringp == NULL) {
        return NULL;
    }
    
    char* start = *stringp;
    char* p = strpbrk(start, delim); // Encontra o primeiro delimitador

    if (p == NULL) {
        // Nenhum delimitador encontrado, este é o último token
        *stringp = NULL;
    } else {
        // Delimitador encontrado
        *p = '\0';             // Substitui o delimitador por nulo
        *stringp = p + 1;      // Avança o ponteiro principal para depois do nulo
    }

    return start;
}

void print_registro(pessoa p){

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

}

void substitui_registro(FILE* fd, FILE* fdh,  pessoa p,char campo){

 int Ncampo;
 char NcampoString[30];
 char lixo = '$';
 header h;
 indice i;

	fseek(fd, -p.tamanhoRegistro, SEEK_CUR);
	h.Offset=ftell(fd);
	fseek(fd,0,SEEK_SET);
	fwrite('0',sizeof(char),1,fd);
	fseek(fd,h.Offset,SEEK_SET);

	if(strcmp(campo,"nomePessoa")==0){
	
		scan_quote_string(NcampoString);

		if(p.tamanhoNomePessoa>=strlen(NcampoString)){
			fseek(fd,8,SEEK_CUR);
			fwrite(strlen(NcampoString),sizeof(int),1,fd);
			fwrite(NcampoString,sizeof(char),strlen(NcampoString),fd);
			fwrite(lixo,sizeof(char),p.tamanhoNomePessoa-strlen(Ncampo),fd);

			h.status='1';
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
		}

		else{
			p.tamanhoNomePessoa = strlen(NcampoString);
			strcpy(p.nomePessoa,NcampoString);
			p.tamanhoRegistro = 16 + p.tamanhoNomePessoa + p.tamanhoNomeUsuario;
			fwrite('1',sizeof(char),1,fd);

			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
			fread(&h.quantidadePessoas,sizeof(int),1,fd);
			fread(&h.quantidadeRemovidos,sizeof(int),1,fd);
			fseek(fd,-4,SEEK_CUR);
			h.quantidadeRemovidos++;
			fwrite(&h.quantidadeRemovidos,sizeof(int),1,fd);
			fwrite(&h.Offset,sizeof(long),1,fd);


			fseek(fd,0,SEEK_END);
			h.Offset=ftell(fd);
			fwrite(&p.removido, sizeof(char), 1, fd);
        	fwrite(&p.tamanhoRegistro, sizeof(int), 1, fd);
        	fwrite(&p.idPessoa, sizeof(int), 1, fd);
        	fwrite(&p.idadePessoa, sizeof(int), 1, fd);
        	fwrite(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
        	fwrite(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
        	fwrite(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
			fwrite(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);

			h.status='1';
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);

			fseek(fdh,0,SEEK_SET);
			fwrite('0',sizeof(char),1,fdh);
			fseek(fdh,TAMANHO_INDICE,SEEK_SET);
			fread(&i.idPessoa,sizeof(int),1,fdh);
			fread(&i.Offset,sizeof(long),1,fdh);
			while(p.idPessoa>=i.idPessoa){
				if(p.idPessoa==i.idPessoa){
					fseek(fdh,-sizeof(long),SEEK_CUR);
					fwrite(&h.Offset,sizeof(long),1,fdh);
					break;
				}
				else{
					fread(&i.idPessoa,sizeof(int),1,fdh);
					fread(&i.Offset,sizeof(long),1,fdh);
				}
			}
			fseek(fdh,0,SEEK_SET);
			fwrite('1',sizeof(char),1,fdh);
			}
	}


	else if(strcmp(campo,"nomeUsuario")==0){
		scan_quote_string(NcampoString);

		if(p.tamanhoNomePessoa>=strlen(NcampoString)){
			fseek(fd,12+p.tamanhoNomePessoa,SEEK_CUR);
			fwrite(strlen(NcampoString),sizeof(int),1,fd);
			fwrite(NcampoString,sizeof(char),strlen(NcampoString),fd);
			fwrite(lixo,sizeof(char),p.tamanhoNomePessoa-strlen(Ncampo),fd);

			h.status='1';
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
		}

		else{
			p.tamanhoNomeUsuario = strlen(NcampoString);
			strcpy(p.nomeUsuario,NcampoString);
			p.tamanhoRegistro = 16 + p.tamanhoNomePessoa + p.tamanhoNomeUsuario;
			fwrite('1',sizeof(char),1,fd);

			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
			fread(&h.quantidadePessoas,sizeof(int),1,fd);
			fread(&h.quantidadeRemovidos,sizeof(int),1,fd);
			fseek(fd,-4,SEEK_CUR);
			h.quantidadeRemovidos++;
			fwrite(&h.quantidadeRemovidos,sizeof(int),1,fd);
			fwrite(&h.Offset,sizeof(long),1,fd);

			fseek(fd,0,SEEK_END);
			h.Offset=ftell(fd);
			fwrite(&p.removido, sizeof(char), 1, fd);
        	fwrite(&p.tamanhoRegistro, sizeof(int), 1, fd);
        	fwrite(&p.idPessoa, sizeof(int), 1, fd);
        	fwrite(&p.idadePessoa, sizeof(int), 1, fd);
        	fwrite(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
        	fwrite(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
        	fwrite(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
			fwrite(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);

			h.status='1';
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);

			fseek(fdh,0,SEEK_SET);
			fwrite('0',sizeof(char),1,fdh);
			fseek(fdh,TAMANHO_INDICE,SEEK_SET);
			fread(&i.idPessoa,sizeof(int),1,fdh);
			fread(&i.Offset,sizeof(long),1,fdh);
			while(p.idPessoa>=i.idPessoa){
				if(p.idPessoa==i.idPessoa){
					fseek(fdh,-sizeof(long),SEEK_CUR);
					fwrite(&h.Offset,sizeof(long),1,fdh);
					break;
				}
				else{
					fread(&i.idPessoa,sizeof(int),1,fdh);
					fread(&i.Offset,sizeof(long),1,fdh);
				}
			}
			fseek(fdh,0,SEEK_SET);
			fwrite('1',sizeof(char),1,fdh);
			}
	}
	
	
	else if(strcmp(campo,"idPessoa")==0){
		scanf("%d",&Ncampo);

			fwrite(&Ncampo,sizeof(int),1,fd);

		h.status='1';
		fseek(fd,0,SEEK_SET);
		fwrite(&h.status,sizeof(char),1,fd);

		fseek(fdh,0,SEEK_SET);
		fwrite('0',sizeof(char),1,fdh);
		fseek(fdh,TAMANHO_INDICE,SEEK_SET);
		fread(&i.idPessoa,sizeof(int),1,fdh);
		fread(&i.Offset,sizeof(long),1,fdh);
		while(p.idPessoa>=i.idPessoa){
			if(p.idPessoa==i.idPessoa){
				fseek(fdh,-TAMANHO_INDICE,SEEK_CUR);
				fwrite(&Ncampo,sizeof(int),1,fdh);
				break;
			}
			else{
				fread(&i.idPessoa,sizeof(int),1,fdh);
				fread(&i.Offset,sizeof(long),1,fdh);
			}
		}
		fseek(fdh,0,SEEK_SET);
		fwrite('1',sizeof(char),1,fdh);
		
	}
	else if(strcmp(campo,"idadePessoa")==0){

		scanf("%d",&Ncampo);

			fseek(fd,4,SEEK_CUR);
			fwrite(&Ncampo,sizeof(int),1,fd);

		h.status='1';
		fseek(fd,0,SEEK_SET);
		fwrite(&h.status,sizeof(char),1,fd);
	}

}

int comparaSegue(const void *a, const void *b) {
    // Converte os ponteiros genéricos (void*) de volta para o nosso tipo (segue*)
    const segue *regA = (const segue *)a;
    const segue *regB = (const segue *)b;


    // CRITÉRIO 1: idPessoaQueSegue (crescente) 
    int a_idSegueNulo = (regA->idPessoaQueSegue == -1);
    int b_idSegueNulo = (regB->idPessoaQueSegue == -1);

    if (a_idSegueNulo != b_idSegueNulo) {
        // Se um é nulo e o outro não, o não-nulo (0) vem antes do nulo (1).
        return a_idSegueNulo - b_idSegueNulo; // (0 - 1 = -1) ou (1 - 0 = 1)
    }
    if (regA->idPessoaQueSegue != regB->idPessoaQueSegue) {
        // Ambos não-nulos e diferentes, ordena crescentemente
        if(regA->idPessoaQueSegue < regB->idPessoaQueSegue){return -1;}
		else {return 1;}
    }

    // CRITÉRIO 2: idPessoaQueESeguida (crescente)
    int a_idSeguidaNulo = (regA->idPessoaQueESeguida == -1);
    int b_idSeguidaNulo = (regB->idPessoaQueESeguida == -1);

    if (a_idSeguidaNulo != b_idSeguidaNulo) {
        return a_idSeguidaNulo - b_idSeguidaNulo; // não-nulo (0) antes de nulo (1)
    }
    if (regA->idPessoaQueSegue != regB->idPessoaQueSegue) {
        // Ambos não-nulos e diferentes, ordena crescentemente
        if(regA->idPessoaQueSegue < regB->idPessoaQueSegue){return -1;}
		else {return 1;}
    }

    // CRITÉRIO 3: dataInicioQueSegue (crescente)
    int a_inicioNulo = (regA->dataInicioQueSegue[0] == '$');
    int b_inicioNulo = (regB->dataInicioQueSegue[0] == '$');

    if (a_inicioNulo != b_inicioNulo) {
        return a_inicioNulo - b_inicioNulo; // não-nulo (0) antes de nulo (1)
    }
    else{ 
        int cmp_inicio = memcmp(regA->dataInicioQueSegue, regB->dataInicioQueSegue, 10);
        if (cmp_inicio != 0) {
            return cmp_inicio;
        }
    }

    // CRITÉRIO 4: dataFimQueSegue (crescente)
    int a_fimNulo = (regA->dataFimQueSegue[0] == '\0');
    int b_fimNulo = (regB->dataFimQueSegue[0] == '\0');

    if (a_fimNulo != b_fimNulo) {
        return a_fimNulo - b_fimNulo; // não-nulo (0) antes de nulo (1)
    }
    else{ // Só compara se ambos não forem nulos
        int cmp_fim = memcmp(regA->dataFimQueSegue, regB->dataFimQueSegue, 10);
        if (cmp_fim != 0) {
            return cmp_fim;
        }
    }

    // EMPATE TOTAL
    return 0;
}