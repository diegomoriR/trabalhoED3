//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"




void substitui_registro(FILE* fd, FILE* fdh,  pessoa p, long offsetP){

 int Ncampo;
 char NcampoString[100];
 char lixo = '$';
 header h;
 indice i;

 char campo[15];
			
        scanf("%*c");
        scanf(" %[^=]", campo);//qual campo quer substituir
        scanf("%*c");
		


	h.status='0';
	fseek(fd,0,SEEK_SET);
	fwrite(&h.status,sizeof(char),1,fd);
	fseek(fd,offsetP,SEEK_SET);

	if(strcmp(campo,"nomePessoa")==0){
		
		int tam, dif;
		scanf("%s",NcampoString);
		memmove(&NcampoString[0], &NcampoString[1], strlen(NcampoString)); // "NOVO\""
		// Remove a última aspa (colocando um '\0')
		NcampoString[strlen(NcampoString) - 1] = '\0';
		tam = strlen(NcampoString);
		if(strcmp(NcampoString,"NULO")==0){tam=0;}
		if(p.removido=='1'){return;}

		
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
			free(p.nomePessoa); // Libere a memória antiga
    		p.nomePessoa = strdup(NcampoString); // Aloque nova memória e copie
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

			fseek(fdh, 0, SEEK_END);
        long tamanhoArquivo = ftell(fdh);//pega o tamanho do arquivo
        const long inicioRegistros = 12;
        int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));//calcula o número de registros
        indice* ibusca = (indice *)malloc(n * sizeof(indice));
        headerIndice hi;
        fseek(fdh, 0, SEEK_SET);
        fread(&hi.status,sizeof(char),1,fdh);
        fseek(fdh, inicioRegistros ,SEEK_SET);
        for(int i=0;i<n;i++){//copia os indices para o vetor
            fread(&ibusca[i].idPessoa,sizeof(int),1,fdh);
            
            fread(&ibusca[i].Offset,sizeof(long),1,fdh);
        }

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
		memmove(&NcampoString[0], &NcampoString[1], strlen(NcampoString)); // "NOVO\""
		// Remove a última aspa (colocando um '\0')
		NcampoString[strlen(NcampoString) - 1] = '\0';
		tam = strlen(NcampoString);
		if(strcmp(NcampoString,"NULO")==0){tam=0;}
		if(p.removido=='1'){return;}
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
			free(p.nomeUsuario); // Libere a memória antiga
    		p.nomeUsuario = strdup(NcampoString); // Aloque nova memória e copie
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
			        
			fseek(fdh, 0, SEEK_END);
        long tamanhoArquivo = ftell(fdh);//pega o tamanho do arquivo
        const long inicioRegistros = 12;
        int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));//calcula o número de registros
        indice* ibusca = (indice *)malloc(n * sizeof(indice));
        headerIndice hi;
        fseek(fdh, 0, SEEK_SET);
        fread(&hi.status,sizeof(char),1,fdh);
        fseek(fdh, inicioRegistros ,SEEK_SET);
        for(int i=0;i<n;i++){//copia os indices para o vetor
            fread(&ibusca[i].idPessoa,sizeof(int),1,fdh);
            fread(&ibusca[i].Offset,sizeof(long),1,fdh);
        }

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
		if(p.removido=='1'){return;}

		fwrite(&Ncampo,sizeof(int),1,fd);

		h.status='1';
		fseek(fd,0,SEEK_SET);
		fwrite(&h.status,sizeof(char),1,fd);

		fseek(fdh,0,SEEK_SET);
		h.status = '0';
		fwrite(&h.status,sizeof(char),1,fdh);
		fseek(fdh,TAMANHO_INDICE,SEEK_SET);
        i.idPessoa=p.idPessoa;
		        
		fseek(fdh, 0, SEEK_END);
        long tamanhoArquivo = ftell(fdh);//pega o tamanho do arquivo
        const long inicioRegistros = 12;
        int n = (tamanhoArquivo - inicioRegistros) / (sizeof(int) + sizeof(long));//calcula o número de registros
        indice* ibusca = (indice *)malloc(n * sizeof(indice));
        headerIndice hi;
        fseek(fdh, 0, SEEK_SET);
        fread(&hi.status,sizeof(char),1,fdh);
        fseek(fdh, inicioRegistros ,SEEK_SET);
        for(int i=0;i<n;i++){//copia os indices para o vetor
            fread(&ibusca[i].idPessoa,sizeof(int),1,fdh);
            fread(&ibusca[i].Offset,sizeof(long),1,fdh);
        }

		
		i.Offset = busca_binaria_indice(ibusca,h.quantidadePessoas,i.idPessoa);
		int posVet = busca_binaria_indice_atualiza(ibusca,h.quantidadePessoas,i.idPessoa);
        fseek(fdh,i.Offset,SEEK_SET);
		fwrite(&Ncampo,sizeof(int),1,fdh);
		for (int j = posVet; j < NUMERO_PESSOAS -1; j++){
            ibusca[j] = ibusca[j+1];
        }
		INICIO_ARQUIVO(fdh);
        hi.status = '0';
        fwrite(&hi.status, sizeof(char), 1, fdh);
        fseek(fdh, 12, SEEK_SET);
        fwrite(ibusca, sizeof(indice), NUMERO_PESSOAS, fdh);
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
		if(p.removido=='1'){return;}

		fread(&p.idPessoa, sizeof(int), 1, fd);
        fwrite(&Ncampo,sizeof(int),1,fd); 
		

	h.status='1';
	fseek(fd,0,SEEK_SET);
	fwrite(&h.status,sizeof(char),1,fd);
	}

}