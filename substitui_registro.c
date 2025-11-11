//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"




void substitui_registro(FILE* fd, FILE* fdh,  pessoa p){

 int Ncampo;
 char NcampoString[100];
 char lixo = '$';
 header h;
 indice i;
 indice* ibusca;
 char *campo;
			
        scanf("%*c");
        scanf(" %[^=]", campo);//qual campo quer substituir
        scanf("%*c");
		

	h.Offset=ftell(fd);
	h.status='0';
	fseek(fd,0,SEEK_SET);
	fwrite(&h.status,sizeof(char),1,fd);
	fseek(fd,h.Offset,SEEK_SET);
	fseek(fd,-p.tamanhoRegistro,SEEK_CUR);

	if(strcmp(campo,"nomePessoa")==0){
		int tam, dif;
		scanf("%s",NcampoString);
		if(strcmp(NcampoString,"NULO")!=0){//confere se é nulo
            //tratando as aspas
            NcampoString[0]=NcampoString[1];
            for(int j=0;j<strlen(NcampoString);j++){
                if(NcampoString[j]=='\"'){
					NcampoString[j]=0;
					break;
				}
                else{NcampoString[j]=NcampoString[j+1];}
            } 
			tam = strlen(NcampoString);
		}
		else{tam=0;}
		if(p.removido='1'){return;}
		
        dif = p.tamanhoNomePessoa-tam;//calcula a difereença de tamanho

		if(dif>=0){//se cabe no registro
			fseek(fd,8,SEEK_CUR);
			fwrite(&tam,sizeof(int),1,fd);
			fwrite(NcampoString,sizeof(char),tam,fd);//escreve o novo campo
			fwrite(&p.tamanhoNomeUsuario,sizeof(int),1,fd);
			fwrite(p.nomeUsuario,sizeof(char),p.tamanhoNomeUsuario,fd);
            for(int k = 0; k < dif; k++) {//completa com lixo
              fwrite(&lixo, sizeof(char), 1, fd);
            }

			h.status='1';
			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
		}

		else if(dif<0){//se não cabe no registro
			p.removido='1';
			p.tamanhoNomePessoa = tam;
			strcpy(p.nomePessoa,NcampoString);//copia o novo nome para a struct
			p.tamanhoRegistro = 16 + p.tamanhoNomePessoa + p.tamanhoNomeUsuario;//calcula o tamanho do novo registro
            fseek(fd,-(sizeof(char)+sizeof(int)),SEEK_CUR);
			fwrite(&p.removido,sizeof(char),1,fd);//marca o registro como removido


			fseek(fd,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fd);
			fseek(fd, sizeof(int), SEEK_CUR);
			fread(&h.quantidadeRemovidos,sizeof(int),1,fd);
			fseek(fd,-sizeof(int),SEEK_CUR);
			h.quantidadeRemovidos++;
			fwrite(&h.quantidadeRemovidos,sizeof(int),1,fd);//aumenta o número de resolvidos 


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
			ibusca=vetor_ind(fdh);
			long offsetIndice = busca_binaria_indice(ibusca,h.quantidadePessoas,i.idPessoa);
            fseek(fdh,offsetIndice,SEEK_SET);
			fread(&i.idPessoa,sizeof(int),1,fdh);
			fwrite(&offset,sizeof(long),1,fdh);
			free(ibusca);

			h.status='1';
			fseek(fdh,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fdh);
			}


	}


	else if(strcmp(campo,"nomeUsuario")==0){
		int tam, dif;
		scanf("%s",NcampoString);
		if(strcmp(NcampoString,"NULO")!=0){
            //tratando as aspas
            NcampoString[0]=NcampoString[1];
            for(int j=0;j<strlen(NcampoString);j++){
                if(NcampoString[j]=='\"'){
					NcampoString[j]=0;
					break;
				}
                else{NcampoString[j]=NcampoString[j+1];}
            } 
			tam = strlen(NcampoString);
		}
		else{tam=0;}
		if(p.removido='1'){return;}
		dif = p.tamanhoNomeUsuario-tam;

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
			ibusca=vetor_ind(fdh);
			long offsetIndice = busca_binaria_indice(ibusca,h.quantidadePessoas,i.idPessoa);
            fseek(fdh,offsetIndice,SEEK_SET);
			fread(&i.idPessoa,sizeof(int),1,fdh);
			fwrite(&offset,sizeof(long),1,fdh);
			free(ibusca);

			h.status='1';
			fseek(fdh,0,SEEK_SET);
			fwrite(&h.status,sizeof(char),1,fdh);
			}
	}
	
	
	else if(strcmp(campo,"idPessoa")==0){
		
		
		scanf("%s",NcampoString);
    	if(strcmp(NcampoString,"NULO")==0){Ncampo= -1;}
        else{Ncampo=atoi(NcampoString);}
		if(p.removido='1'){return;}

		fwrite(&Ncampo,sizeof(int),1,fd);

		h.status='1';
		fseek(fd,0,SEEK_SET);
		fwrite(&h.status,sizeof(char),1,fd);

		fseek(fdh,0,SEEK_SET);
		h.status = '0';
		fwrite(&h.status,sizeof(char),1,fdh);
		fseek(fdh,TAMANHO_INDICE,SEEK_SET);
        i.idPessoa=p.idPessoa;
		ibusca=vetor_ind(fdh);
		i.Offset = busca_binaria_indice(ibusca,h.quantidadePessoas,i.idPessoa);
        fseek(fdh,i.Offset,SEEK_SET);
		fwrite(&Ncampo,sizeof(int),1,fdh);
        fseek(fdh,-sizeof(int),SEEK_CUR);
        fread(&i.idPessoa,sizeof(int),1,fdh);
        fread(&i.Offset,sizeof(long),1,fdh);
        inserirIndiceOrdenado(fdh,i);
		fseek(fdh,0,SEEK_SET);
		h.status='1';
		fwrite(&h.status,sizeof(char),1,fdh);
		free(ibusca);
		
	}
	
	
	else if(strcmp(campo,"idadePessoa")==0){

		
		scanf("%s",NcampoString);
    	if(strcmp(NcampoString,"NULO")==0){Ncampo= -1;}
        else{Ncampo=atoi(NcampoString);}
		if(p.removido='1'){return;}

		fseek(fd,4,SEEK_CUR);
        fwrite(&Ncampo,sizeof(int),1,fd);
			
            

		h.status='1';
		fseek(fd,0,SEEK_SET);
		fwrite(&h.status,sizeof(char),1,fd);
	}

}