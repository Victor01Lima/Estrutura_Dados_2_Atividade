#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <limits.h>
#include "cliente.h"
#include "encadeamento_exterior.h"
#include "compartimento_hash.h"
#include "lista_compartimentos.h"

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
		Cliente_hash[i]->prox-1;
		salva_cliente(Cliente_hash[i],out);
	}
	fclose(out);
}

int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados)
{
	//Busca por um registro de chave x :
//1. Calcular o endereço aplicando a função h(x)
//2. Percorrer a lista encadeada associada ao endereço
//3. Comparar a chave de cada nó da lista encadeada com a chave x , até encontrar o nó desejado
//4. Se final da lista for atingido, registro não está lá

	//TODO: Inserir aqui o codigo do algoritmo
	 // abre os arquivos para leitura
	FILE *arquivo_hash= fopen(nome_arquivo_hash,"rb");
	FILE *arquivo_dados= fopen(nome_arquivo_dados,"rb");

	// funcao H(x)
	int h = hash(cod_cli,23);

	while(!feof(arquivo_hash)){

	}
	Cliente *c =(Cliente *) malloc(sizeof(Cliente));




	// fecha os arquivos
	fclose(arquivo_dados);
	fclose(arquivo_hash);
    return INT_MAX;
}


int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros)
{
//	Inserção de um registro de chave x :
//1. Calcular o endereço aplicando a função h(x)
//2. Buscar registro na lista associada ao endereço h(x)
//3. Se registro for encontrado, sinalizar erro
//4. Se o registro não for encontrado, inserir no final da lista
	//TODO: Inserir aqui o codigo do algoritmo de insercao
	// cria-se um variavel do tipo cliente para armazenar os valores vindos por parametro
	int h = hash(cod_cli,num_registros);
	FILE *arq;
	Cliente *c =(Cliente *) malloc(sizeof(Cliente));
	if(arq=fopen(nome_arquivo_dados,"rb")==NULL){
		printf("Erro ao abrir arquivo!\n");
	}

	Cliente *c= le_cliente(arq);



    return INT_MAX;
}

int exclui(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados)
{
//	Exclusão de um registro de chave x :
//1. Calcular o endereço aplicando a função h(x)
//2. Buscar registro na lista associada ao endereço h(x)
//3. Se registro for encontrado, excluir registro
//4. Se o registro não for encontrado, sinalizar erro
	//TODO: Inserir aqui o codigo do algoritmo de remocao
    return INT_MAX;
}
int hash(int mat, int tam){
    return mat % tam;
}