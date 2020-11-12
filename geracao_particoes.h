#ifndef GERACAO_PARTICOES_H
#define GERACAO_PARTICOES_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "nomes.h"
#include "cliente.h"
#include "stdbool.h"

#include "nomes.h"

typedef struct ClienteAux {
    TCliente* cliente;
     bool congelado;
}ClienteAux;
// Executa o algoritmo de geracao de particoes por Classificacao Interna
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {

    int fim = 0; //variável de controle para saber se arquivo de entrada terminou
    FILE *arq; //declara ponteiro para arquivo

    //abre arquivo para leitura
    if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL) {
        printf("Erro ao abrir arquivo de entrada\n");
    } else {

        //le primeiro cliente
        TCliente *cin = le_cliente(arq);

        while (!(fim)) {
            //le o arquivo e coloca no vetor
            TCliente *v[M];

            int i = 0;
            while (!feof(arq) && i < M) {
                v[i] = cin;
                cin = le_cliente(arq);
                i++;
            }

            //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
            if (i != M) {
                M = i;
            }

            //faz ordenacao
            for (int j = 1; j < M; j++) {
                TCliente *c = v[j];
                i = j - 1;
                while ((i >= 0) && (v[i]->cod_cliente > c->cod_cliente)) {
                    v[i + 1] = v[i];
                    i = i - 1;
                }
                v[i + 1] = c;
            }

            //cria arquivo de particao e faz gravacao
            char *nome_particao = nome_arquivos_saida->nome;
            nome_arquivos_saida = nome_arquivos_saida->prox;

            FILE *p;
            if ((p = fopen(nome_particao, "wb")) == NULL) {
                printf("Erro criar arquivo de saida\n");
            } else {
                for (int i = 0; i < M; i++) {
                    salva_cliente(v[i], p);
                }
                fclose(p);
            }
            if (feof(arq)) {
                fim = 1;
            }
        }
    }
}
int posicao_menor_valor(int *array, int m)
{
    int menor = -1;

    int menorValor = 0;

    for (int a = 0; a < m; a++)
    {
        if (a == 0)
        {
            menor = a;
            menorValor = array[a];
        }
        else
        {
            if (array[a] < menorValor)
            {
                menor = a;
                menorValor = array[a];
            }
        }
    }
    return menor;
}
// Executa o algoritmo de geracao de particoes por Selecao com Substituicao
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {
    FILE *arq; //declara ponteiro para arquivo
   //abre arquivo para leitura
   if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL)
   {
       printf("Erro ao abrir arquivo de entrada\n");
   }
   else
   {
       //le primeiro cliente
       TCliente *cin = le_cliente(arq);
 
       ClienteAux *v= (ClienteAux *) malloc(M * sizeof(ClienteAux));
 
       int i = 0, ultima_posicao = -1;
 
       TCliente *cliente = (TCliente *)malloc(sizeof(TCliente));
       TCliente *posicao = (TCliente *)malloc(sizeof(TCliente));
       char *nome_particao = nome_arquivos_saida->nome;
       nome_arquivos_saida = nome_arquivos_saida->prox;
 
       FILE *p;
 
       if ((p = fopen(nome_particao, "wb")) == NULL)
       {
           printf("Erro criar arquivo de saida\n");
           exit(-1);
       }
 
       while ((cliente = le_cliente(nome_arquivo_entrada)) != NULL)
       {
           if (i < M)
           {
               v[i].cliente = cin;
               cin = le_cliente(arq);
               i++;
           }
           else
           {
               int key = posicao_menor_valor(v->cliente, M);
               printf("\nPosicao do Menor Valor: %d\n", key);
               
               // salva_cliente(posicao, p);
               // v[key] = cliente;
           }
       }
   }
}

// Executa o algoritmo de geracao de particoes por Selecao Natural
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
// n: tamanho do reservatorio
void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n) {
    //TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}



#endif