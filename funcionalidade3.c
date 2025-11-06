//Lucas Soares Leite Santos - 15472162
//Diego Mori Rodrigues - 13782421


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_pessoa.h"


//funcionalidade 3 (SELECT)
void SELECT(char *arquivoSaida){

    FILE *fd = fopen(arquivoSaida, "rb"); //abrindo o arquivo de dados pessoa para a leitura binaria
    if(fd == NULL){
        printf("Falha no processamento do arquivo.\n");// verificando se o arquivo foi aberto corretamente
        return;
    }

    header h;
    fseek(fd, 1, SEEK_SET); // cursor para o inicio do registro de cabecalho
    fread(&h.quantidadePessoas, sizeof(int), 1, fd);
    //printf("qtdep:%d\n",h.quantidadePessoas);
    fread(&h.quantidadeRemovidos,sizeof(int), 1, fd);
    //printf("qtder:%d\n",h.quantidadeRemovidos);
    fread(&h.Offset,sizeof(long), 1, fd);
    //printf("offset:%ld\n",h.Offset);
    int qtdePessoas = h.quantidadePessoas;
    int qtdeRemovidos = h.quantidadeRemovidos;
    char lixo;
    


    //ler todos os dados das pessoas
    pessoa p;
    //removido -> tamanho registro -> idPessoa -> idadePessoa -> tamanho nomePessoa -> nomePessoa -> tamanho nomeUsuario -> nomeUsuario
    
    fread(&p.removido,sizeof(char), 1, fd);
    for(int i = 0; i <qtdePessoas+qtdeRemovidos; i++){
        fread(&p.tamanhoRegistro, sizeof(int), 1, fd);
        
        fread(&p.idPessoa, sizeof(int), 1, fd);
        fread(&p.idadePessoa, sizeof(int), 1, fd);
        fread(&p.tamanhoNomePessoa, sizeof(int), 1, fd);
        p.nomePessoa = (char *) malloc(p.tamanhoNomePessoa + 1);
        fread(p.nomePessoa, sizeof(char), p.tamanhoNomePessoa, fd);
        p.nomePessoa[p.tamanhoNomePessoa] = 0;
        fread(&p.tamanhoNomeUsuario,sizeof(int), 1, fd);
        p.nomeUsuario = (char *) malloc(p.tamanhoNomeUsuario+1);
        fread(p.nomeUsuario, sizeof(char), p.tamanhoNomeUsuario, fd);
        p.nomeUsuario[p.tamanhoNomeUsuario] = 0;
        fread(&lixo,sizeof(char),1,fd);
        if(lixo=='$'){
            while(lixo!='1' || lixo!='0'){
                fread(&lixo,sizeof(char),1,fd);
                if(lixo!='$'){break;}
            }
        }

        if(p.removido == '0'){print_registro(p);} //registro nao esta marcado como removido
        p.removido=lixo;
        free(p.nomePessoa);
        free(p.nomeUsuario);

  
    }
        

    fclose(fd);

        
}

