//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"




void substitui_registro(FILE* fd, FILE* fdh,  pessoa p,char *campo){

 int Ncampo;
 char NcampoString[30];
 char lixo = '$';
 header h;
 indice i;
				

	h.Offset=ftell(fd);
	h.status='0';
	fseek(fd,0,SEEK_SET);
	fwrite(&h.status,sizeof(char),1,fd);
	fseek(fd,h.Offset,SEEK_SET);

	if(strcmp(campo,"nomePessoa")==0){
	
		scan_quote_string(NcampoString);
		int tam = strlen(NcampoString);
        int dif = p.tamanhoNomePessoa-tam;

		if(dif>=0){
			fseek(fd,8,SEEK_CUR);
			fwrite(&tam,sizeof(int),1,fd);
			fwrite(NcampoString,sizeof(char),tam,fd);
			fwrite(&p.tamanhoNomeUsuario,sizeof(int),1,fd);
			fwrite(p.nomeUsuario,sizeof(char),p.tamanhoNomeUsuario,fd);
            for(int k = 0; k < dif; k++) {
              fwrite(&lixo, sizeof(char), 1, fd);
            }

			h.status='1';
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
		}

		else if(dif<0){
			p.removido='1';
			p.tamanhoNomePessoa = tam;
			strcpy(p.nomePessoa,NcampoString);
			p.tamanhoRegistro = 16 + p.tamanhoNomePessoa + p.tamanhoNomeUsuario;
            fseek(fd,-(sizeof(char)+sizeof(int)),SEEK_CUR);
			fwrite(&p.removido,sizeof(char),1,fd);


			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
			fseek(fd, sizeof(int), SEEK_CUR);
			fread(&h.quantidadeRemovidos,sizeof(int),1,fd);
			fseek(fd,-sizeof(int),SEEK_CUR);
			h.quantidadeRemovidos++;
			fwrite(&h.quantidadeRemovidos,sizeof(int),1,fd);


			fseek(fd,0,SEEK_END);
			p.removido='0';
			fwrite(&p.removido, sizeof(char), 1, fd);
        	fwrite(&p.tamanhoRegistro, sizeof(int), 1, fd);
			h.Offset=ftell(fd);
			long offset = h.Offset;
        	fwrite(&p.idPessoa, sizeof(int), 1, fd);
        	fwrite(&p.idadePessoa, sizeof(int), 1, fd);
        	fwrite(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
        	fwrite(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
        	fwrite(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
			fwrite(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
			


			h.status='1';
			fseek(fd,0,SEEK_END);
			h.Offset=ftell(fd);
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
			fseek(fd, 2*sizeof(int), SEEK_CUR);
			fwrite(&h.Offset,sizeof(long),1,fd);

			fseek(fdh,0,SEEK_SET);
			h.status='0';
			fwrite(&h.status,sizeof(char),1,fdh);
            i.idPessoa=p.idPessoa;
			long offsetIndice = busca_ind(fdh,i);
            fseek(fdh,offsetIndice,SEEK_SET);
			fread(&i.idPessoa,sizeof(int),1,fdh);
			fwrite(&offset,sizeof(long),1,fdh);

			h.status='1';
			fseek(fdh,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fdh);
			}


	}


	else if(strcmp(campo,"nomeUsuario")==0){
		scan_quote_string(NcampoString);
		int tam = strlen(NcampoString);
        int dif = p.tamanhoNomeUsuario-tam;

		if(dif>=0){
			fseek(fd,12+p.tamanhoNomePessoa,SEEK_CUR);
			fwrite(&tam,sizeof(int),1,fd);
			fwrite(NcampoString,sizeof(char),tam,fd);
			for(int k = 0; k < dif; k++) {
                fwrite(&lixo, sizeof(char), 1, fd);
            }

			h.status='1';
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
		}

		else if(dif<0){
			p.removido='1';
			p.tamanhoNomeUsuario = tam;
			strcpy(p.nomeUsuario,NcampoString);
			p.tamanhoRegistro = 16 + p.tamanhoNomePessoa + p.tamanhoNomeUsuario;
            fseek(fd,-(sizeof(int)+sizeof(char)),SEEK_CUR);
			fwrite(&p.removido,sizeof(char),1,fd);

			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
			fseek(fd, sizeof(int), SEEK_CUR);
			fread(&h.quantidadeRemovidos,sizeof(int),1,fd);
			fseek(fd,-sizeof(int),SEEK_CUR);
			h.quantidadeRemovidos++;
			fwrite(&h.quantidadeRemovidos,sizeof(int),1,fd);



			fseek(fd,0,SEEK_END);
			p.removido='0';
			fwrite(&p.removido, sizeof(char), 1, fd);
        	fwrite(&p.tamanhoRegistro, sizeof(int), 1, fd);
			h.Offset=ftell(fd);
			long offset = h.Offset;
        	fwrite(&p.idPessoa, sizeof(int), 1, fd);
        	fwrite(&p.idadePessoa, sizeof(int), 1, fd);
        	fwrite(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
        	fwrite(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
        	fwrite(&p.tamanhoNomeUsuario, sizeof(int), 1, fd);
			fwrite(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);

			h.status='1';
			fseek(fd,0,SEEK_END);
			h.Offset=ftell(fd);
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
			fseek(fd, 2*sizeof(int), SEEK_CUR);
			fwrite(&h.Offset,sizeof(long),1,fd);

			fseek(fdh,0,SEEK_SET);
			h.status='0';
			fwrite(&h.status,sizeof(char),1,fdh);
            i.idPessoa=p.idPessoa;
			long offsetIndice = busca_ind(fdh,i);
            fseek(fdh,offsetIndice,SEEK_SET);
			fread(&i.idPessoa,sizeof(int),1,fdh);
			fwrite(&offset,sizeof(long),1,fdh);

			h.status='1';
			fseek(fdh,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fdh);
			}
	}
	
	
	else if(strcmp(campo,"idPessoa")==0){
		scanf("%d",&Ncampo);

			fwrite(&Ncampo,sizeof(int),1,fd);

		h.status='1';
		fseek(fd,0,SEEK_SET);
		fwrite(&h.status,sizeof(char),1,fd);

		fseek(fdh,0,SEEK_SET);
		h.status = '0';
		fwrite(&h.status,sizeof(char),1,fdh);
		fseek(fdh,TAMANHO_INDICE,SEEK_SET);
        i.idPessoa=p.idPessoa;
		i.Offset = busca_ind(fdh,i);
        fseek(fdh,i.Offset,SEEK_SET);
		fwrite(&Ncampo,sizeof(int),1,fdh);
        fseek(fdh,-sizeof(int),SEEK_CUR);
        fread(&i.idPessoa,sizeof(int),1,fdh);
        fread(&i.Offset,sizeof(long),1,fdh);
        inserirIndiceOrdenado(fdh,i);
		fseek(fdh,0,SEEK_SET);
		h.status='1';
		fwrite(&h.status,sizeof(char),1,fdh);
		
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