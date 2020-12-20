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
		Cliente_hash[i]->prox=-1;
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
	Cliente *c =(Cliente *) malloc(sizeof(Cliente));
	// funcao H(x)
	int h = hash(cod_cli,23);
	int contador=0;
	while(!feof(arquivo_dados)){
		c= le_cliente(arquivo_dados);
		contador++;
		if(contador== h){
			break;
		}
	}
	// varrer a posicao encontrada
	while(c->prox!=-1){
		if(c->cod_cliente==cod_cli){
			printf("Cliente encontrado!");
		}
		c=c->prox;
	}

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
//Para inserir novo registro

//Ao passar pelos registros procurando pela chave, guardar o endereço p do
//primeiro nó marcado como LIBERADO (flag ocupado = FALSE )
//Se ao chegar ao final da lista encadeada, a chave não for encontrada, gravar o registro na posição p
//Atualizar ponteiros
//q Nó anterior deve apontar para o registro inserido
//q Nó inserido deve apontar para nó que era apontado pelo nó anterior
	//TODO: Inserir aqui o codigo do algoritmo de insercao
	// cria-se um variavel do tipo cliente para armazenar os valores vindos por parametro
	Cliente *No_inserir =(Cliente *) malloc(sizeof(Cliente));
	No_inserir->cod_cliente=cod_cli;
	strcpy(No_inserir->nome,nome_cli);
	Cliente *No_anterior=(Cliente *) malloc(sizeof(Cliente));
	int posicao=0;
	int p=-1;
	int h = hash(cod_cli,num_registros);
	FILE *arq;
	FILE *arq_hash;
	Cliente *c =(Cliente *) malloc(sizeof(Cliente));
	CompartimentoHash *compartimento = (CompartimentoHash *) malloc(sizeof(CompartimentoHash));
	arq=fopen(nome_arquivo_dados,"rb");
	arq_hash=fopen(nome_arquivo_hash,"rb");

	int aux=0;
	while(!feof(arq_hash)){
			compartimento= le_compartimento(arq_hash);
			if(compartimento==h){
				//compartimento existe, logo iremos procurar se existe um item na  lista encadeada de sua posicao
				while(!feof(arq)){
					c=le_cliente(arq);
					if(aux==h){
						while(c!=-1){
							if(c->status=LIBERADO && p!=-1){
								p=posicao;
							}
							if(cod_cli==c->cod_cliente){
								printf("Cliente já existe, impossivel inserir!");
								break;
							}
							c=c->prox;
							posicao++;
						}
						// caso não exista cliente, podemos inserir.
						if(p!=-1){
							No_inserir->prox=-1;
							c->prox= No_inserir;
							printf("Cliente inserido");
							salva_cliente(c,arq);
							break;
						}
						else{
							while(c!=-1){
								if(c->prox==-1){
									No_inserir->prox=-1;
									c->prox= No_inserir;
									salva_cliente(c,arq);
									printf("Cliente inserido");
									break;
								}
								c=c->prox;
							}
						}
					}
					aux++;
				}
				break;
			}
			//

	}


	fclose(arq_hash);
	fclose(arq);
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
	FILE *arq;
	FILE *arq_hash;
	arq=fopen(nome_arquivo_dados,"rb");
	arq_hash=fopen(nome_arquivo_hash,"rb");
	Cliente *c =(Cliente *) malloc(sizeof(Cliente));
	int h=hash(cod_cli,23);
	int contador=0;
	while(!feof(arq)){
		c=le_cliente(arq);
		if(h==contador){
			while(c!=-1){
				if(c->cod_cliente==cod_cli){
					c=NULL;
					c->status=LIBERADO;
					printf("excluidp");
					break;
				}

				c=c->prox;
			}
			printf("Item não encontrado\n");
		}
		contador++;
	}
	fclose(arq_hash);
	fclose(arq);
    return INT_MAX;
}
int hash(int mat, int tam){
    return mat % tam;
}