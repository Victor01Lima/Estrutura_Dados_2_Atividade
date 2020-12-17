#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include <limits.h>
#include "cliente.h"
#include "encadeamento_exterior.h"


void cria_hash(char *nome_arquivo_hash, int tam)
{
	//TODO: criar a tabela hash
	// cria um vetor dinamicamente do tipo Cliente
	Cliente *Cliente_hash[tam];
	//arquivo de saida é aberto
	FILE *out = fopen("TabelaHash.dat", "wb");
	// laço de repetição para salvar cada posicao do nosso vetor dinamico no arquivo de saida
	for(int i=0 ;i<tam;i++)
	{
		// cada posicao do vetor é definida como NULL
		Cliente_hash[i]=NULL;
		salva_cliente(Cliente_hash[i],out);
	}
	fclose(out);
}

int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados)
{
	//TODO: Inserir aqui o codigo do algoritmo
    return INT_MAX;
}


int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros)
{
	//TODO: Inserir aqui o codigo do algoritmo de insercao
    return INT_MAX;
}

int exclui(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados)
{
	//TODO: Inserir aqui o codigo do algoritmo de remocao
    return INT_MAX;
}
