#ifndef GERACAO_PARTICOES_H
#define GERACAO_PARTICOES_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "nomes.h"
#include "cliente.h"

#include "nomes.h"

// Executa o algoritmo de geracao de particoes por Classificacao Interna
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{

    int fim = 0; //variável de controle para saber se arquivo de entrada terminou
    FILE *arq;   //declara ponteiro para arquivo

    //abre arquivo para leitura
    if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL)
    {
        printf("Erro ao abrir arquivo de entrada\n");
    }
    else
    {

        //le primeiro cliente
        TCliente *cin = le_cliente(arq);

        while (!(fim))
        {
            //le o arquivo e coloca no vetor
            TCliente *v[M];

            int i = 0;
            while (!feof(arq) && i < M)
            {
                v[i] = cin;
                cin = le_cliente(arq);
                i++;
            }

            //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
            if (i != M)
            {
                M = i;
            }

            //faz ordenacao
            for (int j = 1; j < M; j++)
            {
                TCliente *c = v[j];
                i = j - 1;
                while ((i >= 0) && (v[i]->cod_cliente > c->cod_cliente))
                {
                    v[i + 1] = v[i];
                    i = i - 1;
                }
                v[i + 1] = c;
            }

            //cria arquivo de particao e faz gravacao
            char *nome_particao = nome_arquivos_saida->nome;
            nome_arquivos_saida = nome_arquivos_saida->prox;

            FILE *p;
            if ((p = fopen(nome_particao, "wb")) == NULL)
            {
                printf("Erro criar arquivo de saida\n");
            }
            else
            {
                for (int i = 0; i < M; i++)
                {
                    salva_cliente(v[i], p);
                }
                fclose(p);
            }
            if (feof(arq))
            {
                fim = 1;
            }
        }
    }
}

void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
}

// Executa o algoritmo de geracao de particoes por Selecao Natural
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
// n: tamanho do reservatorio

typedef struct ListClients
{
    TCliente lista;
    int posicao;
} ListAux;

ListAux menor_part(TCliente *clientes, int max)
{
    //retorna a menor chave da memoria e o indice correspondente a ela
    TCliente aux;
    ListAux index;
    int menor;

    menor = clientes[0].cod_cliente;
    index.posicao = 0;
    aux = clientes[0];

    for (int i = 1; i < max; i++)
    {
        if (clientes[i].cod_cliente < menor)
        {
            menor = clientes[i].cod_cliente;
            index.posicao = i;
            aux = clientes[i];
        }
    }
    index.lista = aux;
    return index;
}

int total_de_particoes(FILE *f)
{
    TCliente *cliente = (TCliente *)malloc(sizeof(TCliente));
    int cont = 0;
    while (!feof(f))
    {
        fread(cliente, sizeof(TCliente), 1, f);
        cont++;
    }
    return cont - 1;
}

void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n)
{
    FILE *arquivoEntrada, *arquivoParticao;
    arquivoEntrada = fopen(nome_arquivo_entrada, "rb");

    if (arquivoEntrada == NULL)
    {
        printf("Erro ao abrir arquivo de entrada\n");
        exit(-1);
    }

    char *nome_arquivo = nome_arquivos_saida->nome;
    nome_arquivos_saida = nome_arquivos_saida->prox;

    ListAux listAux;
    TCliente *memoria, *reservatorio, *aux;

    memoria = (TCliente *)malloc(sizeof(TCliente) * M);
    reservatorio = (TCliente *)malloc(sizeof(TCliente) * n);
    aux = (TCliente *)malloc(sizeof(TCliente));

    int primeiraVez, i, cont_reservatorio, controle_arquivo, total, contador_registros;

    primeiraVez = 1;
    controle_arquivo = 1;
    cont_reservatorio = 0;
    contador_registros = 0;
    total = total_de_particoes(arquivoEntrada);

    sprintf(nome_arquivo, "part_%d.txt", controle_arquivo);

    arquivoParticao = fopen(nome_arquivo, "wb+");

    while (!feof(arquivoEntrada))
    {
        contador_registros++;
        if (primeiraVez)
        {
            rewind(arquivoParticao);
            // Ler M registros do arquivo para a memória
            for (i = 0; i < M; i++)
            {
                fread(&memoria[i], sizeof(TCliente), 1, arquivoEntrada);
            }
            // Selecionar, no array em memória, o registro r com menor chave
            listAux = menor_part(memoria, M);
            // Gravar o registro r na partição de saída
            fwrite(&listAux.lista, sizeof(TCliente), 1, arquivoParticao);
            primeiraVez = 0;
        }
        // Substituir, no array em memória, o registro r pelo próximo registro do arquivo de entrada
        fread(&aux, sizeof(TCliente), 1, arquivoEntrada);
        // Caso a chave deste último seja menor do que a chave recém gravada, gravá-lo no reservatório e substituir, no array em memória, o registro r pelo próximo registro do arquivo de entrada
        if (listAux.lista.cod_cliente > aux->cod_cliente)
        {
            reservatorio[cont_reservatorio].cod_cliente = aux->cod_cliente;
            strcpy(reservatorio[cont_reservatorio].nome, aux->nome);
            cont_reservatorio++;
        }
        else
        {
            memoria[listAux.posicao].cod_cliente = aux->cod_cliente;
            strcpy(memoria[listAux.posicao].nome, aux->nome);
            listAux = menor_part(memoria, M);
            fwrite(&listAux.lista, sizeof(TCliente), 1, arquivoParticao);
        }
        // Caso ainda exista espaço livre no reservatório, voltar ao passo 2
        if (cont_reservatorio == n)
        {
            // fechar a partição de saída
            fclose(arquivoParticao);
            // copiar os registros do reservatório para o array em memória
            for (i = 0; i < cont_reservatorio; i++)
            {
                memoria[i].cod_cliente = reservatorio[i].cod_cliente;
            }

            controle_arquivo++;

            // esvaziar o reservatório

            // abrir nova partição de saída

            if (contador_registros == total)
                break;

            sprintf(nome_arquivo, "part_%d.txt", controle_arquivo);

            arquivoParticao = fopen(nome_arquivo, "wb+");
        }
    }
}

#endif