// Lucas Soares Leite Santos - 15472162
// Diego Mori Rodrigues - 13782421

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"

void substitui_registro(FILE *fd, FILE *fdh, pessoa p, long offsetP, indice* VetInd)
{

	int Ncampo;
	char NcampoString[100];
	char lixo = '$';
	header h;
	indice i;

	char campo[15];

	scanf("%*c");
	scanf(" %[^=]", campo); // qual campo quer substituir
	scanf("%*c");

	h.status = '0';
	fseek(fd, 0, SEEK_SET);
	fwrite(&h.status, sizeof(char), 1, fd);
	fread(&h.quantidadePessoas, sizeof(char), 1, fd);
	fread(&h.quantidadeRemovidos, sizeof(char), 1, fd);
	fseek(fd, offsetP, SEEK_SET);

	if (strcmp(campo, "nomePessoa") == 0)
	{

		int tam, dif;
		fgets(NcampoString,100,stdin);
		if (strcmp(NcampoString, "NULO") == 0)
		{
			tam = 0;
		}
		else
		{
			memmove(&NcampoString[0], &NcampoString[1], strlen(NcampoString)); // "NOVO\""
			// Remove a última aspa (colocando um '\0')
			NcampoString[strlen(NcampoString) - 1] = '\0';
			NcampoString[strlen(NcampoString) - 1] = '\0';
			tam = strlen(NcampoString);
		}

		if (p.removido == '1')
		{
			return;
		}

		dif = p.tamanhoNomePessoa - tam; // calcula a difereença de tamanho

		if (dif >= 0)
		{ // se cabe no registro
			fseek(fd, 8, SEEK_CUR);
			fwrite(&tam, sizeof(int), 1, fd);
			fwrite(NcampoString, sizeof(char), tam, fd); // escreve o novo campo
			fwrite(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
			fwrite(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
			for (int k = 0; k < dif; k++)
			{ // completa com lixo
				fwrite(&lixo, sizeof(char), 1, fd);
			}

			h.status = '1';
			fseek(fd, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fd);
		}

		else if (dif < 0)
		{ // se não cabe no registro
			p.removido = '1';
			p.tamanhoNomePessoa = tam;
			p.tamanhoRegistro = 16 + p.tamanhoNomePessoa + p.tamanhoNomeUsuario; // calcula o tamanho do novo registro
			fseek(fd, -(sizeof(char) + sizeof(int)), SEEK_CUR);
			fwrite(&p.removido, sizeof(char), 1, fd); // marca o registro como removido

			fseek(fd, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fd);
			fseek(fd, sizeof(int), SEEK_CUR);
			fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
			fseek(fd, -sizeof(int), SEEK_CUR);
			h.quantidadeRemovidos++;
			fwrite(&h.quantidadeRemovidos, sizeof(int), 1, fd); // aumenta o número de resolvidos

			fseek(fd, 0, SEEK_END);
			p.removido = '0';
			fwrite(&p.removido, sizeof(char), 1, fd);
			fwrite(&p.tamanhoRegistro, sizeof(int), 1, fd);
			h.Offset = ftell(fd);
			long offset = h.Offset;
			fwrite(&p.idPessoa, sizeof(int), 1, fd);
			fwrite(&p.idadePessoa, sizeof(int), 1, fd);
			fwrite(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
			fwrite(NcampoString, sizeof(char), p.tamanhoNomePessoa, fd);
			fwrite(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
			fwrite(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);

			h.status = '1';
			fseek(fd, 0, SEEK_END);
			h.Offset = ftell(fd);
			fseek(fd, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fd);
			fseek(fd, 2 * sizeof(int), SEEK_CUR);
			fwrite(&h.Offset, sizeof(long), 1, fd);

			fseek(fdh, 0, SEEK_SET);
			h.status = '0';
			fwrite(&h.status, sizeof(char), 1, fdh);
			i.idPessoa = p.idPessoa;

			long offsetIndice = busca_binaria_indice(VetInd, h.quantidadePessoas, i.idPessoa);
			fseek(fdh, offsetIndice, SEEK_SET);
			fread(&i.idPessoa, sizeof(int), 1, fdh);
			fwrite(&offset, sizeof(long), 1, fdh);
			

			h.status = '1';
			fseek(fdh, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fdh);
		}

		fseek(fd,offsetP + p.tamanhoRegistro, SEEK_SET);
		fflush(fd);
		fflush(fdh);
	}

	else if (strcmp(campo, "nomeUsuario") == 0)
	{
		int tam, dif;
		fgets(NcampoString, 100, stdin);
		if (strcmp(NcampoString, "NULO") == 0)
		{
			tam = 0;
		}
		else
		{
			memmove(&NcampoString[0], &NcampoString[1], strlen(NcampoString)); // "NOVO\"\n"
			// Remove a última aspa (colocando um '\0')
			NcampoString[strlen(NcampoString) - 1] = '\0';
			NcampoString[strlen(NcampoString) - 1] = '\0';
			tam = strlen(NcampoString);
		}
		if (p.removido == '1')
		{
			return;
		}
		dif = p.tamanhoNomeUsuario - tam;

		if (dif >= 0)
		{
			fseek(fd, 12 + p.tamanhoNomePessoa, SEEK_CUR);
			fwrite(&tam, sizeof(int), 1, fd);
			fwrite(NcampoString, sizeof(char), tam, fd);
			for (int k = 0; k < dif; k++)
			{
				fwrite(&lixo, sizeof(char), 1, fd);
			}

			h.status = '1';
			fseek(fd, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fd);
		}

		else if (dif < 0)
		{
			p.removido = '1';
			p.tamanhoNomeUsuario = tam;
			p.tamanhoRegistro = 16 + p.tamanhoNomePessoa + p.tamanhoNomeUsuario;
			fseek(fd, -(sizeof(int) + sizeof(char)), SEEK_CUR);
			fwrite(&p.removido, sizeof(char), 1, fd);

			fseek(fd, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fd);
			fseek(fd, sizeof(int), SEEK_CUR);
			fread(&h.quantidadeRemovidos, sizeof(int), 1, fd);
			fseek(fd, -sizeof(int), SEEK_CUR);
			h.quantidadeRemovidos++;
			fwrite(&h.quantidadeRemovidos, sizeof(int), 1, fd);

			fseek(fd, 0, SEEK_END);
			p.removido = '0';
			fwrite(&p.removido, sizeof(char), 1, fd);
			fwrite(&p.tamanhoRegistro, sizeof(int), 1, fd);
			h.Offset = ftell(fd);
			long offset = h.Offset;
			fwrite(&p.idPessoa, sizeof(int), 1, fd);
			fwrite(&p.idadePessoa, sizeof(int), 1, fd);
			fwrite(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
			fwrite(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
			fwrite(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
			fwrite(NcampoString, sizeof(char), p.tamanhoNomeUsuario, fd);

			h.status = '1';
			fseek(fd, 0, SEEK_END);
			h.Offset = ftell(fd);
			fseek(fd, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fd);
			fseek(fd, 2 * sizeof(int), SEEK_CUR);
			fwrite(&h.Offset, sizeof(long), 1, fd);

			fseek(fdh, 0, SEEK_SET);
			h.status = '0';
			fwrite(&h.status, sizeof(char), 1, fdh);
			i.idPessoa = p.idPessoa;

			long offsetIndice = busca_binaria_indice(VetInd, h.quantidadePessoas, i.idPessoa);
			fseek(fdh, offsetIndice, SEEK_SET);
			fread(&i.idPessoa, sizeof(int), 1, fdh);
			fwrite(&offset, sizeof(long), 1, fdh);

			h.status = '1';
			fseek(fdh, 0, SEEK_SET);
			fwrite(&h.status, sizeof(char), 1, fdh);
		}

		fseek(fd, offsetP + p.tamanhoRegistro, SEEK_SET);
		fflush(fd);
		fflush(fdh);
	}

	else if (strcmp(campo, "idPessoa") == 0)
	{

		scanf("%s", NcampoString);
		if (strcmp(NcampoString, "NULO") == 0)
		{
			Ncampo = -1;
		}
		else
		{
			Ncampo = atoi(NcampoString);
		}
		if (p.removido == '1')
		{
			return;
		}

		fwrite(&Ncampo, sizeof(int), 1, fd);

		h.status = '1';
		fseek(fd, 0, SEEK_SET);
		fwrite(&h.status, sizeof(char), 1, fd);

		fseek(fdh, 0, SEEK_SET);
		h.status = '0';
		fwrite(&h.status, sizeof(char), 1, fdh);
		i.idPessoa = p.idPessoa;

		fseek(fdh, 0, SEEK_END);
		header hi;
		int posVet = busca_binaria_indice_atualiza(VetInd, h.quantidadePessoas, i.idPessoa);
		VetInd[posVet].idPessoa = Ncampo;
		qsort(VetInd, h.quantidadePessoas, sizeof(indice), compara_indice);
		INICIO_ARQUIVO(fdh);
		hi.status = '0';
		fwrite(&hi.status, sizeof(char), 1, fdh);
		fseek(fdh, TAMANHO_HEADER_INDICE, SEEK_SET);
		fwrite(VetInd, sizeof(indice), h.quantidadePessoas, fdh);
		fseek(fdh, 0, SEEK_SET);
		h.status = '1';
		fwrite(&h.status, sizeof(char), 1, fdh);
		fseek(fd, offsetP + p.tamanhoRegistro, SEEK_SET);
		fflush(fd);
		fflush(fdh);
	}

	else if (strcmp(campo, "idadePessoa") == 0)
	{

		scanf("%s", NcampoString);

		if (strcmp(NcampoString, "NULO") == 0)
		{
			Ncampo = -1;
		}
		else
		{
			Ncampo = atoi(NcampoString);
		}
		if (p.removido == '1')
		{
			return;
		}

		fseek(fd,sizeof(int),SEEK_CUR);
		fwrite(&Ncampo, sizeof(int), 1, fd);

		h.status = '1';
		fseek(fd, 0, SEEK_SET);
		fwrite(&h.status, sizeof(char), 1, fd);
		fseek(fd, offsetP + p.tamanhoRegistro, SEEK_SET);
		fflush(fd);
		fflush(fdh);
	}
}